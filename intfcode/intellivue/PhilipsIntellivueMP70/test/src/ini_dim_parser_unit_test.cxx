/**
 * @file ini_dim_parser_unit_test.cxx
 *
 * @brief Defines a unit test class for DIMParser class.
 *
 * @author M Szwaja
 */
//=============================================================================
#include "ini_dim_parser_unit_test.h"
#include "Test/Catch/catch.hpp"
#include "UnitTestReturnCodes.h"
#include "PhilipsIntellivueMP70ReturnCodes.h"
#include "Core/IniParser/simple-ini.h"

DIMParserUnitTest::DIMParserUnitTest() { }

DIMParserUnitTest::~DIMParserUnitTest() { }

DicesRcUnitTest DIMParserUnitTest::RunTests()
{
  static const char* sfn = "DIMParserUnitTest::RunTests() ";
  DicesRcUnitTest status = DicesRcUnitTest::OK;

  SECTION("get_manufacturer()")
  {
    DicesRcUnitTest test_status = get_manufacturer();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_model()")
  {
    DicesRcUnitTest test_status = get_model();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_software_version()")
  {
    DicesRcUnitTest test_status = get_software_version();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_database_name()")
  {
    DicesRcUnitTest test_status = get_database_name();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_database_user()")
  {
    DicesRcUnitTest test_status = get_database_user();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_database_password()")
  {
    DicesRcUnitTest test_status = get_database_password();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_database_host()")
  {
    DicesRcUnitTest test_status = get_database_host();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_port_name()")
  {
    DicesRcUnitTest test_status = get_port_name();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_baud_rate()")
  {
    DicesRcUnitTest test_status = get_baud_rate();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_data_bits()")
  {
    DicesRcUnitTest test_status = get_data_bits();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_stop_bits()")
  {
    DicesRcUnitTest test_status = get_stop_bits();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_handshaking()")
  {
    DicesRcUnitTest test_status = get_handshaking();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_parity()")
  {
    DicesRcUnitTest test_status = get_parity();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_enable_hardware_flow_control()")
  {
    DicesRcUnitTest test_status = get_enable_hardware_flow_control();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_enable_software_flow_control()")
  {
    DicesRcUnitTest test_status = get_enable_software_flow_control();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_connect_indication_port()")
  {
    DicesRcUnitTest test_status = get_connect_indication_port();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_protocol_udp_port()")
  {
    DicesRcUnitTest test_status = get_protocol_udp_port();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("Load()")
  {
    DicesRcUnitTest test_status = Load();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }

  return status;
}

DicesRcUnitTest DIMParserUnitTest::get_manufacturer()
{
  DIMParser parser("");
  parser._manufacturer = "";
  CHECK(parser.get_manufacturer() == "");
  parser._manufacturer = "DocBox";
  CHECK(parser.get_manufacturer() == "DocBox");

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest DIMParserUnitTest::get_model()
{
  DIMParser parser("");
  parser._model = "";
  CHECK(parser.get_model() == "");
  parser._model = "Model";
  CHECK(parser.get_model() == "Model");

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest DIMParserUnitTest::get_software_version()
{
  DIMParser parser("");
  parser._software_version = "";
  CHECK(parser.get_software_version() == "");
  parser._software_version = "V1";
  CHECK(parser.get_software_version() == "V1");

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest DIMParserUnitTest::get_database_name()
{
  DIMParser parser("");
  parser._database_name = "";
  CHECK(parser.get_database_name() == "");
  parser._database_name = "dbname";
  CHECK(parser.get_database_name() == "dbname");

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest DIMParserUnitTest::get_database_user()
{
  DIMParser parser("");
  parser._database_user = "";
  CHECK(parser.get_database_user() == "");
  parser._database_user = "dbuser";
  CHECK(parser.get_database_user() == "dbuser");

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest DIMParserUnitTest::get_database_password()
{
  DIMParser parser("");
  parser._database_password = "";
  CHECK(parser.get_database_password() == "");
  parser._database_password = "dbpassword";
  CHECK(parser.get_database_password() == "dbpassword");

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest DIMParserUnitTest::get_database_host()
{
  DIMParser parser("");
  parser._database_host = "";
  CHECK(parser.get_database_host() == "");
  parser._database_host = "dbhost";
  CHECK(parser.get_database_host() == "dbhost");

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest DIMParserUnitTest::get_port_name()
{
  DIMParser parser("");
  parser._port_name = "";
  CHECK(parser.get_port_name() == "");
  parser._port_name = "/dev/ttyS0";
  CHECK(parser.get_port_name() == "/dev/ttyS0");

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest DIMParserUnitTest::get_baud_rate()
{
  DIMParser parser("");
  parser._baud_rate = 0;
  CHECK(parser.get_baud_rate() == 0);
  parser._baud_rate = 115200;
  CHECK(parser.get_baud_rate() == 115200);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest DIMParserUnitTest::get_data_bits()
{
  DIMParser parser("");
  parser._data_bits = 0;
  CHECK(parser.get_data_bits() == 0);
  parser._data_bits = 8;
  CHECK(parser.get_data_bits() == 8);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest DIMParserUnitTest::get_stop_bits()
{
  DIMParser parser("");
  parser._stop_bits = 0;
  CHECK(parser.get_stop_bits() == 0);
  parser._stop_bits = 1;
  CHECK(parser.get_stop_bits() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest DIMParserUnitTest::get_handshaking()
{
  DIMParser parser("");
  parser._handshaking = 0;
  CHECK(parser.get_handshaking() == 0);
  parser._handshaking = 1;
  CHECK(parser.get_handshaking() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest DIMParserUnitTest::get_parity()
{
  DIMParser parser("");
  parser._parity = "";
  CHECK(parser.get_parity() == "");
  parser._parity = "none";
  CHECK(parser.get_parity() == "none");

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest DIMParserUnitTest::get_enable_hardware_flow_control()
{
  DIMParser parser("");
  parser._enable_hardware_flow_control = false;
  CHECK(parser.get_enable_hardware_flow_control() == false);
  parser._enable_hardware_flow_control = true;
  CHECK(parser.get_enable_hardware_flow_control() == true);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest DIMParserUnitTest::get_enable_software_flow_control()
{
  DIMParser parser("");
  parser._enable_software_flow_control = false;
  CHECK(parser.get_enable_software_flow_control() == false);
  parser._enable_software_flow_control = true;
  CHECK(parser.get_enable_software_flow_control() == true);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest DIMParserUnitTest::get_connect_indication_port()
{
  DIMParser parser("");
  parser._connect_indication_port = 0;
  CHECK(parser.get_connect_indication_port() == 0);
  parser._connect_indication_port = 5000;
  CHECK(parser.get_connect_indication_port() == 5000);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest DIMParserUnitTest::get_protocol_udp_port()
{
  DIMParser parser("");
  parser._protocol_udp_port = 0;
  CHECK(parser.get_protocol_udp_port() == 0);
  parser._protocol_udp_port = 5000;
  CHECK(parser.get_protocol_udp_port() == 5000);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest DIMParserUnitTest::Load()
{
  const std::string kvalid_ini_file = "test_dd_philips_intellivue_mp70.ini";
  const std::string kSectionCfgGeneral = "cfg_general";
  const std::string kSectionCfgDatabase = "cfg_database";
  const std::string kSectionCfgSerialComm = "cfg_serial_comm";
  const std::string kSectionCfgLanComm = "cfg_lan_comm";
  DIMParser parser(kvalid_ini_file);

  // Tests null pointer
  CSimpleIniA* ptr = parser._ini_parser;
  parser._ini_parser = nullptr;
  CHECK(parser.Load("") == DicesRcPhilipsIntellivueMP70::INI_PARSER_OBJECT_POINTER_IS_NULL_FAILURE);
  parser._ini_parser = ptr;

  // Tests file name too long.
  parser._ini_file_path = std::string(257, 'x');
  CHECK(parser.Load("") == DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_INVALID_FILENAME_FAILURE);

  // Tests file name max length 256, but will still fail to load.
  parser._ini_file_path = std::string(256, 'x');
  CHECK(parser.Load("") == DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_LOAD_FILE_FAILURE);

  // Test successful loading but failure to find section name
  parser._ini_file_path = kvalid_ini_file;
  CHECK(parser.Load("") == DicesRcPhilipsIntellivueMP70::PARSE_INI_CFG_FILE_SECTION_NAME_NOT_AVAILABLE_FAILURE);

  parser._manufacturer = "";
  parser._model = "";
  parser._software_version = "";
  parser._database_name = "";
  parser._database_user = "";
  parser._database_password = "";
  parser._database_host = "";
  parser._port_name = "";
  parser._baud_rate = 0;
  parser._data_bits = 0;
  parser._stop_bits = 0;
  parser._handshaking = 0;
  parser._parity = "";
  parser._enable_hardware_flow_control = false;
  parser._enable_software_flow_control = false;
  parser._connect_indication_port = 0;
  parser._protocol_udp_port = 0;

  CHECK(parser.Load(kSectionCfgGeneral) == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(parser.Load(kSectionCfgDatabase) == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(parser.Load(kSectionCfgSerialComm) == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(parser.Load(kSectionCfgLanComm) == DicesRcPhilipsIntellivueMP70::OK);

  CHECK(parser.get_manufacturer() == "Test Manufacturer");
  CHECK(parser.get_model() == "Test Model");
  CHECK(parser.get_software_version() == "Test Version");
  CHECK(parser.get_database_name() == "Test DB Name");
  CHECK(parser.get_database_user() == "Test DB User");
  CHECK(parser.get_database_password() == "Test DB Password");
  CHECK(parser.get_database_host() == "Test DB Host");
  CHECK(parser.get_port_name() == "Test Portname");
  CHECK(parser.get_baud_rate() == 1);
  CHECK(parser.get_data_bits() == 2);
  CHECK(parser.get_stop_bits() == 3);
  CHECK(parser.get_handshaking() == 4);
  CHECK(parser.get_parity() == "Test Parity");
  CHECK(parser.get_enable_hardware_flow_control() == true);
  CHECK(parser.get_enable_software_flow_control() == true);
  CHECK(parser.get_connect_indication_port() == 5);
  CHECK(parser.get_protocol_udp_port() == 6);

  return DicesRcUnitTest::OK;
}

