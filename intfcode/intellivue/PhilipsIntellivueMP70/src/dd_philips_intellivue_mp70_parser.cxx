#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <ndds/ndds_namespace_cpp.h>
#include <climits>
#include <thread>
#include <chrono>
#include "mds.h"
#include "mdsSupport.h"
#include "vmd.h"
#include "vmdSupport.h"
#include "numeric.h"
#include "numericSupport.h"
#include "rtsa.h"
#include "rtsaSupport.h"
#include "enum.h"
#include "enumSupport.h"
#include "alarm.h"
#include "alarmSupport.h"
#include "patdemo.h"
#include "patdemoSupport.h"
#include "docboxSupport.h"
#include "parser.h"
#include "dices_rc_driver.h"
#include "dd_philips_intellivue_mp70_parser.h"
#include "intellivue_association_request.h"
#include "intellivue_association_release_request.h"
#include "intellivue_extended_poll_request.h"
#include "intellivue_single_poll_request.h"
#include "intellivue_single_poll_response.h"
#include "intellivue_set_rtsa_priority_list_request.h"
#include "intellivue_extended_poll_response.h"
#include "intellivue_association_response.h"
#include "intellivue_error_response.h"
#include "intellivue_set_response.h"
#include "intellivue_connect_indication_message.h"
#include "intellivue_mds_create_event_result.h"
#include "intellivue_mds_create_event_report.h"
#include "serial_converter.h"
#include "PhilipsIntellivueMP70ReturnCodes.h"
#include "intellivue_utils.h"
#include "Core/Time/dices-time.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();
static log4cplus::Logger cmd_logger = log4cplus::Logger::getInstance("cmdlogger");
static log4cplus::Logger raw_logger = log4cplus::Logger::getInstance("rawlogger");

DDPhilipsIntellivueMP70Parser::DDPhilipsIntellivueMP70Parser(
  int max_command_length,
  int max_response_length)
  : Parser(max_command_length, max_response_length),
  _handshake_status(DicesRcDriver::OK),
  _connect_indication_msg_received(false),
  _association_release_request_sent(false),
  _association_release_request_sent_lan(false),
  _association_response_msg_received(false),
  _association_refuse_msg_received(false),
  _mds_create_event_report_received(false),
  _port_reconfigured(false),
  _intellivue_data_export_port_number(0),
  _mds_vector_max_index(0),
  _vmd_vector_max_index(0),
  _pat_demo_vector_max_index(0),
  _pat_ident_vector_max_index(0),
  _numeric_vector_max_index(0),
  _rtsa_vector_max_index(0),
  _enumeration_vector_max_index(0),
  _tech_alarm_vector_max_index(0),
  _phys_alarm_vector_max_index(0)
{
  _connect_indication = { 0 };
  _association_response = { 0 };
  _mds_create_event_report = { 0 };
  _extended_poll_response = { 0 };
  _single_poll_response = { 0 };
  _target_time = std::chrono::system_clock::now();

  try
  {
    _create_writer_name_list.insert(CreateWriterName::DeviceDriverStateWriter);
    _create_writer_name_list.insert(CreateWriterName::PatientIdentificationReqWriter);
    _create_writer_name_list.insert(CreateWriterName::PatientDemographicsReqWriter);
    _create_writer_name_list.insert(CreateWriterName::PhysiologicalAlarmSignalWriter);
    _create_writer_name_list.insert(CreateWriterName::TechnicalAlarmSignalWriter);
    _create_writer_name_list.insert(CreateWriterName::InformationSignalWriter);
    _create_writer_name_list.insert(CreateWriterName::ReminderSignalWriter);
    _create_writer_name_list.insert(CreateWriterName::PhysiologicalAlarmContextWriter);
    _create_writer_name_list.insert(CreateWriterName::TechnicalAlarmContextWriter);
    _create_writer_name_list.insert(CreateWriterName::DSAMeasContextWriter);
    _create_writer_name_list.insert(CreateWriterName::DSAMeasObservedValueWriter);
    _create_writer_name_list.insert(CreateWriterName::DSACalcContextWriter);
    _create_writer_name_list.insert(CreateWriterName::DSACalcObservedValueWriter);
    _create_writer_name_list.insert(CreateWriterName::DSASettContextWriter);
    _create_writer_name_list.insert(CreateWriterName::DSASettObservedValueWriter);
    _create_writer_name_list.insert(CreateWriterName::EnumerationMeasContextWriter);
    _create_writer_name_list.insert(CreateWriterName::EnumerationMeasObservedValueWriter);
    _create_writer_name_list.insert(CreateWriterName::EnumerationCalcContextWriter);
    _create_writer_name_list.insert(CreateWriterName::EnumerationCalcObservedValueWriter);
    _create_writer_name_list.insert(CreateWriterName::EnumerationSettContextWriter);
    _create_writer_name_list.insert(CreateWriterName::EnumerationSettObservedValueWriter);
    _create_writer_name_list.insert(CreateWriterName::MDSWriter);
    _create_writer_name_list.insert(CreateWriterName::VMDWriter);
    _create_writer_name_list.insert(CreateWriterName::NumericMeasContextWriter);
    _create_writer_name_list.insert(CreateWriterName::NumericMeasObservedValueWriter);
    _create_writer_name_list.insert(CreateWriterName::NumericCalcContextWriter);
    _create_writer_name_list.insert(CreateWriterName::NumericCalcObservedValueWriter);
    _create_writer_name_list.insert(CreateWriterName::NumericSettContextWriter);
    _create_writer_name_list.insert(CreateWriterName::NumericSettObservedValueWriter);
    _create_writer_name_list.insert(CreateWriterName::RTSAMeasContextWriter);
    _create_writer_name_list.insert(CreateWriterName::RTSAMeasObservedValueWriter);
    _create_writer_name_list.insert(CreateWriterName::RTSACalcContextWriter);
    _create_writer_name_list.insert(CreateWriterName::RTSACalcObservedValueWriter);
    _create_writer_name_list.insert(CreateWriterName::RTSASettContextWriter);
    _create_writer_name_list.insert(CreateWriterName::RTSASettObservedValueWriter);
    _create_writer_name_list.insert(CreateWriterName::TSAMeasContextWriter);
    _create_writer_name_list.insert(CreateWriterName::TSAMeasObservedValueWriter);
    _create_writer_name_list.insert(CreateWriterName::TSACalcContextWriter);
    _create_writer_name_list.insert(CreateWriterName::TSACalcObservedValueWriter);
    _create_writer_name_list.insert(CreateWriterName::TSASettContextWriter);
    _create_writer_name_list.insert(CreateWriterName::TSASettObservedValueWriter);
    _create_writer_name_list.insert(CreateWriterName::PatientIdentificationWriter);
    _create_writer_name_list.insert(CreateWriterName::PatientDemographicsWriter);
    _create_writer_name_list.insert(CreateWriterName::AllergyWriter);
    _create_writer_name_list.insert(CreateWriterName::DiagnosisWriter);
    _create_writer_name_list.insert(CreateWriterName::DxHistoryWriter);
    _create_writer_name_list.insert(CreateWriterName::PatientMedicationWriter);
  }
  catch(std::exception& ex)
  {
    LOG4CPLUS_ERROR(root_logger, " Failed to insert create writer names. "
      << ex.what());
    return;
  }

  try
  {
    _create_reader_name_list.insert(CreateReaderName::PatientDemographicsReqReaderCft);
    _create_reader_name_list.insert(CreateReaderName::PhysiologicalAlarmContextReqReaderCft);
    _create_reader_name_list.insert(CreateReaderName::TechnicalAlarmContextReqReaderCft);
    _create_reader_name_list.insert(CreateReaderName::DSAMeasContextReqReaderCft);
    _create_reader_name_list.insert(CreateReaderName::DSACalcContextReqReaderCft);
    _create_reader_name_list.insert(CreateReaderName::DSASettContextReqReaderCft);
    _create_reader_name_list.insert(CreateReaderName::EnumerationMeasContextReqReaderCft);
    _create_reader_name_list.insert(CreateReaderName::EnumerationCalcContextReqReaderCft);
    _create_reader_name_list.insert(CreateReaderName::EnumerationSettContextReqReaderCft);
    _create_reader_name_list.insert(CreateReaderName::EnumerationSettObservedValueReqReaderCft);
    _create_reader_name_list.insert(CreateReaderName::NumericMeasContextReqReaderCft);
    _create_reader_name_list.insert(CreateReaderName::NumericCalcContextReqReaderCft);
    _create_reader_name_list.insert(CreateReaderName::NumericSettContextReqReaderCft);
    _create_reader_name_list.insert(CreateReaderName::NumericSettObservedValueReqReaderCft);
    _create_reader_name_list.insert(CreateReaderName::RTSAMeasContextReqReaderCft);
    _create_reader_name_list.insert(CreateReaderName::RTSACalcContextReqReaderCft);
    _create_reader_name_list.insert(CreateReaderName::RTSASettContextReqReaderCft);
    _create_reader_name_list.insert(CreateReaderName::TSAMeasContextReqReaderCft);
    _create_reader_name_list.insert(CreateReaderName::TSACalcContextReqReaderCft);
    _create_reader_name_list.insert(CreateReaderName::TSASettContextReqReaderCft);
    _create_reader_name_list.insert(CreateReaderName::PatientIdentificationReqReader);
    _create_reader_name_list.insert(CreateReaderName::DeviceDriverStateReqReaderCft);
  }
  catch(std::exception& ex)
  {
    LOG4CPLUS_ERROR(root_logger, " Failed to insert create reader names. "
      << ex.what());
    return;
  }
}

DDPhilipsIntellivueMP70Parser::~DDPhilipsIntellivueMP70Parser() { }

void DDPhilipsIntellivueMP70Parser::set_is_serial_driver(bool torf)
{
  _is_serial_driver = torf;
}

void DDPhilipsIntellivueMP70Parser::set_database_name(
  const std::string& database_name)
{
  _database_name = database_name;
}

void DDPhilipsIntellivueMP70Parser::set_database_user(
  const std::string& database_user)
{
  _database_user = database_user;
}

void DDPhilipsIntellivueMP70Parser::set_database_password(
  const std::string& database_password)
{
  _database_password = database_password;
}

void DDPhilipsIntellivueMP70Parser::set_database_host(
  const std::string& database_host)
{
  _database_host = database_host;
}

std::string DDPhilipsIntellivueMP70Parser::get_database_name()
{
  return _database_name;
}

std::string DDPhilipsIntellivueMP70Parser::get_database_user()
{
  return _database_user;
}

std::string DDPhilipsIntellivueMP70Parser::get_database_password()
{
  return _database_password;
}

std::string DDPhilipsIntellivueMP70Parser::get_database_host()
{
  return _database_host;
}

std::string DDPhilipsIntellivueMP70Parser::get_intellivue_ip_address()
{
  return _intellivue_ip_address;
}

int DDPhilipsIntellivueMP70Parser::get_intellivue_data_export_port_number()
{
  return _intellivue_data_export_port_number;
}

DicesRcDriver DDPhilipsIntellivueMP70Parser::PopulateDDSInstances()
{
  static const char* sfn = "DDPhilipsIntellivueMP70Parser::PopulateDDSInstances() ";
  DicesRcDriver status = ConnectToDatabase(
    _database_name,
    _database_user,
    _database_password,
    _database_host);
  if (status != DicesRcDriver::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn <<
      DicesRcDriverStatusMessage::DicesRcDriverToString(status));
    return status;
  }

  status = ReadFromDatabase();
  if (status != DicesRcDriver::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn <<
      DicesRcDriverStatusMessage::DicesRcDriverToString(status));
    return status;
  }

  status = DisconnectFromDatabase();
  if (status != DicesRcDriver::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn <<
      DicesRcDriverStatusMessage::DicesRcDriverToString(status));
    return status;
  }

  // All instances read from the database above are set to publish with
  // DicesRcDriver::OK. This is not desired for the intellivue driver because
  // the instances are just empty place holders, intended to be populated by
  // Intellivue response data. Setting all instances to
  // DicesRcDriver::NO_NEW_DATA.
  for (int ix = 0; ix < _mds_instance_list.size(); ix++)
  {
    _mds_instance_list.at(ix).first = DicesRcDriver::NO_NEW_DATA;
  }
  for (int ix = 0; ix < _vmd_instance_list.size(); ix++)
  {
    _vmd_instance_list.at(ix).first = DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _numeric_meas_context_response_instance_list.size();
    ix++)
  {
    _numeric_meas_context_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _numeric_calc_context_response_instance_list.size();
    ix++)
  {
    _numeric_calc_context_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _numeric_sett_context_response_instance_list.size();
    ix++)
  {
    _numeric_sett_context_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _numeric_meas_observed_value_response_instance_list.size();
    ix++)
  {
    _numeric_meas_observed_value_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _numeric_calc_observed_value_response_instance_list.size();
    ix++)
  {
    _numeric_calc_observed_value_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _numeric_sett_observed_value_response_instance_list.size();
    ix++)
  {
    _numeric_sett_observed_value_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _rtsa_meas_context_response_instance_list.size();
    ix++)
  {
    _rtsa_meas_context_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _rtsa_calc_context_response_instance_list.size();
    ix++)
  {
    _rtsa_calc_context_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _rtsa_sett_context_response_instance_list.size();
    ix++)
  {
    _rtsa_sett_context_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _rtsa_meas_observed_value_response_instance_list.size();
    ix++)
  {
    _rtsa_meas_observed_value_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _rtsa_calc_observed_value_response_instance_list.size();
    ix++)
  {
    _rtsa_calc_observed_value_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _rtsa_sett_observed_value_response_instance_list.size();
    ix++)
  {
    _rtsa_sett_observed_value_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _enumeration_meas_context_response_instance_list.size();
    ix++)
  {
    _enumeration_meas_context_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _enumeration_calc_context_response_instance_list.size();
    ix++)
  {
    _enumeration_calc_context_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _enumeration_sett_context_response_instance_list.size();
    ix++)
  {
    _enumeration_sett_context_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _enumeration_meas_observed_value_response_instance_list.size();
    ix++)
  {
    _enumeration_meas_observed_value_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _enumeration_calc_observed_value_response_instance_list.size();
    ix++)
  {
    _enumeration_calc_observed_value_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _enumeration_sett_observed_value_response_instance_list.size();
    ix++)
  {
    _enumeration_sett_observed_value_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _physiological_alarm_context_response_instance_list.size();
    ix++)
  {
    _physiological_alarm_context_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _technical_alarm_context_response_instance_list.size();
    ix++)
  {
    _technical_alarm_context_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _physiological_alarm_signal_response_instance_list.size();
    ix++)
  {
    _physiological_alarm_signal_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _technical_alarm_signal_response_instance_list.size();
    ix++)
  {
    _technical_alarm_signal_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _patient_identification_req_response_instance_list.size();
    ix++)
  {
    _patient_identification_req_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  for (
    int ix = 0;
    ix < _patient_demographics_req_response_instance_list.size();
    ix++)
  {
    _patient_demographics_req_response_instance_list.at(ix).first =
      DicesRcDriver::NO_NEW_DATA;
  }
  return status;
}

DicesRcDriver DDPhilipsIntellivueMP70Parser::ParseCommand()
{
  static const char* sfn = "DDPhilipsIntellivueMP70Parser::ParseCommand() ";
  DicesRcPhilipsIntellivueMP70 status = DicesRcPhilipsIntellivueMP70::OK;
  unsigned int isize = 0;
  const unsigned int krelative_time_65sec = 0x80000;
  const unsigned int krelative_time_1sec = 0x1F40;
  // 0x80000 = 524288, 524288 / (8 * 1000) = 65 seconds
  unsigned int poll_period = krelative_time_65sec;
  static uint16_t poll_number = 0;
  std::chrono::time_point < std::chrono::system_clock > current_time;
  const std::chrono::milliseconds dura(2000); // 2 seconds
  SerialConverter serial_converter;
  static bool first_time_set_rtsa_priority_list = true;
  static const int kmax_ext_arr_size = 7;
  static const int kext_non_static_pos_start = 3;
  static const ExtendedPollRequestType ext_arr[kmax_ext_arr_size] = {
    ExtendedPollRequestType::EXTENDED_NUMERIC_STATIC_REQUEST,
    ExtendedPollRequestType::EXTENDED_WAVEFORM_STATIC_REQUEST,
    ExtendedPollRequestType::EXTENDED_ENUM_STATIC_REQUEST,
    ExtendedPollRequestType::EXTENDED_NUMERIC_ALL_REQUEST,
    ExtendedPollRequestType::EXTENDED_WAVEFORM_ALL_REQUEST,
    ExtendedPollRequestType::EXTENDED_ENUM_ALL_REQUEST,
    ExtendedPollRequestType::EXTENDED_ALARM_REQUEST
  };
  static int ext_index = 0;
  static const int kmax_single_arr_size = 2;
  static const SinglePollRequestType single_arr[kmax_single_arr_size] = {
    SinglePollRequestType::SINGLE_MDS_REQUEST,
    SinglePollRequestType::SINGLE_PATIENT_DEMOGRAPHICS_REQUEST
  };
  static int single_index = 0;

  memset(_raw_command, 0, _max_command_length);
  _command_length = 0;

  // Avoid overflow
  if (poll_number == USHRT_MAX)
  {
    poll_number = 0;
  }

  current_time = std::chrono::system_clock::now();

  if (_mds_create_event_report_received)
  {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    LOG4CPLUS_INFO(root_logger, sfn << "Creating MDS create event result");
    status = IntellivueMDSCreateEventResult::CreateMDSCreateEventResult(
      _raw_command,
      _max_command_length,
      reinterpret_cast<unsigned int*>(&_command_length));
    if (status != DicesRcPhilipsIntellivueMP70::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn <<
        DicesRcPhilipsIntellivueMP70StatusMessage::
        DicesRcPhilipsIntellivueMP70ToString(status));
      return DicesRcDriver::FAIL;
    }
    // Reset flag in case intellivue sends another mds create event report.
    _mds_create_event_report_received = false;

    if (_is_serial_driver)
    {
      status = serial_converter.ConstructSerialMsg(
        _raw_command,
        _max_command_length,
        reinterpret_cast<unsigned int*>(&_command_length));
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL;
      }
    }

    // First, store the data to log file.
    if (_command_length > 0)
    {
      std::string log_message;
      for (int ix = 0; ix < _command_length; ix++)
      {
        log_message += _raw_command[ix];
      }
      // No function name because we are logging the data exactly as it's
      // sent to the attached device. See log4cplus properties file for
      // additional configuration settings.
      LOG4CPLUS_INFO(cmd_logger, log_message);
    }

    return DicesRcDriver::OK;
  }

  // Check to see if driver has been requested to shutdown.
  for (
    int ix = 0;
    ix < _device_driver_state_req_command_instance_list.size();
    ix++)
  {
    if (_device_driver_state_req_command_instance_list.at(ix).second->
      driver_status == docbox::DriverStatus::shutdown)
    {
      LOG4CPLUS_INFO(root_logger, sfn << "Creating association release "
        "request");
      // Attempt to release association with intellivue.
      status = GetAssociationReleaseRequest();
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL;
      }
      // First, store the data to log file.
      if (_command_length > 0)
      {
        std::string log_message;
        for (int ix = 0; ix < _command_length; ix++)
        {
          log_message += _raw_command[ix];
        }
        // No function name because we are logging the data exactly as it's
        // sent to the attached device. See log4cplus properties file for
        // additional configuration settings.
        LOG4CPLUS_INFO(cmd_logger, log_message);
      }
      return DicesRcDriver::OK;
    }
  }

  // Clear device driver state request vector because there weren't any
  // with shutdown state
  while (!_device_driver_state_req_command_instance_list.empty())
  {
    DDS::ReturnCode_t retcode = docbox::DeviceDriverStateTypeSupport::
      delete_data(_device_driver_state_req_command_instance_list.back().
      second);
    if (retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to delete "
        "docbox::DeviceDriverState instance");
      return DicesRcDriver::DEVICE_DRIVER_STATE_INSTANCE_DELETE_FAILURE;
    }
    _device_driver_state_req_command_instance_list.pop_back();
  }

  if (first_time_set_rtsa_priority_list)
  {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    LOG4CPLUS_INFO(root_logger, sfn << "Creating RTSA set priority list "
      "request");
    status = IntellivueSetRTSAPriorityListRequest::CreateSetRTSAPriorityListRequest(
      _raw_command,
      _max_command_length,
      reinterpret_cast<unsigned int*>(&_command_length));
    if (status != DicesRcPhilipsIntellivueMP70::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn <<
        DicesRcPhilipsIntellivueMP70StatusMessage::
        DicesRcPhilipsIntellivueMP70ToString(status));
      return DicesRcDriver::FAIL;
    }
    first_time_set_rtsa_priority_list = false;

    if (_is_serial_driver)
    {
      status = serial_converter.ConstructSerialMsg(
        _raw_command,
        _max_command_length,
        reinterpret_cast<unsigned int*>(&_command_length));
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL;
      }
    }

    // First, store the data to log file.
    if (_command_length > 0)
    {
      std::string log_message;
      for (int ix = 0; ix < _command_length; ix++)
      {
        log_message += _raw_command[ix];
      }
      // No function name because we are logging the data exactly as it's
      // sent to the attached device. See log4cplus properties file for
      // additional configuration settings.
      LOG4CPLUS_INFO(cmd_logger, log_message);
    }

    // Calculate next time
    _target_time = current_time + dura;
    return DicesRcDriver::OK;
  }

  if (current_time > _target_time)
  {
    static bool is_single_poll_turn = false;
    if (!is_single_poll_turn)
    {
      LOG4CPLUS_INFO(root_logger, sfn << "Creating extended poll "
        "request ExtendedPollRequestType: " << static_cast<int>(
        ext_arr[ext_index]));

      if (ext_index < kext_non_static_pos_start)
      {
        poll_period = krelative_time_1sec;
      }
      else
      {
        poll_period = krelative_time_65sec;
      }

      status = IntellivueExtendedPollRequest::CreateExtendedPollRequest(
        _raw_command,
        _max_command_length,
        reinterpret_cast<unsigned int*>(&_command_length),
        ext_arr[ext_index],
        poll_period,
        &poll_number);
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        ext_index++;
        if (ext_index >= kmax_ext_arr_size)
        {
          ext_index = kext_non_static_pos_start;
          is_single_poll_turn = true;
        }
        return DicesRcDriver::FAIL;
      }
      else
      {
        // Calculate next time
        _target_time = current_time + dura;
      }
      poll_number++;
      ext_index++;
      if (ext_index >= kmax_ext_arr_size)
      {
        ext_index = kext_non_static_pos_start;
        is_single_poll_turn = true;
      }
    }
    else
    {
      LOG4CPLUS_INFO(root_logger, sfn << "Creating single poll "
        "request SinglePollRequestType: " << static_cast<int>(
        single_arr[single_index]));
      status = IntellivueSinglePollRequest::CreateSinglePollRequest(
        _raw_command,
        _max_command_length,
        reinterpret_cast<unsigned int*>(&_command_length),
        single_arr[single_index],
        &poll_number);
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        single_index++;
        if (single_index >= kmax_single_arr_size)
        {
          single_index = 0;
          is_single_poll_turn = false;
        }
        return DicesRcDriver::FAIL;
      }
      else
      {
        // Calculate next time
        _target_time = current_time + dura;
      }
      poll_number++;
      single_index++;
      if (single_index >= kmax_single_arr_size)
      {
        single_index = 0;
        is_single_poll_turn = false;
      }
    }

    if (_is_serial_driver)
    {
      // Send association release request through serial port
      // Create serial message from association request
      // Get number of bytes.
      status = serial_converter.ConstructSerialMsg(
        _raw_command,
        _max_command_length,
        reinterpret_cast<unsigned int*>(&_command_length));
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL;
      }
    }

    // First, store the data to log file.
    if (_command_length > 0)
    {
      std::string log_message;
      for (int ix = 0; ix < _command_length; ix++)
      {
        log_message += _raw_command[ix];
      }
      // No function name because we are logging the data exactly as it's
      // sent to the attached device. See log4cplus properties file for
      // additional configuration settings.
      LOG4CPLUS_INFO(cmd_logger, log_message);
    }
    return DicesRcDriver::OK;
  }
  return DicesRcDriver::OK;
}

DicesRcDriver DDPhilipsIntellivueMP70Parser::ParseResponse()
{
  static const char* sfn = "DDPhilipsIntellivueMP70Parser::ParseResponse() ";
  SerialConverter serial_converter;
  DicesRcPhilipsIntellivueMP70 status = DicesRcPhilipsIntellivueMP70::OK;

  // First, store the data to log file.
  if (_response_length > 0)
  {
    std::string log_message;
    for (int ix = 0; ix < _response_length; ix++)
    {
      log_message += _raw_response[ix];
    }
    // No function name because we are logging the data exactly as it comes
    // from the attached device. See log4cplus properties file for additional
    // configuration settings.
    LOG4CPLUS_INFO(raw_logger, log_message);
  }

  if (_response_length > 0)
  {
    if (_is_serial_driver)
    {
      status = serial_converter.UnwrapSerialMsg(
        _raw_response,
        reinterpret_cast<unsigned int*>(&_response_length));
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        if (status == DicesRcPhilipsIntellivueMP70::FRAME_CHECK_SEQUENCE_INCORRECT_FAILURE
          || status == DicesRcPhilipsIntellivueMP70::INCORRECT_PROTOCOL_ID_FAILURE
          || status == DicesRcPhilipsIntellivueMP70::INCORRECT_MESSAGE_TYPE_FAILURE)
        {
          LOG4CPLUS_WARN(root_logger, sfn <<
            DicesRcPhilipsIntellivueMP70StatusMessage::
            DicesRcPhilipsIntellivueMP70ToString(status));
          memset(_raw_response, 0, _max_response_length);
          _response_length = 0;
          status = DicesRcPhilipsIntellivueMP70::OK;
        }
        else
        {
          LOG4CPLUS_ERROR(root_logger, sfn <<
            DicesRcPhilipsIntellivueMP70StatusMessage::
            DicesRcPhilipsIntellivueMP70ToString(status));
          return DicesRcDriver::FAIL;
        }
      }
    }

    // Determine which type of message and call proper function
    bool is_connect_indication_message = false;
    status = IntellivueConnectIndicationMessage::IsConnectIndicationMessage(
      &is_connect_indication_message,
      _raw_response,
      _response_length);
    if (status != DicesRcPhilipsIntellivueMP70::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn <<
        DicesRcPhilipsIntellivueMP70StatusMessage::
        DicesRcPhilipsIntellivueMP70ToString(status));
      return DicesRcDriver::FAIL; // TODO
    }

    bool is_association_response = false;
    status = IntellivueAssociationResponse::IsAssociationResponse(
      &is_association_response,
      _raw_response,
      _response_length);
    if (status != DicesRcPhilipsIntellivueMP70::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn <<
        DicesRcPhilipsIntellivueMP70StatusMessage::
        DicesRcPhilipsIntellivueMP70ToString(status));
      return DicesRcDriver::FAIL; // TODO
    }

    bool is_mds_create_event_report = false;
    status = IntellivueMDSCreateEventReport::IsMDSCreateEventReport(
      &is_mds_create_event_report,
      _raw_response,
      _response_length);
    if (status != DicesRcPhilipsIntellivueMP70::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn <<
        DicesRcPhilipsIntellivueMP70StatusMessage::
        DicesRcPhilipsIntellivueMP70ToString(status));
      return DicesRcDriver::FAIL; // TODO
    }

    bool is_extended_poll_response = false;
    status = IntellivueExtendedPollResponse::IsExtendedPollResponse(
      &is_extended_poll_response,
      _raw_response,
      _response_length);
    if (status != DicesRcPhilipsIntellivueMP70::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn <<
        DicesRcPhilipsIntellivueMP70StatusMessage::
        DicesRcPhilipsIntellivueMP70ToString(status));
      return DicesRcDriver::FAIL; // TODO
    }

    bool is_single_poll_response = false;
    status = IntellivueSinglePollResponse::IsSinglePollResponse(
      &is_single_poll_response,
      _raw_response,
      _response_length);
    if (status != DicesRcPhilipsIntellivueMP70::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn <<
        DicesRcPhilipsIntellivueMP70StatusMessage::
        DicesRcPhilipsIntellivueMP70ToString(status));
      return DicesRcDriver::FAIL;
    }

    bool is_error_response = false;
    status = IntellivueErrorResponse::IsRemoteOperationErrorResponse(
      &is_error_response,
      _raw_response,
      _response_length);
    if (status != DicesRcPhilipsIntellivueMP70::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn <<
        DicesRcPhilipsIntellivueMP70StatusMessage::
        DicesRcPhilipsIntellivueMP70ToString(status));
      return DicesRcDriver::FAIL;
    }

    bool is_set_response = false;
    status = IntellivueSetResponse::IsSetResponse(
      &is_set_response,
      _raw_response,
      _response_length);
    if (status != DicesRcPhilipsIntellivueMP70::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn <<
        DicesRcPhilipsIntellivueMP70StatusMessage::
        DicesRcPhilipsIntellivueMP70ToString(status));
      return DicesRcDriver::FAIL;
    }

    if (is_connect_indication_message)
    {
      LOG4CPLUS_INFO(root_logger, sfn << "Received connect indication "
        "message.");
      status = IntellivueConnectIndicationMessage::DeleteConnectIndicationMessage(
        &_connect_indication);
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL; // TODO
      }

      status = IntellivueConnectIndicationMessage::ParseConnectIndicationMessage(
        &_connect_indication,
        _raw_response,
        _response_length);
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL; // TODO
      }

      memset(_raw_response, 0, _max_response_length);
      _response_length = 0;

      status = IntellivueConnectIndicationMessage::GetIPAddressString(
        &_intellivue_ip_address,
        _connect_indication);
      if (status != DicesRcPhilipsIntellivueMP70::OK
        && status != DicesRcPhilipsIntellivueMP70::GET_IP_ADDRESS_INFO_FAILURE)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL; // TODO
      }

      status = IntellivueConnectIndicationMessage::GetDataExportProtocolPortNumber(
        &_intellivue_data_export_port_number,
        _connect_indication);
      if (status != DicesRcPhilipsIntellivueMP70::OK
        && status != DicesRcPhilipsIntellivueMP70::GET_DATA_EXPORT_PORT_NUMBER_FAILURE)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL; // TODO
      }

      if (_mds_instance_list.size() > 0)
      {
        status = IntellivueConnectIndicationMessage::
          SetMDSWithConnectIndicationMessage(
          &_mds_instance_list.at(0),
          _connect_indication);
        if (status != DicesRcPhilipsIntellivueMP70::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn <<
            DicesRcPhilipsIntellivueMP70StatusMessage::
            DicesRcPhilipsIntellivueMP70ToString(status));
          return DicesRcDriver::FAIL;
        }
      }
      _connect_indication_msg_received = true;
    }
    if (is_association_response)
    {
      LOG4CPLUS_INFO(root_logger, sfn << "Received association response.");
      status = IntellivueAssociationResponse::DeleteAssociationResponse(
        &_association_response);
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL; // TODO
      }

      status = IntellivueAssociationResponse::ParseAssociationResponse(
        &_association_response,
        _raw_response,
        _response_length);
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        if (status == DicesRcPhilipsIntellivueMP70::ASSOCIATION_REFUSED)
        {
          LOG4CPLUS_WARN(root_logger, sfn <<
            DicesRcPhilipsIntellivueMP70StatusMessage::
            DicesRcPhilipsIntellivueMP70ToString(status));
          // Ignore association abort and refuse, and try to associate again
          status = DicesRcPhilipsIntellivueMP70::OK;
          _association_refuse_msg_received = true;
        }
        else if (status == DicesRcPhilipsIntellivueMP70::ASSOCIATION_ABORTED)
        {
          LOG4CPLUS_WARN(root_logger, sfn <<
            DicesRcPhilipsIntellivueMP70StatusMessage::
            DicesRcPhilipsIntellivueMP70ToString(status));
          // Ignore association abort and refuse, and try to associate again
          status = DicesRcPhilipsIntellivueMP70::OK;
        }
        else if (status == DicesRcPhilipsIntellivueMP70::ASSOCIATION_DISCONNECT)
        {
          // Log warning, ignore association disconnect, and try to associate
          // again.
          LOG4CPLUS_WARN(root_logger, sfn << "Ignoring association disconnect "
                         << DicesRcPhilipsIntellivueMP70StatusMessage::
                         DicesRcPhilipsIntellivueMP70ToString(status));
          status = DicesRcPhilipsIntellivueMP70::OK;
        }
        else
        {
          LOG4CPLUS_ERROR(root_logger, sfn <<
            DicesRcPhilipsIntellivueMP70StatusMessage::
            DicesRcPhilipsIntellivueMP70ToString(status));
          return DicesRcDriver::FAIL; // TODO
        }
      }
      else
      {
        _association_response_msg_received = true;
      }
      memset(_raw_response, 0, _max_response_length);
      _response_length = 0;
    }
    if (is_mds_create_event_report)
    {
      LOG4CPLUS_INFO(root_logger, sfn << "Received MDS create event report.");
      status = IntellivueMDSCreateEventReport::DeleteMDSCreateEventReport(
        &_mds_create_event_report);
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL; // TODO
      }

      status = IntellivueMDSCreateEventReport::ParseMDSCreateEventReport(
        &_mds_create_event_report,
        _raw_response,
        _response_length);
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL; // TODO
      }
      _handshake_status = DicesRcDriver::HANDSHAKE_DONE;
      memset(_raw_response, 0, _max_response_length);
      _response_length = 0;

      if (_mds_instance_list.size() > 0
        && _vmd_instance_list.size() > 0)
      {
        if (_mds_instance_list.at(0).second->handle == 0)
        {
          // Generate new MDS handle
          intellivue::Handle new_handle = 0;
          DicesRcPhilipsIntellivueMP70 status = GenerateNewHandle(
            &new_handle);
          if (status != DicesRcPhilipsIntellivueMP70::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn <<
              DicesRcPhilipsIntellivueMP70StatusMessage::
              DicesRcPhilipsIntellivueMP70ToString(status));
            return DicesRcDriver::FAIL;
          }
          // Set new handle for this instance.
          _mds_instance_list.at(0).second->handle = new_handle;
        }

        if (_vmd_instance_list.at(0).second->handle == 0)
        {
          // Generate new VMD handle
          intellivue::Handle new_handle = 0;
          DicesRcPhilipsIntellivueMP70 status = GenerateNewHandle(
            &new_handle);
          if (status != DicesRcPhilipsIntellivueMP70::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn <<
              DicesRcPhilipsIntellivueMP70StatusMessage::
              DicesRcPhilipsIntellivueMP70ToString(status));
            return DicesRcDriver::FAIL;
          }
          // Set new handle for this instance.
          _vmd_instance_list.at(0).second->handle = new_handle;
        }

        status = IntellivueMDSCreateEventReport::SetMDSWithMDSCreateEventReport(
          &_mds_instance_list.at(0),
          _mds_create_event_report);
        if (status != DicesRcPhilipsIntellivueMP70::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn <<
            DicesRcPhilipsIntellivueMP70StatusMessage::
            DicesRcPhilipsIntellivueMP70ToString(status));
          return DicesRcDriver::FAIL;
        }

        status = IntellivueMDSCreateEventReport::SetVMDWithMDSCreateEventReport(
          &_vmd_instance_list.at(0),
          _mds_create_event_report);
        if (status != DicesRcPhilipsIntellivueMP70::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn <<
            DicesRcPhilipsIntellivueMP70StatusMessage::
            DicesRcPhilipsIntellivueMP70ToString(status));
          return DicesRcDriver::FAIL;
        }

        // Parent handle of VMD is the MDS handle
        if (_vmd_instance_list.at(0).second->parent_handle
          != _mds_instance_list.at(0).second->handle)
        {
          _vmd_instance_list.at(0).second->parent_handle = _mds_instance_list.
            at(0).second->handle;
          _vmd_instance_list.at(0).first = DicesRcDriver::OK;
        }

        // Generate new handle for VMD if it doesn't have one yet.
        if (_vmd_instance_list.at(0).second->handle == 0)
        {
          intellivue::Handle new_handle = 1;
          status = GenerateNewHandle(&new_handle);
          if (status != DicesRcPhilipsIntellivueMP70::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn <<
              DicesRcPhilipsIntellivueMP70StatusMessage::
              DicesRcPhilipsIntellivueMP70ToString(status));
            return DicesRcDriver::FAIL;
          }

          if (_vmd_instance_list.at(0).second->handle != new_handle)
          {
            _vmd_instance_list.at(0).second->handle = new_handle;
            _vmd_instance_list.at(0).first = DicesRcDriver::OK;
          }
        }
      }
      _mds_create_event_report_received = true;
    }
    if (is_extended_poll_response)
    {
      LOG4CPLUS_INFO(root_logger, sfn << "Received extended poll response.");
      status = IntellivueExtendedPollResponse::DeleteExtendedPollResponse(
        &_extended_poll_response);
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL; // TODO
      }

      status = IntellivueExtendedPollResponse::ParseExtendedPollResponse(
        &_extended_poll_response,
        _raw_response,
        _response_length);
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL; // TODO
      }
      memset(_raw_response, 0, _max_response_length);
      _response_length = 0;

      status = SetExtendedPollResponseData();
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL; // TODO
      }
    }
    if (is_single_poll_response)
    {
      LOG4CPLUS_INFO(root_logger, sfn << "Received single poll response.");
      status = IntellivueSinglePollResponse::DeleteSinglePollResponse(
        &_single_poll_response);
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL;
      }

      status = IntellivueSinglePollResponse::ParseSinglePollResponse(
        &_single_poll_response,
        _raw_response,
        _response_length);
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL;
      }
      memset(_raw_response, 0, _max_response_length);
      _response_length = 0;

      status = SetSinglePollResponseData();
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL;
      }
    }
    if (is_error_response)
    {
      LOG4CPLUS_INFO(root_logger, sfn << "Received error response.");
      status = IntellivueErrorResponse::ParseRemoteOperationErrorResponse(
        _raw_response,
        _response_length);
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL;
      }
      memset(_raw_response, 0, _max_response_length);
      _response_length = 0;
    }
    if (is_set_response)
    {
      LOG4CPLUS_INFO(root_logger, sfn << "Received set response.");
      status = IntellivueSetResponse::ParseSetResponse(
        _raw_response,
        _response_length);
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL;
      }
      memset(_raw_response, 0, _max_response_length);
      _response_length = 0;
    }
  }

  return DicesRcDriver::OK;
}

DicesRcPhilipsIntellivueMP70 DDPhilipsIntellivueMP70Parser::GetAssociationRequest()
{
  static const char* sfn = "DDPhilipsIntellivueMP70Parser::GetAssociationRequest() ";

  int istat = 0;
  unsigned int isize = 0;
  SerialConverter serial_converter;
  IntellivueAssociationRequest association_request;

  // Create association request and get the number of bytes contained
  // in the request.
  DicesRcPhilipsIntellivueMP70 status = association_request.
    CreateAssociationRequest(
    _raw_command,
    _max_command_length,
    &isize);
  if (status != DicesRcPhilipsIntellivueMP70::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn <<
      DicesRcPhilipsIntellivueMP70StatusMessage::
      DicesRcPhilipsIntellivueMP70ToString(status));
    return status;
  }

  _command_length = static_cast<int>(isize);

  if (_is_serial_driver)
  {
    // Send association request through serial port
    // Create serial message from association request
    // Get number of bytes.
    status = serial_converter.ConstructSerialMsg(
      _raw_command,
      _max_command_length,
      reinterpret_cast<unsigned int*>(&_command_length));
    if (status != DicesRcPhilipsIntellivueMP70::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn <<
        DicesRcPhilipsIntellivueMP70StatusMessage::
        DicesRcPhilipsIntellivueMP70ToString(status));
      return status;
    }
  }
  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 DDPhilipsIntellivueMP70Parser::
GetAssociationReleaseRequest()
{
  static const char* sfn = "DDPhilipsIntellivueMP70Parser::"
    "GetAssociationReleaseRequest() ";

  int istat = 0;
  unsigned int isize = 0;
  SerialConverter serial_converter;

  // Create association release request and get the number of bytes contained
  // in the request.
  DicesRcPhilipsIntellivueMP70 status = IntellivueAssociationReleaseRequest::
    CreateAssociationReleaseRequest(
    _raw_command,
    _max_command_length,
    &isize);
  if (status != DicesRcPhilipsIntellivueMP70::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn <<
      DicesRcPhilipsIntellivueMP70StatusMessage::
      DicesRcPhilipsIntellivueMP70ToString(status));
    return status;
  }

  _command_length = static_cast<int>(isize);

  if (_is_serial_driver)
  {
    // Send association request through serial port
    // Create serial message from association request
    // Get number of bytes.
    status = serial_converter.ConstructSerialMsg(
      _raw_command,
      _max_command_length,
      reinterpret_cast<unsigned int*>(&_command_length));
    if (status != DicesRcPhilipsIntellivueMP70::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn <<
        DicesRcPhilipsIntellivueMP70StatusMessage::
        DicesRcPhilipsIntellivueMP70ToString(status));
      return status;
    }
  }
  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcDriver DDPhilipsIntellivueMP70Parser::GetHandshakeCmd()
{
  static const char* sfn = "DDPhilipsIntellivueMP70Parser::GetHandshakeCmd() ";
  DicesRcPhilipsIntellivueMP70 status = DicesRcPhilipsIntellivueMP70::OK;

  // Clear previous command
  memset(_raw_command, 0, _max_command_length);
  _command_length = 0;

  if (_is_serial_driver)
  {
    if (!_association_release_request_sent
      && !_association_response_msg_received)
    {
      status = GetAssociationReleaseRequest();
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL; // TODO
      }
      _association_release_request_sent = true;
    }
    else if (!_association_response_msg_received)
    {
      status = GetAssociationRequest();
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL; // TODO
      }
    }
  }

  if (!_is_serial_driver
    && _connect_indication_msg_received
    && !_port_reconfigured)
  {
    _handshake_status = DicesRcDriver::RECONFIGURE_PORT_SETTINGS;
    _port_reconfigured = true;
    return _handshake_status;
  }

  if (!_is_serial_driver
    && _port_reconfigured
    && _connect_indication_msg_received
    && !_association_response_msg_received)
  {
    if (!_association_refuse_msg_received)
    {
      _handshake_status = DicesRcDriver::OK;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      status = GetAssociationRequest();
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
                        DicesRcPhilipsIntellivueMP70StatusMessage::
                        DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcDriver::FAIL;
      }
    }
    else
    {
      if (!_association_release_request_sent_lan)
      {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        status = GetAssociationReleaseRequest();
        if (status != DicesRcPhilipsIntellivueMP70::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn <<
                          DicesRcPhilipsIntellivueMP70StatusMessage::
                          DicesRcPhilipsIntellivueMP70ToString(status));
          return DicesRcDriver::FAIL;
        }
        _association_release_request_sent_lan = true;
      }
      else
      {
        // After assoication release request is sent, send the
        // association request one more time. On the second time
        // return failure and exit the driver.
        static int association_release_request_sent_count = 0;
        if (_association_release_request_sent_lan)
        {
          association_release_request_sent_count++;

          if (association_release_request_sent_count > 1)
          {
            // Already sent association request after association release
            // request, exit driver.
            LOG4CPLUS_ERROR(root_logger, sfn << "Sent association request after "
                                                "association release request. "
                                                "No response received. "
                                                "Exiting driver now.");
            _handshake_status = DicesRcDriver::FAIL;
            return _handshake_status;
          }
        }

        _handshake_status = DicesRcDriver::OK;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        status = GetAssociationRequest();
        if (status != DicesRcPhilipsIntellivueMP70::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn <<
                          DicesRcPhilipsIntellivueMP70StatusMessage::
                          DicesRcPhilipsIntellivueMP70ToString(status));
          return DicesRcDriver::FAIL;
        }
      }
    }
  }

  // First, store the data to log file.
  if (_command_length > 0)
  {
    std::string log_message;
    for (int ix = 0; ix < _command_length; ix++)
    {
      log_message += _raw_command[ix];
    }
    // No function name because we are logging the data exactly as it's
    // sent to the attached device. See log4cplus properties file for
    // additional configuration settings.
    LOG4CPLUS_INFO(cmd_logger, log_message);
  }

  return _handshake_status;
}

DicesRcDriver DDPhilipsIntellivueMP70Parser::ShutdownParser()
{
  static const char* sfn = "DDPhilipsIntellivueMP70Parser::ShutdownParser() ";
  return DicesRcDriver::OK;
}

DicesRcPhilipsIntellivueMP70 DDPhilipsIntellivueMP70Parser::
SetExtendedPollResponseData()
{
  static const char* sfn = "DDPhilipsIntellivueMP70Parser::"
    "SetExtendedPollResponseData() ";
  DicesRcPhilipsIntellivueMP70 status = DicesRcPhilipsIntellivueMP70::OK;

  intellivue::OIDType code = _extended_poll_response.pollReply.
    polled_obj_type.code;
  switch (code)
  {
    case NOM_MOC_VMO_METRIC_NU:
      LOG4CPLUS_INFO(root_logger, sfn << "Setting extended numeric response "
        "data.");
      status = SetExtendedNumericResponseData();
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcPhilipsIntellivueMP70::FAIL;
      }
      break;
    case NOM_MOC_VMO_METRIC_SA_RT:
      LOG4CPLUS_INFO(root_logger, sfn << "Setting extended rtsa response "
        "data.");
      status = SetExtendedRTSAResponseData();
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcPhilipsIntellivueMP70::FAIL;
      }
      break;
    case NOM_MOC_VMO_METRIC_ENUM:
      LOG4CPLUS_INFO(root_logger, sfn << "Setting extended enum response "
        "data.");
      status = SetExtendedEnumResponseData();
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcPhilipsIntellivueMP70::FAIL;
      }
      break;
    case NOM_MOC_VMO_AL_MON:
      LOG4CPLUS_INFO(root_logger, sfn << "Setting extended alarm response "
        "data.");
      status = SetExtendedAlarmResponseData();
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcPhilipsIntellivueMP70::FAIL;
      }
      break;
    default:
      LOG4CPLUS_WARN(root_logger, sfn << "Received unknown TYPE code ("
        << static_cast<int>(code) << ") in extended poll response data.");
      break;
  }
  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 DDPhilipsIntellivueMP70Parser::
SetSinglePollResponseData()
{
  static const char* sfn = "DDPhilipsIntellivueMP70Parser::"
    "SetSinglePollResponseData() ";
  DicesRcPhilipsIntellivueMP70 status = DicesRcPhilipsIntellivueMP70::OK;

  intellivue::OIDType code = _single_poll_response.pollReply.
    polled_obj_type.code;
  switch (code)
  {
    case NOM_MOC_VMS_MDS:
      LOG4CPLUS_INFO(root_logger, sfn << "Setting single mds response "
        "data.");
      status = SetSingleMDSResponseData();
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcPhilipsIntellivueMP70::FAIL;
      }
      break;
    case NOM_MOC_PT_DEMOG:
      LOG4CPLUS_INFO(root_logger, sfn << "Setting single patient "
        "demographics response data.");
      status = SetSinglePatientDemographicsResponseData();
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return DicesRcPhilipsIntellivueMP70::FAIL;
      }
      break;
    default:
      LOG4CPLUS_WARN(root_logger, sfn << "Received unknown TYPE code ("
        << static_cast<int>(code) << ") in single poll response data.");
      break;
  }
  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 DDPhilipsIntellivueMP70Parser::
SetExtendedNumericResponseData()
{
  static const char* sfn = "DDPhilipsIntellivueMP70Parser::"
    "SetExtendedNumericResponseData() ";
  DicesRcPhilipsIntellivueMP70 status = DicesRcPhilipsIntellivueMP70::OK;

  intellivue::GlbHandle glb_handle = {
    _extended_poll_response.actionresult.managed_object.m_obj_inst.context_id,
    _extended_poll_response.actionresult.managed_object.m_obj_inst.handle
  };

  for (
    int ix = 0;
    ix < _extended_poll_response.pollReply.poll_info_list.count;
    ix++)
  {
    if (!_extended_poll_response.pollReply.poll_info_list.value)
    {
      LOG4CPLUS_WARN(root_logger, sfn << "SingleContextPoll array in "
        "poll_info_list is a null pointer");
      break;
    }
    intellivue::MdsContext single_context_poll_context_id =
      _extended_poll_response.pollReply.poll_info_list.value[ix].context_id;

    for (
      int iy = 0;
      iy < _extended_poll_response.pollReply.poll_info_list.value[ix].
      poll_info.count;
      iy++)
    {
      if (!_extended_poll_response.pollReply.poll_info_list.value[ix].
        poll_info.value)
      {
        LOG4CPLUS_WARN(root_logger, sfn << "ObservationPoll array in "
          "poll_info is a null pointer");
        break;
      }

      // Get handles of all numeric observed values
      std::vector<intellivue::Handle> handle_list;
      for (
        int iz = 0;
        iz < _extended_poll_response.pollReply.poll_info_list.value[ix].
        poll_info.value[iy].attributes.count;
        iz++)
      {
        try
        {
          handle_list.push_back(
            _extended_poll_response.pollReply.poll_info_list.value[ix].
            poll_info.value[iy].obj_handle);
        }
        catch (const std::exception& ex)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert handle "
            "into vector. " << ex.what());
          return DicesRcPhilipsIntellivueMP70::VECTOR_INSERT_FAILURE;
        }
      }
      // Set absolute timestamp for all metrics found
      if (_extended_poll_response.pollReply.abs_time_stamp.century != 0xFF
        || _extended_poll_response.pollReply.abs_time_stamp.year != 0xFF
        || _extended_poll_response.pollReply.abs_time_stamp.month != 0xFF
        || _extended_poll_response.pollReply.abs_time_stamp.day != 0xFF
        || _extended_poll_response.pollReply.abs_time_stamp.hour != 0xFF
        || _extended_poll_response.pollReply.abs_time_stamp.minute != 0xFF
        || _extended_poll_response.pollReply.abs_time_stamp.second != 0xFF
        || _extended_poll_response.pollReply.abs_time_stamp.sec_fractions != 0xFF)
      {
        for (int ij = 0; ij < handle_list.size(); ij++)
        {
          for (int ik = 0;
            ik < _numeric_meas_observed_value_response_instance_list.
            size();
            ik++)
          {
            if (_numeric_meas_observed_value_response_instance_list.
              at(ik).second->handle == handle_list.at(ij))
            {
              if (!_numeric_meas_observed_value_response_instance_list.
                at(ik).second->device_timestamp)
              {
                _numeric_meas_observed_value_response_instance_list.
                  at(ik).second->device_timestamp =
                  reinterpret_cast<ice::Timespec *>(
                  DDS::Heap_malloc(sizeof(ice::Timespec)));
                if (!_numeric_meas_observed_value_response_instance_list.
                  at(ik).second->device_timestamp)
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "Failed to "
                    "allocate memory for ice::Timespec");
                  continue;
                }
              }
              DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                ConvertIntellivueAbsoluteTimeToDicesTimespec(
                _numeric_meas_observed_value_response_instance_list.
                at(ik).second->device_timestamp,
                _extended_poll_response.pollReply.abs_time_stamp);
              if (status != DicesRcPhilipsIntellivueMP70::OK)
              {
                LOG4CPLUS_ERROR(root_logger, sfn <<
                  DicesRcPhilipsIntellivueMP70StatusMessage::
                  DicesRcPhilipsIntellivueMP70ToString(status));
                return status;
              }
            }
          }
        }
      }

      for (int ij = 0; ij < handle_list.size(); ij++)
      {
        for (int ik = 0;
          ik < _numeric_meas_observed_value_response_instance_list.
          size();
          ik++)
        {
          if (_numeric_meas_observed_value_response_instance_list.
            at(ik).second->handle
            == handle_list.at(ij))
          {
            // Set relative timestamp for all metrics found
            if (!_numeric_meas_observed_value_response_instance_list.
              at(ik).second->device_relative_timestamp)
            {
              _numeric_meas_observed_value_response_instance_list.
                at(ik).second->device_relative_timestamp =
                reinterpret_cast<ice::Duration *>(
                DDS::Heap_malloc(sizeof(ice::Duration)));
              if (!_numeric_meas_observed_value_response_instance_list.
                at(ik).second->device_relative_timestamp)
              {
                LOG4CPLUS_WARN(root_logger, sfn << "Failed to "
                  "allocate memory for ice::Duration");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
            }
            DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
              ConvertIntellivueRelativeTimeToDicesDuration(
              _numeric_meas_observed_value_response_instance_list.
              at(ik).second->device_relative_timestamp,
              _extended_poll_response.pollReply.rel_time_stamp);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }
            _numeric_meas_observed_value_response_instance_list.
              at(ik).second->type.code = _extended_poll_response.
              pollReply.polled_obj_type.code;

            status = IntellivueUtils::
              ConvertIntellivueNomPartitionToDicesNomPartition(
              &_numeric_meas_observed_value_response_instance_list.
              at(ik).second->type.partition,
              _extended_poll_response.pollReply.polled_obj_type.partition);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }
          }
        }
      }
      for (
        int iz = 0;
        iz < _extended_poll_response.pollReply.poll_info_list.value[ix].
        poll_info.value[iy].attributes.count;
        iz++)
      {
        if (!_extended_poll_response.pollReply.poll_info_list.value[ix].
          poll_info.value[iy].attributes.value)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "AVAType array in "
            "attributes is a null pointer");
          break;
        }

        intellivue::Handle obj_handle =
          _extended_poll_response.pollReply.poll_info_list.value[ix].
          poll_info.value[iy].obj_handle;

        std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>
          unique_handle(glb_handle.context_id, glb_handle.handle, single_context_poll_context_id, obj_handle);

        std::map<
          std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
          std::map < intellivue::Handle, unsigned int>>::iterator it;
        it = _map_handle_to_numeric_instance.find(unique_handle);
        if (it == _map_handle_to_numeric_instance.end())
        {
          if (_numeric_vector_max_index
              >= _numeric_meas_context_response_instance_list.size()
              ||_numeric_vector_max_index
              >= _numeric_sett_context_response_instance_list.size()
              ||_numeric_vector_max_index
              >= _numeric_calc_context_response_instance_list.size())
          {
            LOG4CPLUS_INFO(root_logger, sfn << "The maximum number of numeric context "
              "instances are already in use for meas, sett and calc instance lists. "
              "Inserting additional instances.");

            unsigned int nu_meas_inst_diff = _numeric_vector_max_index
                - _numeric_meas_context_response_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= nu_meas_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::NumericContext*> nu_meas_ctxt_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::NumericContextTypeSupport::create_data());
              if (!nu_meas_ctxt_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for numeric measurement context instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _numeric_meas_context_response_instance_list.push_back(nu_meas_ctxt_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "numeric measurement context pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }

            unsigned int nu_sett_inst_diff = _numeric_vector_max_index
                - _numeric_sett_context_response_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= nu_sett_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::NumericContext*> nu_sett_ctxt_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::NumericContextTypeSupport::create_data());
              if (!nu_sett_ctxt_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for numeric setting context instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _numeric_sett_context_response_instance_list.push_back(nu_sett_ctxt_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "numeric setting context pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }

            unsigned int nu_calc_inst_diff = _numeric_vector_max_index
                - _numeric_calc_context_response_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= nu_calc_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::NumericContext*> nu_calc_ctxt_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::NumericContextTypeSupport::create_data());
              if (!nu_calc_ctxt_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for numeric calculation context instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _numeric_calc_context_response_instance_list.push_back(nu_calc_ctxt_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "numeric calculation context pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }
          }
          if (_numeric_vector_max_index
              >= _numeric_meas_observed_value_response_instance_list.size()
              ||_numeric_vector_max_index
              >= _numeric_sett_observed_value_response_instance_list.size()
              ||_numeric_vector_max_index
              >= _numeric_calc_observed_value_response_instance_list.size())
          {
            LOG4CPLUS_INFO(root_logger, sfn << "The maximum number of numeric observed value "
              "instances are already in use for meas, sett and calc instance lists. "
              "Inserting additional instances.");

            unsigned int nu_meas_inst_diff = _numeric_vector_max_index
                - _numeric_meas_observed_value_response_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= nu_meas_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::NumericObservedValue*> nu_meas_obs_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::NumericObservedValueTypeSupport::create_data());
              if (!nu_meas_obs_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for numeric "
                                                    "measurement observed value instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _numeric_meas_observed_value_response_instance_list.push_back(nu_meas_obs_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "numeric measurement observed value pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }

            unsigned int nu_sett_inst_diff = _numeric_vector_max_index
                - _numeric_sett_observed_value_response_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= nu_sett_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::NumericObservedValue*> nu_sett_obs_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::NumericObservedValueTypeSupport::create_data());
              if (!nu_sett_obs_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for numeric setting "
                                                    "observed value instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _numeric_sett_observed_value_response_instance_list.push_back(nu_sett_obs_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "numeric setting observed value pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }

            unsigned int nu_calc_inst_diff = _numeric_vector_max_index
                - _numeric_calc_observed_value_response_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= nu_calc_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::NumericObservedValue*> nu_calc_obs_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::NumericObservedValueTypeSupport::create_data());
              if (!nu_calc_obs_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for numeric "
                                                    "calculation observed value instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _numeric_calc_observed_value_response_instance_list.push_back(nu_calc_obs_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "numeric calculation observed value pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }
          }
          ice::NumericContext* context_instance = nullptr;
          try
          {
            context_instance = _numeric_meas_context_response_instance_list.at(
              _numeric_vector_max_index).second;
            if (!context_instance)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Numeric context "
                "instance is a null pointer at index: "
                << _numeric_vector_max_index);
              return DicesRcPhilipsIntellivueMP70::FAIL;
            }
          }
          catch (std::exception& ex)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get numeric context "
              "instance from instance list at index: "
              << _numeric_vector_max_index << ". " << ex.what());
            return DicesRcPhilipsIntellivueMP70::FAIL;
          }
          ice::NumericObservedValue* obs_val_instance = nullptr;
          try
          {
            obs_val_instance = _numeric_meas_observed_value_response_instance_list.at(
              _numeric_vector_max_index).second;
            if (!obs_val_instance)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Numeric observed value "
                "instance is a null pointer at index: "
                << _numeric_vector_max_index);
              return DicesRcPhilipsIntellivueMP70::FAIL;
            }
          }
          catch (std::exception& ex)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get numeric "
              "observed value instance from instance list at index: "
              << _numeric_vector_max_index << ". " << ex.what());
            return DicesRcPhilipsIntellivueMP70::FAIL;
          }

          if (context_instance->handle == 0 && obs_val_instance->handle == 0)
          {
            // Generate new numeric handle
            intellivue::Handle new_handle = 0;
            DicesRcPhilipsIntellivueMP70 status = GenerateNewHandle(
              &new_handle);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }
            // Set new handle for this instance.
            context_instance->handle = new_handle;
            obs_val_instance->handle = new_handle;

            std::map<intellivue::Handle, unsigned int> handle_to_index;
            std::pair < std::map<intellivue::Handle, unsigned int>::iterator, bool> ret_1 =
              handle_to_index.insert(std::pair<intellivue::Handle, unsigned int>(
              new_handle,
              _numeric_vector_max_index++));
            if (!ret_1.second)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert generated "
                "handle and vector index into map.");
              return DicesRcPhilipsIntellivueMP70::FAIL;
            }

            std::pair < std::map<
              std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
              std::map < intellivue::Handle, unsigned int>>::iterator, bool> ret_2 =
              _map_handle_to_numeric_instance.insert(
              std::pair<
              std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
              std::map < intellivue::Handle, unsigned int>>(
              unique_handle,
              handle_to_index));
            if (!ret_2.second)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert unique handle "
                "and handle and vector index map into map.");
              return DicesRcPhilipsIntellivueMP70::FAIL;
            }
          }
        }

        if (_map_handle_to_numeric_instance[unique_handle].empty())
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Will not be able to "
            "dereference the iterator returned from numeric instance map in "
            "the future. There must be at least one index for numeric "
            "instance vector per object.");
          break;
        }

        intellivue::OIDType attribute_id = _extended_poll_response.pollReply.
          poll_info_list.value[ix].poll_info.value[iy].attributes.value[iz].
          attribute_id;
        switch (attribute_id)
        {
          case NOM_ATTR_ID_HANDLE:
          {
            intellivue::Handle* phandle =
              reinterpret_cast<intellivue::Handle*>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!phandle)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into intellivue::Handle. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            // Handle already set above.
            // Set parent handle to the VMD handle
            if (_vmd_instance_list.size() > 0)
            {
              _numeric_meas_context_response_instance_list.at(
                _map_handle_to_numeric_instance[unique_handle].begin()->second).
                second->parent_handle = _vmd_instance_list.at(0).second->handle;

              _numeric_meas_observed_value_response_instance_list.at(
                _map_handle_to_numeric_instance[unique_handle].begin()->second).
                second->parent_handle = _vmd_instance_list.at(0).second->handle;
            }

          }
            break;
          case NOM_ATTR_ID_TYPE:
          {
            intellivue::TYPE* ptype =
              reinterpret_cast<intellivue::TYPE*>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);

            if (ptype)
            {
              ice::NomPartition dices_nom_partition = ice::nom_part_unspec;
              DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                ConvertIntellivueNomPartitionToDicesNomPartition(
                &dices_nom_partition,
                ptype->partition);
              if (status != DicesRcPhilipsIntellivueMP70::OK)
              {
                LOG4CPLUS_ERROR(root_logger, sfn <<
                  DicesRcPhilipsIntellivueMP70StatusMessage::
                  DicesRcPhilipsIntellivueMP70ToString(status));
                return status;
              }

              if (_numeric_meas_context_response_instance_list.
                at(_map_handle_to_numeric_instance[unique_handle].begin()->
                second).second->type.partition != dices_nom_partition)
              {
                _numeric_meas_context_response_instance_list.
                  at(_map_handle_to_numeric_instance[unique_handle].begin()->
                  second).second->type.partition = dices_nom_partition;
              }

              if (_numeric_meas_context_response_instance_list.
                at(_map_handle_to_numeric_instance[unique_handle].begin()->
                second).second->type.code != ptype->code)
              {
                _numeric_meas_context_response_instance_list.
                  at(_map_handle_to_numeric_instance[unique_handle].begin()->
                  second).second->type.code = ptype->code;
              }

              _numeric_meas_observed_value_response_instance_list.
                at(_map_handle_to_numeric_instance[unique_handle].begin()->
                second).second->type.partition = dices_nom_partition;

              _numeric_meas_observed_value_response_instance_list.
                at(_map_handle_to_numeric_instance[unique_handle].begin()->
                second).second->type.code = ptype->code;
            }
          }
            break;
          case NOM_ATTR_NU_VAL_OBS:
          {
            intellivue::NuObsValue* pnu_obs_val =
              reinterpret_cast<intellivue::NuObsValue*>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (pnu_obs_val)
            {
              ice::MeasurementStatus mstat = 0;
              status = IntellivueUtils::ConvertIntellivueMeasurementStatusToDicesMeasurementStatus(
                &mstat,
                pnu_obs_val->state);
              if (status != DicesRcPhilipsIntellivueMP70::OK)
              {
                LOG4CPLUS_ERROR(root_logger, sfn <<
                  DicesRcPhilipsIntellivueMP70StatusMessage::
                  DicesRcPhilipsIntellivueMP70ToString(status));
                return status;
              }

              if (_numeric_meas_context_response_instance_list.at(
                _map_handle_to_numeric_instance[unique_handle].begin()->second).
                second->measurement_status != mstat)
              {
                _numeric_meas_context_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle].begin()->second).
                  second->measurement_status = mstat;
                if (_numeric_meas_context_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle].begin()->second).
                  second->metric_id != 0)
                {
                  _numeric_meas_context_response_instance_list.at(
                    _map_handle_to_numeric_instance[unique_handle].begin()->
                    second).first = DicesRcDriver::OK;
                }
              }

              if (_numeric_meas_context_response_instance_list.at(
                _map_handle_to_numeric_instance[unique_handle].begin()->second).
                second->unit_code != pnu_obs_val->unit_code)
              {
                _numeric_meas_context_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle].begin()->second).
                  second->unit_code = pnu_obs_val->unit_code;
                if (_numeric_meas_context_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle].begin()->second).
                  second->metric_id != 0)
                {
                  _numeric_meas_context_response_instance_list.at(
                    _map_handle_to_numeric_instance[unique_handle].begin()->
                    second).first = DicesRcDriver::OK;
                }
              }

              intellivue::OIDType metric_id = 0;
              DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                TranslateIntellivePhysioIdToDicesMetricId(
                _numeric_meas_context_response_instance_list.at(
                _map_handle_to_numeric_instance[unique_handle].begin()->second).
                second->vmo_label_string,
                pnu_obs_val->physio_id,
                &metric_id);
              if (status != DicesRcPhilipsIntellivueMP70::OK)
              {
                LOG4CPLUS_ERROR(root_logger, sfn <<
                  DicesRcPhilipsIntellivueMP70StatusMessage::
                  DicesRcPhilipsIntellivueMP70ToString(status));
                return status;
              }

              if (_numeric_meas_context_response_instance_list.at(
                _map_handle_to_numeric_instance[unique_handle].begin()->second).
                second->metric_id != metric_id)
              {
                _numeric_meas_context_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle].begin()->second).
                  second->metric_id = metric_id;
                _numeric_meas_context_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle].begin()->second).
                  first = DicesRcDriver::OK;
              }

              _numeric_meas_observed_value_response_instance_list.at(
                _map_handle_to_numeric_instance[unique_handle].begin()->second).
                second->nu_observed_value.state = mstat;
              _numeric_meas_observed_value_response_instance_list.at(
                _map_handle_to_numeric_instance[unique_handle].begin()->second).
                second->nu_observed_value.unit_code = pnu_obs_val->unit_code;
              _numeric_meas_observed_value_response_instance_list.at(
                _map_handle_to_numeric_instance[unique_handle].begin()->second).
                second->nu_observed_value.metric_id = metric_id;

              ice::FLOATType dices_value = 0;
              status = IntellivueUtils::
                ConvertIntellivueFloatTypeToDicesFloatType(
                &dices_value,
                pnu_obs_val->value);
              if (status != DicesRcPhilipsIntellivueMP70::OK)
              {
                LOG4CPLUS_ERROR(root_logger, sfn <<
                  DicesRcPhilipsIntellivueMP70StatusMessage::
                  DicesRcPhilipsIntellivueMP70ToString(status));
                return status;
              }
              _numeric_meas_observed_value_response_instance_list.at(
                _map_handle_to_numeric_instance[unique_handle].begin()->second).
                second->nu_observed_value.value = dices_value;

              if (_numeric_meas_observed_value_response_instance_list.at(
                _map_handle_to_numeric_instance[unique_handle].begin()->second).
                second->nu_observed_value.metric_id != 0)
              {
                _numeric_meas_observed_value_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle].begin()->second).
                  first = DicesRcDriver::OK;
              }
            }
          }
            break;
          case NOM_ATTR_NU_CMPD_VAL_OBS:
          {
            intellivue::NuObsValueCmp* pnu_obs_val_cmp =
              reinterpret_cast<intellivue::NuObsValueCmp*>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (pnu_obs_val_cmp)
            {
              for (int ij = 0; ij < pnu_obs_val_cmp->count; ij++)
              {
                if (pnu_obs_val_cmp->count >
                  _map_handle_to_numeric_instance[unique_handle].size())
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "Not enough numeric "
                    "instances for NuObsValueCmp. Expecting "
                    << pnu_obs_val_cmp->count << ", actual "
                    << _map_handle_to_numeric_instance[unique_handle].size());
                  break;
                }

                ice::MeasurementStatus mstat = 0;
                status = IntellivueUtils::ConvertIntellivueMeasurementStatusToDicesMeasurementStatus(
                  &mstat,
                  pnu_obs_val_cmp->value[ij].state);
                if (status != DicesRcPhilipsIntellivueMP70::OK)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn <<
                    DicesRcPhilipsIntellivueMP70StatusMessage::
                    DicesRcPhilipsIntellivueMP70ToString(status));
                  return status;
                }

                intellivue::Handle handle = 0;
                bool found_metric_id = false;
                std::map<intellivue::Handle, unsigned int>::iterator it;
                for (
                  it = _map_handle_to_numeric_instance[unique_handle].begin();
                  it != _map_handle_to_numeric_instance[unique_handle].end();
                  it++)
                {
                  intellivue::OIDType metric_id = 0;
                  DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                    TranslateIntellivePhysioIdToDicesMetricId(
                    _numeric_meas_context_response_instance_list.at(
                    it->second).second->vmo_label_string,
                    pnu_obs_val_cmp->value[ij].physio_id,
                    &metric_id);
                  if (status != DicesRcPhilipsIntellivueMP70::OK)
                  {
                    LOG4CPLUS_ERROR(root_logger, sfn <<
                      DicesRcPhilipsIntellivueMP70StatusMessage::
                      DicesRcPhilipsIntellivueMP70ToString(status));
                    return status;
                  }

                  if (_numeric_meas_observed_value_response_instance_list.at(
                    it->second).second->nu_observed_value.metric_id ==
                    metric_id)
                  {
                    handle = it->first;
                    found_metric_id = true;
                    break;
                  }
                }

                if (!found_metric_id)
                {
                  std::map<intellivue::Handle, unsigned int>::iterator cmp_nu_handle_it;
                  cmp_nu_handle_it = std::next(
                    _map_handle_to_numeric_instance[unique_handle].begin(),
                    ij);
                  handle = cmp_nu_handle_it->first;
                }

                intellivue::OIDType metric_id = 0;
                DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                  TranslateIntellivePhysioIdToDicesMetricId(
                  _numeric_meas_context_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle][
                  handle]).second->vmo_label_string,
                  pnu_obs_val_cmp->value[ij].physio_id,
                  &metric_id);
                if (status != DicesRcPhilipsIntellivueMP70::OK)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn <<
                    DicesRcPhilipsIntellivueMP70StatusMessage::
                    DicesRcPhilipsIntellivueMP70ToString(status));
                  return status;
                }

                if (_numeric_meas_context_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle][
                  handle]).second->metric_id != metric_id)
                {
                  _numeric_meas_context_response_instance_list.at(
                    _map_handle_to_numeric_instance[unique_handle][
                    handle]).second->metric_id = metric_id;
                  _numeric_meas_context_response_instance_list.at(
                    _map_handle_to_numeric_instance[unique_handle][
                    handle]).first = DicesRcDriver::OK;
                }

                if (_numeric_meas_context_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle][
                  handle]).second->measurement_status
                  != mstat)
                {
                  _numeric_meas_context_response_instance_list.at(
                    _map_handle_to_numeric_instance[unique_handle][
                    handle]).second->measurement_status =
                    mstat;
                  if (_numeric_meas_context_response_instance_list.at(
                    _map_handle_to_numeric_instance[unique_handle][
                    handle]).second->metric_id != 0)
                  {
                    _numeric_meas_context_response_instance_list.at(
                      _map_handle_to_numeric_instance[unique_handle][
                      handle]).first = DicesRcDriver::OK;
                  }
                }

                if (_numeric_meas_context_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle][
                  handle]).second->unit_code
                  != pnu_obs_val_cmp->value[ij].unit_code)
                {
                  _numeric_meas_context_response_instance_list.at(
                    _map_handle_to_numeric_instance[unique_handle][
                    handle]).second->unit_code =
                    pnu_obs_val_cmp->value[ij].unit_code;
                  if (_numeric_meas_context_response_instance_list.at(
                    _map_handle_to_numeric_instance[unique_handle][
                    handle]).second->metric_id != 0)
                  {
                    _numeric_meas_context_response_instance_list.at(
                      _map_handle_to_numeric_instance[unique_handle][
                      handle]).first = DicesRcDriver::OK;
                  }
                }

                _numeric_meas_observed_value_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle][
                  handle]).second->nu_observed_value.state =
                  mstat;

                _numeric_meas_observed_value_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle][
                  handle]).second->nu_observed_value.
                  unit_code = pnu_obs_val_cmp->value[ij].unit_code;

                _numeric_meas_observed_value_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle][
                  handle]).second-> nu_observed_value.metric_id = metric_id;

                ice::FLOATType dices_value = 0;
                status = IntellivueUtils::
                  ConvertIntellivueFloatTypeToDicesFloatType(
                  &dices_value,
                  pnu_obs_val_cmp->value[ij].value);
                if (status != DicesRcPhilipsIntellivueMP70::OK)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn <<
                    DicesRcPhilipsIntellivueMP70StatusMessage::
                    DicesRcPhilipsIntellivueMP70ToString(status));
                  return status;
                }
                _numeric_meas_observed_value_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle][
                  handle]).second-> nu_observed_value.value = dices_value;

                if (_numeric_meas_observed_value_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle][
                  handle]).second-> nu_observed_value.
                  metric_id != 0)
                {
                  _numeric_meas_observed_value_response_instance_list.at(
                    _map_handle_to_numeric_instance[unique_handle][
                    handle]).first = DicesRcDriver::OK;
                }
              }
            }
          }
            break;
          case NOM_ATTR_TIME_STAMP_ABS:
          {
            intellivue::AbsoluteTime* pabs =
              reinterpret_cast<intellivue::AbsoluteTime *>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!pabs)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into intellivue::AbsoluteTime. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            if (pabs->century != 0xFF
              || pabs->year != 0xFF
              || pabs->month != 0xFF
              || pabs->day != 0xFF
              || pabs->hour != 0xFF
              || pabs->minute != 0xFF
              || pabs->second != 0xFF
              || pabs->sec_fractions != 0xFF)
            {
              std::map<intellivue::OIDType, unsigned int>::iterator numeric_it;
              for (
                numeric_it = _map_handle_to_numeric_instance[unique_handle].begin();
                numeric_it != _map_handle_to_numeric_instance[unique_handle].end();
                numeric_it++)
              {
                if (!_numeric_meas_observed_value_response_instance_list.
                  at(numeric_it->second).
                  second->device_timestamp)
                {
                  _numeric_meas_observed_value_response_instance_list.
                    at(numeric_it->second).
                    second->device_timestamp =
                    reinterpret_cast<ice::Timespec *>(
                    DDS::Heap_malloc(sizeof(ice::Timespec)));
                  if (!_numeric_meas_observed_value_response_instance_list.
                    at(numeric_it->second).
                    second->device_timestamp)
                  {
                    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to "
                      "allocate memory for ice::Timespec");
                    return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
                  }
                }
                DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                  ConvertIntellivueAbsoluteTimeToDicesTimespec(
                  _numeric_meas_observed_value_response_instance_list.
                  at(numeric_it->second).
                  second->device_timestamp,
                  *pabs);
                if (status != DicesRcPhilipsIntellivueMP70::OK)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn <<
                    DicesRcPhilipsIntellivueMP70StatusMessage::
                    DicesRcPhilipsIntellivueMP70ToString(status));
                  return status;
                }
              }
            }
          }
            break;
          case NOM_ATTR_TIME_STAMP_REL:
          {
            intellivue::RelativeTime* prel =
              reinterpret_cast<intellivue::RelativeTime *>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (prel)
            {
              std::map<intellivue::OIDType, unsigned int>::iterator numeric_it;
              for (
                numeric_it = _map_handle_to_numeric_instance[unique_handle].begin();
                numeric_it != _map_handle_to_numeric_instance[unique_handle].end();
                numeric_it++)
              {
                if (!_numeric_meas_observed_value_response_instance_list.
                  at(numeric_it->second).second->device_relative_timestamp)
                {
                  _numeric_meas_observed_value_response_instance_list.
                    at(numeric_it->second).second->device_relative_timestamp =
                    reinterpret_cast<ice::Duration *>(
                    DDS::Heap_malloc(sizeof(ice::Duration)));
                  if (!_numeric_meas_observed_value_response_instance_list.
                    at(numeric_it->second).second->device_relative_timestamp)
                  {
                    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to "
                      "allocate memory for ice::Duration");
                    return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
                  }
                }
                DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                  ConvertIntellivueRelativeTimeToDicesDuration(
                  _numeric_meas_observed_value_response_instance_list.
                  at(numeric_it->second).second->device_relative_timestamp,
                  *prel);
                if (status != DicesRcPhilipsIntellivueMP70::OK)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn <<
                    DicesRcPhilipsIntellivueMP70StatusMessage::
                    DicesRcPhilipsIntellivueMP70ToString(status));
                  return status;
                }
              }
            }
          }
            break;
          case NOM_ATTR_ID_LABEL:
            {
              intellivue::TextId* ptextid =
                  reinterpret_cast<intellivue::TextId *>(
                  _extended_poll_response.pollReply.poll_info_list.value[ix].
                  poll_info.value[iy].attributes.value[iz].attribute_val);
              if (!ptextid)
              {
                LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                  "attribute_val into intellivue::TextId. attribute_id: "
                  << static_cast<int>(attribute_id));
                break;
              }

              std::string dices_vmo_label_string;
              DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::ConvertIntellivueTextIdToVMOLabelString(
                    &dices_vmo_label_string,
                    *ptextid);
              if (status != DicesRcPhilipsIntellivueMP70::OK)
              {
                LOG4CPLUS_WARN(root_logger, sfn <<
                  DicesRcPhilipsIntellivueMP70StatusMessage::
                  DicesRcPhilipsIntellivueMP70ToString(status));
              }

              std::map<intellivue::OIDType, unsigned int>::iterator numeric_it;
              for (
                   numeric_it = _map_handle_to_numeric_instance[unique_handle].begin();
                   numeric_it != _map_handle_to_numeric_instance[unique_handle].end();
                   numeric_it++)
              {
                if (strncmp(
                      _numeric_meas_context_response_instance_list.at(
                        numeric_it->second).second->vmo_label_string,
                      dices_vmo_label_string.c_str(),
                      ice::LONG_STRING_LEN) != 0)
                {
                  strncpy(
                        _numeric_meas_context_response_instance_list.at(
                          numeric_it->second).second->vmo_label_string,
                        dices_vmo_label_string.c_str(),
                        ice::LONG_STRING_LEN);

                  if (_numeric_meas_context_response_instance_list.at(
                        numeric_it->second).second->metric_id != 0)
                  {
                    _numeric_meas_context_response_instance_list.at(
                          numeric_it->second).first = DicesRcDriver::OK;
                  }
                }
              }
            }
            break;
          case NOM_ATTR_ID_LABEL_STRING:
          {
            intellivue::String* plabel =
              reinterpret_cast<intellivue::String *>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (plabel)
            {
              std::string label_string;
              for (int iindex = 0; iindex < plabel->length; iindex++)
              {
                uint8_t ch8 = '\0';
                uint16_t ch16 = plabel->value[iindex];
                // Convert to byte array
                uint8_t byte_0 = ch16 & 0x00ff;
                uint8_t byte_1 = ch16 >> 8;
                uint8_t buf[2] = { byte_0, byte_1 };

                ch16 = ntohs(*(reinterpret_cast<uint16_t*>(&buf[0])));

                DicesRcPhilipsIntellivueMP70 status =
                  IntellivueUtils::Convert16BitUnicodeToAscii(
                  ch16,
                  &ch8);
                if (status != DicesRcPhilipsIntellivueMP70::OK)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn <<
                    DicesRcPhilipsIntellivueMP70StatusMessage::
                    DicesRcPhilipsIntellivueMP70ToString(status));
                  return status;
                }
                label_string += static_cast<char>(ch8);
              }

              std::map<intellivue::OIDType, unsigned int>::iterator numeric_it;
              for (
                numeric_it = _map_handle_to_numeric_instance[unique_handle].begin();
                numeric_it != _map_handle_to_numeric_instance[unique_handle].end();
                numeric_it++)
              {
                if (strncmp(_numeric_meas_context_response_instance_list.
                  at(numeric_it->second).second->metric_info_label_string,
                  label_string.c_str(),
                  ice::LONG_STRING_LEN) != 0)
                {
                  strncpy(_numeric_meas_context_response_instance_list.
                    at(numeric_it->second).second->metric_info_label_string,
                    label_string.c_str(),
                    ice::LONG_STRING_LEN);
                  _numeric_meas_context_response_instance_list.
                    at(numeric_it->second).second->metric_info_label_string[
                    ice::LONG_STRING_LEN] = '\0';

                  if (_numeric_meas_context_response_instance_list.
                    at(numeric_it->second).second->metric_id != 0)
                  {
                    _numeric_meas_context_response_instance_list.
                      at(numeric_it->second).first = DicesRcDriver::OK;
                  }
                }
              }
            }
          }
            break;
          case NOM_ATTR_DISP_RES:
          {
            intellivue::DispResolution* pdisp_res =
              reinterpret_cast<intellivue::DispResolution *>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (pdisp_res)
            {
              std::map<intellivue::OIDType, unsigned int>::iterator numeric_it;
              for (
                numeric_it = _map_handle_to_numeric_instance[unique_handle].begin();
                numeric_it != _map_handle_to_numeric_instance[unique_handle].end();
                numeric_it++)
              {
                if (!_numeric_meas_context_response_instance_list.at(
                  numeric_it->second).second->display_resolution)
                {
                  _numeric_meas_context_response_instance_list.at(
                    numeric_it->second).second->display_resolution =
                    reinterpret_cast<ice::DispResolution*>(
                    DDS::Heap_malloc(sizeof(ice::DispResolution)));
                  if (!_numeric_meas_context_response_instance_list.at(
                    numeric_it->second).second->display_resolution)
                  {
                    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to "
                      "allocate memory for ice::DispResolution");
                    return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
                  }
                }

                if (_numeric_meas_context_response_instance_list.at(
                  numeric_it->second).second->display_resolution->pre_point
                  != static_cast<ice::INTU8>(pdisp_res->pre_point))
                {
                  _numeric_meas_context_response_instance_list.at(
                    numeric_it->second).second->display_resolution->
                    pre_point = static_cast<ice::INTU8>(pdisp_res->pre_point);
                  if (_numeric_meas_context_response_instance_list.at(
                    numeric_it->second).second->metric_id != 0)
                  {
                    _numeric_meas_context_response_instance_list.at(
                      numeric_it->second).first = DicesRcDriver::OK;
                  }
                }
                if (_numeric_meas_context_response_instance_list.at(
                  numeric_it->second).second->display_resolution->post_point
                  != pdisp_res->post_point)
                {
                  _numeric_meas_context_response_instance_list.at(
                    numeric_it->second).second->display_resolution->
                    post_point = pdisp_res->post_point;
                  if (_numeric_meas_context_response_instance_list.at(
                    numeric_it->second).second->metric_id != 0)
                  {
                    _numeric_meas_context_response_instance_list.at(
                      numeric_it->second).first = DicesRcDriver::OK;
                  }
                }
              }
            }
          }
            break;
          case NOM_ATTR_COLOR:
          {
            intellivue::SimpleColour* pcolor =
              reinterpret_cast<intellivue::SimpleColour *>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);

            if (pcolor)
            {
              ice::SimpleColor dices_color = ice::col_black;

              DicesRcPhilipsIntellivueMP70 status =
                IntellivueUtils::ConvertIntellivueColorToDicesColor(
                &dices_color,
                *pcolor);
              if (status != DicesRcPhilipsIntellivueMP70::OK)
              {
                LOG4CPLUS_ERROR(root_logger, sfn <<
                  DicesRcPhilipsIntellivueMP70StatusMessage::
                  DicesRcPhilipsIntellivueMP70ToString(status));
                return status;
              }

              std::map<intellivue::OIDType, unsigned int>::iterator numeric_it;
              for (
                numeric_it = _map_handle_to_numeric_instance[unique_handle].begin();
                numeric_it != _map_handle_to_numeric_instance[unique_handle].end();
                numeric_it++)
              {
                if (!_numeric_meas_context_response_instance_list.at(
                  numeric_it->second).second->color)
                {
                  _numeric_meas_context_response_instance_list.at(
                    numeric_it->second).
                    second->color = reinterpret_cast<ice::SimpleColor*>(
                    DDS::Heap_malloc(sizeof(ice::SimpleColor)));
                  if (!_numeric_meas_context_response_instance_list.at(
                    numeric_it->second).
                    second->color)
                  {
                    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to "
                      "allocate memory for ice::SimpleColor");
                    return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
                  }
                }

                if (*_numeric_meas_context_response_instance_list.at(
                  numeric_it->second).second->color != dices_color)
                {
                  *_numeric_meas_context_response_instance_list.at(
                    numeric_it->second).second->color = dices_color;
                  if (_numeric_meas_context_response_instance_list.at(
                    numeric_it->second).second->metric_id != 0)
                  {
                    _numeric_meas_context_response_instance_list.at(
                      numeric_it->second).first = DicesRcDriver::OK;
                  }
                }
              }
            }
          }
            break;
          case NOM_ATTR_METRIC_SPECN:
          {
            intellivue::MetricSpec* pmspec =
              reinterpret_cast<intellivue::MetricSpec *>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);

            if (pmspec)
            {
              ice::MetricAccess dices_access = 0;
              DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                ConvertIntellivueMetricAccessToDicesMetricAccess(
                &dices_access,
                pmspec->access);
              if (status != DicesRcPhilipsIntellivueMP70::OK)
              {
                LOG4CPLUS_ERROR(root_logger, sfn <<
                  DicesRcPhilipsIntellivueMP70StatusMessage::
                  DicesRcPhilipsIntellivueMP70ToString(status));
                return status;
              }

              if (_numeric_meas_context_response_instance_list.at(
                _map_handle_to_numeric_instance[unique_handle].begin()->second).
                second->metric_specification.access != dices_access)
              {
                _numeric_meas_context_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle].begin()->second).
                  second->metric_specification.access = dices_access;
                if (_numeric_meas_context_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle].begin()->second).
                  second->metric_id != 0)
                {
                  _numeric_meas_context_response_instance_list.at(
                    _map_handle_to_numeric_instance[unique_handle].begin()->
                    second).first = DicesRcDriver::OK;
                }
              }
              ice::MetricCategory dices_category =
                ice::MetricCategory::auto_measurement;
              status = IntellivueUtils::
                ConvertIntellivueMetricCategoryToDicesMetricCategory(
                &dices_category,
                pmspec->category);
              if (status != DicesRcPhilipsIntellivueMP70::OK)
              {
                LOG4CPLUS_ERROR(root_logger, sfn <<
                  DicesRcPhilipsIntellivueMP70StatusMessage::
                  DicesRcPhilipsIntellivueMP70ToString(status));
                return status;
              }
              if (_numeric_meas_context_response_instance_list.at(
                _map_handle_to_numeric_instance[unique_handle].begin()->second).
                second->metric_specification.category != dices_category)
              {
                _numeric_meas_context_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle].begin()->second).
                  second->metric_specification.category = dices_category;
                if (_numeric_meas_context_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle].begin()->second).
                  second->metric_id != 0)
                {
                  _numeric_meas_context_response_instance_list.at(
                    _map_handle_to_numeric_instance[unique_handle].begin()->
                    second).first = DicesRcDriver::OK;
                }
              }
              // MetricRelevance cannot be set properly. Intellivue
              // documentation states that MetricRelevance is for internal use
              // only. There is no way to convert intellivue bits to DICES
              // bits.
              ice::Duration dices_rel_time = { 0 };
              status = IntellivueUtils::
                ConvertIntellivueRelativeTimeToDicesDuration(
                &dices_rel_time,
                pmspec->update_period);
              if (status != DicesRcPhilipsIntellivueMP70::OK)
              {
                LOG4CPLUS_ERROR(root_logger, sfn <<
                  DicesRcPhilipsIntellivueMP70StatusMessage::
                  DicesRcPhilipsIntellivueMP70ToString(status));
                return status;
              }
              if (_numeric_meas_context_response_instance_list.at(
                _map_handle_to_numeric_instance[unique_handle].begin()->second).
                second->metric_specification.update_period.seconds
                != dices_rel_time.seconds)
              {
                _numeric_meas_context_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle].begin()->second).
                  second->metric_specification.update_period.seconds =
                  dices_rel_time.seconds;
                if (_numeric_meas_context_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle].begin()->second).
                  second->metric_id != 0)
                {
                  _numeric_meas_context_response_instance_list.at(
                    _map_handle_to_numeric_instance[unique_handle].begin()->
                    second).first = DicesRcDriver::OK;
                }
              }
              if (_numeric_meas_context_response_instance_list.at(
                _map_handle_to_numeric_instance[unique_handle].begin()->second).
                second->metric_specification.update_period.nanoseconds
                != dices_rel_time.nanoseconds)
              {
                _numeric_meas_context_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle].begin()->second).
                  second->metric_specification.update_period.nanoseconds =
                  dices_rel_time.nanoseconds;
                if (_numeric_meas_context_response_instance_list.at(
                  _map_handle_to_numeric_instance[unique_handle].begin()->second).
                  second->metric_id != 0)
                {
                  _numeric_meas_context_response_instance_list.at(
                    _map_handle_to_numeric_instance[unique_handle].begin()->second).
                    first = DicesRcDriver::OK;
                }
              }

              if (pmspec->structure.ms_comp_no != 0)
              {
                while (_map_handle_to_numeric_instance[unique_handle].size() <
                  pmspec->structure.ms_comp_no)
                {
                  intellivue::Handle new_handle = 1;
                  DicesRcPhilipsIntellivueMP70 status = GenerateNewHandle(
                    &new_handle);
                  if (status != DicesRcPhilipsIntellivueMP70::OK)
                  {
                    LOG4CPLUS_ERROR(root_logger, sfn <<
                      DicesRcPhilipsIntellivueMP70StatusMessage::
                      DicesRcPhilipsIntellivueMP70ToString(status));
                    return status;
                  }

                  if (_numeric_vector_max_index
                      >= _numeric_meas_context_response_instance_list.size()
                      ||_numeric_vector_max_index
                      >= _numeric_sett_context_response_instance_list.size()
                      ||_numeric_vector_max_index
                      >= _numeric_calc_context_response_instance_list.size())
                  {
                    LOG4CPLUS_INFO(root_logger, sfn << "The maximum number of numeric context "
                                                       "instances are already in use for meas, sett and calc instance lists. "
                                                       "Inserting additional instances.");

                    unsigned int nu_meas_inst_diff = _numeric_vector_max_index
                        - _numeric_meas_context_response_instance_list.size();
                    for (unsigned int inst_count = 0;
                         inst_count <= nu_meas_inst_diff;
                         inst_count++)
                    {
                      std::pair<DicesRcDriver, ice::NumericContext*> nu_meas_ctxt_pair(
                            DicesRcDriver::NO_NEW_DATA,
                            ice::NumericContextTypeSupport::create_data());
                      if (!nu_meas_ctxt_pair.second)
                      {
                        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for numeric measurement context instance");
                        return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
                      }
                      try
                      {
                        _numeric_meas_context_response_instance_list.push_back(nu_meas_ctxt_pair);
                      }
                      catch(std::exception& ex)
                      {
                        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                            "numeric measurement context pair onto vector. " << ex.what());
                        return DicesRcPhilipsIntellivueMP70::FAIL;
                      }
                    }

                    unsigned int nu_sett_inst_diff = _numeric_vector_max_index
                        - _numeric_sett_context_response_instance_list.size();
                    for (unsigned int inst_count = 0;
                         inst_count <= nu_sett_inst_diff;
                         inst_count++)
                    {
                      std::pair<DicesRcDriver, ice::NumericContext*> nu_sett_ctxt_pair(
                            DicesRcDriver::NO_NEW_DATA,
                            ice::NumericContextTypeSupport::create_data());
                      if (!nu_sett_ctxt_pair.second)
                      {
                        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for numeric setting context instance");
                        return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
                      }
                      try
                      {
                        _numeric_sett_context_response_instance_list.push_back(nu_sett_ctxt_pair);
                      }
                      catch(std::exception& ex)
                      {
                        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                            "numeric setting context pair onto vector. " << ex.what());
                        return DicesRcPhilipsIntellivueMP70::FAIL;
                      }
                    }

                    unsigned int nu_calc_inst_diff = _numeric_vector_max_index
                        - _numeric_calc_context_response_instance_list.size();
                    for (unsigned int inst_count = 0;
                         inst_count <= nu_calc_inst_diff;
                         inst_count++)
                    {
                      std::pair<DicesRcDriver, ice::NumericContext*> nu_calc_ctxt_pair(
                            DicesRcDriver::NO_NEW_DATA,
                            ice::NumericContextTypeSupport::create_data());
                      if (!nu_calc_ctxt_pair.second)
                      {
                        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for numeric calculation context instance");
                        return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
                      }
                      try
                      {
                        _numeric_calc_context_response_instance_list.push_back(nu_calc_ctxt_pair);
                      }
                      catch(std::exception& ex)
                      {
                        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                            "numeric calculation context pair onto vector. " << ex.what());
                        return DicesRcPhilipsIntellivueMP70::FAIL;
                      }
                    }
                  }
                  if (_numeric_vector_max_index
                      >= _numeric_meas_observed_value_response_instance_list.size()
                      ||_numeric_vector_max_index
                      >= _numeric_sett_observed_value_response_instance_list.size()
                      ||_numeric_vector_max_index
                      >= _numeric_calc_observed_value_response_instance_list.size())
                  {
                    LOG4CPLUS_INFO(root_logger, sfn << "The maximum number of numeric observed value "
                      "instances are already in use for meas, sett and calc instance lists. "
                      "Inserting additional instances.");

                    unsigned int nu_meas_inst_diff = _numeric_vector_max_index
                        - _numeric_meas_observed_value_response_instance_list.size();
                    for (unsigned int inst_count = 0;
                         inst_count <= nu_meas_inst_diff;
                         inst_count++)
                    {
                      std::pair<DicesRcDriver, ice::NumericObservedValue*> nu_meas_obs_pair(
                            DicesRcDriver::NO_NEW_DATA,
                            ice::NumericObservedValueTypeSupport::create_data());
                      if (!nu_meas_obs_pair.second)
                      {
                        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for numeric "
                                                            "measurement observed value instance");
                        return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
                      }
                      try
                      {
                        _numeric_meas_observed_value_response_instance_list.push_back(nu_meas_obs_pair);
                      }
                      catch(std::exception& ex)
                      {
                        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                            "numeric measurement observed value pair onto vector. " << ex.what());
                        return DicesRcPhilipsIntellivueMP70::FAIL;
                      }
                    }

                    unsigned int nu_sett_inst_diff = _numeric_vector_max_index
                        - _numeric_sett_observed_value_response_instance_list.size();
                    for (unsigned int inst_count = 0;
                         inst_count <= nu_sett_inst_diff;
                         inst_count++)
                    {
                      std::pair<DicesRcDriver, ice::NumericObservedValue*> nu_sett_obs_pair(
                            DicesRcDriver::NO_NEW_DATA,
                            ice::NumericObservedValueTypeSupport::create_data());
                      if (!nu_sett_obs_pair.second)
                      {
                        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for numeric setting "
                                                            "observed value instance");
                        return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
                      }
                      try
                      {
                        _numeric_sett_observed_value_response_instance_list.push_back(nu_sett_obs_pair);
                      }
                      catch(std::exception& ex)
                      {
                        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                            "numeric setting observed value pair onto vector. " << ex.what());
                        return DicesRcPhilipsIntellivueMP70::FAIL;
                      }
                    }

                    unsigned int nu_calc_inst_diff = _numeric_vector_max_index
                        - _numeric_calc_observed_value_response_instance_list.size();
                    for (unsigned int inst_count = 0;
                         inst_count <= nu_calc_inst_diff;
                         inst_count++)
                    {
                      std::pair<DicesRcDriver, ice::NumericObservedValue*> nu_calc_obs_pair(
                            DicesRcDriver::NO_NEW_DATA,
                            ice::NumericObservedValueTypeSupport::create_data());
                      if (!nu_calc_obs_pair.second)
                      {
                        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for numeric "
                                                            "calculation observed value instance");
                        return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
                      }
                      try
                      {
                        _numeric_calc_observed_value_response_instance_list.push_back(nu_calc_obs_pair);
                      }
                      catch(std::exception& ex)
                      {
                        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                            "numeric calculation observed value pair onto vector. " << ex.what());
                        return DicesRcPhilipsIntellivueMP70::FAIL;
                      }
                    }
                  }

                  std::pair < std::map<intellivue::Handle,
                    unsigned int>::iterator, bool> ret_1 =
                    _map_handle_to_numeric_instance[unique_handle].insert(
                    std::pair<intellivue::Handle, unsigned int>(
                    new_handle,
                    _numeric_vector_max_index++));
                  if (!ret_1.second)
                  {
                    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert generated "
                      "handle and vector index into map.");
                    return DicesRcPhilipsIntellivueMP70::FAIL;
                  }

                  DDS::ReturnCode_t retcode = ice::NumericContextTypeSupport::
                    copy_data(
                    _numeric_meas_context_response_instance_list.at(
                    _map_handle_to_numeric_instance[unique_handle][new_handle]).
                    second,
                    _numeric_meas_context_response_instance_list.at(
                    _map_handle_to_numeric_instance[unique_handle].begin()->second).
                    second);
                  if (retcode != DDS::RETCODE_OK)
                  {
                    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to copy data "
                      "for NumericContext");
                    return DicesRcPhilipsIntellivueMP70::FAIL;
                  }

                  retcode = ice::NumericObservedValueTypeSupport::copy_data(
                    _numeric_meas_observed_value_response_instance_list.at(
                    _map_handle_to_numeric_instance[unique_handle][new_handle]).
                    second,
                    _numeric_meas_observed_value_response_instance_list.at(
                    _map_handle_to_numeric_instance[unique_handle].begin()->second).
                    second);
                  if (retcode != DDS::RETCODE_OK)
                  {
                    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to copy data "
                      "for NumericObservedValue");
                    return DicesRcPhilipsIntellivueMP70::FAIL;
                  }

                  _numeric_meas_context_response_instance_list.at(
                    _map_handle_to_numeric_instance[unique_handle][new_handle]).
                    second->handle = new_handle;
                  if (_numeric_meas_context_response_instance_list.at(
                    _map_handle_to_numeric_instance[unique_handle][new_handle]).
                    second->metric_id != 0)
                  {
                    _numeric_meas_context_response_instance_list.at(
                      _map_handle_to_numeric_instance[unique_handle][new_handle]).
                      first = DicesRcDriver::OK;
                  }

                  _numeric_meas_observed_value_response_instance_list.at(
                    _map_handle_to_numeric_instance[unique_handle][new_handle]).
                    second->handle = new_handle;
                }
              }
            }
          }
            break;
          default:
            break;
        }
      }
    }
  }

  for (
    int ix = 0;
    ix < _numeric_meas_context_response_instance_list.size();
    ix++)
  {
    // For all context dds instances that have changed, increment context
    // sequence number and set for the same number in observed value.
    if (_numeric_meas_context_response_instance_list.at(ix).first
      == DicesRcDriver::OK)
    {
      _numeric_meas_context_response_instance_list.at(ix).second->
        context_seq_number++;
      _numeric_meas_observed_value_response_instance_list.at(ix).second->
        context_seq_number = _numeric_meas_context_response_instance_list.
        at(ix).second->context_seq_number;
    }
  }
  for (int ix = 0; ix < _numeric_meas_context_response_instance_list.size(); ix++)
  {
    switch (_numeric_meas_context_response_instance_list.at(ix).second->
      metric_specification.category)
    {
      case ice::MetricCategory::auto_calculation:
      case ice::MetricCategory::manual_calculation:
      {
        DDS::ReturnCode_t retcode = ice::NumericContextTypeSupport::copy_data(
          _numeric_calc_context_response_instance_list.at(ix).second,
          _numeric_meas_context_response_instance_list.at(ix).second);
        if (retcode != DDS::RETCODE_OK)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to copy data from "
            "numeric measurement context to numeric calculation context");
          break;
        }
        retcode = ice::NumericObservedValueTypeSupport::copy_data(
          _numeric_calc_observed_value_response_instance_list.at(ix).second,
          _numeric_meas_observed_value_response_instance_list.at(ix).second);
        if (retcode != DDS::RETCODE_OK)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to copy data from "
            "numeric measurement observed value to numeric calculation "
            "observed value");
          break;
        }
        _numeric_calc_context_response_instance_list.at(ix).first =
          _numeric_meas_context_response_instance_list.at(ix).first;
        _numeric_calc_observed_value_response_instance_list.at(ix).first =
          _numeric_meas_observed_value_response_instance_list.at(ix).first;
        if (_numeric_meas_context_response_instance_list.at(ix).first
          == DicesRcDriver::OK)
        {
          // Do not publish measurement.
          _numeric_meas_context_response_instance_list.at(ix).first =
            DicesRcDriver::NO_NEW_DATA;
        }
        if (_numeric_meas_observed_value_response_instance_list.at(ix).first
          == DicesRcDriver::OK)
        {
          // Do not publish measurement.
          _numeric_meas_observed_value_response_instance_list.at(ix).first =
            DicesRcDriver::NO_NEW_DATA;
        }
      }
        break;
      case ice::MetricCategory::auto_setting:
      case ice::MetricCategory::manual_setting:
      {
        DDS::ReturnCode_t retcode = ice::NumericContextTypeSupport::copy_data(
          _numeric_sett_context_response_instance_list.at(ix).second,
          _numeric_meas_context_response_instance_list.at(ix).second);
        if (retcode != DDS::RETCODE_OK)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to copy data from "
            "numeric measurement context to numeric setting context");
          break;
        }
        retcode = ice::NumericObservedValueTypeSupport::copy_data(
          _numeric_sett_observed_value_response_instance_list.at(ix).second,
          _numeric_meas_observed_value_response_instance_list.at(ix).second);
        if (retcode != DDS::RETCODE_OK)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to copy data from "
            "numeric measurement observed value to numeric setting "
            "observed value");
          break;
        }
        _numeric_sett_context_response_instance_list.at(ix).first =
          _numeric_meas_context_response_instance_list.at(ix).first;
        _numeric_sett_observed_value_response_instance_list.at(ix).first =
          _numeric_meas_observed_value_response_instance_list.at(ix).first;
        if (_numeric_meas_context_response_instance_list.at(ix).first
          == DicesRcDriver::OK)
        {
          // Do not publish measurement.
          _numeric_meas_context_response_instance_list.at(ix).first =
            DicesRcDriver::NO_NEW_DATA;
        }
        if (_numeric_meas_observed_value_response_instance_list.at(ix).first
          == DicesRcDriver::OK)
        {
          // Do not publish measurement.
          _numeric_meas_observed_value_response_instance_list.at(ix).first =
            DicesRcDriver::NO_NEW_DATA;
        }
      }
        break;
      case ice::MetricCategory::mcat_unspec:
        LOG4CPLUS_WARN(root_logger, sfn << "MetricCategory is unspecified for "
          "NumericContext at index (" << ix << ")");
        break;
      default:
        // Must be a measurement
        break;
    }
  }
  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 DDPhilipsIntellivueMP70Parser::
SetExtendedRTSAMapping()
{
  static const char* sfn = "DDPhilipsIntellivueMP70Parser::"
                           "SetExtendedRTSAMapping() ";

  intellivue::GlbHandle glb_handle = {
    _extended_poll_response.actionresult.managed_object.m_obj_inst.
    context_id,
    _extended_poll_response.actionresult.managed_object.m_obj_inst.
    handle
  };

  for (
       int ix = 0;
       ix < _extended_poll_response.pollReply.poll_info_list.count;
       ix++)
  {
    if (!_extended_poll_response.pollReply.poll_info_list.value)
    {
      LOG4CPLUS_WARN(root_logger, sfn << "SingleContextPoll array in "
                                         "poll_info_list is a null pointer");
      break;
    }
    intellivue::MdsContext single_context_poll_context_id =
        _extended_poll_response.pollReply.poll_info_list.value[ix].
        context_id;

    for (
         int iy = 0;
         iy < _extended_poll_response.pollReply.poll_info_list.value[ix].
         poll_info.count;
         iy++)
    {
      if (!_extended_poll_response.pollReply.poll_info_list.value[ix].
          poll_info.value)
      {
        LOG4CPLUS_WARN(root_logger, sfn << "ObservationPoll array in "
                                           "poll_info is a null pointer");
        break;
      }

      intellivue::AttributeList attr_list = _extended_poll_response.
          pollReply.poll_info_list.value[ix].poll_info.value[iy].attributes;
      intellivue::Handle obj_handle = _extended_poll_response.pollReply.poll_info_list.
          value[ix].poll_info.value[iy].obj_handle;
      std::set<std::tuple<intellivue::OIDType, uint16_t>> set_arr_info;

      for (int iz = 0; iz < attr_list.count; iz++)
      {
        if (!attr_list.value)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "AVAType array in "
                                             "attributes is a null pointer");
          break;
        }

        intellivue::OIDType attribute_id = attr_list.value[iz].attribute_id;

        switch (attribute_id)
        {
          case NOM_ATTR_SA_VAL_OBS:
            {
              intellivue::SaObsValue* psa_obs_val =
                  reinterpret_cast<intellivue::SaObsValue *>(
                    attr_list.value[iz].attribute_val);

              if (!psa_obs_val)
              {
                LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                                                   "attribute_val into "
                                                   "SaObsValue. attribute_id: "
                               << static_cast<int>(attribute_id));
                break;
              }
              std::tuple<intellivue::OIDType, uint16_t> arr_info_pair(
                    psa_obs_val->physio_id,
                    psa_obs_val->array.length);
              set_arr_info.insert(arr_info_pair);
            }
            break;
          case NOM_ATTR_SA_CMPD_VAL_OBS:
            {
              intellivue::SaObsValueCmp* psa_obs_val_cmp =
                  reinterpret_cast<intellivue::SaObsValueCmp *>(
                    _extended_poll_response.pollReply.poll_info_list.value[ix].
                    poll_info.value[iy].attributes.value[iz].attribute_val);

              if (!psa_obs_val_cmp)
              {
                LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                                                   "attribute_val into "
                                                   "SaObsValueCmp. "
                                                   "attribute_id: "
                               << static_cast<int>(attribute_id));
                break;
              }

              for (int ia = 0; ia < psa_obs_val_cmp->count; ia++)
              {
                if (!psa_obs_val_cmp->value)
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "Pointer to SaObsValue "
                                                     "is null. attribute_id: "
                                 << static_cast<int>(attribute_id));
                  break;
                }
                std::tuple<intellivue::OIDType, uint16_t> arr_info_pair(
                      psa_obs_val_cmp->value[ia].physio_id,
                      psa_obs_val_cmp->value[ia].array.length);
                set_arr_info.insert(arr_info_pair);
              }
            }
            break;
        }
      }

      std::set<std::tuple<intellivue::OIDType, uint16_t>>::iterator it;
      for (it=set_arr_info.begin(); it!=set_arr_info.end(); ++it)
      {
        std::tuple<
            intellivue::MdsContext,
            intellivue::Handle,
            intellivue::MdsContext,
            intellivue::Handle,
            intellivue::OIDType,
            uint16_t>
            unique_handle(
              glb_handle.context_id,
              glb_handle.handle,
              single_context_poll_context_id,
              obj_handle,
              std::get<0>(*it),
              std::get<1>(*it));

        if (_map_handle_to_rtsa_instance.count(unique_handle) == 0)
        {
          if (_rtsa_vector_max_index + 1
              >= _rtsa_meas_context_response_instance_list.size()
              ||_rtsa_vector_max_index + 1
              >= _rtsa_sett_context_response_instance_list.size()
              ||_rtsa_vector_max_index + 1
              >= _rtsa_calc_context_response_instance_list.size())
          {
            LOG4CPLUS_INFO(root_logger, sfn << "The maximum number of rtsa context "
              "instances are already in use for meas, sett and calc instance lists. "
              "Inserting additional instances.");

            unsigned int rtsa_meas_inst_diff = _rtsa_vector_max_index + 1
                - _rtsa_meas_context_response_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= rtsa_meas_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::RTSAContext*> rtsa_meas_ctxt_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::RTSAContextTypeSupport::create_data());
              if (!rtsa_meas_ctxt_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for rtsa measurement context instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _rtsa_meas_context_response_instance_list.push_back(rtsa_meas_ctxt_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "rtsa measurement context pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }

            unsigned int rtsa_sett_inst_diff = _rtsa_vector_max_index + 1
                - _rtsa_sett_context_response_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= rtsa_sett_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::RTSAContext*> rtsa_sett_ctxt_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::RTSAContextTypeSupport::create_data());
              if (!rtsa_sett_ctxt_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for rtsa setting context instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _rtsa_sett_context_response_instance_list.push_back(rtsa_sett_ctxt_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "rtsa setting context pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }

            unsigned int rtsa_calc_inst_diff = _rtsa_vector_max_index + 1
                - _rtsa_calc_context_response_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= rtsa_calc_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::RTSAContext*> rtsa_calc_ctxt_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::RTSAContextTypeSupport::create_data());
              if (!rtsa_calc_ctxt_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for rtsa calculation context instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _rtsa_calc_context_response_instance_list.push_back(rtsa_calc_ctxt_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "rtsa calculation context pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }
          }
          if (_rtsa_vector_max_index + 1
              >= _rtsa_meas_observed_value_response_instance_list.size()
              ||_rtsa_vector_max_index + 1
              >= _rtsa_sett_observed_value_response_instance_list.size()
              ||_rtsa_vector_max_index + 1
              >= _rtsa_calc_observed_value_response_instance_list.size())
          {
            LOG4CPLUS_INFO(root_logger, sfn << "The maximum number of rtsa observed value "
              "instances are already in use for meas, sett and calc instance lists. "
              "Inserting additional instances.");

            unsigned int rtsa_meas_inst_diff = _rtsa_vector_max_index + 1
                - _rtsa_meas_observed_value_response_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= rtsa_meas_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::RTSAObservedValue*> rtsa_meas_obs_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::RTSAObservedValueTypeSupport::create_data());
              if (!rtsa_meas_obs_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for rtsa measurement "
                                                    "observed value instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _rtsa_meas_observed_value_response_instance_list.push_back(rtsa_meas_obs_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "rtsa measurement observed value pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }

            unsigned int rtsa_sett_inst_diff = _rtsa_vector_max_index + 1
                - _rtsa_sett_observed_value_response_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= rtsa_sett_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::RTSAObservedValue*> rtsa_sett_obs_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::RTSAObservedValueTypeSupport::create_data());
              if (!rtsa_sett_obs_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for rtsa setting observed value instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _rtsa_sett_observed_value_response_instance_list.push_back(rtsa_sett_obs_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "rtsa setting observed value pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }

            unsigned int rtsa_calc_inst_diff = _rtsa_vector_max_index + 1
                - _rtsa_calc_observed_value_response_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= rtsa_calc_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::RTSAObservedValue*> rtsa_calc_obs_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::RTSAObservedValueTypeSupport::create_data());
              if (!rtsa_calc_obs_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for rtsa calculation observed value instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _rtsa_calc_observed_value_response_instance_list.push_back(rtsa_calc_obs_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "rtsa calculation observed value pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }
          }
          ice::RTSAContext* context_instance = nullptr;
          try
          {
            context_instance = _rtsa_meas_context_response_instance_list.at(
                  _rtsa_vector_max_index).second;
            if (!context_instance)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "RTSA context "
                                                  "instance is a null pointer "
                                                  "at index: "
                              << _rtsa_vector_max_index);
              return DicesRcPhilipsIntellivueMP70::FAIL;
            }
          }
          catch (std::exception& ex)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get RTSA context "
                                                "instance from instance list "
                                                "at index: "
                            << _rtsa_vector_max_index << ". " << ex.what());
            return DicesRcPhilipsIntellivueMP70::FAIL;
          }
          ice::RTSAObservedValue* obs_val_instance = nullptr;
          try
          {
            obs_val_instance = _rtsa_meas_observed_value_response_instance_list.at(
                  _rtsa_vector_max_index).second;
            if (!obs_val_instance)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "RTSA observed value "
                                                  "instance is a null pointer "
                                                  "at index: "
                              << _rtsa_vector_max_index);
              return DicesRcPhilipsIntellivueMP70::FAIL;
            }
          }
          catch (std::exception& ex)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get RTSA observed "
                                                "value instance from instance "
                                                "list at index: "
                            << _rtsa_vector_max_index << ". " << ex.what());
            return DicesRcPhilipsIntellivueMP70::FAIL;
          }
          if (context_instance->handle == 0 && obs_val_instance->handle == 0)
          {
            // Generate new rtsa handle
            intellivue::Handle new_handle = 0;
            DicesRcPhilipsIntellivueMP70 status = GenerateNewHandle(
                  &new_handle);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                              DicesRcPhilipsIntellivueMP70StatusMessage::
                              DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }
            // Set new handle for this instance.
            context_instance->handle = new_handle;
            obs_val_instance->handle = new_handle;

            if (_vmd_instance_list.size() > 0)
            {
              context_instance->parent_handle =
                  _vmd_instance_list.at(0).second->handle;
              obs_val_instance->parent_handle =
                  _vmd_instance_list.at(0).second->handle;
            }

            std::map<intellivue::Handle, unsigned int> handle_to_index;
            std::pair < std::map<intellivue::Handle, unsigned int>::iterator, bool> ret_1 =
                handle_to_index.insert(std::pair<intellivue::Handle, unsigned int>(
                                         new_handle,
                                         _rtsa_vector_max_index));
            // Each RTSA will have two indeces.
            _rtsa_vector_max_index+=2;
            if (!ret_1.second)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert generated "
                                                  "handle and vector index "
                                                  "into map.");
              return DicesRcPhilipsIntellivueMP70::FAIL;
            }

            std::pair <
                std::map<
                std::tuple<
                intellivue::MdsContext,
                intellivue::Handle,
                intellivue::MdsContext,
                intellivue::Handle,
                intellivue::OIDType,
                uint16_t>,
                std::map < intellivue::Handle, unsigned int>>::iterator, bool> ret_2 =
                _map_handle_to_rtsa_instance.insert(
                  std::pair<
                  std::tuple<
                  intellivue::MdsContext,
                  intellivue::Handle,
                  intellivue::MdsContext,
                  intellivue::Handle,
                  intellivue::OIDType,
                  uint16_t>,
                  std::map < intellivue::Handle, unsigned int>>(
                    unique_handle,
                    handle_to_index));
            if (!ret_2.second)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert unique "
                                                  "handle and handle and "
                                                  "vector index map into map.");
              return DicesRcPhilipsIntellivueMP70::FAIL;
            }
          }
        }
      }
    }
  }

  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 DDPhilipsIntellivueMP70Parser::
SetExtendedRTSAResponseData()
{
  static const char* sfn = "DDPhilipsIntellivueMP70Parser::"
                           "SetExtendedRTSAResponseData() ";

  DicesRcPhilipsIntellivueMP70 status = SetExtendedRTSAMapping();
  if (status != DicesRcPhilipsIntellivueMP70::OK) return status;

  intellivue::GlbHandle glb_handle = {
    _extended_poll_response.actionresult.managed_object.m_obj_inst.
    context_id,
    _extended_poll_response.actionresult.managed_object.m_obj_inst.
    handle
  };

  for (
       int ix = 0;
       ix < _extended_poll_response.pollReply.poll_info_list.count;
       ix++)
  {
    if (!_extended_poll_response.pollReply.poll_info_list.value)
    {
      LOG4CPLUS_WARN(root_logger, sfn << "SingleContextPoll array in "
                                         "poll_info_list is a null pointer");
      break;
    }
    intellivue::MdsContext single_context_poll_context_id =
        _extended_poll_response.pollReply.poll_info_list.value[ix].
        context_id;

    for (
         int iy = 0;
         iy < _extended_poll_response.pollReply.poll_info_list.value[ix].
         poll_info.count;
         iy++)
    {
      if (!_extended_poll_response.pollReply.poll_info_list.value[ix].
          poll_info.value)
      {
        LOG4CPLUS_WARN(root_logger, sfn << "ObservationPoll array in "
                                           "poll_info is a null pointer");
        break;
      }

      intellivue::AttributeList attr_list = _extended_poll_response.
          pollReply.poll_info_list.value[ix].poll_info.value[iy].attributes;
      intellivue::Handle obj_handle = _extended_poll_response.pollReply.
          poll_info_list.value[ix].poll_info.value[iy].obj_handle;
      std::set<std::tuple<intellivue::OIDType, uint16_t>> set_arr_info;

      for (int iz = 0; iz < attr_list.count; iz++)
      {
        if (!attr_list.value)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "AVAType array in "
                                             "attributes is a null pointer");
          break;
        }

        intellivue::OIDType attribute_id = attr_list.value[iz].attribute_id;

        switch (attribute_id)
        {
          case NOM_ATTR_SA_SPECN:
            {
              intellivue::SaSpec* psa_specn =
                  reinterpret_cast<intellivue::SaSpec *>(
                    attr_list.value[iz].attribute_val);
              if (!psa_specn)
              {
                LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                                                   "attribute_val into "
                                                   "intellivue::SaSpec. "
                                                   "attribute_id: "
                               << static_cast<int>(attribute_id));
                break;
              }
              const int kbits_per_byte = 8;
              uint16_t array_size = psa_specn->array_size *
                  (psa_specn->sample_type.sample_size / kbits_per_byte);

              // The physio_id is unknown, so we need to search for one.
              for (std::map<
                   std::tuple<
                   intellivue::MdsContext,
                   intellivue::Handle,
                   intellivue::MdsContext,
                   intellivue::Handle,
                   intellivue::OIDType,
                   uint16_t
                   >,
                   std::map<
                   intellivue::Handle,
                   unsigned int
                   >>::iterator it=_map_handle_to_rtsa_instance.begin();
                   it!=_map_handle_to_rtsa_instance.end();
                   ++it)
              {
                if (std::get<0>(it->first) == glb_handle.context_id
                    && std::get<1>(it->first) == glb_handle.handle
                    && std::get<2>(it->first) == single_context_poll_context_id
                    && std::get<3>(it->first) == obj_handle
                    && std::get<5>(it->first) == array_size)
                {
                  std::tuple<intellivue::OIDType, uint16_t> arr_info_pair(
                        std::get<4>(it->first), array_size);
                  set_arr_info.insert(arr_info_pair);
                }
              }
            }
            break;
          case NOM_ATTR_SA_VAL_OBS:
            {
              intellivue::SaObsValue* psa_obs_val =
                  reinterpret_cast<intellivue::SaObsValue *>(
                    attr_list.value[iz].attribute_val);
              if (!psa_obs_val)
              {
                LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                                                   "attribute_val into "
                                                   "SaObsValue. attribute_id: "
                               << static_cast<int>(attribute_id));
                break;
              }

              std::tuple<intellivue::OIDType, uint16_t> arr_info_pair(
                    psa_obs_val->physio_id,
                    psa_obs_val->array.length);
              set_arr_info.insert(arr_info_pair);
            }
            break;
          case NOM_ATTR_SA_CMPD_VAL_OBS:
            {
              intellivue::SaObsValueCmp* psa_obs_val_cmp =
                  reinterpret_cast<intellivue::SaObsValueCmp *>(
                    attr_list.value[iz].attribute_val);
              if (!psa_obs_val_cmp)
              {
                LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                                                   "attribute_val into "
                                                   "SaObsValueCmp. "
                                                   "attribute_id: "
                               << static_cast<int>(attribute_id));
                break;
              }

              for (int ia = 0; ia < psa_obs_val_cmp->count; ia++)
              {
                if (!psa_obs_val_cmp->value)
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "Pointer to SaObsValue "
                                                     "is null. attribute_id: "
                                 << static_cast<int>(attribute_id));
                  break;
                }
                std::tuple<intellivue::OIDType, uint16_t> arr_info_pair(
                      psa_obs_val_cmp->value[ia].physio_id,
                      psa_obs_val_cmp->value[ia].array.length);
                set_arr_info.insert(arr_info_pair);
              }
            }
            break;
        }
      }

      for (
        int iz = 0;
        iz < attr_list.count;
        iz++)
      {
        if (!attr_list.value)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "AVAType array in "
                                             "attributes is a null pointer");
          break;
        }

        for (std::set<std::tuple<intellivue::OIDType, uint16_t>>::iterator it =
             set_arr_info.begin(); it!=set_arr_info.end(); ++it)
        {
          std::tuple<
              intellivue::MdsContext,
              intellivue::Handle,
              intellivue::MdsContext,
              intellivue::Handle,
              intellivue::OIDType,
              uint16_t
              >unique_handle(
                glb_handle.context_id,
                glb_handle.handle,
                single_context_poll_context_id,
                obj_handle,
                std::get<0>(*it),
                std::get<1>(*it));

          if (_map_handle_to_rtsa_instance[unique_handle].empty())
          {
            LOG4CPLUS_WARN(root_logger, sfn << "Will not be able to "
                                               "dereference the iterator "
                                               "returned from rtsa instance "
                                               "map in the future. There must "
                                               "be at least one index for "
                                               "rtsa instance vector per "
                                               "object.");
            continue;
          }

          // Set absolute timestamp for all metrics found
          if (_extended_poll_response.pollReply.abs_time_stamp.century != 0xFF
              || _extended_poll_response.pollReply.abs_time_stamp.year != 0xFF
              || _extended_poll_response.pollReply.abs_time_stamp.month != 0xFF
              || _extended_poll_response.pollReply.abs_time_stamp.day != 0xFF
              || _extended_poll_response.pollReply.abs_time_stamp.hour != 0xFF
              || _extended_poll_response.pollReply.abs_time_stamp.minute != 0xFF
              || _extended_poll_response.pollReply.abs_time_stamp.second != 0xFF
              || _extended_poll_response.pollReply.abs_time_stamp.sec_fractions != 0xFF)
          {
            if (!_rtsa_meas_observed_value_response_instance_list.at(
                  _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                second->device_timestamp)
            {
              _rtsa_meas_observed_value_response_instance_list.at(
                    _map_handle_to_rtsa_instance[unique_handle].begin()->
                    second).second->device_timestamp =
                  reinterpret_cast<ice::Timespec *>(
                    DDS::Heap_malloc(sizeof(ice::Timespec)));
              if (!_rtsa_meas_observed_value_response_instance_list.at(
                    _map_handle_to_rtsa_instance[unique_handle].begin()->
                    second).second->device_timestamp)
              {
                LOG4CPLUS_WARN(root_logger, sfn << "Failed to allocate "
                                                   "memory for ice::Timespec");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
            }
            DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                ConvertIntellivueAbsoluteTimeToDicesTimespec(
                  _rtsa_meas_observed_value_response_instance_list.at(
                    _map_handle_to_rtsa_instance[unique_handle].begin()->
                    second).second->device_timestamp,
                  _extended_poll_response.pollReply.abs_time_stamp);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                              DicesRcPhilipsIntellivueMP70StatusMessage::
                              DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }
          }

          // Set relative timestamp for all metrics found
          if (!_rtsa_meas_observed_value_response_instance_list.at(
                _map_handle_to_rtsa_instance[unique_handle].begin()->
                second).second->device_relative_timestamp)
          {
            _rtsa_meas_observed_value_response_instance_list.at(
                  _map_handle_to_rtsa_instance[unique_handle].begin()->
                  second).second->device_relative_timestamp =
                reinterpret_cast<ice::Duration *>(
                  DDS::Heap_malloc(sizeof(ice::Duration)));
            if (!_rtsa_meas_observed_value_response_instance_list.at(
                  _map_handle_to_rtsa_instance[unique_handle].begin()->
                  second).second->device_relative_timestamp)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to allocate memory "
                                                 "for ice::Duration");
              return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
            }
          }
          DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
              ConvertIntellivueRelativeTimeToDicesDuration(
                _rtsa_meas_observed_value_response_instance_list.at(
                  _map_handle_to_rtsa_instance[unique_handle].begin()->
                  second).second->device_relative_timestamp,
                _extended_poll_response.pollReply.rel_time_stamp);
          if (status != DicesRcPhilipsIntellivueMP70::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn <<
                            DicesRcPhilipsIntellivueMP70StatusMessage::
                            DicesRcPhilipsIntellivueMP70ToString(status));
            return status;
          }

          // Set type code
          _rtsa_meas_observed_value_response_instance_list.at(
                _map_handle_to_rtsa_instance[unique_handle].begin()->
                second).second->type.code = _extended_poll_response.
              pollReply.polled_obj_type.code;
          _rtsa_meas_context_response_instance_list.at(
                _map_handle_to_rtsa_instance[unique_handle].begin()->
                second).second->type.code = _extended_poll_response.
              pollReply.polled_obj_type.code;

          // Set type partition
          status = IntellivueUtils::
              ConvertIntellivueNomPartitionToDicesNomPartition(
                &_rtsa_meas_observed_value_response_instance_list.at(
                  _map_handle_to_rtsa_instance[unique_handle].begin()->
                  second).second->type.partition,
                _extended_poll_response.pollReply.polled_obj_type.partition);
          if (status != DicesRcPhilipsIntellivueMP70::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn <<
                            DicesRcPhilipsIntellivueMP70StatusMessage::
                            DicesRcPhilipsIntellivueMP70ToString(status));
            return status;
          }
          status = IntellivueUtils::
              ConvertIntellivueNomPartitionToDicesNomPartition(
                &_rtsa_meas_context_response_instance_list.at(
                  _map_handle_to_rtsa_instance[unique_handle].begin()->
                  second).second->type.partition,
                _extended_poll_response.pollReply.polled_obj_type.partition);
          if (status != DicesRcPhilipsIntellivueMP70::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn <<
                            DicesRcPhilipsIntellivueMP70StatusMessage::
                            DicesRcPhilipsIntellivueMP70ToString(status));
            return status;
          }

          intellivue::OIDType attribute_id = attr_list.value[iz].
              attribute_id;
          switch (attribute_id)
          {
            case NOM_ATTR_ID_HANDLE:
              {
                intellivue::Handle* phandle =
                    reinterpret_cast<intellivue::Handle*>(
                      attr_list.value[iz].attribute_val);
                if (!phandle)
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                                                     "attribute_val into "
                                                     "intellivue::Handle. "
                                                     "attribute_id: "
                                 << static_cast<int>(attribute_id));
                  break;
                }

                // Handles set above
                // Set parent handles to the vmd
                if (_vmd_instance_list.size() > 0)
                {
                  _rtsa_meas_context_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->parent_handle = _vmd_instance_list.at(0).second->handle;

                  _rtsa_meas_observed_value_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->parent_handle = _vmd_instance_list.at(0).second->handle;
                }
              }
              break;
            case NOM_ATTR_ID_TYPE:
              {
                intellivue::TYPE* ptype =
                    reinterpret_cast<intellivue::TYPE*>(
                      attr_list.value[iz].attribute_val);
                if (!ptype)
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                                                     "attribute_val into "
                                                     "intellivue::TYPE. "
                                                     "attribute_id: "
                                 << static_cast<int>(attribute_id));
                  break;
                }

                ice::NomPartition dices_nom_partition = ice::nom_part_unspec;
                DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                    ConvertIntellivueNomPartitionToDicesNomPartition(
                      &dices_nom_partition,
                      ptype->partition);
                if (status != DicesRcPhilipsIntellivueMP70::OK)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn <<
                                  DicesRcPhilipsIntellivueMP70StatusMessage::
                                  DicesRcPhilipsIntellivueMP70ToString(status));
                  return status;
                }

                if (_rtsa_meas_context_response_instance_list.
                    at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->type.partition != dices_nom_partition)
                {
                  _rtsa_meas_context_response_instance_list.
                      at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->type.partition = dices_nom_partition;
                }

                if (_rtsa_meas_context_response_instance_list.
                    at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->type.code != ptype->code)
                {
                  _rtsa_meas_context_response_instance_list.
                      at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->type.code = ptype->code;
                }

                _rtsa_meas_observed_value_response_instance_list.
                    at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->type.partition = dices_nom_partition;

                _rtsa_meas_observed_value_response_instance_list.
                    at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->type.code = ptype->code;
              }
              break;
            case NOM_ATTR_METRIC_SPECN:
              {
                intellivue::MetricSpec* pmspec =
                    reinterpret_cast<intellivue::MetricSpec *>(
                      attr_list.value[iz].attribute_val);
                if (!pmspec)
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                                                     "attribute_val into "
                                                     "intellivue::MetricSpec. "
                                                     "attribute_id: "
                                 << static_cast<int>(attribute_id));
                  break;
                }

                ice::MetricAccess dices_access = 0;
                DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                    ConvertIntellivueMetricAccessToDicesMetricAccess(
                      &dices_access,
                      pmspec->access);
                if (status != DicesRcPhilipsIntellivueMP70::OK)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn <<
                                  DicesRcPhilipsIntellivueMP70StatusMessage::
                                  DicesRcPhilipsIntellivueMP70ToString(status));
                  return status;
                }

                if (_rtsa_meas_context_response_instance_list.at(
                      _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->metric_specification.access != dices_access)
                {
                  _rtsa_meas_context_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->metric_specification.access = dices_access;
                  _rtsa_meas_context_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      first = DicesRcDriver::OK;
                }
                ice::MetricCategory dices_category =
                    ice::MetricCategory::auto_measurement;
                status = IntellivueUtils::
                    ConvertIntellivueMetricCategoryToDicesMetricCategory(
                      &dices_category,
                      pmspec->category);
                if (status != DicesRcPhilipsIntellivueMP70::OK)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn <<
                                  DicesRcPhilipsIntellivueMP70StatusMessage::
                                  DicesRcPhilipsIntellivueMP70ToString(status));
                  return status;
                }
                if (_rtsa_meas_context_response_instance_list.at(
                      _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->metric_specification.category != dices_category)
                {
                  _rtsa_meas_context_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->metric_specification.category = dices_category;
                  _rtsa_meas_context_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      first = DicesRcDriver::OK;
                }
                // MetricRelevance cannot be set properly. Intellivue
                // documentation states that MetricRelevance is for internal use
                // only. There is no way to convert intellivue bits to DICES
                // bits.
                ice::Duration dices_rel_time = { 0 };
                status = IntellivueUtils::
                    ConvertIntellivueRelativeTimeToDicesDuration(
                      &dices_rel_time,
                      pmspec->update_period);
                if (status != DicesRcPhilipsIntellivueMP70::OK)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn <<
                                  DicesRcPhilipsIntellivueMP70StatusMessage::
                                  DicesRcPhilipsIntellivueMP70ToString(status));
                  return status;
                }
                if (_rtsa_meas_context_response_instance_list.at(
                      _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->metric_specification.update_period.seconds
                    != dices_rel_time.seconds)
                {
                  _rtsa_meas_context_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->metric_specification.update_period.seconds =
                      dices_rel_time.seconds;
                  _rtsa_meas_context_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      first = DicesRcDriver::OK;
                }
                if (_rtsa_meas_context_response_instance_list.at(
                      _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->metric_specification.update_period.nanoseconds
                    != dices_rel_time.nanoseconds)
                {
                  _rtsa_meas_context_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->metric_specification.update_period.nanoseconds =
                      dices_rel_time.nanoseconds;
                  _rtsa_meas_context_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      first = DicesRcDriver::OK;
                }
              }
              break;
            case NOM_ATTR_SA_SPECN:
              {
                intellivue::SaSpec* psa_specn =
                    reinterpret_cast<intellivue::SaSpec *>(
                      attr_list.value[iz].attribute_val);
                if (!psa_specn)
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                                                     "attribute_val into "
                                                     "intellivue::SaSpec. "
                                                     "attribute_id: "
                                 << static_cast<int>(attribute_id));
                  break;
                }

                std::map<intellivue::OIDType, unsigned int>::iterator rtsa_it;
                for (
                     rtsa_it = _map_handle_to_rtsa_instance[unique_handle].begin();
                     rtsa_it != _map_handle_to_rtsa_instance[unique_handle].end();
                     rtsa_it++)
                {
                  if (_rtsa_meas_context_response_instance_list.
                      at(rtsa_it->second).second->sa_specification.array_size
                      != psa_specn->array_size)
                  {
                    _rtsa_meas_context_response_instance_list.
                        at(rtsa_it->second).second->sa_specification.array_size =
                        psa_specn->array_size;
                    _rtsa_meas_context_response_instance_list.
                        at(rtsa_it->second).first = DicesRcDriver::OK;
                  }

                  if (_rtsa_meas_context_response_instance_list.
                      at(rtsa_it->second).second->sa_specification.flags
                      != psa_specn->flags)
                  {
                    _rtsa_meas_context_response_instance_list.
                        at(rtsa_it->second).second->sa_specification.flags =
                        psa_specn->flags;
                    _rtsa_meas_context_response_instance_list.
                        at(rtsa_it->second).first = DicesRcDriver::OK;
                  }

                  if (!_rtsa_meas_context_response_instance_list.
                      at(rtsa_it->second).
                      second->sa_specification.sample_type)
                  {
                    _rtsa_meas_context_response_instance_list.
                        at(rtsa_it->second).second->sa_specification.sample_type =
                        reinterpret_cast<ice::SampleType*>(
                          DDS::Heap_malloc(sizeof(ice::SampleType)));
                    if (!_rtsa_meas_context_response_instance_list.
                        at(rtsa_it->second).second->sa_specification.sample_type)
                    {
                      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate "
                                                          "memory for "
                                                          "ice::SampleType");
                      return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
                    }
                  }

                  if (_rtsa_meas_context_response_instance_list.
                      at(rtsa_it->second).second->sa_specification.sample_type->
                      sample_size != psa_specn->sample_type.sample_size)
                  {
                    _rtsa_meas_context_response_instance_list.
                        at(rtsa_it->second).second->sa_specification.sample_type->
                        sample_size = psa_specn->sample_type.sample_size;
                    _rtsa_meas_context_response_instance_list.
                        at(rtsa_it->second).first = DicesRcDriver::OK;
                  }

                  if (_rtsa_meas_context_response_instance_list.
                      at(rtsa_it->second).second->sa_specification.sample_type->
                      significant_bits != psa_specn->sample_type.significant_bits)
                  {
                    _rtsa_meas_context_response_instance_list.
                        at(rtsa_it->second).second->sa_specification.sample_type->
                        significant_bits = psa_specn->sample_type.significant_bits;
                    _rtsa_meas_context_response_instance_list.
                        at(rtsa_it->second).first = DicesRcDriver::OK;
                  }
                }
              }
              break;
            case NOM_ATTR_SA_FIXED_VAL_SPECN:
              {
                intellivue::SaFixedValSpec16* psa_fixed_val_spec16 =
                    reinterpret_cast<intellivue::SaFixedValSpec16 *>(
                      attr_list.value[iz].attribute_val);
                if (!psa_fixed_val_spec16)
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                                                     "attribute_val into "
                                                     "intellivue::"
                                                     "SaFixedValSpec16. "
                                                     "attribute_id: "
                                 << static_cast<int>(attribute_id));
                  break;
                }

                if (!psa_fixed_val_spec16->value)
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "Pointer to "
                                                     "intellivue::"
                                                     "SaFixedValSpecEntry16 "
                                                     "is null. "
                                                     "attribute_id: "
                                 << static_cast<int>(attribute_id));
                  break;
                }

                if (!_rtsa_meas_context_response_instance_list.
                    at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->sa_marker_list)
                {
                  _rtsa_meas_context_response_instance_list.
                      at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->sa_marker_list =
                      reinterpret_cast<ice::MarkerListSaVal*>(
                        DDS::Heap_malloc(sizeof(ice::MarkerListSaVal)));
                  if (!_rtsa_meas_context_response_instance_list.
                      at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->sa_marker_list)
                  {
                    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate "
                                                        "memory for "
                                                        "MarkerListSaVal");
                    return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
                  }
                }

                if (!_rtsa_meas_context_response_instance_list.
                    at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->sa_marker_list->ensure_length(
                      psa_fixed_val_spec16->count,
                      psa_fixed_val_spec16->count))
                {
                  LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure "
                                                      "lengthof sa marker "
                                                      "list");
                  DicesRcPhilipsIntellivueMP70::FAIL;
                }

                for (int ix = 0; ix < psa_fixed_val_spec16->count; ix++)
                {
                  if (_rtsa_meas_context_response_instance_list.
                      at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->sa_marker_list->get_at(ix).marker_id !=
                      psa_fixed_val_spec16->value[ix].sa_fixed_val_id)
                  {
                    _rtsa_meas_context_response_instance_list.
                        at(_map_handle_to_rtsa_instance[unique_handle].begin()->
                           second).second->sa_marker_list->operator[](ix).marker_id =
                        psa_fixed_val_spec16->value[ix].sa_fixed_val_id;
                    _rtsa_meas_context_response_instance_list.
                        at(_map_handle_to_rtsa_instance[unique_handle].begin()->
                           second).first = DicesRcDriver::OK;
                  }

                  if (_rtsa_meas_context_response_instance_list.
                      at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->sa_marker_list->get_at(ix).marker_val !=
                      psa_fixed_val_spec16->value[ix].sa_fixed_val)
                  {
                    _rtsa_meas_context_response_instance_list.
                        at(_map_handle_to_rtsa_instance[unique_handle].begin()->
                           second).second->sa_marker_list->operator[](ix).marker_val =
                        psa_fixed_val_spec16->value[ix].sa_fixed_val;
                    _rtsa_meas_context_response_instance_list.
                        at(_map_handle_to_rtsa_instance[unique_handle].begin()->
                           second).first = DicesRcDriver::OK;
                  }
                }
              }
              break;
            case NOM_ATTR_TIME_PD_SAMP:
              {
                intellivue::RelativeTime* ptime_pd_samp =
                    reinterpret_cast<intellivue::RelativeTime *>(
                      attr_list.value[iz].attribute_val);
                if (!ptime_pd_samp)
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                                                     "attribute_val into "
                                                     "intellivue::"
                                                     "RelativeTime. "
                                                     "attribute_id: "
                                 << static_cast<int>(attribute_id));
                  break;
                }

                ice::Duration dices_time_pd_samp = { 0 };
                DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                    ConvertIntellivueRelativeTimeToDicesDuration(
                      &dices_time_pd_samp,
                      *ptime_pd_samp);
                if (status != DicesRcPhilipsIntellivueMP70::OK)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn <<
                                  DicesRcPhilipsIntellivueMP70StatusMessage::
                                  DicesRcPhilipsIntellivueMP70ToString(status));
                  return status;
                }

                if (_rtsa_meas_context_response_instance_list.
                    at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->sample_period.nanoseconds !=
                    dices_time_pd_samp.nanoseconds)
                {
                  _rtsa_meas_context_response_instance_list.
                      at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->sample_period.nanoseconds = dices_time_pd_samp.nanoseconds;
                  _rtsa_meas_context_response_instance_list.
                      at(_map_handle_to_rtsa_instance[unique_handle].begin()->
                         second).first = DicesRcDriver::OK;
                }

                if (_rtsa_meas_context_response_instance_list.
                    at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->sample_period.seconds != dices_time_pd_samp.seconds)
                {
                  _rtsa_meas_context_response_instance_list.
                      at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->sample_period.seconds = dices_time_pd_samp.seconds;
                  _rtsa_meas_context_response_instance_list.
                      at(_map_handle_to_rtsa_instance[unique_handle].begin()->
                         second).first = DicesRcDriver::OK;
                }
              }
              break;
            case NOM_ATTR_SCALE_SPECN_I16:
              {
                intellivue::ScaleRangeSpec16* pscale_range_spec16 =
                    reinterpret_cast<intellivue::ScaleRangeSpec16 *>(
                      attr_list.value[iz].attribute_val);
                if (!pscale_range_spec16)
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                                                     "attribute_val into "
                                                     "intellivue::"
                                                     "ScaleRangeSpec16. "
                                                     "attribute_id: "
                                 << static_cast<int>(attribute_id));
                  break;
                }

                ice::FLOATType lower_absolute_value = 0;
                DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                    ConvertIntellivueFloatTypeToDicesFloatType(
                      &lower_absolute_value,
                      pscale_range_spec16->lower_absolute_value);
                if (status != DicesRcPhilipsIntellivueMP70::OK)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn <<
                                  DicesRcPhilipsIntellivueMP70StatusMessage::
                                  DicesRcPhilipsIntellivueMP70ToString(status));
                  return status;
                }

                ice::FLOATType upper_absolute_value = 0;
                status = IntellivueUtils::
                    ConvertIntellivueFloatTypeToDicesFloatType(
                      &upper_absolute_value,
                      pscale_range_spec16->upper_absolute_value);
                if (status != DicesRcPhilipsIntellivueMP70::OK)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn <<
                                  DicesRcPhilipsIntellivueMP70StatusMessage::
                                  DicesRcPhilipsIntellivueMP70ToString(status));
                  return status;
                }

                std::map<intellivue::OIDType, unsigned int>::iterator rtsa_it;
                for (
                     rtsa_it = _map_handle_to_rtsa_instance[unique_handle].begin();
                     rtsa_it != _map_handle_to_rtsa_instance[unique_handle].end();
                     rtsa_it++)
                {

                  if (_rtsa_meas_context_response_instance_list.
                      at(rtsa_it->second).second->scale_and_range_specification.
                      lower_absolute_value != lower_absolute_value)
                  {
                    _rtsa_meas_context_response_instance_list.
                        at(rtsa_it->second).second->scale_and_range_specification.
                        lower_absolute_value = lower_absolute_value;
                    _rtsa_meas_context_response_instance_list.
                        at(rtsa_it->second).first = DicesRcDriver::OK;
                  }

                  if (_rtsa_meas_context_response_instance_list.
                      at(rtsa_it->second).second->scale_and_range_specification.
                      upper_absolute_value != upper_absolute_value)
                  {
                    _rtsa_meas_context_response_instance_list.
                        at(rtsa_it->second).second->scale_and_range_specification.
                        upper_absolute_value = upper_absolute_value;
                    _rtsa_meas_context_response_instance_list.
                        at(rtsa_it->second).first = DicesRcDriver::OK;
                  }

                  if (_rtsa_meas_context_response_instance_list.
                      at(rtsa_it->second).second->scale_and_range_specification.
                      lower_scaled_value != pscale_range_spec16->
                      lower_scaled_value)
                  {
                    _rtsa_meas_context_response_instance_list.
                        at(rtsa_it->second).second->scale_and_range_specification.
                        lower_scaled_value = pscale_range_spec16->
                        lower_scaled_value;
                    _rtsa_meas_context_response_instance_list.
                        at(rtsa_it->second).first = DicesRcDriver::OK;
                  }

                  if (_rtsa_meas_context_response_instance_list.
                      at(rtsa_it->second).second->scale_and_range_specification.
                      upper_scaled_value != pscale_range_spec16->
                      upper_scaled_value)
                  {
                    _rtsa_meas_context_response_instance_list.
                        at(rtsa_it->second).second->scale_and_range_specification.
                        upper_scaled_value = pscale_range_spec16->
                        upper_scaled_value;
                    _rtsa_meas_context_response_instance_list.
                        at(rtsa_it->second).first = DicesRcDriver::OK;
                  }
                }
              }
              break;
            case NOM_ATTR_SA_VAL_OBS:
              {
                intellivue::SaObsValue* psa_obs_val =
                    reinterpret_cast<intellivue::SaObsValue *>(
                      attr_list.value[iz].attribute_val);

                if (!psa_obs_val)
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                                                     "attribute_val into "
                                                     "SaObsValue. "
                                                     "attribute_id: "
                                 << static_cast<int>(attribute_id));
                  break;
                }

                if (std::get<4>(unique_handle) != psa_obs_val->physio_id
                    || std::get<5>(unique_handle) != psa_obs_val->array.length)
                {
                  break;
                }

                if (_rtsa_meas_context_response_instance_list.at(
                      _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->metric_id != psa_obs_val->physio_id)
                {
                  _rtsa_meas_context_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->metric_id = psa_obs_val->physio_id;
                  _rtsa_meas_context_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      first = DicesRcDriver::OK;
                }
                _rtsa_meas_observed_value_response_instance_list.at(
                      _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->sa_observed_value.metric_id = psa_obs_val->physio_id;

                ice::MeasurementStatus dices_meas_status = 0;
                DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                    ConvertIntellivueMeasurementStatusToDicesMeasurementStatus(
                      &dices_meas_status,
                      psa_obs_val->state);
                if (status != DicesRcPhilipsIntellivueMP70::OK)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn <<
                                  DicesRcPhilipsIntellivueMP70StatusMessage::
                                  DicesRcPhilipsIntellivueMP70ToString(status));
                  return status;
                }

                if (_rtsa_meas_context_response_instance_list.at(
                      _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->measurement_status != dices_meas_status)
                {
                  _rtsa_meas_context_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->measurement_status = dices_meas_status;
                  if (_rtsa_meas_context_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->metric_id != 0)
                  {
                    _rtsa_meas_context_response_instance_list.at(
                          _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                        first = DicesRcDriver::OK;
                  }
                }

                _rtsa_meas_observed_value_response_instance_list.at(
                      _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->sa_observed_value.state = dices_meas_status;

                _rtsa_meas_observed_value_response_instance_list.at(
                      _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    first = DicesRcDriver::OK;

                _rtsa_meas_observed_value_response_instance_list.at(
                      _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->sequence_number++;

                if (_rtsa_meas_observed_value_response_instance_list.at(
                      _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->sequence_number > 4)
                {
                  _rtsa_meas_observed_value_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->sequence_number = 1;
                }

                // TODO Not sure if this is the best place to get these values.
                ice::INTU8 sample_size = 0;
                ice::INTU8 significant_bits = 0;
                if (_rtsa_meas_context_response_instance_list.
                    at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->sa_specification.sample_type)
                {
                  sample_size = _rtsa_meas_context_response_instance_list.
                      at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->sa_specification.sample_type->sample_size;
                  significant_bits = _rtsa_meas_context_response_instance_list.
                      at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->sa_specification.sample_type->significant_bits;
                }
                else
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "Unable to get "
                                                     "sample_size "
                                                     "and significant_bits "
                                                     "from sample_type because "
                                                     "it's a null pointer.");
                }

                ice::SaFlags flags = _rtsa_meas_context_response_instance_list.
                    at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->sa_specification.flags;
                ice::FLOATType lower_absolute_value = _rtsa_meas_context_response_instance_list.
                    at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->scale_and_range_specification.lower_absolute_value;
                ice::FLOATType upper_absolute_value = _rtsa_meas_context_response_instance_list.
                    at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->scale_and_range_specification.upper_absolute_value;
                ice::INTU32 lower_scaled_value = _rtsa_meas_context_response_instance_list.
                    at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->scale_and_range_specification.lower_scaled_value;
                ice::INTU32 upper_scaled_value = _rtsa_meas_context_response_instance_list.
                    at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->scale_and_range_specification.upper_scaled_value;

                const int kbits_per_byte = 8;
                int bytes_per_sample = sample_size / kbits_per_byte;

                int number_of_samples = 0;
                if (bytes_per_sample) // Avoid dividing by zero
                {
                  number_of_samples = psa_obs_val->array.length / bytes_per_sample;
                }

                const int kinstances_per_rtsa = 2;
                // Make sure we don't go over our sequence maximum.
                const int kmax_sequence_size =
                    _rtsa_meas_observed_value_response_instance_list.at(
                      _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                    second->sa_observed_value.array.maximum();
                if ((kmax_sequence_size * kinstances_per_rtsa) < number_of_samples)
                {
                  LOG4CPLUS_WARN(root_logger, sfn << kinstances_per_rtsa
                                 << " sequences with a max size of "
                                 << kmax_sequence_size
                                 << " is not large enough to hold rtsa with "
                                 << number_of_samples
                                 << " samples. The sample array will be "
                                    "truncated until this issue is solved.");
                }


                int number_of_new_sequences = 0;
                if (number_of_samples > kmax_sequence_size)
                {
                  // Determines if more RTSAObservedValues are required to hold
                  // this array
                  number_of_new_sequences = number_of_samples / kmax_sequence_size;

                  for (int offset = 0; offset < number_of_new_sequences; offset++)
                  {
                    // Make sure new samples are identical
                    ice::RTSAObservedValueTypeSupport::copy_data(
                          _rtsa_meas_observed_value_response_instance_list.at(
                            _map_handle_to_rtsa_instance[unique_handle].begin()->second
                            + offset + 1).second,
                          _rtsa_meas_observed_value_response_instance_list.at(
                            _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                          second);

                    // Set to publish the additional arrays.
                    _rtsa_meas_observed_value_response_instance_list.at(
                          _map_handle_to_rtsa_instance[unique_handle].begin()->second
                          + offset + 1).first = DicesRcDriver::OK;
                  }
                }

                int ensure_number_of_samples = number_of_samples;
                int ensure_index = 0;
                while (ensure_number_of_samples)
                {
                  int sequence_len = 0;
                  if (ensure_number_of_samples >= kmax_sequence_size)
                  {
                    sequence_len = kmax_sequence_size;
                  }
                  else
                  {
                    sequence_len = ensure_number_of_samples;
                  }
                  bool ensure_length =
                      _rtsa_meas_observed_value_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second
                        + ensure_index).second->sa_observed_value.array.
                      ensure_length(
                        sequence_len,
                        sequence_len);
                  if (!ensure_length)
                  {
                    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure "
                                                        "RTSA observed value "
                                                        "sequence length with "
                                                        "length "
                                    << sequence_len);
                    DicesRcPhilipsIntellivueMP70::FAIL;
                  }
                  ensure_number_of_samples -= sequence_len;
                  ensure_index++;
                }

                bool mask_required = false;

                if (flags & ice::SaFlagsBits::sa_ext_val_range) mask_required = true;

                int sa_index = 0;
                int instance_offset = 0;
                for (int jx = 0; jx < number_of_samples; jx++)
                {
                  instance_offset = jx / kmax_sequence_size;
                  int instance_array_index = jx % kmax_sequence_size;
                  switch (bytes_per_sample)
                  {
                    case 1:
                      _rtsa_meas_observed_value_response_instance_list.at(
                            _map_handle_to_rtsa_instance[unique_handle].begin()->second
                            + instance_offset).second->sa_observed_value.array[
                          instance_array_index] = psa_obs_val->array.value[sa_index];
                      sa_index++;
                      break;
                    case 2:
                      _rtsa_meas_observed_value_response_instance_list.at(
                            _map_handle_to_rtsa_instance[unique_handle].begin()->second
                            + instance_offset).second->sa_observed_value.array[
                          instance_array_index] = ntohs(*(
                                                          reinterpret_cast<uint16_t*>(&psa_obs_val->array.value[
                                                                                      sa_index])));
                      sa_index += 2;
                      break;
                    case 4:
                      _rtsa_meas_observed_value_response_instance_list.at(
                            _map_handle_to_rtsa_instance[unique_handle].begin()->second
                            + instance_offset).second->sa_observed_value.array[
                          instance_array_index] =
                          ntohl(*(reinterpret_cast<uint32_t*>(&psa_obs_val->array.
                                                              value[sa_index])));
                      sa_index += 4;
                      break;
                    default:
                      LOG4CPLUS_WARN(root_logger, sfn << "Unexpected number "
                                                         "of bytes per sample "
                                                         "received. "
                                                         "Maintenance required.");
                      break;
                  }

                  uint32_t value =
                      _rtsa_meas_observed_value_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second
                        + instance_offset).second->sa_observed_value.array[
                      instance_array_index];

                  // Calculate absolute value using specification
                  double percentage_scaled = (double)value / (double)upper_scaled_value;
                  int absolute_value_range = upper_absolute_value - lower_absolute_value;
                  double absolute_offset = absolute_value_range * percentage_scaled;
                  double new_absolute_value = lower_absolute_value + absolute_offset;

                  _rtsa_meas_observed_value_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second +
                        instance_offset).second->sa_observed_value.array[
                      instance_array_index] = new_absolute_value;
                }
              }
              break;
            case NOM_ATTR_SA_CMPD_VAL_OBS:
              {
                intellivue::SaObsValueCmp* psa_obs_val_cmp =
                    reinterpret_cast<intellivue::SaObsValueCmp *>(
                      attr_list.value[iz].attribute_val);

                if (!psa_obs_val_cmp)
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                                                     "attribute_val into "
                                                     "SaObsValueCmp. "
                                                     "attribute_id: "
                                 << static_cast<int>(attribute_id));
                  break;
                }

                if (!psa_obs_val_cmp->value)
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "In SaObsValueCmp, list "
                                                     "of SaObsValue is a null "
                                                     "pointer. attribute_id: "
                                 << static_cast<int>(attribute_id));
                  break;
                }

                for (int ix = 0; ix < psa_obs_val_cmp->count; ix++)
                {
                  if (std::get<4>(unique_handle) != psa_obs_val_cmp->value[ix].physio_id
                      || std::get<5>(unique_handle) != psa_obs_val_cmp->value[ix].array.length)
                  {
                    continue;
                  }

                  if (_rtsa_meas_context_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->metric_id != psa_obs_val_cmp->value[ix].physio_id)
                  {
                    _rtsa_meas_context_response_instance_list.at(
                          _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                        second->metric_id = psa_obs_val_cmp->value[ix].physio_id;
                    _rtsa_meas_context_response_instance_list.at(
                          _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                        first = DicesRcDriver::OK;
                  }
                  _rtsa_meas_observed_value_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->sa_observed_value.metric_id = psa_obs_val_cmp->value[ix].physio_id;

                  ice::MeasurementStatus dices_meas_status = 0;
                  DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                      ConvertIntellivueMeasurementStatusToDicesMeasurementStatus(
                        &dices_meas_status,
                        psa_obs_val_cmp->value[ix].state);
                  if (status != DicesRcPhilipsIntellivueMP70::OK)
                  {
                    LOG4CPLUS_ERROR(root_logger, sfn <<
                                    DicesRcPhilipsIntellivueMP70StatusMessage::
                                    DicesRcPhilipsIntellivueMP70ToString(status));
                    return status;
                  }

                  if (_rtsa_meas_context_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->measurement_status != dices_meas_status)
                  {
                    _rtsa_meas_context_response_instance_list.at(
                          _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                        second->measurement_status = dices_meas_status;
                    if (_rtsa_meas_context_response_instance_list.at(
                          _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                        second->metric_id != 0)
                    {
                      _rtsa_meas_context_response_instance_list.at(
                            _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                          first = DicesRcDriver::OK;
                    }
                  }

                  _rtsa_meas_observed_value_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->sa_observed_value.state = dices_meas_status;

                  _rtsa_meas_observed_value_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      first = DicesRcDriver::OK;

                  _rtsa_meas_observed_value_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->sequence_number++;

                  if (_rtsa_meas_observed_value_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->sequence_number > 4)
                  {
                    _rtsa_meas_observed_value_response_instance_list.at(
                          _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                        second->sequence_number = 1;
                  }

                  // TODO Not sure if this is the best place to get these values.
                  ice::INTU8 sample_size = 0;
                  ice::INTU8 significant_bits = 0;
                  if (_rtsa_meas_context_response_instance_list.
                      at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->sa_specification.sample_type)
                  {
                    sample_size = _rtsa_meas_context_response_instance_list.
                        at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                        second->sa_specification.sample_type->sample_size;
                    significant_bits = _rtsa_meas_context_response_instance_list.
                        at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                        second->sa_specification.sample_type->significant_bits;
                  }
                  else
                  {
                    LOG4CPLUS_WARN(root_logger, sfn << "Unable to get "
                                                       "sample_size "
                                                       "and significant_bits "
                                                       "from sample_type "
                                                       "because it's a null "
                                                       "pointer.");
                  }
                  ice::SaFlags flags = _rtsa_meas_context_response_instance_list.
                      at(_map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->sa_specification.flags;
                  ice::FLOATType lower_absolute_value =
                      _rtsa_meas_context_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->scale_and_range_specification.lower_absolute_value;
                  ice::FLOATType upper_absolute_value =
                      _rtsa_meas_context_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->scale_and_range_specification.upper_absolute_value;
                  ice::INTU32 lower_scaled_value =
                      _rtsa_meas_context_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->scale_and_range_specification.lower_scaled_value;
                  ice::INTU32 upper_scaled_value =
                      _rtsa_meas_context_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->scale_and_range_specification.upper_scaled_value;

                  const int kbits_per_byte = 8;
                  int bytes_per_sample = sample_size / kbits_per_byte;
                  int number_of_samples = 0;

                  if (bytes_per_sample) // Avoid dividing by zero
                  {
                    number_of_samples = psa_obs_val_cmp->value[ix].array.length
                        / bytes_per_sample;
                  }

                  const int kinstances_per_rtsa = 2;
                  // Make sure we don't go over our sequence maximum.
                  const int kmax_sequence_size =
                      _rtsa_meas_observed_value_response_instance_list.at(
                        _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                      second->sa_observed_value.array.maximum();
                  if ((kmax_sequence_size * kinstances_per_rtsa) < number_of_samples)
                  {
                    LOG4CPLUS_WARN(root_logger, sfn << kinstances_per_rtsa
                                   << " sequences with a max size of "
                                   << kmax_sequence_size
                                   << " is not large enough to hold rtsa with "
                                   << number_of_samples
                                   << " samples. The sample array will be"
                                      "truncated until this issue is solved.");
                  }

                  int number_of_new_sequences = 0;
                  if (number_of_samples > kmax_sequence_size)
                  {
                    // Determines if more RTSAObservedValues are required to hold
                    // this array
                    number_of_new_sequences = number_of_samples / kmax_sequence_size;

                    for (int offset = 0; offset < number_of_new_sequences; offset++)
                    {
                      // Make sure new samples are identical
                      ice::RTSAObservedValueTypeSupport::copy_data(
                            _rtsa_meas_observed_value_response_instance_list.at(
                              _map_handle_to_rtsa_instance[unique_handle].begin()->second
                              + offset + 1).second,
                            _rtsa_meas_observed_value_response_instance_list.at(
                              _map_handle_to_rtsa_instance[unique_handle].begin()->second).
                            second);

                      // Set to publish the additional arrays.
                      _rtsa_meas_observed_value_response_instance_list.at(
                            _map_handle_to_rtsa_instance[unique_handle].begin()->second
                            + offset + 1).first = DicesRcDriver::OK;
                    }
                  }

                  int ensure_number_of_samples = number_of_samples;
                  int ensure_index = 0;
                  while (ensure_number_of_samples)
                  {
                    int sequence_len = 0;
                    if (ensure_number_of_samples >= kmax_sequence_size)
                    {
                      sequence_len = kmax_sequence_size;
                    }
                    else
                    {
                      sequence_len = ensure_number_of_samples;
                    }
                    bool ensure_length =
                        _rtsa_meas_observed_value_response_instance_list.at(
                          _map_handle_to_rtsa_instance[unique_handle].begin()->second
                          + ensure_index).second->sa_observed_value.array.
                        ensure_length(
                          sequence_len,
                          sequence_len);
                    if (!ensure_length)
                    {
                      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure "
                                                          "RTSA observed "
                                                          "value sequence "
                                                          "length with length "
                                      << sequence_len);
                      DicesRcPhilipsIntellivueMP70::FAIL;
                    }
                    ensure_number_of_samples -= sequence_len;
                    ensure_index++;
                  }

                  bool mask_required = false;

                  if (flags & ice::SaFlagsBits::sa_ext_val_range) mask_required = true;

                  int sa_index = 0;
                  int instance_offset = 0;
                  for (int jx = 0; jx < number_of_samples; jx++)
                  {
                    instance_offset = jx / kmax_sequence_size;
                    int instance_array_index = jx % kmax_sequence_size;
                    switch (bytes_per_sample)
                    {
                      case 1:
                        _rtsa_meas_observed_value_response_instance_list.at(
                              _map_handle_to_rtsa_instance[unique_handle].begin()->second
                              + instance_offset).second->sa_observed_value.
                            array[instance_array_index] = psa_obs_val_cmp->value[ix].
                            array.value[sa_index];
                        sa_index++;
                        break;
                      case 2:
                        _rtsa_meas_observed_value_response_instance_list.at(
                              _map_handle_to_rtsa_instance[unique_handle].begin()->second
                              + instance_offset).second->sa_observed_value.
                            array[instance_array_index] = ntohs(*(
                                                                  reinterpret_cast<uint16_t*>(&psa_obs_val_cmp->value[ix].
                                                                                              array.value[sa_index])));
                        sa_index += 2;
                        break;
                      case 4:
                        _rtsa_meas_observed_value_response_instance_list.at(
                              _map_handle_to_rtsa_instance[unique_handle].begin()->second
                              + instance_offset).second->sa_observed_value.
                            array[instance_array_index] = ntohl(*(
                                                                  reinterpret_cast<uint32_t*>(&psa_obs_val_cmp->value[ix].
                                                                                              array.value[sa_index])));
                        sa_index += 4;
                        break;
                      default:
                        LOG4CPLUS_WARN(root_logger, sfn << "Unexpected number "
                                                           "of bytes per "
                                                           "sample received. "
                                                           "Maintenance "
                                                           "required.");
                        break;
                    }

                    uint32_t value =
                        _rtsa_meas_observed_value_response_instance_list.at(
                          _map_handle_to_rtsa_instance[unique_handle].begin()->second
                          + instance_offset).second->sa_observed_value.array[
                        instance_array_index];

                    // Calculate absolute value using specification
                    double percentage_scaled = (double)value / (double)upper_scaled_value;
                    int absolute_value_range = upper_absolute_value - lower_absolute_value;
                    double absolute_offset = absolute_value_range * percentage_scaled;
                    double new_absolute_value = lower_absolute_value + absolute_offset;

                    _rtsa_meas_observed_value_response_instance_list.at(
                          _map_handle_to_rtsa_instance[unique_handle].begin()->second
                          + instance_offset).second->sa_observed_value.array[
                        instance_array_index] = new_absolute_value;
                  }
                }
              }
              break;
            default:
              break;
          }
        }
      }
    }
  }

  for (
       int ix = 0;
       ix < _rtsa_meas_context_response_instance_list.size();
       ix++)
  {
    // We now have a context instance with zero metric_ids for each
    // handle. We need to make sure not to publish the ones with zero
    // metric_ids
    if (_rtsa_meas_context_response_instance_list.at(ix).first
        == DicesRcDriver::OK && _rtsa_meas_context_response_instance_list.
        at(ix).second->metric_id == 0)
    {
      _rtsa_meas_context_response_instance_list.at(ix).first
          = DicesRcDriver::NO_NEW_DATA;
    }

    // For all context dds instances that have changed, increment context
    // sequence number and set for the same number in observed value.
    if (_rtsa_meas_context_response_instance_list.at(ix).first
        == DicesRcDriver::OK)
    {
      _rtsa_meas_context_response_instance_list.at(ix).second->
          context_seq_number++;
      _rtsa_meas_observed_value_response_instance_list.at(ix).second->
          context_seq_number = _rtsa_meas_context_response_instance_list.
          at(ix).second->context_seq_number;
      if (ix < _rtsa_meas_context_response_instance_list.size() - 1)
      {
        _rtsa_meas_observed_value_response_instance_list.at(ix + 1).second->
            context_seq_number = _rtsa_meas_context_response_instance_list.
            at(ix).second->context_seq_number;
      }
    }
  }
  for (int ix = 0; ix < _rtsa_meas_context_response_instance_list.size(); ix++)
  {
    switch (_rtsa_meas_context_response_instance_list.at(ix).second->
            metric_specification.category)
    {
      case ice::MetricCategory::auto_calculation:
      case ice::MetricCategory::manual_calculation:
        {
          DDS::ReturnCode_t retcode = ice::RTSAContextTypeSupport::copy_data(
                _rtsa_calc_context_response_instance_list.at(ix).second,
                _rtsa_meas_context_response_instance_list.at(ix).second);
          if (retcode != DDS::RETCODE_OK)
          {
            LOG4CPLUS_WARN(root_logger, sfn << "Failed to copy data from "
                                               "rtsa measurement context to "
                                               "rtsa calculation context");
            break;
          }
          retcode = ice::RTSAObservedValueTypeSupport::copy_data(
                _rtsa_calc_observed_value_response_instance_list.at(ix).second,
                _rtsa_meas_observed_value_response_instance_list.at(ix).second);
          if (retcode != DDS::RETCODE_OK)
          {
            LOG4CPLUS_WARN(root_logger, sfn << "Failed to copy data from "
                                               "rtsa measurement observed "
                                               "value to rtsa calculation "
                                               "observed value");
            break;
          }
          _rtsa_calc_context_response_instance_list.at(ix).first =
              _rtsa_meas_context_response_instance_list.at(ix).first;
          _rtsa_calc_observed_value_response_instance_list.at(ix).first =
              _rtsa_meas_observed_value_response_instance_list.at(ix).first;
          if (_rtsa_meas_context_response_instance_list.at(ix).first
              == DicesRcDriver::OK)
          {
            // Do not publish measurement.
            _rtsa_meas_context_response_instance_list.at(ix).first =
                DicesRcDriver::NO_NEW_DATA;
          }
          if (_rtsa_meas_observed_value_response_instance_list.at(ix).first
              == DicesRcDriver::OK)
          {
            // Do not publish measurement.
            _rtsa_meas_observed_value_response_instance_list.at(ix).first =
                DicesRcDriver::NO_NEW_DATA;
          }
        }
        break;
      case ice::MetricCategory::auto_setting:
      case ice::MetricCategory::manual_setting:
        {
          DDS::ReturnCode_t retcode = ice::RTSAContextTypeSupport::copy_data(
                _rtsa_sett_context_response_instance_list.at(ix).second,
                _rtsa_meas_context_response_instance_list.at(ix).second);
          if (retcode != DDS::RETCODE_OK)
          {
            LOG4CPLUS_WARN(root_logger, sfn << "Failed to copy data from "
                                               "rtsa measurement context to "
                                               "rtsa setting context");
            break;
          }
          retcode = ice::RTSAObservedValueTypeSupport::copy_data(
                _rtsa_sett_observed_value_response_instance_list.at(ix).second,
                _rtsa_meas_observed_value_response_instance_list.at(ix).second);
          if (retcode != DDS::RETCODE_OK)
          {
            LOG4CPLUS_WARN(root_logger, sfn << "Failed to copy data from "
                                               "rtsa measurement observed "
                                               "value to rtsa setting "
                                               "observed value");
            break;
          }
          _rtsa_sett_context_response_instance_list.at(ix).first =
              _rtsa_meas_context_response_instance_list.at(ix).first;
          _rtsa_sett_observed_value_response_instance_list.at(ix).first =
              _rtsa_meas_observed_value_response_instance_list.at(ix).first;
          if (_rtsa_meas_context_response_instance_list.at(ix).first
              == DicesRcDriver::OK)
          {
            // Do not publish measurement.
            _rtsa_meas_context_response_instance_list.at(ix).first =
                DicesRcDriver::NO_NEW_DATA;
          }
          if (_rtsa_meas_observed_value_response_instance_list.at(ix).first
              == DicesRcDriver::OK)
          {
            // Do not publish measurement.
            _rtsa_meas_observed_value_response_instance_list.at(ix).first =
                DicesRcDriver::NO_NEW_DATA;
          }
        }
        break;
      case ice::MetricCategory::mcat_unspec:
        LOG4CPLUS_WARN(root_logger, sfn << "MetricCategory is unspecified for "
                                           "RTSAContext at index (" << ix
                       << ")");
        break;
      default:
        // Must be a measurement
        break;
    }
  }
  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 DDPhilipsIntellivueMP70Parser::SetExtendedAlarmResponseData()
{
  static const char* sfn = "DDPhilipsIntellivueMP70Parser::SetExtendedAlarmResponseData() ";

  for (
    int ix = 0;
    ix < _extended_poll_response.pollReply.poll_info_list.count;
    ix++)
  {
    if (!_extended_poll_response.pollReply.poll_info_list.value)
    {
      LOG4CPLUS_WARN(root_logger, sfn << "SingleContextPoll array in "
        "PollInfoList is a null pointer");
      break;
    }

    for (
      int iy = 0;
      iy < _extended_poll_response.pollReply.poll_info_list.value[ix].
      poll_info.count;
      iy++)
    {
      if (!_extended_poll_response.pollReply.poll_info_list.value[ix].poll_info.value)
      {
        LOG4CPLUS_WARN(root_logger, sfn << "ObservationPoll array in "
          "poll_info is a null pointer");
        break;
      }

      // Get all alarm sources
      for (
        int iz = 0;
        iz < _extended_poll_response.pollReply.poll_info_list.value[ix].
        poll_info.value[iy].attributes.count;
        iz++)
      {
        intellivue::OIDType attribute_id = _extended_poll_response.pollReply.
          poll_info_list.value[ix].poll_info.value[iy].attributes.value[iz].
          attribute_id;
        switch (attribute_id)
        {
          case NOM_ATTR_AL_MON_T_AL_LIST:
          {
            intellivue::DevAlarmList* pdevice_al_list =
              reinterpret_cast<intellivue::DevAlarmList*>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!pdevice_al_list)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val to DevAlarmList. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }
            if (!pdevice_al_list->value)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "DevAlarmList contains a "
                "null pointer to DevAlarmEntry list. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            for (int ix = 0; ix < pdevice_al_list->count; ix++)
            {
              std::map<intellivue::OIDType, unsigned int>::iterator it;
              it = _map_al_source_to_tech_alarm_instance.find(
                pdevice_al_list->value[ix].al_source);
              if (it == _map_al_source_to_tech_alarm_instance.end())
              {
                if (_tech_alarm_vector_max_index
                  >= _technical_alarm_context_response_instance_list.size())
                {
                  LOG4CPLUS_INFO(root_logger, sfn << "The maximum number of technical alarm context "
                    "instances (" << _technical_alarm_context_response_instance_list.size() << ") are already "
                    "in use. Inserting additional instances.");

                  unsigned int tech_al_inst_diff = _tech_alarm_vector_max_index
                      - _technical_alarm_context_response_instance_list.size();
                  for (unsigned int inst_count = 0;
                       inst_count <= tech_al_inst_diff;
                       inst_count++)
                  {
                    std::pair<DicesRcDriver, ice::AlarmContext*> al_ctxt_pair(
                          DicesRcDriver::NO_NEW_DATA,
                          ice::AlarmContextTypeSupport::create_data());
                    if (!al_ctxt_pair.second)
                    {
                      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for technical "
                                                          "alarm context instance");
                      return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
                    }
                    try
                    {
                      _technical_alarm_context_response_instance_list.push_back(al_ctxt_pair);
                    }
                    catch(std::exception& ex)
                    {
                      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                          "technical alarm context pair onto vector. " << ex.what());
                      return DicesRcPhilipsIntellivueMP70::FAIL;
                    }
                  }
                }
                if (_tech_alarm_vector_max_index
                  >= _technical_alarm_signal_response_instance_list.size())
                {
                  LOG4CPLUS_INFO(root_logger, sfn << "The maximum number of technical alarm signal "
                    "instances (" << _technical_alarm_signal_response_instance_list.size() << ") are already "
                    "in use. Inserting additional instances.");

                  unsigned int tech_al_inst_diff = _tech_alarm_vector_max_index
                      - _technical_alarm_signal_response_instance_list.size();
                  for (unsigned int inst_count = 0;
                       inst_count <= tech_al_inst_diff;
                       inst_count++)
                  {
                    std::pair<DicesRcDriver, ice::AlarmSignal*> al_signal_pair(
                          DicesRcDriver::NO_NEW_DATA,
                          ice::AlarmSignalTypeSupport::create_data());
                    if (!al_signal_pair.second)
                    {
                      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for technical "
                                                          "alarm signal instance");
                      return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
                    }
                    try
                    {
                      _technical_alarm_signal_response_instance_list.push_back(al_signal_pair);
                    }
                    catch(std::exception& ex)
                    {
                      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                          "technical alarm signal pair onto vector. " << ex.what());
                      return DicesRcPhilipsIntellivueMP70::FAIL;
                    }
                  }
                }

                ice::AlarmContext* context_instance = nullptr;
                try
                {
                  context_instance =
                    _technical_alarm_context_response_instance_list.at(
                    _tech_alarm_vector_max_index).second;
                  if (!context_instance)
                  {
                    LOG4CPLUS_ERROR(root_logger, sfn << "Technical alarm "
                      "context instance is a null pointer at index: "
                      << _tech_alarm_vector_max_index);
                    return DicesRcPhilipsIntellivueMP70::FAIL;
                  }
                }
                catch (std::exception& ex)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get "
                    "technical alarm context instance from instance list at "
                    "index: " << _tech_alarm_vector_max_index << ". "
                    << ex.what());
                  return DicesRcPhilipsIntellivueMP70::FAIL;
                }

                ice::AlarmSignal* signal_instance = nullptr;
                try
                {
                  signal_instance =
                    _technical_alarm_signal_response_instance_list.at(
                    _tech_alarm_vector_max_index).second;
                  if (!signal_instance)
                  {
                    LOG4CPLUS_ERROR(root_logger, sfn << "Technical alarm "
                      "signal instance is a null pointer at index: "
                      << _tech_alarm_vector_max_index);
                    return DicesRcPhilipsIntellivueMP70::FAIL;
                  }
                }
                catch (std::exception& ex)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get "
                    "technical alarm signal value instance from instance "
                    "list at index: " << _tech_alarm_vector_max_index << ". "
                    << ex.what());
                  return DicesRcPhilipsIntellivueMP70::FAIL;
                }

                std::pair < std::map<intellivue::OIDType, unsigned int>::iterator, bool> ret_1 =
                  _map_al_source_to_tech_alarm_instance.insert(
                  std::pair<intellivue::OIDType, unsigned int>(
                  pdevice_al_list->value[ix].al_source,
                  _tech_alarm_vector_max_index++));
                if (!ret_1.second)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert "
                    "al_source and vector index into technical alarm map. "
                    "attribute_id: " << static_cast<int>(attribute_id));
                  return DicesRcPhilipsIntellivueMP70::FAIL;
                }

                if (context_instance->handle == 0
                  && signal_instance->handle == 0)
                {
                  // Generate new technical alarm handle
                  intellivue::Handle new_handle = 0;
                  DicesRcPhilipsIntellivueMP70 status = GenerateNewHandle(
                    &new_handle);
                  if (status != DicesRcPhilipsIntellivueMP70::OK)
                  {
                    LOG4CPLUS_ERROR(root_logger, sfn <<
                      DicesRcPhilipsIntellivueMP70StatusMessage::
                      DicesRcPhilipsIntellivueMP70ToString(status));
                    return status;
                  }
                  // Set new handle for this instance.
                  context_instance->handle = new_handle;
                  signal_instance->handle = new_handle;
                  if (_mds_instance_list.size() > 0)
                  {
                    context_instance->parent_handle =
                      _mds_instance_list.at(0).second->handle;
                    signal_instance->parent_handle =
                      _mds_instance_list.at(0).second->handle;
                  }
                }
              }
            }
          }
            break;
          case NOM_ATTR_AL_MON_P_AL_LIST:
          {
            intellivue::DevAlarmList* pdevice_al_list =
              reinterpret_cast<intellivue::DevAlarmList*>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!pdevice_al_list)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val to DevAlarmList. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }
            if (!pdevice_al_list->value)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "DevAlarmList contains a "
                "null pointer to DevAlarmEntry list. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            for (int ix = 0; ix < pdevice_al_list->count; ix++)
            {
              std::map<intellivue::OIDType, unsigned int>::iterator it;
              it = _map_al_source_to_phys_alarm_instance.find(
                pdevice_al_list->value[ix].al_source);
              if (it == _map_al_source_to_phys_alarm_instance.end())
              {
                if (_phys_alarm_vector_max_index
                  >= _physiological_alarm_context_response_instance_list.size())
                {
                  LOG4CPLUS_INFO(root_logger, sfn << "The maximum number of physiological alarm context "
                    "instances (" << _physiological_alarm_context_response_instance_list.size() << ") are already "
                    "in use. Inserting additional instances.");

                  unsigned int phys_al_inst_diff = _phys_alarm_vector_max_index
                      - _physiological_alarm_context_response_instance_list.size();
                  for (unsigned int inst_count = 0;
                       inst_count <= phys_al_inst_diff;
                       inst_count++)
                  {
                    std::pair<DicesRcDriver, ice::AlarmContext*> al_ctxt_pair(
                          DicesRcDriver::NO_NEW_DATA,
                          ice::AlarmContextTypeSupport::create_data());
                    if (!al_ctxt_pair.second)
                    {
                      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for physiological "
                                                          "alarm context instance");
                      return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
                    }
                    try
                    {
                      _physiological_alarm_context_response_instance_list.push_back(al_ctxt_pair);
                    }
                    catch(std::exception& ex)
                    {
                      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                          "physiological alarm context pair onto vector. " << ex.what());
                      return DicesRcPhilipsIntellivueMP70::FAIL;
                    }
                  }
                }
                if (_phys_alarm_vector_max_index
                  >= _physiological_alarm_signal_response_instance_list.size())
                {
                  LOG4CPLUS_INFO(root_logger, sfn << "The maximum number of physiological alarm signal "
                    "instances (" << _physiological_alarm_signal_response_instance_list.size() << ") are already "
                    "in use. Inserting additional instances.");

                  unsigned int phys_al_inst_diff = _phys_alarm_vector_max_index
                      - _physiological_alarm_signal_response_instance_list.size();
                  for (unsigned int inst_count = 0;
                       inst_count <= phys_al_inst_diff;
                       inst_count++)
                  {
                    std::pair<DicesRcDriver, ice::AlarmSignal*> al_signal_pair(
                          DicesRcDriver::NO_NEW_DATA,
                          ice::AlarmSignalTypeSupport::create_data());
                    if (!al_signal_pair.second)
                    {
                      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for physiological "
                                                          "alarm signal instance");
                      return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
                    }
                    try
                    {
                      _physiological_alarm_signal_response_instance_list.push_back(al_signal_pair);
                    }
                    catch(std::exception& ex)
                    {
                      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                          "physiological alarm signal pair onto vector. " << ex.what());
                      return DicesRcPhilipsIntellivueMP70::FAIL;
                    }
                  }
                }

                ice::AlarmContext* context_instance = nullptr;
                try
                {
                  context_instance =
                    _physiological_alarm_context_response_instance_list.at(
                    _phys_alarm_vector_max_index).second;
                  if (!context_instance)
                  {
                    LOG4CPLUS_ERROR(root_logger, sfn << "Physiological alarm "
                      "context instance is a null pointer at index: "
                      << _phys_alarm_vector_max_index);
                    return DicesRcPhilipsIntellivueMP70::FAIL;
                  }
                }
                catch (std::exception& ex)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get "
                    "physiological alarm context instance from instance list at "
                    "index: " << _phys_alarm_vector_max_index << ". "
                    << ex.what());
                  return DicesRcPhilipsIntellivueMP70::FAIL;
                }

                ice::AlarmSignal* signal_instance = nullptr;
                try
                {
                  signal_instance =
                    _physiological_alarm_signal_response_instance_list.at(
                    _phys_alarm_vector_max_index).second;
                  if (!signal_instance)
                  {
                    LOG4CPLUS_ERROR(root_logger, sfn << "Physiological alarm "
                      "signal instance is a null pointer at index: "
                      << _phys_alarm_vector_max_index);
                    return DicesRcPhilipsIntellivueMP70::FAIL;
                  }
                }
                catch (std::exception& ex)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get "
                    "physiological alarm signal value instance from instance "
                    "list at index: " << _phys_alarm_vector_max_index << ". "
                    << ex.what());
                  return DicesRcPhilipsIntellivueMP70::FAIL;
                }

                std::pair < std::map<intellivue::OIDType, unsigned int>::iterator, bool> ret_1 =
                  _map_al_source_to_phys_alarm_instance.insert(
                  std::pair<intellivue::OIDType, int>(
                  pdevice_al_list->value[ix].al_source,
                  _phys_alarm_vector_max_index++));
                if (!ret_1.second)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert "
                    "al_source and vector index into physiological alarm map. "
                    "attribute_id: " << static_cast<int>(attribute_id));
                  return DicesRcPhilipsIntellivueMP70::FAIL;
                }

                if (context_instance->handle == 0
                  && signal_instance->handle == 0)
                {
                  // Generate new physiological alarm handle
                  intellivue::Handle new_handle = 0;
                  DicesRcPhilipsIntellivueMP70 status = GenerateNewHandle(
                    &new_handle);
                  if (status != DicesRcPhilipsIntellivueMP70::OK)
                  {
                    LOG4CPLUS_ERROR(root_logger, sfn <<
                      DicesRcPhilipsIntellivueMP70StatusMessage::
                      DicesRcPhilipsIntellivueMP70ToString(status));
                    return status;
                  }
                  // Set new handle for this instance.
                  context_instance->handle = new_handle;
                  signal_instance->handle = new_handle;
                  if (_vmd_instance_list.size() > 0)
                  {
                    context_instance->parent_handle =
                      _vmd_instance_list.at(0).second->handle;
                    signal_instance->parent_handle =
                      _vmd_instance_list.at(0).second->handle;
                  }
                }
              }
            }
          }
            break;
          default:
            break;
        }
      }

      for (
        int iz = 0;
        iz < _extended_poll_response.pollReply.poll_info_list.value[ix].
        poll_info.value[iy].attributes.count;
        iz++)
      {
        intellivue::OIDType attribute_id = _extended_poll_response.pollReply.
          poll_info_list.value[ix].poll_info.value[iy].attributes.value[iz].
          attribute_id;
        switch (attribute_id)
        {
          case NOM_ATTR_ID_HANDLE:
          {
            intellivue::Handle* phandle =
              reinterpret_cast<intellivue::Handle *>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!phandle)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into Handle. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }
            // NOTE: Handles have already been generated above by the driver.

            // Set parent handles.
            std::map<intellivue::OIDType, unsigned int>::iterator tech_it;
            for (
              tech_it = _map_al_source_to_tech_alarm_instance.begin();
              tech_it != _map_al_source_to_tech_alarm_instance.end();
              tech_it++)
            {
              if (_mds_instance_list.size() > 0)
              {
                _technical_alarm_signal_response_instance_list.at(
                  tech_it->second).second->parent_handle =
                  _mds_instance_list.at(0).second->handle;
              }
            }

            std::map<intellivue::OIDType, unsigned int>::iterator phys_it;
            for (
              phys_it = _map_al_source_to_phys_alarm_instance.begin();
              phys_it != _map_al_source_to_phys_alarm_instance.end();
              phys_it++)
            {
              if (_vmd_instance_list.size() > 0)
              {
                _physiological_alarm_signal_response_instance_list.at(
                  phys_it->second).second->parent_handle =
                  _vmd_instance_list.at(0).second->handle;
              }
            }
          }
            break;
          case NOM_ATTR_ID_TYPE:
          {
            intellivue::TYPE* ptype =
              reinterpret_cast<intellivue::TYPE*>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!ptype)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into TYPE. attribute_id: " << static_cast<int>(
                attribute_id));
              break;
            }

            ice::NomPartition dices_partition =
              ice::NomPartition::nom_part_unspec;
            DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
              ConvertIntellivueNomPartitionToDicesNomPartition(
              &dices_partition,
              ptype->partition);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }

            std::map<intellivue::OIDType, unsigned int>::iterator tech_it;
            for (
              tech_it = _map_al_source_to_tech_alarm_instance.begin();
              tech_it != _map_al_source_to_tech_alarm_instance.end();
              tech_it++)
            {
              _technical_alarm_signal_response_instance_list.at(
                tech_it->second).second->type.partition = dices_partition;
              _technical_alarm_signal_response_instance_list.at(
                tech_it->second).second->type.code = ptype->code;

              if (_technical_alarm_context_response_instance_list.at(
                tech_it->second).second->type.partition != ptype->partition)
              {
                _technical_alarm_context_response_instance_list.at(
                  tech_it->second).second->type.partition = dices_partition;
                _technical_alarm_context_response_instance_list.at(
                  tech_it->second).first = DicesRcDriver::OK;
              }

              if (_technical_alarm_context_response_instance_list.at(
                tech_it->second).second->type.code != ptype->code)
              {
                _technical_alarm_context_response_instance_list.at(
                  tech_it->second).second->type.code = ptype->code;
                _technical_alarm_context_response_instance_list.at(
                  tech_it->second).first = DicesRcDriver::OK;
              }
            }

            std::map<intellivue::OIDType, unsigned int>::iterator phys_it;
            for (
              phys_it = _map_al_source_to_phys_alarm_instance.begin();
              phys_it != _map_al_source_to_phys_alarm_instance.end();
              phys_it++)
            {
              _physiological_alarm_signal_response_instance_list.at(
                phys_it->second).second->type.partition = dices_partition;
              _physiological_alarm_signal_response_instance_list.at(
                phys_it->second).second->type.code = ptype->code;

              if (_physiological_alarm_context_response_instance_list.at(
                phys_it->second).second->type.partition != dices_partition)
              {
                _physiological_alarm_context_response_instance_list.at(
                  phys_it->second).second->type.partition = dices_partition;
                _physiological_alarm_context_response_instance_list.at(
                  phys_it->second).first = DicesRcDriver::OK;
              }

              if (_physiological_alarm_context_response_instance_list.at(
                phys_it->second).second->type.code != ptype->code)
              {
                _physiological_alarm_context_response_instance_list.at(
                  phys_it->second).second->type.code = ptype->code;
                _physiological_alarm_context_response_instance_list.at(
                  phys_it->second).first = DicesRcDriver::OK;
              }
            }
          }
            break;
          case NOM_ATTR_DEV_AL_COND:
          {
            intellivue::DeviceAlertCondition* pdevice_al_cond =
              reinterpret_cast<intellivue::DeviceAlertCondition*>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!pdevice_al_cond)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into DeviceAlertCondition. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }
            // TODO Should anything be done with DeviceAlertCondition?
          }
            break;
          case NOM_ATTR_AL_MON_T_AL_LIST:
          {
            intellivue::DevAlarmList* pdevice_al_list =
              reinterpret_cast<intellivue::DevAlarmList*>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!pdevice_al_list)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into technical DevAlarmList. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }
            if (!pdevice_al_list->value)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "DevAlarmList contains a "
                "null pointer to DevAlarmEntry list. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            for (int ix = 0; ix < pdevice_al_list->count; ix++)
            {
              intellivue::OIDType al_source = pdevice_al_list->value[ix].
                al_source;
              unsigned int vect_index = _map_al_source_to_tech_alarm_instance.at(
                al_source);

              _technical_alarm_signal_response_instance_list.at(
                vect_index).second->alarm_source = pdevice_al_list->value[ix].
                al_source;
              if (_technical_alarm_context_response_instance_list.at(
                vect_index).second->alarm_source != pdevice_al_list->value[ix].
                al_source)
              {
                _technical_alarm_context_response_instance_list.at(
                  vect_index).second->alarm_source = pdevice_al_list->
                  value[ix].al_source;
                _technical_alarm_context_response_instance_list.at(
                  vect_index).first = DicesRcDriver::OK;
              }

              _technical_alarm_context_response_instance_list.at(
                vect_index).second->alarm_condition.alarm_code =
                pdevice_al_list->value[ix].al_code;

              if (pdevice_al_list->value[ix].al_state & AL_LATCHED)
              {
                _technical_alarm_signal_response_instance_list.at(
                  vect_index).second->latch = ice::latching;
                if (_technical_alarm_context_response_instance_list.at(
                  vect_index).second->latch != ice::latching)
                {
                  _technical_alarm_context_response_instance_list.at(
                    vect_index).second->latch = ice::latching;
                  _technical_alarm_context_response_instance_list.at(
                    vect_index).first = DicesRcDriver::OK;
                }
              }
              else
              {
                _technical_alarm_signal_response_instance_list.at(
                  vect_index).second->latch = ice::non_latching;
                if (_technical_alarm_context_response_instance_list.at(
                  vect_index).second->latch != ice::non_latching)
                {
                  _technical_alarm_context_response_instance_list.at(
                    vect_index).second->latch = ice::non_latching;
                  _technical_alarm_context_response_instance_list.at(
                    vect_index).first = DicesRcDriver::OK;
                }
              }

              // Clear inactivation_list
              _technical_alarm_signal_response_instance_list.at(
                vect_index).second->inactivation_list.length(0);

              if (pdevice_al_list->value[ix].al_state & AL_INHIBITED)
              {
                int current_length =
                  _technical_alarm_signal_response_instance_list.at(
                  vect_index).second->inactivation_list.length();
                int max_length = current_length + 1;
                if (!_technical_alarm_signal_response_instance_list.at(
                  vect_index).second->inactivation_list.ensure_length(
                  max_length,
                  max_length))
                {
                  LOG4CPLUS_ERROR(root_logger, sfn << "Unable to "
                    "ensure length (" << max_length << ") of alarm signal "
                    "inactivation_list sequence. The al_state is "
                    "AL_INHIBITED. attribute_id: " << static_cast<int>(
                    attribute_id));
                  continue;
                }

                // NOTE: Using system time
                if (DicesTime::GetTimeOfDayUtc(
                  &_technical_alarm_signal_response_instance_list.at(
                  vect_index).second->inactivation_list[current_length].
                  timestamp) != 0)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get "
                    "UTC time of day from DicesTime tool for alarm "
                    "signal inactivation_list timestamp. The al_state is "
                    "AL_INHIBITED. attribute_id: " << static_cast<int>(
                    attribute_id));
                  continue;
                }
                _technical_alarm_signal_response_instance_list.at(
                  vect_index).second->inactivation_list[current_length].state =
                  ice::si_alarm_off;
              }

              if (pdevice_al_list->value[ix].al_state & AL_SUSPENDED)
              {
                int current_length =
                  _technical_alarm_signal_response_instance_list.at(
                  vect_index).second->inactivation_list.length();
                int max_length = current_length + 1;
                if (!_technical_alarm_signal_response_instance_list.at(
                  vect_index).second->inactivation_list.ensure_length(
                  max_length,
                  max_length))
                {
                  LOG4CPLUS_ERROR(root_logger, sfn << "Unable to ensure "
                    "length (" << max_length << ") of alarm signal "
                    "inactivation_list sequence. The al_state is "
                    "AL_SUSPENDED. attribute_id: " << static_cast<int>(
                    attribute_id));
                  continue;
                }

                // NOTE: Using system time
                if (DicesTime::GetTimeOfDayUtc(
                  &_technical_alarm_signal_response_instance_list.at(
                  vect_index).second->inactivation_list[current_length].
                  timestamp) != 0)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get UTC time "
                    "of day from DicesTime tool for technical alarm signal "
                    "inactivation_list timestamp. The al_state is "
                    "AL_SUSPENDED. attribute_id: " << static_cast<int>(
                    attribute_id));
                  continue;
                }
                _technical_alarm_signal_response_instance_list.at(
                  vect_index).second->inactivation_list[current_length].state =
                  ice::si_alarm_paused;
              }

              // Begin setting priorities. Make sure highest priorities are set
              // over the lowest priorities.
              if (pdevice_al_list->value[ix].al_type == NO_ALERT)
              {
                _technical_alarm_signal_response_instance_list.at(
                  vect_index).second->initial_priority =
                  ice::no_priority_provided;
                if (_technical_alarm_context_response_instance_list.at(
                  vect_index).second->initial_priority
                  != ice::no_priority_provided)
                {
                  _technical_alarm_context_response_instance_list.at(
                    vect_index).second->initial_priority =
                    ice::no_priority_provided;
                  _technical_alarm_context_response_instance_list.at(
                    vect_index).first = DicesRcDriver::OK;
                }
              }
              if (pdevice_al_list->value[ix].al_type & LOW_PRI_T_AL)
              {
                _technical_alarm_signal_response_instance_list.at(
                  vect_index).second->initial_priority = ice::low_priority;
                if (_technical_alarm_context_response_instance_list.at(
                  vect_index).second->initial_priority != ice::low_priority)
                {
                  _technical_alarm_context_response_instance_list.at(
                    vect_index).second->initial_priority = ice::low_priority;
                  _technical_alarm_context_response_instance_list.at(
                    vect_index).first = DicesRcDriver::OK;
                }
              }
              if (pdevice_al_list->value[ix].al_type & MED_PRI_T_AL)
              {
                _technical_alarm_signal_response_instance_list.at(
                  vect_index).second->initial_priority = ice::medium_priority;
                if (_technical_alarm_context_response_instance_list.at(
                  vect_index).second->initial_priority != ice::medium_priority)
                {
                  _technical_alarm_context_response_instance_list.at(
                    vect_index).second->initial_priority =
                    ice::medium_priority;
                  _technical_alarm_context_response_instance_list.at(
                    vect_index).first = DicesRcDriver::OK;
                }
              }
              if (pdevice_al_list->value[ix].al_type & HI_PRI_T_AL)
              {
                _technical_alarm_signal_response_instance_list.at(
                  vect_index).second->initial_priority = ice::high_priority;
                if (_technical_alarm_context_response_instance_list.at(
                  vect_index).second->initial_priority != ice::high_priority)
                {
                  _technical_alarm_context_response_instance_list.at(
                    vect_index).second->initial_priority = ice::high_priority;
                  _technical_alarm_context_response_instance_list.at(
                    vect_index).first = DicesRcDriver::OK;
                }
              }

              switch (pdevice_al_list->value[ix].alert_info_id)
              {
                case GEN_ALMON_INFO:
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "The alert_info_id is "
                    "set to GEN_ALMON_INFO, an AlMonGenInfo structure is "
                    "appended. Currently, the IntelliVue monitor only "
                    "supports the StrAlMonInfo data type. attribute_id: "
                    << static_cast<int>(attribute_id));

                  intellivue::AlMonGenInfo* pal_mon_gen_info =
                    reinterpret_cast<intellivue::AlMonGenInfo*>(
                    pdevice_al_list->value[ix].alert_info);
                  if (!pal_mon_gen_info)
                  {
                    LOG4CPLUS_WARN(root_logger, sfn << "The alert_info "
                      "pointer is a null pointer, therefore AlMonGenInfo "
                      "could not be parsed successfully. attribute_id: "
                      << static_cast<int>(attribute_id));
                    break;
                  }
                  // TODO Should anything be done with AlMonGenInfo?
                }
                  break;
                case STR_ALMON_INFO:
                {
                  intellivue::StrAlMonInfo* pstr_al_mon_info =
                    reinterpret_cast<intellivue::StrAlMonInfo*>(
                    pdevice_al_list->value[ix].alert_info);
                  if (!pstr_al_mon_info)
                  {
                    LOG4CPLUS_WARN(root_logger, sfn << "The alert_info "
                      "pointer is a null pointer, therefore StrAlMonInfo "
                      "could not be parsed successfully. attribute_id: "
                      << static_cast<int>(attribute_id));
                    break;
                  }
                  if (!pstr_al_mon_info->string.value)
                  {
                    LOG4CPLUS_WARN(root_logger, sfn << "In StrAlMonInfo, "
                      "the String value is a null pointer. attribute_id: "
                      << static_cast<int>(attribute_id));
                    break;
                  }

                  std::string info_string;
                  for (
                    int iindex = 0;
                    iindex < pstr_al_mon_info->string.length;
                    iindex++)
                  {
                    uint8_t ch8 = '\0';
                    uint16_t ch16 = pstr_al_mon_info->string.value[iindex];
                    // Convert to byte array
                    uint8_t byte_0 = ch16 & 0x00ff;
                    uint8_t byte_1 = ch16 >> 8;
                    uint8_t buf[2] = { byte_0, byte_1 };

                    ch16 = ntohs(*(reinterpret_cast<uint16_t*>(&buf[0])));

                    DicesRcPhilipsIntellivueMP70 status =
                      IntellivueUtils::Convert16BitUnicodeToAscii(
                      ch16,
                      &ch8);
                    if (status != DicesRcPhilipsIntellivueMP70::OK)
                    {
                      LOG4CPLUS_ERROR(root_logger, sfn <<
                        DicesRcPhilipsIntellivueMP70StatusMessage::
                        DicesRcPhilipsIntellivueMP70ToString(status));
                      return status;
                    }
                    info_string += static_cast<char>(ch8);
                  }

                  if (strncmp(
                    _technical_alarm_context_response_instance_list.at(
                    vect_index).second->event_message,
                    info_string.c_str(),
                    ice::LONG_STRING_LEN) != 0)
                  {
                    strncpy(
                      _technical_alarm_context_response_instance_list.at(
                      vect_index).second->event_message,
                      info_string.c_str(),
                      ice::LONG_STRING_LEN);
                    _technical_alarm_context_response_instance_list.at(
                      vect_index).second->event_message[
                      ice::LONG_STRING_LEN] = '\0';

                    _technical_alarm_context_response_instance_list.at(
                      vect_index).first = DicesRcDriver::OK;
                  }
                }
                  break;
                default:
                  LOG4CPLUS_WARN(root_logger, sfn << "Unknown alert_info_id ("
                    << static_cast<int>(pdevice_al_list->value[ix].
                    alert_info_id) << ") received from Intellivue. "
                    "attribute_id: " << static_cast<int>(attribute_id));
                  break;
              }
              _technical_alarm_signal_response_instance_list.at(
                vect_index).first = DicesRcDriver::OK;
            }
          }
            break;
          case NOM_ATTR_AL_MON_P_AL_LIST:
          {
            intellivue::DevAlarmList* pdevice_al_list =
              reinterpret_cast<intellivue::DevAlarmList*>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!pdevice_al_list)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into physiological DevAlarmList. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }
            if (!pdevice_al_list->value)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "DevAlarmList contains a "
                "null pointer to DevAlarmEntry list. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            for (int ix = 0; ix < pdevice_al_list->count; ix++)
            {
              intellivue::OIDType al_source = pdevice_al_list->value[ix].
                al_source;
              unsigned int vect_index = _map_al_source_to_phys_alarm_instance.at(
                al_source);

              _physiological_alarm_signal_response_instance_list.at(
                vect_index).second->alarm_source = pdevice_al_list->value[ix].
                al_source;
              if (_physiological_alarm_context_response_instance_list.at(
                vect_index).second->alarm_source != pdevice_al_list->value[ix].
                al_source)
              {
                _physiological_alarm_context_response_instance_list.at(
                  vect_index).second->alarm_source = pdevice_al_list->
                  value[ix].al_source;
                _physiological_alarm_context_response_instance_list.at(
                  vect_index).first = DicesRcDriver::OK;
              }

              _physiological_alarm_context_response_instance_list.at(
                vect_index).second->alarm_condition.alarm_code =
                pdevice_al_list->value[ix].al_code;

              if (pdevice_al_list->value[ix].al_state & AL_LATCHED)
              {
                _physiological_alarm_signal_response_instance_list.at(
                  vect_index).second->latch = ice::latching;
                if (_physiological_alarm_context_response_instance_list.at(
                  vect_index).second->latch != ice::latching)
                {
                  _physiological_alarm_context_response_instance_list.at(
                    vect_index).second->latch = ice::latching;
                  _physiological_alarm_context_response_instance_list.at(
                    vect_index).first = DicesRcDriver::OK;
                }
              }
              else
              {
                _physiological_alarm_signal_response_instance_list.at(
                  vect_index).second->latch = ice::non_latching;
                if (_physiological_alarm_context_response_instance_list.at(
                  vect_index).second->latch != ice::non_latching)
                {
                  _physiological_alarm_context_response_instance_list.at(
                    vect_index).second->latch = ice::non_latching;
                  _physiological_alarm_context_response_instance_list.at(
                    vect_index).first = DicesRcDriver::OK;
                }
              }

              // Clear inactivation_list
              _physiological_alarm_signal_response_instance_list.at(
                vect_index).second->inactivation_list.length(0);

              if (pdevice_al_list->value[ix].al_state & AL_INHIBITED)
              {
                int current_length =
                  _physiological_alarm_signal_response_instance_list.at(
                  vect_index).second->inactivation_list.length();
                int max_length = current_length + 1;
                if (!_physiological_alarm_signal_response_instance_list.at(
                  vect_index).second->inactivation_list.ensure_length(
                  max_length,
                  max_length))
                {
                  LOG4CPLUS_ERROR(root_logger, sfn << "Unable to "
                    "ensure length (" << max_length << ") of alarm signal "
                    "inactivation_list sequence. The al_state is "
                    "AL_INHIBITED. attribute_id: " << static_cast<int>(
                    attribute_id));
                  continue;
                }

                // NOTE: Using system time
                if (DicesTime::GetTimeOfDayUtc(
                  &_physiological_alarm_signal_response_instance_list.at(
                  vect_index).second->inactivation_list[current_length].
                  timestamp) != 0)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get "
                    "UTC time of day from DicesTime tool for alarm "
                    "signal inactivation_list timestamp. The al_state is "
                    "AL_INHIBITED. attribute_id: " << static_cast<int>(
                    attribute_id));
                  continue;
                }
                _physiological_alarm_signal_response_instance_list.at(
                  vect_index).second->inactivation_list[current_length].state =
                  ice::si_alarm_off;
              }

              if (pdevice_al_list->value[ix].al_state & AL_SUSPENDED)
              {
                int current_length =
                  _physiological_alarm_signal_response_instance_list.at(
                  vect_index).second->inactivation_list.length();
                int max_length = current_length + 1;
                if (!_physiological_alarm_signal_response_instance_list.at(
                  vect_index).second->inactivation_list.ensure_length(
                  max_length,
                  max_length))
                {
                  LOG4CPLUS_ERROR(root_logger, sfn << "Unable to ensure "
                    "length (" << max_length << ") of alarm signal "
                    "inactivation_list sequence. The al_state is "
                    "AL_SUSPENDED. attribute_id: " << static_cast<int>(
                    attribute_id));
                  continue;
                }

                // NOTE: Using system time
                if (DicesTime::GetTimeOfDayUtc(
                  &_physiological_alarm_signal_response_instance_list.at(
                  vect_index).second->inactivation_list[current_length].
                  timestamp) != 0)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get UTC time "
                    "of day from DicesTime tool for physiological alarm signal "
                    "inactivation_list timestamp. The al_state is "
                    "AL_SUSPENDED. attribute_id: " << static_cast<int>(
                    attribute_id));
                  continue;
                }
                _physiological_alarm_signal_response_instance_list.at(
                  vect_index).second->inactivation_list[current_length].state =
                  ice::si_alarm_paused;
              }

              // Begin setting priorities. Make sure highest priorities are set
              // over the lowest priorities.
              if (pdevice_al_list->value[ix].al_type == NO_ALERT)
              {
                _physiological_alarm_signal_response_instance_list.at(
                  vect_index).second->initial_priority =
                  ice::no_priority_provided;
                if (_physiological_alarm_context_response_instance_list.at(
                  vect_index).second->initial_priority
                  != ice::no_priority_provided)
                {
                  _physiological_alarm_context_response_instance_list.at(
                    vect_index).second->initial_priority =
                    ice::no_priority_provided;
                  _physiological_alarm_context_response_instance_list.at(
                    vect_index).first = DicesRcDriver::OK;
                }
              }
              if (pdevice_al_list->value[ix].al_type & LOW_PRI_T_AL)
              {
                _physiological_alarm_signal_response_instance_list.at(
                  vect_index).second->initial_priority = ice::low_priority;
                if (_physiological_alarm_context_response_instance_list.at(
                  vect_index).second->initial_priority != ice::low_priority)
                {
                  _physiological_alarm_context_response_instance_list.at(
                    vect_index).second->initial_priority = ice::low_priority;
                  _physiological_alarm_context_response_instance_list.at(
                    vect_index).first = DicesRcDriver::OK;
                }
              }
              if (pdevice_al_list->value[ix].al_type & MED_PRI_T_AL)
              {
                _physiological_alarm_signal_response_instance_list.at(
                  vect_index).second->initial_priority = ice::medium_priority;
                if (_physiological_alarm_context_response_instance_list.at(
                  vect_index).second->initial_priority != ice::medium_priority)
                {
                  _physiological_alarm_context_response_instance_list.at(
                    vect_index).second->initial_priority =
                    ice::medium_priority;
                  _physiological_alarm_context_response_instance_list.at(
                    vect_index).first = DicesRcDriver::OK;
                }
              }
              if (pdevice_al_list->value[ix].al_type & HI_PRI_T_AL)
              {
                _physiological_alarm_signal_response_instance_list.at(
                  vect_index).second->initial_priority = ice::high_priority;
                if (_physiological_alarm_context_response_instance_list.at(
                  vect_index).second->initial_priority != ice::high_priority)
                {
                  _physiological_alarm_context_response_instance_list.at(
                    vect_index).second->initial_priority = ice::high_priority;
                  _physiological_alarm_context_response_instance_list.at(
                    vect_index).first = DicesRcDriver::OK;
                }
              }

              switch (pdevice_al_list->value[ix].alert_info_id)
              {
                case GEN_ALMON_INFO:
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "The alert_info_id is "
                    "set to GEN_ALMON_INFO, an AlMonGenInfo structure is "
                    "appended. Currently, the IntelliVue monitor only "
                    "supports the StrAlMonInfo data type. attribute_id: "
                    << static_cast<int>(attribute_id));

                  intellivue::AlMonGenInfo* pal_mon_gen_info =
                    reinterpret_cast<intellivue::AlMonGenInfo*>(
                    pdevice_al_list->value[ix].alert_info);
                  if (!pal_mon_gen_info)
                  {
                    LOG4CPLUS_WARN(root_logger, sfn << "The alert_info "
                      "pointer is a null pointer, therefore AlMonGenInfo "
                      "could not be parsed successfully. attribute_id: "
                      << static_cast<int>(attribute_id));
                    break;
                  }
                  // TODO Should anything be done with AlMonGenInfo?
                }
                  break;
                case STR_ALMON_INFO:
                {
                  intellivue::StrAlMonInfo* pstr_al_mon_info =
                    reinterpret_cast<intellivue::StrAlMonInfo*>(
                    pdevice_al_list->value[ix].alert_info);
                  if (!pstr_al_mon_info)
                  {
                    LOG4CPLUS_WARN(root_logger, sfn << "The alert_info "
                      "pointer is a null pointer, therefore StrAlMonInfo "
                      "could not be parsed successfully. attribute_id: "
                      << static_cast<int>(attribute_id));
                    break;
                  }
                  if (!pstr_al_mon_info->string.value)
                  {
                    LOG4CPLUS_WARN(root_logger, sfn << "In StrAlMonInfo, "
                      "the String value is a null pointer. attribute_id: "
                      << static_cast<int>(attribute_id));
                    break;
                  }

                  std::string info_string;
                  for (
                    int iindex = 0;
                    iindex < pstr_al_mon_info->string.length;
                    iindex++)
                  {
                    uint8_t ch8 = '\0';
                    uint16_t ch16 = pstr_al_mon_info->string.value[iindex];
                    // Convert to byte array
                    uint8_t byte_0 = ch16 & 0x00ff;
                    uint8_t byte_1 = ch16 >> 8;
                    uint8_t buf[2] = { byte_0, byte_1 };

                    ch16 = ntohs(*(reinterpret_cast<uint16_t*>(&buf[0])));

                    DicesRcPhilipsIntellivueMP70 status =
                      IntellivueUtils::Convert16BitUnicodeToAscii(
                      ch16,
                      &ch8);
                    if (status != DicesRcPhilipsIntellivueMP70::OK)
                    {
                      LOG4CPLUS_ERROR(root_logger, sfn <<
                        DicesRcPhilipsIntellivueMP70StatusMessage::
                        DicesRcPhilipsIntellivueMP70ToString(status));
                      return status;
                    }
                    info_string += static_cast<char>(ch8);
                  }

                  if (strncmp(
                    _physiological_alarm_context_response_instance_list.at(
                    vect_index).second->event_message,
                    info_string.c_str(),
                    ice::LONG_STRING_LEN) != 0)
                  {
                    strncpy(
                      _physiological_alarm_context_response_instance_list.at(
                      vect_index).second->event_message,
                      info_string.c_str(),
                      ice::LONG_STRING_LEN);
                    _physiological_alarm_context_response_instance_list.at(
                      vect_index).second->event_message[
                      ice::LONG_STRING_LEN] = '\0';

                    _physiological_alarm_context_response_instance_list.at(
                      vect_index).first = DicesRcDriver::OK;
                  }
                }
                  break;
                default:
                  LOG4CPLUS_WARN(root_logger, sfn << "Unknown alert_info_id ("
                    << static_cast<int>(pdevice_al_list->value[ix].
                    alert_info_id) << ") received from Intellivue. "
                    "attribute_id: " << static_cast<int>(attribute_id));
                  break;
              }
              _physiological_alarm_signal_response_instance_list.at(
                vect_index).first = DicesRcDriver::OK;
            }
          }
            break;
          default:
            break;
        }
      }
    }
  }
  for (
    int ix = 0;
    ix < _technical_alarm_context_response_instance_list.size();
    ix++)
  {
    // For all context dds instances that have changed, increment context
    // sequence number and set for the same number in observed value.
    if (_technical_alarm_context_response_instance_list.at(ix).first
      == DicesRcDriver::OK)
    {
      _technical_alarm_context_response_instance_list.at(ix).second->
        context_seq_number++;
      _technical_alarm_signal_response_instance_list.at(ix).second->
        context_seq_number =
        _technical_alarm_context_response_instance_list.at(ix).second->
        context_seq_number;
    }
  }
  for (
    int ix = 0;
    ix < _physiological_alarm_context_response_instance_list.size();
    ix++)
  {
    // For all context dds instances that have changed, increment context
    // sequence number and set for the same number in observed value.
    if (_physiological_alarm_context_response_instance_list.at(ix).first
      == DicesRcDriver::OK)
    {
      _physiological_alarm_context_response_instance_list.at(ix).second->
        context_seq_number++;
      _physiological_alarm_signal_response_instance_list.at(ix).second->
        context_seq_number =
        _physiological_alarm_context_response_instance_list.at(ix).second->
        context_seq_number;
    }
  }
  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 DDPhilipsIntellivueMP70Parser::
SetExtendedEnumResponseData()
{
  static const char* sfn = "DDPhilipsIntellivueMP70Parser::"
    "SetExtendedEnumResponseData() ";

  intellivue::GlbHandle glb_handle = {
    _extended_poll_response.actionresult.managed_object.m_obj_inst.
    context_id,
    _extended_poll_response.actionresult.managed_object.m_obj_inst.
    handle
  };

  for (
    int ix = 0;
    ix < _extended_poll_response.pollReply.poll_info_list.count;
    ix++)
  {
    if (!_extended_poll_response.pollReply.poll_info_list.value)
    {
      LOG4CPLUS_WARN(root_logger, sfn << "SingleContextPoll array in "
        "poll_info_list is a null pointer");
      break;
    }
    intellivue::MdsContext single_context_poll_context_id =
      _extended_poll_response.pollReply.poll_info_list.value[ix].
      context_id;

    for (
      int iy = 0;
      iy < _extended_poll_response.pollReply.poll_info_list.value[ix].
      poll_info.count;
      iy++)
    {
      if (!_extended_poll_response.pollReply.poll_info_list.value[ix].
        poll_info.value)
      {
        LOG4CPLUS_WARN(root_logger, sfn << "ObservationPoll array in "
          "poll_info is a null pointer");
        break;
      }

      // Get handles of all enum observed values
      std::vector<intellivue::Handle> handle_list;
      for (
        int iz = 0;
        iz < _extended_poll_response.pollReply.poll_info_list.value[ix].
        poll_info.value[iy].attributes.count;
        iz++)
      {
        try
        {
          handle_list.push_back(
            _extended_poll_response.pollReply.poll_info_list.value[ix].
            poll_info.value[iy].obj_handle);
        }
        catch (const std::exception& ex)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert handle "
            "into vector. " << ex.what());
          return DicesRcPhilipsIntellivueMP70::VECTOR_INSERT_FAILURE;
        }
      }
      // Set absolute timestamp for all metrics found
      if (_extended_poll_response.pollReply.abs_time_stamp.century != 0xFF
        || _extended_poll_response.pollReply.abs_time_stamp.year != 0xFF
        || _extended_poll_response.pollReply.abs_time_stamp.month != 0xFF
        || _extended_poll_response.pollReply.abs_time_stamp.day != 0xFF
        || _extended_poll_response.pollReply.abs_time_stamp.hour != 0xFF
        || _extended_poll_response.pollReply.abs_time_stamp.minute != 0xFF
        || _extended_poll_response.pollReply.abs_time_stamp.second != 0xFF
        || _extended_poll_response.pollReply.abs_time_stamp.sec_fractions != 0xFF)
      {
        for (int ij = 0; ij < handle_list.size(); ij++)
        {
          for (int ik = 0;
            ik < _enumeration_meas_observed_value_response_instance_list.
            size();
            ik++)
          {
            if (_enumeration_meas_observed_value_response_instance_list.
              at(ik).second->handle == handle_list.at(ij))
            {
              if (!_enumeration_meas_observed_value_response_instance_list.
                at(ik).second->device_timestamp)
              {
                _enumeration_meas_observed_value_response_instance_list.
                  at(ik).second->device_timestamp =
                  reinterpret_cast<ice::Timespec *>(
                  DDS::Heap_malloc(sizeof(ice::Timespec)));
                if (!_enumeration_meas_observed_value_response_instance_list.
                  at(ik).second->device_timestamp)
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "Failed to "
                    "allocate memory for ice::Timespec");
                  continue;
                }
              }
              DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                ConvertIntellivueAbsoluteTimeToDicesTimespec(
                _enumeration_meas_observed_value_response_instance_list.
                at(ik).second->device_timestamp,
                _extended_poll_response.pollReply.abs_time_stamp);
              if (status != DicesRcPhilipsIntellivueMP70::OK)
              {
                LOG4CPLUS_ERROR(root_logger, sfn <<
                  DicesRcPhilipsIntellivueMP70StatusMessage::
                  DicesRcPhilipsIntellivueMP70ToString(status));
                return status;
              }
            }
          }
        }
      }

      for (int ij = 0; ij < handle_list.size(); ij++)
      {
        for (int ik = 0;
          ik < _enumeration_meas_observed_value_response_instance_list.
          size();
          ik++)
        {
          if (_enumeration_meas_observed_value_response_instance_list.
            at(ik).second->handle
            == handle_list.at(ij))
          {
            // Set relative timestamp for all metrics found
            if (!_enumeration_meas_observed_value_response_instance_list.
              at(ik).second->device_relative_timestamp)
            {
              _enumeration_meas_observed_value_response_instance_list.
                at(ik).second->device_relative_timestamp =
                reinterpret_cast<ice::Duration *>(
                DDS::Heap_malloc(sizeof(ice::Duration)));
              if (!_enumeration_meas_observed_value_response_instance_list.
                at(ik).second->device_relative_timestamp)
              {
                LOG4CPLUS_WARN(root_logger, sfn << "Failed to "
                  "allocate memory for ice::Duration");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
            }
            DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
              ConvertIntellivueRelativeTimeToDicesDuration(
              _enumeration_meas_observed_value_response_instance_list.
              at(ik).second->device_relative_timestamp,
              _extended_poll_response.pollReply.rel_time_stamp);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }
            _enumeration_meas_observed_value_response_instance_list.
              at(ik).second->type.code = _extended_poll_response.
              pollReply.polled_obj_type.code;

            status = IntellivueUtils::
              ConvertIntellivueNomPartitionToDicesNomPartition(
              &_enumeration_meas_observed_value_response_instance_list.
              at(ik).second->type.partition,
              _extended_poll_response.pollReply.polled_obj_type.partition);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }
          }
        }
      }
      for (
        int iz = 0;
        iz < _extended_poll_response.pollReply.poll_info_list.value[ix].
        poll_info.value[iy].attributes.count;
        iz++)
      {
        if (!_extended_poll_response.pollReply.poll_info_list.value[ix].
          poll_info.value[iy].attributes.value)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "AVAType array in "
            "attributes is a null pointer");
          break;
        }

        intellivue::Handle obj_handle =
          _extended_poll_response.pollReply.poll_info_list.value[ix].
          poll_info.value[iy].obj_handle;

        std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>
          unique_handle(glb_handle.context_id, glb_handle.handle, single_context_poll_context_id, obj_handle);

        std::map<
          std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
          std::map < intellivue::Handle, unsigned int>>::iterator it;
        it = _map_handle_to_enumeration_instance.find(unique_handle);
        if (it == _map_handle_to_enumeration_instance.end())
        {
          if (_enumeration_vector_max_index
              >= _enumeration_meas_context_response_instance_list.size()
              ||_enumeration_vector_max_index
              >= _enumeration_sett_context_response_instance_list.size()
              ||_enumeration_vector_max_index
              >= _enumeration_calc_context_response_instance_list.size())
          {
            LOG4CPLUS_INFO(root_logger, sfn << "The maximum number of enumeration context "
              "instances are already in use for meas, sett and calc instance lists. "
              "Inserting additional instances.");

            unsigned int enum_meas_inst_diff = _enumeration_vector_max_index
                - _enumeration_meas_context_response_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= enum_meas_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::EnumerationContext*> enum_meas_ctxt_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::EnumerationContextTypeSupport::create_data());
              if (!enum_meas_ctxt_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for enumeration measurement context instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _enumeration_meas_context_response_instance_list.push_back(enum_meas_ctxt_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "enumeration measurement context pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }

            unsigned int enum_sett_inst_diff = _enumeration_vector_max_index
                - _enumeration_sett_context_response_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= enum_sett_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::EnumerationContext*> enum_sett_ctxt_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::EnumerationContextTypeSupport::create_data());
              if (!enum_sett_ctxt_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for enumeration setting context instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _enumeration_sett_context_response_instance_list.push_back(enum_sett_ctxt_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "enumeration setting context pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }

            unsigned int enum_calc_inst_diff = _enumeration_vector_max_index
                - _enumeration_calc_context_response_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= enum_calc_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::EnumerationContext*> enum_calc_ctxt_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::EnumerationContextTypeSupport::create_data());
              if (!enum_calc_ctxt_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for enumeration calculation context instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _enumeration_calc_context_response_instance_list.push_back(enum_calc_ctxt_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "enumeration calculation context pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }
          }
          if (_enumeration_vector_max_index
              >= _enumeration_meas_observed_value_response_instance_list.size()
              || _enumeration_vector_max_index
              >= _enumeration_sett_observed_value_response_instance_list.size()
              || _enumeration_vector_max_index
              >= _enumeration_calc_observed_value_response_instance_list.size())
          {
            LOG4CPLUS_INFO(root_logger, sfn << "The maximum number of enumeration observed value "
              "instances are already in use for meas, sett and calc instance lists. "
              "Inserting additional instances.");

            unsigned int enum_meas_inst_diff = _enumeration_vector_max_index
                - _enumeration_meas_observed_value_response_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= enum_meas_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::EnumerationObservedValue*> enum_meas_obs_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::EnumerationObservedValueTypeSupport::create_data());
              if (!enum_meas_obs_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for enumeration measurement observed value instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _enumeration_meas_observed_value_response_instance_list.push_back(enum_meas_obs_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "enumeration measurement observed value pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }

            unsigned int enum_sett_inst_diff = _enumeration_vector_max_index
                - _enumeration_sett_observed_value_response_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= enum_sett_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::EnumerationObservedValue*> enum_sett_obs_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::EnumerationObservedValueTypeSupport::create_data());
              if (!enum_sett_obs_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for enumeration setting observed value instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _enumeration_sett_observed_value_response_instance_list.push_back(enum_sett_obs_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "enumeration setting observed value pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }

            unsigned int enum_calc_inst_diff = _enumeration_vector_max_index
                - _enumeration_calc_observed_value_response_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= enum_calc_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::EnumerationObservedValue*> enum_calc_obs_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::EnumerationObservedValueTypeSupport::create_data());
              if (!enum_calc_obs_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for enumeration calculation observed value instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _enumeration_calc_observed_value_response_instance_list.push_back(enum_calc_obs_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "enumeration calculation observed value pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }
          }
          ice::EnumerationContext* context_instance = nullptr;
          try
          {
            context_instance = _enumeration_meas_context_response_instance_list.at(
              _enumeration_vector_max_index).second;
            if (!context_instance)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Enumeration context "
                "instance is a null pointer at index: "
                << _enumeration_vector_max_index);
              return DicesRcPhilipsIntellivueMP70::FAIL;
            }
          }
          catch (std::exception& ex)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get enumeration "
              "context instance from instance list at index: "
              << _enumeration_vector_max_index << ". " << ex.what());
            return DicesRcPhilipsIntellivueMP70::FAIL;
          }
          ice::EnumerationObservedValue* obs_val_instance = nullptr;
          try
          {
            obs_val_instance = _enumeration_meas_observed_value_response_instance_list.at(
              _enumeration_vector_max_index).second;
            if (!obs_val_instance)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Enumeration observed value "
                "instance is a null pointer at index: "
                << _enumeration_vector_max_index);
              return DicesRcPhilipsIntellivueMP70::FAIL;
            }
          }
          catch (std::exception& ex)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get enumeration "
              "observed value instance from instance list at index: "
              << _enumeration_vector_max_index << ". " << ex.what());
            return DicesRcPhilipsIntellivueMP70::FAIL;
          }
          if (context_instance->handle == 0 && obs_val_instance->handle == 0)
          {
            // Generate new enum handle
            intellivue::Handle new_handle = 0;
            DicesRcPhilipsIntellivueMP70 status = GenerateNewHandle(
              &new_handle);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }
            // Set new handle for this instance.
            context_instance->handle = new_handle;
            obs_val_instance->handle = new_handle;

            std::map<intellivue::Handle, unsigned int> handle_to_index;
            std::pair < std::map<intellivue::Handle, unsigned int>::iterator, bool> ret_1 =
              handle_to_index.insert(std::pair<intellivue::Handle, unsigned int>(
              new_handle,
              _enumeration_vector_max_index++));
            if (!ret_1.second)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert generated "
                "handle and vector index into map.");
              return DicesRcPhilipsIntellivueMP70::FAIL;
            }

            std::pair <
              std::map<
              std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
              std::map < intellivue::Handle, unsigned int>>::iterator, bool> ret_2 =
              _map_handle_to_enumeration_instance.insert(
              std::pair<
              std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
              std::map < intellivue::Handle, unsigned int>>(
              unique_handle,
              handle_to_index));
            if (!ret_2.second)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert unique "
                "handle and handle and vector index map into map.");
              return DicesRcPhilipsIntellivueMP70::FAIL;
            }

          }
        }

        if (_map_handle_to_enumeration_instance[unique_handle].empty())
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Will not be able to "
            "dereference the iterator returned from enum instance map in "
            "the future. There must be at least one index for enum "
            "instance vector per object.");
          break;
        }

        intellivue::OIDType attribute_id = _extended_poll_response.pollReply.
          poll_info_list.value[ix].poll_info.value[iy].attributes.value[iz].
          attribute_id;
        switch (attribute_id)
        {
          case NOM_ATTR_ID_HANDLE:
          {
            intellivue::Handle* phandle =
              reinterpret_cast<intellivue::Handle*>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!phandle)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into intellivue::Handle. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            // Handles already set.
            // Set parent handles to the vmd
            if (_vmd_instance_list.size() > 0)
            {
              _enumeration_meas_context_response_instance_list.at(
                _map_handle_to_enumeration_instance[unique_handle].begin()->second).
                second->parent_handle = _vmd_instance_list.at(0).second->handle;

              _enumeration_meas_observed_value_response_instance_list.at(
                _map_handle_to_enumeration_instance[unique_handle].begin()->second).
                second->parent_handle = _vmd_instance_list.at(0).second->handle;
            }
          }
            break;
          case NOM_ATTR_ID_TYPE:
          {
            intellivue::TYPE* ptype =
              reinterpret_cast<intellivue::TYPE*>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!ptype)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into intellivue::TYPE. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            ice::NomPartition dices_nom_partition = ice::nom_part_unspec;
            DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
              ConvertIntellivueNomPartitionToDicesNomPartition(
              &dices_nom_partition,
              ptype->partition);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }

            if (_enumeration_meas_context_response_instance_list.
              at(_map_handle_to_enumeration_instance[unique_handle].begin()->
              second).second->type.partition != dices_nom_partition)
            {
              _enumeration_meas_context_response_instance_list.
                at(_map_handle_to_enumeration_instance[unique_handle].begin()->
                second).second->type.partition = dices_nom_partition;
            }

            if (_enumeration_meas_context_response_instance_list.
              at(_map_handle_to_enumeration_instance[unique_handle].begin()->
              second).second->type.code != ptype->code)
            {
              _enumeration_meas_context_response_instance_list.
                at(_map_handle_to_enumeration_instance[unique_handle].begin()->
                second).second->type.code = ptype->code;
            }

            _enumeration_meas_observed_value_response_instance_list.
              at(_map_handle_to_enumeration_instance[unique_handle].begin()->
              second).second->type.partition = dices_nom_partition;

            _enumeration_meas_observed_value_response_instance_list.
              at(_map_handle_to_enumeration_instance[unique_handle].begin()->
              second).second->type.code = ptype->code;
          }
            break;
          case NOM_ATTR_METRIC_SPECN:
          {
            intellivue::MetricSpec* pmspec =
              reinterpret_cast<intellivue::MetricSpec *>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!pmspec)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into intellivue::MetricSpec. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            ice::MetricAccess dices_access = 0;
            DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
              ConvertIntellivueMetricAccessToDicesMetricAccess(
              &dices_access,
              pmspec->access);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }

            if (_enumeration_meas_context_response_instance_list.at(
              _map_handle_to_enumeration_instance[unique_handle].begin()->second).
              second->metric_specification.access != dices_access)
            {
              _enumeration_meas_context_response_instance_list.at(
                _map_handle_to_enumeration_instance[unique_handle].begin()->
                second).second->metric_specification.access = dices_access;
              if (_enumeration_meas_context_response_instance_list.at(
                _map_handle_to_enumeration_instance[unique_handle].begin()->
                second).second->metric_id != 0)
              {
                _enumeration_meas_context_response_instance_list.at(
                  _map_handle_to_enumeration_instance[unique_handle].begin()->
                  second).first = DicesRcDriver::OK;
              }
            }
            ice::MetricCategory dices_category =
              ice::MetricCategory::auto_measurement;
            status = IntellivueUtils::
              ConvertIntellivueMetricCategoryToDicesMetricCategory(
              &dices_category,
              pmspec->category);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }
            if (_enumeration_meas_context_response_instance_list.at(
              _map_handle_to_enumeration_instance[unique_handle].begin()->second).
              second->metric_specification.category != dices_category)
            {
              _enumeration_meas_context_response_instance_list.at(
                _map_handle_to_enumeration_instance[unique_handle].begin()->
                second).second->metric_specification.category = dices_category;
              if (_enumeration_meas_context_response_instance_list.at(
                _map_handle_to_enumeration_instance[unique_handle].begin()->
                second).second->metric_id != 0)
              {
                _enumeration_meas_context_response_instance_list.at(
                  _map_handle_to_enumeration_instance[unique_handle].begin()->
                  second).first = DicesRcDriver::OK;
              }
            }
            // MetricRelevance cannot be set properly. Intellivue
            // documentation states that MetricRelevance is for internal use
            // only. There is no way to convert intellivue bits to DICES
            // bits.
            ice::Duration dices_rel_time = { 0 };
            status = IntellivueUtils::
              ConvertIntellivueRelativeTimeToDicesDuration(
              &dices_rel_time,
              pmspec->update_period);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }
            if (_enumeration_meas_context_response_instance_list.at(
              _map_handle_to_enumeration_instance[unique_handle].begin()->second).
              second->metric_specification.update_period.seconds
              != dices_rel_time.seconds)
            {
              _enumeration_meas_context_response_instance_list.at(
                _map_handle_to_enumeration_instance[unique_handle].begin()->
                second).
                second->metric_specification.update_period.seconds =
                dices_rel_time.seconds;
              if (_enumeration_meas_context_response_instance_list.at(
                _map_handle_to_enumeration_instance[unique_handle].begin()->
                second).
                second->metric_id != 0)
              {
                _enumeration_meas_context_response_instance_list.at(
                  _map_handle_to_enumeration_instance[unique_handle].begin()->
                  second).
                  first = DicesRcDriver::OK;
              }
            }
            if (_enumeration_meas_context_response_instance_list.at(
              _map_handle_to_enumeration_instance[unique_handle].begin()->second).
              second->metric_specification.update_period.nanoseconds
              != dices_rel_time.nanoseconds)
            {
              _enumeration_meas_context_response_instance_list.at(
                _map_handle_to_enumeration_instance[unique_handle].begin()->
                second).second->metric_specification.update_period.
                nanoseconds = dices_rel_time.nanoseconds;
              if (_enumeration_meas_context_response_instance_list.at(
                _map_handle_to_enumeration_instance[unique_handle].begin()->
                second).second->metric_id != 0)
              {
                _enumeration_meas_context_response_instance_list.at(
                  _map_handle_to_enumeration_instance[unique_handle].begin()->
                  second).first = DicesRcDriver::OK;
              }
            }

            if (pmspec->structure.ms_comp_no != 0)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Found MetricStructure with "
                "compound ms_comp_no (" << static_cast<int>(
                pmspec->structure.ms_comp_no) << "). This shouldn't be "
                "possible for enumeration object, because there is no "
                "enumeration compound observed value attribute. "
                "attribute_id " << static_cast<int>(attribute_id));
              break;
            }
          }
            break;
          case NOM_ATTR_ID_LABEL:
            break;
          case NOM_ATTR_ID_LABEL_STRING:
          {
            intellivue::String* plabel =
              reinterpret_cast<intellivue::String *>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!plabel)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into intellivue::SimpleColour. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            std::string label_string;
            for (int iindex = 0; iindex < plabel->length; iindex++)
            {
              uint8_t ch8 = '\0';
              uint16_t ch16 = plabel->value[iindex];
              // Convert to byte array
              uint8_t byte_0 = ch16 & 0x00ff;
              uint8_t byte_1 = ch16 >> 8;
              uint8_t buf[2] = { byte_0, byte_1 };

              ch16 = ntohs(*(reinterpret_cast<uint16_t*>(&buf[0])));

              DicesRcPhilipsIntellivueMP70 status =
                IntellivueUtils::Convert16BitUnicodeToAscii(
                ch16,
                &ch8);
              if (status != DicesRcPhilipsIntellivueMP70::OK)
              {
                LOG4CPLUS_ERROR(root_logger, sfn <<
                  DicesRcPhilipsIntellivueMP70StatusMessage::
                  DicesRcPhilipsIntellivueMP70ToString(status));
                return status;
              }
              label_string += static_cast<char>(ch8);
            }

            if (strncmp(_enumeration_meas_context_response_instance_list.
              at(_map_handle_to_enumeration_instance[unique_handle].begin()->
              second).second->metric_info_label_string,
              label_string.c_str(),
              ice::LONG_STRING_LEN) != 0)
            {
              strncpy(_enumeration_meas_context_response_instance_list.
                at(_map_handle_to_enumeration_instance[unique_handle].begin()->
                second).second->metric_info_label_string,
                label_string.c_str(),
                ice::LONG_STRING_LEN);
              _enumeration_meas_context_response_instance_list.
                at(_map_handle_to_enumeration_instance[unique_handle].begin()->
                second).second->metric_info_label_string[
                ice::LONG_STRING_LEN] = '\0';

              if (_enumeration_meas_context_response_instance_list.
                at(_map_handle_to_enumeration_instance[unique_handle].begin()->
                second).second->metric_id != 0)
              {
                _enumeration_meas_context_response_instance_list.
                  at(_map_handle_to_enumeration_instance[unique_handle].begin()->
                  second).first = DicesRcDriver::OK;
              }
            }
          }
            break;
          case NOM_ATTR_COLOR:
          {
            intellivue::SimpleColour* pcolor =
              reinterpret_cast<intellivue::SimpleColour *>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!pcolor)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into intellivue::SimpleColour. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            ice::SimpleColor dices_color = ice::col_black;

            DicesRcPhilipsIntellivueMP70 status =
              IntellivueUtils::ConvertIntellivueColorToDicesColor(
              &dices_color,
              *pcolor);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }

            if (!_enumeration_meas_context_response_instance_list.at(
              _map_handle_to_enumeration_instance[unique_handle].begin()->second).
              second->color)
            {
              _enumeration_meas_context_response_instance_list.at(
                _map_handle_to_enumeration_instance[unique_handle].begin()->
                second).second->color = reinterpret_cast<ice::SimpleColor*>(
                DDS::Heap_malloc(sizeof(ice::SimpleColor)));
              if (!_enumeration_meas_context_response_instance_list.at(
                _map_handle_to_enumeration_instance[unique_handle].begin()->
                second).second->color)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to "
                  "allocate memory for ice::SimpleColor");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
            }

            if (*_enumeration_meas_context_response_instance_list.at(
              _map_handle_to_enumeration_instance[unique_handle].begin()->second).
              second->color != dices_color)
            {
              *_enumeration_meas_context_response_instance_list.at(
                _map_handle_to_enumeration_instance[unique_handle].begin()->
                second).second->color = dices_color;
              if (_enumeration_meas_context_response_instance_list.at(
                _map_handle_to_enumeration_instance[unique_handle].begin()->
                second).second->metric_id != 0)
              {
                _enumeration_meas_context_response_instance_list.at(
                  _map_handle_to_enumeration_instance[unique_handle].begin()->
                  second).first = DicesRcDriver::OK;
              }
            }
          }
            break;
          case NOM_ATTR_VAL_ENUM_OBS:
          {
            intellivue::EnumObsVal* penum_obs_val =
              reinterpret_cast<intellivue::EnumObsVal *>(
              _extended_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!penum_obs_val)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into intellivue::EnumObsVal. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            if (_enumeration_meas_context_response_instance_list.at(
              _map_handle_to_enumeration_instance[unique_handle].begin()->second).
              second->metric_id != penum_obs_val->physio_id)
            {
              _enumeration_meas_context_response_instance_list.at(
                _map_handle_to_enumeration_instance[unique_handle].begin()->
                second).second->metric_id = penum_obs_val->physio_id;
              _enumeration_meas_context_response_instance_list.at(
                _map_handle_to_enumeration_instance[unique_handle].begin()->
                second).first = DicesRcDriver::OK;
            }
            _enumeration_meas_observed_value_response_instance_list.at(
              _map_handle_to_enumeration_instance[unique_handle].begin()->second).
              second->enum_observed_value.metric_id = penum_obs_val->physio_id;

            ice::MeasurementStatus dices_meas_status = 0;
            DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
              ConvertIntellivueMeasurementStatusToDicesMeasurementStatus(
              &dices_meas_status,
              penum_obs_val->state);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }

            if (_enumeration_meas_context_response_instance_list.at(
              _map_handle_to_enumeration_instance[unique_handle].begin()->second).
              second->measurement_status != dices_meas_status)
            {
              _enumeration_meas_context_response_instance_list.at(
                _map_handle_to_enumeration_instance[unique_handle].begin()->
                second).
                second->measurement_status = dices_meas_status;
              if (_enumeration_meas_context_response_instance_list.at(
                _map_handle_to_enumeration_instance[unique_handle].begin()->
                second).second->metric_id != 0)
              {
                _enumeration_meas_context_response_instance_list.at(
                  _map_handle_to_enumeration_instance[unique_handle].begin()->
                  second).first = DicesRcDriver::OK;
              }
            }
            _enumeration_meas_observed_value_response_instance_list.at(
              _map_handle_to_enumeration_instance[unique_handle].begin()->second).
              second->enum_observed_value.state = dices_meas_status;

            switch (penum_obs_val->value.choice)
            {
              case ENUM_OBJ_ID_CHOSEN:
                _enumeration_meas_observed_value_response_instance_list.at(
                  _map_handle_to_enumeration_instance[unique_handle].begin()->
                  second).second->enum_observed_value.value._d =
                  ice::EnumValType::e_obj_id;
                _enumeration_meas_observed_value_response_instance_list.at(
                  _map_handle_to_enumeration_instance[unique_handle].begin()->
                  second).second->enum_observed_value.value._u.obj_id =
                  penum_obs_val->value.u.enum_obj_id;
                break;
              case ENUM_OBJ_ID_VAL_CHOSEN:
              {
                _enumeration_meas_observed_value_response_instance_list.at(
                  _map_handle_to_enumeration_instance[unique_handle].begin()->
                  second).second->enum_observed_value.value._d =
                  ice::EnumValType::e_record_oo;
                _enumeration_meas_observed_value_response_instance_list.at(
                  _map_handle_to_enumeration_instance[unique_handle].begin()->
                  second).second->enum_observed_value.value._u.record_oo.
                  record_type_code = penum_obs_val->value.u.enum_obj_id_val.
                  obj_id;

                int record_data_index = 0;
                uint32_t new_int = htonl(penum_obs_val->value.u.
                  enum_obj_id_val.num_val);
                uint8_t* pnew_int = reinterpret_cast<uint8_t*>(&new_int);
                memmove(&_enumeration_meas_observed_value_response_instance_list.at(
                  _map_handle_to_enumeration_instance[unique_handle].begin()->
                  second).second->enum_observed_value.value._u.record_oo.
                  record_data[record_data_index],
                  pnew_int,
                  sizeof(new_int));
                record_data_index += sizeof(new_int);

                uint16_t new_short = htons(penum_obs_val->value.u.
                  enum_obj_id_val.unit_code);
                uint8_t* pnew_short = reinterpret_cast<uint8_t*>(&new_short);
                memmove(&_enumeration_meas_observed_value_response_instance_list.at(
                  _map_handle_to_enumeration_instance[unique_handle].begin()->
                  second).second->enum_observed_value.value._u.record_oo.
                  record_data[record_data_index],
                  pnew_short,
                  sizeof(new_short));
                record_data_index += sizeof(new_short);
              }
                break;
              default:
                LOG4CPLUS_WARN(root_logger, sfn << "Unknown Intellivue "
                  "EnumVal choice (" << static_cast<int>(
                  penum_obs_val->value.choice) << ")");
                break;
            }

            _enumeration_meas_observed_value_response_instance_list.at(
              _map_handle_to_enumeration_instance[unique_handle].begin()->second).
              first = DicesRcDriver::OK;
          }
            break;
          default:
            break;
        }
      }
    }
  }

  for (
    int ix = 0;
    ix < _enumeration_meas_context_response_instance_list.size();
    ix++)
  {
    // For all context dds instances that have changed, increment context
    // sequence number and set for the same number in observed value.
    if (_enumeration_meas_context_response_instance_list.at(ix).first
      == DicesRcDriver::OK)
    {
      _enumeration_meas_context_response_instance_list.at(ix).second->
        context_seq_number++;
      _enumeration_meas_observed_value_response_instance_list.at(ix).second->
        context_seq_number =
        _enumeration_meas_context_response_instance_list.at(ix).second->
        context_seq_number;
    }
  }
  for (int ix = 0; ix < _enumeration_meas_context_response_instance_list.size(); ix++)
  {
    switch (_enumeration_meas_context_response_instance_list.at(ix).second->
      metric_specification.category)
    {
      case ice::MetricCategory::auto_calculation:
      case ice::MetricCategory::manual_calculation:
      {
        DDS::ReturnCode_t retcode = ice::EnumerationContextTypeSupport::copy_data(
          _enumeration_calc_context_response_instance_list.at(ix).second,
          _enumeration_meas_context_response_instance_list.at(ix).second);
        if (retcode != DDS::RETCODE_OK)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to copy data from "
            "enum measurement context to enum calculation context");
          break;
        }
        retcode = ice::EnumerationObservedValueTypeSupport::copy_data(
          _enumeration_calc_observed_value_response_instance_list.at(ix).second,
          _enumeration_meas_observed_value_response_instance_list.at(ix).second);
        if (retcode != DDS::RETCODE_OK)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to copy data from "
            "enum measurement observed value to enum calculation "
            "observed value");
          break;
        }
        _enumeration_calc_context_response_instance_list.at(ix).first =
          _enumeration_meas_context_response_instance_list.at(ix).first;
        _enumeration_calc_observed_value_response_instance_list.at(ix).first =
          _enumeration_meas_observed_value_response_instance_list.at(ix).first;
        if (_enumeration_meas_context_response_instance_list.at(ix).first
          == DicesRcDriver::OK)
        {
          // Do not publish measurement.
          _enumeration_meas_context_response_instance_list.at(ix).first =
            DicesRcDriver::NO_NEW_DATA;
        }
        if (_enumeration_meas_observed_value_response_instance_list.at(ix).first
          == DicesRcDriver::OK)
        {
          // Do not publish measurement.
          _enumeration_meas_observed_value_response_instance_list.at(ix).first =
            DicesRcDriver::NO_NEW_DATA;
        }
      }
        break;
      case ice::MetricCategory::auto_setting:
      case ice::MetricCategory::manual_setting:
      {
        DDS::ReturnCode_t retcode = ice::EnumerationContextTypeSupport::copy_data(
          _enumeration_sett_context_response_instance_list.at(ix).second,
          _enumeration_meas_context_response_instance_list.at(ix).second);
        if (retcode != DDS::RETCODE_OK)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to copy data from "
            "enum measurement context to enum setting context");
          break;
        }
        retcode = ice::EnumerationObservedValueTypeSupport::copy_data(
          _enumeration_sett_observed_value_response_instance_list.at(ix).second,
          _enumeration_meas_observed_value_response_instance_list.at(ix).second);
        if (retcode != DDS::RETCODE_OK)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to copy data from "
            "enum measurement observed value to enum setting "
            "observed value");
          break;
        }
        _enumeration_sett_context_response_instance_list.at(ix).first =
          _enumeration_meas_context_response_instance_list.at(ix).first;
        _enumeration_sett_observed_value_response_instance_list.at(ix).first =
          _enumeration_meas_observed_value_response_instance_list.at(ix).first;
        if (_enumeration_meas_context_response_instance_list.at(ix).first
          == DicesRcDriver::OK)
        {
          // Do not publish measurement.
          _enumeration_meas_context_response_instance_list.at(ix).first =
            DicesRcDriver::NO_NEW_DATA;
        }
        if (_enumeration_meas_observed_value_response_instance_list.at(ix).first
          == DicesRcDriver::OK)
        {
          // Do not publish measurement.
          _enumeration_meas_observed_value_response_instance_list.at(ix).first =
            DicesRcDriver::NO_NEW_DATA;
        }
      }
        break;
      case ice::MetricCategory::mcat_unspec:
        LOG4CPLUS_WARN(root_logger, sfn << "MetricCategory is unspecified for "
          "EnumerationContext at index (" << ix << ")");
        break;
      default:
        // Must be a measurement
        break;
    }
  }
  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 DDPhilipsIntellivueMP70Parser::GenerateNewHandle(
  intellivue::Handle* new_handle)
{
  static const char* sfn = "DDPhilipsIntellivueMP70Parser::"
    "GenerateNewHandle() ";

  if (!new_handle)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "new_handle is a null pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  static intellivue::Handle handle = 0;

  if (handle == USHRT_MAX)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Unable to generate a new unique "
      "handle. The maximum value for an unsigned 16 bit integer ("
      << USHRT_MAX << ") has been reached.");
    handle = 0;
    return DicesRcPhilipsIntellivueMP70::FAIL;
  }

  handle++;
  *new_handle = handle;

  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 DDPhilipsIntellivueMP70Parser::SetSingleMDSResponseData()
{
  static const char* sfn = "DDPhilipsIntellivueMP70Parser::"
    "SetSingleMDSResponseData() ";

  intellivue::GlbHandle glb_handle = {
    _single_poll_response.actionresult.managed_object.m_obj_inst.context_id,
    _single_poll_response.actionresult.managed_object.m_obj_inst.handle
  };

  for (
    int ix = 0;
    ix < _single_poll_response.pollReply.poll_info_list.count;
    ix++)
  {
    if (!_single_poll_response.pollReply.poll_info_list.value)
    {
      LOG4CPLUS_WARN(root_logger, sfn << "SingleContextPoll array in "
        "PollInfoList is a null pointer");
      break;
    }
    intellivue::MdsContext single_context_poll_context_id =
      _single_poll_response.pollReply.poll_info_list.value[ix].context_id;

    for (
      int iy = 0;
      iy < _single_poll_response.pollReply.poll_info_list.value[ix].
      poll_info.count;
      iy++)
    {
      if (!_single_poll_response.pollReply.poll_info_list.value[ix].poll_info.value)
      {
        LOG4CPLUS_WARN(root_logger, sfn << "ObservationPoll array in "
          "poll_info is a null pointer");
        break;
      }

      for (
        int iz = 0;
        iz < _single_poll_response.pollReply.poll_info_list.value[ix].
        poll_info.value[iy].attributes.count;
        iz++)
      {
        // Get handle
        intellivue::Handle obj_handle =
          _single_poll_response.pollReply.poll_info_list.value[ix].
          poll_info.value[iy].obj_handle;

        std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>
          unique_handle(glb_handle.context_id, glb_handle.handle, single_context_poll_context_id, obj_handle);

        std::map<
          std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
          unsigned int>::iterator it;
        it = _map_handle_to_mds_instance.find(unique_handle);
        if (it == _map_handle_to_mds_instance.end())
        {
          if (_mds_vector_max_index >= _mds_instance_list.size())
          {
            LOG4CPLUS_INFO(root_logger, sfn << "The maximum number of MDS "
              "instances (" << _mds_instance_list.size() << ") are already "
              "in use. Inserting additional instances.");

            unsigned int mds_inst_diff = _mds_vector_max_index - _mds_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= mds_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::MDS*> mds_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::MDSTypeSupport::create_data());
              if (!mds_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for MDS instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _mds_instance_list.push_back(mds_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "mds pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }
          }

          std::pair < std::map<
            std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
            unsigned int>::iterator, bool> ret = _map_handle_to_mds_instance.insert(
            std::pair<
            std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
            unsigned int>(unique_handle,
            _mds_vector_max_index++));
          if (!ret.second)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert handle "
              "and vector index into mds map.");
            return DicesRcPhilipsIntellivueMP70::FAIL;
          }

          unsigned int mds_index = 0;
          try
          {
            mds_index = _map_handle_to_mds_instance.at(unique_handle);
          }
          catch (std::exception& ex)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get mds vector "
              "index from map. " << ex.what());
            return DicesRcPhilipsIntellivueMP70::FAIL;
          }

          ice::MDS* mds_instance = nullptr;
          try
          {
            mds_instance = _mds_instance_list.at(mds_index).second;
            if (!mds_instance)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "MDS instance pointer in "
                "vector at index (" << mds_index << ") is a null pointer.");
              return DicesRcPhilipsIntellivueMP70::FAIL;
            }
          }
          catch (std::exception& ex)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get mds instance "
              "at index (" << mds_index << ") from vector. " << ex.what());
            return DicesRcPhilipsIntellivueMP70::FAIL;
          }

          // The reason we're checking for zero here is because a handle might
          // have already been generated by the mds create event.
          if (mds_instance->handle == 0)
          {
            // Generate new MDS handle
            intellivue::Handle new_handle = 0;
            DicesRcPhilipsIntellivueMP70 status = GenerateNewHandle(
              &new_handle);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }
            // Set new handle for this instance.
            mds_instance->handle = new_handle;
          }
        }
        std::map<
          std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
          unsigned int>::iterator vmd_it;
        vmd_it = _map_handle_to_vmd_instance.find(unique_handle);
        if (vmd_it == _map_handle_to_vmd_instance.end())
        {
          if (_vmd_vector_max_index >= _vmd_instance_list.size())
          {
            LOG4CPLUS_INFO(root_logger, sfn << "The maximum number of VMD "
              "instances (" << _vmd_instance_list.size() << ") are already "
              "in use. Inserting additional instances.");

            unsigned int vmd_inst_diff = _vmd_vector_max_index - _vmd_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= vmd_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::VMD*> vmd_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::VMDTypeSupport::create_data());
              if (!vmd_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for VMD instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _vmd_instance_list.push_back(vmd_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "vmd pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }
          }

          std::pair < std::map<
            std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
            unsigned int>::iterator, bool> ret = _map_handle_to_vmd_instance.insert(
            std::pair<std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
            unsigned int>(unique_handle,
            _vmd_vector_max_index++));
          if (!ret.second)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert handle "
              "and vector index into vmd map.");
            return DicesRcPhilipsIntellivueMP70::FAIL;
          }

          unsigned int vmd_index = 0;
          try
          {
            vmd_index = _map_handle_to_vmd_instance.at(unique_handle);
          }
          catch (std::exception& ex)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get vmd vector "
              "index from map. " << ex.what());
            return DicesRcPhilipsIntellivueMP70::FAIL;
          }

          ice::VMD* vmd_instance = nullptr;
          try
          {
            vmd_instance = _vmd_instance_list.at(vmd_index).second;
            if (!vmd_instance)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "VMD instance pointer in "
                "vector at index (" << vmd_index << ") is a null pointer.");
              return DicesRcPhilipsIntellivueMP70::FAIL;
            }
          }
          catch (std::exception& ex)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get vmd instance "
              "at index (" << vmd_index << ") from vector. " << ex.what());
            return DicesRcPhilipsIntellivueMP70::FAIL;
          }

          // The reason we're checking for zero here is because a handle might
          // have already been generated by the mds create event.
          if (vmd_instance->handle == 0)
          {
            // Generate new VMD handle
            intellivue::Handle new_handle = 0;
            DicesRcPhilipsIntellivueMP70 status = GenerateNewHandle(
              &new_handle);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }
            // Set new handle for this instance.
            vmd_instance->handle = new_handle;
          }
        }

        intellivue::OIDType attribute_id = _single_poll_response.pollReply.
          poll_info_list.value[ix].poll_info.value[iy].attributes.value[iz].
          attribute_id;
        switch (attribute_id)
        {
          case NOM_ATTR_ID_HANDLE:
          {
            intellivue::Handle* phandle =
              reinterpret_cast<intellivue::Handle *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!phandle)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into Handle. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }
            std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>
              handle_attr(glb_handle.context_id, glb_handle.handle, single_context_poll_context_id, *phandle);

            std::map<
              std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
              unsigned int>::iterator mds_it;
            mds_it = _map_handle_to_mds_instance.find(handle_attr);
            if (mds_it == _map_handle_to_mds_instance.end())
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Intellivue attribute "
                "handle (" << static_cast<int>(*phandle) << ") is different "
                "than object handle (" << static_cast<int>(std::get<3>(handle_attr))
                << "). Couldn't find handle in handle to mds map.");
            }

            std::map<
              std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
              unsigned int>::iterator vmd_it;
            vmd_it = _map_handle_to_vmd_instance.find(handle_attr);
            if (vmd_it == _map_handle_to_vmd_instance.end())
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Intellivue attribute "
                "handle (" << static_cast<int>(*phandle) << ") is different "
                "than object handle (" << static_cast<int>(std::get<3>(handle_attr))
                << "). Couldn't find handle in handle to vmd map.");
            }
            // NOTE: Handles for MDS and VMD have already been set with handles
            // generated by this driver.
          }
            break;
          case NOM_ATTR_SYS_TYPE:
          {
            intellivue::TYPE* ptype =
              reinterpret_cast<intellivue::TYPE*>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!ptype)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into TYPE. attribute_id: " << static_cast<int>(
                attribute_id));
              break;
            }

            ice::NomPartition dices_partition =
              ice::NomPartition::nom_part_unspec;
            DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
              ConvertIntellivueNomPartitionToDicesNomPartition(
              &dices_partition,
              ptype->partition);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }

            if (_mds_instance_list.at(_map_handle_to_mds_instance[
              unique_handle]).second->system_type.partition != dices_partition)
            {
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                second->system_type.partition = dices_partition;
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                first = DicesRcDriver::OK;
            }

            if (_mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
              second->system_type.code != ptype->code)
            {
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                second->system_type.code = ptype->code;
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                first = DicesRcDriver::OK;
            }
          }
            break;
          case NOM_ATTR_ID_MODEL:
          {
            intellivue::SystemModel* psystem_model =
              reinterpret_cast<intellivue::SystemModel *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!psystem_model)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into SystemModel. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            std::string manufacturer_string;
            for (
              int iindex = 0;
              iindex < psystem_model->manufacturer.length;
              iindex++)
            {
              if (!psystem_model->manufacturer.value)
              {
                LOG4CPLUS_WARN(root_logger, sfn << "Value is a null pointer in "
                  "manufacturer VariableLabel. attribute_id: "
                  << static_cast<int>(attribute_id));
                break;
              }
              manufacturer_string += static_cast<char>(
                psystem_model->manufacturer.value[iindex]);
            }

            if (strncmp(
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
              second->system_model.manufacturer,
              manufacturer_string.c_str(),
              ice::MEDIUM_STRING_LEN) != 0)
            {
              strncpy(
                _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                second->system_model.manufacturer,
                manufacturer_string.c_str(),
                ice::MEDIUM_STRING_LEN);
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                second->system_model.manufacturer[ice::MEDIUM_STRING_LEN] =
                '\0';
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                first = DicesRcDriver::OK;
            }

            std::string model_number_string;
            for (
              int iindex = 0;
              iindex < psystem_model->model_number.length;
              iindex++)
            {
              if (!psystem_model->model_number.value)
              {
                LOG4CPLUS_WARN(root_logger, sfn << "Value is a null pointer in "
                  "model_number VariableLabel. attribute_id: "
                  << static_cast<int>(attribute_id));
                break;
              }
              model_number_string += static_cast<char>(
                psystem_model->model_number.value[iindex]);
            }
            if (strncmp(
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
              second->system_model.model_number,
              model_number_string.c_str(),
              ice::MEDIUM_STRING_LEN) != 0)
            {
              strncpy(
                _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                second->system_model.model_number,
                model_number_string.c_str(),
                ice::MEDIUM_STRING_LEN);
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                second->system_model.model_number[ice::MEDIUM_STRING_LEN] =
                '\0';
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                first = DicesRcDriver::OK;
            }
          }
            break;
          case NOM_ATTR_SYS_ID:
            // TODO Should this be ignored? Seems like an ICE ID.
            break;
          case NOM_ATTR_NOM_VERS:
          {
            uint32_t* pnom_vers =
              reinterpret_cast<uint32_t *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!pnom_vers)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into uint32_t. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            // Convert nomenclature version to bytes and add it to byte array.
            uint16_t nom_vers_bytes[4] = { 0 };
            uint32_t new_int = htonl(*pnom_vers);
            uint8_t* pnew_int = reinterpret_cast<uint8_t*>(&new_int);
            memmove(&nom_vers_bytes[0], pnew_int, sizeof(new_int));
            // Parse major and minor
            uint16_t major = ntohs(*(reinterpret_cast<uint16_t*>(
              &nom_vers_bytes[0])));
            uint16_t minor = ntohs(*(reinterpret_cast<uint16_t*>(
              &nom_vers_bytes[2])));

            if (_mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
              second->nomenclature_version.nom_major_version != major)
            {
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                second->nomenclature_version.nom_major_version = major;
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                first = DicesRcDriver::OK;
            }
            if (_mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
              second->nomenclature_version.nom_minor_version != minor)
            {
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                second->nomenclature_version.nom_minor_version = minor;
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                first = DicesRcDriver::OK;
            }
          }
            break;
          case NOM_ATTR_LOCALIZN:
            break;
          case NOM_ATTR_SYS_SPECN:
          {
            intellivue::SystemSpec* psystem_spec =
              reinterpret_cast<intellivue::SystemSpec *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!psystem_spec)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into SystemSpec. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            if (!_mds_instance_list.at(_map_handle_to_mds_instance[
              unique_handle]).second->system_specification.ensure_length(
              psystem_spec->count, psystem_spec->count))
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length "
                "for ice::SystemSpec sequence with length "
                << static_cast<int>(psystem_spec->count) << ". attribute_id: "
                << static_cast<int>(attribute_id));
              return DicesRcPhilipsIntellivueMP70::DDS_SEQUENCE_ENSURE_LENGTH_FAILURE;
            }

            for (int index = 0; index < psystem_spec->count; index++)
            {
              if (!psystem_spec->value)
              {
                LOG4CPLUS_WARN(root_logger, sfn << "SystemSpec "
                  "SystemSpecEntry list pointer is null");
                break;
              }

              int required_bytes = psystem_spec->value[index].length * 2;
              if (required_bytes > ice::LONG_STRING_LEN)
              {
                LOG4CPLUS_WARN(root_logger, sfn << "SystemSpecEntry "
                  "component_spec string is not long enough to contain "
                  << required_bytes << " bytes.");
                break;
              }

              if (_mds_instance_list.at(_map_handle_to_mds_instance[
                unique_handle]).second->system_specification[index].
                component_capab_id != psystem_spec->value[index].
                component_capab_id)
              {
                _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                  second->system_specification[index].component_capab_id =
                  psystem_spec->value[index].component_capab_id;
                _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                  first = DicesRcDriver::OK;
              }

              int component_spec_index = 0;
              uint16_t new_short = htons(psystem_spec->value[index].length);
              uint8_t* pnew_short = reinterpret_cast<uint8_t*>(&new_short);
              if (memcmp(&_mds_instance_list.at(_map_handle_to_mds_instance[
                unique_handle]).second->system_specification[index].
                component_spec[component_spec_index],
                pnew_short,
                sizeof(new_short)))
              {
                memmove(&_mds_instance_list.at(_map_handle_to_mds_instance[
                  unique_handle]).second->system_specification[index].
                  component_spec[component_spec_index],
                  pnew_short,
                  sizeof(new_short));
                _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                  first = DicesRcDriver::OK;
              }
              component_spec_index += sizeof(new_short);

              intellivue::MdibObjectSupport* pmdib =
                reinterpret_cast<intellivue::MdibObjectSupport *>(
                psystem_spec->value[ix].value);
              if (!pmdib)
              {
                LOG4CPLUS_WARN(root_logger, sfn << "SystemSpecEntry "
                  "MdibObjectSupport list pointer is null");
                break;
              }

              new_short = htons(pmdib->count);
              pnew_short = reinterpret_cast<uint8_t*>(&new_short);
              if (memcmp(&_mds_instance_list.at(_map_handle_to_mds_instance[
                unique_handle]).second->system_specification[index].
                component_spec[component_spec_index],
                pnew_short,
                sizeof(new_short)))
              {
                memmove(&_mds_instance_list.at(_map_handle_to_mds_instance[
                  unique_handle]).second->system_specification[index].
                  component_spec[component_spec_index],
                  pnew_short,
                  sizeof(new_short));
                _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                  first = DicesRcDriver::OK;
              }
              component_spec_index += sizeof(new_short);

              new_short = htons(pmdib->length);
              pnew_short = reinterpret_cast<uint8_t*>(&new_short);
              if (memcmp(&_mds_instance_list.at(_map_handle_to_mds_instance[
                unique_handle]).second->system_specification[index].
                component_spec[component_spec_index],
                pnew_short,
                sizeof(new_short)))
              {
                memmove(&_mds_instance_list.at(_map_handle_to_mds_instance[
                  unique_handle]).second->system_specification[index].
                  component_spec[component_spec_index],
                  pnew_short,
                  sizeof(new_short));
                _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                  first = DicesRcDriver::OK;
              }
              component_spec_index += sizeof(new_short);
              for (int mdib_index = 0; mdib_index < pmdib->count; mdib_index++)
              {
                intellivue::MdibObjectSupportEntry* pmdib_entry =
                  reinterpret_cast<intellivue::MdibObjectSupportEntry *>(
                  pmdib->value);
                if (!pmdib_entry)
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "MdibObjectSupport "
                    "MdibObjectSupportEntry list pointer is null");
                  break;
                }

                new_short = htons(pmdib_entry[mdib_index].object_type.partition);
                pnew_short = reinterpret_cast<uint8_t*>(&new_short);
                if (memcmp(&_mds_instance_list.at(_map_handle_to_mds_instance[
                  unique_handle]).second->system_specification[index].
                  component_spec[component_spec_index],
                  pnew_short,
                  sizeof(new_short)))
                {
                  memmove(&_mds_instance_list.at(_map_handle_to_mds_instance[
                    unique_handle]).second->system_specification[index].
                    component_spec[component_spec_index],
                    pnew_short,
                    sizeof(new_short));
                  _mds_instance_list.at(_map_handle_to_mds_instance[
                    unique_handle]).first = DicesRcDriver::OK;
                }
                component_spec_index += sizeof(new_short);

                new_short = htons(pmdib_entry[mdib_index].object_type.code);
                pnew_short = reinterpret_cast<uint8_t*>(&new_short);
                if (memcmp(&_mds_instance_list.at(_map_handle_to_mds_instance[
                  unique_handle]).second->system_specification[index].
                  component_spec[component_spec_index],
                  pnew_short,
                  sizeof(new_short)))
                {
                  memmove(&_mds_instance_list.at(_map_handle_to_mds_instance[
                    unique_handle]).second->system_specification[index].
                    component_spec[component_spec_index],
                    pnew_short,
                    sizeof(new_short));
                  _mds_instance_list.at(_map_handle_to_mds_instance[
                    unique_handle]).first = DicesRcDriver::OK;
                }
                component_spec_index += sizeof(new_short);

                uint32_t new_int = htonl(pmdib_entry[mdib_index].max_inst);
                uint8_t* pnew_int = reinterpret_cast<uint8_t*>(&new_int);
                if (memcmp(&_mds_instance_list.at(_map_handle_to_mds_instance[
                  unique_handle]).second->system_specification[index].
                  component_spec[component_spec_index],
                  pnew_int,
                  sizeof(new_int)))
                {
                  memmove(&_mds_instance_list.at(_map_handle_to_mds_instance[
                    unique_handle]).second->system_specification[index].
                    component_spec[component_spec_index],
                    pnew_int,
                    sizeof(new_int));
                  _mds_instance_list.at(_map_handle_to_mds_instance[
                    unique_handle]).first = DicesRcDriver::OK;
                }
                component_spec_index += sizeof(new_int);
              }
            }
          }
            break;
          case NOM_ATTR_MDS_GEN_INFO:
            break;
          case NOM_ATTR_ID_PROD_SPECN:
          {
            intellivue::ProductionSpec* pproduction_spec =
              reinterpret_cast<intellivue::ProductionSpec *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!pproduction_spec)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into ProductionSpec. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            int new_count = pproduction_spec->count;
            int seq_max = _mds_instance_list.at(_map_handle_to_mds_instance[
              unique_handle]).second->production_specification.maximum();
            if (pproduction_spec->count > seq_max)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "The count of ProdSpecEntry "
                "from intellivue (" << static_cast<int>(pproduction_spec->
                count) << ") exceeds the maximum DDS sequence size for "
                "ice::ProductionSpec ( " << seq_max << "). attribute_id: "
                << static_cast<int>(attribute_id));
              // Set count to maximum so we can still continue parsing.
              new_count = seq_max;
            }

            if (!_mds_instance_list.at(_map_handle_to_mds_instance[
              unique_handle]).second->production_specification.ensure_length(
              new_count, new_count))
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length "
                "for ice::ProductionSpec sequence with length "
                << static_cast<int>(new_count) << ". attribute_id: "
                << static_cast<int>(attribute_id));
              return DicesRcPhilipsIntellivueMP70::DDS_SEQUENCE_ENSURE_LENGTH_FAILURE;
            }

            for (int entry_index = 0; entry_index < new_count; entry_index++)
            {
              if (!pproduction_spec->value)
              {
                LOG4CPLUS_WARN(root_logger, sfn << "ProductionSpec "
                  "ProdSpecEntry list pointer is null. attribute_id: "
                  << static_cast<int>(attribute_id));
                break;
              }

              ice::ProdSpecType dices_prod_spec_type = ice::unspecified;
              DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                ConvertIntellivueProdSpecTypeToDicesProdSpecType(
                &dices_prod_spec_type,
                pproduction_spec->value[entry_index].spec_type);
              if (status != DicesRcPhilipsIntellivueMP70::OK)
              {
                LOG4CPLUS_ERROR(root_logger, sfn <<
                  DicesRcPhilipsIntellivueMP70StatusMessage::
                  DicesRcPhilipsIntellivueMP70ToString(status));
                return status;
              }
              if (_mds_instance_list.at(_map_handle_to_mds_instance[
                unique_handle]).second->production_specification[entry_index].
                spec_type != dices_prod_spec_type)
              {
                _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                  second->production_specification[entry_index].spec_type =
                  dices_prod_spec_type;
                _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                  first = DicesRcDriver::OK;
              }

              if (_mds_instance_list.at(_map_handle_to_mds_instance[
                unique_handle]).second->production_specification[entry_index].
                component_id != pproduction_spec->value[entry_index].
                component_id)
              {
                _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                  second->production_specification[entry_index].component_id =
                  pproduction_spec->value[entry_index].
                  component_id;
                _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                  first = DicesRcDriver::OK;
              }

              std::string prod_spec;
              for (
                int label_index = 0;
                label_index < pproduction_spec->value[entry_index].prod_spec.length;
                label_index++)
              {
                if (!pproduction_spec->value[entry_index].prod_spec.value)
                {
                  LOG4CPLUS_WARN(root_logger, sfn << "Value is a null pointer in "
                    "prod_spec VariableLabel. attribute_id: "
                    << static_cast<int>(attribute_id));
                  break;
                }
                prod_spec += static_cast<char>(
                  pproduction_spec->value[entry_index].prod_spec.value[label_index]);
              }

              if (strncmp(
                _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                second->production_specification[entry_index].prod_spec,
                prod_spec.c_str(),
                ice::LONG_STRING_LEN) != 0)
              {
                strncpy(
                  _mds_instance_list.at(_map_handle_to_mds_instance[
                  unique_handle]).second->production_specification[entry_index].
                  prod_spec,
                  prod_spec.c_str(),
                  ice::LONG_STRING_LEN);
                _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle])
                  .second->production_specification[entry_index].prod_spec[
                  ice::LONG_STRING_LEN] = '\0';
                _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                  first = DicesRcDriver::OK;
              }
            }
          }
            break;
          case NOM_ATTR_VMS_MDS_STAT:
          {
            intellivue::MDSStatus* pmds_status =
              reinterpret_cast<intellivue::MDSStatus *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!pmds_status)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into MDSStatus. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            ice::MDSStatus dices_mds_status = ice::operating;
            DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
              ConvertIntellivueMDSStatusToDicesMDSStatus(
              &dices_mds_status,
              *pmds_status);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }

            if (_mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
              second->mds_status != dices_mds_status)
            {
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                second->mds_status = dices_mds_status;
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                first = DicesRcDriver::OK;
            }
          }
            break;
          case NOM_ATTR_ID_BED_LABEL:
            break;
          case NOM_ATTR_MODE_OP:
          {
            intellivue::PrivateOID* poperating_mode =
              reinterpret_cast<intellivue::PrivateOID *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!poperating_mode)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into PrivateOID. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            if (!_mds_instance_list.at(_map_handle_to_mds_instance[
              unique_handle]).second->operating_mode)
            {
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                second->operating_mode = reinterpret_cast<ice::PrivateOid *>(
                DDS::Heap_malloc(sizeof(ice::PrivateOid)));
              if (!_mds_instance_list.at(_map_handle_to_mds_instance[
                unique_handle]).second->operating_mode)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to "
                  "allocate memory for ice::PrivateOid. attribute_id: "
                  << static_cast<int>(attribute_id));
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
            }

            if (*_mds_instance_list.at(_map_handle_to_mds_instance[
              unique_handle]).second->operating_mode != *poperating_mode)
            {
              *_mds_instance_list.at(_map_handle_to_mds_instance[
                unique_handle]).second->operating_mode = *poperating_mode;
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                first = DicesRcDriver::OK;
            }
          }
            break;
          case NOM_ATTR_AREA_APPL:
            break;
          case NOM_ATTR_TIME_ABS:
          {
            intellivue::AbsoluteTime* pabsolute_time =
              reinterpret_cast<intellivue::AbsoluteTime *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!pabsolute_time)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into AbsoluteTime. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            if (pabsolute_time->century != 0xFF
              || pabsolute_time->year != 0xFF
              || pabsolute_time->month != 0xFF
              || pabsolute_time->day != 0xFF
              || pabsolute_time->hour != 0xFF
              || pabsolute_time->minute != 0xFF
              || pabsolute_time->second != 0xFF
              || pabsolute_time->sec_fractions != 0xFF)
            {
              if (!_mds_instance_list.at(_map_handle_to_mds_instance[
                unique_handle]).second->date_and_time)
              {
                _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                  second->date_and_time = reinterpret_cast<ice::Timespec *>(
                  DDS::Heap_malloc(sizeof(ice::Timespec)));
                if (!_mds_instance_list.at(_map_handle_to_mds_instance[
                  unique_handle]).second->date_and_time)
                {
                  LOG4CPLUS_ERROR(root_logger, sfn << "Failed to "
                    "allocate memory for ice::Timespec. attribute_id: "
                    << static_cast<int>(attribute_id));
                  return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
                }
              }

              DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                ConvertIntellivueAbsoluteTimeToDicesTimespec(
                _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                second->date_and_time,
                *pabsolute_time);
              if (status != DicesRcPhilipsIntellivueMP70::OK)
              {
                LOG4CPLUS_ERROR(root_logger, sfn <<
                  DicesRcPhilipsIntellivueMP70StatusMessage::
                  DicesRcPhilipsIntellivueMP70ToString(status));
                return status;
              }
            }
          }
            break;
          case NOM_ATTR_TIME_REL:
          {
            intellivue::RelativeTime* prelative_time =
              reinterpret_cast<intellivue::RelativeTime *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!prelative_time)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into RelativeTime. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            if (!_mds_instance_list.at(_map_handle_to_mds_instance[
              unique_handle]).second->relative_time)
            {
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                second->relative_time = reinterpret_cast<ice::Duration *>(
                DDS::Heap_malloc(sizeof(ice::Duration)));
              if (!_mds_instance_list.at(_map_handle_to_mds_instance[
                unique_handle]).second->relative_time)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to "
                  "allocate memory for ice::Timespec. attribute_id: "
                  << static_cast<int>(attribute_id));
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
            }

            DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
              ConvertIntellivueRelativeTimeToDicesDuration(
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
              second->relative_time,
              *prelative_time);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }
          }
            break;
          case NOM_ATTR_ALTITUDE:
          {
            int16_t* paltitude = reinterpret_cast<int16_t *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!paltitude)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into int16_t. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            if (!_mds_instance_list.at(_map_handle_to_mds_instance[
              unique_handle]).second->altitude_meters)
            {
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                second->altitude_meters = reinterpret_cast<ice::INT16 *>(
                DDS::Heap_malloc(sizeof(ice::INT16)));
              if (!_mds_instance_list.at(_map_handle_to_mds_instance[
                unique_handle]).second->altitude_meters)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to "
                  "allocate memory for ice::INT16. attribute_id: "
                  << static_cast<int>(attribute_id));
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
            }

            if (*_mds_instance_list.at(_map_handle_to_mds_instance[
              unique_handle]).second->altitude_meters != *paltitude)
            {
              *_mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                second->altitude_meters = *paltitude;
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                first = DicesRcDriver::OK;
            }
          }
            break;
          case NOM_ATTR_LINE_FREQ:
          {
            intellivue::LineFrequency* pline_frequency =
              reinterpret_cast<intellivue::LineFrequency *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!pline_frequency)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into intellivue::LineFrequency. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            if (!_mds_instance_list.at(_map_handle_to_mds_instance[
              unique_handle]).second->line_frequency)
            {
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                second->line_frequency =
                reinterpret_cast<ice::LineFrequency *>(
                DDS::Heap_malloc(sizeof(ice::LineFrequency)));
              if (!_mds_instance_list.at(_map_handle_to_mds_instance[
                unique_handle]).second->line_frequency)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to "
                  "allocate memory for ice::LineFrequency. attribute_id: "
                  << static_cast<int>(attribute_id));
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
            }

            ice::LineFrequency dices_line_frequency = ice::line_f_unspec;
            DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
              ConvertIntellivueLineFrequencyToDicesLineFrequency(
              &dices_line_frequency,
              *pline_frequency);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }

            if (*_mds_instance_list.at(_map_handle_to_mds_instance[
              unique_handle]).second->line_frequency != dices_line_frequency)
            {
              *_mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                second->line_frequency = dices_line_frequency;
              _mds_instance_list.at(_map_handle_to_mds_instance[unique_handle]).
                first = DicesRcDriver::OK;
            }
          }
            break;
          case NOM_ATTR_ID_ASSOC_NO:
            break;
          default:
            break;
        }
      }
    }
  }

  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 DDPhilipsIntellivueMP70Parser::SetSinglePatientDemographicsResponseData()
{
  static const char* sfn = "DDPhilipsIntellivueMP70Parser::"
    "SetSinglePatientDemographicsResponseData() ";

  intellivue::GlbHandle glb_handle = {
    _single_poll_response.actionresult.managed_object.m_obj_inst.context_id,
    _single_poll_response.actionresult.managed_object.m_obj_inst.handle
  };

  for (
    int ix = 0;
    ix < _single_poll_response.pollReply.poll_info_list.count;
    ix++)
  {
    if (!_single_poll_response.pollReply.poll_info_list.value)
    {
      LOG4CPLUS_WARN(root_logger, sfn << "SingleContextPoll array in "
        "PollInfoList is a null pointer");
      break;
    }
    intellivue::MdsContext single_context_poll_context_id =
      _single_poll_response.pollReply.poll_info_list.value[ix].context_id;

    for (
      int iy = 0;
      iy < _single_poll_response.pollReply.poll_info_list.value[ix].
      poll_info.count;
      iy++)
    {
      if (!_single_poll_response.pollReply.poll_info_list.value[ix].poll_info.value)
      {
        LOG4CPLUS_WARN(root_logger, sfn << "ObservationPoll array in "
          "poll_info is a null pointer");
        break;
      }

      for (
        int iz = 0;
        iz < _single_poll_response.pollReply.poll_info_list.value[ix].
        poll_info.value[iy].attributes.count;
        iz++)
      {
        // Get handle
        intellivue::Handle obj_handle =
          _single_poll_response.pollReply.poll_info_list.value[ix].
          poll_info.value[iy].obj_handle;

        std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>
          unique_handle(glb_handle.context_id, glb_handle.handle, single_context_poll_context_id, obj_handle);

        std::map<
          std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
          unsigned int>::iterator pat_demo_it;
        pat_demo_it = _map_handle_to_pat_demo_instance.find(unique_handle);
        if (pat_demo_it == _map_handle_to_pat_demo_instance.end())
        {
          if (_pat_demo_vector_max_index
            >= _patient_demographics_req_response_instance_list.size())
          {
            LOG4CPLUS_INFO(root_logger, sfn << "The maximum number of patient demographics request "
              "instances (" << _patient_demographics_req_response_instance_list.size() << ") are already "
              "in use. Inserting additional instances.");

            unsigned int pat_demo_inst_diff = _pat_demo_vector_max_index
                - _patient_demographics_req_response_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= pat_demo_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::PatientDemographics*> pat_demo_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::PatientDemographicsTypeSupport::create_data());
              if (!pat_demo_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for PatientDemographics instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _patient_demographics_req_response_instance_list.push_back(pat_demo_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "patient demographics request pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }
          }
          std::pair < std::map<
            std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
            unsigned int>::iterator,
            bool> ret = _map_handle_to_pat_demo_instance.insert(
            std::pair<
            std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
            unsigned int>(unique_handle,
            _pat_demo_vector_max_index++));
          if (!ret.second)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert object "
              "handle and vector index into patient demographics map.");
            return DicesRcPhilipsIntellivueMP70::FAIL;
          }

          unsigned int pat_demo_index = 0;
          try
          {
            pat_demo_index = _map_handle_to_pat_demo_instance.at(unique_handle);
          }
          catch (std::exception& ex)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get patient "
              "demographics vector index from map with object handle: "
              << static_cast<int>(std::get<3>(unique_handle)) << ". " << ex.what());
            return DicesRcPhilipsIntellivueMP70::FAIL;
          }

          ice::PatientDemographics* instance = nullptr;
          try
          {
            instance = _patient_demographics_req_response_instance_list.at(
              pat_demo_index).second;
            if (!instance)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "ice::PatientDemographics "
                "instance is a null pointer at vector index: "
                << pat_demo_index);
              return DicesRcPhilipsIntellivueMP70::FAIL;
            }
          }
          catch (std::exception& ex)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get patient "
              "demographics instance with vector index: "
              << static_cast<int>(pat_demo_index) << ". " << ex.what());
            return DicesRcPhilipsIntellivueMP70::FAIL;
          }
          if (instance->handle == 0)
          {
            // Generate new pat demo handle
            intellivue::Handle new_handle = 0;
            DicesRcPhilipsIntellivueMP70 status = GenerateNewHandle(
              &new_handle);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }
            // Set new handle for this instance.
            instance->handle = new_handle;
          }
        }
        std::map<
          std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
          unsigned int>::iterator pat_ident_it;
        pat_ident_it = _map_handle_to_pat_ident_instance.find(unique_handle);
        if (pat_ident_it == _map_handle_to_pat_ident_instance.end())
        {
          if (_pat_ident_vector_max_index
            >= _patient_identification_req_response_instance_list.size())
          {
            LOG4CPLUS_INFO(root_logger, sfn << "The maximum number of patient identification request "
              "instances (" << _patient_identification_req_response_instance_list.size() << ") are already "
              "in use. Inserting additional instances.");

            unsigned int pat_ident_inst_diff = _pat_ident_vector_max_index
                - _patient_identification_req_response_instance_list.size();
            for (unsigned int inst_count = 0;
                 inst_count <= pat_ident_inst_diff;
                 inst_count++)
            {
              std::pair<DicesRcDriver, ice::PatientIdentification*> pat_ident_pair(
                    DicesRcDriver::NO_NEW_DATA,
                    ice::PatientIdentificationTypeSupport::create_data());
              if (!pat_ident_pair.second)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for PatientIdentification instance");
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
              try
              {
                _patient_identification_req_response_instance_list.push_back(pat_ident_pair);
              }
              catch(std::exception& ex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push_back "
                                                    "patient identification request pair onto vector. " << ex.what());
                return DicesRcPhilipsIntellivueMP70::FAIL;
              }
            }
          }

          std::pair < std::map<
            std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
            unsigned int>::iterator,
            bool> ret = _map_handle_to_pat_ident_instance.insert(
            std::pair<
            std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
            unsigned int>(unique_handle,
            _pat_ident_vector_max_index++));
          if (!ret.second)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed to insert object "
              "handle and vector index into patient identification map.");
            return DicesRcPhilipsIntellivueMP70::FAIL;
          }

          unsigned int pat_ident_index = 0;
          try
          {
            pat_ident_index = _map_handle_to_pat_ident_instance.at(unique_handle);
          }
          catch (std::exception& ex)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get patient "
              "identification vector index from map with object handle: "
              << static_cast<int>(std::get<3>(unique_handle)) << ". " << ex.what());
            return DicesRcPhilipsIntellivueMP70::FAIL;
          }

          ice::PatientIdentification* instance = nullptr;
          try
          {
            instance = _patient_identification_req_response_instance_list.at(
              pat_ident_index).second;
            if (!instance)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "ice::PatientIdentification "
                "instance is a null pointer at vector index: "
                << pat_ident_index);
              return DicesRcPhilipsIntellivueMP70::FAIL;
            }
          }
          catch (std::exception& ex)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get patient "
              "identification instance with vector index: "
              << static_cast<int>(pat_ident_index) << ". " << ex.what());
            return DicesRcPhilipsIntellivueMP70::FAIL;
          }
          if (instance->handle == 0)
          {
            // Generate new pat ident handle
            intellivue::Handle new_handle = 0;
            DicesRcPhilipsIntellivueMP70 status = GenerateNewHandle(
              &new_handle);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }
            // Set new handle for this instance.
            instance->handle = new_handle;
          }
        }

        intellivue::OIDType attribute_id = _single_poll_response.pollReply.
          poll_info_list.value[ix].poll_info.value[iy].attributes.value[iz].
          attribute_id;
        switch (attribute_id)
        {
          case NOM_ATTR_ID_HANDLE:
          {
            intellivue::Handle* phandle =
              reinterpret_cast<intellivue::Handle *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!phandle)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into intellivue::Handle. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>
              handle_attr(glb_handle.context_id, glb_handle.handle, single_context_poll_context_id, *phandle);

            std::map<
              std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
              unsigned int>::iterator pat_demo_it;
            pat_demo_it = _map_handle_to_pat_demo_instance.find(handle_attr);
            if (pat_demo_it == _map_handle_to_pat_demo_instance.end())
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Intellivue attribute "
                "handle (" << static_cast<int>(*phandle) << ") is different "
                "than object handle (" << static_cast<int>(std::get<3>(handle_attr))
                << "). Couldn't find handle in handle to pat demo map.");
            }

            std::map<
              std::tuple<intellivue::MdsContext, intellivue::Handle, intellivue::MdsContext, intellivue::Handle>,
              unsigned int>::iterator pat_ident_it;
            pat_ident_it = _map_handle_to_pat_ident_instance.find(handle_attr);
            if (pat_ident_it == _map_handle_to_pat_ident_instance.end())
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Intellivue attribute "
                "handle (" << static_cast<int>(*phandle) << ") is different "
                "than object handle (" << static_cast<int>(std::get<3>(handle_attr))
                << "). Couldn't find handle in handle to vmd map.");
            }
            // NOTE: Handles for pat demo and pat ident have already been set
            // with handles generated by this driver.

            ice::HANDLE mds_handle = 0;
            if (_mds_instance_list.size() > 0)
            {
              if (_mds_instance_list.at(0).second)
              {
                mds_handle = _mds_instance_list.at(0).second->handle;
              }
            }
            _patient_identification_req_response_instance_list.at(
              _map_handle_to_pat_ident_instance[unique_handle]).second->
              parent_handle = mds_handle;

            _patient_demographics_req_response_instance_list.at(
              _map_handle_to_pat_demo_instance[unique_handle]).second->
              parent_handle = mds_handle;
          }
            break;
          case NOM_ATTR_PT_DEMOG_ST:
          {
            intellivue::PatDemoState* ppat_demo_state =
              reinterpret_cast<intellivue::PatDemoState *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!ppat_demo_state)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into intellivue::PatDemoState. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            ice::PatAdmitState dices_pat_admit_state = ice::pre_admitted;
            DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
              ConvertIntellivuePatDemoStateToDicesPatAdmitState(
              &dices_pat_admit_state,
              *ppat_demo_state);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }

            if (_patient_identification_req_response_instance_list.at(
              _map_handle_to_pat_ident_instance[unique_handle]).second->
              pat_admit_state != dices_pat_admit_state)
            {
              _patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).second->
                pat_admit_state = dices_pat_admit_state;
              _patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).first =
                DicesRcDriver::OK;
            }
          }
            break;
          case NOM_ATTR_PT_TYPE:
          {
            intellivue::PatientType* ppatient_type =
              reinterpret_cast<intellivue::PatientType *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!ppatient_type)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into intellivue::PatientType. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            if (!_patient_demographics_req_response_instance_list.at(
              _map_handle_to_pat_demo_instance[unique_handle]).second->
              patient_type)
            {
              _patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).second->
                patient_type = reinterpret_cast<ice::PatientType *>(
                DDS::Heap_malloc(sizeof(ice::PatientType)));
              if (!_patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).second->
                patient_type)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to "
                  "allocate memory for ice::PatientType. attribute_id: "
                  << static_cast<int>(attribute_id));
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
            }

            ice::PatientType dices_pat_type = ice::pt_unspecified;
            DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
              ConvertIntellivuePatientTypeToDicesPatientType(
              &dices_pat_type,
              *ppatient_type);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }

            if (*_patient_demographics_req_response_instance_list.at(
              _map_handle_to_pat_demo_instance[unique_handle]).second->
              patient_type != dices_pat_type)
            {
              *_patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).second->
                patient_type = dices_pat_type;
              _patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).first =
                DicesRcDriver::OK;
            }
          }
            break;
          case NOM_ATTR_PT_PACED_MODE:
            break;
          case NOM_ATTR_PT_NAME_GIVEN:
          {
            intellivue::String* pname_given =
              reinterpret_cast<intellivue::String *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!pname_given)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into intellivue::String. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            std::string given_name_string;
            for (int iindex = 0; iindex < pname_given->length; iindex++)
            {
              uint8_t ch8 = '\0';
              uint16_t ch16 = pname_given->value[iindex];
              // Convert to byte array
              uint8_t byte_0 = ch16 & 0x00ff;
              uint8_t byte_1 = ch16 >> 8;
              uint8_t buf[2] = { byte_0, byte_1 };

              ch16 = ntohs(*(reinterpret_cast<uint16_t*>(&buf[0])));

              DicesRcPhilipsIntellivueMP70 status =
                IntellivueUtils::Convert16BitUnicodeToAscii(
                ch16,
                &ch8);
              if (status != DicesRcPhilipsIntellivueMP70::OK)
              {
                LOG4CPLUS_ERROR(root_logger, sfn <<
                  DicesRcPhilipsIntellivueMP70StatusMessage::
                  DicesRcPhilipsIntellivueMP70ToString(status));
                return status;
              }
              given_name_string += static_cast<char>(ch8);
            }

            if (strncmp(_patient_identification_req_response_instance_list.at(
              _map_handle_to_pat_ident_instance[unique_handle]).second->
              given_name,
              given_name_string.c_str(),
              ice::SHORT_STRING_LEN) != 0)
            {
              strncpy(_patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).second->
                given_name,
                given_name_string.c_str(),
                ice::SHORT_STRING_LEN);
              _patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).second->
                given_name[ice::SHORT_STRING_LEN] = '\0';
              _patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).first =
                DicesRcDriver::OK;
            }
          }
            break;
          case NOM_ATTR_PT_NAME_FAMILY:
          {
            intellivue::String* pfamily_name =
              reinterpret_cast<intellivue::String *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!pfamily_name)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into intellivue::String. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            std::string family_name_string;
            for (int iindex = 0; iindex < pfamily_name->length; iindex++)
            {
              uint8_t ch8 = '\0';
              uint16_t ch16 = pfamily_name->value[iindex];
              // Convert to byte array
              uint8_t byte_0 = ch16 & 0x00ff;
              uint8_t byte_1 = ch16 >> 8;
              uint8_t buf[2] = { byte_0, byte_1 };

              ch16 = ntohs(*(reinterpret_cast<uint16_t*>(&buf[0])));

              DicesRcPhilipsIntellivueMP70 status =
                IntellivueUtils::Convert16BitUnicodeToAscii(
                ch16,
                &ch8);
              if (status != DicesRcPhilipsIntellivueMP70::OK)
              {
                LOG4CPLUS_ERROR(root_logger, sfn <<
                  DicesRcPhilipsIntellivueMP70StatusMessage::
                  DicesRcPhilipsIntellivueMP70ToString(status));
                return status;
              }
              family_name_string += static_cast<char>(ch8);
            }

            if (strncmp(_patient_identification_req_response_instance_list.at(
              _map_handle_to_pat_ident_instance[unique_handle]).second->
              family_name,
              family_name_string.c_str(),
              ice::SHORT_STRING_LEN) != 0)
            {
              strncpy(_patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).second->
                family_name,
                family_name_string.c_str(),
                ice::SHORT_STRING_LEN);
              _patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).second->
                family_name[ice::SHORT_STRING_LEN] = '\0';
              _patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).first =
                DicesRcDriver::OK;
            }
          }
            break;
          case NOM_ATTR_PT_ID:
          {
            intellivue::String* ppat_id =
              reinterpret_cast<intellivue::String *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!ppat_id)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into intellivue::String. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            std::string pat_id_string;
            for (int iindex = 0; iindex < ppat_id->length; iindex++)
            {
              uint8_t ch8 = '\0';
              uint16_t ch16 = ppat_id->value[iindex];
              // Convert to byte array
              uint8_t byte_0 = ch16 & 0x00ff;
              uint8_t byte_1 = ch16 >> 8;
              uint8_t buf[2] = { byte_0, byte_1 };

              ch16 = ntohs(*(reinterpret_cast<uint16_t*>(&buf[0])));

              DicesRcPhilipsIntellivueMP70 status =
                IntellivueUtils::Convert16BitUnicodeToAscii(
                ch16,
                &ch8);
              if (status != DicesRcPhilipsIntellivueMP70::OK)
              {
                LOG4CPLUS_ERROR(root_logger, sfn <<
                  DicesRcPhilipsIntellivueMP70StatusMessage::
                  DicesRcPhilipsIntellivueMP70ToString(status));
                return status;
              }
              pat_id_string += static_cast<char>(ch8);
            }

            if (strncmp(_patient_identification_req_response_instance_list.at(
              _map_handle_to_pat_ident_instance[unique_handle]).second->
              patient_id,
              pat_id_string.c_str(),
              ice::MEDIUM_STRING_LEN) != 0)
            {
              strncpy(_patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).second->
                patient_id,
                pat_id_string.c_str(),
                ice::MEDIUM_STRING_LEN);
              _patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).second->
                patient_id[ice::MEDIUM_STRING_LEN] = '\0';
              _patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).first =
                DicesRcDriver::OK;
            }
          }
            break;
          case NOM_ATTR_PT_SEX:
          {
            intellivue::PatientSex* ppatient_sex =
              reinterpret_cast<intellivue::PatientSex *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!ppatient_sex)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into intellivue::PatientSex. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            if (!_patient_demographics_req_response_instance_list.at(
              _map_handle_to_pat_demo_instance[unique_handle]).second->sex)
            {
              _patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).second->sex =
                reinterpret_cast<ice::PatientSex *>(
                DDS::Heap_malloc(sizeof(ice::PatientSex)));
              if (!_patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).second->sex)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to "
                  "allocate memory for ice::PatientSex. attribute_id: "
                  << static_cast<int>(attribute_id));
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
            }

            ice::PatientSex dices_pat_sex = ice::sex_unknown;
            DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
              ConvertIntellivuePatientSexToDicesPatientSex(
              &dices_pat_sex,
              *ppatient_sex);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                DicesRcPhilipsIntellivueMP70StatusMessage::
                DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }

            if (*_patient_demographics_req_response_instance_list.at(
              _map_handle_to_pat_demo_instance[unique_handle]).second->sex
              != dices_pat_sex)
            {
              *_patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).second->sex =
                dices_pat_sex;
              _patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).first =
                DicesRcDriver::OK;
            }
          }
            break;
          case NOM_ATTR_PT_DOB:
          {
            intellivue::AbsoluteTime* ppat_dob =
              reinterpret_cast<intellivue::AbsoluteTime *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!ppat_dob)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into intellivue::AbsoluteTime. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            if (!_patient_identification_req_response_instance_list.at(
              _map_handle_to_pat_ident_instance[unique_handle]).second->
              date_of_birth)
            {
              _patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).second->
                date_of_birth = reinterpret_cast<ice::Date *>(
                DDS::Heap_malloc(sizeof(ice::Date)));
              if (!_patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).second->
                date_of_birth)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to "
                  "allocate memory for ice::Date. attribute_id: "
                  << static_cast<int>(attribute_id));
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
            }

            ice::Date dices_pat_dob = { 0 };
            dices_pat_dob.century = ppat_dob->century;
            dices_pat_dob.year = ppat_dob->year;
            dices_pat_dob.month = ppat_dob->month;
            dices_pat_dob.day = ppat_dob->day;

            if (_patient_identification_req_response_instance_list.at(
              _map_handle_to_pat_ident_instance[unique_handle]).second->
              date_of_birth->century != dices_pat_dob.century)
            {
              _patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).second->
                date_of_birth->century = dices_pat_dob.century;
              _patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).first =
                DicesRcDriver::OK;
            }

            if (_patient_identification_req_response_instance_list.at(
              _map_handle_to_pat_ident_instance[unique_handle]).second->
              date_of_birth->year != dices_pat_dob.year)
            {
              _patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).second->
                date_of_birth->year = dices_pat_dob.year;
              _patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).first =
                DicesRcDriver::OK;
            }

            if (_patient_identification_req_response_instance_list.at(
              _map_handle_to_pat_ident_instance[unique_handle]).second->
              date_of_birth->month != dices_pat_dob.month)
            {
              _patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).second->
                date_of_birth->month = dices_pat_dob.month;
              _patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).first =
                DicesRcDriver::OK;
            }

            if (_patient_identification_req_response_instance_list.at(
              _map_handle_to_pat_ident_instance[unique_handle]).second->
              date_of_birth->day != dices_pat_dob.day)
            {
              _patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).second->
                date_of_birth->day = dices_pat_dob.day;
              _patient_identification_req_response_instance_list.at(
                _map_handle_to_pat_ident_instance[unique_handle]).first =
                DicesRcDriver::OK;
            }
          }
            break;
          case NOM_ATTR_PT_HEIGHT:
          {
            intellivue::PatMeasure* ppat_height =
              reinterpret_cast<intellivue::PatMeasure *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!ppat_height)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into intellivue::PatMeasure. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            bool is_invalid = false;
            ice::FLOATType dices_float_type = 0;
            DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                ConvertIntellivueFloatTypeToDicesFloatType(
                  &dices_float_type,
                  ppat_height->value,
                  &is_invalid);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                              DicesRcPhilipsIntellivueMP70StatusMessage::
                              DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }

            if (is_invalid)
            {
              // Intellivue sent invalid number, so we'll send null for
              // this optional field in our DDS Topic.
              if (_patient_demographics_req_response_instance_list.at(
                    _map_handle_to_pat_demo_instance[unique_handle]).second->
                  patient_height)
              {
                // Free memory that has already been allocated and set to
                // null. Set to publish because state changed from
                // allocated to unallocated for this field.
                DDS_Heap_free(_patient_demographics_req_response_instance_list.at(
                                _map_handle_to_pat_demo_instance[unique_handle]).second->
                              patient_height);
                _patient_demographics_req_response_instance_list.at(
                      _map_handle_to_pat_demo_instance[unique_handle]).second->
                    patient_height = nullptr;
                _patient_demographics_req_response_instance_list.at(
                      _map_handle_to_pat_demo_instance[unique_handle]).first =
                    DicesRcDriver::OK;
              }
              break; // Don't continue within this case
            }

            if (!_patient_demographics_req_response_instance_list.at(
              _map_handle_to_pat_demo_instance[unique_handle]).second->
              patient_height)
            {
              _patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).second->
                patient_height = reinterpret_cast<ice::PatMeasure *>(
                DDS::Heap_malloc(sizeof(ice::PatMeasure)));
              if (!_patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).second->
                patient_height)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to "
                  "allocate memory for ice::PatMeasure. attribute_id: "
                  << static_cast<int>(attribute_id));
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
            }

            if (_patient_demographics_req_response_instance_list.at(
              _map_handle_to_pat_demo_instance[unique_handle]).second->
              patient_height->value != dices_float_type)
            {
              _patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).second->
                patient_height->value = dices_float_type;
              _patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).first =
                DicesRcDriver::OK;
            }
            if (_patient_demographics_req_response_instance_list.at(
              _map_handle_to_pat_demo_instance[unique_handle]).second->
              patient_height->m_unit != ppat_height->m_unit)
            {
              _patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).second->
                patient_height->m_unit = ppat_height->m_unit;
              _patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).first =
                DicesRcDriver::OK;
            }
          }
            break;
          case NOM_ATTR_PT_WEIGHT:
          {
            intellivue::PatMeasure* ppat_weight =
              reinterpret_cast<intellivue::PatMeasure *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!ppat_weight)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into intellivue::PatMeasure. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            bool is_invalid = false;
            ice::FLOATType dices_float_type = 0;
            DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                ConvertIntellivueFloatTypeToDicesFloatType(
                  &dices_float_type,
                  ppat_weight->value,
                  &is_invalid);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                              DicesRcPhilipsIntellivueMP70StatusMessage::
                              DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }

            if (is_invalid)
            {
              // Intellivue sent invalid number, so we'll send null for
              // this optional field in our DDS Topic.
              if (_patient_demographics_req_response_instance_list.at(
                    _map_handle_to_pat_demo_instance[unique_handle]).second->
                  patient_weight)
              {
                // Free memory that has already been allocated and set to
                // null. Set to publish because state changed from
                // allocated to unallocated for this field.
                DDS_Heap_free(_patient_demographics_req_response_instance_list.at(
                                _map_handle_to_pat_demo_instance[unique_handle]).second->
                              patient_weight);
                _patient_demographics_req_response_instance_list.at(
                      _map_handle_to_pat_demo_instance[unique_handle]).second->
                    patient_weight = nullptr;
                _patient_demographics_req_response_instance_list.at(
                      _map_handle_to_pat_demo_instance[unique_handle]).first =
                    DicesRcDriver::OK;
              }
              break; // Don't continue within this case
            }

            if (!_patient_demographics_req_response_instance_list.at(
              _map_handle_to_pat_demo_instance[unique_handle]).second->
              patient_weight)
            {
              _patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).second->
                patient_weight = reinterpret_cast<ice::PatMeasure *>(
                DDS::Heap_malloc(sizeof(ice::PatMeasure)));
              if (!_patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).second->
                patient_weight)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to "
                  "allocate memory for ice::PatMeasure. attribute_id: "
                  << static_cast<int>(attribute_id));
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
            }

            if (_patient_demographics_req_response_instance_list.at(
              _map_handle_to_pat_demo_instance[unique_handle]).second->
              patient_weight->value != dices_float_type)
            {
              _patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).second->
                patient_weight->value = dices_float_type;
              _patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).first =
                DicesRcDriver::OK;
            }
            if (_patient_demographics_req_response_instance_list.at(
              _map_handle_to_pat_demo_instance[unique_handle]).second->
              patient_weight->m_unit != ppat_weight->m_unit)
            {
              _patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).second->
                patient_weight->m_unit = ppat_weight->m_unit;
              _patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).first =
                DicesRcDriver::OK;
            }
          }
            break;
          case NOM_ATTR_PT_AGE:
          {
            intellivue::PatMeasure* ppat_age =
              reinterpret_cast<intellivue::PatMeasure *>(
              _single_poll_response.pollReply.poll_info_list.value[ix].
              poll_info.value[iy].attributes.value[iz].attribute_val);
            if (!ppat_age)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
                "attribute_val into intellivue::PatMeasure. attribute_id: "
                << static_cast<int>(attribute_id));
              break;
            }

            bool is_invalid = false;
            ice::FLOATType dices_float_type = 0;
            DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
                ConvertIntellivueFloatTypeToDicesFloatType(
                  &dices_float_type,
                  ppat_age->value,
                  &is_invalid);
            if (status != DicesRcPhilipsIntellivueMP70::OK)
            {
              LOG4CPLUS_ERROR(root_logger, sfn <<
                              DicesRcPhilipsIntellivueMP70StatusMessage::
                              DicesRcPhilipsIntellivueMP70ToString(status));
              return status;
            }

            if (is_invalid)
            {
              // Intellivue sent invalid number, so we'll send null for
              // this optional field in our DDS Topic.
              if (_patient_demographics_req_response_instance_list.at(
                    _map_handle_to_pat_demo_instance[unique_handle]).second->
                  chronological_age)
              {
                // Free memory that has already been allocated and set to
                // null. Set to publish because state changed from
                // allocated to unallocated for this field.
                DDS_Heap_free(_patient_demographics_req_response_instance_list.at(
                                _map_handle_to_pat_demo_instance[unique_handle]).second->
                              chronological_age);
                _patient_demographics_req_response_instance_list.at(
                      _map_handle_to_pat_demo_instance[unique_handle]).second->
                    chronological_age = nullptr;
                _patient_demographics_req_response_instance_list.at(
                      _map_handle_to_pat_demo_instance[unique_handle]).first =
                    DicesRcDriver::OK;
              }
              break; // Don't continue within this case
            }

            if (!_patient_demographics_req_response_instance_list.at(
              _map_handle_to_pat_demo_instance[unique_handle]).second->
              chronological_age)
            {
              _patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).second->
                chronological_age = reinterpret_cast<ice::PatMeasure *>(
                DDS::Heap_malloc(sizeof(ice::PatMeasure)));
              if (!_patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).second->
                chronological_age)
              {
                LOG4CPLUS_ERROR(root_logger, sfn << "Failed to "
                  "allocate memory for ice::PatMeasure. attribute_id: "
                  << static_cast<int>(attribute_id));
                return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
              }
            }

            if (_patient_demographics_req_response_instance_list.at(
              _map_handle_to_pat_demo_instance[unique_handle]).second->
              chronological_age->value != dices_float_type)
            {
              _patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).second->
                chronological_age->value = dices_float_type;
              _patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).first =
                DicesRcDriver::OK;
            }
            if (_patient_demographics_req_response_instance_list.at(
              _map_handle_to_pat_demo_instance[unique_handle]).second->
              chronological_age->m_unit != ppat_age->m_unit)
            {
              _patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).second->
                chronological_age->m_unit = ppat_age->m_unit;
              _patient_demographics_req_response_instance_list.at(
                _map_handle_to_pat_demo_instance[unique_handle]).first =
                DicesRcDriver::OK;
            }
          }
            break;
          case NOM_ATTR_PT_BSA:
            break;
          case NOM_ATTR_PT_BSA_FORMULA:
            break;
          case NOM_ATTR_PT_NOTES1:
          case NOM_ATTR_PT_NOTES2:
            break;
          default:
            break;
        }
      }
    }
  }

  return DicesRcPhilipsIntellivueMP70::OK;
}
