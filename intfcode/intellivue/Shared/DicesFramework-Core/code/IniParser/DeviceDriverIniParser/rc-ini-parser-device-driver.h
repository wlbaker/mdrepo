/**
 * @file DeviceDriverIniParserReturnCodes.h
 *
 * @brief Declares and defines a set of all return codes used in the device
 * driver ini parser tool
 *
 */
//=============================================================================
#ifndef DICES_DEVICE_DRIVER_INI_PARSER_SRC_DICES_DEVICE_DRIVER_INI_PARSER_RETURN_CODES_H_
#define DICES_DEVICE_DRIVER_INI_PARSER_SRC_DICES_DEVICE_DRIVER_INI_PARSER_RETURN_CODES_H_

#include <string>

enum class DicesRcDeviceDriverIniParser
{
  OK = 0,
  FAIL = 1,
  BAD_FUNCTION_ARGUMENT,
  INI_PARSER_LOAD_FILE_FAIL,
  INI_PARSER_INVALID_FILE_PATH,
  INI_PARSER_GENERAL_UDI_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_GENERAL_MANUFACTURER_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_GENERAL_MODEL_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_GENERAL_SOFTWARE_VERSION_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_SERIAL_COMM_PORT_NAME_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_SERIAL_COMM_BAUD_RATE_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_SERIAL_COMM_DATA_BITS_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_SERIAL_COMM_STOP_BITS_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_SERIAL_COMM_HAND_SHAKING_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_SERIAL_COMM_PARITY_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_SERIAL_COMM_HW_FLOW_CONTROL_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_SERIAL_COMM_SW_FLOW_CONTROL_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_MESSAGING_DOMAIN_ID_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_SERIAL_COMM_BAUD_RATE_OUT_OF_RANGE,
  INI_PARSER_SERIAL_COMM_DATA_BITS_OUT_OF_RANGE,
  INI_PARSER_SERIAL_COMM_STOP_BITS_OUT_OF_RANGE,
  INI_PARSER_SERIAL_COMM_HAND_SHAKING_OUT_OF_RANGE,
  INI_PARSER_MESSAGING_DOMAIN_ID_OUT_OF_RANGE,
  INI_PARSER_DATABASE_HOST_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_DATABASE_PORT_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_DATABASE_USER_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_DATABASE_PWD_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_DATABASE_NAME_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_SECTION_NAME_NOT_AVAILABLE
};

class DicesRcDeviceDriverIniParserStatusMessage
{
public:
  const static std::string DicesRcDeviceDriverIniParserToString(const DicesRcDeviceDriverIniParser error_code)
  {
    static const std::string kcfg_general_str = "[cfg_general]";
    static const std::string kcfg_serial_comm_str = "[cfg_serial_comm]";
    static const std::string kcfg_messaging_str = "[cfg_messaging]";
    static const std::string kcfg_database_str = "[cfg_database]";
    
    std::string error_message;
    switch(error_code)
    {
      case DicesRcDeviceDriverIniParser::OK:
        error_message = "Ok";
      break;
      case DicesRcDeviceDriverIniParser::FAIL:
        error_message = "Fail";
      break;
      case DicesRcDeviceDriverIniParser::BAD_FUNCTION_ARGUMENT:
        error_message = "Bad function argument";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_LOAD_FILE_FAIL:
        error_message = "Failed to load ini file";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_INVALID_FILE_PATH:
        error_message = "Invalid ini file path";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_GENERAL_UDI_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_general_str + " \"udi\" key value is not available in the ini file";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_GENERAL_MANUFACTURER_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_general_str + " \"manufacturer\" key value is not available in the ini file";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_GENERAL_MODEL_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_general_str + " \"model\" key value is not available in the ini file";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_GENERAL_SOFTWARE_VERSION_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_general_str + " \"software_version\" key value is not available in the ini file";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_PORT_NAME_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_serial_comm_str + " \"port_name\" key value is not available in the ini file";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_BAUD_RATE_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_serial_comm_str + " \"baud_rate\" key value is not available in the ini file";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_DATA_BITS_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_serial_comm_str + " \"data_bits\" key value is not available in the ini file";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_STOP_BITS_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_serial_comm_str + " \"stop_bits\" key value is not available in the ini file";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_HAND_SHAKING_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_serial_comm_str + " \"handshaking\" key value is not available in the ini file";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_PARITY_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_serial_comm_str + " \"parity\" key value is not available in the ini file";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_HW_FLOW_CONTROL_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_serial_comm_str + " \"enable_hardware_flow_control\" key value is not available in the ini file";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_SW_FLOW_CONTROL_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_serial_comm_str + " \"enable_software_flow_control\" key value is not available in the ini file";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_MESSAGING_DOMAIN_ID_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_messaging_str + " \"domain_id\" key value is not available in the ini file";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_BAUD_RATE_OUT_OF_RANGE:
        error_message = kcfg_serial_comm_str + " \"baud_rate\" value is out of range of an integer";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_DATA_BITS_OUT_OF_RANGE:
        error_message = kcfg_serial_comm_str + " \"data_bits\" value is out of range of an integer";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_STOP_BITS_OUT_OF_RANGE:
        error_message = kcfg_serial_comm_str + " \"stop_bits\" value is out of range";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_HAND_SHAKING_OUT_OF_RANGE:
        error_message = kcfg_serial_comm_str + " \"handshaking\" value is out of range of an integer";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_MESSAGING_DOMAIN_ID_OUT_OF_RANGE:
        error_message = kcfg_messaging_str + " \"baud_rate\" key value is out of range of an integer.";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_DATABASE_HOST_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_database_str + " \"db_host\" key value is not available in the ini file";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_DATABASE_PORT_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_database_str + " \"db_port\" key value is not available in the ini file";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_DATABASE_USER_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_database_str + " \"db_user\" key value is not available in the ini file";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_DATABASE_PWD_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_database_str + " \"db_pwd\" key value is not available in the ini file";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_DATABASE_NAME_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_database_str + " \"db_name\" key value is not available in the ini file";
      break;
      case DicesRcDeviceDriverIniParser::INI_PARSER_SECTION_NAME_NOT_AVAILABLE:
        error_message = "Section name is not available in the ini file";
      break;
      default:
        error_message = "Unknown error code";
      break;
    }
    return error_message;
  }

private:
  // Disallow use of implicitly generated member functions:
  DicesRcDeviceDriverIniParserStatusMessage(const DicesRcDeviceDriverIniParserStatusMessage &src);
  DicesRcDeviceDriverIniParserStatusMessage &operator=(const DicesRcDeviceDriverIniParserStatusMessage &rhs);
};

#endif
