/**
 * @file intellivue_association_request_unit_test.cxx
 *
 * @brief Defines a unit test class for IntellivueAssociationRequest class.
 *
 * @author M Szwaja
 */
//=============================================================================
#include "intellivue_association_request_unit_test.h"
#include "Test/Catch/catch.hpp"
#include "UnitTestReturnCodes.h"
#include "PhilipsIntellivueMP70ReturnCodes.h"

IntellivueAssociationRequestUnitTest::IntellivueAssociationRequestUnitTest() { }

IntellivueAssociationRequestUnitTest::~IntellivueAssociationRequestUnitTest() { }

DicesRcUnitTest IntellivueAssociationRequestUnitTest::RunTests()
{
  static const char* sfn = "IntellivueAssociationRequestUnitTest::RunTests() ";
  DicesRcUnitTest status = DicesRcUnitTest::OK;

  SECTION("CreateAssociationRequest()")
  {
    DicesRcUnitTest test_status = CreateAssociationRequest();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  return status;
}

DicesRcUnitTest IntellivueAssociationRequestUnitTest::CreateAssociationRequest()
{
  static const char* sfn = "IntellivueAssociationRequestUnitTest::CreateAssociationRequest() ";

  struct TestCase {
    std::string desc;
    // Object
    IntellivueAssociationRequest* request;
    // Object data
    const char* filename;
    // Parameters
    uint8_t* association_request_buffer;
    unsigned int size_of_buffer;
    unsigned int* size_of_request;
    // Return value
    DicesRcPhilipsIntellivueMP70 retcode;
    // Expected Outcome
    DicesRcPhilipsIntellivueMP70 x_retcode;
    const uint8_t* x_association_request_buffer;
    unsigned int x_size_of_request;
  };

  static const char* KFilenameAssociationRequestCfg = "../config/association_request_cfg.ini";
  static const char* KFilenameAssociationRequestCfgNotExist = "../config/wrong_association_request_cfg.ini";

  // Association Request
  static const uint8_t kAssociationRequest[] = {
    // Session header
    0x0D, 0xEC,
    // Session data
    0x05, 0x08, 0x13, 0x01, 0x00, 0x16, 0x01,
    0x02, 0x80, 0x00, 0x14, 0x02, 0x00, 0x02,
    // Presentation header
    0xC1, 0xDC, // 0xDC = d220
    0x31, 0x80, 0xA0, 0x80, 0x80, 0x01, 0x01, 0x00,
    0x00, 0xA2, 0x80, 0xA0, 0x03, 0x00, 0x00, 0x01,
    0xA4, 0x80, 0x30, 0x80, 0x02, 0x01, 0x01, 0x06,
    0x04, 0x52, 0x01, 0x00, 0x01, 0x30, 0x80, 0x06,
    0x02, 0x51, 0x01, 0x00, 0x00, 0x00, 0x00, 0x30,
    0x80, 0x02, 0x01, 0x02, 0x06, 0x0C, 0x2A, 0x86,
    0x48, 0xCE, 0x14, 0x02, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x01, 0x30, 0x80, 0x06, 0x0C, 0x2A, 0x86,
    0x48, 0xCE, 0x14, 0x02, 0x01, 0x00, 0x00, 0x00,
    0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x61, 0x80, 0x30, 0x80, 0x02, 0x01, 0x01, 0xA0,
    0x80, 0x60, 0x80, 0xA1, 0x80, 0x06, 0x0C, 0x2A,
    0x86, 0x48, 0xCE, 0x14, 0x02, 0x01, 0x00, 0x00,
    0x00, 0x03, 0x01, 0x00, 0x00, 0xBE, 0x80, 0x28,
    0x80, 0x06, 0x0C, 0x2A, 0x86, 0x48, 0xCE, 0x14,
    0x02, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02,
    0x01, 0x02, 0x81,
    // Length of user data
    0x48, // d72
    // Protocol version
    0x80, 0x00, 0x00, 0x00,
    // Nomenclature version
    0x40, 0x00, 0x00, 0x00,
    // Functional units
    0x00, 0x00, 0x00, 0x00,
    // System type
    0x80, 0x00, 0x00, 0x00,
    // Startup mode
    0x20, 0x00, 0x00, 0x00,
    // Option list count
    0x00, 0x00,
    // Option list length
    0x00, 0x00,
    // Supported profiles count
    0x00, 0x01,
    // Supported profiles length
    0x00, 0x2C, // d44
    // Supported ATT ID
    0x00, 0x01,
    // Supported AVA length
    0x00, 0x28, // d40
    // Poll profile revision
    0x80, 0x00, 0x00, 0x00,
    // Min poll period
    0x00, 0x0C, 0x35, 0x00, // d800000
    // Max MTU RX
    0x00, 0x00, 0x03, 0xE8, // d1000
    // Max MTU TX
    0x00, 0x00, 0x03, 0xE8, // d1000
    // Max BW TX
    0xFF, 0xFF, 0xFF, 0xFF,
    // Poll profile opt options
    0x60, 0x00, 0x00, 0x00,
    // Optional packages count
    0x00, 0x01,
    // Optional packages length
    0x00, 0x0C,
    // Opt attribute ID
    0xF0, 0x01,
    // Opt length
    0x00, 0x08,
    // Poll profile ext opt options
    0x8C, 0x00, 0x00, 0x00,
    // Poll ext count
    0x00, 0x00,
    // Poll ext length
    0x00, 0x00,
    // Presentation trailer and size
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
  };
  
  static const unsigned int kMinimumBufferLength = 238;

  std::vector<TestCase> test_data = {
    { "Success test",
      nullptr,
      KFilenameAssociationRequestCfg,
      new uint8_t[kMinimumBufferLength](), kMinimumBufferLength, new unsigned int(),
      DicesRcPhilipsIntellivueMP70::OK,
      DicesRcPhilipsIntellivueMP70::OK, kAssociationRequest, kMinimumBufferLength },
    { "Null association_request_buffer parameter test",
      nullptr,
      KFilenameAssociationRequestCfg,
      nullptr, 0, new unsigned int(),
      DicesRcPhilipsIntellivueMP70::OK,
      DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE, nullptr, 0 },
    { "Null size_of_request parameter test",
      nullptr,
      KFilenameAssociationRequestCfg,
      new uint8_t[kMinimumBufferLength](), kMinimumBufferLength, nullptr,
      DicesRcPhilipsIntellivueMP70::OK,
      DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE, nullptr, 0 },
    { "Buffer too small test",
      nullptr,
      KFilenameAssociationRequestCfg,
      new uint8_t[kMinimumBufferLength - 1](), kMinimumBufferLength - 1, new unsigned int(),
      DicesRcPhilipsIntellivueMP70::OK,
      DicesRcPhilipsIntellivueMP70::BUFFER_SIZE_TOO_SMALL, nullptr, 0 }
  };

  for (TestCase tc : test_data)
  {
    INFO(tc.desc);
    tc.request = new IntellivueAssociationRequest(tc.filename);
    tc.retcode = tc.request->CreateAssociationRequest(
      tc.association_request_buffer,
      tc.size_of_buffer,
      tc.size_of_request);
    CHECK(tc.retcode == tc.x_retcode);
    if (tc.retcode == DicesRcPhilipsIntellivueMP70::OK)
    {
      CHECK(*tc.size_of_request == tc.x_size_of_request);
      for (int ix = 0; ix < *tc.size_of_request; ix++)
      {
        CAPTURE(ix);
        CHECK(tc.association_request_buffer[ix] ==
          tc.x_association_request_buffer[ix]);
      }
    }
  }

  for (TestCase tc : test_data)
  {
    if (tc.request != nullptr) delete tc.request;
    tc.request = nullptr;
    if (tc.association_request_buffer != nullptr) delete [] tc.association_request_buffer;
    tc.association_request_buffer = nullptr;
    if (tc.size_of_request != nullptr) delete tc.size_of_request;
    tc.size_of_request = nullptr;
  }

  return DicesRcUnitTest::OK;
}

