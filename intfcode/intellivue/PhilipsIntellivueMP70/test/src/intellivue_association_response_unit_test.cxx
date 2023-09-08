/**
 * @file intellivue_association_response_unit_test.cxx
 *
 * @brief Defines a unit test class for IntellivueAssociationResponse class.
 *
 * @author M Szwaja
 */
//=============================================================================
#include "intellivue_association_response_unit_test.h"
#include "catch.hpp"
#include "UnitTestReturnCodes.h"
#include "PhilipsIntellivueMP70ReturnCodes.h"

IntellivueAssociationResponseUnitTest::IntellivueAssociationResponseUnitTest() { }

IntellivueAssociationResponseUnitTest::~IntellivueAssociationResponseUnitTest() { }

DicesRcUnitTest IntellivueAssociationResponseUnitTest::RunTests()
{
  static const char* sfn = "IntellivueAssociationResponseUnitTest::RunTests() ";
  DicesRcUnitTest status = DicesRcUnitTest::OK;

  SECTION("IsAssociationResponse()")
  {
    DicesRcUnitTest test_status = IsAssociationResponse();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  
  SECTION("ParseAssociationResponse()")
  {
    DicesRcUnitTest test_status = ParseAssociationResponse();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  
  SECTION("DeleteAssociationResponse()")
  {
    DicesRcUnitTest test_status = DeleteAssociationResponse();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  
  SECTION("FindAssociationResponseUserDataStart()")
  {
    DicesRcUnitTest test_status = FindAssociationResponseUserDataStart();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }

  return status;
}

DicesRcUnitTest IntellivueAssociationResponseUnitTest::IsAssociationResponse()
{
  static const char* sfn = "IntellivueAssociationResponseUnitTest::IsAssociationResponse() ";

  struct TestCase {
    std::string desc;
    // Parameters
    bool* is_msg;
    const uint8_t* buffer;
    unsigned int numbytes;
    // Return value
    DicesRcPhilipsIntellivueMP70 retcode;
    // Expected Outcome
    DicesRcPhilipsIntellivueMP70 x_retcode;
    const bool x_is_msg;
  };

  static const uint8_t kCNResp[] = { CN_SPDU_SI };
  static const uint8_t kACResp[] = { AC_SPDU_SI };
  static const uint8_t kRFResp[] = { RF_SPDU_SI };
  static const uint8_t kFNResp[] = { FN_SPDU_SI };
  static const uint8_t kDNResp[] = { DN_SPDU_SI };
  static const uint8_t kABResp[] = { AB_SPDU_SI };
  static const uint8_t kXResp[] = { 0xFF };
  static const uint8_t kEmptyResp[] = { };

  std::vector<TestCase> test_data = {
    { "CN_SPDU_SI test",
      new bool(false), kCNResp, 1,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::OK, true },
    { "AC_SPDU_SI test",
      new bool(false), kACResp, 1,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::OK, true },
    { "RF_SPDU_SI test",
      new bool(false), kRFResp, 1,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::OK, true },
    { "FN_SPDU_SI test",
      new bool(false), kFNResp, 1,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::OK, true },
    { "DN_SPDU_SI test",
      new bool(false), kDNResp, 1,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::OK, true },
    { "AB_SPDU_SI test",
      new bool(false), kABResp, 1,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::OK, true },
    { "Other message test",
      new bool(false), kXResp, 1,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::OK, false },
    { "Empty message test",
      new bool(false), kEmptyResp, 0,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::OK, false },
    { "Null is_msg parameter test",
      nullptr, kCNResp, 1,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE, false },
    { "Null buffer parameter test",
      new bool(false), nullptr, 0,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE, false }
  };

  for (TestCase tc : test_data)
  {
    INFO(tc.desc);
    tc.retcode = IntellivueAssociationResponse::IsAssociationResponse(
      tc.is_msg,
      const_cast<uint8_t*>(tc.buffer),
      tc.numbytes);
    CHECK(tc.retcode == tc.x_retcode);
    if (tc.retcode == DicesRcPhilipsIntellivueMP70::OK)
    {
      CHECK(*tc.is_msg == tc.x_is_msg);
    }
  }

  for (TestCase tc : test_data)
  {
    if (tc.is_msg != nullptr) delete tc.is_msg;
    tc.is_msg = nullptr;
  }

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IntellivueAssociationResponseUnitTest::ParseAssociationResponse()
{
  AssociationResponse response = {0};
  uint8_t buf[300] = {0};
  int len = 0;

  // Tests null pointer association response.
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        nullptr,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE);

  // Tests null pointer buffer.
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        nullptr,
        len) == DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE);

  // Tests length < 2
  len = 1;
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);

  // Tests length = 2, but expecting more LI length bytes
  buf[1] = 0xFF;
  len = 2;
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);

  // Tests length = 2, LI length parse successfully, length is greater than
  // remaining bytes.
  buf[1] = 0x0F;
  len = 2;
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);

  // Tests length = 2, LI length parse successfully, length equals the number of
  // remaining bytes.
  buf[1] = 0x00;
  len = 2;
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);

  // Tests length = 2, LI length (3 bytes) parse successfully, length equals the number of
  // remaining bytes.
  buf[1] = 0xFF;
  len = 4;
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);

  // Accept
  buf[0] = AC_SPDU_SI;
  len = 8;
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);

  // Refuse
  buf[0] = RF_SPDU_SI;
  len = 8;
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::ASSOCIATION_REFUSED);

  // abort
  buf[0] = AB_SPDU_SI;
  len = 8;
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::ASSOCIATION_ABORTED);

  // session disconnect
  buf[0] = DN_SPDU_SI;
  len = 8;
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::ASSOCIATION_DISCONNECT);

  // Unknown session header
  buf[0] = 0x00;
  len = 8;
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);

  // Tests user data index out of bounds.
  const uint8_t kbuf[13] = {AC_SPDU_SI, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBE, 0x80, 0x28, 0x80, 0x81};
  memmove(buf, kbuf, 13);
  len = 13;
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);

  // Begins testing of ASNLength algorithm. Using example in the manual
  // where L = 256  or {0x82, 0x01, 0x00}
  const uint8_t kupto_asnlength[16] = {
    AC_SPDU_SI, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xBE, 0x80, 0x28, 0x80, 0x81, 0x82, 0x01, 0x00};
  len = 16 + 256;
  memmove(buf, kupto_asnlength, 16);

  // Tests 16 + ASNLength (256) is within bounds of buffer size (16 + 256).
  // The function should return success.
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::OK);

  // Tests 16 + ASNLength (256) out of bounds of buffer (16 + 255). This test
  // also confirms that the ASNLength algorithm is resulting in 256 for
  // ASNLength which has not been tested before.
  // The function should return failure.
  len = 16 + 255;
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);

  // Resetting for new ASNLength test.
  memset(buf, 0x00, (16 + 256));

  // Begins testing of ASNLength algorithm. Using example in the manual
  // where L = 28  or {0x1C}. Why 28? Because it is the minimun number of
  // bytes needed to parse MDSEUserInfoStd
  const uint8_t kupto_asnlength2[14] = {
    AC_SPDU_SI, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xBE, 0x80, 0x28, 0x80, 0x81, 0x1C};
  len = 14 + 28;
  memset(buf, 0x00, 300); // zero out buffer.
  memmove(buf, kupto_asnlength2, 14);

  // Tests 14 + ASNLength (28) is within bounds of buffer size (14 + 28).
  // The function should return success.
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::OK);

  // Tests 14 + ASNLength (28) out of bounds of buffer (14 + 27). This test
  // also confirms that the ASNLength algorithm is resulting in 28 for
  // ASNLength which has not been tested before.
  // The function should return failure.
  len = 14 + 27;
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);

  // Tests length check on buffer size up until option_list length of
  // MDSEUserInfoStd. The function is expecting to parse a minimum of
  // 28 bytes for MDSEUserInfoStd. The length is set so there are no bytes
  // following ASNLength. The function will return failure.
  len = 14 + 0;
  buf[13] = 0x00; // Set ASNLength to zero
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);

  // Tests length check on buffer size for option_list for loop parsing.
  // Set option_list count = 1 so for loop is entered. In the for loop,
  // the function expects 4 bytes to parse the AVAType attribute_id and
  // length values. The function should return failure.
  len = 14 + 24;
  buf[13] = 0x18; // Set ASNLength to 24
  buf[35] = 0x01; // Set count = 1, so for loop is entered.
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);

  // Tests length check on buffer size for AttributeList supported_aprofiles
  // count and length. The function is expecting 4 bytes after AttributeList
  // option_list parsing. The length is set so there are no bytes following
  // option_list. The function should return failure.
  len = 14 + 24;
  buf[13] = 0x18; // Set ASNLength to 24
  buf[35] = 0x00; // Set option_list count back to zero.
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);

  // Tests length check on buffer size for supported_aprofiles for loop parsing.
  // Set supported_aprofiles count = 1, so for loop is entered. In the for loop,
  // the function expects 4 bytes to parse teh AVAtype attribute_id and
  // length values. The function should return failure.
  len = 14 + 28;
  buf[13] = 0x1C; // Set ASNLength to 32
  buf[39] = 0x01; // Set count = 1, so for loop is entered.
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);

  // Tests AttributeList option_list length check on buffer size.
  // Set option_list length = 255 which will exceed buffer length.
  // The function should return failure.
  len = 14 + 24;
  buf[13] = 0x18; // Set ASNLength to 24
  buf[37] = 0xFF; // Set option_list length = 255
  buf[39] = 0x00; // Reset from previous test
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);

  // Tests option_list AVAType length check on buffer size.
  // Set option_list AVAType length = 255 which will exceed buffer length.
  // The function should return failure.
  len = 14 + 28;
  buf[13] = 0x1C; // Set ASNLength to 28
  buf[35] = 0x01; // option_list count = 1
  buf[37] = 0x00; // Reset from previous test
  buf[41] = 0xFF; // option_list AVAType length = 255
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);

  // Tests AttributeList supported_aprofiles length check on buffer size.
  // Set supported_aprofiles length = 255 which will exceed buffer length.
  // The function should return failure.
  len = 14 + 28;
  buf[13] = 0x1C; // Set ASNLength to 28
  buf[35] = 0x00; // Reset from previous test.
  buf[41] = 0xFF; // Set supported_aprofiles length = 255
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);

  // Tests supported_aprofiles AVAType length check on buffer size.
  // Set supported_aprofiles AVAType length = 255 which will exceed buffer length.
  // The function should return failure.
  len = 14 + 32;
  buf[13] = 0x20; // Set ASNLength to 32
  buf[41] = 0x00; // Reset from previous test.
  buf[39] = 0x01; // Set supported_aprofiles count = 1, so enters loop
  buf[45] = 0xFF; // Set supported_aprofiles AVAType length = 255
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);

  // Tests for success. Enter option_list loop and supported_aprofiles for fun.
  len = 14 + 36;
  buf[13] = 0x24; // Set ASNLength to 36
  buf[35] = 0x01; // option_list count = 1, so enters loop
  buf[43] = 0x01; // Set supported_aprofiles count = 1, so enters loop
  buf[39] = 0x00; // Reset from previous test.
  buf[45] = 0x00; // Reset from previous test.
  CHECK(IntellivueAssociationResponse::ParseAssociationResponse(
        &response,
        &buf[0],
        len) == DicesRcPhilipsIntellivueMP70::OK);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IntellivueAssociationResponseUnitTest::DeleteAssociationResponse()
{
  // Checks null pointer function argument. Expect fail return code.
  CHECK(IntellivueAssociationResponse::DeleteAssociationResponse(nullptr)
        == DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE);

  AssociationResponse* association_response = new (std::nothrow) AssociationResponse();
  REQUIRE(association_response);

  // Checks deleting of nullptrs. Expect success
  CHECK(association_response->sessionHeader.length == nullptr);
  CHECK(association_response->msdseUserInfo.option_list.value == nullptr);
  CHECK(association_response->msdseUserInfo.supported_aprofiles.value == nullptr);
  CHECK(IntellivueAssociationResponse::DeleteAssociationResponse(association_response)
        == DicesRcPhilipsIntellivueMP70::OK);

  // Allocate length array and then delete it. Expect success and nullptr set.
  const int klength_size = 3;
  association_response->sessionHeader.length = new (std::nothrow) uint8_t[3]();
  REQUIRE(association_response->sessionHeader.length);

  CHECK(IntellivueAssociationResponse::DeleteAssociationResponse(association_response)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(association_response->sessionHeader.length == nullptr);

  // Allocate option_list. Expect success and nullptr set.
  association_response->msdseUserInfo.option_list.count = 5;
  association_response->msdseUserInfo.option_list.length = 100;
  association_response->msdseUserInfo.option_list.value = new (std::nothrow) intellivue::AVAType[5]();
  REQUIRE(association_response->msdseUserInfo.option_list.value);
  for (int ix = 0; ix < 5; ix++)
  {
    association_response->msdseUserInfo.option_list.value[ix].attribute_id = 0;
    association_response->msdseUserInfo.option_list.value[ix].length = 10;
    association_response->msdseUserInfo.option_list.value[ix].attribute_val = new (std::nothrow) uint8_t[10]();
    REQUIRE(association_response->msdseUserInfo.option_list.value[ix].attribute_val);
  }

  CHECK(IntellivueAssociationResponse::DeleteAssociationResponse(association_response)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(association_response->msdseUserInfo.option_list.value == nullptr);

  // Allocate supported_aprofiles. Expect success and nullptr set.
  association_response->msdseUserInfo.supported_aprofiles.count = 5;
  association_response->msdseUserInfo.supported_aprofiles.length = 100;
  association_response->msdseUserInfo.supported_aprofiles.value = new (std::nothrow) intellivue::AVAType[5]();
  REQUIRE(association_response->msdseUserInfo.supported_aprofiles.value);
  for (int ix = 0; ix < 5; ix++)
  {
    association_response->msdseUserInfo.supported_aprofiles.value[ix].attribute_id = 0;
    association_response->msdseUserInfo.supported_aprofiles.value[ix].length = 10;
    association_response->msdseUserInfo.supported_aprofiles.value[ix].attribute_val = new (std::nothrow) uint8_t[10]();
    REQUIRE(association_response->msdseUserInfo.supported_aprofiles.value[ix].attribute_val);
  }

  CHECK(IntellivueAssociationResponse::DeleteAssociationResponse(association_response)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(association_response->msdseUserInfo.supported_aprofiles.value == nullptr);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IntellivueAssociationResponseUnitTest::FindAssociationResponseUserDataStart()
{
  int userdataindex = 0;
  uint8_t* buffer = new (std::nothrow) uint8_t[100]();
  REQUIRE(buffer);

  CHECK(IntellivueAssociationResponse::FindAssociationResponseUserDataStart(nullptr, buffer, 0, 0)
        == DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE);

  CHECK(IntellivueAssociationResponse::FindAssociationResponseUserDataStart(&userdataindex, nullptr, 0, 0)
        == DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE);

  uint8_t user_data_start1[] = { 0xBE, 0x80, 0x28, 0x80, 0x81 };
  uint8_t user_data_start2[] = { 0xBE, 0x80, 0x28, 0x80, 0x02, 0x01,
    0x02, 0x81 };

  // Copy user_data_start1 to beginning of buffer. Function should find user data
  // and the user data index is after the set of bytes + 1.
  memset(buffer, 0x00, 100);
  memmove(buffer, user_data_start1, sizeof(user_data_start1));

  CHECK(IntellivueAssociationResponse::FindAssociationResponseUserDataStart(&userdataindex, buffer, 100, 0)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(userdataindex == sizeof(user_data_start1));

  // Copy user_data_start1 to middle of buffer. Function should find user data
  // and the user data index is after the set of bytes + 1.
  memset(buffer, 0x00, 100);
  memmove(&buffer[50], user_data_start1, sizeof(user_data_start1));

  CHECK(IntellivueAssociationResponse::FindAssociationResponseUserDataStart(&userdataindex, buffer, 100, 0)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(userdataindex == 50 + sizeof(user_data_start1));

  // Copy user_data_start1 to end of buffer. Function should return success,
  // but not find user data. The user data index should be returned as -1
  // because there are no bytes after the user data start sequence,
  // meaning the user data index would've exceeded the buffer size.
  memset(buffer, 0x00, 100);
  memmove(&buffer[100 - sizeof(user_data_start1)], user_data_start1, sizeof(user_data_start1));

  CHECK(IntellivueAssociationResponse::FindAssociationResponseUserDataStart(&userdataindex, buffer, 100, 0)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(userdataindex == -1);

  // Do same tests with user_data_start2

  // Copy user_data_start2 to beginning of buffer. Function should find user data
  // and the user data index is after the set of bytes + 1.
  memset(buffer, 0x00, 100);
  memmove(buffer, user_data_start2, sizeof(user_data_start2));

  CHECK(IntellivueAssociationResponse::FindAssociationResponseUserDataStart(&userdataindex, buffer, 100, 0)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(userdataindex == sizeof(user_data_start2));

  // Copy user_data_start2 to middle of buffer. Function should find user data
  // and the user data index is after the set of bytes + 1.
  memset(buffer, 0x00, 100);
  memmove(&buffer[50], user_data_start2, sizeof(user_data_start2));

  CHECK(IntellivueAssociationResponse::FindAssociationResponseUserDataStart(&userdataindex, buffer, 100, 0)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(userdataindex == 50 + sizeof(user_data_start2));

  // Copy user_data_start2 to end of buffer. Function should return success,
  // but not find user data. The user data index should be returned as -1
  // because there are no bytes after the user data start sequence,
  // meaning the user data index would've exceeded the buffer size.
  memset(buffer, 0x00, 100);
  memmove(&buffer[100 - sizeof(user_data_start2)], user_data_start2, sizeof(user_data_start2));

  CHECK(IntellivueAssociationResponse::FindAssociationResponseUserDataStart(&userdataindex, buffer, 100, 0)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(userdataindex == -1);


  // Copy user_data_start2 to beginning of buffer. Function should not find user data
  // because, the numbytes passed into function is the size of the user_data_start2.
  // So same effect as the previous test, execpt the byte sequence appears at the
  // start of the buffer.
  memset(buffer, 0x00, 100);
  memmove(buffer, user_data_start2, sizeof(user_data_start2));

  CHECK(IntellivueAssociationResponse::FindAssociationResponseUserDataStart(&userdataindex, buffer, sizeof(user_data_start2), 0)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(userdataindex == -1);

  // Copy user_data_start2 to beginning of buffer. Function should not find user data
  // because, the index has passed the start of the user_data_start2 sequence.
  // Function will return success, but user data index will be set to -1,
  // because user data start sequnces is not found.
  memset(buffer, 0x00, 100);
  memmove(buffer, user_data_start2, sizeof(user_data_start2));

  CHECK(IntellivueAssociationResponse::FindAssociationResponseUserDataStart(&userdataindex, buffer, 100, 1)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(userdataindex == -1);

  delete [] buffer;
  buffer = nullptr;

  return DicesRcUnitTest::OK;
}
