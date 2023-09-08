/*
 * @file three_pin_rs232_read_interface.h
 *
 * @brief Declares a class which implements a serial reader interface.
 *
 * @author Michael Szwaja
 */
//=============================================================================

#ifndef RS232_READ_INTERFACE_THREE_PIN_H_
#define RS232_READ_INTERFACE_THREE_PIN_H_

#include "rs232-read-interface.h"

#include <memory>

class ThreePinRS232ReadInterface : public RS232ReadInterface
{
public:
    ThreePinRS232ReadInterface();
    ~ThreePinRS232ReadInterface();

    ThreePinRS232ReadInterface(const ThreePinRS232ReadInterface &src) = delete;
    ThreePinRS232ReadInterface & operator =(const ThreePinRS232ReadInterface &rhs) = delete;

protected:
    struct impl;
    std::unique_ptr<impl> _pimpl;

public:
    std::string get_statusmsg(DicesRcrs232 error_code);

    /*
     *! @copydoc RS232ReadInterface::Read(
     *      int fd,
     *      uint8_t *response_buffer,
     *      const ssize_t size,
     *      ssize_t *bytes_transferred)
     *
     * Implements timeout and device disconnection functionality.
     */
    DicesRcrs232 Read(
        int fd,
        uint8_t *response_buffer,
        const size_t size,
        ssize_t *bytes_transferred);

    /*
     * Set sequence of characters which will signal the end of a message read
     * from the serial port.
     * @param [in] sequence Byte array which contains terminating sequence.
     * @param [in] size Number of elements that make up terminating sequence.
     * @return Returns zero for success.
     */
    DicesRcrs232 set_terminating_character_sequence(
        const uint8_t *sequence,
        const size_t size);

private:
    /*
     * Checks to see if file descriptor is valid.
     * @param [in] fd file descriptor
     * @return Returns true if the file descriptor is valid
     */
    bool IsValidFileDescriptor(int fd);

    /*
     * Given a message read from the serial port, determine if the terminating
     * sequence has been read.
     * @param [in] response Byte array which will be checked for terminating
     *   sequence.
     * @param [in] size Number of bytes in the message.
     * @param [in, out] equals Set upon function return and notifies the calling
     *   function if response has terminating sequence.
     * @return Returns zero for success.
     */
    DicesRcrs232 HasReadTerminatingSequence(
        const uint8_t *response,
        const size_t size,
        bool *equals);

public:
    int get_max_serial_timeout_limit();
    void set_max_serial_timeout_limit(const int limit);
    int get_max_serial_timeout_limit_exceeded();
    void set_max_serial_timeout_limit_exceeded(const int limit);
};

#endif // RS232_READ_INTERFACE_THREE_PIN_H_
