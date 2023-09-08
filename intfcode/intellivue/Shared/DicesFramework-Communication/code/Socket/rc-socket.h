/**
 * @file DicesSocketReturnCodes.h
 *
 * @brief Declares and defines a set of all return codes used in the DICES
 * socket tool.
 *
 */
//=============================================================================
#ifndef DICES_SOCKET_RETURN_CODES_H_
#define DICES_SOCKET_RETURN_CODES_H_

#include <string>

enum class DicesRcSocket
{
    OK = 0,
    FAIL = 1,
    BAD_FUNCTION_ARGUMENT,
    SEND_TIMEOUT_IS_A_NULL_POINTER,
    RECV_TIMEOUT_IS_A_NULL_POINTER,
    SOCKET_READ_FUNCTION_NOT_IMPLEMENTED,
    READ_TIMEOUT,
    DEVICE_DISCONNECTION
};

struct DicesRcSocketStatusMessage
{
    DicesRcSocketStatusMessage(const DicesRcSocketStatusMessage &src) = delete;
    DicesRcSocketStatusMessage & operator =(const DicesRcSocketStatusMessage &rhs) = delete;

    const static std::string DicesRcSocketToString(const DicesRcSocket error_code)
    {
        std::string error_message;
        switch (error_code)
        {
          case DicesRcSocket::OK:
            error_message = "Ok";
            break;
          case DicesRcSocket::FAIL:
            error_message = "Fail";
            break;
          case DicesRcSocket::BAD_FUNCTION_ARGUMENT:
            error_message = "Bad function argument";
            break;
          case DicesRcSocket::SEND_TIMEOUT_IS_A_NULL_POINTER:
            error_message = "Sen timeout pointer is null";
            break;
          case DicesRcSocket::RECV_TIMEOUT_IS_A_NULL_POINTER:
            error_message = "Receive timeout pointer is null";
            break;
          case DicesRcSocket::SOCKET_READ_FUNCTION_NOT_IMPLEMENTED:
            error_message = "Interface socket read function has not been "
              "implemented";
            break;
          case DicesRcSocket::READ_TIMEOUT:
            error_message = "Read timeout";
            break;
          case DicesRcSocket::DEVICE_DISCONNECTION:
            error_message = "Device disconnection";
            break;
          default:
            error_message = "Unknown error code";
        }
        return error_message;
    }
};

#endif
