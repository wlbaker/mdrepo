/**
 * @file intellivue_association_release_request_unit_test.cxx
 *
 * @brief Defines a unit test class for IntellivueAssociationReleaseRequest class.
 *
 * @author M Szwaja
 */
//=============================================================================
#include "intellivue_association_release_request_unit_test.h"
#include "Test/Catch/catch.hpp"
#include "UnitTestReturnCodes.h"
#include "PhilipsIntellivueMP70ReturnCodes.h"

IntellivueAssociationReleaseRequestUnitTest::IntellivueAssociationReleaseRequestUnitTest() { }

IntellivueAssociationReleaseRequestUnitTest::~IntellivueAssociationReleaseRequestUnitTest() { }

DicesRcUnitTest IntellivueAssociationReleaseRequestUnitTest::RunTests()
{
  static const char* sfn = "IntellivueAssociationReleaseRequestUnitTest::RunTests() ";
  DicesRcUnitTest status = DicesRcUnitTest::OK;

  SECTION("CreateAssociationReleaseRequest()")
  {
    DicesRcUnitTest test_status = CreateAssociationReleaseRequest();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  return status;
}

DicesRcUnitTest IntellivueAssociationReleaseRequestUnitTest::CreateAssociationReleaseRequest()
{
  static const char* sfn = "IntellivueAssociationReleaseRequestUnitTest::CreateAssociationReleaseRequest() ";

  struct TestCase {
    std::string desc;
    // Parameters
    uint8_t* association_release_request_buffer;
    unsigned int size_of_buffer;
    unsigned int* size_of_request;
    // Return value
    DicesRcPhilipsIntellivueMP70 retcode;
    // Expected Outcome
    DicesRcPhilipsIntellivueMP70 x_retcode;
    const uint8_t* x_association_release_request_buffer;
    unsigned int x_size_of_request;
  };

  // Association Release Request
  static const uint8_t kAssociationReleaseRequest[] = {
    0x09, 0x18 /* ReleaseReqSessionHeader */,
    0xC1, 0x16, 0x61, 0x80, 0x30, 0x80, 0x02, 0x01,
    0x01, 0xA0, 0x80, 0x62, 0x80, 0x80, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x00 /* ReleaseReqPresentationHeader */,
    0x00, 0x00, 0x00, 0x00 /* ReleaseReqPresentationTrailer */
  };
  
  static const unsigned int kMinimumBufferLength = 26;

  std::vector<TestCase> kTestData = {
    { "Success test",
      new uint8_t[kMinimumBufferLength](), kMinimumBufferLength, new unsigned int(),
      DicesRcPhilipsIntellivueMP70::OK,
      DicesRcPhilipsIntellivueMP70::OK, kAssociationReleaseRequest, kMinimumBufferLength },
    { "Null association_release_request_buffer parameter test",
      nullptr, 0, new unsigned int(),
      DicesRcPhilipsIntellivueMP70::OK,
      DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE, nullptr, 0 },
    { "Null size_of_request parameter test",
      new uint8_t[kMinimumBufferLength](), kMinimumBufferLength, nullptr,
      DicesRcPhilipsIntellivueMP70::OK,
      DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE, nullptr, 0 },
    { "Buffer too small test",
      new uint8_t[kMinimumBufferLength - 1](), kMinimumBufferLength - 1, new unsigned int(),
      DicesRcPhilipsIntellivueMP70::OK,
      DicesRcPhilipsIntellivueMP70::BUFFER_SIZE_TOO_SMALL, nullptr, 0 }
  };

  for (TestCase tc : kTestData)
  {
    INFO(tc.desc);
    tc.retcode = IntellivueAssociationReleaseRequest::CreateAssociationReleaseRequest(
      tc.association_release_request_buffer,
      tc.size_of_buffer,
      tc.size_of_request);
    CHECK(tc.retcode == tc.x_retcode);
    if (tc.retcode == DicesRcPhilipsIntellivueMP70::OK)
    {
      CHECK(*tc.size_of_request == tc.x_size_of_request);
      for (int ix = 0; ix < *tc.size_of_request; ix++)
      {
        CAPTURE(ix);
        CHECK(tc.association_release_request_buffer[ix] ==
          tc.x_association_release_request_buffer[ix]);
      }
    }
  }

  for (TestCase tc : kTestData)
  {
    if (tc.association_release_request_buffer != nullptr) delete [] tc.association_release_request_buffer;
    tc.association_release_request_buffer = nullptr;
    if (tc.size_of_request != nullptr) delete tc.size_of_request;
    tc.size_of_request = nullptr;
  }

  return DicesRcUnitTest::OK;
}
