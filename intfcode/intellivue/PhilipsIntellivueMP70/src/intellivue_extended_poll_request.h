/**
 * @file intellivue_extended_poll_request.h
 *
 * @brief Declares a class which creates extended poll request
 *
 * Reference:
 * 		Data Export Interface Programming Guide
 * 		IntelliVue Patient Monitor
 * 		MP70
 *
 * 		Philips Reorder Part Number: 451261001426
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_EXTENDED_POLL_REQUEST_H_
#define PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_EXTENDED_POLL_REQUEST_H_

#include <cstdint>
#include <string>

enum class DicesRcPhilipsIntellivueMP70;

enum ExtendedPollRequestType
{
  EXTENDED_ALARM_STATIC_REQUEST = 0,
  EXTENDED_ALARM_REQUEST,
  EXTENDED_NUMERIC_STATIC_REQUEST,
  EXTENDED_NUMERIC_DYNAMIC_REQUEST,
  EXTENDED_NUMERIC_ALL_REQUEST,
  EXTENDED_WAVEFORM_STATIC_REQUEST,
  EXTENDED_WAVEFORM_DYNAMIC_REQUEST,
  EXTENDED_WAVEFORM_ALL_REQUEST,
  EXTENDED_ENUM_STATIC_REQUEST,
  EXTENDED_ENUM_DYNAMIC_REQUEST,
  EXTENDED_ENUM_ALL_REQUEST
};

class IntellivueExtendedPollRequest
{
 public:
  IntellivueExtendedPollRequest();
  virtual ~IntellivueExtendedPollRequest();

  static DicesRcPhilipsIntellivueMP70 CreateExtendedPollRequest(
    uint8_t* ext_poll_request_buffer,
    unsigned int size_of_buffer,
    unsigned int* size_of_request,
    ExtendedPollRequestType poll_type,
    unsigned int poll_period,
    uint16_t* poll_number);

 private:
  /// Disallow use of implicitly generated member functions:
  IntellivueExtendedPollRequest(const IntellivueExtendedPollRequest& src);
  IntellivueExtendedPollRequest &operator=(const IntellivueExtendedPollRequest& rhs);
};

#endif
