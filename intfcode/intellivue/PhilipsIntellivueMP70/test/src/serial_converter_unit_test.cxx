/**
 * @file serial_converter_unit_test.cxx
 *
 * @brief Defines a unit test class for SerialConverter class.
 *
 * @author M Szwaja
 */
//=============================================================================
#include "serial_converter_unit_test.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <cstring>
#include "Test/Catch/catch.hpp"
#include "UnitTestReturnCodes.h"
#include "serial_converter.h"
#include "PhilipsIntellivueMP70ReturnCodes.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

SerialConverterUnitTest::SerialConverterUnitTest() { }

SerialConverterUnitTest::~SerialConverterUnitTest() { }

DicesRcUnitTest SerialConverterUnitTest::RunTests()
{
  static const char* sfn = "SerialConverterUnitTest::RunTests() ";
  DicesRcUnitTest status = DicesRcUnitTest::OK;

  SECTION("ConstructSerialMsg()")
  {
    DicesRcUnitTest test_status = ConstructSerialMsg();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }

  SECTION("UnwrapSerialMsg()")
  {
    DicesRcUnitTest test_status = UnwrapSerialMsg();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }

  SECTION("CreateFCSTable()")
  {
    DicesRcUnitTest test_status = CreateFCSTable();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }

  SECTION("CalculateNewFCS()")
  {
    DicesRcUnitTest test_status = CalculateNewFCS();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  return status;
}

DicesRcUnitTest SerialConverterUnitTest::ConstructSerialMsg()
{
  static const char* sfn = "SerialConverterUnitTest::ConstructSerialMsg() ";
  DicesRcPhilipsIntellivueMP70 status = DicesRcPhilipsIntellivueMP70::OK;
  SerialConverter converter;

  const unsigned int kmax_buff_size = 30;
  uint8_t buffer[kmax_buff_size] = { 0 };
  buffer[0] = 'H';
  buffer[1] = 'e';
  buffer[2] = 'l';
  buffer[3] = 'l';
  buffer[4] = 'o';
  buffer[5] = 0xC1;
  buffer[6] = 0xC0;
  buffer[7] = 0x7D;
  unsigned int numbytes_buffer = 8;

  uint8_t test_exp_result[kmax_buff_size] = { 0 };
  test_exp_result[0] = 0xC0; // BOF
  test_exp_result[1] = 0x11; // protocol id
  test_exp_result[2] = 0x01; // message type
  test_exp_result[3] = 0x00; // length[0]
  test_exp_result[4] = 0x08; // length[1] 0x0008 = 8
  test_exp_result[5] = 0x48; // H
  test_exp_result[6] = 0x65; // e
  test_exp_result[7] = 0x6C; // l
  test_exp_result[8] = 0x6C; // l
  test_exp_result[9] = 0x6F; // o
  test_exp_result[10] = 0x7D; // 0x7D inserted before control character
  test_exp_result[11] = 0xC1 ^ 0x20; // XOR control character with 0x20
  test_exp_result[12] = 0x7D; // 0x7D inserted before control character
  test_exp_result[13] = 0xC0 ^ 0x20; // XOR control character with 0x20
  test_exp_result[14] = 0x7D; // 0x7D inserted before control character
  test_exp_result[15] = 0x7D ^ 0x20; // XOR control character with 0x20
  test_exp_result[16] = 0x36; // FCS[0]
  test_exp_result[17] = 0xBF; // FCS[1]
  test_exp_result[18] = 0xC1; // EOF
  unsigned int numbytes_exp_buffer = 19;

  status = converter.ConstructSerialMsg(
    nullptr,
    kmax_buff_size,
    &numbytes_buffer);
  CHECK(status == DicesRcPhilipsIntellivueMP70::
    NULL_POINTER_FUNCTION_ARGUMENT_FAILURE);

  status = converter.ConstructSerialMsg(
    buffer,
    kmax_buff_size,
    nullptr);
  CHECK(status == DicesRcPhilipsIntellivueMP70::
    NULL_POINTER_FUNCTION_ARGUMENT_FAILURE);

  CHECK(numbytes_buffer == 8);
  status = converter.ConstructSerialMsg(
    buffer,
    kmax_buff_size,
    &numbytes_buffer);
  CHECK(status == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(numbytes_buffer == numbytes_exp_buffer);
  CHECK(memcmp(buffer, test_exp_result, kmax_buff_size) == 0);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest SerialConverterUnitTest::UnwrapSerialMsg()
{
  static const char* sfn = "SerialConverterUnitTest::UnwrapSerialMsg() ";
  DicesRcPhilipsIntellivueMP70 status = DicesRcPhilipsIntellivueMP70::OK;

  const unsigned int kmax_buff_size = 30;
  unsigned int numbytes_buffer = 19;
  uint8_t buffer[kmax_buff_size] = { 0 };
  buffer[0] = 0xC0; // BOF
  buffer[1] = 0x11; // protocol id
  buffer[2] = 0x01; // message type
  buffer[3] = 0x00; // length[0]
  buffer[4] = 0x08; // length[1] 0x0008 = 8
  buffer[5] = 0x48; // H
  buffer[6] = 0x65; // e
  buffer[7] = 0x6C; // l
  buffer[8] = 0x6C; // l
  buffer[9] = 0x6F; // o
  buffer[10] = 0x7D; // 0x7D inserted before control character
  buffer[11] = 0xC1 ^ 0x20; // XOR control character with 0x20
  buffer[12] = 0x7D; // 0x7D inserted before control character
  buffer[13] = 0xC0 ^ 0x20; // XOR control character with 0x20
  buffer[14] = 0x7D; // 0x7D inserted before control character
  buffer[15] = 0x7D ^ 0x20; // XOR control character with 0x20
  buffer[16] = 0x36; // FCS[0]
  buffer[17] = 0xBF; // FCS[1]
  buffer[18] = 0xC1; // EOF

  uint8_t test_exp_result[kmax_buff_size] = { 0 };
  test_exp_result[0] = 'H';
  test_exp_result[1] = 'e';
  test_exp_result[2] = 'l';
  test_exp_result[3] = 'l';
  test_exp_result[4] = 'o';
  test_exp_result[5] = 0xC1;
  test_exp_result[6] = 0xC0;
  test_exp_result[7] = 0x7D;
  unsigned int numbytes_exp_buffer = 8;

  status = SerialConverter::UnwrapSerialMsg(nullptr, &numbytes_buffer);
  CHECK(status == DicesRcPhilipsIntellivueMP70::
    NULL_POINTER_FUNCTION_ARGUMENT_FAILURE);

  status = SerialConverter::UnwrapSerialMsg(buffer, nullptr);
  CHECK(status == DicesRcPhilipsIntellivueMP70::
    NULL_POINTER_FUNCTION_ARGUMENT_FAILURE);

  CHECK(numbytes_buffer == 19);
  status = SerialConverter::UnwrapSerialMsg(buffer, &numbytes_buffer);
  CHECK(status == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(numbytes_buffer == numbytes_exp_buffer);
  CHECK(memcmp(buffer, test_exp_result, numbytes_buffer) == 0);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest SerialConverterUnitTest::CreateFCSTable()
{
  static const char* sfn = "SerialConverterUnitTest::ConstructSerialMsg() ";
  DicesRcPhilipsIntellivueMP70 status = DicesRcPhilipsIntellivueMP70::OK;
  SerialConverter::CreateFCSTable();
  // Nothing to check here with void function.
  return DicesRcUnitTest::OK;
}

DicesRcUnitTest SerialConverterUnitTest::CalculateNewFCS()
{
  static const char* sfn = "SerialConverterUnitTest::CalculateNewFCS() ";
  DicesRcPhilipsIntellivueMP70 status = DicesRcPhilipsIntellivueMP70::OK;

  const unsigned int kmax_buff_size = 30;
  uint8_t buffer[kmax_buff_size] = { 0 };
  buffer[0] = 'H';
  buffer[1] = 'e';
  buffer[2] = 'l';
  buffer[3] = 'l';
  buffer[4] = 'o';
  buffer[5] = 0xC1;
  buffer[6] = 0xC0;
  buffer[7] = 0x7D;
  unsigned int numbytes_buffer = 8;
  uint16_t old_fcs = 0;
  uint16_t fcsval = 0;

  status = SerialConverter::CalculateNewFCS(
    old_fcs,
    nullptr,
    buffer,
    numbytes_buffer);
  CHECK(status == DicesRcPhilipsIntellivueMP70::
    NULL_POINTER_FUNCTION_ARGUMENT_FAILURE);

  status = SerialConverter::CalculateNewFCS(
    old_fcs,
    &fcsval,
    nullptr,
    numbytes_buffer);
  CHECK(status == DicesRcPhilipsIntellivueMP70::
    NULL_POINTER_FUNCTION_ARGUMENT_FAILURE);

  status = SerialConverter::CalculateNewFCS(
    old_fcs,
    &fcsval,
    buffer,
    numbytes_buffer);
  CHECK(status == DicesRcPhilipsIntellivueMP70::OK);

  return DicesRcUnitTest::OK;
}
