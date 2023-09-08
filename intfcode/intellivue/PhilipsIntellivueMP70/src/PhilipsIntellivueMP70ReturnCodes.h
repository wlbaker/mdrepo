/**
 * @file DicesRS232ReturnCodes.h
 *
 * @brief Declares and defines a set of all return codes used in the DICES
 * RS232 tool.
 *
 */
//=============================================================================
#ifndef DD_PHILIPS_INTELLIVUE_MP70_SRC_RETURN_CODES_H_
#define DD_PHILIPS_INTELLIVUE_MP70_SRC_RETURN_CODES_H_

#include <string>

enum class DicesRcPhilipsIntellivueMP70
{
  OK = 0,
  FAIL = 1,

  NULL_POINTER_FUNCTION_ARGUMENT_FAILURE,
  NO_NEW_DATA,

  MEMORY_ALLOCATION_FAILURE,
  VECTOR_INSERT_FAILURE,
  VECTOR_ACCESS_FAILURE,
  BUFFER_SIZE_TOO_SMALL,

  FRAME_CHECK_SEQUENCE_INCORRECT_FAILURE,
  INCORRECT_PROTOCOL_ID_FAILURE,
  INCORRECT_MESSAGE_TYPE_FAILURE,

  GET_IP_ADDRESS_INFO_FAILURE,
  GET_DATA_EXPORT_PORT_NUMBER_FAILURE,

  PARSE_RESPONSE_FAILURE,

  ASSOCIATION_REFUSED,
  ASSOCIATION_ABORTED,
  ASSOCIATION_DISCONNECT,

  UNKNOWN_SINGLE_POLL_REQUEST_TYPE,
  UNKNOWN_EXTENDED_POLL_REQUEST_TYPE,

  // Parse ini configuration file errors
  INI_PARSER_OBJECT_POINTER_IS_NULL_FAILURE,
  PARSE_INI_CFG_FILE_FAILURE,
  PARSE_INI_CFG_FILE_INVALID_FILENAME_FAILURE,
  PARSE_INI_CFG_FILE_LOAD_FILE_FAILURE,
  PARSE_INI_CFG_FILE_KEY_VALUE_NOT_AVAILABLE_FAILURE,
  PARSE_INI_CFG_FILE_SECTION_NAME_NOT_AVAILABLE_FAILURE,

  // Parse command line argument errors
  PARSE_CMD_LN_ARGS_FAILURE,
  PARSE_CMD_LN_ARGS_UDI_FAILURE,
  PARSE_CMD_LN_ARGS_DISABLE_LAN_IO_FAILURE,
  PARSE_CMD_LN_ARGS_DISABLE_SERIAL_IO_FAILURE,
  PARSE_CMD_LN_ARGS_SERIAL_PORT_NAME_FAILURE,
  PARSE_CMD_LN_ARGS_LOCAL_IP_ADDRESS_FAILURE,
  PARSE_CMD_LN_ARGS_BROADCAST_ADDRESS_FAILURE,
  PARSE_CMD_LN_ARGS_DEVICE_IP_ADDRESS_FAILURE,

  // General configuration (command line and ini configuration file) errors
  UPDATE_PERIOD_MILLISEC_NOT_MULTIPLE_OF_1000_FAILURE,
  SERIAL_IO_AND_LAN_IO_BOTH_ENABLED_FAILURE,
  SERIAL_IO_AND_LAN_IO_BOTH_DISABLED_FAILURE,

  RS232_SET_TERMINATING_SEQUENCE_FAILURE,
  RS232_OPEN_FAILURE,

  SOCKET_OPEN_FAILURE,

  BASE_DRIVER_RUN_DRIVER_FAILURE,

  DDS_SEQUENCE_ENSURE_LENGTH_FAILURE
};

class DicesRcPhilipsIntellivueMP70StatusMessage
{
 public:

  const static std::string DicesRcPhilipsIntellivueMP70ToString(
    const DicesRcPhilipsIntellivueMP70 error_code)
  {
    std::string error_message;
    switch (error_code)
    {
      case DicesRcPhilipsIntellivueMP70::OK:
        error_message = "Ok";
        break;
      case DicesRcPhilipsIntellivueMP70::FAIL:
        error_message = "Fail";
        break;

      case DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE:
        error_message = "Failed to use null pointer function argument";
        break;
      case DicesRcPhilipsIntellivueMP70::NO_NEW_DATA:
        error_message = "No new data is available in DDS instance";
        break;

      case DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE:
        error_message = "Failed to allocate memory";
        break;
      case DicesRcPhilipsIntellivueMP70::VECTOR_INSERT_FAILURE:
        error_message = "Failed to insert into vector";
        break;
      case DicesRcPhilipsIntellivueMP70::VECTOR_ACCESS_FAILURE:
        error_message = "Failed to access element of vector";
        break;
      case DicesRcPhilipsIntellivueMP70::BUFFER_SIZE_TOO_SMALL:
        error_message = "Buffer size is too small";
        break;

      case DicesRcPhilipsIntellivueMP70::FRAME_CHECK_SEQUENCE_INCORRECT_FAILURE:
        error_message = "Failed to generated the same frame check sequence "
          "in message";
        break;
      case DicesRcPhilipsIntellivueMP70::INCORRECT_PROTOCOL_ID_FAILURE:
        error_message = "Found incorrect protocol id in message";
        break;
      case DicesRcPhilipsIntellivueMP70::INCORRECT_MESSAGE_TYPE_FAILURE:
        error_message = "Found incorrect message type in message";
        break;

      case DicesRcPhilipsIntellivueMP70::GET_IP_ADDRESS_INFO_FAILURE:
        error_message = "Failed to get ip address information from connect "
          "indication message";
        break;
      case DicesRcPhilipsIntellivueMP70::GET_DATA_EXPORT_PORT_NUMBER_FAILURE:
        error_message = "Failed to get data export port number from connect "
          "indication message";
        break;

      case DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE:
        error_message = "Failed to parse response";
        break;

      case DicesRcPhilipsIntellivueMP70::ASSOCIATION_REFUSED:
        error_message = "Association refused";
        break;
      case DicesRcPhilipsIntellivueMP70::ASSOCIATION_ABORTED:
        error_message = "Association aborted";
        break;
      case DicesRcPhilipsIntellivueMP70::ASSOCIATION_DISCONNECT:
        error_message = "Association disconnect";
        break;

      case DicesRcPhilipsIntellivueMP70::UNKNOWN_SINGLE_POLL_REQUEST_TYPE:
        error_message = "Unknown single poll request type";
        break;
      case DicesRcPhilipsIntellivueMP70::UNKNOWN_EXTENDED_POLL_REQUEST_TYPE:
        error_message = "Unknown extended poll request type";
        break;

      case DicesRcPhilipsIntellivueMP70::INI_PARSER_OBJECT_POINTER_IS_NULL_FAILURE:
        error_message = "Ini parser object pointer is null";
        break;
      case DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_FAILURE:
        error_message = "Failed to parse ini configuration file";
        break;
      case DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_INVALID_FILENAME_FAILURE:
        error_message = "Failed to parse ini configuration file. "
          "The file name is invalid.";
        break;
      case DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_LOAD_FILE_FAILURE:
        error_message = "Failed to load ini configuration file.";
        break;
      case DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_KEY_VALUE_NOT_AVAILABLE_FAILURE:
        error_message = "Failed to parse ini configuration file. "
          "The key value is not available";
        break;
      case DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_SECTION_NAME_NOT_AVAILABLE_FAILURE:
        error_message = "Failed to parse ini configuration file. "
          "The section name is not available";
        break;

      case DicesRcPhilipsIntellivueMP70::PARSE_CMD_LN_ARGS_FAILURE:
        error_message = "Failed to parse command line arguments";
        break;
      case DicesRcPhilipsIntellivueMP70::PARSE_CMD_LN_ARGS_UDI_FAILURE:
        error_message = "Failed to parse UDI from command line arguments";
        break;
      case DicesRcPhilipsIntellivueMP70::PARSE_CMD_LN_ARGS_DISABLE_LAN_IO_FAILURE:
        error_message = "Failed to parse disable LAN io from command line "
          "arguments";
        break;
      case DicesRcPhilipsIntellivueMP70::PARSE_CMD_LN_ARGS_DISABLE_SERIAL_IO_FAILURE:
        error_message = "Failed to parse disable serial io from command line "
          "arguments";
        break;
      case DicesRcPhilipsIntellivueMP70::PARSE_CMD_LN_ARGS_SERIAL_PORT_NAME_FAILURE:
        error_message = "Failed to parse serial port name from command line "
          "arguments";
        break;
      case DicesRcPhilipsIntellivueMP70::PARSE_CMD_LN_ARGS_LOCAL_IP_ADDRESS_FAILURE:
        error_message = "Failed to parse local ip address from command line "
          "arguments";
        break;
      case DicesRcPhilipsIntellivueMP70::PARSE_CMD_LN_ARGS_BROADCAST_ADDRESS_FAILURE:
        error_message = "Failed to parse broadcast address from command line "
          "arguments";
        break;
      case DicesRcPhilipsIntellivueMP70::PARSE_CMD_LN_ARGS_DEVICE_IP_ADDRESS_FAILURE:
        error_message = "Failed to parse device ip address from command line "
          "arguments";
        break;

      case DicesRcPhilipsIntellivueMP70::UPDATE_PERIOD_MILLISEC_NOT_MULTIPLE_OF_1000_FAILURE:
        error_message = "Failed to use update period milliseconds because "
          "they must be a multiple of 1000";
        break;
      case DicesRcPhilipsIntellivueMP70::SERIAL_IO_AND_LAN_IO_BOTH_ENABLED_FAILURE:
        error_message = "Failed to enable both serial and lan io. Only one "
          "protocol must be enabled";
        break;
      case DicesRcPhilipsIntellivueMP70::SERIAL_IO_AND_LAN_IO_BOTH_DISABLED_FAILURE:
        error_message = "Failed to disable both serial and lan io. One "
          "protocol must be enabled";
        break;

      case DicesRcPhilipsIntellivueMP70::RS232_SET_TERMINATING_SEQUENCE_FAILURE:
        error_message = "Failed to set terminating sequence for RS232 read implementation.";
        break;
      case DicesRcPhilipsIntellivueMP70::RS232_OPEN_FAILURE:
        error_message = "Failed to open serial port";
        break;

      case DicesRcPhilipsIntellivueMP70::SOCKET_OPEN_FAILURE:
        error_message = "Failed to open socket port";
        break;

      case DicesRcPhilipsIntellivueMP70::BASE_DRIVER_RUN_DRIVER_FAILURE:
        error_message = "Failed to run Driver::RunDriver function";
        break;

      case DicesRcPhilipsIntellivueMP70::DDS_SEQUENCE_ENSURE_LENGTH_FAILURE:
        error_message = "Failed to ensure length of DDS Sequence";
        break;

      default: // should not be reached
        error_message = "Unknown error code";
        break;
    }
    return error_message;
  }
 private:
  // Disallow use of implicitly generated member functions:
  DicesRcPhilipsIntellivueMP70StatusMessage(const DicesRcPhilipsIntellivueMP70StatusMessage &src);
  DicesRcPhilipsIntellivueMP70StatusMessage &operator=(const DicesRcPhilipsIntellivueMP70StatusMessage &rhs);
};

#endif
