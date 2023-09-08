/**
 * @file rs232.h
 *
 * @author Michael Szwaja
 */
//=============================================================================

#include "rs232.h"

#ifdef _WIN32
#   include <windows.h>
#   include <time.h>
#   include <string.h>
#   include <stdio.h>
#else
#   include <string>
#   include <iostream>
#   include <sstream>
#   include <time.h>
#   include <stdio.h>
#   include <string.h>
#   include <termios.h>
#   include <sys/ioctl.h>
#   include <unistd.h>
#   include <fcntl.h>
#   include <sys/types.h>
#   include <sys/stat.h>
#   include <limits.h>
#endif

#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <errno.h>

#include "rc-base-communication.h"
#include "rc-rs232.h"
#include "rs232-read-interface.h"

static const char *kDefaultPortName = "/dev/ttyS0";
static const int kDefaultBaudrate = 115200;
static const int kDefaultDataBits = 8;
static const rs232_parity kDefaultParity = parity_none;
static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

/*
 * IMPLEMENTATION
 */
struct RS232::impl
{
    // MEMBER VARS
    std::string _statusmsg;
    std::string _portname;
    int _baudrate;
    int _databits;
    rs232_stopbits _stopbits;
    int _handshaking;
    rs232_parity _parity;
    bool _enable_hardware_flow_control;
    bool _enable_software_flow_control;
    RS232ReadInterface *_serial_read_impl;
    struct termios *_old_port_settings;
    PORTHANDLE _port_handle;
    bool _is_open;

    // CTOR + DTOR
    impl(RS232ReadInterface* serial_impl)
    : _serial_read_impl(serial_impl),
      _portname(kDefaultPortName),
      _baudrate(kDefaultBaudrate),
      _databits(kDefaultDataBits),
      _stopbits(one_stopbit),
      _handshaking(0),
      _parity(kDefaultParity),
      _enable_hardware_flow_control(false),
      _enable_software_flow_control(false),
      _port_handle(-1),
      _is_open(false)
    {
        _old_port_settings = new (std::nothrow) termios();
    }

    impl(
        RS232ReadInterface *serial_impl,
        const char *portname,
        int baudrate,
        int databits,
        rs232_stopbits stopbits,
        int handshaking,
        rs232_parity parity,
        bool enable_hardware_flow_control,
        bool enable_software_flow_control)
    : _serial_read_impl(serial_impl),
      _portname(portname),
      _baudrate(baudrate),
      _databits(databits),
      _stopbits(stopbits),
      _handshaking(handshaking),
      _parity(parity),
      _enable_hardware_flow_control(enable_hardware_flow_control),
      _enable_software_flow_control(enable_software_flow_control),
      _port_handle(-1),
      _is_open(false)
    {
        _old_port_settings = new (std::nothrow) termios();
    }

    ~impl()
    {
        delete _old_port_settings;

        _old_port_settings = nullptr;
    }

    // METHODS
    DicesRcBaseComm Open()
    {
        static const char* sfn = "RS232::Open()";

#ifdef _WIN32
        LOG4CPLUS_ERROR(root_logger,
            sfn << " may need to be modified for Windows. "
            "Modify windows RS232::FlushComport() as well. -Mike");
        _port_handle = -1;
        return DicesRcBaseComm::FAIL;

        stringstream ss;
        DCB port_settings = { 0 };
        COMMTIMEOUTS cptimeouts = { 0 };

        if (_is_open)
        {
            LOG4CPLUS_WARN(root_logger,
                sfn << " Port " << _portname << " already open");
          return DicesRcBaseComm::OK;
        }

        const int kdci_len = 64;
        char _sdci[kdci_len] = { 0 }; // Device control information

        switch(_baudrate)
        {
            case 110:
            case 300:
            case 600:
            case 1200:
            case 2400:
            case 4800:
            case 9600:
            case 19200:
            case 38400:
            case 57600:
            case 115200:
            case 128000:
            case 256000:
                break;
            default:
                LOG4CPLUS_ERROR(root_logger,
                    sfn << " Invalid baudrate " << _baudrate);
                return DicesRcBaseComm::INVALID_BAUD_RATE_FAILURE;
        }

        std::string baudrate_str = std::to_string(_baudrate);
        std::string complete_str = "baud=" + baudrate_str + " data=8 parity=N stop=1";

        strncpy(_sdci, complete_str.c_str(), kdci_len);
        _sdci[kdci_len - 1] = 0;

        _port_handle = CreateFileA(
            _portname.c_str(),
            GENERIC_READ | GENERIC_WRITE,
            0, // no share
            0, // no security
            OPEN_EXISTING,
            0, // no threads
            0); // no templates

        if (_port_handle == INVALID_HANDLE_VALUE)
        {
            int lasterr = GetLastError();
            char errmsg [256] = "";
            ss << sfn << " unable to open comport "
                << _portname
                << " (" << lasterr << ")" << std::endl;
            FormatMessage(
                FORMAT_MESSAGE_FROM_SYSTEM,
                0,
                lasterr,
                0,
                errmsg,
                sizeof (errmsg),
                0);

            ss << errmsg;
            LOG4CPLUS_ERROR(root_logger, ss.str());

            _port_handle = -1;

            return DicesRcBaseComm::OPEN_PORT_FAILURE;
        }

        port_settings.DCBlength = sizeof (port_settings);

        if (!BuildCommDCBA(_sdci, &port_settings))
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " unable to set comport dcb settings");

            CloseHandle(_port_handle);
            _port_handle = -1;

            return DicesRcBaseComm::SET_PORT_SETTINGS_FAILURE;
        }

        if (!SetCommState(_port_handle, &port_settings))
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " unable to set comport cfg settings");

            CloseHandle(_port_handle);
            _port_handle = -1;

            return DicesRcBaseComm::SET_PORT_SETTINGS_FAILURE;
        }

        cptimeouts.ReadIntervalTimeout = MAXDWORD;

        if (!SetCommTimeouts(_port_handle, &cptimeouts))
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " unable to set comport time-out settings");

            CloseHandle(_port_handle);

            // NOTE (DH): Although never hit, due to early return, I do not believe break
            //  is the correct statement and for now will just return 'DicesRcBaseComm::FAIL'
            //break;
            return DicesRcBaseComm::FAIL;
        }
#else
        std::stringstream ss;
        int baudr = 0;
        struct termios new_port_settings = { 0 };

        if (_is_open)
        {
            LOG4CPLUS_WARN(root_logger,
                sfn << " Port " << _portname << " already open");
            return DicesRcBaseComm::OK;
        }

        switch (_baudrate)
        {
        case 50:
            baudr = B50;
            break;
        case 75:
            baudr = B75;
            break;
        case 110:
            baudr = B110;
            break;
        case 134:
            baudr = B134;
            break;
        case 150:
            baudr = B150;
            break;
        case 200:
            baudr = B200;
            break;
        case 300:
            baudr = B300;
            break;
        case 600:
            baudr = B600;
            break;
        case 1200:
            baudr = B1200;
            break;
        case 1800:
            baudr = B1800;
            break;
        case 2400:
            baudr = B2400;
            break;
        case 4800:
            baudr = B4800;
            break;
        case 9600:
            baudr = B9600;
            break;
        case 19200:
            baudr = B19200;
            break;
        case 38400:
            baudr = B38400;
            break;
        case 57600:
            baudr = B57600;
            break;
        case 115200:
            baudr = B115200;
            break;
        case 230400:
            baudr = B230400;
            break;
        case 460800:
            baudr = B460800;
            break;
        case 500000:
            baudr = B500000;
            break;
        case 576000:
            baudr = B576000;
            break;
        case 921600:
            baudr = B921600;
            break;
        case 1000000:
            baudr = B1000000;
            break;
        default:
            LOG4CPLUS_ERROR(root_logger,
                sfn << " For port " << _portname << ", invalid baudrate " << _baudrate);
            _port_handle = -1;
            return DicesRcBaseComm::INVALID_BAUD_RATE_FAILURE;
        }

        _port_handle = open(_portname.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
        if (_port_handle < 0)
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " unable to open comport " << strerror(errno));
            _port_handle = -1;
            return DicesRcBaseComm::OPEN_PORT_FAILURE;
        }

        //fcntl(_hport[*portnumber], F_SETFL, 0); // Block read/write
        fcntl(_port_handle, F_SETFL, FNDELAY); // Return immediately upon read/write

        if (!_old_port_settings)
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " pointer to termios old port settings is a null pointer");
            return DicesRcBaseComm::OLD_PORT_SETTINGS_POINTER_IS_NULL_FAILURE;
        }

        int _error = tcgetattr(_port_handle, _old_port_settings);
        if (_error == -1)
        {
            close(_port_handle);
            LOG4CPLUS_ERROR(root_logger,
                sfn << " unable to read portsettings " << strerror(errno));
            _port_handle = -1;
            return DicesRcBaseComm::GET_PORT_SETTINGS_FAILURE;
        }

        // Sets both input and output baudrate speeds
        cfsetspeed(&new_port_settings, baudr);

        new_port_settings.c_cflag |= (CLOCAL | CREAD); // Enable

        // Parity
        int iparitybitcheckandstrip = 1;
        switch (_parity)
        {
        case parity_none:
            iparitybitcheckandstrip = 0;
            new_port_settings.c_cflag &= ~PARENB;
            break;
        case parity_even:
            new_port_settings.c_cflag |= PARENB;
            new_port_settings.c_cflag &= ~PARODD;
            break;
        case parity_odd:
            new_port_settings.c_cflag |= PARENB;
            new_port_settings.c_cflag |= PARODD;
            break;
        case parity_space:
            new_port_settings.c_cflag &= ~PARENB;
            break;
        default: // parity_none
            iparitybitcheckandstrip = 0;
            new_port_settings.c_cflag &= ~PARENB;
        }

        if (iparitybitcheckandstrip != 0)
        {
            // Enable checking and stripping of the parity bit
            new_port_settings.c_iflag |= (INPCK | ISTRIP);
        }

        // Stop bits
        switch (_stopbits)
        {
        case two_stopbits:
            new_port_settings.c_cflag |= CSTOPB;
            break;
        case one_stopbit:
            new_port_settings.c_cflag &= ~CSTOPB;
            break;
        case one_point_five_stopbits:
            LOG4CPLUS_ERROR(root_logger,
                sfn << " this function doesn't handle 1.5 stopbits.");
            _port_handle = -1;
            return DicesRcBaseComm::ONE_POINT_FIVE_STOP_BITS_IS_NOT_IMPLEMENTED_FAILURE;
        }

        // Byte size
        new_port_settings.c_cflag &= ~CSIZE;

        switch (_databits)
        {
        case 8:
            new_port_settings.c_cflag |= CS8;
            break;
        case 7:
            new_port_settings.c_cflag |= CS7;
            break;
        case 6:
            new_port_settings.c_cflag |= CS6;
            break;
        case 5:
            new_port_settings.c_cflag |= CS5;
            break;
        }

        if (_enable_hardware_flow_control)
        {
            // Enable hardware flow control
            new_port_settings.c_cflag |= CRTSCTS; // Also called CNEW_RTSCTS
        }
        else
        {
            // Disable hardware flow control
            new_port_settings.c_cflag &= ~CRTSCTS; // Also called CNEW_RTSCTS

            new_port_settings.c_lflag &= 0;
            new_port_settings.c_oflag &= 0;
        }

        if (_enable_software_flow_control)
        {
            // Partially Disable
            new_port_settings.c_iflag |= IXON | IXOFF;
        }
        else
        {
            new_port_settings.c_iflag &= 0;
        }

        /* NOTE: From http://unixwiz.net/techtips/termios-vmin-vtime.html
         *
         * VMIN and VTIME defined
         *
         * VMIN is a character count ranging from 0 to 255 characters, and VTIME is
         * time measured in 0.1 second intervals, (0 to 25.5 seconds). The value of
         * "zero" is special to both of these parameters, and this suggests four
         * combinations discussed below. In every case, the question is when a read()
         * system call is satisfied. Here is the read() prototype call:
         *
         * int n = read(fd, buffer, nbytes);
         *
         * The tty driver maintains an input queue of bytes already
         * read from the serial line and not passed to the user, so not every read()
         * call waits for actual I/O - the read may very well be satisfied directly
         * from the input queue.
         *
         * VMIN = 0 and VTIME = 0
         * This is a completely non-blocking read - the call is satisfied
         * immediately directly from the driver's input queue. If data are available,
         * they transfer to the caller's buffer up to nbytes and return.
         * Otherwise zero is immediately returned to indicate "no data". Note that
         * this is "polling" of the serial port, and it's almost always a bad idea.
         * If done repeatedly, it can consume enormous amounts of processor time and
         * is highly inefficient. Don't use this mode unless you really, really know
         * what you're doing.
         *
         * VMIN = 0 and VTIME > 0
         * This is a pure timed read. If data are available in the input queue, it's
         * transferred to the caller's buffer up to a maximum of nbytes, and returned
         * immediately to the caller. Otherwise the driver blocks until data arrive,
         * or when VTIME tenths expire from the start of the call. If the timer
         * expires without data, zero is returned. A single byte is sufficient to
         * satisfy this read call, but if more is available in the input queue, it's
         * returned to the caller. Note that this is an overall timer, not an
         * intercharacter one.
         *
         * VMIN > 0 and VTIME > 0
         * A read() is satisfied when either VMIN characters have been transferred to
         * the caller's buffer, or when VTIME tenths expire between characters. Since
         * this timer is not started until the first character arrives, this call can
         * block indefinitely if the serial line is idle. This is the most common
         * mode of operation, and we consider VTIME to be an intercharacter timeout,
         * not an overall one. This call should never return zero bytes read.
         *
         * VMIN > 0 and VTIME = 0
         * This is a counted read that is satisfied only when at least VMIN
         * characters have been transferred to the caller's buffer - there is no
         * timing component involved. This read can be satisfied from the driver's
         * input queue (where the call could return immediately), or by waiting for
         * new data to arrive. In this respect the call could block indefinitely.
         * Consider the behavior undefined when nbytes is less than VMIN.
         */

        new_port_settings.c_cc [VTIME] = 1;
        new_port_settings.c_cc [VMIN] = 1;

        // Flush the line
        tcflush(_port_handle, TCIFLUSH);

        // Set all options
        _error = tcsetattr(_port_handle, TCSANOW, &new_port_settings);
        if (_error == -1)
        {
            close(_port_handle);
            LOG4CPLUS_ERROR(root_logger,
                sfn << " unable to adjust port settings " << strerror(errno));
            _port_handle = -1;
            return DicesRcBaseComm::SET_PORT_SETTINGS_FAILURE;
        }
#endif

        _is_open = true;

        return DicesRcBaseComm::OK;
    }

    DicesRcBaseComm Close()
    {
        if (_is_open)
        {
#ifdef _WIN32
            CloseHandle(_port_handle);
#else
            close(_port_handle);
            tcsetattr(_port_handle, TCSANOW, _old_port_settings);
#endif
            _port_handle = -1;
            _is_open = false;
        }

        return DicesRcBaseComm::OK;
    }

    DicesRcBaseComm Flush()
    {
        static const char* sfn = "RS232::Flush()";

#ifdef _WIN32
        LOG4CPLUS_WARN(root_logger,
            sfn << " Windows flush has not been implemented.");
#else
        usleep(1000);

        if (tcflush(_port_handle, TCIOFLUSH) != 0)
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " tcflush error: " << strerror(errno));
            return DicesRcBaseComm::FLUSH_FAILURE;
        }
#endif

        return DicesRcBaseComm::OK;
    }

    DicesRcBaseComm Send(const uint8_t *buffer, const size_t buffer_size)
    {
        static const char* sfn = "RS232::Send()";

        if (!buffer)
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " Function argument buffer is a null pointer.");
          return DicesRcBaseComm::BAD_FUNCTION_ARGUMENT;
        }

        ssize_t nbytes = 0;

#ifdef _WIN32
        if (!WriteFile(_port_handle, buffer, buffer_size,
            reinterpret_cast<LPDWORD>(&nbytes), NULL))
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " Failed to write to serial port");
            return DicesRcBaseComm::SEND_FAILURE;
        }
#else
        nbytes = write(_port_handle, buffer, buffer_size);
#endif

        if (nbytes < buffer_size)
        {
            LOG4CPLUS_WARN(root_logger,
                sfn << " Failed to write all bytes to the "
                "file descriptor. Wrote " << nbytes << " out of "
                << buffer_size << " total bytes.");
          return DicesRcBaseComm::SEND_COMPLETE_BUFFER_FAILURE;
        }

        return DicesRcBaseComm::OK;
    }

    DicesRcBaseComm Read(uint8_t *buffer, const size_t buffer_size, ssize_t *bytes_transferred)
    {
        static const char* sfn = "RS232::Read()";

        if (!buffer)
        {
            LOG4CPLUS_DEBUG(root_logger,
                sfn << " Function argument buffer is a null pointer.");
            return DicesRcBaseComm::BAD_FUNCTION_ARGUMENT;
        }

        if (!_serial_read_impl)
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " Serial interface is a null pointer.");
            return DicesRcBaseComm::READ_FUNCTION_NOT_IMPLEMENTED_FAILURE;
        }

        DicesRcrs232 retcode = _serial_read_impl->Read(
            _port_handle,
            buffer,
            buffer_size,
            bytes_transferred);
        if (retcode != DicesRcrs232::OK)
        {
            switch (retcode)
            {
            case DicesRcrs232::DEVICE_DISCONNECTION:
                return DicesRcBaseComm::DEVICE_DISCONNECTION;
            case DicesRcrs232::READ_TIMEOUT:
                return DicesRcBaseComm::READ_TIMEOUT;
            default:
                LOG4CPLUS_ERROR(root_logger,
                    sfn << " Failed to read from serial port");
                return DicesRcBaseComm::READ_FAILURE;
            }
        }

        return DicesRcBaseComm::OK;
    }

    bool IsCTSEnabled()
    {
        int status = 0;

#ifdef _WIN32
        GetCommModemStatus(_port_handle, reinterpret_cast<LPDWORD>(&status));
        if (status & MS_CTS_ON)
        {
            return true;
        }
#else
        status = ioctl(_port_handle, TIOCMGET, &status);
        // Check for TIOCM_CTS CTS (clear to send)
        if (status & TIOCM_CTS)
        {
            return true;
        }
#endif

        return false;
    }

    bool IsDTREnabled()
    {
        static const char* sfn = "RS232::IsDTREnabled() ";

#ifdef _WIN32
        LOG4CPLUS_WARN(root_logger,
            sfn << "Not yet implemented");
#else
        int status = ioctl(_port_handle, TIOCMGET, &status);
        // Check for TIOCM_DTR DTR (data terminal ready)
        if (status & TIOCM_DTR)
        {
            return true;
        }
#endif

        return false;
    }
};

/*
 * SOURCE
 */
RS232::RS232(RS232ReadInterface* serial_impl)
    : _pimpl(new impl(serial_impl))
{
}

RS232::~RS232()
{
}

RS232::RS232(
    RS232ReadInterface *serial_impl,
    const char *portname,
    int baudrate,
    int databits,
    rs232_stopbits stopbits,
    int handshaking,
    rs232_parity parity,
    bool enable_hardware_flow_control,
    bool enable_software_flow_control
)
: _pimpl(new impl(
    serial_impl,
    portname,
    baudrate,
    databits,
    stopbits,
    handshaking,
    parity,
    enable_hardware_flow_control,
    enable_software_flow_control))
{
}

DicesRcBaseComm RS232::Open()
{
    return _pimpl->Open();
}

DicesRcBaseComm RS232::Close()
{
    return _pimpl->Close();
}

DicesRcBaseComm RS232::Flush()
{
    return _pimpl->Flush();
}

DicesRcBaseComm RS232::Read(uint8_t *buffer, const size_t buffer_size, ssize_t *bytes_transferred)
{
    return _pimpl->Read(buffer, buffer_size, bytes_transferred);
}

DicesRcBaseComm RS232::Send(const uint8_t *buffer, const size_t buffer_size)
{
    return _pimpl->Send(buffer, buffer_size);
}

bool RS232::IsCTSEnabled()
{
    return _pimpl->IsCTSEnabled();
}

bool RS232::IsDTREnabled()
{
    return _pimpl->IsDTREnabled();
}

// ACCESSORS AND MUTATORS
std::string RS232::get_portname()
{
    return _pimpl->_portname;
}

int RS232::get_baudrate()
{
    return _pimpl->_baudrate;
}

int RS232::get_databits()
{
    return _pimpl->_databits;
}

rs232_stopbits RS232::get_stopbits()
{
    return _pimpl->_stopbits;
}

int RS232::get_handshaking()
{
    return _pimpl->_handshaking;
}

rs232_parity RS232::get_parity()
{
    return _pimpl->_parity;
}

bool RS232::get_enable_hardware_flow_control()
{
    return _pimpl->_enable_hardware_flow_control;
}

bool RS232::get_enable_software_flow_control()
{
    return _pimpl->_enable_software_flow_control;
}

std::string RS232::get_statusmsg(DicesRcrs232 error_code)
{
    //return DicesRcrs232StatusMessage::DicesRcrs232ToString(error_code);
    _pimpl->_statusmsg = DicesRcrs232StatusMessage::DicesRcrs232ToString(error_code);
    return _pimpl->_statusmsg;
}

int RS232::get_port_handle()
{
    return _pimpl->_port_handle;
}

bool RS232::get_is_open()
{
    return _pimpl->_is_open;
}

void RS232::set_portname(const std::string &portname)
{
    _pimpl->_portname = portname;
}

void RS232::set_baudrate(int baudrate)
{
    _pimpl->_baudrate = baudrate;
}

void RS232::set_databits(int databits)
{
    _pimpl->_databits = databits;
}

void RS232::set_stopbits(rs232_stopbits stopbits)
{
    _pimpl->_stopbits = stopbits;
}

void RS232::set_handshaking(int handshaking)
{
    _pimpl->_handshaking = handshaking;
}

void RS232::set_parity(rs232_parity parity)
{
    _pimpl->_parity = parity;
}

void RS232::set_enable_hardware_flow_control(bool enable)
{
    _pimpl->_enable_hardware_flow_control = enable;
}

void RS232::set_enable_software_flow_control(bool enable)
{
    _pimpl->_enable_software_flow_control = enable;
}
