/**
 * @file device_driver_ini_parser.cxx
 * 
 * @brief Defines a class which parses device driver ini file
 *
 * More documentation can be found at 
 * http://code.jellycan.com/simpleini-doc/html/annotated.html
 */
//=============================================================================

#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include "ini-parser-device-driver.h"

static log4cplus::Logger g_root = log4cplus::Logger::getRoot();

static const char* kSectionCfgGeneral = "cfg_general";
static const char* kSectionCfgSerialComm = "cfg_serial_comm";
static const char* kSectionCfgMessaging = "cfg_messaging";
static const char* kSectionCfgDatabase = "cfg_database";

static const char* kUdi = "udi";
static const char* kManufacturer = "manufacturer";
static const char* kModel = "model";
static const char* kSoftwareVersion = "software_version";

static const char* kPortName = "port_name";
static const char* kBaudRate = "baud_rate";
static const char* kDataBits = "data_bits";
static const char* kStopBits = "stop_bits";
static const char* kHandshaking = "handshaking";
static const char* kParity = "parity";
static const char* kEnableHardwareFlowControl = "enable_hardware_flow_control";
static const char* kEnableSoftwareFlowControl = "enable_software_flow_control";

static const char* kDomainId = "domain_id";

static const char* kHost = "db_host";
static const char* kPort = "db_port";
static const char* kUser = "db_user";
static const char* kPwd = "db_pwd";
static const char* kName = "db_name";

static const char* kDefaultUDI = "";
static const char* kDefaultManufacturer = "";
static const char* kDefaultModel = "";
static const char* kDefaultSoftwareVersion = "";

static const char* kDefaultPortName = "/dev/ttyS0";
static const int kDefaultBaudRate = 9600;
static const int kDefaultDataBits = 8;
static const int kDefaultStopBits = 0;
static const int kDefaultHandshaking = 0;
static const char* kDefaultParity = "none";
static const bool kDefaultEnableHardwareFlowControl = false;
static const bool kDefaultEnableSoftwareFlowControl = false;

static const int kDefaultDomainId = 2;

static const char* kDefaultHost = "";
static const char* kDefaultPort = "";
static const char* kDefaultUser = "";
static const char* kDefaultPwd = "";
static const char* kDefaultName = "";

static const int kMaxFilePathLength = 4096;

DIMParser::DIMParser(std::string file_path)
  : _ini_file_path(file_path),
  _udi(kDefaultUDI),
  _manufacturer(kDefaultManufacturer),
  _model(kDefaultModel),
  _software_version(kDefaultSoftwareVersion),
  _port_name(kDefaultPortName),
  _baud_rate(kDefaultBaudRate),
  _data_bits(kDefaultDataBits),
  _stop_bits(kDefaultStopBits),
  _handshaking(kDefaultHandshaking),
  _parity(kDefaultParity),
  _enable_hardware_flow_control(kDefaultEnableHardwareFlowControl),
  _enable_software_flow_control(kDefaultEnableSoftwareFlowControl),
  _domain_id(kDefaultDomainId),
  _db_host(kDefaultHost),
  _db_port(kDefaultPort),
  _db_user(kDefaultUser),
  _db_pwd(kDefaultPwd),
  _db_name(kDefaultName)
{ 
}

DIMParser::~DIMParser()
{
}

std::string DIMParser::get_udi()
{
  return _udi;
}

std::string DIMParser::get_manufacturer()
{
  return _manufacturer;
}

std::string DIMParser::get_model()
{
  return _model;
}

std::string DIMParser::get_software_version()
{
  return _software_version;
}

std::string DIMParser::get_port_name()
{
  return _port_name;
}

int DIMParser::get_baud_rate()
{
  return _baud_rate;
}

int DIMParser::get_data_bits()
{
  return _data_bits;
}

int DIMParser::get_stop_bits()
{
  return _stop_bits;
}

int DIMParser::get_handshaking()
{
  return _handshaking;
}

std::string DIMParser::get_parity()
{
  return _parity;
}

bool DIMParser::get_enable_hardware_flow_control()
{
  return _enable_hardware_flow_control;
}

bool DIMParser::get_enable_software_flow_control()
{
  return _enable_software_flow_control;
}

int DIMParser::get_domain_id()
{
  return _domain_id;
}

std::string DIMParser::get_db_host()
{
  return _db_host;
}

std::string DIMParser::get_db_port()
{
  return _db_port;
}

std::string DIMParser::get_db_user()
{
  return _db_user;
}

std::string DIMParser::get_db_pwd()
{
  return _db_pwd;
}

std::string DIMParser::get_db_name()
{
  return _db_name;
}

DicesRcDeviceDriverIniParser DIMParser::Load(std::string section_name)
{
  static const char* sfn = "DIMParser::Load()";
  CSimpleIniA ini_parser;

  if (_ini_file_path.length() > kMaxFilePathLength)
  {
    LOG4CPLUS_ERROR(g_root, sfn << " The file path " << _ini_file_path
    << " exceeds the maximum string size (" << kMaxFilePathLength << ")");
    return DicesRcDeviceDriverIniParser::INI_PARSER_INVALID_FILE_PATH;
  }

  if(ini_parser.LoadFile(_ini_file_path.c_str()))
  {
    LOG4CPLUS_ERROR(g_root, sfn << " failed to load ini file " << _ini_file_path);
    return DicesRcDeviceDriverIniParser::INI_PARSER_LOAD_FILE_FAIL;
  }

  // GetValue(section name, key name) returns a const char.
  // Section is the area in the .ini file in the square braces. Think of it as
  // a header for a group of related values.
  // Key is how you identify different values, generally these are a one to one
  // mapping although SimpleIni allows for non-unique keys. 
  // See Documentation for details.

  // String Values
  // Default return is NULL
  
  // cfg_general
  if (section_name.compare(kSectionCfgGeneral) == 0)
  {
    // UDI
    if (!ini_parser.GetValue(kSectionCfgGeneral, kUdi))
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kUdi << " is NULL");
      return DicesRcDeviceDriverIniParser::INI_PARSER_GENERAL_UDI_KEY_VALUE_NOT_AVAILABLE;
    }
    else
    {
      _udi = ini_parser.GetValue(kSectionCfgGeneral, kUdi);
    }

    // Manufacturer
    if (!ini_parser.GetValue(kSectionCfgGeneral, kManufacturer))
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kManufacturer << " is NULL");
      return DicesRcDeviceDriverIniParser::INI_PARSER_GENERAL_MANUFACTURER_KEY_VALUE_NOT_AVAILABLE;
    }
    else
    {
      _manufacturer = ini_parser.GetValue(kSectionCfgGeneral, kManufacturer);
    }

    // Model
    if (!ini_parser.GetValue(kSectionCfgGeneral, kModel))
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kModel << " is NULL");
      return DicesRcDeviceDriverIniParser::INI_PARSER_GENERAL_MODEL_KEY_VALUE_NOT_AVAILABLE;
    }
    else
    {
      _model = ini_parser.GetValue(kSectionCfgGeneral, kModel);
    }

    // Software version
    if (!ini_parser.GetValue(kSectionCfgGeneral, kSoftwareVersion))
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kSoftwareVersion << " is NULL");
      return DicesRcDeviceDriverIniParser::INI_PARSER_GENERAL_SOFTWARE_VERSION_KEY_VALUE_NOT_AVAILABLE;
    }
    else
    {
      _software_version = ini_parser.GetValue(kSectionCfgGeneral,
        kSoftwareVersion);
    }
  }
  else if (section_name.compare(kSectionCfgSerialComm) == 0)
  {
    // cfg_serial_comm

    // port name
    if (!ini_parser.GetValue(kSectionCfgSerialComm, kPortName))
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kPortName << " is NULL");
      return DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_PORT_NAME_KEY_VALUE_NOT_AVAILABLE;
    }
    else
    {
      _port_name = ini_parser.GetValue(kSectionCfgSerialComm, kPortName);
    }

    // Baud rate
    long baud_rate_value = ini_parser.GetLongValue(kSectionCfgSerialComm, kBaudRate, -1);
    if (baud_rate_value > INT_MAX || baud_rate_value < INT_MIN)
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kBaudRate 
        << " value " << baud_rate_value << " is not in range of int.");
      return DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_BAUD_RATE_OUT_OF_RANGE;
    }

    _baud_rate = static_cast<int>(baud_rate_value );
    if (_baud_rate == -1)
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kBaudRate 
        << " not assigned a value in " << _ini_file_path);
      return DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_BAUD_RATE_KEY_VALUE_NOT_AVAILABLE;
    }

    // Data bits
    long data_bits_value = ini_parser.GetLongValue(kSectionCfgSerialComm, kDataBits, -1);
    if (data_bits_value > INT_MAX || data_bits_value < INT_MIN)
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kDataBits 
        << " value " << data_bits_value << " is not in range of int.");
      return DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_DATA_BITS_OUT_OF_RANGE;
    }

    _data_bits = static_cast<int>(data_bits_value);
    if (_data_bits == -1)
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kDataBits 
        << " not assigned a value in " << _ini_file_path);
      return DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_DATA_BITS_KEY_VALUE_NOT_AVAILABLE;
    }

    // Stop bits
    long stop_bits_value = ini_parser.GetLongValue(kSectionCfgSerialComm, kStopBits, -1);
    if (stop_bits_value == -1)
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kStopBits 
        << " not assigned a value in " << _ini_file_path);
      return DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_STOP_BITS_KEY_VALUE_NOT_AVAILABLE;
    }
    if (stop_bits_value > 2 || stop_bits_value < 0)
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kStopBits 
        << " value " << stop_bits_value << " is not valid - expecting 0, 1 or 2.");
      return DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_STOP_BITS_OUT_OF_RANGE;
    }
    _stop_bits = static_cast<int>(stop_bits_value);

    // handshaking
    long handshaking_value = static_cast<int>(ini_parser.GetLongValue(
      kSectionCfgSerialComm, kHandshaking, -1));
    if (handshaking_value > INT_MAX || handshaking_value < INT_MIN)
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kHandshaking 
        << " value " << handshaking_value << " is not in range of int.");
      return DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_HAND_SHAKING_OUT_OF_RANGE;
    }

    _handshaking = static_cast<int>(handshaking_value);
    if (_handshaking == -1)
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kHandshaking 
        << " not assigned a value in " << _ini_file_path);
      return DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_HAND_SHAKING_KEY_VALUE_NOT_AVAILABLE;
    }

    // parity
    if (!ini_parser.GetValue(kSectionCfgSerialComm, kParity))
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kParity << " is NULL");
      return DicesRcDeviceDriverIniParser::INI_PARSER_SERIAL_COMM_PARITY_KEY_VALUE_NOT_AVAILABLE;
    }
    else
    {
      _parity = ini_parser.GetValue(kSectionCfgSerialComm, kParity);
    }

    // Enable hardware flow control
    _enable_hardware_flow_control = ini_parser.GetBoolValue(kSectionCfgSerialComm, kEnableHardwareFlowControl);

    // Enable software flow control
    _enable_software_flow_control = ini_parser.GetBoolValue(kSectionCfgSerialComm, kEnableSoftwareFlowControl);
  }
  else if (section_name.compare(kSectionCfgMessaging) == 0)
  {
    // cfg_messaging
    // Domain ID
    long domain_id_value = ini_parser.GetLongValue(kSectionCfgMessaging, kDomainId, -1);
    if (domain_id_value > INT_MAX || domain_id_value < INT_MIN)
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kDomainId 
        << " value " << domain_id_value << " is not in range of int.");
      return DicesRcDeviceDriverIniParser::INI_PARSER_MESSAGING_DOMAIN_ID_OUT_OF_RANGE;
    }

    _domain_id = static_cast<int>(domain_id_value);
    if (_domain_id == -1)
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kDomainId 
        << " not assigned a value in " << _ini_file_path);
      return DicesRcDeviceDriverIniParser::INI_PARSER_MESSAGING_DOMAIN_ID_KEY_VALUE_NOT_AVAILABLE;
    }
  }
  else if (section_name.compare(kSectionCfgDatabase) == 0)
  {
    // host
    if (!ini_parser.GetValue(kSectionCfgDatabase, kHost))
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kHost << " is NULL");
      return DicesRcDeviceDriverIniParser::INI_PARSER_DATABASE_HOST_KEY_VALUE_NOT_AVAILABLE;
    }
    else
    {
      _db_host = ini_parser.GetValue(kSectionCfgDatabase, kHost);
    }

    // port
    if (!ini_parser.GetValue(kSectionCfgDatabase, kPort))
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kPort << " is NULL");
      return DicesRcDeviceDriverIniParser::INI_PARSER_DATABASE_PORT_KEY_VALUE_NOT_AVAILABLE;
    }
    else
    {
      _db_port = ini_parser.GetValue(kSectionCfgDatabase, kPort);
    }
    
    // user
    if (!ini_parser.GetValue(kSectionCfgDatabase, kUser))
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kUser << " is NULL");
      return DicesRcDeviceDriverIniParser::INI_PARSER_DATABASE_USER_KEY_VALUE_NOT_AVAILABLE;
    }
    else
    {
      _db_user = ini_parser.GetValue(kSectionCfgDatabase, kUser);
    }

    // pwd
    if (!ini_parser.GetValue(kSectionCfgDatabase, kPwd))
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kPwd << " is NULL");
      return DicesRcDeviceDriverIniParser::INI_PARSER_DATABASE_PWD_KEY_VALUE_NOT_AVAILABLE;
    }
    else
    {
      _db_pwd = ini_parser.GetValue(kSectionCfgDatabase, kPwd);
    }

    // database name
    if (!ini_parser.GetValue(kSectionCfgDatabase, kName))
    {
      LOG4CPLUS_ERROR(g_root, sfn << " " << kName << " is NULL");
      return DicesRcDeviceDriverIniParser::INI_PARSER_DATABASE_NAME_KEY_VALUE_NOT_AVAILABLE;
    }
    else
    {
      _db_name = ini_parser.GetValue(kSectionCfgDatabase,
        kName);
    }
  }
  else
  {
    LOG4CPLUS_ERROR(g_root, sfn << " Unknown section name " << section_name);
    return DicesRcDeviceDriverIniParser::INI_PARSER_SECTION_NAME_NOT_AVAILABLE;
  }

  return DicesRcDeviceDriverIniParser::OK;
}

DicesRcDeviceDriverIniParser DIMParser::PrintConfig()
{
  static const char* sfn = "DIMParser::PrintConfig()";
  // Return value for GetSection is a pointer to TKeyVal, which is typedef'd:
  // std::multimap<Entry,const SI_CHAR *,typename Entry::KeyOrder>. 
  
  // Entry refers to the actual ini element, and has members pItem and pMessage.
  // Rather than explicitely writing out this type, the c++11 auto keyword is 
  // recommended.
  CSimpleIniA ini_parser;
  
  if (_ini_file_path.length() > kMaxFilePathLength)
  {
    LOG4CPLUS_ERROR(g_root, sfn << " The file path " << _ini_file_path
    << " exceeds the maximum string size (" << kMaxFilePathLength << ")");
    return DicesRcDeviceDriverIniParser::INI_PARSER_INVALID_FILE_PATH;
  }

  if(ini_parser.LoadFile(_ini_file_path.c_str()))
  {
    LOG4CPLUS_ERROR(g_root, sfn << " failed to load ini file " << _ini_file_path);
    return DicesRcDeviceDriverIniParser::INI_PARSER_LOAD_FILE_FAIL;
  }

  auto map = ini_parser.GetSection("cfg_general");

  std::stringstream ss;
  // TODO: Yes, zero.  GetSection returns zero, not nullptr.  GetSection is
  // from a tool we're importing from elsewhere and I (rengland) hesitate to
  // change it without further research.
  if (map != 0)
  {
    ss << "\ncfg_general values:"  << std::endl;
    for (auto iter = map->cbegin(); iter != map->cend(); ++iter)
    {
      ss << "Key: " << iter->first.pItem << " Value: " << iter->second 
        << std::endl;
    }
  }

  map = ini_parser.GetSection("cfg_serial_comm");

  if (map != 0)
  {
    ss << "\ncfg_serial_comm values:"  << std::endl;
    for (auto iter = map->cbegin(); iter != map->cend(); ++iter)
    {
      ss << "Key: " << iter->first.pItem << " Value: " << iter->second 
        << std::endl;
    }
  }

  map = ini_parser.GetSection("cfg_messaging");

  if (map != 0)
  {
    ss << "\ncfg_messaging values:"  << std::endl;
    for (auto iter = map->cbegin(); iter != map->cend(); ++iter)
    {
      ss << "Key: " << iter->first.pItem << " Value: " << iter->second 
        << std::endl;
    }
  }

  map = ini_parser.GetSection("cfg_database");

  if (map != 0)
  {
    ss << "\ncfg_database values:"  << std::endl;
    for (auto iter = map->cbegin(); iter != map->cend(); ++iter)
    {
      ss << "Key: " << iter->first.pItem << " Value: " << iter->second 
        << std::endl;
    }
  }

  LOG4CPLUS_INFO(g_root, ss.str());
  ss.str(""); // Clear

  return DicesRcDeviceDriverIniParser::OK;
}
