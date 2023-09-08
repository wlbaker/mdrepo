/**
 * @file module_service_ini_parser.cxx
 *
 * @brief Defines a class which parses the ini configuration file of the
 * module service. The data members of this class are set by values in an
 * external ini file.
 *
 * @author M Szwaja
 */
//=============================================================================

#include "ini-parser-module-service.h"
#include "simple-ini.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include "rc-ini-parser-module-service.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

static const char* kSectionCfgGeneral = "cfg_general";

static const char* kModuleUdi = "module_udi";
static const char* kRackUdi = "rack_udi";
static const char* kLCDLocationPortMapping = "lcd_location_port_mapping";
static const char* kNetworkInterface = "network_interface";

static const int kMaxFilePathLength = 4096;


struct ModuleServiceIniParser::impl
{
  std::string _module_udi;
  std::string _rack_udi;
  std::string _lcd_location_port_mapping;
  std::string _network_interface;

  std::string _ini_file_path;

  impl(std::string file_path)
    : _ini_file_path(file_path)
  {
  }

  ~impl() = default;

  DicesRcModuleServiceIniParser Load(std::string section_name)
  {
    static const char* sfn = "ModuleServiceIniParser::Load()";
    CSimpleIniA ini_parser;

    // Permit data values to span multiple lines in ini file
    ini_parser.SetMultiLine();

    if (_ini_file_path.length() > kMaxFilePathLength)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << " The file path " << _ini_file_path
        << " exceeds the maximum string size (" << kMaxFilePathLength << ")");
      return DicesRcModuleServiceIniParser::INI_PARSER_INVALID_FILE_PATH;
    }

    if (ini_parser.LoadFile(_ini_file_path.c_str()))
    {
      LOG4CPLUS_ERROR(root_logger, sfn << " failed to load ini file " << _ini_file_path);
      return DicesRcModuleServiceIniParser::INI_PARSER_LOAD_FILE_FAIL;
    }

    // Check for valid section name

    if (section_name.compare(kSectionCfgGeneral) != 0)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << " Unknown section name " << section_name);
      return DicesRcModuleServiceIniParser::INI_PARSER_SECTION_NAME_NOT_AVAILABLE;
    }

    // GetValue(section name, key name) returns a const char.
    // Section is the area in the .ini file in the square braces. Think of it as
    // a header for a group of related values.
    // Key is how you identify different values, generally these are a one to one
    // mapping although SimpleIni allows for non-unique keys.
    // See Documentation for details.

    // For String values, the default return is NULL.

    // Module UDI
    if (!ini_parser.GetValue(kSectionCfgGeneral, kModuleUdi))
    {
      LOG4CPLUS_ERROR(root_logger, sfn << " " << kModuleUdi << " is NULL");
      return DicesRcModuleServiceIniParser::INI_PARSER_GENERAL_MODULE_UDI_KEY_VALUE_NOT_AVAILABLE;
    }
    else
    {
      _module_udi = ini_parser.GetValue(kSectionCfgGeneral, kModuleUdi);
    }

    // Rack UDI
    if (!ini_parser.GetValue(kSectionCfgGeneral, kRackUdi))
    {
      LOG4CPLUS_ERROR(root_logger, sfn << " " << kRackUdi << " is NULL");
      return DicesRcModuleServiceIniParser::INI_PARSER_GENERAL_RACK_UDI_KEY_VALUE_NOT_AVAILABLE;
    }
    else
    {
      _rack_udi = ini_parser.GetValue(kSectionCfgGeneral, kRackUdi);
    }

    // LCD location port mapping
    if (!ini_parser.GetValue(kSectionCfgGeneral, kLCDLocationPortMapping))
    {
      LOG4CPLUS_ERROR(root_logger, sfn << " " << kLCDLocationPortMapping
        << " is NULL");
      return DicesRcModuleServiceIniParser::INI_PARSER_GENERAL_LCD_LOCATION_PORT_MAPPING_KEY_VALUE_NOT_AVAILABLE;
    }
    else
    {
      _lcd_location_port_mapping = ini_parser.GetValue(
        kSectionCfgGeneral,
        kLCDLocationPortMapping);
    }

    // Network Interface
    if (!ini_parser.GetValue(kSectionCfgGeneral, kNetworkInterface))
    {
      LOG4CPLUS_ERROR(root_logger, sfn << " " << kNetworkInterface
        << " is NULL");
      return DicesRcModuleServiceIniParser::INI_PARSER_GENERAL_NETWORK_INTERFACE_KEY_VALUE_NOT_AVAILABLE;
    }
    else
    {
      _network_interface = ini_parser.GetValue(
        kSectionCfgGeneral,
        kNetworkInterface);
    }


    return DicesRcModuleServiceIniParser::OK;
  }

  DicesRcModuleServiceIniParser PrintConfig()
  {
    static const char* sfn = "ModuleServiceIniParser::PrintConfig()";
    std::stringstream ss;

    ss << kSectionCfgGeneral << " values:" << std::endl
      << kModuleUdi << " = " << _module_udi << std::endl
      << kRackUdi << " = " << _rack_udi << std::endl
      << kLCDLocationPortMapping << " = " << _lcd_location_port_mapping
      << std::endl
      << kNetworkInterface << " = " << _network_interface
      << std::endl;
    LOG4CPLUS_INFO(root_logger, ss.str());

    return DicesRcModuleServiceIniParser::OK;
  }
};

ModuleServiceIniParser::ModuleServiceIniParser(std::string file_path)
  : _pimpl(nullptr)
{
  static const char* sfn = "ModuleServiceIniParser::ModuleServiceIniParser() ";
  _pimpl = std::unique_ptr<impl>(new (std::nothrow) impl(file_path));
  if (!_pimpl)
  {
    LOG4CPLUS_ERROR(root_logger, "Failed to create impl");
    return;
  }
}

ModuleServiceIniParser::~ModuleServiceIniParser()
{
}

std::string ModuleServiceIniParser::get_module_udi()
{
  return _pimpl->_module_udi;
}

std::string ModuleServiceIniParser::get_rack_udi()
{
  return _pimpl->_rack_udi;
}

std::string ModuleServiceIniParser::get_lcd_location_port_mapping()
{
  return _pimpl->_lcd_location_port_mapping;
}

std::string ModuleServiceIniParser::get_network_interface()
{
  return _pimpl->_network_interface;
}

DicesRcModuleServiceIniParser ModuleServiceIniParser::Load(std::string section_name)
{
  return _pimpl->Load(section_name);
}

DicesRcModuleServiceIniParser ModuleServiceIniParser::PrintConfig()
{
  return _pimpl->PrintConfig();
}

