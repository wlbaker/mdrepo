/**
 * @file rs232.h
 *
 * @author Michael Szwaja
 */
//=============================================================================

#ifndef RS232_H_
#define RS232_H_

#include <memory>
#include <Common/dices-framework-enum.h>
#include "base-communication.h"

#include <Common/dices-framework-enum.h>

#ifdef _WIN32
typedef HANDLE PORTHANDLE;
#else
typedef int PORTHANDLE;
#endif

class RS232ReadInterface;
enum class DicesRcrs232;
enum class DicesRcBaseComm;

class RS232 : public BaseComm
{
public:
    RS232(RS232ReadInterface *serial_impl);
    RS232(
        RS232ReadInterface *serial_impl,
        const char *portname,
        int baudrate,
        int databits,
        rs232_stopbits stopbits,
        int handshaking,
        rs232_parity parity,
        bool enable_hardware_flow_control,
        bool enable_software_flow_control);
    ~RS232();

private:
    RS232(const RS232 &src) = delete;
    RS232 & operator =(const RS232 &rhs) = delete;

protected:
    struct impl;
    std::unique_ptr<impl> _pimpl;

public:
    DicesRcBaseComm Open();
    DicesRcBaseComm Close();
    DicesRcBaseComm Flush();
    DicesRcBaseComm Read(uint8_t *buffer, const size_t buffer_size, ssize_t *bytes_transferred);
    DicesRcBaseComm Send(const uint8_t *buffer, const size_t buffer_size);
    bool IsCTSEnabled();
    bool IsDTREnabled();

    // ACCESSORS AND MUTATORS
    std::string get_portname();
    int get_baudrate();
    int get_databits();
    rs232_stopbits get_stopbits();
    int get_handshaking();
    rs232_parity get_parity();
    bool get_enable_hardware_flow_control();
    bool get_enable_software_flow_control();
    std::string get_statusmsg(DicesRcrs232 error_code);
    int get_port_handle();
    bool get_is_open();

    void set_portname(const std::string &portname);
    void set_baudrate(int baudrate);
    void set_databits(int databits);
    void set_stopbits(rs232_stopbits stopbits);
    void set_handshaking(int handshaking);
    void set_parity(rs232_parity parity);
    void set_enable_hardware_flow_control(bool enable);
    void set_enable_software_flow_control(bool enable);
};

#endif // RS232_H_
