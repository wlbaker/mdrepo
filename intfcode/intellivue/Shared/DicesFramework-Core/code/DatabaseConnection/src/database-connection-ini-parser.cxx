/**
 * @file database_connection_ini_parser.cxx
 * 
 * @brief Defines a class which parses database connection ini file
 *
 * More documentation can be found at 
 * http://code.jellycan.com/simpleini-doc/html/annotated.html
 */
//=============================================================================

#include "database-connection-ini-parser.h"
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include "rc-database-connection.h"
#include "simple-ini.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

static const char* kSectionCfgDatabase = "cfg_database";
static const char* kSectionAppContentDatabase = "appcontent_database";


static const char* kHost = "database_host";
static const char* kUser = "database_user";
static const char* kPwd = "database_password";
static const char* kName = "database_name";

static const char* kDefaultHost = "";
static const char* kDefaultUser = "";
static const char* kDefaultPwd = "";
static const char* kDefaultName = "";

static const int kMaxFilePathLength = 4096;

struct DatabaseConnectionIniParser::impl
{
  // Database configuration
  std::string _database_host;
  std::string _database_user;
  std::string _database_password;
  std::string _database_name;

  std::string _ini_file_path;

  impl() = default;

  ~impl() = default;

  DicesRcDatabaseConnectionIniParser Load(const std::string& section_name)
  {
    static const char* sfn = "DatabaseConnectionIniParser::Load() ";
    CSimpleIniA ini_parser;

    if (_ini_file_path.length() > kMaxFilePathLength)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "The file path " << _ini_file_path
      << " exceeds the maximum string size (" << kMaxFilePathLength << ")");
      return DicesRcDatabaseConnectionIniParser::INI_PARSER_INVALID_FILE_PATH;
    }

    if(ini_parser.LoadFile(_ini_file_path.c_str()))
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to load ini file " << _ini_file_path);
      return DicesRcDatabaseConnectionIniParser::INI_PARSER_LOAD_FILE_FAIL;
    }

    // GetValue(section name, key name) returns a const char.
    // Section is the area in the .ini file in the square braces. Think of it as
    // a header for a group of related values.
    // Key is how you identify different values, generally these are a one to one
    // mapping although SimpleIni allows for non-unique keys.
    // See Documentation for details.

    // String Values
    // Default return is NULL
    if (section_name.compare(kSectionCfgDatabase) == 0)
    {
      // host
      if (!ini_parser.GetValue(kSectionCfgDatabase, kHost))
      {
        LOG4CPLUS_ERROR(root_logger, sfn << kHost << " is NULL");
        return DicesRcDatabaseConnectionIniParser::INI_PARSER_DATABASE_HOST_KEY_VALUE_NOT_AVAILABLE;
      }
      else
      {
        _database_host = ini_parser.GetValue(kSectionCfgDatabase, kHost);
      }

      // user
      if (!ini_parser.GetValue(kSectionCfgDatabase, kUser))
      {
        LOG4CPLUS_ERROR(root_logger, sfn << kUser << " is NULL");
        return DicesRcDatabaseConnectionIniParser::INI_PARSER_DATABASE_USER_KEY_VALUE_NOT_AVAILABLE;
      }
      else
      {
        _database_user = ini_parser.GetValue(kSectionCfgDatabase, kUser);
      }

      // pwd
      if (!ini_parser.GetValue(kSectionCfgDatabase, kPwd))
      {
        LOG4CPLUS_ERROR(root_logger, sfn << kPwd << " is NULL");
        return DicesRcDatabaseConnectionIniParser::INI_PARSER_DATABASE_PWD_KEY_VALUE_NOT_AVAILABLE;
      }
      else
      {
        _database_password = ini_parser.GetValue(kSectionCfgDatabase, kPwd);
      }

      // database name
      if (!ini_parser.GetValue(kSectionCfgDatabase, kName))
      {
        LOG4CPLUS_ERROR(root_logger, sfn << kName << " is NULL");
        return DicesRcDatabaseConnectionIniParser::INI_PARSER_DATABASE_NAME_KEY_VALUE_NOT_AVAILABLE;
      }
      else
      {
        _database_name = ini_parser.GetValue(kSectionCfgDatabase, kName);
      }
    }
    else if (section_name.compare(kSectionAppContentDatabase) == 0)
    {
      // host
      if (!ini_parser.GetValue(kSectionAppContentDatabase, kHost))
      {
        LOG4CPLUS_ERROR(root_logger, sfn << kHost << " is NULL");
        return DicesRcDatabaseConnectionIniParser::INI_PARSER_DATABASE_HOST_KEY_VALUE_NOT_AVAILABLE;
      }
      else
      {
        _database_host = ini_parser.GetValue(kSectionAppContentDatabase, kHost);
      }

      // user
      if (!ini_parser.GetValue(kSectionAppContentDatabase, kUser))
      {
        LOG4CPLUS_ERROR(root_logger, sfn << kUser << " is NULL");
        return DicesRcDatabaseConnectionIniParser::INI_PARSER_DATABASE_USER_KEY_VALUE_NOT_AVAILABLE;
      }
      else
      {
        _database_user = ini_parser.GetValue(kSectionAppContentDatabase, kUser);
      }

      // pwd
      if (!ini_parser.GetValue(kSectionAppContentDatabase, kPwd))
      {
        LOG4CPLUS_ERROR(root_logger, sfn << kPwd << " is NULL");
        return DicesRcDatabaseConnectionIniParser::INI_PARSER_DATABASE_PWD_KEY_VALUE_NOT_AVAILABLE;
      }
      else
      {
        _database_password = ini_parser.GetValue(kSectionAppContentDatabase, kPwd);
      }

      // database name
      if (!ini_parser.GetValue(kSectionAppContentDatabase, kName))
      {
        LOG4CPLUS_ERROR(root_logger, sfn << kName << " is NULL");
        return DicesRcDatabaseConnectionIniParser::INI_PARSER_DATABASE_NAME_KEY_VALUE_NOT_AVAILABLE;
      }
      else
      {
        _database_name = ini_parser.GetValue(kSectionAppContentDatabase, kName);
      }
    }
    else
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Unknown section name " << section_name);
      return DicesRcDatabaseConnectionIniParser::INI_PARSER_SECTION_NAME_NOT_AVAILABLE;
    }

    return DicesRcDatabaseConnectionIniParser::OK;
  }
};

DatabaseConnectionIniParser::DatabaseConnectionIniParser(const std::string& file_path)
  :_pimpl(nullptr)
{
  static const char* sfn = "DatabaseConnectionIniParser::DatabaseConnectionIniParser() ";
  _pimpl = std::unique_ptr<impl>(new (std::nothrow) impl());
  if (!_pimpl)
  {
    LOG4CPLUS_ERROR(log4cplus::Logger::getRoot(), sfn << "Failed to create impl");
    return;
  }

  _pimpl->_ini_file_path = file_path;
}

DatabaseConnectionIniParser::~DatabaseConnectionIniParser()
{
}

std::string DatabaseConnectionIniParser::get_database_host()
{
  return _pimpl->_database_host;
}

std::string DatabaseConnectionIniParser::get_database_user()
{
  return _pimpl->_database_user;
}

std::string DatabaseConnectionIniParser::get_database_password()
{
  return _pimpl->_database_password;
}

std::string DatabaseConnectionIniParser::get_database_name()
{
  return _pimpl->_database_name;
}

DicesRcDatabaseConnectionIniParser DatabaseConnectionIniParser::Load(const std::string& section_name)
{
  return _pimpl->Load(section_name);
}
