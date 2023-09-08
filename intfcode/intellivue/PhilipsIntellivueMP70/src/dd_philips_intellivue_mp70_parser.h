/**
 * @file dd_philips_intellivue_mp70_parser.h
 *
 * @breif Declares a class parser class for the Philips Intellivue.
 * 
 * @author Michael Szwaja
 * 
 */
//=============================================================================
#ifndef PHILIPS_INTELLIVUE_MP70_SRC_DD_PHILIPS_INTELLIVUE_MP70_PARSER_H_
#define PHILIPS_INTELLIVUE_MP70_SRC_DD_PHILIPS_INTELLIVUE_MP70_PARSER_H_

#include "parser.h"
#include "intellivue.h"
#include <chrono>
#include <tuple>

enum class DicesRcDriver;
enum class DicesRcPhilipsIntellivueMP70;

struct ConnectIndication
{
  intellivue::Nomenclature nomenclature;
  intellivue::ROapdus roapdus;
  intellivue::ROIVapdu roivapdu;
  intellivue::EventReportArgument eventreparg;
  intellivue::ConnectIndInfo conninfo;
};

struct AssociationResponse
{
  intellivue::SessionHeader sessionHeader;
  intellivue::SPpdu spdh;
  intellivue::MDSEUserInfoStd msdseUserInfo;
};

struct MDSCreateEventReport
{
  intellivue::SPpdu sppdu;
  intellivue::ROapdus roapdus;
  intellivue::ROIVapdu roivapdu;
  intellivue::EventReportArgument eventArg;
  intellivue::MdsCreateInfo createInfo;
};

struct ExtendedPollResponse
{
  intellivue::SPpdu sppdu;
  intellivue::ROapdus roapdus;
  intellivue::RORSapdu rorsapdu;
  intellivue::ROLRSapdu rolrs;
  intellivue::ActionResult actionresult;
  intellivue::PollMdibDataReplyExt pollReply;
};

struct SinglePollResponse
{
  intellivue::SPpdu sppdu;
  intellivue::ROapdus roapdus;
  intellivue::RORSapdu rorsapdu;
  intellivue::ROLRSapdu rolrs;
  intellivue::ActionResult actionresult;
  intellivue::PollMdibDataReply pollReply;
};

class DDPhilipsIntellivueMP70Parser : public Parser
{
 public:
  DDPhilipsIntellivueMP70Parser(int max_command_length, int max_response_length);
  ~DDPhilipsIntellivueMP70Parser();

  void set_is_serial_driver(bool torf);

  void set_database_name(const std::string& database_name);
  void set_database_user(const std::string& database_user);
  void set_database_password(const std::string& database_password);
  void set_database_host(const std::string& database_host);
  std::string get_database_name();
  std::string get_database_user();
  std::string get_database_password();
  std::string get_database_host();
  std::string get_intellivue_ip_address();
  int get_intellivue_data_export_port_number();

  DicesRcDriver PopulateDDSInstances();
  DicesRcDriver ParseCommand();
  DicesRcDriver ParseResponse();
  DicesRcDriver GetHandshakeCmd();
  DicesRcDriver ShutdownParser();

 private:
  // Disallow use of implicitly generated member functions:
  DDPhilipsIntellivueMP70Parser(const DDPhilipsIntellivueMP70Parser &src);
  DDPhilipsIntellivueMP70Parser &operator=(const DDPhilipsIntellivueMP70Parser &rhs);

  DicesRcPhilipsIntellivueMP70 GetAssociationRequest();
  DicesRcPhilipsIntellivueMP70 GetAssociationReleaseRequest();
  DicesRcPhilipsIntellivueMP70 SetExtendedPollResponseData();
  DicesRcPhilipsIntellivueMP70 SetSinglePollResponseData();
  DicesRcPhilipsIntellivueMP70 GenerateNewHandle(
    intellivue::Handle* new_handle);
  DicesRcPhilipsIntellivueMP70 SetExtendedNumericResponseData();
  DicesRcPhilipsIntellivueMP70 SetExtendedRTSAResponseData();
  DicesRcPhilipsIntellivueMP70 SetExtendedEnumResponseData();
  DicesRcPhilipsIntellivueMP70 SetExtendedAlarmResponseData();
  DicesRcPhilipsIntellivueMP70 SetSingleMDSResponseData();
  DicesRcPhilipsIntellivueMP70 SetSinglePatientDemographicsResponseData();

  DicesRcPhilipsIntellivueMP70 SetExtendedRTSAMapping();

  bool _connect_indication_msg_received;
  bool _association_release_request_sent;
  bool _association_release_request_sent_lan;
  bool _association_response_msg_received;
  bool _association_refuse_msg_received;
  bool _mds_create_event_report_received;
  bool _is_serial_driver;
  bool _port_reconfigured;
  std::string _database_name;
  std::string _database_user;
  std::string _database_password;
  std::string _database_host;
  std::string _intellivue_ip_address;
  int _intellivue_data_export_port_number;
  DicesRcDriver _handshake_status;

  ConnectIndication _connect_indication;
  AssociationResponse _association_response;
  MDSCreateEventReport _mds_create_event_report;
  ExtendedPollResponse _extended_poll_response;
  SinglePollResponse _single_poll_response;

  std::chrono::time_point < std::chrono::system_clock > _target_time;
  std::map<
  std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
  unsigned int>
  _map_handle_to_mds_instance;
  std::map<
    std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
    unsigned int>
  _map_handle_to_vmd_instance;
  std::map<
  std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
  unsigned int>
  _map_handle_to_pat_demo_instance;
  std::map<
  std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
  unsigned int>
  _map_handle_to_pat_ident_instance;
  std::map<
  std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
  std::map<intellivue::Handle, unsigned int>>
  _map_handle_to_numeric_instance;
  std::map<
  std::tuple<
  intellivue::MdsContext, // See intellivue GlbHandle
  intellivue::Handle, // See intellivue GlbHandle
  intellivue::MdsContext, // See intellivue SingleContextPoll
  intellivue::Handle, // See ObservationPoll obj_handle
  intellivue::OIDType, // See SaObsValue and SaObsValueCmp physio_id
  uint16_t // Array size
  >,
  std::map<
  intellivue::Handle, // Unique handle generated by driver.
  unsigned int // Vector index
  >>
  _map_handle_to_rtsa_instance;
  std::map<
  std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
  std::map<intellivue::Handle, unsigned int>>
  _map_handle_to_enumeration_instance;
  std::map<intellivue::OIDType, unsigned int> _map_al_source_to_tech_alarm_instance;
  std::map<intellivue::OIDType, unsigned int> _map_al_source_to_phys_alarm_instance;
  unsigned int _mds_vector_max_index;
  unsigned int _vmd_vector_max_index;
  unsigned int _pat_demo_vector_max_index;
  unsigned int _pat_ident_vector_max_index;
  unsigned int _numeric_vector_max_index;
  unsigned int _rtsa_vector_max_index;
  unsigned int _enumeration_vector_max_index;
  unsigned int _tech_alarm_vector_max_index;
  unsigned int _phys_alarm_vector_max_index;
};

#endif
