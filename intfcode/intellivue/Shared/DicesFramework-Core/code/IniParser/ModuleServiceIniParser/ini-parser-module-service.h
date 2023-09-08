/**
 * @file module_service_ini_parser.h
 *
 * @brief Declares a class which parses the ini configuration file of the
 * module service. The data members of this class are set by values in an
 * external ini file.
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef DICES_MODULE_SERVICE_INI_PARSER_SRC_MODULE_SERVICE_INI_PARSER_H
#define	DICES_MODULE_SERVICE_INI_PARSER_SRC_MODULE_SERVICE_INI_PARSER_H

#include <string>
#include <memory>

enum class DicesRcModuleServiceIniParser;

class ModuleServiceIniParser
{
 public:
  ModuleServiceIniParser(std::string file_path);
  ~ModuleServiceIniParser();

  std::string get_module_udi();
  std::string get_rack_udi();
  std::string get_lcd_location_port_mapping();
  std::string get_network_interface();

  DicesRcModuleServiceIniParser Load(std::string section_name);
  DicesRcModuleServiceIniParser PrintConfig();

  ModuleServiceIniParser(const ModuleServiceIniParser &src) = delete;
  ModuleServiceIniParser &operator=(const ModuleServiceIniParser &rhs) = delete;

protected:
    struct impl;
    std::unique_ptr<impl> _pimpl;
};

#endif

