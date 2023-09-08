/**
 * @file ini_dim_parser_unit_test.h
 *
 * @brief Declares a unit test class for DimParser class.
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_TEST_SRC_DIM_PARSER_UNIT_TEST_H_
#define PHILIPS_INTELLIVUE_MP70_TEST_SRC_DIM_PARSER_UNIT_TEST_H_

#include "ini_dim_parser.h"

enum class DicesRcUnitTest;

class DIMParserUnitTest
{
 public:
  DIMParserUnitTest();
  ~DIMParserUnitTest();

  DicesRcUnitTest RunTests();

 private:
  // Disallow use of implicitly generated member functions:
  DIMParserUnitTest(const DIMParserUnitTest &src);
  DIMParserUnitTest &operator=(const DIMParserUnitTest &rhs);

  DicesRcUnitTest get_manufacturer();
  DicesRcUnitTest get_model();
  DicesRcUnitTest get_software_version();
  DicesRcUnitTest get_database_name();
  DicesRcUnitTest get_database_user();
  DicesRcUnitTest get_database_password();
  DicesRcUnitTest get_database_host();
  DicesRcUnitTest get_port_name();
  DicesRcUnitTest get_baud_rate();
  DicesRcUnitTest get_data_bits();
  DicesRcUnitTest get_stop_bits();
  DicesRcUnitTest get_handshaking();
  DicesRcUnitTest get_parity();
  DicesRcUnitTest get_enable_hardware_flow_control();
  DicesRcUnitTest get_enable_software_flow_control();
  DicesRcUnitTest get_connect_indication_port();
  DicesRcUnitTest get_protocol_udp_port();
  DicesRcUnitTest Load();
};

#endif

