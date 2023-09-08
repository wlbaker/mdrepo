#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>

#include <alarm.h>
#include <battery.h>
#include <channel.h>
#include <clock.h>
#include <cnote.h>
#include <cplan.h>
#include <enum.h>
#include <expr.h>
#include <location.h>
#include <mds.h>
#include <numeric.h>
#include <operator.h>
#include <patdemo.h>
#include <rtsa.h>
#include <trendevt.h>
#include <vmd.h>
#include <allergy.h>
#include <docbox.h>
#include <tsa.h>
#include <dsa.h>
#include <diagnostics.h>
#include "connection-factory.h"
#include "base-dao.h"


struct BaseDAO::impl
{
  static std::map<std::string,std::string> _topicTableMap;

  impl() = default;
  ~impl() = default;

  pqxx::connection* getConnection()
  {
    return ConnectionFactory::instance()->getConnection();
  }

  std::string getTableName(std::string topicName)
  {
    std::string emptyName;

    // lookup database table name
    auto topicTableMapIt = _topicTableMap.find(topicName);
    if (topicTableMapIt == _topicTableMap.end())
    {
      // error condition: no table found for topic
      return emptyName;
    }

    return topicTableMapIt->second;
  }
};

// map topic name to database table name
std::map<std::string,std::string> BaseDAO::impl::_topicTableMap =
{
  {ice::NumericMeasObservedValueTopic, "numeric_meas_observed_value"},
  {ice::NumericMeasContextTopic, "numeric_meas_context"},
  {ice::NumericMeasContextReqTopic, "numeric_meas_context_req"},
  {ice::NumericCalcObservedValueTopic, "numeric_calc_observed_value"},
  {ice::NumericCalcContextTopic, "numeric_calc_context"},
  {ice::NumericCalcContextReqTopic, "numeric_calc_context_req"},
  {ice::NumericSettObservedValueTopic, "numeric_sett_observed_value"},
  {ice::NumericSettObservedValueReqTopic, "numeric_sett_observed_value_req"},
  {ice::NumericSettContextTopic, "numeric_sett_context"},
  {ice::NumericSettContextReqTopic, "numeric_sett_context_req"},
  {ice::RTSAMeasObservedValueTopic, "rtsa_meas_observed_value"},
  {ice::RTSAMeasContextTopic, "rtsa_meas_context"},
  {ice::RTSAMeasContextReqTopic, "rtsa_meas_context_req"},
  {ice::RTSACalcObservedValueTopic, "rtsa_calc_observed_value"},
  {ice::RTSACalcContextTopic, "rtsa_calc_context"},
  {ice::RTSACalcContextReqTopic, "rtsa_calc_context_req"},
  {ice::RTSASettObservedValueTopic, "rtsa_sett_observed_value"},
  {ice::RTSASettContextTopic, "rtsa_sett_context"},
  {ice::RTSASettContextReqTopic, "rtsa_sett_context_req"},
  {ice::MDSTopic, "mds"},
  {ice::VMDTopic, "vmd"},
  {ice::ChannelTopic, "channel"},
  {ice::BatteryTopic, "battery"},
  {ice::ClockTopic, "clock"},
  {ice::ClockTopicReq, "clock_req"},
  {ice::PhysiologicalAlarmSignalTopic, "physiological_alarm_signal"},
  {ice::TechnicalAlarmSignalTopic, "technical_alarm_signal"},
  {ice::InformationSignalTopic, "information_signal"},
  {ice::ReminderSignalTopic, "reminder_signal"},
  {ice::PhysiologicalAlarmContextTopic, "physiological_alarm_context"},
  {ice::PhysiologicalAlarmContextReqTopic, "physiological_alarm_context_req"},
  {ice::TechnicalAlarmContextTopic, "technical_alarm_context"},
  {ice::TechnicalAlarmContextReqTopic, "technical_alarm_context_req"},
  {ice::EnumerationMeasContextTopic, "enum_meas_context"},
  {ice::EnumerationMeasContextReqTopic, "enum_meas_context_req"},
  {ice::EnumerationMeasObservedValueTopic, "enum_meas_observed_value"},
  {ice::EnumerationCalcContextTopic, "enum_calc_context"},
  {ice::EnumerationCalcContextReqTopic, "enum_calc_context_req"},
  {ice::EnumerationCalcObservedValueTopic, "enum_calc_observed_value"},
  {ice::EnumerationSettContextTopic, "enum_sett_context"},
  {ice::EnumerationSettContextReqTopic, "enum_sett_context_req"},
  {ice::EnumerationSettObservedValueTopic, "enum_sett_observed_value"},
  {ice::EnumerationSettObservedValueReqTopic, "enum_sett_observed_value_req"},
  {ice::PatientDemographicsTopic, "patient_demographics"},
  {ice::PatientDemographicsReqTopic, "patient_demographics_req"},
  {ice::PatientIdentificationTopic, "patient_identification"},
  {ice::PatientIdentificationReqTopic, "patient_identification_req"},
  {ice::PatientIdentificationObjTopic, "patient_identification_obj"},
  {ice::PatientIdentificationErrorTopic, "patient_identification_error"},
  {ice::OperatorTopic, "operator"},
  {ice::OperatorAuthenticationTopic, "operator_authentication"},
  {ice::OperatorAuthenticationObjTopic, "operator_authentication_obj"},
  {ice::OperatorAuthenticationReqTopic, "operator_authentication_req"},
  {ice::OperatorAuthenticationErrorTopic, "operator_authentication_error"},
  {ice::LocationTopic, "location"},
  {ice::LocationReqTopic, "location_req"},
  {ice::AllergyTopic, "allergy"},
  {ice::AllergyReqTopic, "allergy_req"},
  {docbox::TrendEventTopic, "trend_event"},
  {docbox::DeviceDriverStateTopic, "device_driver_state"},
  {docbox::DeviceDriverStateReqTopic, "device_driver_state_req"},
  {docbox::DeviceDriverStateObjTopic, "device_driver_state_obj"},
  {docbox::ModuleServiceIdentificationTopic, "module_service_identification"},
  {docbox::ModuleServiceIdentificationReqTopic, "module_service_identification_req"},
  {docbox::ModuleServiceStateTopic, "module_service_state"},
  {docbox::ModuleServiceStateReqTopic, "module_service_state_req"},
  {docbox::ModuleServiceStateObjTopic, "module_service_state_obj"},
  {docbox::DeviceDriverLauncherStateTopic, "device_driver_launcher_state"},
  {docbox::DeviceDriverLauncherStateReqTopic, "device_driver_launcher_state_req"},
  {docbox::DeviceDriverLauncherStateObjTopic, "device_driver_launcher_state_obj"},
  {docbox::InactivitySignalTopic, "inactivity_signal"},
  {docbox::LCDModuleStateTopic, "lcd_module_state"},
  {docbox::ModuleServiceFocusTopic, "module_service_focus"},
  {docbox::ModuleServiceFocusObjTopic, "module_service_focus_obj"},
  {docbox::ModuleServiceFocusReqTopic, "module_service_focus_req"},
  {docbox::ModuleServiceFocusErrorTopic, "module_service_focus_error"},
  {docbox::DriverManagerStateTopic, "driver_manager_state"},
  {docbox::DriverManagerStateReqTopic, "driver_manager_state_req"},
  {docbox::ModuleDisplayStateTopic, "module_display_state"},
  {docbox::ModuleDisplayStateReqTopic, "module_display_state_req"},
  {expr::PatientMedicationTopic, "patient_medication"},
  {expr::PatientMedicationReqTopic, "patient_medication_req"},
  {expr::DiagnosisTopic, "diagnosis"},
  {expr::DiagnosisReqTopic, "diagnosis_req"},
  {expr::DxHistoryTopic, "dxhistory"},
  {expr::DxHistoryReqTopic, "dxhistory_req"},
  {ice::TSAMeasContextTopic, "tsa_meas_context"},
  {ice::TSAMeasContextReqTopic, "tsa_meas_context_req"},
  {ice::TSACalcContextTopic, "tsa_calc_context"},
  {ice::TSACalcContextReqTopic, "tsa_calc_context_req"},
  {ice::TSASettContextTopic, "tsa_sett_context"},
  {ice::TSASettContextReqTopic, "tsa_sett_context_req"},
  {ice::TSAMeasObservedValueTopic, "tsa_meas_observed_value"},
  {ice::TSACalcObservedValueTopic, "tsa_calc_observed_value"},
  {ice::TSASettObservedValueTopic, "tsa_sett_observed_value"},
  {ice::DSAMeasContextTopic, "dsa_meas_context"},
  {ice::DSAMeasContextReqTopic, "dsa_meas_context_req"},
  {ice::DSACalcContextTopic, "dsa_calc_context"},
  {ice::DSACalcContextReqTopic, "dsa_calc_context_req"},
  {ice::DSASettContextTopic, "dsa_sett_context"},
  {ice::DSASettContextReqTopic, "dsa_sett_context_req"},
  {ice::DSAMeasObservedValueTopic, "dsa_meas_observed_value"},
  {ice::DSACalcObservedValueTopic, "dsa_calc_observed_value"},
  {ice::DSASettObservedValueTopic, "dsa_sett_observed_value"},
  {ice::ClinicalNoteBundleTopic, "clinical_note_bundle"},
  {ice::ClinicalNoteTopic, "clinical_note"},
  {ice::CarePlanTopic, "care_plan"},
  {ice::CarePlanActivityTopic, "care_plan_activity"},
  {ice::ObservationTopic, "observation"},
  {ice::ObservationComponentTopic, "observation_component"},
  {ice::DiagnosticReportTopic, "diagnostic_report"}
};

BaseDAO::BaseDAO() 
  :_pimpl(nullptr)
{
  static const char* sfn = "BaseDAO::BaseDAO() ";
  _pimpl = std::unique_ptr<impl>(new (std::nothrow) impl());
  if (!_pimpl)
  {
    LOG4CPLUS_ERROR(log4cplus::Logger::getRoot(), sfn << "Failed to create impl");
    return;
  }
}

BaseDAO::~BaseDAO()
{
}
    
pqxx::connection* BaseDAO::getConnection()
{
  return _pimpl->getConnection();
}

std::string BaseDAO::getTableName(std::string topicName)
{
  return _pimpl->getTableName(topicName);
}
