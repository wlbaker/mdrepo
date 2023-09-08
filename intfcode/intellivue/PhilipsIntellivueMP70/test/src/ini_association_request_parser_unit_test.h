/**
 * @file ini_association_request_parser_unit_test.h
 *
 * @brief Declares a unit test class for IniAssociationRequestParser class.
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_TEST_SRC_INI_ASSOCIATION_REQUEST_PARSER_UNIT_TEST_H_
#define PHILIPS_INTELLIVUE_MP70_TEST_SRC_INI_ASSOCIATION_REQUEST_PARSER_UNIT_TEST_H_

#include "ini_association_request_parser.h"

enum class DicesRcUnitTest;

class IniAssociationRequestParserUnitTest
{
 public:
  IniAssociationRequestParserUnitTest();
  ~IniAssociationRequestParserUnitTest();

  DicesRcUnitTest RunTests();

 private:
  // Disallow use of implicitly generated member functions:
  IniAssociationRequestParserUnitTest(const IniAssociationRequestParserUnitTest &src);
  IniAssociationRequestParserUnitTest &operator=(const IniAssociationRequestParserUnitTest &rhs);

  DicesRcUnitTest get_length_of_request();
  DicesRcUnitTest get_length_of_userdata();
  DicesRcUnitTest get_protocol_version();
  DicesRcUnitTest get_nomenclature_version();
  DicesRcUnitTest get_functional_units();
  DicesRcUnitTest get_system_type();
  DicesRcUnitTest get_startup_mode();
  DicesRcUnitTest get_option_list_count();
  DicesRcUnitTest get_option_list_length();
  DicesRcUnitTest get_supported_profiles_count();
  DicesRcUnitTest get_supported_profiles_length();
  DicesRcUnitTest get_supported_att_id();
  DicesRcUnitTest get_supported_ava_length();
  DicesRcUnitTest get_poll_profile_revision();
  DicesRcUnitTest get_min_poll_period();
  DicesRcUnitTest get_max_mtu_rx();
  DicesRcUnitTest get_max_mtu_tx();
  DicesRcUnitTest get_max_bw_tx();
  DicesRcUnitTest get_poll_profile_opt_options();
  DicesRcUnitTest get_optional_packages_count();
  DicesRcUnitTest get_optional_packages_length();
  DicesRcUnitTest get_opt_attribute_id();
  DicesRcUnitTest get_opt_length();
  DicesRcUnitTest get_poll_profile_ext_opt_options();
  DicesRcUnitTest get_poll_ext_count();
  DicesRcUnitTest get_poll_ext_length();
  DicesRcUnitTest Load();
};

#endif

