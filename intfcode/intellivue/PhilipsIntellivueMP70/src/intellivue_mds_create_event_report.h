/**
 * @file intellivue_mds_create_event_report.h
 *
 * @brief Declares a class which parses MDS create event report response.
 *
 * @author M Szwaja
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_MDS_CREATE_EVENT_REPORT_H_
#define PHILIPS_INTELLIVUE_MP70_SRC_INTELLIVUE_MDS_CREATE_EVENT_REPORT_H_

#include <cstdint>
#include "dd_philips_intellivue_mp70_parser.h"

enum class DicesRcPhilipsIntellivueMP70;

class IntellivueMDSCreateEventReport
{
 public:

  static DicesRcPhilipsIntellivueMP70 IsMDSCreateEventReport(
    bool* is_msg,
    uint8_t* buffer,
    unsigned int numbytes);

  static DicesRcPhilipsIntellivueMP70 ParseMDSCreateEventReport(
    MDSCreateEventReport* mds_create_event_report,
    uint8_t* buffer,
    unsigned int numbytes);

  static DicesRcPhilipsIntellivueMP70 DeleteMDSCreateEventReport(
    MDSCreateEventReport* mds_create_event_report);

  static DicesRcPhilipsIntellivueMP70 SetMDSWithMDSCreateEventReport(
    std::pair<DicesRcDriver, ice::MDS*>* instance_pair,
    const MDSCreateEventReport& mds_create_event_report);

  static DicesRcPhilipsIntellivueMP70 SetVMDWithMDSCreateEventReport(
    std::pair<DicesRcDriver, ice::VMD*>* instance_pair,
    const MDSCreateEventReport& mds_create_event_report);

 private:
  // Disallow use of implicitly generated member functions:
  IntellivueMDSCreateEventReport(const IntellivueMDSCreateEventReport& src);
  IntellivueMDSCreateEventReport &operator=(const IntellivueMDSCreateEventReport& rhs);

  IntellivueMDSCreateEventReport();
  ~IntellivueMDSCreateEventReport();
};

#endif
