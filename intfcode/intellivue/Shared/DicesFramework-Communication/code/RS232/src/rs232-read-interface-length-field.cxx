/**
 * @file length_field_rs232_read_interface.cxx
 *
 * @brief Defines a class which implements a serial reader interface. This
 * class is designed for communication protocols where the message length is a
 * field in the message.
 *
 * @author Robert England
 */
//=============================================================================

#include "rs232-read-interface-length-field.h"

#ifdef _WIN32
#   include <windows.h>
#endif

#include <string.h>
#include <unistd.h>
#include <time.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>

#include "rc-rs232.h"

static const int kMaxTerminatingCharSequenceSize = 100;
static const int kMaxSerialTimeoutLimit = 1000;
static const int kMaxSerialTimeoutLimitExceeded = 2;

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

struct LengthFieldRS232ReadInterface::impl
{
    // MEMBERS
    int _prefix_size;
    int _length_field_size;
    int _suffix_size;
    bool _length_includes_pre_suf;
    int _serial_failure_count;
    int _serial_failure_limit_exceeded_count;
    int _max_serial_timeout_limit;
    int _max_serial_timeout_limit_exceeded;

    // CTOR + DTOR
    impl(
        int prefix_size,
        int length_field_size,
        int suffix_size,
        bool length_includes_pre_suf)
    : _prefix_size(prefix_size),
      _length_field_size(length_field_size),
      _suffix_size(suffix_size),
      _length_includes_pre_suf(length_includes_pre_suf),
      _serial_failure_count(0),
      _serial_failure_limit_exceeded_count(0),
      _max_serial_timeout_limit(kMaxSerialTimeoutLimit),
      _max_serial_timeout_limit_exceeded(kMaxSerialTimeoutLimitExceeded)
    {

    }

    ~impl() = default;

    DicesRcrs232 Read(
        int fd,
        uint8_t *response_buffer,
        const size_t size,
        ssize_t *bytes_transferred)
    {
        static const char *sfn = "LengthFieldRS232ReadInterface::Read()";

        if (!IsValidFileDescriptor(fd))
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " Bad file descriptor.");
            return DicesRcrs232::FAIL;
        }

        if (!response_buffer)
        {
            LOG4CPLUS_DEBUG(root_logger,
                sfn << " Response buffer is null pointer.");
            return DicesRcrs232::BAD_FUNCTION_ARGUMENT;
        }

        if (!bytes_transferred)
        {
            LOG4CPLUS_DEBUG(root_logger,
                sfn << " bytes_transferred is null pointer.");
            return DicesRcrs232::BAD_FUNCTION_ARGUMENT;
        }

        DicesRcrs232 istat = DicesRcrs232::OK;
        unsigned int buffer_pos = 0;
        *bytes_transferred = 0; // Start at zero
        unsigned int length_field = 0;
        unsigned int total_length = _prefix_size + _length_field_size + _suffix_size;

        // Start reading one byte at a time
        while(1)
        {
            unsigned char byte = 0;
            ssize_t nbytes = 0;

            // Read character from port
    #ifdef _WIN32
            ReadFile(
                reinterpret_cast<HANDLE>(fd),
                reinterpret_cast<char*>(&byte),
                1,
                (LPDWORD)((void *)&nbytes),
                NULL);
    #else
            fd_set rfds;
            struct timeval tv;
            FD_ZERO(&rfds);
            FD_SET(fd, &rfds);
            tv.tv_sec = 0;
            tv.tv_usec = 1000;
            nbytes = -1;

            nbytes = select(fd + 1, &rfds, NULL, NULL, &tv);
            // Don't see much point in returning an actual error here so much as just trying again.
            if (nbytes < 0)
            {
                LOG4CPLUS_ERROR(root_logger,
                    sfn << " select(2) failure");
            }

            if (nbytes > 0)
            {
                nbytes = read(fd, reinterpret_cast<char*>(&byte), 1);
            }
    #endif

            if (nbytes > 0)
            {
                response_buffer[buffer_pos] = byte;
                buffer_pos++;
                *bytes_transferred += nbytes;

                // Reset timeout counters
                _serial_failure_limit_exceeded_count = 0;
                _serial_failure_count = 0;

                // Calculate length field, once it has been read
                if (buffer_pos > _prefix_size && buffer_pos <= (_prefix_size + _length_field_size))
                {
                    length_field = length_field * 256 + static_cast<unsigned int>(byte);
                }

                if (buffer_pos == (_prefix_size + _length_field_size))
                {
                    if (_length_includes_pre_suf)
                    {
                        total_length = length_field;
                    }
                    else
                    {
                        total_length += length_field;
                    }
                }

                // Determine if that byte marks the end of a serial transmission
                if (buffer_pos >= total_length) break;
            }
            else
            {
                _serial_failure_count++;
                if (_serial_failure_limit_exceeded_count >= _max_serial_timeout_limit_exceeded)
                {
                    _serial_failure_limit_exceeded_count = 0;
                    istat = DicesRcrs232::DEVICE_DISCONNECTION;
                    break;
                }

                if (_serial_failure_count >= _max_serial_timeout_limit)
                {
                    _serial_failure_limit_exceeded_count++;
                    _serial_failure_count = 0;
                    istat = DicesRcrs232::READ_TIMEOUT;
                    break;
                }
            }
        }

        return istat;
    }


    bool IsValidFileDescriptor(int fd)
    {
        return (fd > 0);
    }
};

LengthFieldRS232ReadInterface::LengthFieldRS232ReadInterface(
    int prefix_size,
    int length_field_size,
    int suffix_size,
    bool length_includes_pre_suf
)
: RS232ReadInterface(),
  _pimpl(new impl(
    prefix_size,
    length_field_size,
    suffix_size,
    length_includes_pre_suf))
{
}

LengthFieldRS232ReadInterface::~LengthFieldRS232ReadInterface()
{
}

std::string LengthFieldRS232ReadInterface::get_statusmsg(DicesRcrs232 error_code)
{
    return DicesRcrs232StatusMessage::DicesRcrs232ToString(error_code);
}

DicesRcrs232 LengthFieldRS232ReadInterface::Read(
    int fd,
    uint8_t *response_buffer,
    const size_t size,
    ssize_t *bytes_transferred)
{
    return _pimpl->Read(fd, response_buffer, size, bytes_transferred);
}


bool LengthFieldRS232ReadInterface::IsValidFileDescriptor(int fd)
{
    return _pimpl->IsValidFileDescriptor(fd);
}

int LengthFieldRS232ReadInterface::get_max_serial_timeout_limit()
{
    return _pimpl->_max_serial_timeout_limit;
}

void LengthFieldRS232ReadInterface::set_max_serial_timeout_limit(const int limit)
{
    _pimpl->_max_serial_timeout_limit = limit;
}

int LengthFieldRS232ReadInterface::get_max_serial_timeout_limit_exceeded()
{
    return _pimpl->_max_serial_timeout_limit_exceeded;
}

void LengthFieldRS232ReadInterface::set_max_serial_timeout_limit_exceeded(const int limit)
{
    _pimpl->_max_serial_timeout_limit_exceeded = limit;
}
