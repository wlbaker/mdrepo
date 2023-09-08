/**
 * @file isocket_read.h
 *
 * @brief Declares a socket interface. This is a base class for a socket
 * reader.
 *
 * @author Michael Szwaja
 */
//=============================================================================

#ifndef SOCKET_READ_INTERFACE_H_
#define SOCKET_READ_INTERFACE_H_

#include <unistd.h>

enum class DicesRcSocket;

class SocketReadInterface
{
protected:
    // Protected constructor so that no one besides a derived class should
    // instantiate this class.
    SocketReadInterface() = default;

public:
    virtual ~SocketReadInterface() = default;

    SocketReadInterface(const SocketReadInterface &src) = delete;
    SocketReadInterface & operator =(const SocketReadInterface &rhs) = delete;

  /**
   * Reads socket and stores response in buffer.
   * @param [in] fd File descriptor of open socket
   * @param [in] psockaddr_in Pointer to socket address information.
   * @param [in] precv_buf Pointer to buffer that will contain message upon
   *   function return.
   * @param [in] recv_buf_max_size The number of bytes allocated for the
   *   precv_buf.
   * @param [in] flags Mask of zero or more flags. see recvfrom() function
   *   documentation.
   * @param [in, out] pnbytes_transferred Number of bytes read into receive
   *   buffer.
   * @return Returns zero for success.
   */
    virtual DicesRcSocket Read(
        int fd,
        struct sockaddr_in *psockaddr_in,
        char *precv_buf,
        int recv_buf_max_sized,
        int flags,
        ssize_t *pnbytes_transferred) = 0;
};

#endif // SOCKET_READ_INTERFACE_H_
