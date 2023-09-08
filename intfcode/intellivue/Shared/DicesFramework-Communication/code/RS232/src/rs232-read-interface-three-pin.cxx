/**
 * @file three_pin_rs232_read_interface.cxx
 *
 * @brief Defines a class which implements a serial reader interface. This
 * class is designed for communication with a serial port with only 3 pins
 * used for communication.
 *
 * @author Michael Szwaja
 */
//=============================================================================

#include "rs232-read-interface-three-pin.h"

#ifdef _WIN32
#   include <windows.h>
#endif

#include <string.h>
#include <unistd.h>
#include <time.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>

#include "rc-rs232.h"

static const ssize_t kMaxTerminatingCharSequenceSize = 100;
static const int kMaxSerialTimeoutLimit = 100000;
static const int kMaxSerialTimeoutLimitExceeded = 2;
static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

// TODO: MOVE 'millisleep' INTO COMMON/TOOLS OR UTILITIES
/**
 * Sleep a number of milliseconds
 * @param [in] millisecs number of milliseconds to sleep
 */
static void millisleep(int millisecs)
{
#ifdef _WIN32
    Sleep(millisecs);
#else
    static const int mega = 1000 * 1000;
    struct timespec tspec = { millisecs / 1000, (millisecs % 1000) * mega };
    struct timespec tspecdummy = { 0 };
    nanosleep(&tspec, &tspecdummy);
#endif
}

struct ThreePinRS232ReadInterface::impl {
    // MEMBERS
    uint8_t *_terminating_char_seq;
    size_t _terminating_char_seq_size;
    int _serial_timeout_count;
    int _serial_timeout_limit_exceeded_count;
    int _max_serial_timeout_limit;
    int _max_serial_timeout_limit_exceeded;

    // CTOR + DTOR
    impl()
    : _terminating_char_seq_size(0),
      _serial_timeout_count(0),
      _serial_timeout_limit_exceeded_count(0),
      _max_serial_timeout_limit(kMaxSerialTimeoutLimit),
      _max_serial_timeout_limit_exceeded(kMaxSerialTimeoutLimitExceeded)
    {
        _terminating_char_seq = new (std::nothrow) uint8_t[kMaxTerminatingCharSequenceSize]();
    }

    ~impl()
    {
        delete [] _terminating_char_seq;
        _terminating_char_seq = nullptr;
    }

    // METHODS
    DicesRcrs232 Read(
        int fd,
        uint8_t *response_buffer,
        const size_t size,
        ssize_t *bytes_transferred)
    {
        static const char *sfn = "ThreePinRS232ReadInterface::Read()";

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
        *bytes_transferred = 0; // Start at zero

        // Start reading one byte at a time
        while (1)
        {
            unsigned char byte = 0;
            ssize_t nbytes = 0;

            // Read character from port
#ifdef _WIN32
            ReadFile(
                reinterpret_cast<HANDLE>(_input_fd),
                reinterpret_cast<char*>(&byte),
                1,
                (LPDWORD)((void *)&nbytes),
                NULL);
#else
            nbytes = read(fd, reinterpret_cast<char*>(&byte), 1);
#endif

            if (nbytes > 0)
            {
                response_buffer [*bytes_transferred] = byte;
                *bytes_transferred += nbytes;

                // Reset timeout counters
                _serial_timeout_limit_exceeded_count = 0;
                _serial_timeout_count = 0;

                // Determine if that byte marks the end of a serial transmission
                bool stop_reading = false;
                if (HasReadTerminatingSequence(
                        response_buffer,
                        *bytes_transferred,
                        &stop_reading) != DicesRcrs232::OK)
                {
                    return DicesRcrs232::FAIL;
                }

                if (stop_reading) break;

                // Determine if read buffer is full
                if (*bytes_transferred >= size) break;
            }
            else
            {
                _serial_timeout_count++;
                if (_serial_timeout_limit_exceeded_count >= _max_serial_timeout_limit_exceeded)
                {
                    _serial_timeout_limit_exceeded_count = 0;
                    istat = DicesRcrs232::DEVICE_DISCONNECTION;
                    break;
                }
                if (_serial_timeout_count >= _max_serial_timeout_limit)
                {
                    _serial_timeout_limit_exceeded_count++;
                    _serial_timeout_count = 0;
                    istat = DicesRcrs232::READ_TIMEOUT;
                    break;
                }
            }

            millisleep(0);
        }

        return istat;
    }

    DicesRcrs232 set_terminating_character_sequence(
        const uint8_t *sequence,
        const size_t size)
    {
        static const char *sfn = "ThreePinRS232ReadInterface::set_terminating_character_sequence()";

        if (!sequence)
        {
            LOG4CPLUS_DEBUG(root_logger,
                sfn << " sequence is a null pointer.");
            return DicesRcrs232::BAD_FUNCTION_ARGUMENT;
        }

        if (size > kMaxTerminatingCharSequenceSize)
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " not enough memory allocated.");
            return DicesRcrs232::FAIL;
        }

        memcpy(_terminating_char_seq, sequence, size);
        _terminating_char_seq_size = size;

        return DicesRcrs232::OK;
    }

    bool IsValidFileDescriptor(int fd)
    {
        return (fd > 0);
    }

    DicesRcrs232 HasReadTerminatingSequence(
        const uint8_t *response,
        const size_t size,
        bool *equals)
    {
        static const char *sfn = "ThreePinRS232ReadInterface::HasReadTerminatingSequence()";

        if (!equals)
        {
            LOG4CPLUS_DEBUG(root_logger,
                sfn << " Equals pointer is null");
            return DicesRcrs232::BAD_FUNCTION_ARGUMENT;
        }

        *equals = false;

        if (!response)
        {
            LOG4CPLUS_DEBUG(root_logger,
                sfn << " Response is pointer to null");
            return DicesRcrs232::BAD_FUNCTION_ARGUMENT;
        }

        if (!_terminating_char_seq_size)
        {
            LOG4CPLUS_ERROR(root_logger,
                sfn << " Zero characters in terminating sequence.");
            return DicesRcrs232::FAIL;
        }

        if (size < _terminating_char_seq_size)
        {
            return DicesRcrs232::OK;
        }

        if (!memcmp(
            &response[size - _terminating_char_seq_size],
            _terminating_char_seq, _terminating_char_seq_size))
        {
            *equals = true;
        }

        return DicesRcrs232::OK;
    }
};

ThreePinRS232ReadInterface::ThreePinRS232ReadInterface()
: RS232ReadInterface(),
  _pimpl(new impl())
{
}

ThreePinRS232ReadInterface::~ThreePinRS232ReadInterface()
{
}

std::string ThreePinRS232ReadInterface::get_statusmsg(DicesRcrs232 error_code)
{
    return DicesRcrs232StatusMessage::DicesRcrs232ToString(error_code);
}

DicesRcrs232 ThreePinRS232ReadInterface::Read(
    int fd,
    uint8_t *response_buffer,
    const size_t size,
    ssize_t *bytes_transferred)
{
    return _pimpl->Read(fd, response_buffer, size, bytes_transferred);
}

DicesRcrs232 ThreePinRS232ReadInterface::set_terminating_character_sequence(
    const uint8_t *sequence,
    const size_t size)
{
    return _pimpl->set_terminating_character_sequence(sequence, size);
}

bool ThreePinRS232ReadInterface::IsValidFileDescriptor(int fd)
{
    return _pimpl->IsValidFileDescriptor(fd);
}

DicesRcrs232 ThreePinRS232ReadInterface::HasReadTerminatingSequence(
    const uint8_t *response,
    const size_t size,
    bool *equals)
{
    return _pimpl->HasReadTerminatingSequence(response, size, equals);
}

int ThreePinRS232ReadInterface::get_max_serial_timeout_limit()
{
    return _pimpl->_max_serial_timeout_limit;
}

void ThreePinRS232ReadInterface::set_max_serial_timeout_limit(const int limit)
{
    _pimpl->_max_serial_timeout_limit = limit;
}

int ThreePinRS232ReadInterface::get_max_serial_timeout_limit_exceeded()
{
    return _pimpl->_max_serial_timeout_limit_exceeded;
}

void ThreePinRS232ReadInterface::set_max_serial_timeout_limit_exceeded(const int limit)
{
    _pimpl->_max_serial_timeout_limit_exceeded = limit;
}
