/**
 * @file dices_rc_base_comm.h
 *
 * @brief Return codes for base communication class
 *
 * @author Michael Szwaja
 */
//=============================================================================
#ifndef RC_BASE_COMMUNICATION_H_
#define	RC_BASE_COMMUNICATION_H_

#include <string>

enum class DicesRcBaseComm
{
    OK = 0,
    FAIL = 1,
    BAD_FUNCTION_ARGUMENT,

    READ_TIMEOUT,
    DEVICE_DISCONNECTION,

    READ_FUNCTION_NOT_IMPLEMENTED_FAILURE,

    PORT_IS_ALREADY_OPEN_FAILURE,
    OPEN_PORT_FAILURE,
    OPEN_SOCKET_FAILURE,

    UNKNOWN_IP_PROTOCOL_FAILURE,
    INVALID_BAUD_RATE_FAILURE,
    ONE_POINT_FIVE_STOP_BITS_IS_NOT_IMPLEMENTED_FAILURE,

    OLD_PORT_SETTINGS_POINTER_IS_NULL_FAILURE,
    GET_PORT_SETTINGS_FAILURE,
    SET_PORT_SETTINGS_FAILURE,
    SET_NONBLOCKING_IO_FAILURE,
    SET_SEND_TIMEOUT_FAILURE,
    SET_READ_TIMEOUT_FAILURE,

    SOCKADDR_IN_POINTER_IS_NULL_FAILURE,
    CONVERT_IP_ADDRESS_TO_STRUCT_IN_ADDR_FAILURE,
    BIND_IP_ADDRESS_TO_SOCKET_FAILURE,

    SEND_FAILURE,
    SEND_COMPLETE_BUFFER_FAILURE,

    READ_FAILURE,

    FLUSH_FAILURE,

    DATABASE_CONNECTION_ERROR,
    DATABASE_CONNECTION_NULL,
    DATABASE_QUERY_EXCEPTION,
    DATABASE_STANDARD_EXCEPTION,
    DATABASE_RESULTSET_ERROR,
    DATABASE_SQL_STATEMENT_NULL,
    DATABASE_RESULTSET_NULL
};

class DicesRcBaseCommStatusMessage
{
public:
    DicesRcBaseCommStatusMessage() = delete;
    ~DicesRcBaseCommStatusMessage() = delete;

    DicesRcBaseCommStatusMessage(const DicesRcBaseCommStatusMessage &src) = delete;
    DicesRcBaseCommStatusMessage & operator =(const DicesRcBaseCommStatusMessage &rhs) = delete;

    // METHODS
    const static std::string DicesRcBaseCommToString(const DicesRcBaseComm error_code)
    {
        std::string error_message;
        switch (error_code)
        {
            case DicesRcBaseComm::OK:
                error_message = "Ok";
                break;
            case DicesRcBaseComm::FAIL:
                error_message = "Fail";
                break;
            case DicesRcBaseComm::BAD_FUNCTION_ARGUMENT:
                error_message = "Bad function argument";
                break;

            case DicesRcBaseComm::READ_TIMEOUT:
                error_message = "Read timeout";
                break;
            case DicesRcBaseComm::DEVICE_DISCONNECTION:
                error_message = "Detected device disconnection";
                break;

            case DicesRcBaseComm::PORT_IS_ALREADY_OPEN_FAILURE:
                error_message = "The port is already open";
                break;
            case DicesRcBaseComm::OPEN_PORT_FAILURE:
                error_message = "Failed to open port";
                break;
            case DicesRcBaseComm::OPEN_SOCKET_FAILURE:
                error_message = "Failed to open socket";
                break;

            case DicesRcBaseComm::UNKNOWN_IP_PROTOCOL_FAILURE:
                error_message = "Unknown IP protocol";
                break;
            case DicesRcBaseComm::INVALID_BAUD_RATE_FAILURE:
                error_message = "Failed to set invalid baud rate";
                break;
            case DicesRcBaseComm::ONE_POINT_FIVE_STOP_BITS_IS_NOT_IMPLEMENTED_FAILURE:
                error_message = "1.5 stopbits is not implemented";
                break;

            case DicesRcBaseComm::OLD_PORT_SETTINGS_POINTER_IS_NULL_FAILURE:
                error_message = "Old port settings pointer is null";
                break;
            case DicesRcBaseComm::GET_PORT_SETTINGS_FAILURE:
                error_message = "Failed to get port settings";
                break;
            case DicesRcBaseComm::SET_PORT_SETTINGS_FAILURE:
                error_message = "Failed to set port settings";
                break;
            case DicesRcBaseComm::SET_NONBLOCKING_IO_FAILURE:
                error_message = "Failed to set nonblocking io";
                break;
            case DicesRcBaseComm::SET_SEND_TIMEOUT_FAILURE:
                error_message = "Failed to set send timeout";
                break;
            case DicesRcBaseComm::SET_READ_TIMEOUT_FAILURE:
                error_message = "Failed to set read timeout";
                break;

            case DicesRcBaseComm::SOCKADDR_IN_POINTER_IS_NULL_FAILURE:
                error_message = "Struct sockaddr_in pointer is null";
                break;
            case DicesRcBaseComm::CONVERT_IP_ADDRESS_TO_STRUCT_IN_ADDR_FAILURE:
                error_message = "Failed to convert IP address to struct in_addr";
                break;
            case DicesRcBaseComm::BIND_IP_ADDRESS_TO_SOCKET_FAILURE:
                error_message = "Failed to bind IP address to socket";
                break;

            case DicesRcBaseComm::SEND_FAILURE:
                error_message = "Failed to send";
                break;
            case DicesRcBaseComm::SEND_COMPLETE_BUFFER_FAILURE:
                error_message = "Failed to send complete buffer";
                break;
            case DicesRcBaseComm::READ_FUNCTION_NOT_IMPLEMENTED_FAILURE:
                error_message = "Read function not implemented";
                break;
            case DicesRcBaseComm::READ_FAILURE:
                error_message = "Failed to read";
                break;
            case DicesRcBaseComm::FLUSH_FAILURE:
                error_message = "Failed to flush";
                break;

            case DicesRcBaseComm::DATABASE_CONNECTION_ERROR:
                error_message = "Failed to connect to database";
                break;
            case DicesRcBaseComm::DATABASE_CONNECTION_NULL:
                error_message = "Database connection is null";
                break;
            case DicesRcBaseComm::DATABASE_QUERY_EXCEPTION:
                error_message = "Database query exception occurred";
                break;
            case DicesRcBaseComm::DATABASE_STANDARD_EXCEPTION:
                error_message = "Standard exception occurred during database query";
                break;
            case DicesRcBaseComm::DATABASE_RESULTSET_ERROR:
                error_message = "Error parsing resultset";
                break;
            case DicesRcBaseComm::DATABASE_SQL_STATEMENT_NULL:
                error_message = "SQL statement is null";
                break;
            case DicesRcBaseComm::DATABASE_RESULTSET_NULL:
                error_message = "Query result set is null";
                break;

            default: // should not be reached
                error_message = "Unknown status code";
                break;
        }
        return error_message;
    }
};

#endif // RC_BASE_COMMUNICATION_H_
