/**
 * @file intellivue_association_request_unit_test.h
 *
 * @brief Declares a unit test class for IntellivueAssociationRequest class.
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_TEST_SRC_INTELLIVUE_ASSOCIATION_REQUEST_UNIT_TEST_H_
#define PHILIPS_INTELLIVUE_MP70_TEST_SRC_INTELLIVUE_ASSOCIATION_REQUEST_UNIT_TEST_H_

#include "intellivue_association_request.h"

enum class DicesRcUnitTest;

class IntellivueAssociationRequestUnitTest
{
 public:
  IntellivueAssociationRequestUnitTest();
  ~IntellivueAssociationRequestUnitTest();

  DicesRcUnitTest RunTests();

 private:
  // Disallow use of implicitly generated member functions:
  IntellivueAssociationRequestUnitTest(const IntellivueAssociationRequestUnitTest &src);
  IntellivueAssociationRequestUnitTest &operator=(const IntellivueAssociationRequestUnitTest &rhs);

  DicesRcUnitTest CreateAssociationRequest();
};

#endif

