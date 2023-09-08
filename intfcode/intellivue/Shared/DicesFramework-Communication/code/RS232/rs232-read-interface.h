/**
 * @file rs232_read_interface.h
 *
 * @brief Declares a serial interface. This is a base class for a serial port
 * reader.
 *
 * @author Michael Szwaja
 */
//=============================================================================

#ifndef RS232_READ_INTERFACE_H_
#define RS232_READ_INTERFACE_H_

#include <string>

enum class DicesRcrs232;

class RS232ReadInterface
{
protected:
    // Protected constructor so that no one besides the derived class should
    // instantiates this class.
    RS232ReadInterface() = default;

public:
    virtual ~RS232ReadInterface() = default;

    RS232ReadInterface(const RS232ReadInterface &src) = delete;
    RS232ReadInterface &operator=(const RS232ReadInterface &rhs) = delete;

    /*
     * Reads from the serial port until terminating sequence of characters has
     * been read. File descriptor must be open.
     * @param [in] fd File descriptor of open serial port.
     * @param [in, out] response_buffer Pointer to buffer which will contain
     *   bytes read from the serial port upon function return.
     * @param [in] size Maximum number of bytes the response_buffer can hold.
     * @param [in, out] bytes_transferred Will contain the number of bytes read
     *   from the serial port upon function return.
     * @return Returns zero for success. Depending on the implementation, this
     *   function may also return other values that don't neccessarily mean
     *   failure.
     */
    virtual DicesRcrs232 Read(int fd, uint8_t *response_buffer, const size_t size, ssize_t *bytes_transferred) = 0;
};

#endif // RS232_READ_INTERFACE_H_
