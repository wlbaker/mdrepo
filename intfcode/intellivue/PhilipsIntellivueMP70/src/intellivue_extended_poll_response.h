/**
 * @file intellivue_extended_poll_response.h
 *
 * @brief Declares class which parses extended poll responses from intellivue
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_EXTENDED_POLL_RESPONSE_H_
#define PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_EXTENDED_POLL_RESPONSE_H_

#include <cstdint>
#include "dd_philips_intellivue_mp70_parser.h"

enum class DicesRcPhilipsIntellivueMP70;

class IntellivueExtendedPollResponse
{
 public:
  IntellivueExtendedPollResponse();
  virtual ~IntellivueExtendedPollResponse();

  static DicesRcPhilipsIntellivueMP70 IsExtendedPollResponse(
    bool* is_msg,
    uint8_t* buffer,
    unsigned int numbytes);

  static DicesRcPhilipsIntellivueMP70 ParseExtendedPollResponse(
    ExtendedPollResponse* ext_poll_response,
    uint8_t* buffer,
    unsigned int numbytes);

  static DicesRcPhilipsIntellivueMP70 DeleteExtendedPollResponse(
    ExtendedPollResponse* ext_poll_response);

 private:
  /// Disallow use of implicitly generated member functions:
  IntellivueExtendedPollResponse(const IntellivueExtendedPollResponse& src);
  IntellivueExtendedPollResponse &operator=(const IntellivueExtendedPollResponse& rhs);
};

#endif
