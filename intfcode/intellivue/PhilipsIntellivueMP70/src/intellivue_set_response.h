/**
 * @file intellivue_set_response.h
 *
 * @brief Declares class which parses set responses from intellivue
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_SET_RESPONSE_H_
#define PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_SET_RESPONSE_H_

#include <cstdint>
#include "dd_philips_intellivue_mp70_parser.h"

enum class DicesRcPhilipsIntellivueMP70;

class IntellivueSetResponse
{
 public:
  IntellivueSetResponse();
  virtual ~IntellivueSetResponse();

  static DicesRcPhilipsIntellivueMP70 IsSetResponse(
    bool* is_msg,
    uint8_t* buffer,
    unsigned int numbytes);

  static DicesRcPhilipsIntellivueMP70 ParseSetResponse(
    uint8_t* buffer,
    unsigned int numbytes);

 private:
  /// Disallow use of implicitly generated member functions:
  IntellivueSetResponse(const IntellivueSetResponse& src);
  IntellivueSetResponse &operator=(const IntellivueSetResponse& rhs);
};

#endif
