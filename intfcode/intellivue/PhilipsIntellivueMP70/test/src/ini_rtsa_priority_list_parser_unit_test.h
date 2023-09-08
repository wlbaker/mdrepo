/**
 * @file ini_rtsa_priority_list_parser_unit_test.h
 *
 * @brief Declares a unit test class for IniRTSAPriorityListParser class.
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_TEST_SRC_INI_RTSA_PRIORITY_LIST_PARSER_UNIT_TEST_H_
#define PHILIPS_INTELLIVUE_MP70_TEST_SRC_INI_RTSA_PRIORITY_LIST_PARSER_UNIT_TEST_H_

#include "ini_rtsa_priority_list_parser.h"

enum class DicesRcUnitTest;

class IniRTSAPriorityListParserUnitTest
{
 public:
  IniRTSAPriorityListParserUnitTest();
  ~IniRTSAPriorityListParserUnitTest();

  DicesRcUnitTest RunTests();

 private:
  // Disallow use of implicitly generated member functions:
  IniRTSAPriorityListParserUnitTest(const IniRTSAPriorityListParserUnitTest &src);
  IniRTSAPriorityListParserUnitTest &operator=(const IniRTSAPriorityListParserUnitTest &rhs);

  DicesRcUnitTest get_waveform_1();
  DicesRcUnitTest get_waveform_2();
  DicesRcUnitTest get_waveform_3();
  DicesRcUnitTest get_waveform_4();
  DicesRcUnitTest get_waveform_5();
  DicesRcUnitTest get_waveform_6();
  DicesRcUnitTest get_waveform_7();
  DicesRcUnitTest get_waveform_8();
  DicesRcUnitTest get_waveform_9();
  DicesRcUnitTest get_waveform_10();
  DicesRcUnitTest get_waveform_11();
  DicesRcUnitTest Load();
};

#endif

