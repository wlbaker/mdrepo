/**
 * @file ini_association_request_parser_unit_test.cxx
 *
 * @brief Defines a unit test class for IniAssociationRequestParser class.
 *
 * @author M Szwaja
 */
//=============================================================================
#include "ini_association_request_parser_unit_test.h"
#include "Test/Catch/catch.hpp"
#include "UnitTestReturnCodes.h"
#include "PhilipsIntellivueMP70ReturnCodes.h"
#include "Core/IniParser/simple-ini.h"

IniAssociationRequestParserUnitTest::IniAssociationRequestParserUnitTest() { }

IniAssociationRequestParserUnitTest::~IniAssociationRequestParserUnitTest() { }

DicesRcUnitTest IniAssociationRequestParserUnitTest::RunTests()
{
  static const char* sfn = "IntellivueAssociationReleaseRequestUnitTest::RunTests() ";
  DicesRcUnitTest status = DicesRcUnitTest::OK;

  SECTION("get_length_of_request()")
  {
    DicesRcUnitTest test_status = get_length_of_request();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_length_of_userdata()")
  {
    DicesRcUnitTest test_status = get_length_of_userdata();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_protocol_version()")
  {
    DicesRcUnitTest test_status = get_protocol_version();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_nomenclature_version()")
  {
    DicesRcUnitTest test_status = get_nomenclature_version();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_functional_units()")
  {
    DicesRcUnitTest test_status = get_functional_units();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_system_type()")
  {
    DicesRcUnitTest test_status = get_system_type();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_startup_mode()")
  {
    DicesRcUnitTest test_status = get_startup_mode();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_option_list_count()")
  {
    DicesRcUnitTest test_status = get_option_list_count();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_option_list_length()")
  {
    DicesRcUnitTest test_status = get_option_list_length();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_supported_profiles_count()")
  {
    DicesRcUnitTest test_status = get_supported_profiles_count();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_supported_profiles_length()")
  {
    DicesRcUnitTest test_status = get_supported_profiles_length();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_supported_att_id()")
  {
    DicesRcUnitTest test_status = get_supported_att_id();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_supported_ava_length()")
  {
    DicesRcUnitTest test_status = get_supported_ava_length();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_poll_profile_revision()")
  {
    DicesRcUnitTest test_status = get_poll_profile_revision();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_min_poll_period()")
  {
    DicesRcUnitTest test_status = get_min_poll_period();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_max_mtu_rx()")
  {
    DicesRcUnitTest test_status = get_max_mtu_rx();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_max_mtu_tx()")
  {
    DicesRcUnitTest test_status = get_max_mtu_tx();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_max_bw_tx()")
  {
    DicesRcUnitTest test_status = get_max_bw_tx();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_poll_profile_opt_options()")
  {
    DicesRcUnitTest test_status = get_poll_profile_opt_options();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_optional_packages_count()")
  {
    DicesRcUnitTest test_status = get_optional_packages_count();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_optional_packages_length()")
  {
    DicesRcUnitTest test_status = get_optional_packages_length();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_opt_attribute_id()")
  {
    DicesRcUnitTest test_status = get_opt_attribute_id();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_opt_length()")
  {
    DicesRcUnitTest test_status = get_opt_length();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_poll_profile_ext_opt_options()")
  {
    DicesRcUnitTest test_status = get_poll_profile_ext_opt_options();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_poll_ext_count()")
  {
    DicesRcUnitTest test_status = get_poll_ext_count();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("get_poll_ext_length()")
  {
    DicesRcUnitTest test_status = get_poll_ext_length();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("Load()")
  {
    DicesRcUnitTest test_status = Load();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }

  return status;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_length_of_request()
{
  IniAssociationRequestParser parser("");
  parser._length_of_request = 0;
  CHECK(parser.get_length_of_request() == 0);
  parser._length_of_request = 1;
  CHECK(parser.get_length_of_request() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_length_of_userdata()
{
  IniAssociationRequestParser parser("");
  parser._length_of_userdata = 0;
  CHECK(parser.get_length_of_userdata() == 0);
  parser._length_of_userdata = 1;
  CHECK(parser.get_length_of_userdata() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_protocol_version()
{
  IniAssociationRequestParser parser("");
  parser._protocol_version = 0;
  CHECK(parser.get_protocol_version() == 0);
  parser._protocol_version = 1;
  CHECK(parser.get_protocol_version() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_nomenclature_version()
{
  IniAssociationRequestParser parser("");
  parser._nomenclature_version = 0;
  CHECK(parser.get_nomenclature_version() == 0);
  parser._nomenclature_version = 1;
  CHECK(parser.get_nomenclature_version() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_functional_units()
{
  IniAssociationRequestParser parser("");
  parser._functional_units = 0;
  CHECK(parser.get_functional_units() == 0);
  parser._functional_units = 1;
  CHECK(parser.get_functional_units() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_system_type()
{
  IniAssociationRequestParser parser("");
  parser._system_type = 0;
  CHECK(parser.get_system_type() == 0);
  parser._system_type = 1;
  CHECK(parser.get_system_type() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_startup_mode()
{
  IniAssociationRequestParser parser("");
  parser._startup_mode = 0;
  CHECK(parser.get_startup_mode() == 0);
  parser._startup_mode = 1;
  CHECK(parser.get_startup_mode() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_option_list_count()
{
  IniAssociationRequestParser parser("");
  parser._option_list_count = 0;
  CHECK(parser.get_option_list_count() == 0);
  parser._option_list_count = 1;
  CHECK(parser.get_option_list_count() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_option_list_length()
{
  IniAssociationRequestParser parser("");
  parser._option_list_length = 0;
  CHECK(parser.get_option_list_length() == 0);
  parser._option_list_length = 1;
  CHECK(parser.get_option_list_length() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_supported_profiles_count()
{
  IniAssociationRequestParser parser("");
  parser._supported_profiles_count = 0;
  CHECK(parser.get_supported_profiles_count() == 0);
  parser._supported_profiles_count = 1;
  CHECK(parser.get_supported_profiles_count() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_supported_profiles_length()
{
  IniAssociationRequestParser parser("");
  parser._supported_profiles_length = 0;
  CHECK(parser.get_supported_profiles_length() == 0);
  parser._supported_profiles_length = 1;
  CHECK(parser.get_supported_profiles_length() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_supported_att_id()
{
  IniAssociationRequestParser parser("");
  parser._supported_att_id = 0;
  CHECK(parser.get_supported_att_id() == 0);
  parser._supported_att_id = 1;
  CHECK(parser.get_supported_att_id() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_supported_ava_length()
{
  IniAssociationRequestParser parser("");
  parser._supported_ava_length = 0;
  CHECK(parser.get_supported_ava_length() == 0);
  parser._supported_ava_length = 1;
  CHECK(parser.get_supported_ava_length() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_poll_profile_revision()
{
  IniAssociationRequestParser parser("");
  parser._poll_profile_revision = 0;
  CHECK(parser.get_poll_profile_revision() == 0);
  parser._poll_profile_revision = 1;
  CHECK(parser.get_poll_profile_revision() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_min_poll_period()
{
  IniAssociationRequestParser parser("");
  parser._min_poll_period = 0;
  CHECK(parser.get_min_poll_period() == 0);
  parser._min_poll_period = 1;
  CHECK(parser.get_min_poll_period() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_max_mtu_rx()
{
  IniAssociationRequestParser parser("");
  parser._max_mtu_rx = 0;
  CHECK(parser.get_max_mtu_rx() == 0);
  parser._max_mtu_rx = 1;
  CHECK(parser.get_max_mtu_rx() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_max_mtu_tx()
{
  IniAssociationRequestParser parser("");
  parser._max_mtu_tx = 0;
  CHECK(parser.get_max_mtu_tx() == 0);
  parser._max_mtu_tx = 1;
  CHECK(parser.get_max_mtu_tx() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_max_bw_tx()
{
  IniAssociationRequestParser parser("");
  parser._max_bw_tx = 0;
  CHECK(parser.get_max_bw_tx() == 0);
  parser._max_bw_tx = 1;
  CHECK(parser.get_max_bw_tx() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_poll_profile_opt_options()
{
  IniAssociationRequestParser parser("");
  parser._poll_profile_opt_options = 0;
  CHECK(parser.get_poll_profile_opt_options() == 0);
  parser._poll_profile_opt_options = 1;
  CHECK(parser.get_poll_profile_opt_options() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_optional_packages_count()
{
  IniAssociationRequestParser parser("");
  parser._optional_packages_count = 0;
  CHECK(parser.get_optional_packages_count() == 0);
  parser._optional_packages_count = 1;
  CHECK(parser.get_optional_packages_count() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_optional_packages_length()
{
  IniAssociationRequestParser parser("");
  parser._optional_packages_length = 0;
  CHECK(parser.get_optional_packages_length() == 0);
  parser._optional_packages_length = 1;
  CHECK(parser.get_optional_packages_length() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_opt_attribute_id()
{
  IniAssociationRequestParser parser("");
  parser._opt_attribute_id = 0;
  CHECK(parser.get_opt_attribute_id() == 0);
  parser._opt_attribute_id = 1;
  CHECK(parser.get_opt_attribute_id() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_opt_length()
{
  IniAssociationRequestParser parser("");
  parser._opt_length = 0;
  CHECK(parser.get_opt_length() == 0);
  parser._opt_length = 1;
  CHECK(parser.get_opt_length() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_poll_profile_ext_opt_options()
{
  IniAssociationRequestParser parser("");
  parser._poll_profile_ext_opt_options = 0;
  CHECK(parser.get_poll_profile_ext_opt_options() == 0);
  parser._poll_profile_ext_opt_options = 1;
  CHECK(parser.get_poll_profile_ext_opt_options() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_poll_ext_count()
{
  IniAssociationRequestParser parser("");
  parser._poll_ext_count = 0;
  CHECK(parser.get_poll_ext_count() == 0);
  parser._poll_ext_count = 1;
  CHECK(parser.get_poll_ext_count() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::get_poll_ext_length()
{
  IniAssociationRequestParser parser("");
  parser._poll_ext_length = 0;
  CHECK(parser.get_poll_ext_length() == 0);
  parser._poll_ext_length = 1;
  CHECK(parser.get_poll_ext_length() == 1);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IniAssociationRequestParserUnitTest::Load()
{
  const std::string kvalid_ini_file = "test_association_request_cfg.ini";
  const std::string kvalid_section_name = "cfg_association_request";
  IniAssociationRequestParser parser(kvalid_ini_file);

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

  parser._length_of_request = 0;
  parser._length_of_userdata = 0;
  parser._protocol_version = 0;
  parser._nomenclature_version = 0;
  parser._functional_units = 0;
  parser._system_type = 0;
  parser._startup_mode = 0;
  parser._option_list_count = 0;
  parser._option_list_length = 0;
  parser._supported_profiles_count = 0;
  parser._supported_profiles_length = 0;
  parser._supported_att_id = 0;
  parser._supported_ava_length = 0;
  parser._poll_profile_revision = 0;
  parser._poll_profile_revision = 0;
  parser._min_poll_period = 0;
  parser._max_mtu_rx = 0;
  parser._max_mtu_tx = 0;
  parser._max_bw_tx = 0;
  parser._poll_profile_opt_options = 0;
  parser._optional_packages_count = 0;
  parser._optional_packages_length = 0;
  parser._opt_attribute_id = 0;
  parser._opt_length = 0;
  parser._poll_profile_ext_opt_options = 0;
  parser._poll_ext_count = 0;
  parser._poll_ext_length = 0;

  CHECK(parser.Load(kvalid_section_name) == DicesRcPhilipsIntellivueMP70::OK);

  CHECK(parser.get_length_of_request() == 1);
  CHECK(parser.get_length_of_userdata() == 2);
  CHECK(parser.get_protocol_version() == 0x80000000);
  CHECK(parser.get_nomenclature_version() == 0x40000000);
  CHECK(parser.get_functional_units() == 3);
  CHECK(parser.get_system_type() == 0x80000000);
  CHECK(parser.get_startup_mode() == 0x20000000);
  CHECK(parser.get_option_list_count() == 4);
  CHECK(parser.get_option_list_length() == 5);
  CHECK(parser.get_supported_profiles_count() == 6);
  CHECK(parser.get_supported_profiles_length() == 7);
  CHECK(parser.get_supported_att_id() == 8);
  CHECK(parser.get_supported_ava_length() == 9);
  CHECK(parser.get_poll_profile_revision() == 0x80000000);
  CHECK(parser.get_poll_profile_revision() == 0x80000000);
  CHECK(parser.get_min_poll_period() == 10);
  CHECK(parser.get_max_mtu_rx() == 11);
  CHECK(parser.get_max_mtu_tx() == 12);
  CHECK(parser.get_max_bw_tx() == 0xffffffff);
  CHECK(parser.get_poll_profile_opt_options() == 0x60000000);
  CHECK(parser.get_optional_packages_count() == 13);
  CHECK(parser.get_optional_packages_length() == 14);
  CHECK(parser.get_opt_attribute_id() == 0xf001);
  CHECK(parser.get_opt_length() == 15);
  CHECK(parser.get_poll_profile_ext_opt_options() == 0x8C000000);
  CHECK(parser.get_poll_ext_count() == 16);
  CHECK(parser.get_poll_ext_length() == 17);

  return DicesRcUnitTest::OK;
}

