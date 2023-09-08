/*
 * File:   bus_comm.cxx
 * Author: Robert England
 *
 * Created on November 17, 2014
 * Last Modified on November 17, 2014
 */

#include "bus_comm.h"

#include "dices_rc_driver.h"
#include "parser.h"

#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>

#include "patdemoSupport.h"
#include "allergySupport.h"
#include "alarmSupport.h"
#include "dsaSupport.h"
#include "enumSupport.h"
#include "exprSupport.h"
#include "mdsSupport.h"
#include "vmdSupport.h"
#include "numericSupport.h"
#include "rtsaSupport.h"
#include "tsaSupport.h"
#include "docboxSupport.h"

#include "ndds/ndds_namespace_cpp.h"

#include "dicestyperegister.h"
#include "Utilities/DDSUtil/ddsutil.h"
#include "Core/Time/dices-time.h"

static const int kMDSHandle = 10;

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();
static log4cplus::Logger data_logger = log4cplus::Logger::getInstance("datalogger");

static const char* kXMLQosConfig = "DicesBaseDriverConfig.xml";

BusComm::BusComm(Parser* parser) : _parser(parser),
  _participant(nullptr),
  _publisher(nullptr),
  _subscriber(nullptr),
  _patient_identification_req_data_writer(nullptr),
  _patient_demographics_req_data_writer(nullptr),
  _physiological_alarm_signal_data_writer(nullptr),
  _technical_alarm_signal_data_writer(nullptr),
  _information_signal_data_writer(nullptr),
  _reminder_signal_data_writer(nullptr),
  _physiological_alarm_context_data_writer(nullptr),
  _technical_alarm_context_data_writer(nullptr),
  _dsa_meas_context_data_writer(nullptr),
  _dsa_meas_observed_value_data_writer(nullptr),
  _dsa_calc_context_data_writer(nullptr),
  _dsa_calc_observed_value_data_writer(nullptr),
  _dsa_sett_context_data_writer(nullptr),
  _dsa_sett_observed_value_data_writer(nullptr),
  _enumeration_meas_context_data_writer(nullptr),
  _enumeration_meas_observed_value_data_writer(nullptr),
  _enumeration_calc_context_data_writer(nullptr),
  _enumeration_calc_observed_value_data_writer(nullptr),
  _enumeration_sett_context_data_writer(nullptr),
  _enumeration_sett_observed_value_data_writer(nullptr),
  _mds_data_writer(nullptr),
  _vmd_data_writer(nullptr),
  _numeric_meas_context_data_writer(nullptr),
  _numeric_meas_observed_value_data_writer(nullptr),
  _numeric_calc_context_data_writer(nullptr),
  _numeric_calc_observed_value_data_writer(nullptr),
  _numeric_sett_context_data_writer(nullptr),
  _numeric_sett_observed_value_data_writer(nullptr),
  _rtsa_meas_context_data_writer(nullptr),
  _rtsa_meas_observed_value_data_writer(nullptr),
  _rtsa_calc_context_data_writer(nullptr),
  _rtsa_calc_observed_value_data_writer(nullptr),
  _rtsa_sett_context_data_writer(nullptr),
  _rtsa_sett_observed_value_data_writer(nullptr),
  _tsa_meas_context_data_writer(nullptr),
  _tsa_meas_observed_value_data_writer(nullptr),
  _tsa_calc_context_data_writer(nullptr),
  _tsa_calc_observed_value_data_writer(nullptr),
  _tsa_sett_context_data_writer(nullptr),
  _tsa_sett_observed_value_data_writer(nullptr),
  _patient_identification_data_writer(nullptr),
  _patient_demographics_data_writer(nullptr),
  _allergy_data_writer(nullptr),
  _allergy_data_reader(nullptr),
  _diagnosis_data_writer(nullptr),
  _dxhistory_data_writer(nullptr),
  _patient_medication_data_writer(nullptr),
  _patient_demographics_req_data_reader(nullptr),
  _physiological_alarm_context_req_data_reader(nullptr),
  _technical_alarm_context_req_data_reader(nullptr),
  _dsa_meas_context_req_data_reader(nullptr),
  _dsa_calc_context_req_data_reader(nullptr),
  _dsa_sett_context_req_data_reader(nullptr),
  _enumeration_meas_context_req_data_reader(nullptr),
  _enumeration_calc_context_req_data_reader(nullptr),
  _enumeration_sett_context_req_data_reader(nullptr),
  _enumeration_sett_observed_value_req_data_reader(nullptr),
  _numeric_meas_context_req_data_reader(nullptr),
  _numeric_calc_context_req_data_reader(nullptr),
  _numeric_sett_context_req_data_reader(nullptr),
  _numeric_sett_observed_value_req_data_reader(nullptr),
  _rtsa_meas_context_req_data_reader(nullptr),
  _rtsa_calc_context_req_data_reader(nullptr),
  _rtsa_sett_context_req_data_reader(nullptr),
  _tsa_meas_context_req_data_reader(nullptr),
  _tsa_calc_context_req_data_reader(nullptr),
  _tsa_sett_context_req_data_reader(nullptr),
  _patient_identification_req_data_reader(nullptr),
  _device_driver_state_req_data_reader(nullptr) { }

DicesRcDriver BusComm::InitDDSObjects()
{
  static const char* sfn = "BusComm::InitDDSObjects() ";

  // Load custom app creation XML document into Domain Participant Factory.
  try
  {
    DDSUTIL::loadConfig(kXMLQosConfig);
  }
  catch (const DDSUTIL::ReturnCode& ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception occurred loading xml config file "
      << kXMLQosConfig << ". " << ex.what());
    return DicesRcDriver::XML_QOS_FILE_LOAD_FAILURE;
  }

  // NOTE this currently causes a crash when called from an App because the app has already registered some of these types.
  // When the baseApp is finished all these registers will be called exactly once.
  DICESTypeRegister type_register;
  DICESTypeRegisterRC tr_retcode = type_register.registerAllTypes();
  if (tr_retcode != DICESTypeRegisterRC::OK)
  {
    LOG4CPLUS_ERROR(root_logger, " Failed to register participant types." <<
      DICESTypeRegisterRCStatusMessage::DICESTypeRegisterToString(tr_retcode));
    return DicesRcDriver::TYPE_REGISTER_FAILURE;
  }

  // Look up the DomainParticipant
  _participant = DDSTheParticipantFactory->
    create_participant_from_config("DICESBaseDriverParticipantLibrary::DICESBaseDriverParticipant");
  if (!_participant)
  {
    LOG4CPLUS_ERROR(root_logger, " Failed to create DomainParticipant object.");
    return DicesRcDriver::PARTICIPANT_CREATE_FAILURE;
  }

  std::set<CreateWriterName> create_writer_name_list = _parser->
    get_create_writer_name_list();
  if (!create_writer_name_list.empty())
  {
    // Look up the Publisher
    _publisher = _participant->lookup_publisher_by_name("DICESBaseDriverPublisher");
    if (!_publisher)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Publisher object.");
      return DicesRcDriver::PUBLISHER_LOOKUP_FAILURE;
    }
  }

  if (!create_writer_name_list.empty())
  {
    // Look up the Subscriber
    _subscriber = _participant->lookup_subscriber_by_name(
      "DICESBaseDriverSubscriber");
    if (!_subscriber)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Subscriber object.");
      return DicesRcDriver::SUBSCRIBER_LOOKUP_FAILURE;
    }
  }

  if (create_writer_name_list.count(CreateWriterName::DeviceDriverStateWriter))
  {
    DicesRcDriverStatus ds_retcode = _driver_status_handler.DDSInit(
      _publisher,
      _parser->get_ice_id());
    if (ds_retcode != DicesRcDriverStatus::OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to initialize Driver Status handler: "
        << DicesRcDriverStatusStatusMessage::DicesRcDriverStatusToString(ds_retcode));
      return DicesRcDriver::DRIVER_STATUS_HANDLER_INIT_FAILURE;
    }
    ds_retcode = _driver_status_handler.Connecting();
    if (ds_retcode != DicesRcDriverStatus::OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set Driver Status to Connecting: "
        << DicesRcDriverStatusStatusMessage::DicesRcDriverStatusToString(ds_retcode));
      return DicesRcDriver::DRIVER_STATUS_CONNECTING_FAILURE;
    }
  }

  if (create_writer_name_list.count(CreateWriterName::PatientIdentificationReqWriter))
  {
    // Initialize data writers
    DDS::DataWriter* base_patient_identification_req_data_writer = _publisher->lookup_datawriter_by_name("PatientIdentificationReqWriter");
    if (!base_patient_identification_req_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Patient Identification Request Data Writer.");
      return DicesRcDriver::PATIENT_IDENTIFICATION_REQUEST_WRITER_LOOKUP_FAILURE;
    }
    _patient_identification_req_data_writer = ice::PatientIdentificationDataWriter::narrow(base_patient_identification_req_data_writer);
    if (!_patient_identification_req_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Patient Identification Request Data Writer.");
      return DicesRcDriver::PATIENT_IDENTIFICATION_REQUEST_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::PatientDemographicsReqWriter))
  {
    DDS::DataWriter* base_patient_demographics_req_data_writer = _publisher->lookup_datawriter_by_name("PatientDemographicsReqWriter");
    if (!base_patient_demographics_req_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Patient Demographics Request Data Writer.");
      return DicesRcDriver::PATIENT_DEMOGRAPHICS_REQUEST_WRITER_LOOKUP_FAILURE;
    }
    _patient_demographics_req_data_writer = ice::PatientDemographicsDataWriter::narrow(base_patient_demographics_req_data_writer);
    if (!_patient_demographics_req_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Patient Demographics Request Data Writer.");
      return DicesRcDriver::PATIENT_DEMOGRAPHICS_REQUEST_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::PhysiologicalAlarmSignalWriter))
  {
    DDS::DataWriter* base_physiological_alarm_signal_data_writer = _publisher->lookup_datawriter_by_name("PhysiologicalAlarmSignalWriter");
    if (!base_physiological_alarm_signal_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Physiological Alarm Signal Data Writer.");
      return DicesRcDriver::PHYSIOLOGICAL_ALARM_SIGNAL_WRITER_LOOKUP_FAILURE;
    }
    _physiological_alarm_signal_data_writer = ice::AlarmSignalDataWriter::narrow(base_physiological_alarm_signal_data_writer);
    if (!_physiological_alarm_signal_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Physiological Alarm Signal Data Writer.");
      return DicesRcDriver::PHYSIOLOGICAL_ALARM_SIGNAL_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::TechnicalAlarmSignalWriter))
  {
    DDS::DataWriter* base_technical_alarm_signal_data_writer = _publisher->lookup_datawriter_by_name("TechnicalAlarmSignalWriter");
    if (!base_technical_alarm_signal_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Technical Alarm Signal Data Writer.");
      return DicesRcDriver::TECHNICAL_ALARM_SIGNAL_WRITER_LOOKUP_FAILURE;
    }
    _technical_alarm_signal_data_writer = ice::AlarmSignalDataWriter::narrow(base_technical_alarm_signal_data_writer);
    if (!_technical_alarm_signal_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Technical Alarm Signal Data Writer.");
      return DicesRcDriver::TECHNICAL_ALARM_SIGNAL_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::InformationSignalWriter))
  {
    DDS::DataWriter* base_information_signal_data_writer = _publisher->lookup_datawriter_by_name("InformationSignalWriter");
    if (!base_information_signal_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Information Signal Data Writer.");
      return DicesRcDriver::INFORMATION_SIGNAL_WRITER_LOOKUP_FAILURE;
    }
    _information_signal_data_writer = ice::InformationSignalDataWriter::narrow(base_information_signal_data_writer);
    if (!_information_signal_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Information Signal Data Writer.");
      return DicesRcDriver::INFORMATION_SIGNAL_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::ReminderSignalWriter))
  {
    DDS::DataWriter* base_reminder_signal_data_writer = _publisher->lookup_datawriter_by_name("ReminderSignalWriter");
    if (!base_reminder_signal_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Reminder Signal Data Writer.");
      return DicesRcDriver::REMINDER_SIGNAL_WRITER_LOOKUP_FAILURE;
    }
    _reminder_signal_data_writer = ice::ReminderSignalDataWriter::narrow(base_reminder_signal_data_writer);
    if (!_reminder_signal_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Reminder Signal Data Writer.");
      return DicesRcDriver::REMINDER_SIGNAL_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::PhysiologicalAlarmContextWriter))
  {
    DDS::DataWriter* base_physiological_alarm_context_data_writer = _publisher->lookup_datawriter_by_name("PhysiologicalAlarmContextWriter");
    if (!base_physiological_alarm_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Physiological Alarm Context Data Writer.");
      return DicesRcDriver::PHYSIOLOGICAL_ALARM_CONTEXT_WRITER_LOOKUP_FAILURE;
    }
    _physiological_alarm_context_data_writer = ice::AlarmContextDataWriter::narrow(base_physiological_alarm_context_data_writer);
    if (!_physiological_alarm_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Physiological Alarm Context Data Writer.");
      return DicesRcDriver::PHYSIOLOGICAL_ALARM_CONTEXT_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::TechnicalAlarmContextWriter))
  {
    DDS::DataWriter* base_technical_alarm_context_data_writer = _publisher->lookup_datawriter_by_name("TechnicalAlarmContextWriter");
    if (!base_technical_alarm_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Technical Alarm Context Data Writer.");
      return DicesRcDriver::TECHNICAL_ALARM_CONTEXT_WRITER_LOOKUP_FAILURE;
    }
    _technical_alarm_context_data_writer = ice::AlarmContextDataWriter::narrow(base_technical_alarm_context_data_writer);
    if (!_technical_alarm_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Technical Alarm Context Data Writer.");
      return DicesRcDriver::TECHNICAL_ALARM_CONTEXT_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::DSAMeasContextWriter))
  {
    DDS::DataWriter* base_dsa_meas_context_data_writer = _publisher->lookup_datawriter_by_name("DSAMeasContextWriter");
    if (!base_dsa_meas_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup DSA Meas Context Data Writer.");
      return DicesRcDriver::DSA_MEAS_CONTEXT_WRITER_LOOKUP_FAILURE;
    }
    _dsa_meas_context_data_writer = ice::DSAContextDataWriter::narrow(base_dsa_meas_context_data_writer);
    if (!_dsa_meas_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow DSA Meas Context Data Writer.");
      return DicesRcDriver::DSA_MEAS_CONTEXT_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::DSAMeasObservedValueWriter))
  {
    DDS::DataWriter* base_dsa_meas_observed_value_data_writer = _publisher->lookup_datawriter_by_name("DSAMeasObservedValueWriter");
    if (!base_dsa_meas_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup DSA Meas Observed Value Data Writer.");
      return DicesRcDriver::DSA_MEAS_OBSERVED_VALUE_WRITER_LOOKUP_FAILURE;
    }
    _dsa_meas_observed_value_data_writer = ice::DSAObservedValueDataWriter::narrow(base_dsa_meas_observed_value_data_writer);
    if (!_dsa_meas_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow DSA Meas Observed Value Data Writer.");
      return DicesRcDriver::DSA_MEAS_OBSERVED_VALUE_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::DSACalcContextWriter))
  {
    DDS::DataWriter* base_dsa_calc_context_data_writer = _publisher->lookup_datawriter_by_name("DSACalcContextWriter");
    if (!base_dsa_calc_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup DSA Calc Context Data Writer.");
      return DicesRcDriver::DSA_CALC_CONTEXT_WRITER_LOOKUP_FAILURE;
    }
    _dsa_calc_context_data_writer = ice::DSAContextDataWriter::narrow(base_dsa_calc_context_data_writer);
    if (!_dsa_calc_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow DSA Calc Context Data Writer.");
      return DicesRcDriver::DSA_CALC_CONTEXT_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::DSACalcObservedValueWriter))
  {
    DDS::DataWriter* base_dsa_calc_observed_value_data_writer = _publisher->lookup_datawriter_by_name("DSACalcObservedValueWriter");
    if (!base_dsa_calc_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup DSA Calc Observed Value Data Writer.");
      return DicesRcDriver::DSA_CALC_OBSERVED_VALUE_WRITER_LOOKUP_FAILURE;
    }
    _dsa_calc_observed_value_data_writer = ice::DSAObservedValueDataWriter::narrow(base_dsa_calc_observed_value_data_writer);
    if (!_dsa_calc_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow DSA Calc Observed Value Data Writer.");
      return DicesRcDriver::DSA_CALC_OBSERVED_VALUE_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::DSASettContextWriter))
  {
    DDS::DataWriter* base_dsa_sett_context_data_writer = _publisher->lookup_datawriter_by_name("DSASettContextWriter");
    if (!base_dsa_sett_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup DSA Sett Context Data Writer.");
      return DicesRcDriver::DSA_SETT_CONTEXT_WRITER_LOOKUP_FAILURE;
    }
    _dsa_sett_context_data_writer = ice::DSAContextDataWriter::narrow(base_dsa_sett_context_data_writer);
    if (!_dsa_sett_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow DSA Sett Context Data Writer.");
      return DicesRcDriver::DSA_SETT_CONTEXT_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::DSASettObservedValueWriter))
  {
    DDS::DataWriter* base_dsa_sett_observed_value_data_writer = _publisher->lookup_datawriter_by_name("DSASettObservedValueWriter");
    if (!base_dsa_sett_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup DSA Sett Observed Value Data Writer.");
      return DicesRcDriver::DSA_SETT_OBSERVED_VALUE_WRITER_LOOKUP_FAILURE;
    }
    _dsa_sett_observed_value_data_writer = ice::DSAObservedValueDataWriter::narrow(base_dsa_sett_observed_value_data_writer);
    if (!_dsa_sett_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow DSA Sett Observed Value Data Writer.");
      return DicesRcDriver::DSA_SETT_OBSERVED_VALUE_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::EnumerationMeasContextWriter))
  {
    DDS::DataWriter* base_enumeration_meas_context_data_writer = _publisher->lookup_datawriter_by_name("EnumerationMeasContextWriter");
    if (!base_enumeration_meas_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Enumeration Meas Context Data Writer.");
      return DicesRcDriver::ENUMERATION_MEAS_CONTEXT_WRITER_LOOKUP_FAILURE;
    }
    _enumeration_meas_context_data_writer = ice::EnumerationContextDataWriter::narrow(base_enumeration_meas_context_data_writer);
    if (!_enumeration_meas_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Enumeration Meas Context Data Writer.");
      return DicesRcDriver::ENUMERATION_MEAS_CONTEXT_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::EnumerationMeasObservedValueWriter))
  {
    DDS::DataWriter* base_enumeration_meas_observed_value_data_writer = _publisher->lookup_datawriter_by_name("EnumerationMeasObservedValueWriter");
    if (!base_enumeration_meas_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Enumeration Meas Observed Value Data Writer.");
      return DicesRcDriver::ENUMERATION_MEAS_OBSERVED_VALUE_WRITER_LOOKUP_FAILURE;
    }
    _enumeration_meas_observed_value_data_writer = ice::EnumerationObservedValueDataWriter::narrow(base_enumeration_meas_observed_value_data_writer);
    if (!_enumeration_meas_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Enumeration Meas Observed Value Data Writer.");
      return DicesRcDriver::ENUMERATION_MEAS_OBSERVED_VALUE_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::EnumerationCalcContextWriter))
  {
    DDS::DataWriter* base_enumeration_calc_context_data_writer = _publisher->lookup_datawriter_by_name("EnumerationCalcContextWriter");
    if (!base_enumeration_calc_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Enumeration Calc Context Data Writer.");
      return DicesRcDriver::ENUMERATION_CALC_CONTEXT_WRITER_LOOKUP_FAILURE;
    }
    _enumeration_calc_context_data_writer = ice::EnumerationContextDataWriter::narrow(base_enumeration_calc_context_data_writer);
    if (!_enumeration_calc_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Enumeration Calc Context Data Writer.");
      return DicesRcDriver::ENUMERATION_CALC_CONTEXT_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::EnumerationCalcObservedValueWriter))
  {
    DDS::DataWriter* base_enumeration_calc_observed_value_data_writer = _publisher->lookup_datawriter_by_name("EnumerationCalcObservedValueWriter");
    if (!base_enumeration_calc_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Enumeration Calc Observed Value Data Writer.");
      return DicesRcDriver::ENUMERATION_CALC_OBSERVED_VALUE_WRITER_LOOKUP_FAILURE;
    }
    _enumeration_calc_observed_value_data_writer = ice::EnumerationObservedValueDataWriter::narrow(base_enumeration_calc_observed_value_data_writer);
    if (!_enumeration_calc_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Enumeration Calc Observed Value Data Writer.");
      return DicesRcDriver::ENUMERATION_CALC_OBSERVED_VALUE_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::EnumerationSettContextWriter))
  {
    DDS::DataWriter* base_enumeration_sett_context_data_writer = _publisher->lookup_datawriter_by_name("EnumerationSettContextWriter");
    if (!base_enumeration_sett_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Enumeration Sett Context Data Writer.");
      return DicesRcDriver::ENUMERATION_SETT_CONTEXT_WRITER_LOOKUP_FAILURE;
    }
    _enumeration_sett_context_data_writer = ice::EnumerationContextDataWriter::narrow(base_enumeration_sett_context_data_writer);
    if (!_enumeration_sett_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Enumeration Sett Context Data Writer.");
      return DicesRcDriver::ENUMERATION_SETT_CONTEXT_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::EnumerationSettObservedValueWriter))
  {
    DDS::DataWriter* base_enumeration_sett_observed_value_data_writer = _publisher->lookup_datawriter_by_name("EnumerationSettObservedValueWriter");
    if (!base_enumeration_sett_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Enumeration Sett Observed Value Data Writer.");
      return DicesRcDriver::ENUMERATION_SETT_OBSERVED_VALUE_WRITER_LOOKUP_FAILURE;
    }
    _enumeration_sett_observed_value_data_writer = ice::EnumerationObservedValueDataWriter::narrow(base_enumeration_sett_observed_value_data_writer);
    if (!_enumeration_sett_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Enumeration Sett Observed Value Data Writer.");
      return DicesRcDriver::ENUMERATION_SETT_OBSERVED_VALUE_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::MDSWriter))
  {
    DDS::DataWriter* base_mds_data_writer = _publisher->lookup_datawriter_by_name("MDSWriter");
    if (!base_mds_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup MDS Data Writer.");
      return DicesRcDriver::MDS_WRITER_LOOKUP_FAILURE;
    }
    _mds_data_writer = ice::MDSDataWriter::narrow(base_mds_data_writer);
    if (!_mds_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow MDS Data Writer.");
      return DicesRcDriver::MDS_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::VMDWriter))
  {
    DDS::DataWriter* base_vmd_data_writer = _publisher->lookup_datawriter_by_name("VMDWriter");
    if (!base_vmd_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup VMD Data Writer.");
      return DicesRcDriver::VMD_WRITER_LOOKUP_FAILURE;
    }
    _vmd_data_writer = ice::VMDDataWriter::narrow(base_vmd_data_writer);
    if (!_vmd_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow VMD Data Writer.");
      return DicesRcDriver::VMD_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::NumericMeasContextWriter))
  {
    DDS::DataWriter* base_numeric_meas_context_data_writer = _publisher->lookup_datawriter_by_name("NumericMeasContextWriter");
    if (!base_numeric_meas_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Numeric Meas Context Data Writer.");
      return DicesRcDriver::NUMERIC_MEAS_CONTEXT_WRITER_LOOKUP_FAILURE;
    }
    _numeric_meas_context_data_writer = ice::NumericContextDataWriter::narrow(base_numeric_meas_context_data_writer);
    if (!_numeric_meas_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Numeric Meas Context Data Writer.");
      return DicesRcDriver::NUMERIC_MEAS_CONTEXT_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::NumericMeasObservedValueWriter))
  {
    DDS::DataWriter* base_numeric_meas_observed_value_data_writer = _publisher->lookup_datawriter_by_name("NumericMeasObservedValueWriter");
    if (!base_numeric_meas_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Numeric Meas Observed Value Data Writer.");
      return DicesRcDriver::NUMERIC_MEAS_OBSERVED_VALUE_WRITER_LOOKUP_FAILURE;
    }
    _numeric_meas_observed_value_data_writer = ice::NumericObservedValueDataWriter::narrow(base_numeric_meas_observed_value_data_writer);
    if (!_numeric_meas_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Numeric Meas Observed Value Data Writer.");
      return DicesRcDriver::NUMERIC_MEAS_OBSERVED_VALUE_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::NumericCalcContextWriter))
  {
    DDS::DataWriter* base_numeric_calc_context_data_writer = _publisher->lookup_datawriter_by_name("NumericCalcContextWriter");
    if (!base_numeric_calc_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Numeric Calc Context Data Writer.");
      return DicesRcDriver::NUMERIC_CALC_CONTEXT_WRITER_LOOKUP_FAILURE;
    }
    _numeric_calc_context_data_writer = ice::NumericContextDataWriter::narrow(base_numeric_calc_context_data_writer);
    if (!_numeric_calc_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Numeric Calc Context Data Writer.");
      return DicesRcDriver::NUMERIC_CALC_CONTEXT_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::NumericCalcObservedValueWriter))
  {
    DDS::DataWriter* base_numeric_calc_observed_value_data_writer = _publisher->lookup_datawriter_by_name("NumericCalcObservedValueWriter");
    if (!base_numeric_calc_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Numeric Calc Observed Value Data Writer.");
      return DicesRcDriver::NUMERIC_CALC_OBSERVED_VALUE_WRITER_LOOKUP_FAILURE;
    }
    _numeric_calc_observed_value_data_writer = ice::NumericObservedValueDataWriter::narrow(base_numeric_calc_observed_value_data_writer);
    if (!_numeric_calc_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Numeric Calc Observed Value Data Writer.");
      return DicesRcDriver::NUMERIC_CALC_OBSERVED_VALUE_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::NumericSettContextWriter))
  {
    DDS::DataWriter* base_numeric_sett_context_data_writer = _publisher->lookup_datawriter_by_name("NumericSettContextWriter");
    if (!base_numeric_sett_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Numeric Sett Context Data Writer.");
      return DicesRcDriver::NUMERIC_SETT_CONTEXT_WRITER_LOOKUP_FAILURE;
    }
    _numeric_sett_context_data_writer = ice::NumericContextDataWriter::narrow(base_numeric_sett_context_data_writer);
    if (!_numeric_sett_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Numeric Sett Context Data Writer.");
      return DicesRcDriver::NUMERIC_SETT_CONTEXT_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::NumericSettObservedValueWriter))
  {
    DDS::DataWriter* base_numeric_sett_observed_value_data_writer = _publisher->lookup_datawriter_by_name("NumericSettObservedValueWriter");
    if (!base_numeric_sett_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Numeric Sett Observed Value Data Writer.");
      return DicesRcDriver::NUMERIC_SETT_OBSERVED_VALUE_WRITER_LOOKUP_FAILURE;
    }
    _numeric_sett_observed_value_data_writer = ice::NumericObservedValueDataWriter::narrow(base_numeric_sett_observed_value_data_writer);
    if (!_numeric_sett_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Numeric Sett Observed Value Data Writer.");
      return DicesRcDriver::NUMERIC_SETT_OBSERVED_VALUE_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::RTSAMeasContextWriter))
  {
    DDS::DataWriter* base_rtsa_meas_context_data_writer = _publisher->lookup_datawriter_by_name("RTSAMeasContextWriter");
    if (!base_rtsa_meas_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup RTSA Meas Context Data Writer.");
      return DicesRcDriver::RTSA_MEAS_CONTEXT_WRITER_LOOKUP_FAILURE;
    }
    _rtsa_meas_context_data_writer = ice::RTSAContextDataWriter::narrow(base_rtsa_meas_context_data_writer);
    if (!_rtsa_meas_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow RTSA Meas Context Data Writer.");
      return DicesRcDriver::RTSA_MEAS_CONTEXT_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::RTSAMeasObservedValueWriter))
  {
    DDS::DataWriter* base_rtsa_meas_observed_value_data_writer = _publisher->lookup_datawriter_by_name("RTSAMeasObservedValueWriter");
    if (!base_rtsa_meas_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup RTSA Meas Observed Value Data Writer.");
      return DicesRcDriver::RTSA_MEAS_OBSERVED_VALUE_WRITER_LOOKUP_FAILURE;
    }
    _rtsa_meas_observed_value_data_writer = ice::RTSAObservedValueDataWriter::narrow(base_rtsa_meas_observed_value_data_writer);
    if (!_rtsa_meas_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow RTSA Meas Observed Value Data Writer.");
      return DicesRcDriver::RTSA_MEAS_OBSERVED_VALUE_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::RTSACalcContextWriter))
  {
    DDS::DataWriter* base_rtsa_calc_context_data_writer = _publisher->lookup_datawriter_by_name("RTSACalcContextWriter");
    if (!base_rtsa_calc_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup RTSA Calc Context Data Writer.");
      return DicesRcDriver::RTSA_CALC_CONTEXT_WRITER_LOOKUP_FAILURE;
    }
    _rtsa_calc_context_data_writer = ice::RTSAContextDataWriter::narrow(base_rtsa_calc_context_data_writer);
    if (!_rtsa_calc_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow RTSA Calc Context Data Writer.");
      return DicesRcDriver::RTSA_CALC_CONTEXT_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::RTSACalcObservedValueWriter))
  {
    DDS::DataWriter* base_rtsa_calc_observed_value_data_writer = _publisher->lookup_datawriter_by_name("RTSACalcObservedValueWriter");
    if (!base_rtsa_calc_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup RTSA Calc Observed Value Data Writer.");
      return DicesRcDriver::RTSA_CALC_OBSERVED_VALUE_WRITER_LOOKUP_FAILURE;
    }
    _rtsa_calc_observed_value_data_writer = ice::RTSAObservedValueDataWriter::narrow(base_rtsa_calc_observed_value_data_writer);
    if (!_rtsa_calc_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow RTSA Calc Observed Value Data Writer.");
      return DicesRcDriver::RTSA_CALC_OBSERVED_VALUE_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::RTSASettContextWriter))
  {
    DDS::DataWriter* base_rtsa_sett_context_data_writer = _publisher->lookup_datawriter_by_name("RTSASettContextWriter");
    if (!base_rtsa_sett_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup RTSA Sett Context Data Writer.");
      return DicesRcDriver::RTSA_SETT_CONTEXT_WRITER_LOOKUP_FAILURE;
    }
    _rtsa_sett_context_data_writer = ice::RTSAContextDataWriter::narrow(base_rtsa_sett_context_data_writer);
    if (!_rtsa_sett_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow RTSA Sett Context Data Writer.");
      return DicesRcDriver::RTSA_SETT_CONTEXT_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::RTSASettObservedValueWriter))
  {
    DDS::DataWriter* base_rtsa_sett_observed_value_data_writer = _publisher->lookup_datawriter_by_name("RTSASettObservedValueWriter");
    if (!base_rtsa_sett_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup RTSA Sett Observed Value Data Writer.");
      return DicesRcDriver::RTSA_SETT_OBSERVED_VALUE_WRITER_LOOKUP_FAILURE;
    }
    _rtsa_sett_observed_value_data_writer = ice::RTSAObservedValueDataWriter::narrow(base_rtsa_sett_observed_value_data_writer);
    if (!_rtsa_sett_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow RTSA Sett Observed Value Data Writer.");
      return DicesRcDriver::RTSA_SETT_OBSERVED_VALUE_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::TSAMeasContextWriter))
  {
    DDS::DataWriter* base_tsa_meas_context_data_writer = _publisher->lookup_datawriter_by_name("TSAMeasContextWriter");
    if (!base_tsa_meas_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup TSA Meas Context Data Writer.");
      return DicesRcDriver::TSA_MEAS_CONTEXT_WRITER_LOOKUP_FAILURE;
    }
    _tsa_meas_context_data_writer = ice::TSAContextDataWriter::narrow(base_tsa_meas_context_data_writer);
    if (!_tsa_meas_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow TSA Meas Context Data Writer.");
      return DicesRcDriver::TSA_MEAS_CONTEXT_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::TSAMeasObservedValueWriter))
  {
    DDS::DataWriter* base_tsa_meas_observed_value_data_writer = _publisher->lookup_datawriter_by_name("TSAMeasObservedValueWriter");
    if (!base_tsa_meas_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup TSA Meas Observed Value Data Writer.");
      return DicesRcDriver::TSA_MEAS_OBSERVED_VALUE_WRITER_LOOKUP_FAILURE;
    }
    _tsa_meas_observed_value_data_writer = ice::TSAObservedValueDataWriter::narrow(base_tsa_meas_observed_value_data_writer);
    if (!_tsa_meas_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow TSA Meas Observed Value Data Writer.");
      return DicesRcDriver::TSA_MEAS_OBSERVED_VALUE_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::TSACalcContextWriter))
  {
    DDS::DataWriter* base_tsa_calc_context_data_writer = _publisher->lookup_datawriter_by_name("TSACalcContextWriter");
    if (!base_tsa_calc_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup TSA Calc Context Data Writer.");
      return DicesRcDriver::TSA_CALC_CONTEXT_WRITER_LOOKUP_FAILURE;
    }
    _tsa_calc_context_data_writer = ice::TSAContextDataWriter::narrow(base_tsa_calc_context_data_writer);
    if (!_tsa_calc_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow TSA Calc Context Data Writer.");
      return DicesRcDriver::TSA_CALC_CONTEXT_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::TSACalcObservedValueWriter))
  {
    DDS::DataWriter* base_tsa_calc_observed_value_data_writer = _publisher->lookup_datawriter_by_name("TSACalcObservedValueWriter");
    if (!base_tsa_calc_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup TSA Calc Observed Value Data Writer.");
      return DicesRcDriver::TSA_CALC_OBSERVED_VALUE_WRITER_LOOKUP_FAILURE;
    }
    _tsa_calc_observed_value_data_writer = ice::TSAObservedValueDataWriter::narrow(base_tsa_calc_observed_value_data_writer);
    if (!_tsa_calc_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow TSA Calc Observed Value Data Writer.");
      return DicesRcDriver::TSA_CALC_OBSERVED_VALUE_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::TSASettContextWriter))
  {
    DDS::DataWriter* base_tsa_sett_context_data_writer = _publisher->lookup_datawriter_by_name("TSASettContextWriter");
    if (!base_tsa_sett_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup TSA Sett Context Data Writer.");
      return DicesRcDriver::TSA_SETT_CONTEXT_WRITER_LOOKUP_FAILURE;
    }
    _tsa_sett_context_data_writer = ice::TSAContextDataWriter::narrow(base_tsa_sett_context_data_writer);
    if (!_tsa_sett_context_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow TSA Sett Context Data Writer.");
      return DicesRcDriver::TSA_SETT_CONTEXT_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::TSASettObservedValueWriter))
  {
    DDS::DataWriter* base_tsa_sett_observed_value_data_writer = _publisher->lookup_datawriter_by_name("TSASettObservedValueWriter");
    if (!base_tsa_sett_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup TSA Sett Observed Value Data Writer.");
      return DicesRcDriver::TSA_SETT_OBSERVED_VALUE_WRITER_LOOKUP_FAILURE;
    }
    _tsa_sett_observed_value_data_writer = ice::TSAObservedValueDataWriter::narrow(base_tsa_sett_observed_value_data_writer);
    if (!_tsa_sett_observed_value_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow TSA Sett Observed Value Data Writer.");
      return DicesRcDriver::TSA_SETT_OBSERVED_VALUE_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::PatientIdentificationWriter))
  {
    DDS::DataWriter* base_patient_identification_data_writer = _publisher->lookup_datawriter_by_name("PatientIdentificationWriter");
    if (!base_patient_identification_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Patient Identification Data Writer.");
      return DicesRcDriver::PATIENT_IDENTIFICATION_WRITER_LOOKUP_FAILURE;
    }
    _patient_identification_data_writer = ice::PatientIdentificationDataWriter::narrow(base_patient_identification_data_writer);
    if (!_patient_identification_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Patient Identification Data Writer.");
      return DicesRcDriver::PATIENT_IDENTIFICATION_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::PatientDemographicsWriter))
  {
    DDS::DataWriter* base_patient_demographics_data_writer = _publisher->lookup_datawriter_by_name("PatientDemographicsWriter");
    if (!base_patient_demographics_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Patient Demographics Data Writer.");
      return DicesRcDriver::PATIENT_DEMOGRAPHICS_WRITER_LOOKUP_FAILURE;
    }
    _patient_demographics_data_writer = ice::PatientDemographicsDataWriter::narrow(base_patient_demographics_data_writer);
    if (!_patient_demographics_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Patient Demographics Data Writer.");
      return DicesRcDriver::PATIENT_DEMOGRAPHICS_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::AllergyWriter))
  {
    DDS::DataWriter* base_allergy_data_writer = _publisher->lookup_datawriter_by_name("AllergyWriter");
    if (!base_allergy_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Allergy Data Writer.");
      return DicesRcDriver::ALLERGY_WRITER_LOOKUP_FAILURE;
    }
    _allergy_data_writer = ice::AllergyDataWriter::narrow(base_allergy_data_writer);
    if (!_allergy_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Allergy Data Writer.");
      return DicesRcDriver::ALLERGY_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::DiagnosisWriter))
  {
    DDS::DataWriter* base_diagnosis_data_writer = _publisher->lookup_datawriter_by_name("DiagnosisWriter");
    if (!base_diagnosis_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Diagnosis Data Writer.");
      return DicesRcDriver::DIAGNOSIS_WRITER_LOOKUP_FAILURE;
    }
    _diagnosis_data_writer = expr::DiagnosisDataWriter::narrow(base_diagnosis_data_writer);
    if (!_diagnosis_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Diagnosis Data Writer.");
      return DicesRcDriver::DIAGNOSIS_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::DxHistoryWriter))
  {
    DDS::DataWriter* base_dxhistory_data_writer = _publisher->lookup_datawriter_by_name("DxHistoryWriter");
    if (!base_dxhistory_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup DxHistory Data Writer.");
      return DicesRcDriver::DXHISTORY_WRITER_LOOKUP_FAILURE;
    }
    _dxhistory_data_writer = expr::DxHistoryDataWriter::narrow(base_dxhistory_data_writer);
    if (!_dxhistory_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow DxHistory Data Writer.");
      return DicesRcDriver::DXHISTORY_WRITER_NARROW_FAILURE;
    }
  }
  if (create_writer_name_list.count(CreateWriterName::PatientMedicationWriter))
  {
    DDS::DataWriter* base_patient_medication_data_writer = _publisher->lookup_datawriter_by_name("PatientMedicationWriter");
    if (!base_patient_medication_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup PatientMedication Data Writer.");
      return DicesRcDriver::PATIENT_MEDICATION_WRITER_LOOKUP_FAILURE;
    }
    _patient_medication_data_writer = expr::PatientMedicationDataWriter::narrow(base_patient_medication_data_writer);
    if (!_patient_medication_data_writer)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow PatientMedication Data Writer.");
      return DicesRcDriver::PATIENT_MEDICATION_WRITER_NARROW_FAILURE;
    }
  }

  std::set<CreateReaderName> create_reader_name_list = _parser->
    get_create_reader_name_list();
  if (create_reader_name_list.count(CreateReaderName::PatientDemographicsReqReaderCft))
  {
    // Initialize data readers
    DDS::DataReader* base_patient_demographics_req_data_reader = _subscriber->lookup_datareader_by_name("PatientDemographicsReqReaderCft");
    if (!base_patient_demographics_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Patient Demographics Request Data Reader.");
      return DicesRcDriver::PATIENT_DEMOGRAPHICS_READER_LOOKUP_FAILURE;
    }
    _patient_demographics_req_data_reader = ice::PatientDemographicsDataReader::narrow(base_patient_demographics_req_data_reader);
    if (!_patient_demographics_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Patient Demographics Request Data Reader.");
      return DicesRcDriver::PATIENT_DEMOGRAPHICS_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::PhysiologicalAlarmContextReqReaderCft))
  {
    DDS::DataReader* base_physiological_alarm_context_req_data_reader = _subscriber->lookup_datareader_by_name("PhysiologicalAlarmContextReqReaderCft");
    if (!base_physiological_alarm_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Physiological Alarm Context Request Data Reader.");
      return DicesRcDriver::PHYSIOLOGICAL_ALARM_CONTEXT_REQUEST_READER_LOOKUP_FAILURE;
    }
    _physiological_alarm_context_req_data_reader = ice::AlarmContextDataReader::narrow(base_physiological_alarm_context_req_data_reader);
    if (!_physiological_alarm_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Physiological Alarm Context Request Data Reader.");
      return DicesRcDriver::PHYSIOLOGICAL_ALARM_CONTEXT_REQUEST_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::TechnicalAlarmContextReqReaderCft))
  {
    DDS::DataReader* base_technical_alarm_context_req_data_reader = _subscriber->lookup_datareader_by_name("TechnicalAlarmContextReqReaderCft");
    if (!base_technical_alarm_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Technical Alarm Context Request Data Reader.");
      return DicesRcDriver::TECHNICAL_ALARM_CONTEXT_REQUEST_READER_LOOKUP_FAILURE;
    }
    _technical_alarm_context_req_data_reader = ice::AlarmContextDataReader::narrow(base_technical_alarm_context_req_data_reader);
    if (!_technical_alarm_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Technical Alarm Context Request Data Reader.");
      return DicesRcDriver::TECHNICAL_ALARM_CONTEXT_REQUEST_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::DSAMeasContextReqReaderCft))
  {
    DDS::DataReader* base_dsa_meas_context_req_data_reader = _subscriber->lookup_datareader_by_name("DSAMeasContextReqReaderCft");
    if (!base_dsa_meas_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup DSA Meas Context Request Data Reader.");
      return DicesRcDriver::DSA_MEAS_CONTEXT_REQUEST_READER_LOOKUP_FAILURE;
    }
    _dsa_meas_context_req_data_reader = ice::DSAContextDataReader::narrow(base_dsa_meas_context_req_data_reader);
    if (!_dsa_meas_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow DSA Meas Context Request Data Reader.");
      return DicesRcDriver::DSA_MEAS_CONTEXT_REQUEST_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::DSACalcContextReqReaderCft))
  {
    DDS::DataReader* base_dsa_calc_context_req_data_reader = _subscriber->lookup_datareader_by_name("DSACalcContextReqReaderCft");
    if (!base_dsa_calc_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup DSA Calc Context Request Data Reader.");
      return DicesRcDriver::DSA_CALC_CONTEXT_REQUEST_READER_LOOKUP_FAILURE;
    }
    _dsa_calc_context_req_data_reader = ice::DSAContextDataReader::narrow(base_dsa_calc_context_req_data_reader);
    if (!_dsa_calc_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow DSA Calc Context Request Data Reader.");
      return DicesRcDriver::DSA_CALC_CONTEXT_REQUEST_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::DSASettContextReqReaderCft))
  {
    DDS::DataReader* base_dsa_sett_context_req_data_reader = _subscriber->lookup_datareader_by_name("DSASettContextReqReaderCft");
    if (!base_dsa_sett_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup DSA Sett Context Request Data Reader.");
      return DicesRcDriver::DSA_SETT_CONTEXT_REQUEST_READER_LOOKUP_FAILURE;
    }
    _dsa_sett_context_req_data_reader = ice::DSAContextDataReader::narrow(base_dsa_sett_context_req_data_reader);
    if (!_dsa_sett_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow DSA Sett Context Request Data Reader.");
      return DicesRcDriver::DSA_SETT_CONTEXT_REQUEST_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::EnumerationMeasContextReqReaderCft))
  {
    DDS::DataReader* base_enumeration_meas_context_req_data_reader = _subscriber->lookup_datareader_by_name("EnumerationMeasContextReqReaderCft");
    if (!base_enumeration_meas_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Enumeration Meas Context Request Data Reader.");
      return DicesRcDriver::ENUMERATION_MEAS_CONTEXT_REQUEST_READER_LOOKUP_FAILURE;
    }
    _enumeration_meas_context_req_data_reader = ice::EnumerationContextDataReader::narrow(base_enumeration_meas_context_req_data_reader);
    if (!_enumeration_meas_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Enumeration Meas Context Request Data Reader.");
      return DicesRcDriver::ENUMERATION_MEAS_CONTEXT_REQUEST_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::EnumerationCalcContextReqReaderCft))
  {
    DDS::DataReader* base_enumeration_calc_context_req_data_reader = _subscriber->lookup_datareader_by_name("EnumerationCalcContextReqReaderCft");
    if (!base_enumeration_calc_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Enumeration Calc Context Request Data Reader.");
      return DicesRcDriver::ENUMERATION_CALC_CONTEXT_REQUEST_READER_LOOKUP_FAILURE;
    }
    _enumeration_calc_context_req_data_reader = ice::EnumerationContextDataReader::narrow(base_enumeration_calc_context_req_data_reader);
    if (!_enumeration_calc_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Enumeration Calc Context Request Data Reader.");
      return DicesRcDriver::ENUMERATION_CALC_CONTEXT_REQUEST_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::EnumerationSettContextReqReaderCft))
  {
    DDS::DataReader* base_enumeration_sett_context_req_data_reader = _subscriber->lookup_datareader_by_name("EnumerationSettContextReqReaderCft");
    if (!base_enumeration_sett_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Enumeration Sett Context Request Data Reader.");
      return DicesRcDriver::ENUMERATION_SETT_CONTEXT_REQUEST_READER_LOOKUP_FAILURE;
    }
    _enumeration_sett_context_req_data_reader = ice::EnumerationContextDataReader::narrow(base_enumeration_sett_context_req_data_reader);
    if (!_enumeration_sett_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Enumeration Sett Context Request Data Reader.");
      return DicesRcDriver::ENUMERATION_SETT_CONTEXT_REQUEST_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::EnumerationSettObservedValueReqReaderCft))
  {
    DDS::DataReader* base_enumeration_sett_observed_value_req_data_reader = _subscriber->lookup_datareader_by_name("EnumerationSettObservedValueReqReaderCft");
    if (!base_enumeration_sett_observed_value_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Enumeration Sett Observed Value Request Data Reader.");
      return DicesRcDriver::ENUMERATION_SETT_OBSERVED_VALUE_REQUEST_READER_LOOKUP_FAILURE;
    }
    _enumeration_sett_observed_value_req_data_reader = ice::EnumerationObservedValueDataReader::narrow(base_enumeration_sett_observed_value_req_data_reader);
    if (!_enumeration_sett_observed_value_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Enumeration Sett Observed Value Request Data Reader.");
      return DicesRcDriver::ENUMERATION_SETT_OBSERVED_VALUE_REQUEST_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::NumericMeasContextReqReaderCft))
  {
    DDS::DataReader* base_numeric_meas_context_req_data_reader = _subscriber->lookup_datareader_by_name("NumericMeasContextReqReaderCft");
    if (!base_numeric_meas_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Numeric Meas Context Request Data Reader.");
      return DicesRcDriver::NUMERIC_MEAS_CONTEXT_REQUEST_READER_LOOKUP_FAILURE;
    }
    _numeric_meas_context_req_data_reader = ice::NumericContextDataReader::narrow(base_numeric_meas_context_req_data_reader);
    if (!_numeric_meas_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Numeric Meas Context Request Data Reader.");
      return DicesRcDriver::NUMERIC_MEAS_CONTEXT_REQUEST_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::NumericCalcContextReqReaderCft))
  {
    DDS::DataReader* base_numeric_calc_context_req_data_reader = _subscriber->lookup_datareader_by_name("NumericCalcContextReqReaderCft");
    if (!base_numeric_calc_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Numeric Calc Context Request Data Reader.");
      return DicesRcDriver::NUMERIC_CALC_CONTEXT_REQUEST_READER_LOOKUP_FAILURE;
    }
    _numeric_calc_context_req_data_reader = ice::NumericContextDataReader::narrow(base_numeric_calc_context_req_data_reader);
    if (!_numeric_calc_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Numeric Calc Context Request Data Reader.");
      return DicesRcDriver::NUMERIC_CALC_CONTEXT_REQUEST_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::NumericSettContextReqReaderCft))
  {
    DDS::DataReader* base_numeric_sett_context_req_data_reader = _subscriber->lookup_datareader_by_name("NumericSettContextReqReaderCft");
    if (!base_numeric_sett_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Numeric Sett Context Request Data Reader.");
      return DicesRcDriver::NUMERIC_SETT_CONTEXT_REQUEST_READER_LOOKUP_FAILURE;
    }
    _numeric_sett_context_req_data_reader = ice::NumericContextDataReader::narrow(base_numeric_sett_context_req_data_reader);
    if (!_numeric_sett_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Numeric Sett Context Request Data Reader.");
      return DicesRcDriver::NUMERIC_SETT_CONTEXT_REQUEST_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::NumericSettObservedValueReqReaderCft))
  {
    DDS::DataReader* base_numeric_sett_observed_value_req_data_reader = _subscriber->lookup_datareader_by_name("NumericSettObservedValueReqReaderCft");
    if (!base_numeric_sett_observed_value_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Numeric Sett Observed Value Request Data Reader.");
      return DicesRcDriver::NUMERIC_SETT_OBSERVED_VALUE_REQUEST_READER_LOOKUP_FAILURE;
    }
    _numeric_sett_observed_value_req_data_reader = ice::NumericObservedValueDataReader::narrow(base_numeric_sett_observed_value_req_data_reader);
    if (!_numeric_sett_observed_value_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Numeric Sett Observed Value Request Data Reader.");
      return DicesRcDriver::NUMERIC_SETT_OBSERVED_VALUE_REQUEST_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::RTSAMeasContextReqReaderCft))
  {
    DDS::DataReader* base_rtsa_meas_context_req_data_reader = _subscriber->lookup_datareader_by_name("RTSAMeasContextReqReaderCft");
    if (!base_rtsa_meas_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup RTSA Meas Context Request Data Reader.");
      return DicesRcDriver::RTSA_MEAS_CONTEXT_REQUEST_READER_LOOKUP_FAILURE;
    }
    _rtsa_meas_context_req_data_reader = ice::RTSAContextDataReader::narrow(base_rtsa_meas_context_req_data_reader);
    if (!_rtsa_meas_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow RTSA Meas Context Request Data Reader.");
      return DicesRcDriver::RTSA_MEAS_CONTEXT_REQUEST_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::RTSACalcContextReqReaderCft))
  {
    DDS::DataReader* base_rtsa_calc_context_req_data_reader = _subscriber->lookup_datareader_by_name("RTSACalcContextReqReaderCft");
    if (!base_rtsa_calc_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup RTSA Calc Context Request Data Reader.");
      return DicesRcDriver::RTSA_CALC_CONTEXT_REQUEST_READER_LOOKUP_FAILURE;
    }
    _rtsa_calc_context_req_data_reader = ice::RTSAContextDataReader::narrow(base_rtsa_calc_context_req_data_reader);
    if (!_rtsa_calc_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow RTSA Calc Context Request Data Reader.");
      return DicesRcDriver::RTSA_CALC_CONTEXT_REQUEST_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::RTSASettContextReqReaderCft))
  {
    DDS::DataReader* base_rtsa_sett_context_req_data_reader = _subscriber->lookup_datareader_by_name("RTSASettContextReqReaderCft");
    if (!base_rtsa_sett_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup RTSA Sett Context Request Data Reader.");
      return DicesRcDriver::RTSA_SETT_CONTEXT_REQUEST_READER_LOOKUP_FAILURE;
    }
    _rtsa_sett_context_req_data_reader = ice::RTSAContextDataReader::narrow(base_rtsa_sett_context_req_data_reader);
    if (!_rtsa_sett_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow RTSA Sett Context Request Data Reader.");
      return DicesRcDriver::RTSA_SETT_CONTEXT_REQUEST_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::TSAMeasContextReqReaderCft))
  {
    DDS::DataReader* base_tsa_meas_context_req_data_reader = _subscriber->lookup_datareader_by_name("TSAMeasContextReqReaderCft");
    if (!base_tsa_meas_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup TSA Meas Context Request Data Reader.");
      return DicesRcDriver::TSA_MEAS_CONTEXT_REQUEST_READER_LOOKUP_FAILURE;
    }
    _tsa_meas_context_req_data_reader = ice::TSAContextDataReader::narrow(base_tsa_meas_context_req_data_reader);
    if (!_tsa_meas_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow TSA Meas Context Request Data Reader.");
      return DicesRcDriver::TSA_MEAS_CONTEXT_REQUEST_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::TSACalcContextReqReaderCft))
  {
    DDS::DataReader* base_tsa_calc_context_req_data_reader = _subscriber->lookup_datareader_by_name("TSACalcContextReqReaderCft");
    if (!base_tsa_calc_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup TSA Calc Context Request Data Reader.");
      return DicesRcDriver::TSA_CALC_CONTEXT_REQUEST_READER_LOOKUP_FAILURE;
    }
    _tsa_calc_context_req_data_reader = ice::TSAContextDataReader::narrow(base_tsa_calc_context_req_data_reader);
    if (!_tsa_calc_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow TSA Calc Context Request Data Reader.");
      return DicesRcDriver::TSA_CALC_CONTEXT_REQUEST_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::TSASettContextReqReaderCft))
  {
    DDS::DataReader* base_tsa_sett_context_req_data_reader = _subscriber->lookup_datareader_by_name("TSASettContextReqReaderCft");
    if (!base_tsa_sett_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup TSA Sett Context Request Data Reader.");
      return DicesRcDriver::TSA_SETT_CONTEXT_REQUEST_READER_LOOKUP_FAILURE;
    }
    _tsa_sett_context_req_data_reader = ice::TSAContextDataReader::narrow(base_tsa_sett_context_req_data_reader);
    if (!_tsa_sett_context_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow TSA Sett Context Request Data Reader.");
      return DicesRcDriver::TSA_SETT_CONTEXT_REQUEST_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::PatientIdentificationReqReader))
  {
    DDS::DataReader* base_patient_identification_req_data_reader = _subscriber->lookup_datareader_by_name("PatientIdentificationReqReader");
    if (!base_patient_identification_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Patient Identification Request Data Reader.");
      return DicesRcDriver::PATIENT_IDENTIFICATION_REQUEST_READER_LOOKUP_FAILURE;
    }
    _patient_identification_req_data_reader = ice::PatientIdentificationDataReader::narrow(base_patient_identification_req_data_reader);
    if (!_patient_identification_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Patient Identification Request Data Reader.");
      return DicesRcDriver::PATIENT_IDENTIFICATION_REQUEST_READER_NARROW_FAILURE;
    }
  }
  if (create_reader_name_list.count(CreateReaderName::DeviceDriverStateReqReaderCft))
  {
    DDS::DataReader* base_device_driver_state_req_data_reader = _subscriber->lookup_datareader_by_name("DeviceDriverStateReqReaderCft");
    if (!base_device_driver_state_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Device Driver State Request Data Reader.");
      return DicesRcDriver::DEVICE_DRIVER_STATE_REQUEST_READER_LOOKUP_FAILURE;
    }
    _device_driver_state_req_data_reader = docbox::DeviceDriverStateDataReader::narrow(base_device_driver_state_req_data_reader);
    if (!_device_driver_state_req_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Device Driver State Request Data Reader.");
      return DicesRcDriver::DEVICE_DRIVER_STATE_REQUEST_READER_NARROW_FAILURE;
    }
  }

  if (create_reader_name_list.count(CreateReaderName::AllergyReader))
  {
    DDS::DataReader* base_allergy_data_reader = _subscriber->lookup_datareader_by_name("AllergyReader");
    if (!base_allergy_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Allergy Data Reader.");
      return DicesRcDriver::ALLERGY_READER_LOOKUP_FAILURE;
    }
    _allergy_data_reader = ice::AllergyDataReader::narrow(base_allergy_data_reader);
    if (!_allergy_data_reader)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Allergy Data Reader.");
      return DicesRcDriver::ALLERGY_READER_NARROW_FAILURE;
    }
  }

  return DicesRcDriver::OK;
}

DicesRcDriver BusComm::Associate()
{
  DicesRcDriver dr_retcode = _parser->SetICEID();
  if (dr_retcode != DicesRcDriver::OK)
  {
    LOG4CPLUS_ERROR(root_logger, " Failed to set ICE ID: "
      << DicesRcDriverStatusMessage::DicesRcDriverToString(dr_retcode));
    return DicesRcDriver::SET_ICE_ID_FAILURE;
  }

  std::set<CreateWriterName> create_writer_name_list = _parser->
    get_create_writer_name_list();

  if (create_writer_name_list.count(CreateWriterName::DeviceDriverStateWriter))
  {
    DicesRcDriverStatus ds_retcode = _driver_status_handler.Operating();
    if (ds_retcode != DicesRcDriverStatus::OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set Driver Status to Operating: "
        << DicesRcDriverStatusStatusMessage::DicesRcDriverStatusToString(ds_retcode));
      return DicesRcDriver::DRIVER_STATUS_OPERATING_FAILURE;
    }
  }
  return SetContentFilters();
}

DicesRcDriver BusComm::SetContentFilters()
{
  DDS::ReturnCode_t retcode = DDS::RETCODE_OK;

  std::string ice_id_str = _parser->get_ice_id();
  ice_id_str.insert(0, "'");
  ice_id_str.append("'");
  // Filter params for Alarm Context, Enum Requests, Numeric Requests
  const char* four_param_list[] = { ice_id_str.c_str(), "0", "0", "0" };
  DDS::StringSeq expression_parameters_four;
  expression_parameters_four.from_array(four_param_list, 4);
  // Filter params for DSA, RTSA, TSA Requests
  const char* three_param_list[] = { ice_id_str.c_str(), "0", "0" };
  DDS::StringSeq expression_parameters_three;
  expression_parameters_three.from_array(three_param_list, 3);
  // Filter params for Driver State Requests
  const char* one_param_list[] = { ice_id_str.c_str() };
  DDS::StringSeq expression_parameters_one;
  expression_parameters_one.from_array(one_param_list, 1);

  if (!_physiological_alarm_context_req_data_reader)
  {
    LOG4CPLUS_INFO(root_logger, " Physiological Alarm Context Request Reader is a null pointer");
  }
  else
  {
    DDS::TopicDescription* base_physiological_alarm_context_req_topic = _physiological_alarm_context_req_data_reader->get_topicdescription();
    if (!base_physiological_alarm_context_req_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Physiological Alarm Context Request Topic.");
      return DicesRcDriver::PHYSIOLOGICAL_ALARM_CONTEXT_REQUEST_TOPIC_LOOKUP_FAILURE;
    }
    DDS::ContentFilteredTopic *physiological_alarm_context_req_cft_topic = DDS::ContentFilteredTopic::narrow(base_physiological_alarm_context_req_topic);
    if (!physiological_alarm_context_req_cft_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Physiological Alarm Context Request Topic.");
      return DicesRcDriver::PHYSIOLOGICAL_ALARM_CONTEXT_REQUEST_TOPIC_NARROW_FAILURE;
    }
    retcode = physiological_alarm_context_req_cft_topic->set_expression_parameters(expression_parameters_four);
    if (retcode != DDS_RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set expression parameters for Physiological Alarm Context Request Content Filter.");
      return DicesRcDriver::PHYSIOLOGICAL_ALARM_CONTEXT_REQUEST_TOPIC_FILTER_FAILURE;
    }
  }

  if (!_technical_alarm_context_req_data_reader)
  {
    LOG4CPLUS_INFO(root_logger, " Technical Alarm Context Request Reader is a null pointer");
  }
  else
  {
    DDS::TopicDescription* base_technical_alarm_context_req_topic = _technical_alarm_context_req_data_reader->get_topicdescription();
    if (!base_technical_alarm_context_req_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Technical Alarm Context Request Topic.");
      return DicesRcDriver::TECHNICAL_ALARM_CONTEXT_REQUEST_TOPIC_LOOKUP_FAILURE;
    }
    DDS::ContentFilteredTopic *technical_alarm_context_req_cft_topic = DDS::ContentFilteredTopic::narrow(base_technical_alarm_context_req_topic);
    if (!technical_alarm_context_req_cft_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Technical Alarm Context Request Topic.");
      return DicesRcDriver::TECHNICAL_ALARM_CONTEXT_REQUEST_TOPIC_NARROW_FAILURE;
    }
    retcode = technical_alarm_context_req_cft_topic->set_expression_parameters(expression_parameters_four);
    if (retcode != DDS_RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set expression parameters for Technical Alarm Context Request Content Filter.");
      return DicesRcDriver::TECHNICAL_ALARM_CONTEXT_REQUEST_TOPIC_FILTER_FAILURE;
    }
  }

  if (!_dsa_meas_context_req_data_reader)
  {
    LOG4CPLUS_INFO(root_logger, "  DSA Meas Context Request Reader is a null pointer");
  }
  else
  {
    DDS::TopicDescription* base_dsa_meas_context_req_topic = _dsa_meas_context_req_data_reader->get_topicdescription();
    if (!base_dsa_meas_context_req_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup DSA Meas Context Request Topic.");
      return DicesRcDriver::DSA_MEAS_CONTEXT_REQUEST_TOPIC_LOOKUP_FAILURE;
    }
    DDS::ContentFilteredTopic *dsa_meas_context_req_cft_topic = DDS::ContentFilteredTopic::narrow(base_dsa_meas_context_req_topic);
    if (!dsa_meas_context_req_cft_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow DSA Meas Context Request Topic.");
      return DicesRcDriver::DSA_MEAS_CONTEXT_REQUEST_TOPIC_NARROW_FAILURE;
    }
    retcode = dsa_meas_context_req_cft_topic->set_expression_parameters(expression_parameters_three);
    if (retcode != DDS_RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set expression parameters for DSA Meas Context Request Content Filter.");
      return DicesRcDriver::DSA_MEAS_CONTEXT_REQUEST_TOPIC_FILTER_FAILURE;
    }
  }
  if (!_dsa_calc_context_req_data_reader)
  {
    LOG4CPLUS_INFO(root_logger, "  DSA Calc Context Request Reader is a null pointer");
  }
  else
  {
    DDS::TopicDescription* base_dsa_calc_context_req_topic = _dsa_calc_context_req_data_reader->get_topicdescription();
    if (!base_dsa_calc_context_req_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup DSA Calc Context Request Topic.");
      return DicesRcDriver::DSA_CALC_CONTEXT_REQUEST_TOPIC_LOOKUP_FAILURE;
    }
    DDS::ContentFilteredTopic *dsa_calc_context_req_cft_topic = DDS::ContentFilteredTopic::narrow(base_dsa_calc_context_req_topic);
    if (!dsa_calc_context_req_cft_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow DSA Calc Context Request Topic.");
      return DicesRcDriver::DSA_CALC_CONTEXT_REQUEST_TOPIC_NARROW_FAILURE;
    }
    retcode = dsa_calc_context_req_cft_topic->set_expression_parameters(expression_parameters_three);
    if (retcode != DDS_RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set expression parameters for DSA Calc Context Request Content Filter.");
      return DicesRcDriver::DSA_CALC_CONTEXT_REQUEST_TOPIC_FILTER_FAILURE;
    }
  }
  if (!_dsa_sett_context_req_data_reader)
  {
    LOG4CPLUS_INFO(root_logger, "  DSA Sett Context Request Reader is a null pointer");
  }
  else
  {
    DDS::TopicDescription* base_dsa_sett_context_req_topic = _dsa_sett_context_req_data_reader->get_topicdescription();
    if (!base_dsa_sett_context_req_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup DSA Sett Context Request Topic.");
      return DicesRcDriver::DSA_SETT_CONTEXT_REQUEST_TOPIC_LOOKUP_FAILURE;
    }
    DDS::ContentFilteredTopic *dsa_sett_context_req_cft_topic = DDS::ContentFilteredTopic::narrow(base_dsa_sett_context_req_topic);
    if (!dsa_sett_context_req_cft_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow DSA Sett Context Request Topic.");
      return DicesRcDriver::DSA_SETT_CONTEXT_REQUEST_TOPIC_NARROW_FAILURE;
    }
    retcode = dsa_sett_context_req_cft_topic->set_expression_parameters(expression_parameters_three);
    if (retcode != DDS_RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set expression parameters for DSA Sett Context Request Content Filter.");
      return DicesRcDriver::DSA_SETT_CONTEXT_REQUEST_TOPIC_FILTER_FAILURE;
    }
  }

  if (!_enumeration_meas_context_req_data_reader)
  {
    LOG4CPLUS_INFO(root_logger, " Enumeration Meas Context Request Reader is a null pointer");
  }
  else
  {
    DDS::TopicDescription* base_enumeration_meas_context_req_topic = _enumeration_meas_context_req_data_reader->get_topicdescription();
    if (!base_enumeration_meas_context_req_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Enumeration Meas Context Request Topic.");
      return DicesRcDriver::ENUMERATION_MEAS_CONTEXT_REQUEST_TOPIC_LOOKUP_FAILURE;
    }
    DDS::ContentFilteredTopic *enumeration_meas_context_req_cft_topic = DDS::ContentFilteredTopic::narrow(base_enumeration_meas_context_req_topic);
    if (!enumeration_meas_context_req_cft_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Enumeration Meas Context Request Topic.");
      return DicesRcDriver::ENUMERATION_MEAS_CONTEXT_REQUEST_TOPIC_NARROW_FAILURE;
    }
    retcode = enumeration_meas_context_req_cft_topic->set_expression_parameters(expression_parameters_four);
    if (retcode != DDS_RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set expression parameters for Enumeration Meas Context Request Content Filter.");
      return DicesRcDriver::ENUMERATION_MEAS_CONTEXT_REQUEST_TOPIC_FILTER_FAILURE;
    }
  }
  if (!_enumeration_calc_context_req_data_reader)
  {
    LOG4CPLUS_INFO(root_logger, " Enumeration Calc Context Request Reader is a null pointer");
  }
  else
  {
    DDS::TopicDescription* base_enumeration_calc_context_req_topic = _enumeration_calc_context_req_data_reader->get_topicdescription();
    if (!base_enumeration_calc_context_req_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Enumeration Calc Context Request Topic.");
      return DicesRcDriver::ENUMERATION_CALC_CONTEXT_REQUEST_TOPIC_LOOKUP_FAILURE;
    }
    DDS::ContentFilteredTopic *enumeration_calc_context_req_cft_topic = DDS::ContentFilteredTopic::narrow(base_enumeration_calc_context_req_topic);
    if (!enumeration_calc_context_req_cft_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Enumeration Calc Context Request Topic.");
      return DicesRcDriver::ENUMERATION_CALC_CONTEXT_REQUEST_TOPIC_NARROW_FAILURE;
    }
    retcode = enumeration_calc_context_req_cft_topic->set_expression_parameters(expression_parameters_four);
    if (retcode != DDS_RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set expression parameters for Enumeration Calc Context Request Content Filter.");
      return DicesRcDriver::ENUMERATION_CALC_CONTEXT_REQUEST_TOPIC_FILTER_FAILURE;
    }
  }
  if (!_enumeration_sett_context_req_data_reader)
  {
    LOG4CPLUS_INFO(root_logger, " Enumeration Sett Context Request Reader is a null pointer");
  }
  else
  {
    DDS::TopicDescription* base_enumeration_sett_context_req_topic = _enumeration_sett_context_req_data_reader->get_topicdescription();
    if (!base_enumeration_sett_context_req_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Enumeration Sett Context Request Topic.");
      return DicesRcDriver::ENUMERATION_SETT_CONTEXT_REQUEST_TOPIC_LOOKUP_FAILURE;
    }
    DDS::ContentFilteredTopic *enumeration_sett_context_req_cft_topic = DDS::ContentFilteredTopic::narrow(base_enumeration_sett_context_req_topic);
    if (!enumeration_sett_context_req_cft_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Enumeration Sett Context Request Topic.");
      return DicesRcDriver::ENUMERATION_SETT_CONTEXT_REQUEST_TOPIC_NARROW_FAILURE;
    }
    retcode = enumeration_sett_context_req_cft_topic->set_expression_parameters(expression_parameters_four);
    if (retcode != DDS_RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set expression parameters for Enumeration Sett Context Request Content Filter.");
      return DicesRcDriver::ENUMERATION_SETT_CONTEXT_REQUEST_TOPIC_FILTER_FAILURE;
    }
  }
  if (!_enumeration_sett_observed_value_req_data_reader)
  {
    LOG4CPLUS_INFO(root_logger, " Enumeration Sett Observed Value Request Reader is a null pointer");
  }
  else
  {
    DDS::TopicDescription* base_enumeration_sett_observed_value_req_topic = _enumeration_sett_observed_value_req_data_reader->get_topicdescription();
    if (!base_enumeration_sett_observed_value_req_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Enumeration Sett Observed Value Request Topic.");
      return DicesRcDriver::ENUMERATION_SETT_OBSERVED_VALUE_REQUEST_TOPIC_LOOKUP_FAILURE;
    }
    DDS::ContentFilteredTopic *enumeration_sett_observed_value_req_cft_topic = DDS::ContentFilteredTopic::narrow(base_enumeration_sett_observed_value_req_topic);
    if (!enumeration_sett_observed_value_req_cft_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Enumeration Sett Observed Value Request Topic.");
      return DicesRcDriver::ENUMERATION_SETT_OBSERVED_VALUE_REQUEST_TOPIC_NARROW_FAILURE;
    }
    retcode = enumeration_sett_observed_value_req_cft_topic->set_expression_parameters(expression_parameters_four);
    if (retcode != DDS_RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set expression parameters for Enumeration Sett Observed Value Request Content Filter.");
      return DicesRcDriver::ENUMERATION_SETT_OBSERVED_VALUE_REQUEST_TOPIC_FILTER_FAILURE;
    }
  }

  if (!_numeric_meas_context_req_data_reader)
  {
    LOG4CPLUS_INFO(root_logger, "  Numeric Meas Context Request Reader is a null pointer");
  }
  else
  {
    DDS::TopicDescription* base_numeric_meas_context_req_topic = _numeric_meas_context_req_data_reader->get_topicdescription();
    if (!base_numeric_meas_context_req_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Numeric Meas Context Request Topic.");
      return DicesRcDriver::NUMERIC_MEAS_CONTEXT_REQUEST_TOPIC_LOOKUP_FAILURE;
    }
    DDS::ContentFilteredTopic *numeric_meas_context_req_cft_topic = DDS::ContentFilteredTopic::narrow(base_numeric_meas_context_req_topic);
    if (!numeric_meas_context_req_cft_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Numeric Meas Context Request Topic.");
      return DicesRcDriver::NUMERIC_MEAS_CONTEXT_REQUEST_TOPIC_NARROW_FAILURE;
    }
    retcode = numeric_meas_context_req_cft_topic->set_expression_parameters(expression_parameters_four);
    if (retcode != DDS_RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set expression parameters for Numeric Meas Context Request Content Filter.");
      return DicesRcDriver::NUMERIC_MEAS_CONTEXT_REQUEST_TOPIC_FILTER_FAILURE;
    }
  }
  if (!_numeric_calc_context_req_data_reader)
  {
    LOG4CPLUS_INFO(root_logger, "  Numeric Calc Context Request Reader is a null pointer");
  }
  else
  {
    DDS::TopicDescription* base_numeric_calc_context_req_topic = _numeric_calc_context_req_data_reader->get_topicdescription();
    if (!base_numeric_calc_context_req_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Numeric Calc Context Request Topic.");
      return DicesRcDriver::NUMERIC_CALC_CONTEXT_REQUEST_TOPIC_LOOKUP_FAILURE;
    }
    DDS::ContentFilteredTopic *numeric_calc_context_req_cft_topic = DDS::ContentFilteredTopic::narrow(base_numeric_calc_context_req_topic);
    if (!numeric_calc_context_req_cft_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Numeric Calc Context Request Topic.");
      return DicesRcDriver::NUMERIC_CALC_CONTEXT_REQUEST_TOPIC_NARROW_FAILURE;
    }
    retcode = numeric_calc_context_req_cft_topic->set_expression_parameters(expression_parameters_four);
    if (retcode != DDS_RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set expression parameters for Numeric Calc Context Request Content Filter.");
      return DicesRcDriver::NUMERIC_CALC_CONTEXT_REQUEST_TOPIC_FILTER_FAILURE;
    }
  }
  if (!_numeric_sett_context_req_data_reader)
  {
    LOG4CPLUS_INFO(root_logger, " Numeric Sett Context Request Reader is a null pointer");
  }
  else
  {
    DDS::TopicDescription* base_numeric_sett_context_req_topic = _numeric_sett_context_req_data_reader->get_topicdescription();
    if (!base_numeric_sett_context_req_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Numeric Sett Context Request Topic.");
      return DicesRcDriver::NUMERIC_SETT_CONTEXT_REQUEST_TOPIC_LOOKUP_FAILURE;
    }
    DDS::ContentFilteredTopic *numeric_sett_context_req_cft_topic = DDS::ContentFilteredTopic::narrow(base_numeric_sett_context_req_topic);
    if (!numeric_sett_context_req_cft_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Numeric Sett Context Request Topic.");
      return DicesRcDriver::NUMERIC_SETT_CONTEXT_REQUEST_TOPIC_NARROW_FAILURE;
    }
    retcode = numeric_sett_context_req_cft_topic->set_expression_parameters(expression_parameters_four);
    if (retcode != DDS_RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set expression parameters for Numeric Sett Context Request Content Filter.");
      return DicesRcDriver::NUMERIC_SETT_CONTEXT_REQUEST_TOPIC_FILTER_FAILURE;
    }
  }
  if (!_numeric_sett_observed_value_req_data_reader)
  {
    LOG4CPLUS_INFO(root_logger, " Numeric Sett Observed Value Request Reader is a null pointer");
  }
  else
  {
    DDS::TopicDescription* base_numeric_sett_observed_value_req_topic = _numeric_sett_observed_value_req_data_reader->get_topicdescription();
    if (!base_numeric_sett_observed_value_req_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Numeric Sett Observed Value Request Topic.");
      return DicesRcDriver::NUMERIC_SETT_OBSERVED_VALUE_REQUEST_TOPIC_LOOKUP_FAILURE;
    }
    DDS::ContentFilteredTopic *numeric_sett_observed_value_req_cft_topic = DDS::ContentFilteredTopic::narrow(base_numeric_sett_observed_value_req_topic);
    if (!numeric_sett_observed_value_req_cft_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Numeric Sett Observed Value Request Topic.");
      return DicesRcDriver::NUMERIC_SETT_OBSERVED_VALUE_REQUEST_TOPIC_NARROW_FAILURE;
    }
    retcode = numeric_sett_observed_value_req_cft_topic->set_expression_parameters(expression_parameters_four);
    if (retcode != DDS_RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set expression parameters for Numeric Sett Observed Value Request Content Filter.");
      return DicesRcDriver::NUMERIC_SETT_OBSERVED_VALUE_REQUEST_TOPIC_FILTER_FAILURE;
    }
  }

  if (!_rtsa_meas_context_req_data_reader)
  {
    LOG4CPLUS_INFO(root_logger, " RTSA Meas Context Request Reader is a null pointer");
  }
  else
  {
    DDS::TopicDescription* base_rtsa_meas_context_req_topic = _rtsa_meas_context_req_data_reader->get_topicdescription();
    if (!base_rtsa_meas_context_req_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup RTSA Meas Context Request Topic.");
      return DicesRcDriver::RTSA_MEAS_CONTEXT_REQUEST_TOPIC_LOOKUP_FAILURE;
    }
    DDS::ContentFilteredTopic *rtsa_meas_context_req_cft_topic = DDS::ContentFilteredTopic::narrow(base_rtsa_meas_context_req_topic);
    if (!rtsa_meas_context_req_cft_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow RTSA Meas Context Request Topic.");
      return DicesRcDriver::RTSA_MEAS_CONTEXT_REQUEST_TOPIC_NARROW_FAILURE;
    }
    retcode = rtsa_meas_context_req_cft_topic->set_expression_parameters(expression_parameters_three);
    if (retcode != DDS_RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set expression parameters for RTSA Meas Context Request Content Filter.");
      return DicesRcDriver::RTSA_MEAS_CONTEXT_REQUEST_TOPIC_FILTER_FAILURE;
    }
  }
  if (!_rtsa_calc_context_req_data_reader)
  {
    LOG4CPLUS_INFO(root_logger, " RTSA Calc Context Request Reader is a null pointer");
  }
  else
  {
    DDS::TopicDescription* base_rtsa_calc_context_req_topic = _rtsa_calc_context_req_data_reader->get_topicdescription();
    if (!base_rtsa_calc_context_req_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup RTSA Calc Context Request Topic.");
      return DicesRcDriver::RTSA_CALC_CONTEXT_REQUEST_TOPIC_LOOKUP_FAILURE;
    }
    DDS::ContentFilteredTopic *rtsa_calc_context_req_cft_topic = DDS::ContentFilteredTopic::narrow(base_rtsa_calc_context_req_topic);
    if (!rtsa_calc_context_req_cft_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow RTSA Calc Context Request Topic.");
      return DicesRcDriver::RTSA_CALC_CONTEXT_REQUEST_TOPIC_NARROW_FAILURE;
    }
    retcode = rtsa_calc_context_req_cft_topic->set_expression_parameters(expression_parameters_three);
    if (retcode != DDS_RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set expression parameters for RTSA Calc Context Request Content Filter.");
      return DicesRcDriver::RTSA_CALC_CONTEXT_REQUEST_TOPIC_FILTER_FAILURE;
    }
  }
  if (!_rtsa_sett_context_req_data_reader)
  {
    LOG4CPLUS_INFO(root_logger, "  RTSA Sett Context Request Reader is a null pointer");
  }
  else
  {
    DDS::TopicDescription* base_rtsa_sett_context_req_topic = _rtsa_sett_context_req_data_reader->get_topicdescription();
    if (!base_rtsa_sett_context_req_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup RTSA Sett Context Request Topic.");
      return DicesRcDriver::RTSA_SETT_CONTEXT_REQUEST_TOPIC_LOOKUP_FAILURE;
    }
    DDS::ContentFilteredTopic *rtsa_sett_context_req_cft_topic = DDS::ContentFilteredTopic::narrow(base_rtsa_sett_context_req_topic);
    if (!rtsa_sett_context_req_cft_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow RTSA Sett Context Request Topic.");
      return DicesRcDriver::RTSA_SETT_CONTEXT_REQUEST_TOPIC_NARROW_FAILURE;
    }
    retcode = rtsa_sett_context_req_cft_topic->set_expression_parameters(expression_parameters_three);
    if (retcode != DDS_RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set expression parameters for RTSA Sett Context Request Content Filter.");
      return DicesRcDriver::RTSA_SETT_CONTEXT_REQUEST_TOPIC_FILTER_FAILURE;
    }
  }

  if (!_tsa_meas_context_req_data_reader)
  {
    LOG4CPLUS_INFO(root_logger, " TSA Meas Context Request Reader is a null pointer");
  }
  else
  {
    DDS::TopicDescription* base_tsa_meas_context_req_topic = _tsa_meas_context_req_data_reader->get_topicdescription();
    if (!base_tsa_meas_context_req_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup TSA Meas Context Request Topic.");
      return DicesRcDriver::TSA_MEAS_CONTEXT_REQUEST_TOPIC_LOOKUP_FAILURE;
    }
    DDS::ContentFilteredTopic *tsa_meas_context_req_cft_topic = DDS::ContentFilteredTopic::narrow(base_tsa_meas_context_req_topic);
    if (!tsa_meas_context_req_cft_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow TSA Meas Context Request Topic.");
      return DicesRcDriver::TSA_MEAS_CONTEXT_REQUEST_TOPIC_NARROW_FAILURE;
    }
    retcode = tsa_meas_context_req_cft_topic->set_expression_parameters(expression_parameters_three);
    if (retcode != DDS_RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set expression parameters for TSA Meas Context Request Content Filter.");
      return DicesRcDriver::TSA_MEAS_CONTEXT_REQUEST_TOPIC_FILTER_FAILURE;
    }
  }
  if (!_tsa_calc_context_req_data_reader)
  {
    LOG4CPLUS_INFO(root_logger, " TSA Calc Context Request Reader is a null pointer");
  }
  else
  {
    DDS::TopicDescription* base_tsa_calc_context_req_topic = _tsa_calc_context_req_data_reader->get_topicdescription();
    if (!base_tsa_calc_context_req_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup TSA Calc Context Request Topic.");
      return DicesRcDriver::TSA_CALC_CONTEXT_REQUEST_TOPIC_LOOKUP_FAILURE;
    }
    DDS::ContentFilteredTopic *tsa_calc_context_req_cft_topic = DDS::ContentFilteredTopic::narrow(base_tsa_calc_context_req_topic);
    if (!tsa_calc_context_req_cft_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow TSA Calc Context Request Topic.");
      return DicesRcDriver::TSA_CALC_CONTEXT_REQUEST_TOPIC_NARROW_FAILURE;
    }
    retcode = tsa_calc_context_req_cft_topic->set_expression_parameters(expression_parameters_three);
    if (retcode != DDS_RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set expression parameters for TSA Calc Context Request Content Filter.");
      return DicesRcDriver::TSA_CALC_CONTEXT_REQUEST_TOPIC_FILTER_FAILURE;
    }
  }
  if (!_tsa_sett_context_req_data_reader)
  {
    LOG4CPLUS_INFO(root_logger, " TSA Sett Context Request Reader is a null pointer");
  }
  else
  {
    DDS::TopicDescription* base_tsa_sett_context_req_topic = _tsa_sett_context_req_data_reader->get_topicdescription();
    if (!base_tsa_sett_context_req_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup TSA Sett Context Request Topic.");
      return DicesRcDriver::TSA_SETT_CONTEXT_REQUEST_TOPIC_LOOKUP_FAILURE;
    }
    DDS::ContentFilteredTopic *tsa_sett_context_req_cft_topic = DDS::ContentFilteredTopic::narrow(base_tsa_sett_context_req_topic);
    if (!tsa_sett_context_req_cft_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow TSA Sett Context Request Topic.");
      return DicesRcDriver::TSA_SETT_CONTEXT_REQUEST_TOPIC_NARROW_FAILURE;
    }
    retcode = tsa_sett_context_req_cft_topic->set_expression_parameters(expression_parameters_three);
    if (retcode != DDS_RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set expression parameters for TSA Sett Context Request Content Filter.");
      return DicesRcDriver::TSA_SETT_CONTEXT_REQUEST_TOPIC_FILTER_FAILURE;
    }
  }

  if (!_device_driver_state_req_data_reader)
  {
    LOG4CPLUS_INFO(root_logger, " Device Driver State Request Reader is a null pointer");
  }
  else
  {
    DDS::TopicDescription* base_device_driver_state_req_topic = _device_driver_state_req_data_reader->get_topicdescription();
    if (!base_device_driver_state_req_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to lookup Device Driver State Request Topic.");
      return DicesRcDriver::DEVICE_DRIVER_STATE_REQUEST_TOPIC_LOOKUP_FAILURE;
    }
    DDS::ContentFilteredTopic *device_driver_state_req_cft_topic = DDS::ContentFilteredTopic::narrow(base_device_driver_state_req_topic);
    if (!device_driver_state_req_cft_topic)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to narrow Device Driver State Request Topic.");
      return DicesRcDriver::DEVICE_DRIVER_STATE_REQUEST_TOPIC_NARROW_FAILURE;
    }
    retcode = device_driver_state_req_cft_topic->set_expression_parameters(expression_parameters_one);
    if (retcode != DDS_RETCODE_OK)
    {
      LOG4CPLUS_ERROR(root_logger, " Failed to set expression parameters for Device Driver State Request Content Filter.");
      return DicesRcDriver::DEVICE_DRIVER_STATE_REQUEST_TOPIC_FILTER_FAILURE;
    }
  }
  return DicesRcDriver::OK;
}

DicesRcDriver BusComm::ReadFromBus()
{
  DDS::ReturnCode_t retcode = DDS::RETCODE_OK;

  if (_physiological_alarm_context_req_data_reader)
  {
    // Read data from DDS bus
    ice::AlarmContextSeq physiological_alarm_context_data_seq;
    DDS::SampleInfoSeq physiological_alarm_context_info_seq;
    retcode = _physiological_alarm_context_req_data_reader->read(
      physiological_alarm_context_data_seq,
      physiological_alarm_context_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < physiological_alarm_context_data_seq.length(); ++ix)
      {
        if (physiological_alarm_context_info_seq[ix].valid_data)
        {
          // If the data item was valid, copy into a fresh instance
          ice::AlarmContext* instance = ice::AlarmContextTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::PHYSIOLOGICAL_ALARM_CONTEXT_INSTANCE_CREATE_FAILURE;
          }
          ice::AlarmContextTypeSupport::copy_data(instance, &physiological_alarm_context_data_seq[ix]);
          _parser->AddPhysAlarmContextCommand(instance);
        }
      }
    }
    if (_physiological_alarm_context_req_data_reader->return_loan(physiological_alarm_context_data_seq, physiological_alarm_context_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::PHYSIOLOGICAL_ALARM_CONTEXT_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
  }

  if (_technical_alarm_context_req_data_reader)
  {
    ice::AlarmContextSeq technical_alarm_context_data_seq;
    DDS::SampleInfoSeq technical_alarm_context_info_seq;
    retcode = _technical_alarm_context_req_data_reader->read(
      technical_alarm_context_data_seq,
      technical_alarm_context_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < technical_alarm_context_data_seq.length(); ++ix)
      {
        if (technical_alarm_context_info_seq[ix].valid_data)
        {
          // If the data item was valid, copy into a fresh instance
          ice::AlarmContext* instance = ice::AlarmContextTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::TECHNICAL_ALARM_CONTEXT_INSTANCE_CREATE_FAILURE;
          }
          ice::AlarmContextTypeSupport::copy_data(instance, &technical_alarm_context_data_seq[ix]);
          _parser->AddTechAlarmContextCommand(instance);
        }
      }
    }
    if (_technical_alarm_context_req_data_reader->return_loan(technical_alarm_context_data_seq, technical_alarm_context_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::TECHNICAL_ALARM_CONTEXT_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
  }

  if (_dsa_meas_context_req_data_reader)
  {
    ice::DSAContextSeq dsa_meas_context_data_seq;
    DDS::SampleInfoSeq dsa_meas_context_info_seq;
    retcode = _dsa_meas_context_req_data_reader->read(
      dsa_meas_context_data_seq,
      dsa_meas_context_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < dsa_meas_context_data_seq.length(); ++ix)
      {
        if (dsa_meas_context_info_seq[ix].valid_data)
        {
          ice::DSAContext* instance = ice::DSAContextTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::DSA_MEAS_CONTEXT_INSTANCE_CREATE_FAILURE;
          }
          ice::DSAContextTypeSupport::copy_data(instance, &dsa_meas_context_data_seq[ix]);
          _parser->AddDSAMeasContextCommand(instance);
        }
      }
    }
    if (_dsa_meas_context_req_data_reader->return_loan(dsa_meas_context_data_seq, dsa_meas_context_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::DSA_MEAS_CONTEXT_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
  }
  if (_dsa_calc_context_req_data_reader)
  {
    ice::DSAContextSeq dsa_calc_context_data_seq;
    DDS::SampleInfoSeq dsa_calc_context_info_seq;
    retcode = _dsa_calc_context_req_data_reader->read(
      dsa_calc_context_data_seq,
      dsa_calc_context_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < dsa_calc_context_data_seq.length(); ++ix)
      {
        if (dsa_calc_context_info_seq[ix].valid_data)
        {
          ice::DSAContext* instance = ice::DSAContextTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::DSA_CALC_CONTEXT_INSTANCE_CREATE_FAILURE;
          }
          ice::DSAContextTypeSupport::copy_data(instance, &dsa_calc_context_data_seq[ix]);
          _parser->AddDSACalcContextCommand(instance);
        }
      }
    }
    if (_dsa_calc_context_req_data_reader->return_loan(dsa_calc_context_data_seq, dsa_calc_context_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::DSA_CALC_CONTEXT_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
  }
  if (_dsa_sett_context_req_data_reader)
  {
    ice::DSAContextSeq dsa_sett_context_data_seq;
    DDS::SampleInfoSeq dsa_sett_context_info_seq;
    retcode = _dsa_sett_context_req_data_reader->read(
      dsa_sett_context_data_seq,
      dsa_sett_context_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < dsa_sett_context_data_seq.length(); ++ix)
      {
        if (dsa_sett_context_info_seq[ix].valid_data)
        {
          ice::DSAContext* instance = ice::DSAContextTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::DSA_SETT_CONTEXT_INSTANCE_CREATE_FAILURE;
          }
          ice::DSAContextTypeSupport::copy_data(instance, &dsa_sett_context_data_seq[ix]);
          _parser->AddDSASettContextCommand(instance);
        }
      }
    }
    if (_dsa_sett_context_req_data_reader->return_loan(dsa_sett_context_data_seq, dsa_sett_context_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::DSA_SETT_CONTEXT_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
  }

  if (_enumeration_meas_context_req_data_reader)
  {
    ice::EnumerationContextSeq enumeration_meas_context_data_seq;
    DDS::SampleInfoSeq enumeration_meas_context_info_seq;
    retcode = _enumeration_meas_context_req_data_reader->read(
      enumeration_meas_context_data_seq,
      enumeration_meas_context_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < enumeration_meas_context_data_seq.length(); ++ix)
      {
        if (enumeration_meas_context_info_seq[ix].valid_data)
        {
          ice::EnumerationContext* instance = ice::EnumerationContextTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::ENUMERATION_MEAS_CONTEXT_INSTANCE_CREATE_FAILURE;
          }
          ice::EnumerationContextTypeSupport::copy_data(instance, &enumeration_meas_context_data_seq[ix]);
          _parser->AddEnumerationMeasContextCommand(instance);
        }
      }
    }
    if (_enumeration_meas_context_req_data_reader->return_loan(enumeration_meas_context_data_seq, enumeration_meas_context_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::ENUMERATION_MEAS_CONTEXT_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
  }
  if (_enumeration_calc_context_req_data_reader)
  {
    ice::EnumerationContextSeq enumeration_calc_context_data_seq;
    DDS::SampleInfoSeq enumeration_calc_context_info_seq;
    retcode = _enumeration_calc_context_req_data_reader->read(
      enumeration_calc_context_data_seq,
      enumeration_calc_context_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < enumeration_calc_context_data_seq.length(); ++ix)
      {
        if (enumeration_calc_context_info_seq[ix].valid_data)
        {
          ice::EnumerationContext* instance = ice::EnumerationContextTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::ENUMERATION_CALC_CONTEXT_INSTANCE_CREATE_FAILURE;
          }
          ice::EnumerationContextTypeSupport::copy_data(instance, &enumeration_calc_context_data_seq[ix]);
          _parser->AddEnumerationCalcContextCommand(instance);
        }
      }
    }
    if (_enumeration_calc_context_req_data_reader->return_loan(enumeration_calc_context_data_seq, enumeration_calc_context_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::ENUMERATION_CALC_CONTEXT_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
  }
  if (_enumeration_sett_context_req_data_reader)
  {
    ice::EnumerationContextSeq enumeration_sett_context_data_seq;
    DDS::SampleInfoSeq enumeration_sett_context_info_seq;
    retcode = _enumeration_sett_context_req_data_reader->read(
      enumeration_sett_context_data_seq,
      enumeration_sett_context_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < enumeration_sett_context_data_seq.length(); ++ix)
      {
        if (enumeration_sett_context_info_seq[ix].valid_data)
        {
          ice::EnumerationContext* instance = ice::EnumerationContextTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::ENUMERATION_SETT_CONTEXT_INSTANCE_CREATE_FAILURE;
          }
          ice::EnumerationContextTypeSupport::copy_data(instance, &enumeration_sett_context_data_seq[ix]);
          _parser->AddEnumerationSettContextCommand(instance);
        }
      }
    }
    if (_enumeration_sett_context_req_data_reader->return_loan(enumeration_sett_context_data_seq, enumeration_sett_context_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::ENUMERATION_SETT_CONTEXT_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
  }
  if (_enumeration_sett_observed_value_req_data_reader)
  {
    ice::EnumerationObservedValueSeq enumeration_sett_observed_value_data_seq;
    DDS::SampleInfoSeq enumeration_sett_observed_value_info_seq;
    retcode = _enumeration_sett_observed_value_req_data_reader->read(
      enumeration_sett_observed_value_data_seq,
      enumeration_sett_observed_value_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < enumeration_sett_observed_value_data_seq.length(); ++ix)
      {
        if (enumeration_sett_observed_value_info_seq[ix].valid_data)
        {
          ice::EnumerationObservedValue* instance = ice::EnumerationObservedValueTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::ENUMERATION_SETT_OBSERVED_VALUE_INSTANCE_CREATE_FAILURE;
          }
          ice::EnumerationObservedValueTypeSupport::copy_data(instance, &enumeration_sett_observed_value_data_seq[ix]);
          _parser->AddEnumerationSettObservedValueCommand(instance);
        }
      }
    }
    if (_enumeration_sett_observed_value_req_data_reader->return_loan(enumeration_sett_observed_value_data_seq, enumeration_sett_observed_value_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::ENUMERATION_SETT_OBSERVED_VALUE_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
  }

  if (_numeric_meas_context_req_data_reader)
  {
    ice::NumericContextSeq numeric_meas_context_data_seq;
    DDS::SampleInfoSeq numeric_meas_context_info_seq;
    retcode = _numeric_meas_context_req_data_reader->read(
      numeric_meas_context_data_seq,
      numeric_meas_context_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < numeric_meas_context_data_seq.length(); ++ix)
      {
        if (numeric_meas_context_info_seq[ix].valid_data)
        {
          ice::NumericContext* instance = ice::NumericContextTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::NUMERIC_MEAS_CONTEXT_INSTANCE_CREATE_FAILURE;
          }
          ice::NumericContextTypeSupport::copy_data(instance, &numeric_meas_context_data_seq[ix]);
          _parser->AddNumericMeasContextCommand(instance);
        }
      }
    }
    if (_numeric_meas_context_req_data_reader->return_loan(numeric_meas_context_data_seq, numeric_meas_context_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::NUMERIC_MEAS_CONTEXT_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
  }
  if (_numeric_calc_context_req_data_reader)
  {
    ice::NumericContextSeq numeric_calc_context_data_seq;
    DDS::SampleInfoSeq numeric_calc_context_info_seq;
    retcode = _numeric_calc_context_req_data_reader->read(
      numeric_calc_context_data_seq,
      numeric_calc_context_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < numeric_calc_context_data_seq.length(); ++ix)
      {
        if (numeric_calc_context_info_seq[ix].valid_data)
        {
          ice::NumericContext* instance = ice::NumericContextTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::NUMERIC_CALC_CONTEXT_INSTANCE_CREATE_FAILURE;
          }
          ice::NumericContextTypeSupport::copy_data(instance, &numeric_calc_context_data_seq[ix]);
          _parser->AddNumericCalcContextCommand(instance);
        }
      }
    }
    if (_numeric_calc_context_req_data_reader->return_loan(numeric_calc_context_data_seq, numeric_calc_context_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::NUMERIC_CALC_CONTEXT_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
  }
  if (_numeric_sett_context_req_data_reader)
  {
    ice::NumericContextSeq numeric_sett_context_data_seq;
    DDS::SampleInfoSeq numeric_sett_context_info_seq;
    retcode = _numeric_sett_context_req_data_reader->read(
      numeric_sett_context_data_seq,
      numeric_sett_context_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < numeric_sett_context_data_seq.length(); ++ix)
      {
        if (numeric_sett_context_info_seq[ix].valid_data)
        {
          ice::NumericContext* instance = ice::NumericContextTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::NUMERIC_SETT_CONTEXT_INSTANCE_CREATE_FAILURE;
          }
          ice::NumericContextTypeSupport::copy_data(instance, &numeric_sett_context_data_seq[ix]);
          _parser->AddNumericSettContextCommand(instance);
        }
      }
    }
    if (_numeric_sett_context_req_data_reader->return_loan(numeric_sett_context_data_seq, numeric_sett_context_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::NUMERIC_SETT_CONTEXT_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
  }
  if (_numeric_sett_observed_value_req_data_reader)
  {
    ice::NumericObservedValueSeq numeric_sett_observed_value_data_seq;
    DDS::SampleInfoSeq numeric_sett_observed_value_info_seq;
    retcode = _numeric_sett_observed_value_req_data_reader->read(
      numeric_sett_observed_value_data_seq,
      numeric_sett_observed_value_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < numeric_sett_observed_value_data_seq.length(); ++ix)
      {
        if (numeric_sett_observed_value_info_seq[ix].valid_data)
        {
          ice::NumericObservedValue* instance = ice::NumericObservedValueTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::NUMERIC_SETT_OBSERVED_VALUE_INSTANCE_CREATE_FAILURE;
          }
          ice::NumericObservedValueTypeSupport::copy_data(instance, &numeric_sett_observed_value_data_seq[ix]);
          _parser->AddNumericSettObservedValueCommand(instance);
        }
      }
    }
    if (_numeric_sett_observed_value_req_data_reader->return_loan(numeric_sett_observed_value_data_seq, numeric_sett_observed_value_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::NUMERIC_SETT_OBSERVED_VALUE_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
  }

  if (_rtsa_meas_context_req_data_reader)
  {
    ice::RTSAContextSeq rtsa_meas_context_data_seq;
    DDS::SampleInfoSeq rtsa_meas_context_info_seq;
    retcode = _rtsa_meas_context_req_data_reader->read(
      rtsa_meas_context_data_seq,
      rtsa_meas_context_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < rtsa_meas_context_data_seq.length(); ++ix)
      {
        if (rtsa_meas_context_info_seq[ix].valid_data)
        {
          ice::RTSAContext* instance = ice::RTSAContextTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::RTSA_MEAS_CONTEXT_INSTANCE_CREATE_FAILURE;
          }
          ice::RTSAContextTypeSupport::copy_data(instance, &rtsa_meas_context_data_seq[ix]);
          _parser->AddRTSAMeasContextCommand(instance);
        }
      }
    }
    if (_rtsa_meas_context_req_data_reader->return_loan(rtsa_meas_context_data_seq, rtsa_meas_context_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::RTSA_MEAS_CONTEXT_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
  }
  if (_rtsa_calc_context_req_data_reader)
  {
    ice::RTSAContextSeq rtsa_calc_context_data_seq;
    DDS::SampleInfoSeq rtsa_calc_context_info_seq;
    retcode = _rtsa_calc_context_req_data_reader->read(
      rtsa_calc_context_data_seq,
      rtsa_calc_context_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < rtsa_calc_context_data_seq.length(); ++ix)
      {
        if (rtsa_calc_context_info_seq[ix].valid_data)
        {
          ice::RTSAContext* instance = ice::RTSAContextTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::RTSA_CALC_CONTEXT_INSTANCE_CREATE_FAILURE;
          }
          ice::RTSAContextTypeSupport::copy_data(instance, &rtsa_calc_context_data_seq[ix]);
          _parser->AddRTSACalcContextCommand(instance);
        }
      }
    }
    if (_rtsa_calc_context_req_data_reader->return_loan(rtsa_calc_context_data_seq, rtsa_calc_context_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::RTSA_CALC_CONTEXT_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
  }
  if (_rtsa_sett_context_req_data_reader)
  {
    ice::RTSAContextSeq rtsa_sett_context_data_seq;
    DDS::SampleInfoSeq rtsa_sett_context_info_seq;
    retcode = _rtsa_sett_context_req_data_reader->read(
      rtsa_sett_context_data_seq,
      rtsa_sett_context_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < rtsa_sett_context_data_seq.length(); ++ix)
      {
        if (rtsa_sett_context_info_seq[ix].valid_data)
        {
          ice::RTSAContext* instance = ice::RTSAContextTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::RTSA_SETT_CONTEXT_INSTANCE_CREATE_FAILURE;
          }
          ice::RTSAContextTypeSupport::copy_data(instance, &rtsa_sett_context_data_seq[ix]);
          _parser->AddRTSASettContextCommand(instance);
        }
      }
    }
    if (_rtsa_sett_context_req_data_reader->return_loan(rtsa_sett_context_data_seq, rtsa_sett_context_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::RTSA_SETT_CONTEXT_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
  }

  if (_tsa_meas_context_req_data_reader)
  {
    ice::TSAContextSeq tsa_meas_context_data_seq;
    DDS::SampleInfoSeq tsa_meas_context_info_seq;
    retcode = _tsa_meas_context_req_data_reader->read(
      tsa_meas_context_data_seq,
      tsa_meas_context_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < tsa_meas_context_data_seq.length(); ++ix)
      {
        if (tsa_meas_context_info_seq[ix].valid_data)
        {
          ice::TSAContext* instance = ice::TSAContextTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::TSA_MEAS_CONTEXT_INSTANCE_CREATE_FAILURE;
          }
          ice::TSAContextTypeSupport::copy_data(instance, &tsa_meas_context_data_seq[ix]);
          _parser->AddTSAMeasContextCommand(instance);
        }
      }
    }
    if (_tsa_meas_context_req_data_reader->return_loan(tsa_meas_context_data_seq, tsa_meas_context_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::TSA_MEAS_CONTEXT_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
  }
  if (_tsa_calc_context_req_data_reader)
  {
    ice::TSAContextSeq tsa_calc_context_data_seq;
    DDS::SampleInfoSeq tsa_calc_context_info_seq;
    retcode = _tsa_calc_context_req_data_reader->read(
      tsa_calc_context_data_seq,
      tsa_calc_context_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < tsa_calc_context_data_seq.length(); ++ix)
      {
        if (tsa_calc_context_info_seq[ix].valid_data)
        {
          ice::TSAContext* instance = ice::TSAContextTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::TSA_CALC_CONTEXT_INSTANCE_CREATE_FAILURE;
          }
          ice::TSAContextTypeSupport::copy_data(instance, &tsa_calc_context_data_seq[ix]);
          _parser->AddTSACalcContextCommand(instance);
        }
      }
    }
    if (_tsa_calc_context_req_data_reader->return_loan(tsa_calc_context_data_seq, tsa_calc_context_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::TSA_CALC_CONTEXT_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
  }
  if (_tsa_sett_context_req_data_reader)
  {
    ice::TSAContextSeq tsa_sett_context_data_seq;
    DDS::SampleInfoSeq tsa_sett_context_info_seq;
    retcode = _tsa_sett_context_req_data_reader->read(
      tsa_sett_context_data_seq,
      tsa_sett_context_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < tsa_sett_context_data_seq.length(); ++ix)
      {
        if (tsa_sett_context_info_seq[ix].valid_data)
        {
          ice::TSAContext* instance = ice::TSAContextTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::TSA_SETT_CONTEXT_INSTANCE_CREATE_FAILURE;
          }
          ice::TSAContextTypeSupport::copy_data(instance, &tsa_sett_context_data_seq[ix]);
          _parser->AddTSASettContextCommand(instance);
        }
      }
    }
    if (_tsa_sett_context_req_data_reader->return_loan(tsa_sett_context_data_seq, tsa_sett_context_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::TSA_SETT_CONTEXT_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
  }

  if (_patient_identification_req_data_reader)
  {
    ice::PatientIdentificationSeq patient_identification_req_data_seq;
    DDS::SampleInfoSeq patient_identification_req_info_seq;
    retcode = _patient_identification_req_data_reader->read(
      patient_identification_req_data_seq,
      patient_identification_req_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::NOT_READ_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < patient_identification_req_data_seq.length(); ++ix)
      {
        if (patient_identification_req_info_seq[ix].valid_data)
        {
          // If the data item was valid, copy into a fresh instance
          ice::PatientIdentification* instance = ice::PatientIdentificationTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::PATIENT_IDENTIFICATION_INSTANCE_CREATE_FAILURE;
          }
          ice::PatientIdentificationTypeSupport::copy_data(instance, &patient_identification_req_data_seq[ix]);
          _parser->AddPatientIdentificationCommand(instance);
        }
      }
    }
    if (_patient_identification_req_data_reader->return_loan(patient_identification_req_data_seq, patient_identification_req_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::PATIENT_IDENTIFICATION_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
  }

  if (_device_driver_state_req_data_reader)
  {
    bool quit = false;
    docbox::DeviceDriverStateSeq device_driver_state_data_seq;
    DDS::SampleInfoSeq device_driver_state_info_seq;
    retcode = _device_driver_state_req_data_reader->read(
      device_driver_state_data_seq,
      device_driver_state_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < device_driver_state_data_seq.length(); ++ix)
      {
        if (device_driver_state_info_seq[ix].valid_data &&
          device_driver_state_data_seq[ix].driver_status == docbox::DriverStatus::shutdown)
        {
          quit = true;
        }

        if (device_driver_state_info_seq[ix].valid_data)
        {
          // If the data item was valid, copy into a fresh instance
          docbox::DeviceDriverState* instance = docbox::DeviceDriverStateTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::DEVICE_DRIVER_STATE_INSTANCE_CREATE_FAILURE;
          }
          docbox::DeviceDriverStateTypeSupport::copy_data(instance, &device_driver_state_data_seq[ix]);
          _parser->AddDeviceDriverStateCommand(instance);
        }
      }
    }
    if (_device_driver_state_req_data_reader->return_loan(device_driver_state_data_seq, device_driver_state_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::DEVICE_DRIVER_STATE_REQUEST_READER_LOAN_RETURN_FAILURE;
    }
    if (quit) return DicesRcDriver::QUIT;
  }

  if (_allergy_data_reader)
  {
    bool quit = false;
    ice::AllergySeq allergy_data_seq;
    DDS::SampleInfoSeq allergy_info_seq;
    retcode = _allergy_data_reader->read(
      allergy_data_seq,
      allergy_info_seq,
      DDS::LENGTH_UNLIMITED,
      DDS::ANY_SAMPLE_STATE,
      DDS::ANY_VIEW_STATE,
      DDS::ANY_INSTANCE_STATE);
    if (retcode == DDS::RETCODE_OK)
    {
      for (int ix = 0; ix < allergy_data_seq.length(); ++ix)
      {
        if (allergy_info_seq[ix].valid_data)
        {
          // If the data item was valid, copy into a fresh instance
          ice::Allergy* instance = ice::AllergyTypeSupport::create_data();
          if (!instance)
          {
            return DicesRcDriver::ALLERGY_INSTANCE_CREATE_FAILURE;
          }
          ice::AllergyTypeSupport::copy_data(instance, &allergy_data_seq[ix]);
          _parser->AddAllergyCommand(instance);
        }
      }
    }
    if (_allergy_data_reader->return_loan(allergy_data_seq, allergy_info_seq) != DDS::RETCODE_OK)
    {
      return DicesRcDriver::ALLERGY_READER_RETURN_LOAN_FAILURE;
    }
    if (quit) return DicesRcDriver::QUIT;
  }
  return DicesRcDriver::OK;
}

DicesRcDriver BusComm::WriteToBus()
{
  DicesRcDriver driver_retcode = DicesRcDriver::OK;
  DDS::ReturnCode_t dds_retcode = DDS::RETCODE_OK;

  int index = 0;

  ice::PatientIdentification* patient_identification_req_instance = nullptr;
  while (_parser->GetPatientIdentificationReqToPublish(&patient_identification_req_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&patient_identification_req_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Patient Identification Request source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_patient_identification_req_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Patient Identification Request Writer is a null pointer");
      break;
    }
    dds_retcode = _patient_identification_req_data_writer->write(*patient_identification_req_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Patient Identification Request Instance: Handle: " << patient_identification_req_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::PATIENT_IDENTIFICATION_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Patient Identification Request Instance: Handle: " << patient_identification_req_instance->handle << std::endl);
    _parser->SetPatientIdentificationReqAsPublished(index);
  }
  ice::PatientDemographics* patient_demographics_req_instance = nullptr;
  while (_parser->GetPatientDemographicsReqToPublish(&patient_demographics_req_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&patient_demographics_req_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Patient Demographics Request source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_patient_demographics_req_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Patient Demographics Request Writer is a null pointer");
      break;
    }
    dds_retcode = _patient_demographics_req_data_writer->write(*patient_demographics_req_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Patient Demographics Request Instance: Handle: " << patient_demographics_req_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::PATIENT_DEMOGRAPHICS_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Patient Demographics Request Instance: Handle: " << patient_demographics_req_instance->handle << std::endl);
    _parser->SetPatientDemographicsReqAsPublished(index);
  }
  ice::MDS* mds_instance = nullptr;
  while (_parser->GetMDSToPublish(&mds_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&mds_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set MDS source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_mds_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because MDS Writer is a null pointer");
      break;
    }
    dds_retcode = _mds_data_writer->write(*mds_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write MDS Instance: Handle: " << mds_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::MDS_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published MDS Instance: Handle: " << mds_instance->handle << std::endl);
    _parser->SetMDSAsPublished(index);
  }
  ice::VMD* vmd_instance = nullptr;
  while (_parser->GetVMDToPublish(&vmd_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&vmd_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set VMD source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_vmd_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because VMD Writer is a null pointer");
      break;
    }
    dds_retcode = _vmd_data_writer->write(*vmd_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write VMD Instance: Handle: " << vmd_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::VMD_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published VMD Instance: Handle: " << vmd_instance->handle << std::endl);
    _parser->SetVMDAsPublished(index);
  }

  ice::AlarmSignal* physiological_alarm_signal_instance = nullptr;
  while (_parser->GetPhysAlarmSignalToPublish(&physiological_alarm_signal_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&physiological_alarm_signal_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Physiological Alarm Signal source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_physiological_alarm_signal_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Physiological Alarm Signal Writer is a null pointer");
      break;
    }
    dds_retcode = _physiological_alarm_signal_data_writer->write(*physiological_alarm_signal_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Physiological Alarm Signal Instance: Handle: " << physiological_alarm_signal_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::PHYSIOLOGICAL_ALARM_SIGNAL_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Physiological Alarm Signal Instance: Handle: " << physiological_alarm_signal_instance->handle << std::endl);
    _parser->SetPhysAlarmSignalAsPublished(index);
  }
  ice::AlarmSignal* technical_alarm_signal_instance = nullptr;
  while (_parser->GetTechAlarmSignalToPublish(&technical_alarm_signal_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&technical_alarm_signal_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Technical Alarm Signal source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_technical_alarm_signal_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Technical Alarm Signal Writer is a null pointer");
      break;
    }
    dds_retcode = _technical_alarm_signal_data_writer->write(*technical_alarm_signal_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Technical Alarm Signal Instance: Handle: " << technical_alarm_signal_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::TECHNICAL_ALARM_SIGNAL_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Technical Alarm Signal Instance: Handle: " << technical_alarm_signal_instance->handle << std::endl);
    _parser->SetTechAlarmSignalAsPublished(index);
  }
  ice::InformationSignal* information_signal_instance = nullptr;
  while (_parser->GetInformationSignalToPublish(&information_signal_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&information_signal_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Information Signal source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_information_signal_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Information Signal Writer is a null pointer");
      break;
    }
    dds_retcode = _information_signal_data_writer->write(*information_signal_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Information Signal Instance: Handle: " << information_signal_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::INFORMATION_SIGNAL_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Information Signal Instance: Handle: " << information_signal_instance->handle << std::endl);
    _parser->SetInformationSignalAsPublished(index);
  }
  ice::ReminderSignal* reminder_signal_instance = nullptr;
  while (_parser->GetReminderSignalToPublish(&reminder_signal_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&reminder_signal_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Reminder Signal source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_reminder_signal_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Reminder Signal Writer is a null pointer");
      break;
    }
    dds_retcode = _reminder_signal_data_writer->write(*reminder_signal_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Reminder Signal Instance: Handle: " << reminder_signal_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::REMINDER_SIGNAL_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Reminder Signal Instance: Handle: " << reminder_signal_instance->handle << std::endl);
    _parser->SetReminderSignalAsPublished(index);
  }
  ice::AlarmContext* physiological_alarm_context_instance = nullptr;
  while (_parser->GetPhysAlarmContextToPublish(&physiological_alarm_context_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&physiological_alarm_context_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Physiological Alarm Context source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_physiological_alarm_context_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Physiological Alarm Context Writer is a null pointer");
      break;
    }
    dds_retcode = _physiological_alarm_context_data_writer->write(*physiological_alarm_context_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Physiological Alarm Context Instance: Handle: " << physiological_alarm_context_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::PHYSIOLOGICAL_ALARM_CONTEXT_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Physiological Alarm Context Instance: Handle: " << physiological_alarm_context_instance->handle << std::endl);
    _parser->SetPhysAlarmContextAsPublished(index);
  }
  ice::AlarmContext* technical_alarm_context_instance = nullptr;
  while (_parser->GetTechAlarmContextToPublish(&technical_alarm_context_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&technical_alarm_context_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Technical Alarm Context source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_technical_alarm_context_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Technical Alarm Context Writer is a null pointer");
      break;
    }
    dds_retcode = _technical_alarm_context_data_writer->write(*technical_alarm_context_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Technical Alarm Context Instance: Handle: " << technical_alarm_context_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::TECHNICAL_ALARM_CONTEXT_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Technical Alarm Context Instance: Handle: " << technical_alarm_context_instance->handle << std::endl);
    _parser->SetTechAlarmContextAsPublished(index);
  }

  ice::DSAContext* dsa_meas_context_instance = nullptr;
  while (_parser->GetDSAMeasContextToPublish(&dsa_meas_context_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&dsa_meas_context_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set DSA Meas Context source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_dsa_meas_context_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because DSA Meas Context Writer is a null pointer");
      break;
    }
    dds_retcode = _dsa_meas_context_data_writer->write(*dsa_meas_context_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write DSA Meas Context Instance: Handle: " << dsa_meas_context_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::DSA_MEAS_CONTEXT_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published DSA Meas Context Instance: Handle: " << dsa_meas_context_instance->handle << std::endl);
    _parser->SetDSAMeasContextAsPublished(index);
  }
  ice::DSAObservedValue* dsa_meas_observed_value_instance = nullptr;
  while (_parser->GetDSAMeasObservedValueToPublish(&dsa_meas_observed_value_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&dsa_meas_observed_value_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set DSA Meas Observed Value source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_dsa_meas_observed_value_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because DSA Meas Observed Value Writer is a null pointer");
      break;
    }
    dds_retcode = _dsa_meas_observed_value_data_writer->write(*dsa_meas_observed_value_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write DSA Meas Observed Value Instance: Handle: " << dsa_meas_observed_value_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::DSA_MEAS_OBSERVED_VALUE_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published DSA Meas Observed Value Instance: Handle: " << dsa_meas_observed_value_instance->handle << std::endl);
    _parser->SetDSAMeasObservedValueAsPublished(index);
  }
  ice::DSAContext* dsa_calc_context_instance = nullptr;
  while (_parser->GetDSACalcContextToPublish(&dsa_calc_context_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&dsa_calc_context_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set DSA Calc Context source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_dsa_calc_context_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because DSA Calc Context Writer is a null pointer");
      break;
    }
    dds_retcode = _dsa_calc_context_data_writer->write(*dsa_calc_context_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write DSA Calc Context Instance: Handle: " << dsa_calc_context_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::DSA_CALC_CONTEXT_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published DSA Calc Context Instance: Handle: " << dsa_calc_context_instance->handle << std::endl);
    _parser->SetDSACalcContextAsPublished(index);
  }
  ice::DSAObservedValue* dsa_calc_observed_value_instance = nullptr;
  while (_parser->GetDSACalcObservedValueToPublish(&dsa_calc_observed_value_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&dsa_calc_observed_value_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set DSA Calc Observed Value source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_dsa_calc_observed_value_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because DSA Calc Observed Value Writer is a null pointer");
      break;
    }
    dds_retcode = _dsa_calc_observed_value_data_writer->write(*dsa_calc_observed_value_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write DSA Calc Observed Value Instance: Handle: " << dsa_calc_observed_value_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::DSA_CALC_OBSERVED_VALUE_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published DSA Calc Observed Value Instance: Handle: " << dsa_calc_observed_value_instance->handle << std::endl);
    _parser->SetDSACalcObservedValueAsPublished(index);
  }
  ice::DSAContext* dsa_sett_context_instance = nullptr;
  while (_parser->GetDSASettContextToPublish(&dsa_sett_context_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&dsa_sett_context_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set DSA Sett Context source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_dsa_sett_context_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because DSA Sett Context Writer is a null pointer");
      break;
    }
    dds_retcode = _dsa_sett_context_data_writer->write(*dsa_sett_context_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write DSA Sett Context Instance: Handle: " << dsa_sett_context_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::DSA_SETT_CONTEXT_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published DSA Sett Context Instance: Handle: " << dsa_sett_context_instance->handle << std::endl);
    _parser->SetDSASettContextAsPublished(index);
  }
  ice::DSAObservedValue* dsa_sett_observed_value_instance = nullptr;
  while (_parser->GetDSASettObservedValueToPublish(&dsa_sett_observed_value_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&dsa_sett_observed_value_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set DSA Sett Observed Value source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_dsa_sett_observed_value_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because DSA Sett Observed Value Writer is a null pointer");
      break;
    }
    dds_retcode = _dsa_sett_observed_value_data_writer->write(*dsa_sett_observed_value_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write DSA Sett Observed Value Instance: Handle: " << dsa_sett_observed_value_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::DSA_SETT_OBSERVED_VALUE_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published DSA Sett Observed Value Instance: Handle: " << dsa_sett_observed_value_instance->handle << std::endl);
    _parser->SetDSASettObservedValueAsPublished(index);
  }

  ice::EnumerationContext* enumeration_meas_context_instance = nullptr;
  while (_parser->GetEnumerationMeasContextToPublish(&enumeration_meas_context_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&enumeration_meas_context_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Enumeration Meas Context source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_enumeration_meas_context_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Enumeration Meas Context Writer is a null pointer");
      break;
    }
    dds_retcode = _enumeration_meas_context_data_writer->write(*enumeration_meas_context_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Enumeration Meas Context Instance: Handle: " << enumeration_meas_context_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::ENUMERATION_MEAS_CONTEXT_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Enumeration Meas Context Instance: Handle: " << enumeration_meas_context_instance->handle << std::endl);
    _parser->SetEnumerationMeasContextAsPublished(index);
  }
  ice::EnumerationObservedValue* enumeration_meas_observed_value_instance = nullptr;
  while (_parser->GetEnumerationMeasObservedValueToPublish(&enumeration_meas_observed_value_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&enumeration_meas_observed_value_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Enumeration Meas Observed Value source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_enumeration_meas_observed_value_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Enumeration Meas Observed Value Writer is a null pointer");
      break;
    }
    dds_retcode = _enumeration_meas_observed_value_data_writer->write(*enumeration_meas_observed_value_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Enumeration Meas Observed Value Instance: Handle: " << enumeration_meas_observed_value_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::ENUMERATION_MEAS_OBSERVED_VALUE_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Enumeration Meas Observed Value Instance: Handle: " << enumeration_meas_observed_value_instance->handle << std::endl);
    _parser->SetEnumerationMeasObservedValueAsPublished(index);
  }
  ice::EnumerationContext* enumeration_calc_context_instance = nullptr;
  while (_parser->GetEnumerationCalcContextToPublish(&enumeration_calc_context_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&enumeration_calc_context_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Enumeration Calc Context source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_enumeration_calc_context_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Enumeration Calc Context Writer is a null pointer");
      break;
    }
    dds_retcode = _enumeration_calc_context_data_writer->write(*enumeration_calc_context_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Enumeration Calc Context Instance: Handle: " << enumeration_calc_context_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::ENUMERATION_CALC_CONTEXT_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Enumeration Calc Context Instance: Handle: " << enumeration_calc_context_instance->handle << std::endl);
    _parser->SetEnumerationCalcContextAsPublished(index);
  }
  ice::EnumerationObservedValue* enumeration_calc_observed_value_instance = nullptr;
  while (_parser->GetEnumerationCalcObservedValueToPublish(&enumeration_calc_observed_value_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&enumeration_calc_observed_value_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Enumeration Calc Observed Value source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_enumeration_calc_observed_value_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Enumeration Calc Observed Value Writer is a null pointer");
      break;
    }
    dds_retcode = _enumeration_calc_observed_value_data_writer->write(*enumeration_calc_observed_value_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Enumeration Calc Observed Value Instance: Handle: " << enumeration_calc_observed_value_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::ENUMERATION_CALC_OBSERVED_VALUE_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Enumeration Calc Observed Value Instance: Handle: " << enumeration_calc_observed_value_instance->handle << std::endl);
    _parser->SetEnumerationCalcObservedValueAsPublished(index);
  }
  ice::EnumerationContext* enumeration_sett_context_instance = nullptr;
  while (_parser->GetEnumerationSettContextToPublish(&enumeration_sett_context_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&enumeration_sett_context_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Enumeration Sett Context source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_enumeration_sett_context_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Enumeration Sett Context Writer is a null pointer");
      break;
    }
    dds_retcode = _enumeration_sett_context_data_writer->write(*enumeration_sett_context_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Enumeration Sett Context Instance: Handle: " << enumeration_sett_context_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::ENUMERATION_SETT_CONTEXT_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Enumeration Sett Context Instance: Handle: " << enumeration_sett_context_instance->handle << std::endl);
    _parser->SetEnumerationSettContextAsPublished(index);
  }
  ice::EnumerationObservedValue* enumeration_sett_observed_value_instance = nullptr;
  while (_parser->GetEnumerationSettObservedValueToPublish(&enumeration_sett_observed_value_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&enumeration_sett_observed_value_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Enumeration Sett Observed Value source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_enumeration_sett_observed_value_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Enumeration Sett Observed Value Writer is a null pointer");
      break;
    }
    dds_retcode = _enumeration_sett_observed_value_data_writer->write(*enumeration_sett_observed_value_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Enumeration Sett Observed Value Instance: Handle: " << enumeration_sett_observed_value_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::ENUMERATION_SETT_OBSERVED_VALUE_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Enumeration Sett Observed Value Instance: Handle: " << enumeration_sett_observed_value_instance->handle << std::endl);
    _parser->SetEnumerationSettObservedValueAsPublished(index);
  }

  ice::NumericContext* numeric_meas_context_instance = nullptr;
  while (_parser->GetNumericMeasContextToPublish(&numeric_meas_context_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&numeric_meas_context_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Numeric Meas Context source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_numeric_meas_context_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Numeric Meas Context Writer is a null pointer");
      break;
    }
    dds_retcode = _numeric_meas_context_data_writer->write(*numeric_meas_context_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Numeric Meas Context Instance: Handle: " << numeric_meas_context_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::NUMERIC_MEAS_CONTEXT_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Numeric Meas Context Instance: Handle: " << numeric_meas_context_instance->handle << std::endl);
    _parser->SetNumericMeasContextAsPublished(index);
  }
  ice::NumericObservedValue* numeric_meas_observed_value_instance = nullptr;
  while (_parser->GetNumericMeasObservedValueToPublish(&numeric_meas_observed_value_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&numeric_meas_observed_value_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Numeric Meas Observed Value source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_numeric_meas_observed_value_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Numeric Meas Observed Value Writer is a null pointer");
      break;
    }
    dds_retcode = _numeric_meas_observed_value_data_writer->write(*numeric_meas_observed_value_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Numeric Meas Observed Value Instance: Handle: " << numeric_meas_observed_value_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::NUMERIC_MEAS_OBSERVED_VALUE_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Numeric Meas Observed Value Instance: Handle: " << numeric_meas_observed_value_instance->handle << std::endl);
    _parser->SetNumericMeasObservedValueAsPublished(index);
  }
  ice::NumericContext* numeric_calc_context_instance = nullptr;
  while (_parser->GetNumericCalcContextToPublish(&numeric_calc_context_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&numeric_calc_context_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Numeric Calc Context source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_numeric_calc_context_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Numeric Calc Context Writer is a null pointer");
      break;
    }
    dds_retcode = _numeric_calc_context_data_writer->write(*numeric_calc_context_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Numeric Calc Context Instance: Handle: " << numeric_calc_context_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::NUMERIC_CALC_CONTEXT_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Numeric Calc Context Instance: Handle: " << numeric_calc_context_instance->handle << std::endl);
    _parser->SetNumericCalcContextAsPublished(index);
  }
  ice::NumericObservedValue* numeric_calc_observed_value_instance = nullptr;
  while (_parser->GetNumericCalcObservedValueToPublish(&numeric_calc_observed_value_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&numeric_calc_observed_value_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Numeric Calc Observed Value source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_numeric_calc_observed_value_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Numeric Calc Observed Value Writer is a null pointer");
      break;
    }
    dds_retcode = _numeric_calc_observed_value_data_writer->write(*numeric_calc_observed_value_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Numeric Calc Observed Value Instance: Handle: " << numeric_calc_observed_value_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::NUMERIC_CALC_OBSERVED_VALUE_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Numeric Calc Observed Value Instance: Handle: " << numeric_calc_observed_value_instance->handle << std::endl);
    _parser->SetNumericCalcObservedValueAsPublished(index);
  }
  ice::NumericContext* numeric_sett_context_instance = nullptr;
  while (_parser->GetNumericSettContextToPublish(&numeric_sett_context_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&numeric_sett_context_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Numeric Sett Context source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_numeric_sett_context_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Numeric Sett Context Writer is a null pointer");
      break;
    }
    dds_retcode = _numeric_sett_context_data_writer->write(*numeric_sett_context_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Numeric Sett Context Instance: Handle: " << numeric_sett_context_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::NUMERIC_SETT_CONTEXT_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Numeric Sett Context Instance: Handle: " << numeric_sett_context_instance->handle << std::endl);
    _parser->SetNumericSettContextAsPublished(index);
  }
  ice::NumericObservedValue* numeric_sett_observed_value_instance = nullptr;
  while (_parser->GetNumericSettObservedValueToPublish(&numeric_sett_observed_value_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&numeric_sett_observed_value_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Numeric Sett Observed Value source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_numeric_sett_observed_value_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Numeric Sett Observed Value Writer is a null pointer");
      break;
    }
    dds_retcode = _numeric_sett_observed_value_data_writer->write(*numeric_sett_observed_value_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Numeric Sett Observed Value Instance: Handle: " << numeric_sett_observed_value_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::NUMERIC_SETT_OBSERVED_VALUE_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Numeric Sett Observed Value Instance: Handle: " << numeric_sett_observed_value_instance->handle << std::endl);
    _parser->SetNumericSettObservedValueAsPublished(index);
  }

  ice::RTSAContext* rtsa_meas_context_instance = nullptr;
  while (_parser->GetRTSAMeasContextToPublish(&rtsa_meas_context_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&rtsa_meas_context_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set RTSA Meas Context source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_rtsa_meas_context_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because RTSA Meas Context Writer is a null pointer");
      break;
    }
    dds_retcode = _rtsa_meas_context_data_writer->write(*rtsa_meas_context_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write RTSA Meas Context Instance: Handle: " << rtsa_meas_context_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::RTSA_MEAS_CONTEXT_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published RTSA Meas Context Instance: Handle: " << rtsa_meas_context_instance->handle << std::endl);
    _parser->SetRTSAMeasContextAsPublished(index);
  }
  ice::RTSAObservedValue* rtsa_meas_observed_value_instance = nullptr;
  while (_parser->GetRTSAMeasObservedValueToPublish(&rtsa_meas_observed_value_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&rtsa_meas_observed_value_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set RTSA Meas Observed Value source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_rtsa_meas_observed_value_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because RTSA Meas Observed Value Writer is a null pointer");
      break;
    }
    dds_retcode = _rtsa_meas_observed_value_data_writer->write(*rtsa_meas_observed_value_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write RTSA Meas Observed Value Instance: Handle: " << rtsa_meas_observed_value_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::RTSA_MEAS_OBSERVED_VALUE_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published RTSA Meas Observed Value Instance: Handle: " << rtsa_meas_observed_value_instance->handle << std::endl);
    _parser->SetRTSAMeasObservedValueAsPublished(index);
  }
  ice::RTSAContext* rtsa_calc_context_instance = nullptr;
  while (_parser->GetRTSACalcContextToPublish(&rtsa_calc_context_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&rtsa_calc_context_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set RTSA Calc Context source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_rtsa_calc_context_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because RTSA Calc Context Writer is a null pointer");
      break;
    }
    dds_retcode = _rtsa_calc_context_data_writer->write(*rtsa_calc_context_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write RTSA Calc Context Instance: Handle: " << rtsa_calc_context_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::RTSA_CALC_CONTEXT_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published RTSA Calc Context Instance: Handle: " << rtsa_calc_context_instance->handle << std::endl);
    _parser->SetRTSACalcContextAsPublished(index);
  }
  ice::RTSAObservedValue* rtsa_calc_observed_value_instance = nullptr;
  while (_parser->GetRTSACalcObservedValueToPublish(&rtsa_calc_observed_value_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&rtsa_calc_observed_value_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set RTSA Calc Observed Value source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_rtsa_calc_observed_value_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because RTSA Calc Observed Value Writer is a null pointer");
      break;
    }
    dds_retcode = _rtsa_calc_observed_value_data_writer->write(*rtsa_calc_observed_value_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write RTSA Calc Observed Value Instance: Handle: " << rtsa_calc_observed_value_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::RTSA_CALC_OBSERVED_VALUE_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published RTSA Calc Observed Value Instance: Handle: " << rtsa_calc_observed_value_instance->handle << std::endl);
    _parser->SetRTSACalcObservedValueAsPublished(index);
  }
  ice::RTSAContext* rtsa_sett_context_instance = nullptr;
  while (_parser->GetRTSASettContextToPublish(&rtsa_sett_context_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&rtsa_sett_context_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set RTSA Sett Context source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_rtsa_sett_context_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because RTSA Sett Context Writer is a null pointer");
      break;
    }
    dds_retcode = _rtsa_sett_context_data_writer->write(*rtsa_sett_context_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write RTSA Sett Context Instance: Handle: " << rtsa_sett_context_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::RTSA_SETT_CONTEXT_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published RTSA Sett Context Instance: Handle: " << rtsa_sett_context_instance->handle << std::endl);
    _parser->SetRTSASettContextAsPublished(index);
  }
  ice::RTSAObservedValue* rtsa_sett_observed_value_instance = nullptr;
  while (_parser->GetRTSASettObservedValueToPublish(&rtsa_sett_observed_value_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&rtsa_sett_observed_value_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set RTSA Sett Observed Value source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_rtsa_sett_observed_value_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because RTSA Sett Observed Value Writer is a null pointer");
      break;
    }
    dds_retcode = _rtsa_sett_observed_value_data_writer->write(*rtsa_sett_observed_value_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write RTSA Sett Observed Value Instance: Handle: " << rtsa_sett_observed_value_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::RTSA_SETT_OBSERVED_VALUE_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published RTSA Sett Observed Value Instance: Handle: " << rtsa_sett_observed_value_instance->handle << std::endl);
    _parser->SetRTSASettObservedValueAsPublished(index);
  }

  ice::TSAContext* tsa_meas_context_instance = nullptr;
  while (_parser->GetTSAMeasContextToPublish(&tsa_meas_context_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&tsa_meas_context_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set TSA Meas Context source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_tsa_meas_context_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because TSA Meas Context Writer is a null pointer");
      break;
    }
    dds_retcode = _tsa_meas_context_data_writer->write(*tsa_meas_context_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write TSA Meas Context Instance: Handle: " << tsa_meas_context_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::TSA_MEAS_CONTEXT_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published TSA Meas Context Instance: Handle: " << tsa_meas_context_instance->handle << std::endl);
    _parser->SetTSAMeasContextAsPublished(index);
  }
  ice::TSAObservedValue* tsa_meas_observed_value_instance = nullptr;
  while (_parser->GetTSAMeasObservedValueToPublish(&tsa_meas_observed_value_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&tsa_meas_observed_value_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set TSA Meas Observed Value source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_tsa_meas_observed_value_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because TSA Meas Observed Value Writer is a null pointer");
      break;
    }
    dds_retcode = _tsa_meas_observed_value_data_writer->write(*tsa_meas_observed_value_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write TSA Meas Observed Value Instance: Handle: " << tsa_meas_observed_value_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::TSA_MEAS_OBSERVED_VALUE_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published TSA Meas Observed Value Instance: Handle: " << tsa_meas_observed_value_instance->handle << std::endl);
    _parser->SetTSAMeasObservedValueAsPublished(index);
  }
  ice::TSAContext* tsa_calc_context_instance = nullptr;
  while (_parser->GetTSACalcContextToPublish(&tsa_calc_context_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&tsa_calc_context_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set TSA Calc Context source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_tsa_calc_context_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because TSA Calc Context Writer is a null pointer");
      break;
    }
    dds_retcode = _tsa_calc_context_data_writer->write(*tsa_calc_context_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write TSA Calc Context Instance: Handle: " << tsa_calc_context_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::TSA_CALC_CONTEXT_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published TSA Calc Context Instance: Handle: " << tsa_calc_context_instance->handle << std::endl);
    _parser->SetTSACalcContextAsPublished(index);
  }
  ice::TSAObservedValue* tsa_calc_observed_value_instance = nullptr;
  while (_parser->GetTSACalcObservedValueToPublish(&tsa_calc_observed_value_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&tsa_calc_observed_value_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set TSA Calc Observed Value source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_tsa_calc_observed_value_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because TSA Calc Observed Value Writer is a null pointer");
      break;
    }
    dds_retcode = _tsa_calc_observed_value_data_writer->write(*tsa_calc_observed_value_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write TSA Calc Observed Value Instance: Handle: " << tsa_calc_observed_value_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::TSA_CALC_OBSERVED_VALUE_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published TSA Calc Observed Value Instance: Handle: " << tsa_calc_observed_value_instance->handle << std::endl);
    _parser->SetTSACalcObservedValueAsPublished(index);
  }
  ice::TSAContext* tsa_sett_context_instance = nullptr;
  while (_parser->GetTSASettContextToPublish(&tsa_sett_context_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&tsa_sett_context_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set TSA Sett Context source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_tsa_sett_context_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because TSA Sett Context Writer is a null pointer");
      break;
    }
    dds_retcode = _tsa_sett_context_data_writer->write(*tsa_sett_context_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write TSA Sett Context Instance: Handle: " << tsa_sett_context_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::TSA_SETT_CONTEXT_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published TSA Sett Context Instance: Handle: " << tsa_sett_context_instance->handle << std::endl);
    _parser->SetTSASettContextAsPublished(index);
  }
  ice::TSAObservedValue* tsa_sett_observed_value_instance = nullptr;
  while (_parser->GetTSASettObservedValueToPublish(&tsa_sett_observed_value_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&tsa_sett_observed_value_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set TSA Sett Observed Value source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_tsa_sett_observed_value_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because TSA Sett Observed Value Writer is a null pointer");
      break;
    }
    dds_retcode = _tsa_sett_observed_value_data_writer->write(*tsa_sett_observed_value_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write TSA Sett Observed Value Instance: Handle: " << tsa_sett_observed_value_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::TSA_SETT_OBSERVED_VALUE_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published TSA Sett Observed Value Instance: Handle: " << tsa_sett_observed_value_instance->handle << std::endl);
    _parser->SetTSASettObservedValueAsPublished(index);
  }

  ice::PatientIdentification* patient_identification_instance = nullptr;
  while (_parser->GetPatientIdentificationToPublish(&patient_identification_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&patient_identification_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Patient Identification source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_patient_identification_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Patient Identification Writer is a null pointer");
      break;
    }
    dds_retcode = _patient_identification_data_writer->write(*patient_identification_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Patient Identification Instance: Handle: " << patient_identification_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::PATIENT_IDENTIFICATION_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Patient Identification Instance: Handle: " << patient_identification_instance->handle << std::endl);
    _parser->SetPatientIdentificationAsPublished(index);
  }
  ice::PatientDemographics* patient_demographics_instance = nullptr;
  while (_parser->GetPatientDemographicsToPublish(&patient_demographics_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&patient_demographics_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Patient Demographics source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_patient_demographics_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Patient Demographics Writer is a null pointer");
      break;
    }
    dds_retcode = _patient_demographics_data_writer->write(*patient_demographics_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Patient Demographics Instance: Handle: " << patient_demographics_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::PATIENT_DEMOGRAPHICS_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Patient Demographics Instance: Handle: " << patient_demographics_instance->handle << std::endl);
    _parser->SetPatientDemographicsAsPublished(index);
  }
  ice::Allergy* allergy_instance = nullptr;
  while (_parser->GetAllergyToPublish(&allergy_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&allergy_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Allergy source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_allergy_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Allergy Writer is a null pointer");
      break;
    }
    dds_retcode = _allergy_data_writer->write(*allergy_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Allergy Instance: Handle: " << allergy_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::ALLERGY_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Allergy Instance: Handle: " << allergy_instance->handle << std::endl);
    _parser->SetAllergyAsPublished(index);
  }
  expr::Diagnosis* diagnosis_instance = nullptr;
  while (_parser->GetDiagnosisToPublish(&diagnosis_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&diagnosis_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Diagnosis source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_diagnosis_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Diagnosis Writer is a null pointer");
      break;
    }
    dds_retcode = _diagnosis_data_writer->write(*diagnosis_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Diagnosis Instance: Handle: " << diagnosis_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::DIAGNOSIS_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Diagnosis Instance: Handle: " << diagnosis_instance->handle << std::endl);
    _parser->SetDiagnosisAsPublished(index);
  }
  expr::DxHistory* dxhistory_instance = nullptr;
  while (_parser->GetDxHistoryToPublish(&dxhistory_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&dxhistory_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set DxHistory source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_dxhistory_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because DxHistory Writer is a null pointer");
      break;
    }
    dds_retcode = _dxhistory_data_writer->write(*dxhistory_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write DxHistory Instance: Handle: " << dxhistory_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::DXHISTORY_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published DxHistory Instance: Handle: " << dxhistory_instance->handle << std::endl);
    _parser->SetDxHistoryAsPublished(index);
  }
  expr::PatientMedication* medication_instance = nullptr;
  while (_parser->GetMedicationToPublish(&medication_instance, &index) == DicesRcDriver::OK)
  {
    if (DicesTime::GetTimeOfDayUtc(&medication_instance->source_timestamp) != 0)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to set Medication source_timestamp.");
      driver_retcode = DicesRcDriver::GET_TIME_OF_DAY_UTC_FAILURE;
    }
    if (!_patient_medication_data_writer)
    {
      LOG4CPLUS_INFO(data_logger, " Unable to write because Medication Writer is a null pointer");
      break;
    }
    dds_retcode = _patient_medication_data_writer->write(*medication_instance, DDS::HANDLE_NIL);
    if (dds_retcode != DDS::RETCODE_OK)
    {
      LOG4CPLUS_ERROR(data_logger, " Failed to write Medication Instance: Handle: " << medication_instance->handle << std::endl);
      driver_retcode = DicesRcDriver::PATIENT_MEDICATION_INSTANCE_WRITE_FAILURE;
    }
    LOG4CPLUS_INFO(data_logger, " Published Medication Instance: Handle: " << medication_instance->handle << std::endl);
    _parser->SetMedicationAsPublished(index);
  }

  return driver_retcode;
}

DicesRcDriver BusComm::ShutdownDDSObjects()
{
  DicesRcDriverStatus ds_retcode = _driver_status_handler.Shutdown();
  if (ds_retcode != DicesRcDriverStatus::OK)
  {
    LOG4CPLUS_ERROR(root_logger, " Failed to set Driver Status to Shutdown: "
      << DicesRcDriverStatusStatusMessage::DicesRcDriverStatusToString(ds_retcode));
    return DicesRcDriver::DRIVER_STATUS_SHUTDOWN_FAILURE;
  }
  ds_retcode = _driver_status_handler.DDSShutdown();
  if (ds_retcode != DicesRcDriverStatus::OK)
  {
    LOG4CPLUS_ERROR(root_logger, " Failed to shutdown Driver Status handler: "
      << DicesRcDriverStatusStatusMessage::DicesRcDriverStatusToString(ds_retcode));
    return DicesRcDriver::DRIVER_STATUS_HANDLER_SHUTDOWN_FAILURE;
  }

  DDS::ReturnCode_t dds_retcode = _participant->delete_contained_entities();
  if (dds_retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, " Failed to delete DDS entities.");
    return DicesRcDriver::DELETE_CONTAINED_ENTITIES_FAILURE;
  }

  dds_retcode = DDSTheParticipantFactory->delete_participant(_participant);
  if (dds_retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, " Failed to delete participant with the participant factory");
    return DicesRcDriver::DELETE_PARTICIPANT_FAILURE;
  }
  _participant = nullptr;

  dds_retcode = TheParticipantFactory->finalize_instance();
  if (dds_retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, " Failed to finalize instance with the participant factory");
    return DicesRcDriver::FINALIZE_INSTANCE_FAILURE;
  }

  return DicesRcDriver::OK;
}

DicesRcDriver BusComm::PublishDeviceDriverStateError()
{
  DicesRcDriverStatus ds_retcode = _driver_status_handler.Error();
  if (ds_retcode != DicesRcDriverStatus::OK)
  {
    LOG4CPLUS_ERROR(root_logger, " Failed to set Driver Status to Error: "
      << DicesRcDriverStatusStatusMessage::DicesRcDriverStatusToString(ds_retcode));
    return DicesRcDriver::DRIVER_STATUS_ERROR_FAILURE;
  }
  return DicesRcDriver::OK;
}
