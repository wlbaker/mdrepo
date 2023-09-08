/**
 * @file ModuleServiceIniParserReturnCodes.h
 *
 * @brief Declares and defines a set of all return codes used in the module
 * service ini parser tool
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef DICES_MODULE_SERVICE_INI_PARSER_SRC_DICES_MODULE_SERVICE_INI_PARSER_RETURN_CODES_H_
#define DICES_MODULE_SERVICE_INI_PARSER_SRC_DICES_MODULE_SERVICE_INI_PARSER_RETURN_CODES_H_

#include <string>

enum class DicesRcModuleServiceIniParser
{
  OK = 0,
  FAIL = 1,
  BAD_FUNCTION_ARGUMENT,
  INI_PARSER_LOAD_FILE_FAIL,
  INI_PARSER_INVALID_FILE_PATH,
  INI_PARSER_GENERAL_MODULE_UDI_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_GENERAL_RACK_UDI_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_GENERAL_LCD_LOCATION_PORT_MAPPING_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_GENERAL_NETWORK_INTERFACE_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_SECTION_NAME_NOT_AVAILABLE
};

class DicesRcModuleServiceIniParserStatusMessage
{
 public:

  const static std::string DicesRcModuleServiceIniParserToString(const DicesRcModuleServiceIniParser error_code)
  {
    static const std::string kcfg_general_str = "[cfg_general]";

    std::string error_message;
    switch (error_code)
    {
      case DicesRcModuleServiceIniParser::OK:
        error_message = "Ok";
        break;
      case DicesRcModuleServiceIniParser::FAIL:
        error_message = "Fail";
        break;
      case DicesRcModuleServiceIniParser::BAD_FUNCTION_ARGUMENT:
        error_message = "Bad function argument";
        break;
      case DicesRcModuleServiceIniParser::INI_PARSER_LOAD_FILE_FAIL:
        error_message = "Failed to load ini file";
        break;
      case DicesRcModuleServiceIniParser::INI_PARSER_INVALID_FILE_PATH:
        error_message = "Invalid ini file path";
        break;
      case DicesRcModuleServiceIniParser::INI_PARSER_GENERAL_MODULE_UDI_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_general_str + " \"module_udi\" key value is "
          "not available in the ini file";
        break;
      case DicesRcModuleServiceIniParser::INI_PARSER_GENERAL_RACK_UDI_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_general_str + " \"rack_udi\" key value is not "
          "available in the ini file";
        break;
      case DicesRcModuleServiceIniParser::INI_PARSER_GENERAL_LCD_LOCATION_PORT_MAPPING_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_general_str + " \"lcd_location_port_mapping\" "
          "key value is not available in the ini file";
        break;
      case DicesRcModuleServiceIniParser::INI_PARSER_GENERAL_NETWORK_INTERFACE_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_general_str + " \"network_interface\" "
          "key value is not available in the ini file";
        break;
      case DicesRcModuleServiceIniParser::INI_PARSER_SECTION_NAME_NOT_AVAILABLE:
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
  DicesRcModuleServiceIniParserStatusMessage(const DicesRcModuleServiceIniParserStatusMessage &src);
  DicesRcModuleServiceIniParserStatusMessage &operator=(const DicesRcModuleServiceIniParserStatusMessage &rhs);
};

#endif

