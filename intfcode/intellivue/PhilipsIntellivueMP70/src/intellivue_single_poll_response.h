/**
 * @file intellivue_single_poll_response.h
 *
 * @brief Declares class which parses single poll responses from intellivue
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_SINGLE_POLL_RESPONSE_H_
#define PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_SINGLE_POLL_RESPONSE_H_

#include <cstdint>
#include "dd_philips_intellivue_mp70_parser.h"

enum class DicesRcPhilipsIntellivueMP70;

class IntellivueSinglePollResponse
{
 public:
  IntellivueSinglePollResponse();
  virtual ~IntellivueSinglePollResponse();

  static DicesRcPhilipsIntellivueMP70 IsSinglePollResponse(
    bool* is_msg,
    uint8_t* buffer,
    unsigned int numbytes);

  static DicesRcPhilipsIntellivueMP70 ParseSinglePollResponse(
    SinglePollResponse* single_poll_response,
    uint8_t* buffer,
    unsigned int numbytes);

  static DicesRcPhilipsIntellivueMP70 DeleteSinglePollResponse(
    SinglePollResponse* single_poll_response);

 private:
  /// Disallow use of implicitly generated member functions:
  IntellivueSinglePollResponse(const IntellivueSinglePollResponse& src);
  IntellivueSinglePollResponse &operator=(const IntellivueSinglePollResponse& rhs);
};

#endif
