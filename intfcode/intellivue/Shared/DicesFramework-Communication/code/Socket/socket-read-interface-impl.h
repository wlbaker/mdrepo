
#ifndef SOCKET_READ_INTERFACE_IMPL_H_
#define SOCKET_READ_INTERFACE_IMPL_H_

#include "socket-read-interface.h"

#include <memory>
//#include <string>

enum class DicesRcSocket;

class SocketReadImplInterface : public SocketReadInterface
{
public:
    SocketReadImplInterface();
    ~SocketReadImplInterface();

    SocketReadImplInterface(const SocketReadImplInterface &src);
    SocketReadImplInterface & operator =(const SocketReadImplInterface &rhs);

protected:
    struct impl;
    std::unique_ptr<impl> _pimpl;

public:
    std::string get_statusmsg(DicesRcSocket error_code);

    void ResetCounters();

    /**
     *! @copydoc SocketReadInterface::Read(int fd, struct sockaddr_in* psockaddr_in,
     *! char* precv_buf, int recv_buf_max_size, int flags,
     *! ssize_t* pnbytes_transferred)
     *
     * Implements timeout and device disconnection functionality.
     */
    DicesRcSocket Read(
        int fd,
        struct sockaddr_in *psockaddr_in,
        char *precv_buf,
        int recv_buf_max_sized,
        int flags,
        ssize_t *pnbytes_transferred);

    int get_max_socket_timeout_limit();
    void set_max_socket_timeout_limit(const int limit);
    int get_max_socket_timeout_limit_exceeded();
    void set_max_socket_timeout_limit_exceeded(const int limit);
};

#endif // SOCKET_READ_INTERFACE_IMPL_H_
