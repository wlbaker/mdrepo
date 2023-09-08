/**
 * @file ini_rtsa_priority_list_parser_unit_test.cxx
 *
 * @brief Defines a unit test class for IniRTSAPriorityListParser class.
 *
 * @author M Szwaja
 */
//=============================================================================
#include "ini_rtsa_priority_list_parser_unit_test.h"
#include "Test/Catch/catch.hpp"
#include "UnitTestReturnCodes.h"
#include "PhilipsIntellivueMP70ReturnCodes.h"
#include "Core/IniParser/simple-ini.h"

IniRTSAPriorityListParserUnitTest::IniRTSAPriorityListParserUnitTest() { }

IniRTSAPriorityListParserUnitTest::~IniRTSAPriorityListParserUnitTest() { }

DicesRcUnitTest IniRTSAPriorityListParserUnitTest::RunTests()
{
  static const char* sfn = "IniRTSAPriorityListParserUnitTest::RunTests() ";
  DicesRcUnitTest status = DicesRcUnitTest::OK;

  SECTION("get_waveform_1()")
  {
    DicesRcUnitTest test_status = get_waveform_1();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_waveform_2()")
  {
    DicesRcUnitTest test_status = get_waveform_2();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_waveform_3()")
  {
    DicesRcUnitTest test_status = get_waveform_3();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_waveform_4()")
  {
    DicesRcUnitTest test_status = get_waveform_4();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_waveform_5()")
  {
    DicesRcUnitTest test_status = get_waveform_5();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_waveform_6()")
  {
    DicesRcUnitTest test_status = get_waveform_6();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_waveform_7()")
  {
    DicesRcUnitTest test_status = get_waveform_7();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_waveform_8()")
  {
    DicesRcUnitTest test_status = get_waveform_8();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_waveform_9()")
  {
    DicesRcUnitTest test_status = get_waveform_9();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_waveform_10()")
  {
    DicesRcUnitTest test_status = get_waveform_10();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_waveform_11()")
  {
    DicesRcUnitTest test_status = get_waveform_11();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("Load()")
  {
    DicesRcUnitTest test_status = Load();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }

  return status;
}

DicesRcUnitTest IniRTSAPriorityListParserUnitTest::get_waveform_1()
{
  IniRTSAPriorityListParser parser("");
  parser._waveform_1 = 0;
  CHECK(parser.get_waveform_1() == 0);
  parser._waveform_1 = 1;
  CHECK(parser.get_waveform_1() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniRTSAPriorityListParserUnitTest::get_waveform_2()
{
  IniRTSAPriorityListParser parser("");
  parser._waveform_2 = 0;
  CHECK(parser.get_waveform_2() == 0);
  parser._waveform_2 = 1;
  CHECK(parser.get_waveform_2() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniRTSAPriorityListParserUnitTest::get_waveform_3()
{
  IniRTSAPriorityListParser parser("");
  parser._waveform_3 = 0;
  CHECK(parser.get_waveform_3() == 0);
  parser._waveform_3 = 1;
  CHECK(parser.get_waveform_3() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniRTSAPriorityListParserUnitTest::get_waveform_4()
{
  IniRTSAPriorityListParser parser("");
  parser._waveform_4 = 0;
  CHECK(parser.get_waveform_4() == 0);
  parser._waveform_4 = 1;
  CHECK(parser.get_waveform_4() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniRTSAPriorityListParserUnitTest::get_waveform_5()
{
  IniRTSAPriorityListParser parser("");
  parser._waveform_5 = 0;
  CHECK(parser.get_waveform_5() == 0);
  parser._waveform_5 = 1;
  CHECK(parser.get_waveform_5() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniRTSAPriorityListParserUnitTest::get_waveform_6()
{
  IniRTSAPriorityListParser parser("");
  parser._waveform_6 = 0;
  CHECK(parser.get_waveform_6() == 0);
  parser._waveform_6 = 1;
  CHECK(parser.get_waveform_6() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniRTSAPriorityListParserUnitTest::get_waveform_7()
{
  IniRTSAPriorityListParser parser("");
  parser._waveform_7 = 0;
  CHECK(parser.get_waveform_7() == 0);
  parser._waveform_7 = 1;
  CHECK(parser.get_waveform_7() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniRTSAPriorityListParserUnitTest::get_waveform_8()
{
  IniRTSAPriorityListParser parser("");
  parser._waveform_8 = 0;
  CHECK(parser.get_waveform_8() == 0);
  parser._waveform_8 = 1;
  CHECK(parser.get_waveform_8() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniRTSAPriorityListParserUnitTest::get_waveform_9()
{
  IniRTSAPriorityListParser parser("");
  parser._waveform_9 = 0;
  CHECK(parser.get_waveform_9() == 0);
  parser._waveform_9 = 1;
  CHECK(parser.get_waveform_9() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniRTSAPriorityListParserUnitTest::get_waveform_10()
{
  IniRTSAPriorityListParser parser("");
  parser._waveform_10 = 0;
  CHECK(parser.get_waveform_10() == 0);
  parser._waveform_10 = 1;
  CHECK(parser.get_waveform_10() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniRTSAPriorityListParserUnitTest::get_waveform_11()
{
  IniRTSAPriorityListParser parser("");
  parser._waveform_11 = 0;
  CHECK(parser.get_waveform_11() == 0);
  parser._waveform_11 = 1;
  CHECK(parser.get_waveform_11() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniRTSAPriorityListParserUnitTest::Load()
{
  const std::string kvalid_ini_file = "test_rtsa_priority_list.ini";
  const std::string kvalid_section_name = "cfg_rtsa_priority_list";
  IniRTSAPriorityListParser parser(kvalid_ini_file);

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

  parser._waveform_1 = 0;
  parser._waveform_2 = 0;
  parser._waveform_3 = 0;
  parser._waveform_4 = 0;
  parser._waveform_5 = 0;
  parser._waveform_6 = 0;
  parser._waveform_7 = 0;
  parser._waveform_8 = 0;
  parser._waveform_9 = 0;
  parser._waveform_10 = 0;
  parser._waveform_11 = 0;

  CHECK(parser.Load(kvalid_section_name) == DicesRcPhilipsIntellivueMP70::OK);

  CHECK(parser.get_waveform_1() == 1);
  CHECK(parser.get_waveform_2() == 2);
  CHECK(parser.get_waveform_3() == 3);
  CHECK(parser.get_waveform_4() == 4);
  CHECK(parser.get_waveform_5() == 5);
  CHECK(parser.get_waveform_6() == 6);
  CHECK(parser.get_waveform_7() == 7);
  CHECK(parser.get_waveform_8() == 8);
  CHECK(parser.get_waveform_9() == 9);
  CHECK(parser.get_waveform_10() == 10);
  CHECK(parser.get_waveform_11() == 11);

  return DicesRcUnitTest::OK;
}

