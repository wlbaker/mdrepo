/**
 * @file intellivue_set_rtsa_priority_list_request.h
 *
 * @brief Declares a class which creates a set rtsa priority list request.
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
#ifndef PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_SET_RTSA_PRIORITY_LIST_REQUEST_H_
#define PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_SET_RTSA_PRIORITY_LIST_REQUEST_H_

#include <cstdint>
#include <string>

enum class DicesRcPhilipsIntellivueMP70;

class IntellivueSetRTSAPriorityListRequest
{
 public:
  IntellivueSetRTSAPriorityListRequest();
  virtual ~IntellivueSetRTSAPriorityListRequest();

  /**
   * Create the set rtsa priority list request buffer.
   */
  static DicesRcPhilipsIntellivueMP70 CreateSetRTSAPriorityListRequest(
    uint8_t* set_rtsa_priority_list_request_buffer,
    unsigned int size_of_buffer,
    unsigned int* size_of_request);

 private:
  /// Disallow use of implicitly generated member functions:
  IntellivueSetRTSAPriorityListRequest(const IntellivueSetRTSAPriorityListRequest& src);
  IntellivueSetRTSAPriorityListRequest &operator=(const IntellivueSetRTSAPriorityListRequest& rhs);
};

#endif
