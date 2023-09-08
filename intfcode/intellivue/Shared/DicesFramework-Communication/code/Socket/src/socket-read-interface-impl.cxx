
#include "socket-read-interface-impl.h"

#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>

#include "rc-socket.h"

static const int kMaxSocketTimeoutLimit = 100000;
static const int kMaxSocketTimeoutLimitExceeded = 2;
static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

struct SocketReadImplInterface::impl {
    // MEMBERS
    int _socket_recvfrom_timeout_count;
    int _socket_recvfrom_timeout_exceeded_count;
    int _max_socket_timeout_limit;
    int _max_socket_timeout_limit_exceeded;

    // CTOR + DTOR
    impl()
    : _socket_recvfrom_timeout_count(0),
      _socket_recvfrom_timeout_exceeded_count(0),
      _max_socket_timeout_limit(kMaxSocketTimeoutLimit),
      _max_socket_timeout_limit_exceeded(kMaxSocketTimeoutLimitExceeded)
    {
    }

    ~impl() = default;

    // METHODS
    void ResetCounters()
    {
        _socket_recvfrom_timeout_count = 0;
        _socket_recvfrom_timeout_exceeded_count = 0;
    }

    DicesRcSocket Read(
        int fd,
        struct sockaddr_in *psockaddr_in,
        char *precv_buf,
        int recv_buf_max_size,
        int flags,
        ssize_t *pnbytes_transferred)
    {
        static const char* sfn = "SocketReadImplInterface::Read()";

        if (!pnbytes_transferred)
        {
            LOG4CPLUS_DEBUG(root_logger,
                sfn << " Pointer to number of bytes transferred is null.");
          return DicesRcSocket::BAD_FUNCTION_ARGUMENT;
        }
        *pnbytes_transferred = 0;

        socklen_t slen = sizeof(*psockaddr_in);
        DicesRcSocket istat = DicesRcSocket::OK;

        *pnbytes_transferred = recvfrom(
            fd,
            reinterpret_cast<char *>(precv_buf),
            recv_buf_max_size,
            flags,
            reinterpret_cast<struct sockaddr *>(psockaddr_in),
            &slen);

        if (*pnbytes_transferred >= 0) {
            _socket_recvfrom_timeout_count = 0;
            _socket_recvfrom_timeout_exceeded_count = 0;
        }

        if (*pnbytes_transferred == -1)
        {
            // -1 could cause problems, set back to zero
            *pnbytes_transferred = 0;

            // TODO This errno condition should work, but has not been tested
            // since this class became a tool
            if (errno == EAGAIN)
            {
                _socket_recvfrom_timeout_count++;
                if (_socket_recvfrom_timeout_exceeded_count >= _max_socket_timeout_limit_exceeded)
                {
                    _socket_recvfrom_timeout_exceeded_count = 0;
                    istat = DicesRcSocket::DEVICE_DISCONNECTION;
                }
                else if(_socket_recvfrom_timeout_count >= _max_socket_timeout_limit)
                {
                    _socket_recvfrom_timeout_exceeded_count++;
                    _socket_recvfrom_timeout_count = 0;
                    istat = DicesRcSocket::READ_TIMEOUT;
                }
            }
            else
            {
                LOG4CPLUS_ERROR(root_logger,
                    sfn << " recvfrom error: " << strerror(errno));
                istat = DicesRcSocket::FAIL;
            }
        }

        return istat;
    }
};

SocketReadImplInterface::SocketReadImplInterface()
: SocketReadInterface(),
  _pimpl(new impl())
{
}

SocketReadImplInterface::~SocketReadImplInterface()
{
}

std::string SocketReadImplInterface::get_statusmsg(DicesRcSocket error_code)
{
  return DicesRcSocketStatusMessage::DicesRcSocketToString(error_code);
}

int SocketReadImplInterface::get_max_socket_timeout_limit()
{
  return _pimpl->_max_socket_timeout_limit;
}

void SocketReadImplInterface::set_max_socket_timeout_limit(const int limit)
{
  _pimpl->_max_socket_timeout_limit = limit;
}

int SocketReadImplInterface::get_max_socket_timeout_limit_exceeded()
{
  return _pimpl->_max_socket_timeout_limit_exceeded;
}

void SocketReadImplInterface::set_max_socket_timeout_limit_exceeded(const int limit)
{
  _pimpl->_max_socket_timeout_limit_exceeded = limit;
}

void SocketReadImplInterface::ResetCounters()
{
    _pimpl->ResetCounters();
}

DicesRcSocket SocketReadImplInterface::Read(
    int fd,
    struct sockaddr_in *psockaddr_in,
    char *precv_buf,
    int recv_buf_max_size,
    int flags,
    ssize_t *pnbytes_transferred)
{
    _pimpl->Read(fd, psockaddr_in, precv_buf, recv_buf_max_size, flags, pnbytes_transferred);
}
