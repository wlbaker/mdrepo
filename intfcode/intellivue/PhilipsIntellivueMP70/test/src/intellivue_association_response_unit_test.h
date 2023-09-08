/**
 * @file intellivue_association_response_unit_test.h
 *
 * @brief Declares a unit test class for IntellivueAssociationResponse class.
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_TEST_SRC_INTELLIVUE_ASSOCIATION_RESPONSE_UNIT_TEST_H_
#define PHILIPS_INTELLIVUE_MP70_TEST_SRC_INTELLIVUE_ASSOCIATION_RESPONSE_UNIT_TEST_H_

#include "intellivue_association_response.h"

enum class DicesRcUnitTest;

class IntellivueAssociationResponseUnitTest
{
 public:
  IntellivueAssociationResponseUnitTest();
  ~IntellivueAssociationResponseUnitTest();

  DicesRcUnitTest RunTests();

 private:
  // Disallow use of implicitly generated member functions:
  IntellivueAssociationResponseUnitTest(const IntellivueAssociationResponseUnitTest &src);
  IntellivueAssociationResponseUnitTest &operator=(const IntellivueAssociationResponseUnitTest &rhs);

  DicesRcUnitTest IsAssociationResponse();
  DicesRcUnitTest ParseAssociationResponse();
  DicesRcUnitTest DeleteAssociationResponse();
  DicesRcUnitTest FindAssociationResponseUserDataStart();
};

#endif

