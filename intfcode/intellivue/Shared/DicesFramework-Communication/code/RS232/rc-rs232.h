/**
 * @file DicesRS232ReturnCodes.h
 *
 * @brief Declares and defines a set of all return codes used in the DICES
 * RS232 tool.
 *
 */
//=============================================================================

#ifndef RC_RS232_H_
#define RC_RS232_H_

#include <string>

enum class DicesRcrs232
{
    OK = 0,
    FAIL = 1,
    BAD_FUNCTION_ARGUMENT,
    SERIAL_READ_FUNCTION_NOT_IMPLEMENTED,
    READ_TIMEOUT,
    DEVICE_DISCONNECTION
};

struct DicesRcrs232StatusMessage
{
    DicesRcrs232StatusMessage(const DicesRcrs232StatusMessage &src) = delete;
    DicesRcrs232StatusMessage &operator=(const DicesRcrs232StatusMessage &rhs) = delete;

    const static std::string DicesRcrs232ToString(const DicesRcrs232 error_code)
    {
        std::string error_message;
        switch (error_code)
        {
        case DicesRcrs232::OK:
            error_message = "Ok";
            break;
        case DicesRcrs232::FAIL:
            error_message = "Fail";
            break;
        case DicesRcrs232::BAD_FUNCTION_ARGUMENT:
            error_message = "Bad function argument";
            break;
        case DicesRcrs232::SERIAL_READ_FUNCTION_NOT_IMPLEMENTED:
            error_message = "Interface serial read function has not been implemented";
            break;
        case DicesRcrs232::READ_TIMEOUT:
            error_message = "Read timeout";
            break;
        case DicesRcrs232::DEVICE_DISCONNECTION:
            error_message = "Device disconnection";
            break;
        default: // should not be reached
            error_message = "Unknown error code";
        }

        return error_message;
    }
};

#endif // RC_RS232_H_
