
#include "socket.h"

#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <iostream>
#include <errno.h>
#include <sys/time.h>
#include <sys/fcntl.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <thread>
#include <chrono>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>

#include "socket-read-interface.h"
#include "rc-socket.h"
#include "rc-base-communication.h"

static const int kInvalidFileDescriptor = -1;
static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

struct Socket::impl
{
    // MEMBERS
    SocketReadInterface *_socket_read_impl;
    int _socket_fd;
    SocketIPProtocol _socket_protocol;
    bool _enable_blocking_io;
    bool _enable_bind_socket;
    timeval *_send_timeout;
    timeval *_recv_timeout;
    int _sendto_flags;
    int _recvfrom_flags;

    struct sockaddr_in *_psockaddr_in;
    uint16_t _port_number;
    std::string _ip_address;

    // CTOR + DTOR
    impl(SocketReadInterface* psocket_impl)
    : _socket_read_impl(psocket_impl),
      _socket_fd(kInvalidFileDescriptor),
      _socket_protocol(SOCKET_IPPROTO_UDP),
      _enable_blocking_io(false),
      _enable_bind_socket(false),
      _sendto_flags(0),
      _recvfrom_flags(0),
      _port_number(0)
    {
        _recv_timeout = new (std::nothrow) timeval();
        _send_timeout = new (std::nothrow) timeval();
        _psockaddr_in = new (std::nothrow) sockaddr_in();
    }

    impl(
        SocketReadInterface *psocket_impl,
        SocketIPProtocol protocol,
        bool enable_blocking_io,
        bool enable_bind_socket,
        timeval *recv_timeout,
        timeval *send_timeout,
        int sendto_flags,
        int recvfrom_flags,
        std::string ip_address,
        uint16_t port_number)
    : _socket_read_impl(psocket_impl),
      _socket_fd(kInvalidFileDescriptor),
      _socket_protocol(protocol),
      _enable_blocking_io(enable_blocking_io),
      _enable_bind_socket(enable_bind_socket),
      _sendto_flags(sendto_flags),
      _recvfrom_flags(recvfrom_flags),
      _ip_address(ip_address),
      _port_number(port_number)
    {
        if (recv_timeout)
        {
            _recv_timeout = new (std::nothrow) timeval(*recv_timeout);
        }
        else
        {
            _recv_timeout = new (std::nothrow) timeval();
        }

        if (send_timeout)
        {
            _send_timeout = new (std::nothrow) timeval(*send_timeout);
        }
        else
        {
            _send_timeout = new (std::nothrow) timeval();
        }

        _psockaddr_in = new (std::nothrow) sockaddr_in();
    }

    ~impl()
    {
        delete _recv_timeout;
        delete _send_timeout;
        delete _psockaddr_in;
    }

    // METHODS
    DicesRcBaseComm Open()
    {
        static const char* sfn = "Socket::Open()";

        if (!_psockaddr_in)
        {
            LOG4CPLUS_DEBUG(root_logger,
                sfn << " Pointer to sockaddr_in is null.");
            return DicesRcBaseComm::SOCKADDR_IN_POINTER_IS_NULL_FAILURE;
        }

        // Open socket
        switch (_socket_protocol)
        {
        case SOCKET_IPPROTO_IP:
            // TODO This protocol was not tested. Test and make changes when
            // necessary.
            _socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
            break;
        case SOCKET_IPPROTO_UDP:
            _socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            break;
        case SOCKET_IPPROTO_TCP:
            // TODO This protocol was not tested. Test and make changes when
            // necessary.
            _socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            break;
        default:
            // This should not be reached
            LOG4CPLUS_ERROR(root_logger,
                sfn << " Unknown socket protocol (" << _socket_protocol << ")");
            return DicesRcBaseComm::UNKNOWN_IP_PROTOCOL_FAILURE;
        }

        if (_socket_fd == -1)
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " socket error " << strerror(errno));
            return DicesRcBaseComm::OPEN_SOCKET_FAILURE;
        }

        if (!_enable_blocking_io)
        {
            DicesRcSocket status = SetNonBlocking();
            if (status != DicesRcSocket::OK)
            {
                LOG4CPLUS_ERROR(root_logger,
                    sfn << " " << DicesRcSocketStatusMessage::DicesRcSocketToString(status));

                DicesRcBaseComm base_comm_status = Close();
                if (base_comm_status != DicesRcBaseComm::OK)
                {
                    LOG4CPLUS_ERROR(root_logger,
                        sfn << " " << DicesRcBaseCommStatusMessage::DicesRcBaseCommToString(base_comm_status));
                }
                return DicesRcBaseComm::SET_NONBLOCKING_IO_FAILURE;
            }
        }
        else
        {
            // The timeval must be set to zero to block forever, otherwise the timeout
            // time applies.
            DicesRcSocket status = SetReceiveTimeout();
            if (status != DicesRcSocket::OK)
            {
                LOG4CPLUS_ERROR(root_logger,
                    sfn << " " << DicesRcSocketStatusMessage::DicesRcSocketToString(status));

                DicesRcBaseComm base_comm_status = Close();
                if (base_comm_status != DicesRcBaseComm::OK)
                {
                    LOG4CPLUS_ERROR(root_logger,
                    sfn << " " << DicesRcBaseCommStatusMessage::DicesRcBaseCommToString(base_comm_status));
                }
                return DicesRcBaseComm::SET_READ_TIMEOUT_FAILURE;
            }

            status = SetSendTimeout();
            if (status != DicesRcSocket::OK)
            {
                LOG4CPLUS_ERROR(root_logger,
                    sfn << " " << DicesRcSocketStatusMessage::DicesRcSocketToString(status));

                DicesRcBaseComm base_comm_status = Close();
                if (base_comm_status != DicesRcBaseComm::OK)
                {
                    LOG4CPLUS_ERROR(root_logger,
                        sfn << " " << DicesRcBaseCommStatusMessage::DicesRcBaseCommToString(base_comm_status));
                }
                return DicesRcBaseComm::SET_SEND_TIMEOUT_FAILURE;
            }
        }

        // Clear everything for new socket address
        memset(_psockaddr_in, 0, sizeof (*_psockaddr_in));

        _psockaddr_in->sin_family = AF_INET;
        _psockaddr_in->sin_port = htons(_port_number);

        // IP address string which contains IP address NULL for
        // INADDR_ANY (server) or "nnn.nnn.nnn.nnn".
        if (_ip_address.empty())
        {
            _psockaddr_in->sin_addr.s_addr = htonl(INADDR_ANY);
        }
        else
        {
            int ixret = inet_aton(_ip_address.c_str(), &_psockaddr_in->sin_addr);
            if (!ixret)
            {
                LOG4CPLUS_ERROR(root_logger,
                    sfn << " inet_aton error (" << ixret << ")");

                DicesRcBaseComm base_comm_status = Close();
                if (base_comm_status != DicesRcBaseComm::OK)
                {
                    LOG4CPLUS_ERROR(root_logger,
                        sfn << " " << DicesRcBaseCommStatusMessage::DicesRcBaseCommToString(base_comm_status));
                }
                return DicesRcBaseComm::CONVERT_IP_ADDRESS_TO_STRUCT_IN_ADDR_FAILURE;
            }
        }

        if (_enable_bind_socket)
        {
            int bind_status = bind(
                _socket_fd,
                reinterpret_cast<struct sockaddr *>(_psockaddr_in),
                sizeof (*_psockaddr_in));
            if (bind_status == -1)
            {
                LOG4CPLUS_ERROR(root_logger,
                    sfn << " bind error " << strerror(errno));

                DicesRcBaseComm base_comm_status = Close();
                if (base_comm_status != DicesRcBaseComm::OK)
                {
                    LOG4CPLUS_ERROR(root_logger,
                        sfn << " " << DicesRcBaseCommStatusMessage::DicesRcBaseCommToString(base_comm_status));
                }
                return DicesRcBaseComm::BIND_IP_ADDRESS_TO_SOCKET_FAILURE;
            }
        }

        return DicesRcBaseComm::OK;
    }

    DicesRcBaseComm Close()
    {
        static const char* sfn = "Socket::Close()";
        if (_socket_fd != kInvalidFileDescriptor &&
            close(_socket_fd))
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " close error " << strerror(errno));
            return DicesRcBaseComm::FAIL;
        }

        _socket_fd = kInvalidFileDescriptor;
        return DicesRcBaseComm::OK;
    }

    DicesRcBaseComm Send(const uint8_t *buffer, const size_t buffer_size)
    {
        static const char* sfn = "Socket::Send()";

        if (!buffer)
        {
            LOG4CPLUS_DEBUG(root_logger,
                sfn << " pointer to buffer is null");
            return DicesRcBaseComm::BAD_FUNCTION_ARGUMENT;
        }

        socklen_t slen = sizeof (*_psockaddr_in);

        ssize_t total_nbytes = 0;
        unsigned int timeout_counter = 0;
        const unsigned int kmax_timeouts = 100;
        while (total_nbytes < buffer_size)
        {
            errno = 0;
            ssize_t nbytes = sendto(
                _socket_fd,
                buffer,
                buffer_size,
                _sendto_flags,
                reinterpret_cast<const struct sockaddr *>(_psockaddr_in),
                slen);
            if (nbytes < 0)
            {
                if (errno != EAGAIN)
                {
                    LOG4CPLUS_ERROR(root_logger,
                      sfn << " sendto() error " << strerror(errno));
                    return DicesRcBaseComm::SEND_FAILURE;
                }
                else
                {
                    // TODO I didn't realize a non blocking socket could timeout with
                    // EAGAIN where it would normally block and wait. Try to send buffer
                    // for about 10 seconds. If ten seconds is reached, return with
                    // failure.
                    timeout_counter++;
                    LOG4CPLUS_WARN(root_logger, sfn << " sendto() error " << strerror(errno));
                    if (timeout_counter >= kmax_timeouts)
                    {
                        LOG4CPLUS_ERROR(root_logger,
                            sfn << " Failed to sendto() Maximum number of timeouts reached.");
                        return DicesRcBaseComm::SEND_FAILURE;
                    }

                    // Sleep for one tenth of a second.
                    std::this_thread::sleep_for(std::chrono::microseconds(100000));
                }
            }
            else
            {
                total_nbytes += nbytes;
            }
        }

        return DicesRcBaseComm::OK;
    }

    DicesRcBaseComm Read(uint8_t *buffer, const size_t buffer_size, ssize_t *bytes_transferred)
    {
        static const char* sfn = "Socket::Read()";

        if (!bytes_transferred)
        {
            LOG4CPLUS_DEBUG(root_logger,
                sfn << " Number of bytes transferred is pointer to null");
            return DicesRcBaseComm::BAD_FUNCTION_ARGUMENT;
        }

        if (!_socket_read_impl)
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " Socket implementation is pointer to null");
            return DicesRcBaseComm::READ_FUNCTION_NOT_IMPLEMENTED_FAILURE;
        }

        if (!buffer)
        {
            LOG4CPLUS_DEBUG(root_logger,
                sfn << " Receive buffer is a pointer to null");
            return DicesRcBaseComm::BAD_FUNCTION_ARGUMENT;
        }

        DicesRcSocket retcode =
            _socket_read_impl->Read(
                _socket_fd,
                _psockaddr_in,
                reinterpret_cast<char *>(buffer),
                buffer_size,
                _recvfrom_flags,
                bytes_transferred);
        if (retcode != DicesRcSocket::OK)
        {
            LOG4CPLUS_WARN(root_logger,
                sfn << " " << DicesRcSocketStatusMessage::DicesRcSocketToString(retcode));

            if (retcode == DicesRcSocket::READ_TIMEOUT)
            {
                return DicesRcBaseComm::READ_TIMEOUT;
            }

            if (retcode == DicesRcSocket::DEVICE_DISCONNECTION)
            {
                return DicesRcBaseComm::DEVICE_DISCONNECTION;
            }

            return DicesRcBaseComm::READ_FAILURE;
        }

        return DicesRcBaseComm::OK;
    }

    /**
     * Set duration of timeout when sendto() function is called. This timeout
     * is only effective with socket is blocking. A zero value will never
     * timeout.
     * @param [in] tv Pointer to timeval structure.
     * @return Returns zero for success.
     */
    DicesRcSocket set_send_timeout(const timeval *tv)
    {
        static const char *sfn = "Socket::set_send_timeout()";

        if (!tv)
        {
            LOG4CPLUS_DEBUG(root_logger,
                sfn << " tv is pointer to null");
            return DicesRcSocket::BAD_FUNCTION_ARGUMENT;
        }

        if (!_send_timeout)
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " send timeout is pointer to null");
            return DicesRcSocket::SEND_TIMEOUT_IS_A_NULL_POINTER;
        }

        memcpy(_send_timeout, tv, sizeof(*_send_timeout));

        return DicesRcSocket::OK;
    }

    /**
     * Set duration of timeout when recvfrom() function is called. This timeout
     * is only effective with socket is blocking. A zero value will never
     * timeout.
     * @param [in] tv Pointer to timeval structure.
     * @return Returns zero for success.
     */
    DicesRcSocket set_recv_timeout(const timeval *tv)
    {
        static const char *sfn = "Socket::set_recv_timeout()";

        if (!tv)
        {
            LOG4CPLUS_DEBUG(root_logger,
                sfn << " tv is pointer to null");
            return DicesRcSocket::BAD_FUNCTION_ARGUMENT;
        }

        if (!_recv_timeout)
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " recv timeout is pointer to null");
            return DicesRcSocket::RECV_TIMEOUT_IS_A_NULL_POINTER;
        }

        memcpy(_recv_timeout, tv, sizeof(*_recv_timeout));

        return DicesRcSocket::OK;
    }

    /**
     * Precondition: handle must point to an open socket. Sets socket to
     * to non blocking.
     * @return Returns zero for success.
     */
    DicesRcSocket SetNonBlocking()
    {
        static const char *sfn = "Socket::SetNonBlocking()";
        int flags = 0;
        int istat = 0;

        // If O_NONBLOCK is defined, then set the flags using the Posix way
#if defined(O_NONBLOCK)
        // Get current flags from file descriptor
        flags = fcntl(_socket_fd, F_GETFL, 0);
        if (flags == -1)
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " fcntl error: " << strerror(errno));
            return DicesRcSocket::FAIL;
        }

        // Set O_NONBLOCK with the old flags
        istat = fcntl(_socket_fd, F_SETFL, flags | O_NONBLOCK);
        if (istat == -1)
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " fcntl error: " << strerror(errno));
            return DicesRcSocket::FAIL;
        }

#else
        // Otherwise, use the old way of doing it
        flags = 1;

        istat = ioctl(_socket_fd, FIOBIO, &flags);
        if (istat == -1)
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " ioctl error: " << strerror(errno));
            return DicesRcSocket::FAIL;
        }

#endif

        return DicesRcSocket::OK;
    }

    /**
     * Precondition: Socket is open and file descriptor is valid. Sets receive
     * timeout for socket. TODO Only works when socket is set to block?
     * @param [in] tv Duration at which the socket receive operation should
     *   timeout.
     * @return Returns zero for success.
     */
    DicesRcSocket SetReceiveTimeout()
    {
        static const char *sfn = "Socket::SetReceiveTimeout()";

        if (!_recv_timeout)
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " recv timeout is pointer to null");
            return DicesRcSocket::RECV_TIMEOUT_IS_A_NULL_POINTER;
        }

        if (setsockopt(
            _socket_fd,
            SOL_SOCKET,
            SO_RCVTIMEO,
            _recv_timeout,
            sizeof (*_recv_timeout)) < 0)
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " setsockopt error: " << strerror(errno));
            return DicesRcSocket::FAIL;
        }

        return DicesRcSocket::OK;
    }

    /**
     * Precondition: Socket is open and file descriptor is valid. Sets send
     * timeout for socket. TODO Only works when socket is set to block?
     * @param [in] tv Duration at which the socket send operation should
     *   timeout.
     * @return Returns zero for success.
     */
    DicesRcSocket SetSendTimeout()
    {
        static const char *sfn = "Socket::SetSendTimeout()";

        if (!_send_timeout)
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " send timeout is pointer to null");
            return DicesRcSocket::SEND_TIMEOUT_IS_A_NULL_POINTER;
        }

        if (setsockopt(
            _socket_fd,
            SOL_SOCKET,
            SO_SNDTIMEO,
            _send_timeout,
            sizeof (*_send_timeout)) < 0)
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " setsockopt error: " << strerror(errno));
            return DicesRcSocket::FAIL;
        }

        return DicesRcSocket::OK;
    }
};

Socket::Socket(SocketReadInterface *psocket_impl)
: _pimpl(new impl(psocket_impl))
{
}

Socket::Socket(
    SocketReadInterface *psocket_impl,
    SocketIPProtocol protocol,
    bool enable_blocking_io,
    bool enable_bind_socket,
    timeval *recv_timeout,
    timeval *send_timeout,
    int sendto_flags,
    int recvfrom_flags,
    std::string ip_address,
    uint16_t port_number)
: _pimpl(new impl(
    psocket_impl,
    protocol,
    enable_blocking_io,
    enable_bind_socket,
    recv_timeout,
    send_timeout,
    sendto_flags,
    recvfrom_flags,
    ip_address,
    port_number))
{
}

Socket::~Socket()
{
}

DicesRcBaseComm Socket::Open()
{
    return _pimpl->Open();
}

DicesRcBaseComm Socket::Close()
{
    return _pimpl->Close();
}

DicesRcBaseComm Socket::Send(const uint8_t *buffer, const size_t buffer_size)
{
    return _pimpl->Send(buffer, buffer_size);
}

DicesRcBaseComm Socket::Read(uint8_t *buffer, const size_t buffer_size, ssize_t *bytes_transferred)
{
    return _pimpl->Read(buffer, buffer_size, bytes_transferred);
}

DicesRcSocket Socket::set_send_timeout(const timeval *tv)
{
    return _pimpl->set_send_timeout(tv);
}

DicesRcSocket Socket::set_recv_timeout(const timeval *tv)
{
    return _pimpl->set_recv_timeout(tv);
}

DicesRcSocket Socket::SetNonBlocking()
{
    return _pimpl->SetNonBlocking();
}

DicesRcSocket Socket::SetReceiveTimeout()
{
    return _pimpl->SetReceiveTimeout();
}

DicesRcSocket Socket::SetSendTimeout()
{
    return _pimpl->SetSendTimeout();
}

void Socket::set_port_number(const uint16_t port_number)
{
    _pimpl->_port_number = port_number;
}

void Socket::set_ip_address(const std::string ip_address)
{
    _pimpl->_ip_address = ip_address;
}

void Socket::set_enable_blocking_io(bool blocking)
{
    _pimpl->_enable_blocking_io = blocking;
}

void Socket::set_socket_protocol(SocketIPProtocol protocol)
{
    _pimpl->_socket_protocol = protocol;
}

void Socket::set_sendto_flags(int sendto_flags)
{
    _pimpl->_sendto_flags = sendto_flags;
}

void Socket::set_recvfrom_flags(int recvfrom_flags)
{
    _pimpl->_recvfrom_flags = recvfrom_flags;
}

int Socket::get_socket_fd()
{
    return _pimpl->_socket_fd;
}

void Socket::set_enable_bind_socket(bool enable_bind_socket)
{
    _pimpl->_enable_bind_socket = enable_bind_socket;
}
