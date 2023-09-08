/**
 * @file intellivue_association_release_request_unit_test.h
 *
 * @brief Declares a unit test class for IntellivueAssociationReleaseRequest class.
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_TEST_SRC_INTELLIVUE_ASSOCIATION_RELEASE_REQUEST_UNIT_TEST_H_
#define PHILIPS_INTELLIVUE_MP70_TEST_SRC_INTELLIVUE_ASSOCIATION_RELEASE_REQUEST_UNIT_TEST_H_

#include "intellivue_association_release_request.h"

enum class DicesRcUnitTest;

class IntellivueAssociationReleaseRequestUnitTest
{
 public:
  IntellivueAssociationReleaseRequestUnitTest();
  ~IntellivueAssociationReleaseRequestUnitTest();

  DicesRcUnitTest RunTests();

 private:
  // Disallow use of implicitly generated member functions:
  IntellivueAssociationReleaseRequestUnitTest(const IntellivueAssociationReleaseRequestUnitTest &src);
  IntellivueAssociationReleaseRequestUnitTest &operator=(const IntellivueAssociationReleaseRequestUnitTest &rhs);

  DicesRcUnitTest CreateAssociationReleaseRequest();
};

#endif

