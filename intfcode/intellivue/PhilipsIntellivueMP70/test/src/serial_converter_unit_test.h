/**
 * @file serial_converter_unit_test.h
 *
 * @brief Declares a unit test class for SerialConverter class.
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_TEST_SRC_SERIAL_CONVERTER_UNIT_TEST_H_
#define PHILIPS_INTELLIVUE_MP70_TEST_SRC_SERIAL_CONVERTER_UNIT_TEST_H_

enum class DicesRcUnitTest;

class SerialConverterUnitTest
{
 public:
  SerialConverterUnitTest();
  ~SerialConverterUnitTest();

  DicesRcUnitTest RunTests();

 private:
  // Disallow use of implicitly generated member functions:
  SerialConverterUnitTest(const SerialConverterUnitTest &src);
  SerialConverterUnitTest &operator=(const SerialConverterUnitTest &rhs);

  DicesRcUnitTest ConstructSerialMsg();
  DicesRcUnitTest UnwrapSerialMsg();
  DicesRcUnitTest CreateFCSTable();
  DicesRcUnitTest CalculateNewFCS();
};

#endif

