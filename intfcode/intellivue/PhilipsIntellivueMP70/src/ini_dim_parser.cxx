/**
 * @file SimpleIni_parser.cxx
 * 
 * @brief Implementation file for SimpleIni_parser class.
 * 
 * More documentation can be found at 
 * http://code.jellycan.com/simpleini-doc/html/annotated.html
 **/

#include "ini_dim_parser.h"
#include <sstream>
#include "stdlib.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include "PhilipsIntellivueMP70ReturnCodes.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

static const char* kSectionCfgGeneral = "cfg_general";
static const char* kSectionCfgDatabase = "cfg_database";
static const char* kSectionCfgSerialComm = "cfg_serial_comm";
static const char* kSectionCfgLanComm = "cfg_lan_comm";

static const char* kManufacturer = "manufacturer";
static const char* kModel = "model";
static const char* kSoftwareVersion = "software_version";

static const char* kDatabaseName = "database_name";
static const char* kDatabaseUser = "database_user";
static const char* kDatabasePassword = "database_password";
static const char* kDatabaseHost = "database_host";

static const char* kDisableSerialIo = "disable_serial_io";
static const char* kPortName = "port_name";
static const char* kBaudRate = "baud_rate";
static const char* kDataBits = "data_bits";
static const char* kStopBits = "stop_bits";
static const char* kHandshaking = "handshaking";
static const char* kParity = "parity";
static const char* kEnableHardwareFlowControl = "enable_hardware_flow_control";
static const char* kEnableSoftwareFlowControl = "enable_software_flow_control";

static const char* kDisableLanIo = "disable_lan_io";
static const char* kConnectIndicationPort = "connect_indication_port";
static const char* kProtocolUDPPort = "protocol_udp_port";

static const char* kDefaultManufacturer = "Philips";
static const char* kDefaultModel = "Intellivue-MP70";
static const char* kDefaultSoftwareVersion = "V1.2.3.4";
static const bool kDefaultDisableSerialIo = false;
static const char* kDefaultPortName = "/dev/ttyS0";
static const int kDefaultBaudRate = 115200;
static const int kDefaultDataBits = 8;
static const int kDefaultStopBits = 0;
static const int kDefaultHandshaking = 0;
static const char* kDefaultParity = "none";
static const bool kDefaultEnableHardwareFlowControl = false;
static const bool kDefaultEnableSoftwareFlowControl = false;
static const bool kDefaultDisableLanIo = false;
static const int kDefaultConnectIndicationPort = 24005;
static const int kDefaultProtocolUDPPort = 24105;

DIMParser::DIMParser(std::string file_path)
  : IniParser(file_path),
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
  _connect_indication_port(kDefaultConnectIndicationPort),
  _protocol_udp_port(kDefaultProtocolUDPPort) { }

DIMParser::~DIMParser() { }

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

std::string DIMParser::get_database_name()
{
  return _database_name;
}

std::string DIMParser::get_database_user()
{
  return _database_user;
}

std::string DIMParser::get_database_password()
{
  return _database_password;
}

std::string DIMParser::get_database_host()
{
  return _database_host;
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

int DIMParser::get_connect_indication_port()
{
  return _connect_indication_port;
}

int DIMParser::get_protocol_udp_port()
{
  return _protocol_udp_port;
}

DicesRcPhilipsIntellivueMP70 DIMParser::Load(std::string section_name)
{
  static const char* sfn = "DIMParser::Load() ";

  if (!_ini_parser)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "_ini_parser is a null pointer.");
    return DicesRcPhilipsIntellivueMP70::INI_PARSER_OBJECT_POINTER_IS_NULL_FAILURE;
  }

  const int kmax_file_size = 256;
  if (_ini_file_path.length() > kmax_file_size)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "File name exceeds max string size ("
      << kmax_file_size << ").");
    return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_INVALID_FILENAME_FAILURE;
  }

  if (_ini_parser->LoadFile(_ini_file_path.c_str()))
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to load " << _ini_file_path
      << " file.");
    return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_LOAD_FILE_FAILURE;
  }

  // GetValue(section name, key name) returns a const char.
  // Section is the area in the .ini file in the square braces. Think of it as
  // a header for a group of related values.
  // Key is how you identify different values, generally these are a one to one
  // mapping although SimpleIni allows for non-unique keys. 
  // See Documentation for details. TODO

  // String Values
  // Default return is NULL

  // cfg_general
  if (!strcmp(section_name.c_str(), kSectionCfgGeneral))
  {
    // Manufacturer
    if (!_ini_parser->GetValue(kSectionCfgGeneral, kManufacturer))
    {
      LOG4CPLUS_ERROR(root_logger, sfn << kManufacturer << " is NULL");
      return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_KEY_VALUE_NOT_AVAILABLE_FAILURE;
    }
    else
      _manufacturer = _ini_parser->GetValue(kSectionCfgGeneral, kManufacturer);

    // Model
    if (!_ini_parser->GetValue(kSectionCfgGeneral, kModel))
    {
      LOG4CPLUS_ERROR(root_logger, sfn << kModel << " is NULL");
      return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_KEY_VALUE_NOT_AVAILABLE_FAILURE;
    }
    else
      _model = _ini_parser->GetValue(kSectionCfgGeneral, kModel);

    // Software version
    if (!_ini_parser->GetValue(kSectionCfgGeneral, kSoftwareVersion))
    {
      LOG4CPLUS_ERROR(root_logger, sfn << kSoftwareVersion << " is NULL");
      return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_KEY_VALUE_NOT_AVAILABLE_FAILURE;
    }
    else
      _software_version = _ini_parser->GetValue(kSectionCfgGeneral, kSoftwareVersion);
  }
  else if (!strcmp(section_name.c_str(), kSectionCfgDatabase))
  {
    // Database name
    if (!_ini_parser->GetValue(kSectionCfgDatabase, kDatabaseName))
    {
      LOG4CPLUS_ERROR(root_logger, sfn << kDatabaseName << " is NULL");
      return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_KEY_VALUE_NOT_AVAILABLE_FAILURE;
    }
    else
      _database_name = _ini_parser->GetValue(kSectionCfgDatabase, kDatabaseName);

    // Database user
    if (!_ini_parser->GetValue(kSectionCfgDatabase, kDatabaseUser))
    {
      LOG4CPLUS_ERROR(root_logger, sfn << kDatabaseUser << " is NULL");
      return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_KEY_VALUE_NOT_AVAILABLE_FAILURE;
    }
    else
      _database_user = _ini_parser->GetValue(kSectionCfgDatabase, kDatabaseUser);

    // Database password
    if (!_ini_parser->GetValue(kSectionCfgDatabase, kDatabasePassword))
    {
      LOG4CPLUS_ERROR(root_logger, sfn << kDatabasePassword << " is NULL");
      return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_KEY_VALUE_NOT_AVAILABLE_FAILURE;
    }
    else
      _database_password = _ini_parser->GetValue(kSectionCfgDatabase, kDatabasePassword);

    // Database host
    if (!_ini_parser->GetValue(kSectionCfgDatabase, kDatabaseHost))
    {
      LOG4CPLUS_ERROR(root_logger, sfn << kDatabaseHost << " is NULL");
      return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_KEY_VALUE_NOT_AVAILABLE_FAILURE;
    }
    else
      _database_host = _ini_parser->GetValue(kSectionCfgDatabase, kDatabaseHost);
  }
  else if (!strcmp(section_name.c_str(), kSectionCfgSerialComm))
  {
    // cfg_serial_comm
    // port name
    if (!_ini_parser->GetValue(kSectionCfgSerialComm, kPortName))
    {
      LOG4CPLUS_ERROR(root_logger, sfn << kPortName << " is NULL");
      return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_KEY_VALUE_NOT_AVAILABLE_FAILURE;
    }
    else
      _port_name = _ini_parser->GetValue(kSectionCfgSerialComm, kPortName);

    // Baud rate
    _baud_rate = static_cast<int>(_ini_parser->GetLongValue(
      kSectionCfgSerialComm, kBaudRate, -1));
    if (_baud_rate == -1)
    {
      LOG4CPLUS_WARN(root_logger, sfn << kBaudRate
        << " not assigned a value in " << _ini_file_path);
      return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_KEY_VALUE_NOT_AVAILABLE_FAILURE;
    }

    // Data bits
    _data_bits = static_cast<int>(_ini_parser->GetLongValue(
      kSectionCfgSerialComm, kDataBits, -1));
    if (_data_bits == -1)
    {
      LOG4CPLUS_WARN(root_logger, sfn << kDataBits
        << " not assigned a value in " << _ini_file_path);
      return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_KEY_VALUE_NOT_AVAILABLE_FAILURE;
    }

    // Stop bits
    _stop_bits = static_cast<int>(_ini_parser->GetLongValue(
      kSectionCfgSerialComm, kStopBits, -1));
    if (_stop_bits == -1)
    {
      LOG4CPLUS_WARN(root_logger, sfn << kStopBits
        << " not assigned a value in " << _ini_file_path);
      return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_KEY_VALUE_NOT_AVAILABLE_FAILURE;
    }

    // handshaking
    _handshaking = static_cast<int>(_ini_parser->GetLongValue(
      kSectionCfgSerialComm, kHandshaking, -1));
    if (_handshaking == -1)
    {
      LOG4CPLUS_WARN(root_logger, sfn << kHandshaking
        << " not assigned a value in " << _ini_file_path);
      return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_KEY_VALUE_NOT_AVAILABLE_FAILURE;
    }

    // parity
    if (!_ini_parser->GetValue(kSectionCfgSerialComm, kParity))
    {
      LOG4CPLUS_ERROR(root_logger, sfn << kParity << " is NULL");
      return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_KEY_VALUE_NOT_AVAILABLE_FAILURE;
    }
    else
      _parity = _ini_parser->GetValue(kSectionCfgSerialComm, kParity);

    // Enable hardware flow control
    _enable_hardware_flow_control = _ini_parser->GetBoolValue(kSectionCfgSerialComm, kEnableHardwareFlowControl);

    // Enable software flow control
    _enable_software_flow_control = _ini_parser->GetBoolValue(kSectionCfgSerialComm, kEnableSoftwareFlowControl);
  }
  else if (!strcmp(section_name.c_str(), kSectionCfgLanComm))
  {
    // cfg_lan_comm
    // Connect Indication Port
    _connect_indication_port = static_cast<int>(_ini_parser->GetLongValue(
      kSectionCfgLanComm, kConnectIndicationPort, -1));
    if (_connect_indication_port == -1)
    {
      LOG4CPLUS_WARN(root_logger, sfn << kConnectIndicationPort
        << " not assigned a value in " << _ini_file_path);
      return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_KEY_VALUE_NOT_AVAILABLE_FAILURE;
    }

    // Protocol UDP Port
    _protocol_udp_port = static_cast<int>(_ini_parser->GetLongValue(
      kSectionCfgLanComm, kProtocolUDPPort, -1));
    if (_protocol_udp_port == -1)
    {
      LOG4CPLUS_WARN(root_logger, sfn << kProtocolUDPPort
        << " not assigned a value in " << _ini_file_path);
      return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_KEY_VALUE_NOT_AVAILABLE_FAILURE;
    }
  }
  else
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Unknown section name " << section_name);
    return DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_SECTION_NAME_NOT_AVAILABLE_FAILURE;
  }

  return DicesRcPhilipsIntellivueMP70::OK;
}

