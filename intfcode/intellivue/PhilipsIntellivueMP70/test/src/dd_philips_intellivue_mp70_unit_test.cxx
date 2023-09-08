/**
 * @file dd_philips_intellivue_mp70_unit_test.cxx
 *
 * @brief Defines a unit test class for DDPhilipsIntellivueMP70 class.
 *
 * @author M Szwaja
 */
//=============================================================================
#include "dd_philips_intellivue_mp70_unit_test.h"
#include <cstring>
#include "dd_philips_intellivue_mp70.h"
#include "Test/Catch/catch.hpp"
#include "UnitTestReturnCodes.h"
#include "PhilipsIntellivueMP70ReturnCodes.h"

DDPhilipsIntellivueMP70UnitTest::DDPhilipsIntellivueMP70UnitTest() { }

DDPhilipsIntellivueMP70UnitTest::~DDPhilipsIntellivueMP70UnitTest() { }

DicesRcUnitTest DDPhilipsIntellivueMP70UnitTest::RunTests()
{
  static const char* sfn = "DDPhilipsIntellivueMP70UnitTest::RunTests() ";
  DicesRcUnitTest status = DicesRcUnitTest::OK;

  SECTION("ParseIniCfgFile()")
  {
    DicesRcUnitTest test_status = ParseIniCfgFile();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("ParseCommandLine()")
  {
    DicesRcUnitTest test_status = ParseCommandLine();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("RunDriver()")
  {
    DicesRcUnitTest test_status = RunDriver();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  return status;
}

DicesRcUnitTest DDPhilipsIntellivueMP70UnitTest::ParseIniCfgFile()
{
  DDPhilipsIntellivueMP70 dd;
  const std::string ini_path = "test_dd_philips_intellivue_mp70.ini";

  // Checks for default values before parsing ini file.
  CHECK(dd._manufacturer == "");
  CHECK(dd._model == "");
  CHECK(dd._software_version == "");
  CHECK(dd._database_name == "");
  CHECK(dd._database_user == "");
  CHECK(dd._database_password == "");
  CHECK(dd._database_host == "");
  CHECK(dd._portname == "");
  CHECK(dd._baudrate == 115200);
  CHECK(dd._databits == 8);
  CHECK(dd._stopbits == 0);
  CHECK(dd._handshaking == 0);
  CHECK(dd._parity == "");
  CHECK(dd._enable_hardware_flow_control == false);
  CHECK(dd._enable_software_flow_control == false);
  CHECK(dd._connect_indication_receive_port_number == 24005);
  CHECK(dd._upd_receive_port_number == 24105);

  // Parses the ini file.
  CHECK(dd.ParseIniCfgFile(ini_path) == DicesRcPhilipsIntellivueMP70::OK);

  // Checks for parsed values from the ini file.
  CHECK(dd._manufacturer == "Test Manufacturer");
  CHECK(dd._model == "Test Model");
  CHECK(dd._software_version == "Test Version");
  CHECK(dd._database_name == "Test DB Name");
  CHECK(dd._database_user == "Test DB User");
  CHECK(dd._database_password == "Test DB Password");
  CHECK(dd._database_host == "Test DB Host");
  CHECK(dd._portname == "Test Portname");
  CHECK(dd._baudrate == 1);
  CHECK(dd._databits == 2);
  CHECK(dd._stopbits == 3);
  CHECK(dd._handshaking == 4);
  CHECK(dd._parity == "Test Parity");
  CHECK(dd._enable_hardware_flow_control == true);
  CHECK(dd._enable_software_flow_control == true);
  CHECK(dd._connect_indication_receive_port_number == 5);
  CHECK(dd._upd_receive_port_number == 6);

  // Make sure we can successfully call the function again.
  CHECK(dd.ParseIniCfgFile(ini_path) == DicesRcPhilipsIntellivueMP70::OK);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest DDPhilipsIntellivueMP70UnitTest::ParseCommandLine()
{
  DDPhilipsIntellivueMP70 dd;

  // Test for failure when passing null pointer.
  CHECK(dd.ParseCommandLine(0, nullptr) == DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE);

  // Allocate and set command line  arguments for testing.
  int argc = 11;
  char** argv = new (std::nothrow) char*[argc]();
  argv[0] = new (std::nothrow) char[40]();
  argv[1] = new (std::nothrow) char[40]();
  argv[2] = new (std::nothrow) char[40]();
  argv[3] = new (std::nothrow) char[40]();
  argv[4] = new (std::nothrow) char[40]();
  argv[5] = new (std::nothrow) char[40]();
  argv[6] = new (std::nothrow) char[40]();
  argv[7] = new (std::nothrow) char[40]();
  argv[8] = new (std::nothrow) char[40]();
  argv[9] = new (std::nothrow) char[40]();
  argv[10] = new (std::nothrow) char[40]();
  strncpy(argv[0], "empty", 40);
  strncpy(argv[1], "-udi", 40);
  strncpy(argv[2], "test udi", 40);
  strncpy(argv[3], "-portname", 40);
  strncpy(argv[4], "/dev/ttyS4", 40);
  strncpy(argv[5], "-localIp", 40);
  strncpy(argv[6], "1.1.1.1", 40);
  strncpy(argv[7], "-bcast", 40);
  strncpy(argv[8], "2.2.2.2", 40);
  strncpy(argv[9], "-deviceIp", 40);
  strncpy(argv[10], "3.3.3.3", 40);

  // No udi
  CHECK(dd.ParseCommandLine(1, argv) == DicesRcPhilipsIntellivueMP70::PARSE_CMD_LN_ARGS_UDI_FAILURE);

  // Udi option, but no argument
  dd._udi = "";
  CHECK(dd.ParseCommandLine(2, argv) == DicesRcPhilipsIntellivueMP70::PARSE_CMD_LN_ARGS_UDI_FAILURE);
  CHECK(dd._udi == "");

  // udi option and argument
  dd._udi = "";
  CHECK(dd.ParseCommandLine(3, argv) == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(dd._udi == "test udi");

  // no portname argument
  dd._portname = "";
  dd._udi = "";
  CHECK(dd.ParseCommandLine(4, argv) == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(dd._udi == "test udi");
  CHECK(dd._portname == "");

  // udi and portname set.
  dd._portname = "";
  dd._udi = "";
  CHECK(dd.ParseCommandLine(5, argv) == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(dd._portname == "/dev/ttyS4");
  CHECK(dd._udi == "test udi");

  // Test everything.
  dd._portname = "";
  dd._udi = "";
  dd._local_ip_address = "";
  dd._broadcast_address = "";
  dd._device_ip_address = "";
  CHECK(dd.ParseCommandLine(11, argv) == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(dd._portname == "/dev/ttyS4");
  CHECK(dd._udi == "test udi");
  CHECK(dd._local_ip_address == "1.1.1.1");
  CHECK(dd._broadcast_address == "2.2.2.2");
  CHECK(dd._device_ip_address == "3.3.3.3");

  // Test no local ip argument
  dd._portname = "";
  dd._udi = "";
  dd._local_ip_address = "";
  dd._broadcast_address = "";
  dd._device_ip_address = "";
  CHECK(dd.ParseCommandLine(6, argv) == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(dd._portname == "/dev/ttyS4");
  CHECK(dd._udi == "test udi");
  CHECK(dd._local_ip_address == "");

  // Test option followed by another option with no argument
  strncpy(argv[6], "-bcast", 40);

  dd._portname = "";
  dd._udi = "";
  dd._local_ip_address = "";
  dd._broadcast_address = "";
  dd._device_ip_address = "";
  CHECK(dd.ParseCommandLine(7, argv) == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(dd._portname == "/dev/ttyS4");
  CHECK(dd._udi == "test udi");
  CHECK(dd._local_ip_address == "");
  CHECK(dd._broadcast_address == "");

  // Test unknown option
  strncpy(argv[6], "-unknown", 40);

  dd._portname = "";
  dd._udi = "";
  dd._local_ip_address = "";
  dd._broadcast_address = "";
  dd._device_ip_address = "";
  CHECK(dd.ParseCommandLine(7, argv) == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(dd._portname == "/dev/ttyS4");
  CHECK(dd._udi == "test udi");
  CHECK(dd._local_ip_address == "");
  CHECK(dd._broadcast_address == "");

  // delete command line arguments.
  for (int ix = 0; ix < argc; ix++)
  {
    delete [] argv[ix];
    argv[ix] = nullptr;
  }
  delete [] argv;
  argv = nullptr;

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest DDPhilipsIntellivueMP70UnitTest::RunDriver()
{
  WARN("Not implemented because of RunDriver loop");
  return DicesRcUnitTest::OK;
}

