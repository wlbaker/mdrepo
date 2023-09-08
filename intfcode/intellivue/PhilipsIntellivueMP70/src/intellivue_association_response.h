/**
 * @file intellivue_association_response.h
 *
 * @brief Declares class which parses association responses from intellivue
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_ASSOCIATION_RESPONSE_H_
#define PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_ASSOCIATION_RESPONSE_H_

#include <cstdint>
#include "dd_philips_intellivue_mp70_parser.h"

enum class DicesRcPhilipsIntellivueMP70;

class IntellivueAssociationResponse
{
 public:
  friend class IntellivueAssociationResponseUnitTest;

  IntellivueAssociationResponse();
  virtual ~IntellivueAssociationResponse();

  static DicesRcPhilipsIntellivueMP70 IsAssociationResponse(
    bool* is_msg,
    uint8_t* buffer,
    unsigned int numbytes);

  static DicesRcPhilipsIntellivueMP70 ParseAssociationResponse(
    AssociationResponse* association_response,
    uint8_t* buffer,
    unsigned int numbytes);

  static DicesRcPhilipsIntellivueMP70 DeleteAssociationResponse(
    AssociationResponse* association_response);

 private:
  /// Disallow use of implicitly generated member functions:
  IntellivueAssociationResponse(const IntellivueAssociationResponse& src);
  IntellivueAssociationResponse &operator=(const IntellivueAssociationResponse& rhs);

  static DicesRcPhilipsIntellivueMP70 FindAssociationResponseUserDataStart(
    int* iuserdataindex,
    uint8_t* buffer,
    int numbytes,
    int iindex);
};

#endif
