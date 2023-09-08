/**
 * @file   database_connection_ini_parser.h
 * @author M Szwaja
 *
 * @brief This is a class declaration that defines a Load function
 * which utilize SimpleIni.h. This class has variables that need
 * to be set outside of its own scope, the desired values for these
 * variables are located within an ini file, this class holds two functions 
 * for accessing these values.
 */
//=============================================================================
#ifndef DICES_DEVICE_DRIVER_INI_PARSER_SRC_DATABASE_CONNECTION_INI_PARSER_H_
#define	DICES_DEVICE_DRIVER_INI_PARSER_SRC_DATABASE_CONNECTION_INI_PARSER_H_

#include <string>
#include <memory>

enum class DicesRcDatabaseConnectionIniParser;

// This is a class that has variables that need to be set from an
// external file. The values are stored in a .ini file.
class DatabaseConnectionIniParser
{
public:
  DatabaseConnectionIniParser(const std::string& file_path);
  ~DatabaseConnectionIniParser();

  std::string get_database_host();
  std::string get_database_user();
  std::string get_database_password();
  std::string get_database_name();

  DicesRcDatabaseConnectionIniParser Load(const std::string& section_name);

  DatabaseConnectionIniParser(const DatabaseConnectionIniParser &src) = delete;
  DatabaseConnectionIniParser &operator=(const DatabaseConnectionIniParser &rhs) = delete;

protected:
  struct impl;
  std::unique_ptr<impl> _pimpl;

};

#endif

