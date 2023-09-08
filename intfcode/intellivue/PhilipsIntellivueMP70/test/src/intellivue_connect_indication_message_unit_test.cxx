/**
 * @file intellivue_connect_indication_message_unit_test.cxx
 *
 * @brief Defines a unit test class for IntellivueConnectIndicationMessage class.
 *
 * @author M Szwaja
 */
//=============================================================================
#include "intellivue_connect_indication_message_unit_test.h"
#include <ndds/ndds_namespace_cpp.h>
#include <mdsSupport.h>
#include "catch.hpp"
#include "UnitTestReturnCodes.h"
#include "PhilipsIntellivueMP70ReturnCodes.h"
#include <dices_rc_driver.h>

IntellivueConnectIndicationMessageUnitTest::IntellivueConnectIndicationMessageUnitTest() { }

IntellivueConnectIndicationMessageUnitTest::~IntellivueConnectIndicationMessageUnitTest() { }

DicesRcUnitTest IntellivueConnectIndicationMessageUnitTest::RunTests()
{
  static const char* sfn = "IntellivueConnectIndicationMessageUnitTest::RunTests() ";
  DicesRcUnitTest status = DicesRcUnitTest::OK;

  SECTION("IsConnectIndicationMessage()")
  {
    DicesRcUnitTest test_status = IsConnectIndicationMessage();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("ParseConnectIndicationMessage()")
  {
    DicesRcUnitTest test_status = ParseConnectIndicationMessage();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("DeleteConnectIndicationMessage()")
  {
    DicesRcUnitTest test_status = DeleteConnectIndicationMessage();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("SetMDSWithConnectIndicationMessage()")
  {
    DicesRcUnitTest test_status = SetMDSWithConnectIndicationMessage();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("GetIPAddressString()")
  {
    DicesRcUnitTest test_status = GetIPAddressString();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  SECTION("GetDataExportProtocolPortNumber()")
  {
    DicesRcUnitTest test_status = GetDataExportProtocolPortNumber();
    if (test_status != DicesRcUnitTest::OK) status = test_status;
  }
  return status;
}

DicesRcUnitTest IntellivueConnectIndicationMessageUnitTest::IsConnectIndicationMessage()
{
  bool ismsg = false;

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

  static const uint8_t kE1[] = { 0xE1 };
  static const uint8_t kCNResp[] = { CN_SPDU_SI };
  static const uint8_t kACResp[] = { AC_SPDU_SI };
  static const uint8_t kRFResp[] = { RF_SPDU_SI };
  static const uint8_t kFNResp[] = { FN_SPDU_SI };
  static const uint8_t kDNResp[] = { DN_SPDU_SI };
  static const uint8_t kABResp[] = { AB_SPDU_SI };
  static const uint8_t kXResp[] = { 0xFF };
  static const uint8_t kEmptyResp[] = { };

  std::vector<TestCase> test_data = {
    { "Null is_msg parameter test",
      nullptr, kCNResp, 1,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE, false },
    { "Null buffer parameter test",
      &ismsg, nullptr, 0,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE, false },
    { "0xE1 test",
      &ismsg, kE1, 1,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::OK, false },
    { "CN_SPDU_SI test",
      &ismsg, kCNResp, 1,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::OK, false },
    { "AC_SPDU_SI test",
      &ismsg, kACResp, 1,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::OK, false },
    { "RF_SPDU_SI test",
      &ismsg, kRFResp, 1,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::OK, false },
    { "FN_SPDU_SI test",
      &ismsg, kFNResp, 1,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::OK, false },
    { "DN_SPDU_SI test",
      &ismsg, kDNResp, 1,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::OK, false },
    { "AB_SPDU_SI test",
      &ismsg, kABResp, 1,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::OK, false },
    { "Other message test",
      &ismsg, kXResp, 1,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::OK, true },
    { "Empty message test",
      &ismsg, kEmptyResp, 0,
      DicesRcPhilipsIntellivueMP70::FAIL,
      DicesRcPhilipsIntellivueMP70::OK, false }
  };

  for (TestCase tc : test_data)
  {
    INFO(tc.desc);
    tc.retcode = IntellivueConnectIndicationMessage::IsConnectIndicationMessage(
      tc.is_msg,
      const_cast<uint8_t*>(tc.buffer),
      tc.numbytes);
    CHECK(tc.retcode == tc.x_retcode);
    if (tc.retcode == DicesRcPhilipsIntellivueMP70::OK)
    {
      CHECK(*tc.is_msg == tc.x_is_msg);
    }
  }

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IntellivueConnectIndicationMessageUnitTest::ParseConnectIndicationMessage()
{
  ConnectIndication connect_indication = {0};
  const int kmax_buffer_size = 100;
  uint8_t buffer[kmax_buffer_size] = {0};

  CHECK(IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(nullptr, buffer, kmax_buffer_size)
        == DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE);
  CHECK(IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(&connect_indication, nullptr, kmax_buffer_size)
        == DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE);

  // 3 is not enough bytes to parse Nomenclature. Function should return failure.
  CHECK(IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(&connect_indication, buffer, 3)
        == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);
  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
          == DicesRcPhilipsIntellivueMP70::OK);
  // 4 is enough bytes to parse Nomenclature, but not enought bytes to parse
  // ROapdus. Function should return failure.
  CHECK(IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(&connect_indication, buffer, 4)
        == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);
  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
          == DicesRcPhilipsIntellivueMP70::OK);
  // 8 is enough bytes to parse Nomenclature and ROapdus, but not enough to
  // parse ROIVapdu.
  CHECK(IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(&connect_indication, buffer, 8)
        == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);
  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
          == DicesRcPhilipsIntellivueMP70::OK);
  // 14 is enough bytes to parse up to ROIVapdu, but not enough to
  // parse EventReportArgument.
  CHECK(IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(&connect_indication, buffer, 14)
        == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);
  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
          == DicesRcPhilipsIntellivueMP70::OK);
  // 28 is enough bytes to parse up to EventReportArgument, but not enough to
  // parse ConnectIndInfo count and length bytes of AttributeList.
  CHECK(IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(&connect_indication, buffer, 28)
        == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);
  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
          == DicesRcPhilipsIntellivueMP70::OK);
  // 32 is enough bytes to parse up ConnectIndInfo count and length bytes of AttributeList.
  // Function will return success because AttributeList count is zero, and therefore
  // loop is not entered to parse more bytes.
  CHECK(IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(&connect_indication, buffer, 32)
        == DicesRcPhilipsIntellivueMP70::OK);
  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
          == DicesRcPhilipsIntellivueMP70::OK);
  // 32 is enough bytes to parse up ConnectIndInfo count and length bytes of AttributeList,
  // but not enough bytes to parse attribute_id and length.
  // Function will return failure because loop is entered to parse AVATypes.
  buffer[29] = 0x01; // count is 1. should enter loop
  CHECK(IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(&connect_indication, buffer, 32)
        == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);
  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
          == DicesRcPhilipsIntellivueMP70::OK);
  // 36 is enough bytes to parse up ConnectIndInfo AttributeList AVAType
  // attribute_id and length. Function should return success.
  buffer[29] = 0x01; // count is 1. should enter loop
  CHECK(IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(&connect_indication, buffer, 36)
        == DicesRcPhilipsIntellivueMP70::OK);
  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
          == DicesRcPhilipsIntellivueMP70::OK);

  // Test for currupted length fields in buffer.
  memset(buffer, 0x00, 100); // Reset.

  // 32 bytes is just enough to parse without failure. Set ROapdus length 1 byte to long.
  buffer[7] = 25; // Set ROapdus length field greater than 24 (remaining buffer size)
  CHECK(IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(&connect_indication, buffer, 32)
        == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);
  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
          == DicesRcPhilipsIntellivueMP70::OK);

  // Set acceptable ROapdus length. Function should return success.
  buffer[7] = 24; // Set appropriate ROapdus length
  CHECK(IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(&connect_indication, buffer, 32)
        == DicesRcPhilipsIntellivueMP70::OK);
  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
          == DicesRcPhilipsIntellivueMP70::OK);

  // Set ROIVapdu length 1 byte to long.
  buffer[13] = 19; // Set ROapdus length field greater than 18 (remaining buffer size)
  CHECK(IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(&connect_indication, buffer, 32)
        == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);

  // Set acceptable ROIVapdu length. Function should return success.
  buffer[13] = 18; // Set appropriate ROapdus length
  CHECK(IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(&connect_indication, buffer, 32)
        == DicesRcPhilipsIntellivueMP70::OK);
  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
          == DicesRcPhilipsIntellivueMP70::OK);

  // Set EventReportArgument length 1 byte to long.
  buffer[27] = 5; // Set EventReportArgument length field greater than 4 (remaining buffer size)
  CHECK(IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(&connect_indication, buffer, 32)
        == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);
  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
          == DicesRcPhilipsIntellivueMP70::OK);

  // Set acceptable EventReportArgument length. Function should return success.
  buffer[27] = 4; // Set appropriate EventReportArgument length
  CHECK(IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(&connect_indication, buffer, 32)
        == DicesRcPhilipsIntellivueMP70::OK);
  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
          == DicesRcPhilipsIntellivueMP70::OK);

  // Set ConnectIndInfo AttributeList length 1 byte to long.
  buffer[31] = 1; // Set ConnectIndInfo AttributeList length field greater than 0 (remaining buffer size)
  CHECK(IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(&connect_indication, buffer, 32)
        == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);
  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
          == DicesRcPhilipsIntellivueMP70::OK);

  // Set acceptable ConnectIndInfo AttributeList length. Function should return success.
  buffer[31] = 0; // Set appropriate ConnectIndInfo AttributeList length
  CHECK(IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(&connect_indication, buffer, 32)
        == DicesRcPhilipsIntellivueMP70::OK);
  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
          == DicesRcPhilipsIntellivueMP70::OK);

  // Increased buffer length to 36 so we can test AVAType length.
  // Setting ConnectIndInfo count to 1 and length to 4 to enter loop.
  // Setting ConnectIndInfo AVAType length 1 byte to long.
  // Function should return failure.
  buffer[29] = 1; // Set appropriate ConnectIndInfo AttributeList count
  buffer[31] = 4; // Set appropriate ConnectIndInfo AttributeList length
  buffer[35] = 1; // Set ConnectIndInfo AttributeList AVAType length field greater than 0 (remaining buffer size)
  CHECK(IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(&connect_indication, buffer, 36)
        == DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE);
  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
          == DicesRcPhilipsIntellivueMP70::OK);

  // Set acceptable ConnectIndInfo AttributeList AVAType length. Function should return success.
  buffer[35] = 0; // Set appropriate ConnectIndInfo AttributeList AVAType length
  CHECK(IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(&connect_indication, buffer, 36)
        == DicesRcPhilipsIntellivueMP70::OK);
  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
          == DicesRcPhilipsIntellivueMP70::OK);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IntellivueConnectIndicationMessageUnitTest::DeleteConnectIndicationMessage()
{
  ConnectIndication connect_indication = {0};

  // Test null pointer function argument. Function should return failure.
  CHECK(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(nullptr)
      == DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE);

  // Tests newly constructed ConnectIndication message. Everything
  // inside connect_indication should be null pointer already.
  CHECK(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
      == DicesRcPhilipsIntellivueMP70::OK);

  // Tests deletion of allocated AVAType array.
  // Function should return success and set AVAType value to null pointer.
  const int kavatype_len = 4;
  connect_indication.conninfo.count = kavatype_len;
  connect_indication.conninfo.value = new (std::nothrow) intellivue::AVAType[kavatype_len]();
  REQUIRE(connect_indication.conninfo.value);
  CHECK(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
      == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(connect_indication.conninfo.value == nullptr);

  // Tests count != 0 with AVAType value array as a null pointer.
  // Function should return success.
  connect_indication.conninfo.count = 1;
  connect_indication.conninfo.value = nullptr;
  CHECK(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
      == DicesRcPhilipsIntellivueMP70::OK);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IntellivueConnectIndicationMessageUnitTest::SetMDSWithConnectIndicationMessage()
{
  ConnectIndication connect_indication = {0};

  // Tests null pointer function argument failure.
  CHECK(IntellivueConnectIndicationMessage::SetMDSWithConnectIndicationMessage(nullptr, connect_indication)
        == DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE);

  // Tests null pointer function argument failure when the MDS pointer is null.
  std::pair<DicesRcDriver, ice::MDS*> instance_pair(DicesRcDriver::NO_NEW_DATA, nullptr);
  CHECK(IntellivueConnectIndicationMessage::SetMDSWithConnectIndicationMessage(&instance_pair, connect_indication)
        == DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE);
  CHECK(instance_pair.first == DicesRcDriver::NO_NEW_DATA);

  // Create the DDS instance and assign it to the MDS pointer in pair. This
  // should resolve the null pointer failures and the function should return
  // success.
  instance_pair.second = ice::MDS::TypeSupport::create_data();
  REQUIRE(instance_pair.second);
  instance_pair.first = DicesRcDriver::NO_NEW_DATA;
  CHECK(IntellivueConnectIndicationMessage::SetMDSWithConnectIndicationMessage(&instance_pair, connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(instance_pair.first == DicesRcDriver::NO_NEW_DATA);

  // Set count != 0 to enter loop, but AVAType pointer will be null.
  // Function should return success, but there are no attributes to parse into MDS
  const int kattr_list_count = 1;
  connect_indication.conninfo.count = kattr_list_count;
  connect_indication.conninfo.value = nullptr;
  instance_pair.first = DicesRcDriver::NO_NEW_DATA;
  CHECK(IntellivueConnectIndicationMessage::SetMDSWithConnectIndicationMessage(&instance_pair, connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(instance_pair.first == DicesRcDriver::NO_NEW_DATA);

  // The count != 0, AVAType pointer value is not null, but attribute_val is null pointer.
  // Function should return success, but still no system type attribute to parse.
  connect_indication.conninfo.value = new (std::nothrow) intellivue::AVAType[kattr_list_count]();
  REQUIRE(connect_indication.conninfo.value);
  REQUIRE(kattr_list_count > 0);
  connect_indication.conninfo.value[0].attribute_id = NOM_ATTR_SYS_TYPE;
  connect_indication.conninfo.value[0].length = 0;
  connect_indication.conninfo.value[0].attribute_val = nullptr;
  instance_pair.first = DicesRcDriver::NO_NEW_DATA;
  CHECK(IntellivueConnectIndicationMessage::SetMDSWithConnectIndicationMessage(&instance_pair, connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(instance_pair.first == DicesRcDriver::NO_NEW_DATA);

  // Set attribute_val for system type, and set testable values.
  // Function should return success, and we should see these values are
  // populated in the MDS instance.
  connect_indication.conninfo.value[0].attribute_val = new (std::nothrow) uint8_t[sizeof(intellivue::TYPE)]();
  REQUIRE(connect_indication.conninfo.value[0].attribute_val);
  // Convert back to type so we can assign values.
  intellivue::TYPE* type_val = reinterpret_cast<intellivue::TYPE*>(connect_indication.conninfo.value[0].attribute_val);
  REQUIRE(type_val);
  // Set partition to 1 and code to 2.
  const int kpartition_val = 1;
  const int kcode_val = 2;
  type_val->partition = kpartition_val;
  type_val->code = kcode_val;
  REQUIRE(instance_pair.second->system_type.partition == 0);
  REQUIRE(instance_pair.second->system_type.code == 0);
  instance_pair.first = DicesRcDriver::NO_NEW_DATA;
  CHECK(IntellivueConnectIndicationMessage::SetMDSWithConnectIndicationMessage(&instance_pair, connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(instance_pair.second->system_type.partition == kpartition_val);
  CHECK(instance_pair.second->system_type.code == kcode_val);
  CHECK(instance_pair.first == DicesRcDriver::OK);

  // Delete all the allocations made for previous tests, so we can start testing
  // the next attribute.
  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);

  // Create new AVAType array. Test production specification with null pointer
  // attribute_val. The function should return success, but there's nothing
  // to set in the MDS.
  connect_indication.conninfo.value = new (std::nothrow) intellivue::AVAType[1]();
  REQUIRE(connect_indication.conninfo.value);
  connect_indication.conninfo.value[0].attribute_id = NOM_ATTR_ID_PROD_SPECN;
  connect_indication.conninfo.value[0].length = 0;
  connect_indication.conninfo.value[0].attribute_val = nullptr;
  instance_pair.first = DicesRcDriver::NO_NEW_DATA;
  CHECK(IntellivueConnectIndicationMessage::SetMDSWithConnectIndicationMessage(&instance_pair, connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(instance_pair.first == DicesRcDriver::NO_NEW_DATA);

  // Allocate attribute_val with production specification. the production
  // specification entry array pointer will be null. The function should
  // return success, but there's nothing ot set in the MDS.
  connect_indication.conninfo.value[0].attribute_val = new (std::nothrow) uint8_t[sizeof(intellivue::ProductionSpec)]();
  REQUIRE(connect_indication.conninfo.value[0].attribute_val);
  instance_pair.first = DicesRcDriver::NO_NEW_DATA;
  CHECK(IntellivueConnectIndicationMessage::SetMDSWithConnectIndicationMessage(&instance_pair, connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(instance_pair.first == DicesRcDriver::NO_NEW_DATA);

  // Allocate the production specification entry list and assign pointer.
  // Everything in the production specification entry is zero, event the
  // prod_spec value which is a pointer. The function should return success.
  // length of prduction specification in the MDS will be set, but entries
  // will be default.
  intellivue::ProductionSpec* attr_val = reinterpret_cast<intellivue::ProductionSpec*>(
        connect_indication.conninfo.value[0].attribute_val);
  REQUIRE(attr_val);
  const int kprod_spec_entry_count = 5;
  attr_val->count = kprod_spec_entry_count;
  attr_val->length = 0;
  attr_val->value = new (std::nothrow) intellivue::ProdSpecEntry[kprod_spec_entry_count]();
  REQUIRE(attr_val->value);
  instance_pair.first = DicesRcDriver::NO_NEW_DATA;
  CHECK(IntellivueConnectIndicationMessage::SetMDSWithConnectIndicationMessage(&instance_pair, connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);
  REQUIRE(instance_pair.second->production_specification.length() == kprod_spec_entry_count);
  for (int ix = 0; ix < kprod_spec_entry_count; ix++)
  {
    CHECK(instance_pair.second->production_specification.get_at(ix).component_id == 0);
    CHECK(instance_pair.second->production_specification.get_at(ix).spec_type == ice::ProdSpecType::unspecified);
    CHECK(std::string(instance_pair.second->production_specification.get_at(ix).prod_spec) == std::string(""));
  }
  CHECK(instance_pair.first == DicesRcDriver::OK);

  // Set all the production specification entries and allocate memory for the
  // prod_spec.value string. Set string to testable value. Function should
  // return success, and the MDS should be set with the same production
  // specification.
  const std::string test_str = "hello";
  for (int ix = 0; ix < kprod_spec_entry_count; ix++)
  {
    intellivue::ProdSpecEntry* entry = reinterpret_cast<intellivue::ProdSpecEntry*>(&attr_val->value[ix]);
    entry->component_id = ix;
    entry->spec_type = static_cast<int>(ice::ProdSpecType::part_number);
    entry->prod_spec.length = 0;
    const int kvalue_len = 10;
    entry->prod_spec.value = new (std::nothrow) uint8_t[kvalue_len]();
    REQUIRE(entry->prod_spec.value);

    strncpy(reinterpret_cast<char*>(entry->prod_spec.value), test_str.c_str(), kvalue_len);
    entry->prod_spec.value[kvalue_len - 1] = '\0';
  }
  instance_pair.first = DicesRcDriver::NO_NEW_DATA;
  CHECK(IntellivueConnectIndicationMessage::SetMDSWithConnectIndicationMessage(&instance_pair, connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);
  REQUIRE(instance_pair.second->production_specification.length() == kprod_spec_entry_count);
  for (int ix = 0; ix < kprod_spec_entry_count; ix++)
  {
    CHECK(instance_pair.second->production_specification.get_at(ix).component_id == ix);
    CHECK(instance_pair.second->production_specification.get_at(ix).spec_type == ice::ProdSpecType::part_number);
    CHECK(std::string(instance_pair.second->production_specification.get_at(ix).prod_spec) == std::string(test_str));
  }
  CHECK(instance_pair.first == DicesRcDriver::OK);

  // Delete all the allocations made for previous tests, so we can start testing
  // the next attribute.
  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);

  // Create new AVAType array. Test id model with null pointer
  // attribute_val. The function should return success, but there's nothing
  // to set in the MDS.
  const int kattr_list_count2 = 1;
  connect_indication.conninfo.value = new (std::nothrow) intellivue::AVAType[kattr_list_count2]();
  REQUIRE(connect_indication.conninfo.value);
  REQUIRE(kattr_list_count2 > 0);
  connect_indication.conninfo.value[0].attribute_id = NOM_ATTR_ID_MODEL;
  connect_indication.conninfo.value[0].length = 0;
  connect_indication.conninfo.value[0].attribute_val = nullptr;
  instance_pair.first = DicesRcDriver::NO_NEW_DATA;
  CHECK(IntellivueConnectIndicationMessage::SetMDSWithConnectIndicationMessage(&instance_pair, connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(instance_pair.first == DicesRcDriver::NO_NEW_DATA);

  // Allocate attribute_val with sytem model. the sytem model string
  // pointers will be null. The function should return success, but
  // there's nothing ot set in the MDS.
  connect_indication.conninfo.value[0].attribute_val = new (std::nothrow) uint8_t[sizeof(intellivue::SystemModel)]();
  REQUIRE(connect_indication.conninfo.value[0].attribute_val);
  instance_pair.first = DicesRcDriver::NO_NEW_DATA;
  CHECK(IntellivueConnectIndicationMessage::SetMDSWithConnectIndicationMessage(&instance_pair, connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(instance_pair.first == DicesRcDriver::NO_NEW_DATA);

  // Allocate strings within system model. Set them with testable values.
  // The function should return success and the MDS set with these values.
  intellivue::SystemModel* sys_model = reinterpret_cast<intellivue::SystemModel*>(
        connect_indication.conninfo.value[0].attribute_val);
  REQUIRE(sys_model);
  const int kmax_str_size = 15;
  sys_model->manufacturer.value = new (std::nothrow) uint8_t[kmax_str_size]();
  REQUIRE(sys_model->manufacturer.value);
  sys_model->model_number.value = new (std::nothrow) uint8_t[kmax_str_size]();
  REQUIRE(sys_model->model_number.value);
  const std::string kmanufacturer = "Manufacturer";
  const std::string kmodel = "Model";
  strncpy(reinterpret_cast<char*>(sys_model->manufacturer.value), kmanufacturer.c_str(), kmax_str_size);
  sys_model->manufacturer.value[kmax_str_size - 1] = '\0';
  strncpy(reinterpret_cast<char*>(sys_model->model_number.value), kmodel.c_str(), kmax_str_size);
  sys_model->model_number.value[kmax_str_size - 1] = '\0';
  REQUIRE(std::string(instance_pair.second->system_model.manufacturer) == std::string(""));
  REQUIRE(std::string(instance_pair.second->system_model.model_number) == std::string(""));
  instance_pair.first = DicesRcDriver::NO_NEW_DATA;
  CHECK(IntellivueConnectIndicationMessage::SetMDSWithConnectIndicationMessage(&instance_pair, connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(std::string(instance_pair.second->system_model.manufacturer) == kmanufacturer);
  CHECK(std::string(instance_pair.second->system_model.model_number) == kmodel);
  CHECK(instance_pair.first == DicesRcDriver::OK);

  // Delete all the allocations made for previous tests, so we can start testing
  // the next attribute.
  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);
  // Reset MDS instance data for new test, because attributes have already
  // been set by previous tests.
  REQUIRE(ice::MDS::TypeSupport::delete_data(instance_pair.second) == DDS::RETCODE_OK);
  instance_pair.second = ice::MDS::TypeSupport::create_data();
  REQUIRE(instance_pair.second);
  instance_pair.first = DicesRcDriver::NO_NEW_DATA;

  // Test multiple attributes. Test unknown attribute_id with in AttributeList.
  // Function should succeed. MDS should be set with known attribute values
  // and set to publish.
  const int kattr_list_count3 = 4;
  connect_indication.conninfo.count = kattr_list_count3;
  connect_indication.conninfo.value = new (std::nothrow) intellivue::AVAType[kattr_list_count3]();
  REQUIRE(connect_indication.conninfo.value);
  REQUIRE(kattr_list_count3 > 3);
  // Unknown attribute_id, with allocated attribute_val.
  connect_indication.conninfo.value[0].attribute_id = 0;
  connect_indication.conninfo.value[0].length = 0;
  connect_indication.conninfo.value[0].attribute_val = new (std::nothrow) uint8_t[1]();
  // Type
  connect_indication.conninfo.value[1].attribute_id = NOM_ATTR_SYS_TYPE;
  connect_indication.conninfo.value[1].length = 0;
  connect_indication.conninfo.value[1].attribute_val = new (std::nothrow) uint8_t[sizeof(intellivue::TYPE)]();
  REQUIRE(connect_indication.conninfo.value[1].attribute_val);
  intellivue::TYPE* type_val2 = reinterpret_cast<intellivue::TYPE*>(connect_indication.conninfo.value[1].attribute_val);
  REQUIRE(type_val2);
  type_val2->partition = kpartition_val;
  type_val2->code = kcode_val;
  // Production specification
  connect_indication.conninfo.value[2].attribute_id = NOM_ATTR_ID_PROD_SPECN;
  connect_indication.conninfo.value[2].length = 0;
  connect_indication.conninfo.value[2].attribute_val = new (std::nothrow) uint8_t[sizeof(intellivue::ProductionSpec)]();
  REQUIRE(connect_indication.conninfo.value[2].attribute_val);
  intellivue::ProductionSpec* attr_val2 = reinterpret_cast<intellivue::ProductionSpec*>(
        connect_indication.conninfo.value[2].attribute_val);
  REQUIRE(attr_val2);
  const int kprod_spec_entry_count2 = 1;
  attr_val2->count = kprod_spec_entry_count2;
  attr_val2->length = 0;
  attr_val2->value = new (std::nothrow) intellivue::ProdSpecEntry[kprod_spec_entry_count2]();
  REQUIRE(attr_val2->value);
  for (int ix = 0; ix < kprod_spec_entry_count2; ix++)
  {
    intellivue::ProdSpecEntry* entry = reinterpret_cast<intellivue::ProdSpecEntry*>(&attr_val2->value[ix]);
    REQUIRE(entry);
    entry->component_id = ix;
    entry->spec_type = static_cast<int>(ice::ProdSpecType::part_number);
    entry->prod_spec.length = 0;
    const int kvalue_len = 10;
    entry->prod_spec.value = new (std::nothrow) uint8_t[kvalue_len]();
    REQUIRE(entry->prod_spec.value);

    strncpy(reinterpret_cast<char*>(entry->prod_spec.value), test_str.c_str(), kvalue_len);
    entry->prod_spec.value[kvalue_len - 1] = '\0';
  }
  // SystemModel
  connect_indication.conninfo.value[3].attribute_id = NOM_ATTR_ID_MODEL;
  connect_indication.conninfo.value[3].length = 0;
  connect_indication.conninfo.value[3].attribute_val = new (std::nothrow) uint8_t[sizeof(intellivue::SystemModel)]();
  REQUIRE(connect_indication.conninfo.value[3].attribute_val);
  intellivue::SystemModel* sys_model2 = reinterpret_cast<intellivue::SystemModel*>(
        connect_indication.conninfo.value[3].attribute_val);
  REQUIRE(sys_model2);
  sys_model2->manufacturer.value = new (std::nothrow) uint8_t[kmax_str_size]();
  REQUIRE(sys_model2->manufacturer.value);
  sys_model2->model_number.value = new (std::nothrow) uint8_t[kmax_str_size]();
  REQUIRE(sys_model2->model_number.value);
  strncpy(reinterpret_cast<char*>(sys_model2->manufacturer.value), kmanufacturer.c_str(), kmax_str_size);
  sys_model2->manufacturer.value[kmax_str_size - 1] = '\0';
  strncpy(reinterpret_cast<char*>(sys_model2->model_number.value), kmodel.c_str(), kmax_str_size);
  sys_model2->model_number.value[kmax_str_size - 1] = '\0';
  // Test and check results.
  CHECK(IntellivueConnectIndicationMessage::SetMDSWithConnectIndicationMessage(&instance_pair, connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(instance_pair.second->system_type.partition == kpartition_val);
  CHECK(instance_pair.second->system_type.code == kcode_val);
  REQUIRE(instance_pair.second->production_specification.length() == kprod_spec_entry_count2);
  for (int ix = 0; ix < kprod_spec_entry_count2; ix++)
  {
    CHECK(instance_pair.second->production_specification.get_at(ix).component_id == ix);
    CHECK(instance_pair.second->production_specification.get_at(ix).spec_type == ice::ProdSpecType::part_number);
    CHECK(std::string(instance_pair.second->production_specification.get_at(ix).prod_spec) == std::string(test_str));
  }
  CHECK(std::string(instance_pair.second->system_model.manufacturer) == kmanufacturer);
  CHECK(std::string(instance_pair.second->system_model.model_number) == kmodel);
  CHECK(instance_pair.first == DicesRcDriver::OK);

  // Tests calling again with the same message. Function should not set OK for
  // publishing.
  instance_pair.first = DicesRcDriver::NO_NEW_DATA;
  CHECK(IntellivueConnectIndicationMessage::SetMDSWithConnectIndicationMessage(&instance_pair, connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(instance_pair.first == DicesRcDriver::NO_NEW_DATA);


  // Tests changing component_id of production specification entry. Changed from
  // 1 to 10. Function should return success and set MDS with change to publish.
  REQUIRE(kprod_spec_entry_count2 > 0);
  intellivue::ProdSpecEntry* entry = reinterpret_cast<intellivue::ProdSpecEntry*>(&attr_val2->value[0]);
  const int knew_comp_id = 10;
  entry->component_id = knew_comp_id; // Change value of component id.
  instance_pair.first = DicesRcDriver::NO_NEW_DATA;
  REQUIRE(instance_pair.second->production_specification.length() > 0);
  CHECK(instance_pair.second->production_specification.get_at(0).component_id == 0);
  CHECK(IntellivueConnectIndicationMessage::SetMDSWithConnectIndicationMessage(&instance_pair, connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);
  REQUIRE(instance_pair.second->production_specification.length() > 0);
  CHECK(instance_pair.second->production_specification.get_at(0).component_id == knew_comp_id);
  CHECK(instance_pair.first == DicesRcDriver::OK);


  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);
  REQUIRE(ice::MDS::TypeSupport::delete_data(instance_pair.second) == DDS::RETCODE_OK);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IntellivueConnectIndicationMessageUnitTest::GetIPAddressString()
{
  std::string ip_address;
  ConnectIndication connect_indication = {0};

  // Tests null pointer funtion argument.
  CHECK(IntellivueConnectIndicationMessage::GetIPAddressString(nullptr, connect_indication)
        == DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE);

  // Test will succeed, but since attribute list count is zero there's
  // no ip address found.
  CHECK(IntellivueConnectIndicationMessage::GetIPAddressString(&ip_address, connect_indication)
        == DicesRcPhilipsIntellivueMP70::GET_IP_ADDRESS_INFO_FAILURE);

  // Tests loop entered but null pointer for AVAType list. Function
  // Should return failure because IP address was not found.
  const int kattr_list_count = 2;
  connect_indication.conninfo.count = kattr_list_count;
  CHECK(IntellivueConnectIndicationMessage::GetIPAddressString(&ip_address, connect_indication)
        == DicesRcPhilipsIntellivueMP70::GET_IP_ADDRESS_INFO_FAILURE);

  // Allocate attributes. One attribute will be unknown, and the other will be
  // the production specification. The attribute_val pointers will be null.
  // Function should return failure because the IP address was not found.

  connect_indication.conninfo.value = new (std::nothrow) intellivue::AVAType[kattr_list_count]();
  REQUIRE(connect_indication.conninfo.value);
  REQUIRE(kattr_list_count > 1);
  connect_indication.conninfo.value[0].attribute_id = 0;
  connect_indication.conninfo.value[1].attribute_id = NOM_ATTR_NET_ADDR_INFO;

  // Tests AVATypes with null pointer attribute_val
  CHECK(IntellivueConnectIndicationMessage::GetIPAddressString(&ip_address, connect_indication)
        == DicesRcPhilipsIntellivueMP70::GET_IP_ADDRESS_INFO_FAILURE);

  // Allocate attribute_val for the second attribute. Function should
  // return success with ip address string set.
  connect_indication.conninfo.value[1].attribute_val = new (std::nothrow) uint8_t[sizeof(intellivue::IpAddressInfo)]();
  REQUIRE(connect_indication.conninfo.value[1].attribute_val);
  intellivue::IpAddressInfo* attr_val2 = reinterpret_cast<intellivue::IpAddressInfo*>(
        connect_indication.conninfo.value[1].attribute_val);
  REQUIRE(attr_val2);

  //
  CHECK(IntellivueConnectIndicationMessage::GetIPAddressString(&ip_address, connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(ip_address == "0.0.0.0");

  // NOTE: value array has size 4 in data type definition for IpAddressInfo
  attr_val2->ip_address.value[0] = 0;
  attr_val2->ip_address.value[1] = 2;
  attr_val2->ip_address.value[2] = 3;
  attr_val2->ip_address.value[3] = 0xFF;

  CHECK(IntellivueConnectIndicationMessage::GetIPAddressString(&ip_address, connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(ip_address == "0.2.3.255");

  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);

  return DicesRcUnitTest::OK;
}

DicesRcUnitTest IntellivueConnectIndicationMessageUnitTest::GetDataExportProtocolPortNumber()
{
  int port_number = 0;
  ConnectIndication connect_indication = {0};

  // Tests null pointer funtion argument.
  CHECK(IntellivueConnectIndicationMessage::GetDataExportProtocolPortNumber(nullptr, connect_indication)
        == DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE);

  // Test will succeed, but since attribute list count is zero there's
  // no ip address found.
  CHECK(IntellivueConnectIndicationMessage::GetDataExportProtocolPortNumber(&port_number, connect_indication)
        == DicesRcPhilipsIntellivueMP70::GET_DATA_EXPORT_PORT_NUMBER_FAILURE);

  // Tests loop entered but null pointer for AVAType list. Function
  // Should return failure because IP address was not found.
  const int kattr_list_count = 2;
  connect_indication.conninfo.count = kattr_list_count;
  CHECK(IntellivueConnectIndicationMessage::GetDataExportProtocolPortNumber(&port_number, connect_indication)
        == DicesRcPhilipsIntellivueMP70::GET_DATA_EXPORT_PORT_NUMBER_FAILURE);

  // Allocate attributes. One attribute will be unknown, and the other will be
  // the production specification. The attribute_val pointers will be null.
  // Function should return failure because the IP address was not found.
  connect_indication.conninfo.value = new (std::nothrow) intellivue::AVAType[kattr_list_count]();
  REQUIRE(connect_indication.conninfo.value);
  REQUIRE(kattr_list_count > 1);
  connect_indication.conninfo.value[0].attribute_id = 0;
  connect_indication.conninfo.value[1].attribute_id = NOM_ATTR_PCOL_SUPPORT;

  // Tests AVATypes with null pointer attribute_val
  CHECK(IntellivueConnectIndicationMessage::GetDataExportProtocolPortNumber(&port_number, connect_indication)
        == DicesRcPhilipsIntellivueMP70::GET_DATA_EXPORT_PORT_NUMBER_FAILURE);

  // Allocate attribute_val for the second attribute. Function should
  // return success with ip address string set.
  connect_indication.conninfo.value[1].attribute_val = new (std::nothrow) uint8_t[sizeof(intellivue::ProtoSupport)]();
  REQUIRE(connect_indication.conninfo.value[1].attribute_val);
  intellivue::ProtoSupport* attr_val = reinterpret_cast<intellivue::ProtoSupport*>(
        connect_indication.conninfo.value[1].attribute_val);
  REQUIRE(attr_val);

  CHECK(IntellivueConnectIndicationMessage::GetDataExportProtocolPortNumber(&port_number, connect_indication)
        == DicesRcPhilipsIntellivueMP70::GET_DATA_EXPORT_PORT_NUMBER_FAILURE);
  CHECK(port_number == 0);

  const int kproto_count = 2;
  attr_val->count = kproto_count;

  CHECK(IntellivueConnectIndicationMessage::GetDataExportProtocolPortNumber(&port_number, connect_indication)
        == DicesRcPhilipsIntellivueMP70::GET_DATA_EXPORT_PORT_NUMBER_FAILURE);
  CHECK(port_number == 0);

  attr_val->value = new (std::nothrow) intellivue::ProtoSupportEntry[kproto_count]();
  REQUIRE(attr_val->value);
  REQUIRE(kproto_count > 1);
  attr_val->value[1].appl_proto = AP_ID_DATA_OUT;
  const int ktest_port_number = 5005;
  attr_val->value[1].port_number = ktest_port_number;

  CHECK(IntellivueConnectIndicationMessage::GetDataExportProtocolPortNumber(&port_number, connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);
  CHECK(port_number == ktest_port_number);

  REQUIRE(IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(&connect_indication)
        == DicesRcPhilipsIntellivueMP70::OK);

  return DicesRcUnitTest::OK;
}
