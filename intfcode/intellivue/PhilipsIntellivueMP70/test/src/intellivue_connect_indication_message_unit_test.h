/**
 * @file intellivue_connect_indication_message_unit_test.h
 *
 * @brief Declares a unit test class for IntellivueConnectIndicationMessage class.
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_TEST_SRC_INTELLIVUE_CONNECT_INDICATION_MESSAGE_UNIT_TEST_H_
#define PHILIPS_INTELLIVUE_MP70_TEST_SRC_INTELLIVUE_CONNECT_INDICATION_MESSAGE_UNIT_TEST_H_

#include "intellivue_connect_indication_message.h"

enum class DicesRcUnitTest;

class IntellivueConnectIndicationMessageUnitTest
{
 public:
  IntellivueConnectIndicationMessageUnitTest();
  ~IntellivueConnectIndicationMessageUnitTest();

  DicesRcUnitTest RunTests();

 private:
  // Disallow use of implicitly generated member functions:
  IntellivueConnectIndicationMessageUnitTest(const IntellivueConnectIndicationMessageUnitTest &src);
  IntellivueConnectIndicationMessageUnitTest &operator=(const IntellivueConnectIndicationMessageUnitTest &rhs);

  DicesRcUnitTest IsConnectIndicationMessage();
  DicesRcUnitTest ParseConnectIndicationMessage();
  DicesRcUnitTest DeleteConnectIndicationMessage();
  DicesRcUnitTest SetMDSWithConnectIndicationMessage();
  DicesRcUnitTest GetIPAddressString();
  DicesRcUnitTest GetDataExportProtocolPortNumber();
};

#endif
