/**
 * @file DatabaseConnectionReturnCodes.h
 *
 * @brief Declares and defines a set of all return codes used in the database
 * connection tool.
 *
 */
//=============================================================================
#ifndef DATABASE_CONNECTION_SRC_DATABASE_CONNECTION_RETURN_CODES_H_
#define DATABASE_CONNECTION_SRC_DATABASE_CONNECTION_RETURN_CODES_H_

#include <string>

enum class DicesRcDatabaseConnectionIniParser
{
  OK = 0,
  FAIL = 1,
  BAD_FUNCTION_ARGUMENT,
  INI_PARSER_LOAD_FILE_FAIL,
  INI_PARSER_INVALID_FILE_PATH,
  INI_PARSER_DATABASE_HOST_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_DATABASE_USER_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_DATABASE_PWD_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_DATABASE_NAME_KEY_VALUE_NOT_AVAILABLE,
  INI_PARSER_SECTION_NAME_NOT_AVAILABLE
};

class DicesRcDatabaseConnectionIniParserStatusMessage
{
public:
  const static std::string DicesRcDatabaseConnectionIniParserToString(const DicesRcDatabaseConnectionIniParser error_code)
  {
    static const std::string kcfg_database_str = "[cfg_database]";
    
    std::string error_message;
    switch(error_code)
    {
      case DicesRcDatabaseConnectionIniParser::OK:
        error_message = "Ok";
      break;
      case DicesRcDatabaseConnectionIniParser::FAIL:
        error_message = "Fail";
      break;
      case DicesRcDatabaseConnectionIniParser::BAD_FUNCTION_ARGUMENT:
        error_message = "Bad function argument";
      break;
      case DicesRcDatabaseConnectionIniParser::INI_PARSER_LOAD_FILE_FAIL:
        error_message = "Failed to load ini file";
      break;
      case DicesRcDatabaseConnectionIniParser::INI_PARSER_INVALID_FILE_PATH:
        error_message = "Invalid ini file path";
      break;
      case DicesRcDatabaseConnectionIniParser::INI_PARSER_DATABASE_HOST_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_database_str + " \"database_host\" key value is not available in the ini file";
      break;
      case DicesRcDatabaseConnectionIniParser::INI_PARSER_DATABASE_USER_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_database_str + " \"database_user\" key value is not available in the ini file";
      break;
      case DicesRcDatabaseConnectionIniParser::INI_PARSER_DATABASE_PWD_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_database_str + " \"database_password\" key value is not available in the ini file";
      break;
      case DicesRcDatabaseConnectionIniParser::INI_PARSER_DATABASE_NAME_KEY_VALUE_NOT_AVAILABLE:
        error_message = kcfg_database_str + " \"database_name\" key value is not available in the ini file";
      break;
      case DicesRcDatabaseConnectionIniParser::INI_PARSER_SECTION_NAME_NOT_AVAILABLE:
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
  DicesRcDatabaseConnectionIniParserStatusMessage(const DicesRcDatabaseConnectionIniParserStatusMessage &src);
  DicesRcDatabaseConnectionIniParserStatusMessage &operator=(const DicesRcDatabaseConnectionIniParserStatusMessage &rhs);
};

#endif
