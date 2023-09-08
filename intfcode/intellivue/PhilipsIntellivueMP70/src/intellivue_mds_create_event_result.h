/**
 * @file intellivue_mds_create_event_result.h
 *
 * @brief Declares a class which creates an MDS create event result message.
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_MDS_CREATE_EVENT_RESULT_H_
#define PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_MDS_CREATE_EVENT_RESULT_H_

#include <cstdint>
#include "dd_philips_intellivue_mp70_parser.h"

enum class DicesRcPhilipsIntellivueMP70;

class IntellivueMDSCreateEventResult
{
 public:

  static DicesRcPhilipsIntellivueMP70 CreateMDSCreateEventResult(
    uint8_t* mds_create_event_result,
    unsigned int size_of_buffer,
    unsigned int* size_of_request);

 private:
  // Disallow use of implicitly generated member functions:
  IntellivueMDSCreateEventResult(const IntellivueMDSCreateEventResult& src);
  IntellivueMDSCreateEventResult &operator=(const IntellivueMDSCreateEventResult& rhs);

  IntellivueMDSCreateEventResult();
  ~IntellivueMDSCreateEventResult();
};

#endif
