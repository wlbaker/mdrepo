/**
 * @file socket.h
 *
 * @brief Declares a class which handles all socket operations.
 *
 * @author Michael Szwaja
 */
//=============================================================================

#ifndef SOCKET_H_
#define SOCKET_H_

#include <memory>
//#include <string>

#include "base-communication.h"

enum class DicesRcSocket;
enum class DicesRcBaseComm;
class SocketReadInterface;
struct timeval;
struct sockaddr_in;

enum SocketIPProtocol
{
  SOCKET_IPPROTO_IP = 0, // IPPROTO_IP dummy for IP
  SOCKET_IPPROTO_UDP, // IPPROTO_UDP user datagram protocol
  SOCKET_IPPROTO_TCP // IPPROTO_TCP
};

class Socket : public BaseComm
{
public:
    Socket(SocketReadInterface *psocket_impl);
    Socket(SocketReadInterface *psocket_impl,
        SocketIPProtocol protocol,
        bool enable_blocking_io,
        bool enable_bind_socket,
        timeval *recv_timeout,
        timeval *send_timeout,
        int sendto_flags,
        int recvfrom_flags,
        std::string ip_address,
        uint16_t port_number);
    ~Socket();

    Socket(const Socket &src) = delete;
    Socket & operator =(const Socket &rhs) = delete;

protected:
    struct impl;
    std::unique_ptr<impl> _pimpl;

public:
    DicesRcBaseComm Open();

    DicesRcBaseComm Close();

    DicesRcBaseComm Send(const uint8_t *buffer, const size_t buffer_size);

    DicesRcBaseComm Read(uint8_t *buffer, const size_t buffer_size, ssize_t *bytes_transferred);

    /**
     * Set duration of timeout when sendto() function is called. This timeout
     * is only effective with socket is blocking. A zero value will never
     * timeout.
     * @param [in] tv Pointer to timeval structure.
     * @return Returns zero for success.
     */
    DicesRcSocket set_send_timeout(const timeval *tv);

    /**
     * Set duration of timeout when recvfrom() function is called. This timeout
     * is only effective with socket is blocking. A zero value will never
     * timeout.
     * @param [in] tv Pointer to timeval structure.
     * @return Returns zero for success.
     */
    DicesRcSocket set_recv_timeout(const timeval *tv);

private:
    /**
     * Precondition: handle must point to an open socket. Sets socket to
     * to non blocking.
     * @return Returns zero for success.
     */
    DicesRcSocket SetNonBlocking();

    /**
     * Precondition: Socket is open and file descriptor is valid. Sets receive
     * timeout for socket. TODO Only works when socket is set to block?
     * @param [in] tv Duration at which the socket receive operation should
     *   timeout.
     * @return Returns zero for success.
     */
    DicesRcSocket SetReceiveTimeout();

    /**
     * Precondition: Socket is open and file descriptor is valid. Sets send
     * timeout for socket. TODO Only works when socket is set to block?
     * @param [in] tv Duration at which the socket send operation should
     *   timeout.
     * @return Returns zero for success.
     */
    DicesRcSocket SetSendTimeout();

public:
  void set_port_number(const uint16_t port_number);
  void set_ip_address(const std::string ip_address);
  void set_enable_blocking_io(bool blocking);
  void set_socket_protocol(SocketIPProtocol protocol);
  void set_sendto_flags(int sendto_flags);
  void set_recvfrom_flags(int recvfrom_flags);
  int get_socket_fd();
  void set_enable_bind_socket(bool enable_bind_socket);
};

#endif // SOCKET_H_
