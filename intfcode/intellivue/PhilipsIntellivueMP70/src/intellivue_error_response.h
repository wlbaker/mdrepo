/**
 * @file intellivue_error_response.h
 *
 * @brief Declares class which parses error responses from intellivue
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_ERROR_RESPONSE_H_
#define PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_ERROR_RESPONSE_H_

#include <cstdint>
#include "dd_philips_intellivue_mp70_parser.h"

enum class DicesRcPhilipsIntellivueMP70;

class IntellivueErrorResponse
{
 public:
  IntellivueErrorResponse();
  virtual ~IntellivueErrorResponse();

  static DicesRcPhilipsIntellivueMP70 IsRemoteOperationErrorResponse(
    bool* is_msg,
    uint8_t* buffer,
    unsigned int numbytes);

  static DicesRcPhilipsIntellivueMP70 ParseRemoteOperationErrorResponse(
    uint8_t* buffer,
    unsigned int numbytes);

 private:
  /// Disallow use of implicitly generated member functions:
  IntellivueErrorResponse(const IntellivueErrorResponse& src);
  IntellivueErrorResponse &operator=(const IntellivueErrorResponse& rhs);
};

#endif
