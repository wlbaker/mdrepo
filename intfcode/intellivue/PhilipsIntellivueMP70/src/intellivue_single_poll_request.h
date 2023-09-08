/**
 * @file intellivue_single_poll_request.h
 *
 * @brief Declares a class which creates a single poll request
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
#ifndef PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_SINGLE_POLL_REQUEST_H_
#define PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_SINGLE_POLL_REQUEST_H_

#include <cstdint>

enum class DicesRcPhilipsIntellivueMP70;

enum SinglePollRequestType
{
  SINGLE_MDS_REQUEST = 0,
  SINGLE_PATIENT_DEMOGRAPHICS_REQUEST
};

class IntellivueSinglePollRequest
{
 public:
  IntellivueSinglePollRequest();
  virtual ~IntellivueSinglePollRequest();

  static DicesRcPhilipsIntellivueMP70 CreateSinglePollRequest(
    uint8_t* single_poll_request_buffer,
    unsigned int size_of_buffer,
    unsigned int* size_of_request,
    SinglePollRequestType poll_type,
    uint16_t* poll_number);

 private:
  /// Disallow use of implicitly generated member functions:
  IntellivueSinglePollRequest(const IntellivueSinglePollRequest& src);
  IntellivueSinglePollRequest &operator=(const IntellivueSinglePollRequest& rhs);
};

#endif
