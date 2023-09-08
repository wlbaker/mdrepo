/*
 * @file length_field_rs232_read_interface.h
 *
 * @brief Declares a class which implements a serial reader interface.
 *
 * @author Robert England
 */
//=============================================================================

#ifndef RS232_READ_INTERFACE_LENGTH_FIELD_H_
#define RS232_READ_INTERFACE_LENGTH_FIELD_H_

#include "rs232-read-interface.h"

#include <memory>

class LengthFieldRS232ReadInterface : public RS232ReadInterface
{
public:
    LengthFieldRS232ReadInterface(
        int prefix_size,
        int length_field_size,
        int suffix_size,
        bool length_includes_pre_suf);
    ~LengthFieldRS232ReadInterface();

    LengthFieldRS232ReadInterface(const LengthFieldRS232ReadInterface &src) = default;
    LengthFieldRS232ReadInterface & operator =(const LengthFieldRS232ReadInterface &rhs) = default;

protected:
    struct impl;
    std::unique_ptr<impl> _pimpl;

public:
    std::string get_statusmsg(DicesRcrs232 error_code);

    /*
     *! @copydoc RS232ReadInterface::Read(int fd, uint8_t* response_buffer,
     * const ssize_t size, ssize_t* bytes_transferred)
     *
     * Implements timeout and device disconnection functionality.
     */
    DicesRcrs232 Read(
        int fd,
        uint8_t *response_buffer,
        const size_t size,
        ssize_t *bytes_transferred);

private:
    /*
     * Checks to see if file descriptor is valid.
     * @param [in] fd file descriptor
     * @return Returns true if the file descriptor is valid
     */
    bool IsValidFileDescriptor(int fd);

public:
    int get_max_serial_timeout_limit();
    void set_max_serial_timeout_limit(const int limit);
    int get_max_serial_timeout_limit_exceeded();
    void set_max_serial_timeout_limit_exceeded(const int limit);
};

#endif // RS232_READ_INTERFACE_LENGTH_FIELD_H_
