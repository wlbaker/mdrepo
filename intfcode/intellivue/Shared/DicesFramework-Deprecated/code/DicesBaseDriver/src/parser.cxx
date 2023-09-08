/*
 * File:   parser.cxx
 * Author: Robert England
 */

#include <iterator>

#include "parser.h"

#include "dices_rc_driver.h"

#include "alarm.h"
#include "alarmSupport.h"
#include "allergySupport.h"
#include "common.h"
#include "patdemoSupport.h"
#include "dsa.h"
#include "enum.h"
#include "enumSupport.h"
#include "exprSupport.h"
#include "mds.h"
#include "mdsSupport.h"
#include "numeric.h"
#include "numericSupport.h"
#include "rtsa.h"
#include "rtsaSupport.h"
#include "tsa.h"
#include "vmd.h"
#include "vmdSupport.h"

#include "ndds/ndds_namespace_cpp.h"

#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>

#include "Core/DatabaseConnection/connection-factory.h"

static const std::vector<std::string> top_fields = {
  // ice_id is provided by the command line
  "handle",
  "parent_handle"
  // source_timestamp is generated at write time
};
static const std::vector<std::string> vmo_fields = {
  "type_partition",
  "type_code",
};
static const std::vector<std::string> alarm_context_fields = {
  "alarm_source",
  "context_seq_number",
  "event_message",
  "initial_priority",
  "latch",
  "alarm_condition_seconds",
  "alarm_signal_generation_delay",
  "alarm_signal_inactivation_state",
  "auditory_alarm_signal_set_tbd",
  "alarm_paused_seconds",
  "audio_paused_seconds",
  "alarm_acknowledge_seconds",
  "alarm_condition_type",
  "alarm_condition_limit_type",
  "alarm_condition_limit_value",
  "alarm_condition_alarm_code",
  "alarm_condition_unit_code",
  "alarm_parameters",
  "alarm_preset_list_tbd",
  "escalation_list_type",
  "escalation_list_path",
  "visual_alarm_characteristics_type",
  "auditory_reminder_signal_seconds",
  "auditory_alarm_signal_db"
};
static const std::vector<std::string> metric_context_fields = {
  "metric_specification_duration_seconds",
  "metric_specification_duration_nanoseconds",
  "metric_specification_category",
  "metric_specification_access",
  "metric_specification_relevance",
  "max_delay_time_seconds",
  "max_delay_time_nanoseconds",
  "vmo_label_string",
  "vmo_source_list_vmo_type",
  "vmo_source_list_glb_handle_context_id",
  "vmo_source_list_glb_handle_handle",
  "metric_source_list",
  "unit_label_string",
  "msmt_site_list",
  "body_site_list",
  "metric_status",
  "measure_period_value",
  "measure_period_code",
  "averaging_period_value",
  "averaging_period_code",
  "start_time",
  "stop_time",
  "metric_calibration_cal_type",
  "metric_calibration_cal_state",
  "metric_calibration_cal_time",
  "color",
  "measurement_status",
  "metric_id",
  "metric_info_label_string",
  "substance_nomenclature_id",
  "substance_nomenclature_code",
  "substance_label_string"
};
static const std::vector<std::string> sample_array_context_fields = {
  "sa_specification_array_size",
  "sa_specification_sample_type_sample_size",
  "sa_specification_sample_type_significant_bits",
  "sa_specification_sample_type_signed_samples",
  "sa_specification_flags",
  "compression",
  "sa_marker_list_marker_id",
  "sa_marker_list_marker_val",
  "scale_and_range_specification_lower_absolute_value",
  "scale_and_range_specification_upper_absolute_value",
  "scale_and_range_specification_lower_scaled_value",
  "scale_and_range_specification_upper_scaled_value",
  "sa_physiological_range_lower_scaled_value",
  "sa_physiological_range_upper_scaled_value",
  "visual_grid_absolute_value",
  "visual_grid_scaled_value",
  "visual_grid_level",
  "sa_calibration_data_lower_absolute_value",
  "sa_calibration_data_upper_absolute_value",
  "sa_calibration_data_lower_scaled_value",
  "sa_calibration_data_upper_scaled_value",
  "sa_calibration_data_increment",
  "sa_calibration_data_cal_type",
  "filter_specification_filter_type",
  "filter_specification_filter_frequency",
  "filter_specification_filger_order",
  "filter_label_string",
  "sa_signal_frequency_low_edge_freq",
  "sa_signal_frequency_high_edge_freq",
  "sa_measure_resolution"
};
static const std::vector<std::string> dsa_context_fields = {
  "distribution_range_specification_first_element_value",
  "distribution_range_specification_last_element_value",
  "x_unit_code",
  "x_unit_label_string"
};
static const std::vector<std::string> enumeration_context_fields = {
  "enum_measure_range",
  "enum_measure_range_bits",
  "enum_measure_range_labels_value",
  "enum_measure_range_labels_label"
};
static const std::vector<std::string> vms_fields = {
  "system_type_partition",
  "system_type_code",
  "system_model_manufacturer",
  "system_model_model_number",
  "nomenclature_version_nom_major_version",
  "nomenclature_version_nom_minor_version",
  "system_capability",
  "system_specification_component_capab_id",
  "system_specification_component_spec"
};
static const std::vector<std::string> mds_fields = {
  "mds_status",
  "operating_mode",
  "date_and_time",
  "relative_time_seconds",
  "relative_time_nanoseconds",
  "power_status",
  "battery_level",
  "remaining_battery_minutes",
  "altitude_meters",
  "line_frequency"
};
static const std::vector<std::string> vmd_fields = {
  "instance_number",
  "measurement_principle",
  "locale_language",
  "locale_country",
  "locale_charset",
  "locale_str_spec_str_max_len",
  "locale_str_spec_str_flags",
  "vmo_label_string",
  "vmd_status",
  "position",
  "operating_hours",
  "operating_cycles",
  "vmd_model_manufacturer",
  "vmd_model_model_number",
  "production_specification_spec_type",
  "production_specification_component_id",
  "production_specification_prod_spec"
};
static const std::vector<std::string> numeric_context_fields = {
  "nu_measure_range_lower_value",
  "nu_measure_range_upper_value",
  "nu_physiological_range_lower_value",
  "nu_physiological_range_upper_value",
  "display_resolution_pre_point",
  "display_resolution_post_point",
  "accuracy"
};
static const std::vector<std::string> rtsa_context_fields = {
  "sample_period_seconds",
  "sample_period_nanoseconds",
  "sweep_speed_value",
  "sweep_speed_unit_code",
  "average_reporting_delay_seconds",
  "average_reporting_delay_nanoseconds",
  "sample_time_sync_seconds",
  "sample_time_sync_nanoseconds"
};
static const std::vector<std::string> tsa_context_fields = {
  "sample_period_seconds",
  "sample_period_nanoseconds",
  "sweep_speed_value",
  "sweep_speed_unit_code"
};

static const int kExpectedMDSTableColumnCount = 30;
static const int kExpectedVMDTableColumnCount = 26;
static const int kExpectedNumericContextsTableColumnCount = 53;
static const int kExpectedEnumContextsTableColumnCount = 50;
static const int kExpectedRTSAContextsTableColumnCount = 84;
static const int kExpectedAlarmsTableColumnCount = 33;
static const int kExpectedPatientIdentificationTableColumnCount = 17;
static const int kExpectedPatientDemographicsTableColumnCount = 37;
static const int kExpectedAllergyTableColumnCount = 39;
static const int kExpectedDiagnosisTableColumnCount = 24;
static const int kExpectedDxHistoryTableColumnCount = 26;
static const int kExpectedPatientMedicationTableColumnCount = 24;
static const int kExpectedOperatorTableColumnCount = 16;
static const int kExpectedOperatorAuthenticationErrorTableColumnCount = 9;
static const int kExpectedOperatorAuthenticationTableColumnCount = 9;
static const int kExpectedAppFocusStateTableColumnCount = 3;

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();
static const char* kTableMDS = "mds";
static const char* kTableVMD = "vmds";
static const char* kTableNumeric = "numeric_contexts";
static const char* kTableEnumeration = "enum_contexts";
static const char* kTableRTSA = "sample_array_contexts";
static const char* kTableAlarms = "alarms";
static const char* kTablePatientIdentification = "pat_idents";
static const char* kTablePatientIdentificationReq = "pat_ident_reqs";
static const char* kTablePatientDemographics = "pat_demos";
static const char* kTablePatientDemographicsReq = "pat_demo_reqs";
static const char* kTableAllergy = "allergies";
static const char* kTableAllergyReq = "allergy_reqs";
static const char* kTableDiagnosis = "diagnoses";
static const char* kTableDiagnosisReq = "diagnosis_reqs";
static const char* kTableDxHistory = "dx_histories";
static const char* kTableDxHistoryReq = "dx_history_reqs";
static const char* kTablePatientMedication = "patient_medications";
static const char* kTablePatientMedicationReq = "patient_medication_reqs";

static const std::string kHeaderColumnNames =
  "id, "
  "instance_name";
static const std::string kTopColumnNames =
  "ice_id, "
  "handle, "
  "parent_handle, "
  "source_timestamp_seconds, "
  "source_timestamp_nanoseconds";
static const std::string kVMOColumnNames =
  "type_partition, "
  "type_code";
static const std::string kVMSColumnNames =
  "system_type_partition, "
  "system_type_code, "
  "system_model_manufacturer, "
  "system_model_model_number, "
  "nomenclature_version_nom_major_version, "
  "nomenclature_version_nom_minor_version, "
  "system_capability, "
  "system_specification_component_capab_id, "
  "system_specification_component_spec, "
  "production_specification_spec_type, "
  "production_specification_component_id, "
  "production_specification_prod_spec";
static const std::string kMDSColumnNames =
  "mds_status, "
  "operating_mode, "
  "date_and_time_seconds, "
  "date_and_time_nanoseconds, "
  "relative_time_seconds, "
  "relative_time_nanoseconds, "
  "power_status, "
  "battery_level, "
  "remaining_battery_minutes, "
  "altitude_meters, "
  "line_frequency";
static const std::string kVMDColumnNames =
  "instance_number, "
  "measurement_principle, "
  "locale_language, "
  "locale_country, "
  "locale_charset, "
  "locale_str_spec_str_max_len, "
  "locale_str_spec_str_flags, "
  "vmo_label_string, "
  "vmd_status, "
  "position, "
  "operating_hours, "
  "operation_cycles, "
  "vmd_model_manufacturer, "
  "vmd_model_model_number, "
  "production_specification_spec_type, "
  "production_specification_component_id, "
  "production_specification_prod_spec";
static const std::string kMetricContextColumnNames =
  "context_seq_number, "
  "metric_specification_update_period_seconds, "
  "metric_specification_update_period_nanoseconds, "
  "metric_specification_category, "
  "metric_specification_access, "
  "metric_specification_relevance, "
  "max_delay_time_seconds, "
  "max_delay_time_nanoseconds, "
  "vmo_label_string, "
  "vmo_source_list_vmo_type, "
  "vmo_source_list_glb_handle_context_id, "
  "vmo_source_list_glb_handle_handle, "
  "metric_source_list, "
  "unit_code, "
  "unit_label_string, "
  "msmt_site_list, "
  "body_site_list, "
  "metric_status, "
  "measure_period_value, "
  "measure_period_unit_code, "
  "averaging_period_value, "
  "averaging_period_unit_code, "
  "start_time_seconds, "
  "start_time_nanoseconds, "
  "stop_time_seconds, "
  "stop_time_nanoseconds, "
  "metric_calibration_cal_type, "
  "metric_calibration_cal_state, "
  "metric_calibration_cal_time_seconds, "
  "metric_calibration_cal_time_nanoseconds, "
  "color, "
  "measurement_status, "
  "metric_id, "
  "metric_info_label_string, "
  "substance_nomenclature_id, "
  "substance_nomenclature_code, "
  "substance_label_string";
static const std::string kNumericContextColumnNames =
  "nu_measure_range_lower_value, "
  "nu_measure_range_upper_value, "
  "nu_physiological_range_lower_value, "
  "nu_physiological_range_upper_value, "
  "display_resolution_pre_point, "
  "display_resolution_post_point, "
  "accuracy";
static const std::string kEnumerationContextColumnNames =
  "enum_measure_range, "
  "enum_measure_range_bits, "
  "enum_measure_range_labels_value, "
  "enum_measure_range_labels_label";
static const std::string kSampleArrayContextColumnNames =
  "sa_specification_array_size, "
  "sa_specification_sample_type_sample_size, "
  "sa_specification_sample_type_significant_bits, "
  "sa_specification_sample_type_signed_samples, "
  "sa_specification_flags, "
  "compression, "
  "sa_marker_list_marker_id, "
  "sa_marker_list_marker_val, "
  "scale_and_range_specification_lower_absolute_value, "
  "scale_and_range_specification_upper_absolute_value, "
  "scale_and_range_specification_lower_scaled_value, "
  "scale_and_range_specification_upper_scaled_value, "
  "sa_physiological_range_lower_scaled_value, "
  "sa_physiological_range_upper_scaled_value, "
  "visual_grid_absolute_value, "
  "visual_grid_scaled_value, "
  "visual_grid_level, "
  "sa_calibration_data_lower_absolute_value, "
  "sa_calibration_data_upper_absolute_value, "
  "sa_calibration_data_lower_scaled_value, "
  "sa_calibration_data_upper_scaled_value, "
  "sa_calibration_data_increment, "
  "sa_calibration_data_cal_type, "
  "filter_specification_filter_type, "
  "filter_specification_filter_frequency, "
  "filter_specification_filter_order, "
  "filter_label_string, "
  "sa_signal_frequency_low_edge_freq, "
  "sa_signal_frequency_high_edge_freq, "
  "sa_measure_resolution";
static const std::string kRTSAContextColumnNames =
  "sample_period_seconds, "
  "sample_period_nanoseconds, "
  "sweep_speed_value, "
  "sweep_speed_unit_code, "
  "average_reporting_delay_seconds, "
  "average_reporting_delay_nanoseconds, "
  "sample_time_sync_seconds, "
  "sample_time_sync_nanoseconds";
static const std::string kAlarmContextColumnNames =
  "alarm_source, "
  "context_seq_number, "
  " event_message , "
  "initial_priority, "
  "latch, "
  "alarm_condition_seconds, "
  "alarm_signal_generation_delay, "
  "alarm_signal_inactivation_state, "
  "auditory_alarm_signal_set_tbd, "
  "alarm_paused_seconds, "
  "audio_paused_seconds, "
  "alarm_acknowledge_seconds, "
  "alarm_condition_type, "
  "alarm_condition_limit_type, "
  "alarm_condition_limit_value, "
  "alarm_condition_alarm_code, "
  "alarm_condition_unit_code, "
  "alarm_parameters, "
  "alarm_preset_list_tbd, "
  "escalation_list_type, "
  "escalation_list_path, "
  "visual_alarm_characteristics_type, "
  "auditory_reminder_signal_seconds, "
  "auditory_alarm_signal_db";
static const std::string kPatientIdentificationColumnNames =
  "given_name, "
  "family_name, "
  "middle_name , "
  "date_of_birth_century, "
  "date_of_birth_year, "
  "date_of_birth_month, "
  "date_of_birth_day, "
  "patient_id, "
  "patient_id_provenance, "
  "verified, "
  "pat_admit_state, "
  "pat_episode_id, "
  "episode_start_seconds, "
  "episode_start_nanoseconds";
static const std::string kPatientDemographicsColumnNames =
  "sex, "
  "gender, "
  "race_race_type, "
  "race_provenance, "
  "patient_type, "
  "chronological_age_value, "
  "chronological_age_m_unit, "
  "patient_height_value, "
  "patient_height_m_unit, "
  "patient_weight_value, "
  "patient_weight_m_unit, "
  "neonatal_gestational_age_value, "
  "neonatal_gestational_age_m_unit, "
  "neonatal_patient_birth_length_value, "
  "neonatal_patient_birth_length_m_unit, "
  "neonatal_patient_birth_weight_value, "
  "neonatal_patient_birth_weight_m_unit, "
  "neonatal_patient_head_circumference_value, "
  "neonatal_patient_head_circumference_m_unit, "
  "neonatal_mother_patient_id_given_name, "
  "neonatal_mother_patient_id_family_name, "
  "neonatal_mother_patient_id_middle_name, "
  "neonatal_mother_patient_id_date_of_birth_century, "
  "neonatal_mother_patient_id_date_of_birth_year, "
  "neonatal_mother_patient_id_date_of_birth_month, "
  "neonatal_mother_patient_id_date_of_birth_day, "
  "neonatal_mother_patient_id_patient_id, "
  "neonatal_mother_patient_id_patient_id_provenance, "
  "neonatal_mother_patient_id_verified, "
  "neonatal_mother_patient_id_pat_admit_state, "
  "neonatal_mother_patient_id_pat_episode_id, "
  "neonatal_mother_patient_id_episode_start_seconds, "
  "neonatal_mother_patient_id_episode_start_nanoseconds, "
  "neonatal_mother_name";
static const std::string kAllergyColumnNames =
  "patient_id_given_name, "
  "patient_id_family_name, "
  "patient_id_middle_name, "
  "patient_id_date_of_birth_century, "
  "patient_id_date_of_birth_year, "
  "patient_id_date_of_birth_month, "
  "patient_id_date_of_birth_day, "
  "patient_id_patient_id, "
  "patient_id_patient_id_provenance, "
  "patient_id_verified, "
  "patient_id_pat_admit_state, "
  "patient_id_pat_episode_id, "
  "patient_id_episode_start_seconds, "
  "patient_id_episode_start_nanoseconds, "
  "adverse_event_count, "
  "adverse_events_adverse_event_date_century, "
  "adverse_events_adverse_event_date_year, "
  "adverse_events_adverse_event_date_month, "
  "adverse_events_adverse_event_date_day, "
  "adverse_events_adverse_event_type, "
  "adverse_events_coded_product_code_system_pair_code_system_ident, "
  "adverse_events_coded_product_code_system_pair_code_system_name, "
  "adverse_events_coded_product_code, "
  "adverse_events_coded_product_label, "
  "adverse_events_free_text_product, "
  "adverse_events_rxns_coded_rxn_code_sys_pair_code_sys_id, "
  "adverse_events_rxns_coded_rxn_code_sys_pair_code_sys_name, "
  "adverse_events_reactions_coded_reaction_code, "
  "adverse_events_reactions_coded_reaction_label, "
  "adverse_events_reactions_free_text_reaction, "
  "adverse_events_reactions_severity_coded_severity, "
  "adverse_events_reactions_severity_free_text_severity";
static const std::string kDiagnosisColumnNames =
  "diagnosis, "
  "procedure, "
  "physician, "
  "patient_identification_given_name, "
  "patient_identification_family_name, "
  "patient_identification_middle_name, "
  "patient_identification_date_of_birth_century, "
  "patient_identification_date_of_birth_year, "
  "patient_identification_date_of_birth_month, "
  "patient_identification_date_of_birth_day, "
  "patient_identification_patient_id, "
  "patient_identification_patient_id_provenance, "
  "patient_identification_verified, "
  "patient_identification_pat_admit_state, "
  "patient_identification_pat_episode_id, "
  "patient_identification_episode_start_seconds, "
  "patient_identification_episode_start_nanoseconds";
static const std::string kDxHistoryColumnNames =
  "health_problem, "
  "recent_procedure, "
  "patient_identification_given_name, "
  "patient_identification_family_name, "
  "patient_identification_middle_name, "
  "patient_identification_date_of_birth_century, "
  "patient_identification_date_of_birth_year, "
  "patient_identification_date_of_birth_month, "
  "patient_identification_date_of_birth_day, "
  "patient_identification_patient_id, "
  "patient_identification_patient_id_provenance, "
  "patient_identification_verified, "
  "patient_identification_pat_admit_state, "
  "patient_identification_pat_episode_id, "
  "patient_identification_episode_start_seconds, "
  "patient_identification_episode_start_nanoseconds, "
  "problem_count, "
  "problem_list, "
  "recent_procedures";
static const std::string kPatientMedicationColumnNames =
  "patient_identification_given_name, "
  "patient_identification_family_name, "
  "patient_identification_middle_name, "
  "patient_identification_date_of_birth_century, "
  "patient_identification_date_of_birth_year, "
  "patient_identification_date_of_birth_month, "
  "patient_identification_date_of_birth_day, "
  "patient_identification_patient_id, "
  "patient_identification_patient_id_provenance, "
  "patient_identification_verified, "
  "patient_identification_pat_admit_state, "
  "patient_identification_pat_episode_id, "
  "patient_identification_episode_start_seconds, "
  "patient_identification_episode_start_nanoseconds, "
  "medication_count, "
  "medication_list_name, "
  "medication_list_dose";

static const ice::SignalConditionType kDefaultSignalCondition =
  ice::SignalConditionType::technical_alarm_signal;

DicesRcDriver Parser::AllocateMessageBuffers()
{
  _raw_command = new (std::nothrow) uint8_t[get_max_command_length()];
  if (!_raw_command)
  {
    LOG4CPLUS_ERROR(root_logger, " Unable to allocate space for raw command buffer.");
    return DicesRcDriver::COMMAND_BUFFER_ALLOCATION_FAILURE;
  }

  _raw_response = new (std::nothrow) uint8_t[get_max_response_length()];
  if (!_raw_response)
  {
    LOG4CPLUS_ERROR(root_logger, " Unable to allocate space for raw response buffer.");
    return DicesRcDriver::RESPONSE_BUFFER_ALLOCATION_FAILURE;
  }
  return DicesRcDriver::OK;
}

std::set<CreateWriterName> Parser::get_create_writer_name_list()
{
  return _create_writer_name_list;
}

std::set<CreateReaderName> Parser::get_create_reader_name_list()
{
  return _create_reader_name_list;
}

DicesRcDriver Parser::set_ice_id(const std::string& ice_id)
{
  _ice_id = ice_id;
  return DicesRcDriver::OK;
}

std::string Parser::get_ice_id()
{
  return _ice_id;
}

DicesRcDriver Parser::SetICEID()
{
  for (std::pair<DicesRcDriver, ice::PatientIdentification*> &entry : _patient_identification_req_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::PatientDemographics*> &entry : _patient_demographics_req_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::AlarmSignal*> &entry : _physiological_alarm_signal_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::AlarmSignal*> &entry : _technical_alarm_signal_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::InformationSignal*> &entry : _information_signal_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::ReminderSignal*> &entry : _reminder_signal_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::AlarmContext*> &entry : _physiological_alarm_context_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::AlarmContext*> &entry : _technical_alarm_context_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }

  for (std::pair<DicesRcDriver, ice::DSAContext*> &entry : _dsa_meas_context_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::DSAObservedValue*> &entry : _dsa_meas_observed_value_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::DSAContext*> &entry : _dsa_calc_context_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::DSAObservedValue*> &entry : _dsa_calc_observed_value_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::DSAContext*> &entry : _dsa_sett_context_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::DSAObservedValue*> &entry : _dsa_sett_observed_value_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }

  for (std::pair<DicesRcDriver, ice::EnumerationContext*> &entry : _enumeration_meas_context_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::EnumerationObservedValue*> &entry : _enumeration_meas_observed_value_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::EnumerationContext*> &entry : _enumeration_calc_context_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::EnumerationObservedValue*> &entry : _enumeration_calc_observed_value_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::EnumerationContext*> &entry : _enumeration_sett_context_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::EnumerationObservedValue*> &entry : _enumeration_sett_observed_value_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }

  for (std::pair<DicesRcDriver, ice::MDS*> &entry : _mds_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::VMD*> &entry : _vmd_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }

  for (std::pair<DicesRcDriver, ice::NumericContext*> &entry : _numeric_meas_context_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::NumericObservedValue*> &entry : _numeric_meas_observed_value_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::NumericContext*> &entry : _numeric_calc_context_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::NumericObservedValue*> &entry : _numeric_calc_observed_value_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::NumericContext*> &entry : _numeric_sett_context_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::NumericObservedValue*> &entry : _numeric_sett_observed_value_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }

  for (std::pair<DicesRcDriver, ice::RTSAContext*> &entry : _rtsa_meas_context_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::RTSAObservedValue*> &entry : _rtsa_meas_observed_value_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::RTSAContext*> &entry : _rtsa_calc_context_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::RTSAObservedValue*> &entry : _rtsa_calc_observed_value_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::RTSAContext*> &entry : _rtsa_sett_context_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::RTSAObservedValue*> &entry : _rtsa_sett_observed_value_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }

  for (std::pair<DicesRcDriver, ice::TSAContext*> &entry : _tsa_meas_context_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::TSAObservedValue*> &entry : _tsa_meas_observed_value_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::TSAContext*> &entry : _tsa_calc_context_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::TSAObservedValue*> &entry : _tsa_calc_observed_value_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::TSAContext*> &entry : _tsa_sett_context_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::TSAObservedValue*> &entry : _tsa_sett_observed_value_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }

  for (std::pair<DicesRcDriver, ice::PatientIdentification*> &entry : _patient_identification_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::PatientDemographics*> &entry : _patient_demographics_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, ice::Allergy*> &entry : _allergy_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, expr::Diagnosis*> &entry : _diagnosis_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, expr::DxHistory*> &entry : _dxhistory_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }
  for (std::pair<DicesRcDriver, expr::PatientMedication*> &entry : _patient_medication_response_instance_list)
  {
    strncpy(entry.second->ice_id, _ice_id.c_str(), ice::MAX_LEN_ICE_ID);
    entry.second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  }

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::DeallocateMessageBuffers()
{
  delete [] _raw_command;
  _raw_command = 0;
  _command_length = 0;

  delete [] _raw_response;
  _raw_response = 0;
  _response_length = 0;

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::get_raw_command(uint8_t* buffer, int buf_length)
{
  if (buf_length < get_command_length())
  {
    LOG4CPLUS_ERROR(root_logger, " Input buffer to Parser::get_raw_command too short.");
    return DicesRcDriver::DESTINATION_TOO_SHORT_FAILURE;
  }

  memset(buffer, 0, buf_length);
  memcpy(buffer, _raw_command, get_command_length());

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::set_raw_response(const uint8_t* buffer, int buf_length)
{
  if (buf_length > get_max_response_length())
  {
    LOG4CPLUS_ERROR(root_logger, " Input buffer to Parser::set_raw_response too long.");
    return DicesRcDriver::ORIGIN_TOO_LONG_FAILURE;
  }

  memset(_raw_response, 0, get_max_response_length());
  memcpy(_raw_response, buffer, buf_length);
  _response_length = buf_length;

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ConnectToDatabase(
  const std::string& database_name,
  const std::string& database_user,
  const std::string& database_password,
  const std::string& database_host)
{
  static const char* sfn = "Parser::ConnectToDatabase() ";

  if (_database_connection)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Database connection is already open");
    return DicesRcDriver::OK;
  }

  // NOTE: The following statements overide the default database information
  // in the ConnectionFactory. If the defaults are important in the future,
  // then overload this function to make the function arguments optional
  ConnectionFactory::set_db_name(database_name);
  ConnectionFactory::set_db_user(database_user);
  ConnectionFactory::set_db_pwd(database_password);
  ConnectionFactory::set_host(database_host);

  _database_connection = ConnectionFactory::instance()->getConnection();
  if (!_database_connection)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to get database connection "
      "from ConnectionFactory to database \"" << database_name << "\"");
    return DicesRcDriver::DATABASE_CONNECTION_FAILURE;
  }

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::DisconnectFromDatabase()
{
  static const char* sfn = "Parser::DisconnectFromDatabase() ";

  if (_database_connection == nullptr)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Database is not connected");
    return DicesRcDriver::OK;
  }

  ConnectionFactory::instance()->Disconnect();

  _database_connection = nullptr;

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ConvertPostgresByteaHexToICEINTU8(
  const std::string& str_value,
  ice::INTU8* value)
{
  static const char* sfn = "Parser::ConvertPostgresByteaHexToICEINTU8() ";
  if (value == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument value is a null "
      "pointer");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }
  *value = 0;

  // Postgres bytea is binary data "byte array"
  // See Postgres documentation on bytea hex string format
  // Example: "\x34" is byte value 4

  const int kbyte_string_min_size = 2;
  if (str_value.size() < kbyte_string_min_size)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to parse ascii hexadecimal "
      "string \"" << str_value << "\". Must be at least size "
      << kbyte_string_min_size);
    return DicesRcDriver::DATABASE_OCTET_STRING_PARSE_FAILURE;
  }

  static const std::string kstr_prefix = "\\x";

  if (str_value.at(0) != kstr_prefix.at(0)
    || str_value.at(1) != kstr_prefix.at(1))
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to parse unknown bytea "
      "hexadecimal string format \"" << str_value << "\". Must be preceded by "
      "the sequence " << kstr_prefix);
    return DicesRcDriver::DATABASE_OCTET_STRING_PARSE_FAILURE;
  }

  std::string hex_ascii_char_str = str_value;

  // Erase prefix
  hex_ascii_char_str.erase(0, kstr_prefix.length());

  int sum_value = 0;
  const int kbyte_str_length = 2;

  if ((hex_ascii_char_str.size() % kbyte_str_length) != 0)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to parse unknown bytea "
      "hexadecimal string format \"" << hex_ascii_char_str << "\". Must be "
      << kbyte_str_length << " characters per byte");
    return DicesRcDriver::DATABASE_OCTET_STRING_PARSE_FAILURE;
  }

  for (int ix = 0; ix < hex_ascii_char_str.size(); ix += kbyte_str_length)
  {
    int curr_int = 0;

    // Convert hexadecimal string to decimal
    std::stringstream ss;
    std::string byte_str = hex_ascii_char_str.substr(ix, kbyte_str_length);
    ss << std::hex << byte_str;
    ss >> curr_int;

    if (ss.fail())
    {
      LOG4CPLUS_WARN(root_logger, sfn << "Failed to convert ascii hexadecimal "
        "string \"" << byte_str << "\" to integer.");
      return DicesRcDriver::DATABASE_OCTET_STRING_PARSE_FAILURE;
    }

    // Convert character to byte value
    std::string int_string(1, static_cast<char>(curr_int));
    std::istringstream iss(int_string);
    iss >> curr_int;

    if (iss.fail())
    {
      LOG4CPLUS_WARN(root_logger, sfn << "Failed to convert string "
        "\"" << int_string << "\" to integer. ");
      return DicesRcDriver::DATABASE_OCTET_STRING_PARSE_FAILURE;
    }

    // Example of what's happening below:
    // \x323535 converted to ascii characters: x32 = '2' x35 = '5' x35 = '5'
    // This is how a byte value of 255 is represented in the bytea data type
    // of Postgres. To get the result 255, we'll need to do a little math:
    // 2 x (10 ^ 2) = 200
    // 5 x (10 ^ 1) =  50
    // 5 x (10 ^ 0) =   5
    //               +___
    // Result:        255
    // In this example:
    // hex_ascii_char_str.size() = 6 (without prefix \x)
    // kbyte_str_length = 2
    // (ix / kbyte_str_length) starts at zero and increments by one with
    // each iteration of the loop.
    double exponent = (hex_ascii_char_str.size() / kbyte_str_length)
      - (ix / kbyte_str_length) - 1;
    double base = 10;
    curr_int *= pow(base, exponent);
    sum_value += curr_int;
  }

  *value = static_cast<ice::INTU8>(sum_value);
  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ReadFromDatabase()
{
  static const char* sfn = "Parser::ReadFromDatabase() ";

  DicesRcDriver status = DicesRcDriver::OK;
  status = ReadFromMDSTable();
  if (status != DicesRcDriver::OK)
  {
    if (status == DicesRcDriver::DATABASE_READ_TABLE_FAILURE)
    {
      LOG4CPLUS_WARN(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      status = DicesRcDriver::OK;
    }
    else
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
  }

  status = ReadFromVMDTable();
  if (status != DicesRcDriver::OK)
  {
    if (status == DicesRcDriver::DATABASE_READ_TABLE_FAILURE)
    {
      LOG4CPLUS_WARN(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      status = DicesRcDriver::OK;
    }
    else
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
  }

  status = ReadFromNumericTable();
  if (status != DicesRcDriver::OK)
  {
    if (status == DicesRcDriver::DATABASE_READ_TABLE_FAILURE)
    {
      LOG4CPLUS_WARN(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      status = DicesRcDriver::OK;
    }
    else
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
  }

  status = ReadFromEnumerationTable();
  if (status != DicesRcDriver::OK)
  {
    if (status == DicesRcDriver::DATABASE_READ_TABLE_FAILURE)
    {
      LOG4CPLUS_WARN(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      status = DicesRcDriver::OK;
    }
    else
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
  }

  status = ReadFromRTSATable();
  if (status != DicesRcDriver::OK)
  {
    if (status == DicesRcDriver::DATABASE_READ_TABLE_FAILURE)
    {
      LOG4CPLUS_WARN(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      status = DicesRcDriver::OK;
    }
    else
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
  }

  status = ReadFromAlarmsTable();
  if (status != DicesRcDriver::OK)
  {
    if (status == DicesRcDriver::DATABASE_READ_TABLE_FAILURE)
    {
      LOG4CPLUS_WARN(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      status = DicesRcDriver::OK;
    }
    else
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
  }

  status = ReadFromPatientIdentificationTable();
  if (status != DicesRcDriver::OK)
  {
    if (status == DicesRcDriver::DATABASE_READ_TABLE_FAILURE)
    {
      LOG4CPLUS_WARN(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      status = DicesRcDriver::OK;
    }
    else
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
  }

  status = ReadFromPatientIdentificationReqTable();
  if (status != DicesRcDriver::OK)
  {
    if (status == DicesRcDriver::DATABASE_READ_TABLE_FAILURE)
    {
      LOG4CPLUS_WARN(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      status = DicesRcDriver::OK;
    }
    else
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
  }

  status = ReadFromPatientDemographicsTable();
  if (status != DicesRcDriver::OK)
  {
    if (status == DicesRcDriver::DATABASE_READ_TABLE_FAILURE)
    {
      LOG4CPLUS_WARN(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      status = DicesRcDriver::OK;
    }
    else
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
  }

  status = ReadFromPatientDemographicsReqTable();
  if (status != DicesRcDriver::OK)
  {
    if (status == DicesRcDriver::DATABASE_READ_TABLE_FAILURE)
    {
      LOG4CPLUS_WARN(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      status = DicesRcDriver::OK;
    }
    else
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
  }

  status = ReadFromAllergyTable();
  if (status != DicesRcDriver::OK)
  {
    if (status == DicesRcDriver::DATABASE_READ_TABLE_FAILURE)
    {
      LOG4CPLUS_WARN(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      status = DicesRcDriver::OK;
    }
    else
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
  }

  status = ReadFromAllergyReqTable();
  if (status != DicesRcDriver::OK)
  {
    if (status == DicesRcDriver::DATABASE_READ_TABLE_FAILURE)
    {
      LOG4CPLUS_WARN(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      status = DicesRcDriver::OK;
    }
    else
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
  }

  status = ReadFromPatientMedicationTable();
  if (status != DicesRcDriver::OK)
  {
    if (status == DicesRcDriver::DATABASE_READ_TABLE_FAILURE)
    {
      LOG4CPLUS_WARN(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      status = DicesRcDriver::OK;
    }
    else
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
  }

  status = ReadFromPatientMedicationReqTable();
  if (status != DicesRcDriver::OK)
  {
    if (status == DicesRcDriver::DATABASE_READ_TABLE_FAILURE)
    {
      LOG4CPLUS_WARN(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      status = DicesRcDriver::OK;
    }
    else
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
  }

  status = ReadFromDxHistoryTable();
  if (status != DicesRcDriver::OK)
  {
    if (status == DicesRcDriver::DATABASE_READ_TABLE_FAILURE)
    {
      LOG4CPLUS_WARN(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      status = DicesRcDriver::OK;
    }
    else
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
  }

  status = ReadFromDxHistoryReqTable();
  if (status != DicesRcDriver::OK)
  {
    if (status == DicesRcDriver::DATABASE_READ_TABLE_FAILURE)
    {
      LOG4CPLUS_WARN(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      status = DicesRcDriver::OK;
    }
    else
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
  }

  status = ReadFromDiagnosisTable();
  if (status != DicesRcDriver::OK)
  {
    if (status == DicesRcDriver::DATABASE_READ_TABLE_FAILURE)
    {
      LOG4CPLUS_WARN(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      status = DicesRcDriver::OK;
    }
    else
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
  }

  status = ReadFromDiagnosisReqTable();
  if (status != DicesRcDriver::OK)
  {
    if (status == DicesRcDriver::DATABASE_READ_TABLE_FAILURE)
    {
      LOG4CPLUS_WARN(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      status = DicesRcDriver::OK;
    }
    else
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
  }

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ParseCSVToArray(
  std::vector<std::pair<ice::FLOATType, bool>>*dest,
  const std::string& src)
{
  static const char* sfn = "Parser::ParseCSVToArray() ";
  if (!dest)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument dest is a null "
      "pointer.");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }
  dest->clear();

  // Copy source into string which we can modify.
  std::string temp_src = src;

  size_t comma_pos = 0;
  while (comma_pos != std::string::npos)
  {
    bool not_null = true;
    comma_pos = temp_src.find(',', 0);
    std::string str_value;
    if (comma_pos != std::string::npos)
    {
      str_value = temp_src.substr(0, comma_pos);
      temp_src.erase(0, comma_pos + 1);
    }
    else
    {
      str_value = temp_src;
      temp_src.erase();
    }
    float value = 0;
    if (str_value.empty())
    {
      not_null = false;
    }
    else
    {
      std::istringstream iss(str_value);

      iss >> value;
      if (iss.fail())
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to extract float "
          "from string \"" << str_value << "\"");
        return DicesRcDriver::ISTRINGSTREAM_EXTRACT_FORMATTED_OUTPUT_FAILURE;
      }
    }
    try
    {
      std::pair < ice::FLOATType, bool> value_pair(value, not_null);
      dest->push_back(value_pair);
    }
    catch (std::exception& ex)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push back onto "
        "vector. " << ex.what());
      return DicesRcDriver::VECTOR_PUSH_BACK_FAILURE;
    }
  }

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ParseCSVToArray(
  std::vector<std::pair<ice::INT32, bool>>*dest,
  const std::string& src)
{
  static const char* sfn = "Parser::ParseCSVToArray() ";
  if (!dest)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument dest is a null "
      "pointer.");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }
  dest->clear();

  // Copy source into string which we can modify.
  std::string temp_src = src;

  size_t comma_pos = 0;
  while (comma_pos != std::string::npos)
  {
    bool not_null = true;
    comma_pos = temp_src.find(',', 0);
    std::string str_value;
    if (comma_pos != std::string::npos)
    {
      str_value = temp_src.substr(0, comma_pos);
      temp_src.erase(0, comma_pos + 1);
    }
    else
    {
      str_value = temp_src;
      temp_src.erase();
    }
    int value = 0;
    if (str_value.empty())
    {
      not_null = false;
    }
    else
    {
      std::istringstream iss(str_value);

      iss >> value;
      if (iss.fail())
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to extract int "
          "from string \"" << str_value << "\"");
        return DicesRcDriver::ISTRINGSTREAM_EXTRACT_FORMATTED_OUTPUT_FAILURE;
      }
    }
    try
    {
      std::pair < ice::INT32, bool> value_pair(value, not_null);
      dest->push_back(value_pair);
    }
    catch (std::exception& ex)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push back onto "
        "vector. " << ex.what());
      return DicesRcDriver::VECTOR_PUSH_BACK_FAILURE;
    }
  }

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ParseCSVToArray(
  std::vector<std::pair<ice::INTU32, bool>>*dest,
  const std::string& src)
{
  static const char* sfn = "Parser::ParseCSVToArray() ";
  if (!dest)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument dest is a null "
      "pointer.");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }
  dest->clear();

  // Copy source into string which we can modify.
  std::string temp_src = src;

  size_t comma_pos = 0;
  while (comma_pos != std::string::npos)
  {
    bool not_null = true;
    comma_pos = temp_src.find(',', 0);
    std::string str_value;
    if (comma_pos != std::string::npos)
    {
      str_value = temp_src.substr(0, comma_pos);
      temp_src.erase(0, comma_pos + 1);
    }
    else
    {
      str_value = temp_src;
      temp_src.erase();
    }
    unsigned int value = 0;
    if (str_value.empty())
    {
      not_null = false;
    }
    else
    {
      std::istringstream iss(str_value);

      iss >> value;
      if (iss.fail())
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to extract unsigned int "
          "from string \"" << str_value << "\"");
        return DicesRcDriver::ISTRINGSTREAM_EXTRACT_FORMATTED_OUTPUT_FAILURE;
      }
    }
    try
    {
      std::pair < ice::INTU32, bool> value_pair(value, not_null);
      dest->push_back(value_pair);
    }
    catch (std::exception& ex)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push back onto "
        "vector. " << ex.what());
      return DicesRcDriver::VECTOR_PUSH_BACK_FAILURE;
    }
  }

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ParseCSVToArray(
  std::vector<std::pair<ice::INT16, bool>>*dest,
  const std::string& src)
{
  static const char* sfn = "Parser::ParseCSVToArray() ";
  if (!dest)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument dest is a null "
      "pointer.");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }
  dest->clear();

  // Copy source into string which we can modify.
  std::string temp_src = src;

  size_t comma_pos = 0;
  while (comma_pos != std::string::npos)
  {
    bool not_null = true;
    comma_pos = temp_src.find(',', 0);
    std::string str_value;
    if (comma_pos != std::string::npos)
    {
      str_value = temp_src.substr(0, comma_pos);
      temp_src.erase(0, comma_pos + 1);
    }
    else
    {
      str_value = temp_src;
      temp_src.erase();
    }
    short value = 0;
    if (str_value.empty())
    {
      not_null = false;
    }
    else
    {
      std::istringstream iss(str_value);

      iss >> value;
      if (iss.fail())
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to extract short "
          "from string \"" << str_value << "\"");
        return DicesRcDriver::ISTRINGSTREAM_EXTRACT_FORMATTED_OUTPUT_FAILURE;
      }
    }
    try
    {
      std::pair < ice::INT16, bool> value_pair(value, not_null);
      dest->push_back(value_pair);
    }
    catch (std::exception& ex)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push back onto "
        "vector. " << ex.what());
      return DicesRcDriver::VECTOR_PUSH_BACK_FAILURE;
    }
  }

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ParseCSVToArray(
  std::vector<std::pair<ice::INTU16, bool>>*dest,
  const std::string& src)
{
  static const char* sfn = "Parser::ParseCSVToArray() ";
  if (!dest)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument dest is a null "
      "pointer.");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }
  dest->clear();

  // Copy source into string which we can modify.
  std::string temp_src = src;

  size_t comma_pos = 0;
  while (comma_pos != std::string::npos)
  {
    bool not_null = true;
    comma_pos = temp_src.find(',', 0);
    std::string str_value;
    if (comma_pos != std::string::npos)
    {
      str_value = temp_src.substr(0, comma_pos);
      temp_src.erase(0, comma_pos + 1);
    }
    else
    {
      str_value = temp_src;
      temp_src.erase();
    }
    unsigned short value = 0;
    if (str_value.empty())
    {
      not_null = false;
    }
    else
    {
      std::istringstream iss(str_value);

      iss >> value;
      if (iss.fail())
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to extract unsigned short "
          "from string \"" << str_value << "\"");
        return DicesRcDriver::ISTRINGSTREAM_EXTRACT_FORMATTED_OUTPUT_FAILURE;
      }
    }
    try
    {
      std::pair < ice::INTU16, bool> value_pair(value, not_null);
      dest->push_back(value_pair);
    }
    catch (std::exception& ex)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push back onto "
        "vector. " << ex.what());
      return DicesRcDriver::VECTOR_PUSH_BACK_FAILURE;
    }
  }

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ParseCSVToArray(
  std::vector<std::pair<std::string, bool>>*dest,
  const std::string& src)
{
  static const char* sfn = "Parser::ParseCSVToArray() ";
  if (!dest)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument dest is a null "
      "pointer.");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }
  dest->clear();

  // Copy source into string which we can modify.
  std::string temp_src = src;

  size_t comma_pos = 0;
  while (comma_pos != std::string::npos)
  {
    comma_pos = temp_src.find(',', 0);
    std::string str_value;
    bool not_null = true;
    if (comma_pos != std::string::npos)
    {
      str_value = temp_src.substr(0, comma_pos);
      temp_src.erase(0, comma_pos + 1);
    }
    else
    {
      str_value = temp_src;
      temp_src.erase();
    }
    if (str_value.empty())
    {
      not_null = false;
    }
    try
    {
      std::pair < std::string, bool> value_pair(str_value, not_null);
      dest->push_back(value_pair);
    }
    catch (std::exception& ex)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push back onto "
        "vector. " << ex.what());
      return DicesRcDriver::VECTOR_PUSH_BACK_FAILURE;
    }
  }
  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ParseCSVSequences(
  std::vector<std::pair<std::string, std::vector<unsigned int>>>*dest,
  const std::string& src)
{
  static const char* sfn = "Parser::ParseCSVSequences() ";

  if (!dest)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument dest is a null "
      "pointer.");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }
  dest->clear();

  const char kopen_bracket = '[';
  const char kclose_bracket = ']';
  int depth_index = 0;
  std::string sequence_str;
  std::vector<unsigned int> sequence_locator_vect;
  bool after_open = false;
  const unsigned int kstart_index = 0;

  // Make sure that we have the same number of '[' and ']' characters
  int sub_array_form_check = 0;
  for (int ix = 0; ix < src.size(); ix++)
  {
    if (src.at(ix) == kopen_bracket) sub_array_form_check++;
    if (src.at(ix) == kclose_bracket) sub_array_form_check--;
  }

  if (sub_array_form_check)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "CSV has bad format. There must be "
      "an equal number of " << kopen_bracket << " and " << kclose_bracket
      << " characters to parse sequences.");
    return DicesRcDriver::FAIL;
  }

  for (int ix = 0; ix < src.size(); ix++)
  {
    if (src.at(ix) == kopen_bracket)
    {
      after_open = true;
      if ((depth_index + 1) > sequence_locator_vect.size())
      {
        try
        {
          sequence_locator_vect.push_back(kstart_index);
        }
        catch (std::exception& ex)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push back index "
            "onto vector. " << ex.what());
          return DicesRcDriver::VECTOR_PUSH_BACK_FAILURE;
        }
      }
      else
      {
        try
        {
          sequence_locator_vect.at(depth_index)++;
        }
        catch (std::exception& ex)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to increment index "
            "at position " << depth_index << ". " << ex.what());
          return DicesRcDriver::VECTOR_PUSH_BACK_FAILURE;
        }
      }
      depth_index++;
    }
    else if (src.at(ix) == kclose_bracket)
    {
      if (after_open)
      {
        after_open = false;
        std::pair<std::string, std::vector<unsigned int>> sub_sequence_pair(
          sequence_str,
          sequence_locator_vect);

        try
        {
          dest->push_back(sub_sequence_pair);
        }
        catch (std::exception& ex)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push back sub "
            "sequence pair onto vector. " << ex.what());
          return DicesRcDriver::VECTOR_PUSH_BACK_FAILURE;
        }
      }
      sequence_str = "";
      depth_index--;
    }
    else
    {
      sequence_str += src.at(ix);
    }
  }

  if (dest->empty())
  {
    // Iterated through string without any sub sequences. Add sequence
    // string as the only sequence.
    std::pair<std::string, std::vector<unsigned int>> sequence_pair(
      sequence_str,
      sequence_locator_vect);

    try
    {
      dest->push_back(sequence_pair);
    }
    catch (std::exception& ex)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to push back sequence pair "
        "onto vector. " << ex.what());
      return DicesRcDriver::VECTOR_PUSH_BACK_FAILURE;
    }
  }

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ReadFromMDSTable()
{
  static const char* sfn = "Parser::ReadFromMDSTable() ";

  if (_database_connection == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Database is not connected");
    return DicesRcDriver::DATABASE_CONNECTION_FAILURE;
  }

  std::string column_names =
    kHeaderColumnNames + ", " + kTopColumnNames + ", " + kVMSColumnNames + ", "
    + kMDSColumnNames;
  pqxx::result table_result;
  try
  {
    pqxx::work database_work(*_database_connection);
    table_result = database_work.exec(
      "SELECT " + column_names + " FROM " + std::string(kTableMDS) + ";");
    database_work.commit();
  }
  catch (const std::exception &ex)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to read the " << kTableMDS
      << " table from the database. " << ex.what());
    return DicesRcDriver::DATABASE_READ_TABLE_FAILURE;
  }

  if (table_result.columns() < kExpectedMDSTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table result contains "
      << table_result.columns() << " columns, but this function requires "
      << kExpectedMDSTableColumnCount << " columns to parse successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  try
  {
    _mds_instance_list.resize(table_result.size());
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for MDS "
      "instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  for (int ix = 0; ix < table_result.size(); ix++)
  {
    ice::MDS* mds_instance = ice::MDSTypeSupport::create_data();
    if (!mds_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for MDS");
      return DicesRcDriver::MDS_INSTANCE_CREATE_FAILURE;
    }
    _mds_instance_list.at(ix).second = mds_instance;

    strncpy(
      _mds_instance_list.at(ix).second->ice_id,
      table_result[ix][2].as<std::string>("").c_str(),
      ice::MAX_LEN_ICE_ID);
    _mds_instance_list.at(ix).second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
    _mds_instance_list.at(ix).second->handle =
      table_result[ix][3].as<ice::HANDLE>(0);
    _mds_instance_list.at(ix).second->parent_handle =
      table_result[ix][4].as<ice::HANDLE>(0);
    _mds_instance_list.at(ix).second->source_timestamp.seconds =
      table_result[ix][5].as<long>(0);
    _mds_instance_list.at(ix).second->source_timestamp.nanoseconds =
      table_result[ix][6].as<long>(0);
    _mds_instance_list.at(ix).second->system_type.partition =
      static_cast<ice::NomPartition>(table_result[ix][7].as<int>(
      ice::NomPartition::nom_part_unspec));
    _mds_instance_list.at(ix).second->system_type.code =
      table_result[ix][8].as<ice::OIDType>(0);
    strncpy(
      _mds_instance_list.at(ix).second->system_model.manufacturer,
      table_result[ix][9].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _mds_instance_list.at(ix).second->system_model.manufacturer[
      ice::MEDIUM_STRING_LEN] = '\0';
    strncpy(
      _mds_instance_list.at(ix).second->system_model.model_number,
      table_result[ix][10].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _mds_instance_list.at(ix).second->system_model.model_number[
      ice::MEDIUM_STRING_LEN] = '\0';
    _mds_instance_list.at(ix).second->nomenclature_version.
      nom_major_version = static_cast<ice::NomMajorVersionBits>(
      table_result[ix][11].as<int>(0));
    _mds_instance_list.at(ix).second->nomenclature_version.
      nom_minor_version = table_result[ix][12].as<int>(0);
    _mds_instance_list.at(ix).second->system_capability =
      static_cast<ice::SystemCapabilityBits>(table_result[ix][13].as<int>(0));
    // SystemSpec
    // NOTE: If any fields are null, then SystemSpec sequence will be empty.
    if (!table_result[ix][14].is_null() && !table_result[ix][15].is_null())
    {
      std::string sys_spec_component_capab_id_str = table_result[ix][14].
        as<std::string>("");
      std::string sys_spec_component_spec_str = table_result[ix][15].
        as<std::string>("");
      std::vector < std::pair < ice::INTU16, bool>>
        sys_spec_component_capab_id_vect;
      std::vector < std::pair < std::string, bool>>
        sys_spec_component_spec_vect;
      DicesRcDriver status = ParseCSVToArray(
        &sys_spec_component_capab_id_vect,
        sys_spec_component_capab_id_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &sys_spec_component_spec_vect,
        sys_spec_component_spec_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      if (sys_spec_component_capab_id_vect.size()
        != sys_spec_component_spec_vect.size())
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "To set ice::SystemSpec "
          "sequence, component_capab_id and component_spec must have the same "
          "number of elements");
        return DicesRcDriver::FAIL;
      }
      for (int iy = 0; iy < sys_spec_component_capab_id_vect.size(); iy++)
      {
        if (!sys_spec_component_capab_id_vect.at(iy).second)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "In ice::SystemSpecEntry, "
            "component_capab_id data member is not optional, therefore null is "
            "not an acceptable value.");
          return DicesRcDriver::FAIL;
        }
      }
      // NOTE: If a component_spec string is marked with null, then an empty
      // string is stored in the string. This is because component_spec is not
      // optional in ice::SystemSpecEntry.
      if (_mds_instance_list.at(ix).second->system_specification.ensure_length(
        sys_spec_component_capab_id_vect.size(),
        sys_spec_component_capab_id_vect.size()) == false)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
          "ice::SystemSpec DDS sequence with length: "
          << sys_spec_component_capab_id_vect.size());
        return DicesRcDriver::FAIL;
      }
      for (int iy = 0; iy < sys_spec_component_capab_id_vect.size(); iy++)
      {
        _mds_instance_list.at(ix).second->system_specification[iy].
          component_capab_id = sys_spec_component_capab_id_vect.at(iy).first;
      }
      for (int iy = 0; iy < sys_spec_component_spec_vect.size(); iy++)
      {
        strncpy(
          _mds_instance_list.at(ix).second->system_specification[iy].
          component_spec,
          sys_spec_component_spec_vect.at(iy).first.c_str(),
          ice::LONG_STRING_LEN);
        _mds_instance_list.at(ix).second->system_specification[iy].
          component_spec[ice::LONG_STRING_LEN] = '\0';
      }
    }
    // ProductionSpec
    // NOTE: If any fields are null, then the ProductionSpec sequence will be
    // empty.
    if (!table_result[ix][16].is_null()
      && !table_result[ix][17].is_null()
      && !table_result[ix][18].is_null())
    {
      std::string prod_spec_spec_type_str = table_result[ix][16].
        as<std::string>("");
      std::string prod_spec_component_id_str = table_result[ix][17].
        as<std::string>("");
      std::string prod_spec_prod_spec_str = table_result[ix][18].
        as<std::string>("");
      std::vector < std::pair < ice::INT32, bool>> prod_spec_spec_type_vect;
      std::vector < std::pair < ice::INTU16, bool>>
        prod_spec_component_id_vect;
      std::vector < std::pair < std::string, bool>> prod_spec_prod_spec_vect;
      DicesRcDriver status = ParseCSVToArray(
        &prod_spec_spec_type_vect,
        prod_spec_spec_type_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &prod_spec_component_id_vect,
        prod_spec_component_id_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &prod_spec_prod_spec_vect,
        prod_spec_prod_spec_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      if (prod_spec_spec_type_vect.size() != prod_spec_component_id_vect.size()
        || prod_spec_spec_type_vect.size() != prod_spec_prod_spec_vect.size())
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "To set ice::ProductionSpec "
          "sequence, spec_type, component_id, and prod_spec must have the "
          "same number of elements");
        return DicesRcDriver::FAIL;
      }
      for (int iy = 0; iy < prod_spec_spec_type_vect.size(); iy++)
      {
        if (!prod_spec_spec_type_vect.at(iy).second)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "In ice::ProductionSpecEntry, "
            "spec_type data member is not optional, therefore null is not an "
            "acceptable value.");
          return DicesRcDriver::FAIL;
        }
      }
      for (int iy = 0; iy < prod_spec_component_id_vect.size(); iy++)
      {
        if (!prod_spec_component_id_vect.at(iy).second)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "In ice::ProductionSpecEntry, "
            "component_id data member is not optional, therefore null is not "
            "an acceptable value.");
          return DicesRcDriver::FAIL;
        }
      }
      // NOTE: If a prod_spec string is marked with null, then an empty
      // string is stored in the string. This is because prod_spec is not
      // optional in ice::ProdSpecEntry.
      if (_mds_instance_list.at(ix).second->production_specification.
        ensure_length(
        prod_spec_spec_type_vect.size(),
        prod_spec_spec_type_vect.size()) == false)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
          "ice::ProductionSpec DDS sequence with length: "
          << prod_spec_spec_type_vect.size());
        return DicesRcDriver::FAIL;
      }
      for (int iy = 0; iy < prod_spec_spec_type_vect.size(); iy++)
      {
        _mds_instance_list.at(ix).second->production_specification[iy].
          spec_type = static_cast<ice::ProdSpecType>(
          prod_spec_spec_type_vect.at(iy).first);
      }
      for (int iy = 0; iy < prod_spec_component_id_vect.size(); iy++)
      {
        _mds_instance_list.at(ix).second->production_specification[iy].
          component_id = prod_spec_component_id_vect.at(iy).first;
      }
      for (int iy = 0; iy < prod_spec_prod_spec_vect.size(); iy++)
      {
        strncpy(
          _mds_instance_list.at(ix).second->production_specification[iy].
          prod_spec,
          prod_spec_prod_spec_vect.at(iy).first.c_str(),
          ice::LONG_STRING_LEN);
        _mds_instance_list.at(ix).second->production_specification[iy].
          prod_spec[ice::LONG_STRING_LEN] = '\0';
      }
    }
    _mds_instance_list.at(ix).second->mds_status =
      static_cast<ice::MDSStatus>(table_result[ix][19].as<int>(
      ice::MDSStatus::disassociated));
    if (table_result[ix][20].is_null())
    {
      _mds_instance_list.at(ix).second->operating_mode = nullptr;
    }
    else
    {
      _mds_instance_list.at(ix).second->operating_mode =
        reinterpret_cast<ice::PrivateOid*>(DDS::Heap_malloc(sizeof(
        ice::PrivateOid)));
      if (!_mds_instance_list.at(ix).second->operating_mode)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for operating mode");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      *_mds_instance_list.at(ix).second->operating_mode =
        table_result[ix][20].as<ice::PrivateOid>(0);
    }
    if (table_result[ix][21].is_null() && table_result[ix][22].is_null())
    {
      _mds_instance_list.at(ix).second->date_and_time = nullptr;
    }
    else
    {
      _mds_instance_list.at(ix).second->date_and_time =
        reinterpret_cast<ice::Timespec*>(DDS::Heap_malloc(sizeof(
        ice::Timespec)));
      if (!_mds_instance_list.at(ix).second->date_and_time)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for date and time");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      _mds_instance_list.at(ix).second->date_and_time->seconds =
        table_result[ix][21].as<long>(0);
      _mds_instance_list.at(ix).second->date_and_time->nanoseconds =
        table_result[ix][22].as<long>(0);
    }
    if (table_result[ix][23].is_null() && table_result[ix][24].is_null())
    {
      _mds_instance_list.at(ix).second->relative_time = nullptr;
    }
    else
    {
      _mds_instance_list.at(ix).second->relative_time =
        reinterpret_cast<ice::Duration*>(DDS::Heap_malloc(sizeof(
        ice::Duration)));
      if (!_mds_instance_list.at(ix).second->relative_time)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for relative time");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      _mds_instance_list.at(ix).second->relative_time->seconds =
        table_result[ix][23].as<long>(0);
      _mds_instance_list.at(ix).second->relative_time->nanoseconds =
        table_result[ix][24].as<long>(0);
    }
    if (table_result[ix][25].is_null())
    {
      _mds_instance_list.at(ix).second->power_status = nullptr;
    }
    else
    {
      _mds_instance_list.at(ix).second->power_status =
        reinterpret_cast<ice::PowerStatus*>(DDS::Heap_malloc(sizeof(
        ice::PowerStatus)));
      if (!_mds_instance_list.at(ix).second->power_status)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for power status");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      *_mds_instance_list.at(ix).second->power_status =
        static_cast<ice::PowerStatusBits>(table_result[ix][25].
        as<int>(0));
    }
    if (table_result[ix][26].is_null())
    {
      _mds_instance_list.at(ix).second->battery_level = nullptr;
    }
    else
    {
      _mds_instance_list.at(ix).second->battery_level =
        reinterpret_cast<ice::INTU16*>(DDS::Heap_malloc(sizeof(
        ice::INTU16)));
      if (!_mds_instance_list.at(ix).second->battery_level)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for battery level");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      *_mds_instance_list.at(ix).second->battery_level =
        table_result[ix][26].as<ice::INTU16>(0);
    }
    if (table_result[ix][27].is_null())
    {
      _mds_instance_list.at(ix).second->remaining_battery_minutes = nullptr;
    }
    else
    {
      _mds_instance_list.at(ix).second->remaining_battery_minutes =
        reinterpret_cast<ice::INTU16*>(DDS::Heap_malloc(sizeof(
        ice::INTU16)));
      if (!_mds_instance_list.at(ix).second->remaining_battery_minutes)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for remaining battery minutes");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      *_mds_instance_list.at(ix).second->remaining_battery_minutes =
        table_result[ix][27].as<ice::INTU16>(0);
    }
    if (table_result[ix][28].is_null())
    {
      _mds_instance_list.at(ix).second->altitude_meters = nullptr;
    }
    else
    {
      _mds_instance_list.at(ix).second->altitude_meters =
        reinterpret_cast<ice::INT16*>(DDS::Heap_malloc(sizeof(
        ice::INT16)));
      if (!_mds_instance_list.at(ix).second->altitude_meters)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for altitude meters");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      *_mds_instance_list.at(ix).second->altitude_meters =
        table_result[ix][28].as<ice::INT16>(0);
    }
    if (table_result[ix][29].is_null())
    {
      _mds_instance_list.at(ix).second->line_frequency = nullptr;
    }
    else
    {
      _mds_instance_list.at(ix).second->line_frequency =
        reinterpret_cast<ice::LineFrequency*>(DDS::Heap_malloc(sizeof(
        ice::LineFrequency)));
      if (!_mds_instance_list.at(ix).second->line_frequency)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for line frequency");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      *_mds_instance_list.at(ix).second->line_frequency =
        static_cast<ice::LineFrequency>(table_result[ix][29].as<int>(
        ice::LineFrequency::line_f_unspec));
    }
    _mds_instance_list.at(ix).first = DicesRcDriver::OK;
  }
  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ReadFromVMDTable()
{
  static const char* sfn = "Parser::ReadFromVMDTable() ";

  if (_database_connection == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Database is not connected");
    return DicesRcDriver::DATABASE_CONNECTION_FAILURE;
  }

  std::string column_names =
    kHeaderColumnNames + ", " + kTopColumnNames + ", " + kVMOColumnNames
    + ", " + kVMDColumnNames;
  pqxx::result table_result;
  try
  {
    pqxx::work database_work(*_database_connection);
    table_result = database_work.exec(
      "SELECT " + column_names + " FROM " + std::string(kTableVMD) + ";");
    database_work.commit();
  }
  catch (const std::exception &ex)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to read the " << kTableVMD
      << " table from the database. " << ex.what());
    return DicesRcDriver::DATABASE_READ_TABLE_FAILURE;
  }

  if (table_result.columns() < kExpectedVMDTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table result contains "
      << table_result.columns() << " columns, but this function requires "
      << kExpectedVMDTableColumnCount << " columns to parse successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  try
  {
    _vmd_instance_list.resize(table_result.size());
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for VMD "
      "instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  for (int ix = 0; ix < table_result.size(); ix++)
  {
    ice::VMD* vmd_instance = ice::VMDTypeSupport::create_data();
    if (!vmd_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for VMD");
      return DicesRcDriver::VMD_INSTANCE_CREATE_FAILURE;
    }
    _vmd_instance_list.at(ix).second = vmd_instance;

    _vmd_instance_list.at(ix).second->handle =
      table_result[ix][3].as<ice::HANDLE>(0);
    strncpy(
      _vmd_instance_list.at(ix).second->ice_id,
      table_result[ix][2].as<std::string>("").c_str(),
      ice::MAX_LEN_ICE_ID);
    _vmd_instance_list.at(ix).second->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
    _vmd_instance_list.at(ix).second->instance_number =
      table_result[ix][9].as<ice::InstNumber>(0);
    _vmd_instance_list.at(ix).second->locale.charset =
      static_cast<ice::CharSet>(table_result[ix][13].as<int>(
      ice::LocaleCharSetUTF8));
    _vmd_instance_list.at(ix).second->locale.country =
      table_result[ix][12].as<ice::INTU32>(ice::LocaleCountryUSA);
    _vmd_instance_list.at(ix).second->locale.language =
      table_result[ix][11].as<ice::INTU32>(ice::LocaleLanguageEnglish);
    _vmd_instance_list.at(ix).second->locale.str_spec.str_flags =
      table_result[ix][15].as<ice::StringFlags>(
      ice::StringFlagsBits::str_flag_nt);
    _vmd_instance_list.at(ix).second->locale.str_spec.str_max_len =
      table_result[ix][14].as<ice::INTU16>(ice::LocaleStrMaxLen);
    if (table_result[ix][10].is_null())
    {
      _vmd_instance_list.at(ix).second->measurement_principle = nullptr;
    }
    else
    {
      _vmd_instance_list.at(ix).second->measurement_principle =
        reinterpret_cast<ice::MsmtPrinciple*>(DDS::Heap_malloc(sizeof(ice::MsmtPrinciple)));
      if (!_vmd_instance_list.at(ix).second->measurement_principle)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for measurement principle");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      *_vmd_instance_list.at(ix).second->measurement_principle =
        table_result[ix][10].as<ice::MsmtPrinciple>(0);
    }
    if (table_result[ix][19].is_null())
    {
      _vmd_instance_list.at(ix).second->operating_hours = nullptr;
    }
    else
    {
      _vmd_instance_list.at(ix).second->operating_hours =
        reinterpret_cast<ice::INTU32*>(DDS::Heap_malloc(sizeof(ice::INTU32)));
      if (!_vmd_instance_list.at(ix).second->operating_hours)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for operating hours");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      *_vmd_instance_list.at(ix).second->operating_hours =
        table_result[ix][19].as<ice::INTU32>(0);
    }

    if (table_result[ix][20].is_null())
    {
      _vmd_instance_list.at(ix).second->operation_cycles = nullptr;
    }
    else
    {
      _vmd_instance_list.at(ix).second->operation_cycles =
        reinterpret_cast<ice::INTU32*>(DDS::Heap_malloc(sizeof(ice::INTU32)));
      if (!_vmd_instance_list.at(ix).second->operation_cycles)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for operating cycles");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      *_vmd_instance_list.at(ix).second->operation_cycles =
        table_result[ix][20].as<ice::INTU32>(0);
    }

    _vmd_instance_list.at(ix).second->parent_handle =
      table_result[ix][4].as<ice::HANDLE>(0);
    _vmd_instance_list.at(ix).second->position =
      table_result[ix][18].as<ice::INTU16>(0);
    // ProductionSpec
    // NOTE: If any fields are null, then the ProductionSpec sequence will be
    // empty.
    if (!table_result[ix][23].is_null()
      && !table_result[ix][24].is_null()
      && !table_result[ix][25].is_null())
    {
      std::string prod_spec_spec_type_str = table_result[ix][23].
        as<std::string>("");
      std::string prod_spec_component_id_str = table_result[ix][24].
        as<std::string>("");
      std::string prod_spec_prod_spec_str = table_result[ix][25].
        as<std::string>("");
      std::vector < std::pair < ice::INT32, bool>> prod_spec_spec_type_vect;
      std::vector < std::pair < ice::INTU16, bool>>
        prod_spec_component_id_vect;
      std::vector < std::pair < std::string, bool>> prod_spec_prod_spec_vect;
      DicesRcDriver status = ParseCSVToArray(
        &prod_spec_spec_type_vect,
        prod_spec_spec_type_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &prod_spec_component_id_vect,
        prod_spec_component_id_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &prod_spec_prod_spec_vect,
        prod_spec_prod_spec_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      if (prod_spec_spec_type_vect.size() != prod_spec_component_id_vect.size()
        || prod_spec_spec_type_vect.size() != prod_spec_prod_spec_vect.size())
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "To set ice::ProductionSpec "
          "sequence, spec_type, component_id, and prod_spec must have the "
          "same number of elements");
        return DicesRcDriver::FAIL;
      }
      for (int iy = 0; iy < prod_spec_spec_type_vect.size(); iy++)
      {
        if (!prod_spec_spec_type_vect.at(iy).second)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "In ice::ProductionSpecEntry, "
            "spec_type data member is not optional, therefore null is not an "
            "acceptable value.");
          return DicesRcDriver::FAIL;
        }
      }
      for (int iy = 0; iy < prod_spec_component_id_vect.size(); iy++)
      {
        if (!prod_spec_component_id_vect.at(iy).second)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "In ice::ProductionSpecEntry, "
            "component_id data member is not optional, therefore null is not "
            "an acceptable value.");
          return DicesRcDriver::FAIL;
        }
      }
      // NOTE: If a prod_spec string is marked with null, then an empty
      // string is stored in the string. This is because prod_spec is not
      // optional in ice::ProdSpecEntry.
      if (_vmd_instance_list.at(ix).second->production_specification.
        ensure_length(
        prod_spec_spec_type_vect.size(),
        prod_spec_spec_type_vect.size()) == false)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
          "ice::ProductionSpec DDS sequence with length: "
          << prod_spec_spec_type_vect.size());
        return DicesRcDriver::FAIL;
      }
      for (int iy = 0; iy < prod_spec_spec_type_vect.size(); iy++)
      {
        _vmd_instance_list.at(ix).second->production_specification[iy].
          spec_type = static_cast<ice::ProdSpecType>(
          prod_spec_spec_type_vect.at(iy).first);
      }
      for (int iy = 0; iy < prod_spec_component_id_vect.size(); iy++)
      {
        _vmd_instance_list.at(ix).second->production_specification[iy].
          component_id = prod_spec_component_id_vect.at(iy).first;
      }
      for (int iy = 0; iy < prod_spec_prod_spec_vect.size(); iy++)
      {
        strncpy(
          _vmd_instance_list.at(ix).second->production_specification[iy].
          prod_spec,
          prod_spec_prod_spec_vect.at(iy).first.c_str(),
          ice::LONG_STRING_LEN);
        _vmd_instance_list.at(ix).second->production_specification[iy].
          prod_spec[ice::LONG_STRING_LEN] = '\0';
      }
    }
    _vmd_instance_list.at(ix).second->source_timestamp.nanoseconds =
      table_result[ix][6].as<long>(0);
    _vmd_instance_list.at(ix).second->source_timestamp.seconds =
      table_result[ix][5].as<long>(0);
    _vmd_instance_list.at(ix).second->type.code =
      table_result[ix][8].as<ice::OIDType>(0);
    _vmd_instance_list.at(ix).second->type.partition =
      static_cast<ice::NomPartition>(table_result[ix][7].as<int>(
      ice::NomPartition::nom_part_unspec));
    strncpy(
      _vmd_instance_list.at(ix).second->vmd_model.manufacturer,
      table_result[ix][21].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _vmd_instance_list.at(ix).second->vmd_model.manufacturer[
      ice::MEDIUM_STRING_LEN] = '\0';
    strncpy(
      _vmd_instance_list.at(ix).second->vmd_model.model_number,
      table_result[ix][22].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _vmd_instance_list.at(ix).second->vmd_model.model_number[
      ice::MEDIUM_STRING_LEN] = '\0';
    _vmd_instance_list.at(ix).second->vmd_status =
      table_result[ix][17].as<ice::VMDStatus>(0);
    strncpy(
      _vmd_instance_list.at(ix).second->vmo_label_string,
      table_result[ix][16].as<std::string>("").c_str(),
      ice::LONG_STRING_LEN);
    _vmd_instance_list.at(ix).second->vmo_label_string[
      ice::LONG_STRING_LEN] = '\0';
    _vmd_instance_list.at(ix).first = DicesRcDriver::OK;
  }
  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ReadFromNumericTable()
{
  static const char* sfn = "Parser::ReadFromNumericTable() ";

  if (_database_connection == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Database is not connected");
    return DicesRcDriver::DATABASE_CONNECTION_FAILURE;
  }

  std::string column_names =
    kHeaderColumnNames + ", " + kTopColumnNames + ", " + kVMOColumnNames
    + ", " + kMetricContextColumnNames + ", " + kNumericContextColumnNames;
  pqxx::result table_result;
  try
  {
    pqxx::work database_work(*_database_connection);
    table_result = database_work.exec(
      "SELECT " + column_names + " FROM " + std::string(kTableNumeric) + ";");
    database_work.commit();
  }
  catch (const std::exception &ex)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to read the " << kTableNumeric
      << " table from the database. " << ex.what());
    return DicesRcDriver::DATABASE_READ_TABLE_FAILURE;
  }

  if (table_result.columns() < kExpectedNumericContextsTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table result contains "
      << table_result.columns() << " columns, but this function requires "
      << kExpectedNumericContextsTableColumnCount << " columns to parse "
      "successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  int meas_count = 0;
  int calc_count = 0;
  int sett_count = 0;
  for (int ix = 0; ix < table_result.size(); ix++)
  {
    ice::MetricCategory category = static_cast<ice::MetricCategory>(
      table_result[ix][12].as<int>(ice::MetricCategory::mcat_unspec));
    switch (category)
    {
      case ice::MetricCategory::auto_measurement:
      case ice::MetricCategory::manual_measurement:
        meas_count++;
        break;
      case ice::MetricCategory::auto_calculation:
      case ice::MetricCategory::manual_calculation:
        calc_count++;
        break;
      case ice::MetricCategory::auto_setting:
      case ice::MetricCategory::manual_setting:
        sett_count++;
        break;
      case ice::MetricCategory::mcat_unspec:
      default:
        LOG4CPLUS_WARN(root_logger, sfn << "Cannot determine from "
          "MetricCategory (" << static_cast<int>(category) << ") if numeric "
          "is measurement, calculation, and setting.");
        break;
    }
  }

  try
  {
    _numeric_meas_context_response_instance_list.resize(meas_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "NumericContext measurement instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  try
  {
    _numeric_meas_observed_value_response_instance_list.resize(meas_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "NumericObservedValue measurement instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  try
  {
    _numeric_calc_context_response_instance_list.resize(calc_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "NumericContext calculation instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  try
  {
    _numeric_calc_observed_value_response_instance_list.resize(calc_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "NumericObservedValue calculation instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  try
  {
    _numeric_sett_context_response_instance_list.resize(sett_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "NumericContext setting instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  try
  {
    _numeric_sett_observed_value_response_instance_list.resize(sett_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "NumericObservedValue setting instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  // Use counters as indexes now.
  meas_count = 0;
  calc_count = 0;
  sett_count = 0;
  for (int ix = 0; ix < table_result.size(); ix++)
  {
    ice::NumericContext* numeric_context_instance =
      ice::NumericContextTypeSupport::create_data();
    if (!numeric_context_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for "
        "NumericContext");
      return DicesRcDriver::NUMERIC_CONTEXT_INSTANCE_CREATE_FAILURE;
    }
    ice::NumericObservedValue* numeric_obs_val_instance =
      ice::NumericObservedValueTypeSupport::create_data();
    if (!numeric_obs_val_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for "
        "NumericObservedValue");
      DDS::ReturnCode_t retcode = ice::NumericContextTypeSupport::
        delete_data(numeric_context_instance);
      if (retcode != DDS::RETCODE_OK)
      {
        LOG4CPLUS_WARN(root_logger, sfn << "Failed to delete_data() for "
          "NumericContext instance");
      }
      numeric_context_instance = nullptr;
      return DicesRcDriver::NUMERIC_OBSERVED_VALUE_INSTANCE_CREATE_FAILURE;
    }

    ice::MetricCategory category = static_cast<ice::MetricCategory>(
      table_result[ix][12].as<int>(ice::MetricCategory::mcat_unspec));
    switch (category)
    {
      case ice::MetricCategory::auto_measurement:
      case ice::MetricCategory::manual_measurement:
      {
        _numeric_meas_context_response_instance_list.at(meas_count).
          second = numeric_context_instance;
        _numeric_meas_observed_value_response_instance_list.at(meas_count).
          second = numeric_obs_val_instance;

        DicesRcDriver status = ParseNumericContextResultTuple(
          _numeric_meas_context_response_instance_list.at(meas_count).second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _numeric_meas_context_response_instance_list.at(meas_count).first =
          DicesRcDriver::OK;

        status = ParseNumericObservedValueResultTuple(
          _numeric_meas_observed_value_response_instance_list.at(meas_count).
          second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _numeric_meas_observed_value_response_instance_list.at(meas_count).
          first = DicesRcDriver::NO_NEW_DATA;

        meas_count++;
      }
        break;
      case ice::MetricCategory::auto_calculation:
      case ice::MetricCategory::manual_calculation:
      {
        _numeric_calc_context_response_instance_list.at(calc_count).
          second = numeric_context_instance;
        _numeric_calc_observed_value_response_instance_list.at(calc_count).
          second = numeric_obs_val_instance;

        DicesRcDriver status = ParseNumericContextResultTuple(
          _numeric_calc_context_response_instance_list.at(calc_count).
          second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _numeric_calc_context_response_instance_list.at(calc_count).
          first = DicesRcDriver::OK;

        status = ParseNumericObservedValueResultTuple(
          _numeric_calc_observed_value_response_instance_list.at(calc_count).
          second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _numeric_calc_observed_value_response_instance_list.at(calc_count).
          first = DicesRcDriver::NO_NEW_DATA;

        calc_count++;
      }
        break;
      case ice::MetricCategory::auto_setting:
      case ice::MetricCategory::manual_setting:
      {
        _numeric_sett_context_response_instance_list.at(sett_count).
          second = numeric_context_instance;
        _numeric_sett_observed_value_response_instance_list.at(sett_count).
          second = numeric_obs_val_instance;

        DicesRcDriver status = ParseNumericContextResultTuple(
          _numeric_sett_context_response_instance_list.at(sett_count).second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _numeric_sett_context_response_instance_list.at(sett_count).first
          = DicesRcDriver::OK;

        status = ParseNumericObservedValueResultTuple(
          _numeric_sett_observed_value_response_instance_list.at(sett_count).
          second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _numeric_sett_observed_value_response_instance_list.at(sett_count).
          first = DicesRcDriver::NO_NEW_DATA;

        sett_count++;
      }
        break;
      case ice::MetricCategory::mcat_unspec:
      default:
      {
        LOG4CPLUS_WARN(root_logger, sfn << "Cannot determine from "
          "MetricCategory (" << static_cast<int>(category) << ") if numeric "
          "is measurement, calculation, and setting.");

        DDS::ReturnCode_t retcode = ice::NumericContextTypeSupport::
          delete_data(numeric_context_instance);
        if (retcode != DDS::RETCODE_OK)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to delete_data() for "
            "NumericContext instance");
        }
        numeric_context_instance = nullptr;

        retcode = ice::NumericObservedValueTypeSupport::
          delete_data(numeric_obs_val_instance);
        if (retcode != DDS::RETCODE_OK)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to delete_data() for "
            "NumericObservedValue instance");
        }
        numeric_obs_val_instance = nullptr;
      }
        break;
    }
  }
  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ParseNumericContextResultTuple(
  ice::NumericContext* instance,
  const pqxx::result::tuple& table_tuple)
{
  static const char* sfn = "Parser::ParseNumericContextResultTuple() ";
  if (instance == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument instance is a null pointer.");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }

  if (table_tuple.size() < kExpectedNumericContextsTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table tuple contains "
      << table_tuple.size() << " columns, but this function requires "
      << kExpectedNumericContextsTableColumnCount << " columns to parse "
      "successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  strncpy(
    instance->ice_id,
    table_tuple[2].as<std::string>("").c_str(),
    ice::MAX_LEN_ICE_ID);
  instance->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  instance->handle = table_tuple[3].as<ice::HANDLE>(0);
  instance->parent_handle = table_tuple[4].as<ice::HANDLE>(0);
  instance->source_timestamp.seconds = table_tuple[5].as<long>(0);
  instance->source_timestamp.nanoseconds = table_tuple[6].as<long>(0);
  instance->type.partition = static_cast<ice::NomPartition>(
    table_tuple[7].as<int>(ice::NomPartition::nom_part_unspec));
  instance->type.code = table_tuple[8].as<ice::OIDType>(0);
  instance->context_seq_number = table_tuple[9].as<long>(0);
  instance->metric_specification.update_period.seconds =
    table_tuple[10].as<long>(0);
  instance->metric_specification.update_period.nanoseconds =
    table_tuple[11].as<long>(0);
  instance->metric_specification.category = static_cast<ice::MetricCategory>(
    table_tuple[12].as<int>(ice::MetricCategory::mcat_unspec));
  instance->metric_specification.access = table_tuple[13].as<
    ice::MetricAccess>(0);
  instance->metric_specification.relevance = table_tuple[14].as<
    ice::MetricRelevance>(0);
  if (table_tuple[15].is_null() && table_tuple[16].is_null())
  {
    instance->max_delay_time = nullptr;
  }
  else
  {
    instance->max_delay_time =
      reinterpret_cast<ice::Duration*>(DDS::Heap_malloc(sizeof(ice::Duration)));
    if (!instance->max_delay_time)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for max delay time");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->max_delay_time->seconds = table_tuple[15].as<long>(0);
    instance->max_delay_time->nanoseconds = table_tuple[16].as<long>(0);
  }
  strncpy(
    instance->vmo_label_string,
    table_tuple[17].as<std::string>("").c_str(),
    ice::LONG_STRING_LEN);
  instance->vmo_label_string[ice::LONG_STRING_LEN] = '\0';
  // VmoSourceList
  // NOTE: If any fields are null, then the VmoSourceList sequence will be
  // empty.
  if (!table_tuple[18].is_null()
    && !table_tuple[19].is_null()
    && !table_tuple[20].is_null())
  {
    std::string vmo_src_list_vmo_type_str = table_tuple[18].
      as<std::string>("");
    std::string vmo_src_list_context_id_str = table_tuple[19].
      as<std::string>("");
    std::string vmo_src_list_handle_str = table_tuple[20].
      as<std::string>("");
    std::vector < std::pair < ice::INTU16, bool>> vmo_src_list_vmo_type_vect;
    std::vector < std::pair < ice::INTU16, bool>> vmo_src_list_context_id_vect;
    std::vector < std::pair < ice::INTU16, bool>> vmo_src_list_handle_vect;
    DicesRcDriver status = ParseCSVToArray(
      &vmo_src_list_vmo_type_vect,
      vmo_src_list_vmo_type_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(
      &vmo_src_list_context_id_vect,
      vmo_src_list_context_id_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(
      &vmo_src_list_handle_vect,
      vmo_src_list_handle_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    if (vmo_src_list_vmo_type_vect.size() != vmo_src_list_context_id_vect.size()
      || vmo_src_list_vmo_type_vect.size() != vmo_src_list_handle_vect.size())
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "To set ice::VmoSourceList "
        "sequence, vmo_type, context_id, and handle must have the "
        "same number of elements");
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < vmo_src_list_vmo_type_vect.size(); iy++)
    {
      if (!vmo_src_list_vmo_type_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::VmoSourceEntry, "
          "vmo_type data member is not optional, therefore null is not an "
          "acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < vmo_src_list_context_id_vect.size(); iy++)
    {
      if (!vmo_src_list_context_id_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::GLBHANDLE, "
          "context_id data member is not optional, therefore null is not "
          "an acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < vmo_src_list_handle_vect.size(); iy++)
    {
      if (!vmo_src_list_handle_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::GLBHANDLE, "
          "handle data member is not optional, therefore null is not "
          "an acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->vmo_source_list.ensure_length(
      vmo_src_list_vmo_type_vect.size(),
      vmo_src_list_vmo_type_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::VmoSourceList DDS sequence with length: "
        << vmo_src_list_vmo_type_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < vmo_src_list_vmo_type_vect.size(); iy++)
    {
      instance->vmo_source_list[iy].vmo_type = static_cast<ice::OIDType>(
        vmo_src_list_vmo_type_vect.at(iy).first);
    }
    for (int iy = 0; iy < vmo_src_list_context_id_vect.size(); iy++)
    {
      instance->vmo_source_list[iy].glb_handle.context_id =
        static_cast<ice::MdsContext>(vmo_src_list_context_id_vect.at(iy).
        first);
    }
    for (int iy = 0; iy < vmo_src_list_handle_vect.size(); iy++)
    {
      instance->vmo_source_list[iy].glb_handle.handle =
        static_cast<ice::HANDLE>(vmo_src_list_handle_vect.at(iy).first);
    }
  }
  // MetricSourceList
  // NOTE: If any fields are null, then the MetricSourceList sequence will be
  // empty.
  if (!table_tuple[21].is_null())
  {
    std::string metric_source_list_str = table_tuple[21].
      as<std::string>("");
    std::vector < std::pair < ice::INTU16, bool>> metric_source_list_vect;
    DicesRcDriver status = ParseCSVToArray(
      &metric_source_list_vect,
      metric_source_list_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    for (int iy = 0; iy < metric_source_list_vect.size(); iy++)
    {
      if (!metric_source_list_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::MetricSourceList, "
          "each element is an ice::OIDType and is not optional, therefore "
          "null is not an acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->metric_source_list.ensure_length(
      metric_source_list_vect.size(),
      metric_source_list_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::MetricSourceList DDS sequence with length: "
        << metric_source_list_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < metric_source_list_vect.size(); iy++)
    {
      instance->metric_source_list[iy] = static_cast<ice::OIDType>(
        metric_source_list_vect.at(iy).first);
    }
  }
  instance->unit_code = table_tuple[22].as<ice::OIDType>(0);
  strncpy(
    instance->unit_label_string,
    table_tuple[23].as<std::string>("").c_str(),
    ice::LONG_STRING_LEN);
  // SiteList msmt_site_list
  // NOTE: If any fields are null, then the SiteList sequence will be
  // empty.
  if (!table_tuple[24].is_null())
  {
    std::string msmt_site_list_str = table_tuple[24].
      as<std::string>("");
    std::vector < std::pair < ice::INTU16, bool>>msmt_site_list_vect;
    DicesRcDriver status = ParseCSVToArray(
      &msmt_site_list_vect,
      msmt_site_list_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    for (int iy = 0; iy < msmt_site_list_vect.size(); iy++)
    {
      if (!msmt_site_list_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::SiteList "
          "(msmt_site_list), each element is an ice::OIDType and is not "
          "optional, therefore null is not an acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->msmt_site_list.ensure_length(
      msmt_site_list_vect.size(),
      msmt_site_list_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::SiteList (msmt_site_list) DDS sequence with length: "
        << msmt_site_list_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < msmt_site_list_vect.size(); iy++)
    {
      instance->msmt_site_list[iy] = static_cast<ice::OIDType>(
        msmt_site_list_vect.at(iy).first);
    }
  }
  // SiteList body_site_list
  // NOTE: If any fields are null, then the SiteList sequence will be
  // empty.
  if (!table_tuple[25].is_null())
  {
    std::string body_site_list_str = table_tuple[25].
      as<std::string>("");
    std::vector < std::pair < ice::INTU16, bool>>body_site_list_vect;
    DicesRcDriver status = ParseCSVToArray(
      &body_site_list_vect,
      body_site_list_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    for (int iy = 0; iy < body_site_list_vect.size(); iy++)
    {
      if (!body_site_list_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::SiteList "
          "(body_site_list), each element is an ice::OIDType and is not "
          "optional, therefore null is not an acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->body_site_list.ensure_length(
      body_site_list_vect.size(),
      body_site_list_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::SiteList (body_site_list) DDS sequence with length: "
        << body_site_list_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < body_site_list_vect.size(); iy++)
    {
      instance->body_site_list[iy] = static_cast<ice::OIDType>(
        body_site_list_vect.at(iy).first);
    }
  }
  instance->unit_label_string[ice::LONG_STRING_LEN] = '\0';
  instance->metric_status = table_tuple[26].as<ice::MetricStatus>(0);
  if (table_tuple[27].is_null() && table_tuple[28].is_null())
  {
    instance->measure_period = nullptr;
  }
  else
  {
    instance->measure_period =
      reinterpret_cast<ice::MetricMeasure*>(DDS::Heap_malloc(sizeof(
      ice::MetricMeasure)));
    if (!instance->measure_period)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for measure period");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->measure_period->value = table_tuple[27].as<ice::FLOATType>(0);
    instance->measure_period->unit_code = table_tuple[28].as<
      ice::OIDType>(0);
  }
  if (table_tuple[29].is_null() && table_tuple[30].is_null())
  {
    instance->averaging_period = nullptr;
  }
  else
  {
    instance->averaging_period =
      reinterpret_cast<ice::MetricMeasure*>(DDS::Heap_malloc(sizeof(
      ice::MetricMeasure)));
    if (!instance->averaging_period)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for averaging period");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->averaging_period->value = table_tuple[29].as<
      ice::FLOATType>(0);
    instance->averaging_period->unit_code = table_tuple[30].as<
      ice::OIDType>(0);
  }
  if (table_tuple[31].is_null() && table_tuple[32].is_null())
  {
    instance->start_time = nullptr;
  }
  else
  {
    instance->start_time =
      reinterpret_cast<ice::Timespec*>(DDS::Heap_malloc(sizeof(
      ice::Timespec)));
    if (!instance->start_time)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for start time");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->start_time->seconds = table_tuple[31].as<long>(0);
    instance->start_time->nanoseconds = table_tuple[32].as<long>(0);
  }
  if (table_tuple[33].is_null() && table_tuple[34].is_null())
  {
    instance->stop_time = nullptr;
  }
  else
  {
    instance->stop_time =
      reinterpret_cast<ice::Timespec*>(DDS::Heap_malloc(sizeof(
      ice::Timespec)));
    if (!instance->stop_time)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for stop time");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->stop_time->seconds = table_tuple[33].as<long>(0);
    instance->stop_time->nanoseconds = table_tuple[34].as<long>(0);
  }
  // MetricCalibration
  // NOTE: If any fields are null, then the MetricCalibration sequence will be
  // empty.
  if (!table_tuple[35].is_null()
    && !table_tuple[36].is_null()
    && !table_tuple[37].is_null()
    && !table_tuple[38].is_null())
  {
    std::string metric_cal_type_str = table_tuple[35].
      as<std::string>("");
    std::string metric_cal_state_str = table_tuple[36].
      as<std::string>("");
    std::string metric_cal_time_secs_str = table_tuple[37].
      as<std::string>("");
    std::string metric_cal_time_nsecs_str = table_tuple[38].
      as<std::string>("");
    std::vector < std::pair < ice::INT32, bool>>metric_cal_type_vect;
    std::vector < std::pair < ice::INT32, bool>>metric_cal_state_vect;
    std::vector < std::pair < ice::INT32, bool>>metric_cal_time_secs_vect;
    std::vector < std::pair < ice::INT32, bool>>metric_cal_time_nsecs_vect;
    DicesRcDriver status = ParseCSVToArray(
      &metric_cal_type_vect,
      metric_cal_type_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(
      &metric_cal_state_vect,
      metric_cal_state_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(
      &metric_cal_time_secs_vect,
      metric_cal_time_secs_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(
      &metric_cal_time_nsecs_vect,
      metric_cal_time_nsecs_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    if (metric_cal_type_vect.size() != metric_cal_state_vect.size()
      || metric_cal_type_vect.size() != metric_cal_time_secs_vect.size()
      || metric_cal_type_vect.size() != metric_cal_time_nsecs_vect.size())
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "To set ice::MetricCalibration "
        "sequence, cal_type, cal_state, cal_time_seconds, and "
        "cal_time_nanoseconds must have the same number of elements");
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < metric_cal_type_vect.size(); iy++)
    {
      if (!metric_cal_type_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::MetricCalEntry, "
          "cal_type is not optional, therefore null is not an acceptable "
          "value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < metric_cal_state_vect.size(); iy++)
    {
      if (!metric_cal_state_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::MetricCalEntry, "
          "cal_state is not optional, therefore null is not an acceptable "
          "value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < metric_cal_time_secs_vect.size(); iy++)
    {
      if (!metric_cal_time_secs_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::Timespec, "
          "seconds is not optional, therefore null is not an acceptable "
          "value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < metric_cal_time_nsecs_vect.size(); iy++)
    {
      if (!metric_cal_time_nsecs_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::Timespec, "
          "nanoseconds is not optional, therefore null is not an acceptable "
          "value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->metric_calibration.ensure_length(
      metric_cal_type_vect.size(),
      metric_cal_type_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::MetricCalibration DDS sequence with length: "
        << metric_cal_type_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < metric_cal_type_vect.size(); iy++)
    {
      instance->metric_calibration[iy].cal_type =
        static_cast<ice::MetricCalType>(metric_cal_type_vect.at(iy).first);
    }
    for (int iy = 0; iy < metric_cal_state_vect.size(); iy++)
    {
      instance->metric_calibration[iy].cal_state =
        static_cast<ice::MetricCalState>(metric_cal_state_vect.at(iy).first);
    }
    for (int iy = 0; iy < metric_cal_time_secs_vect.size(); iy++)
    {
      instance->metric_calibration[iy].cal_time.seconds =
        static_cast<DDS::Long>(metric_cal_time_secs_vect.at(iy).first);
    }
    for (int iy = 0; iy < metric_cal_time_nsecs_vect.size(); iy++)
    {
      instance->metric_calibration[iy].cal_time.nanoseconds =
        static_cast<DDS::Long>(metric_cal_time_nsecs_vect.at(iy).first);
    }
  }
  if (table_tuple[39].is_null())
  {
    instance->color = nullptr;
  }
  else
  {
    instance->color = reinterpret_cast<ice::SimpleColor*>(
      DDS::Heap_malloc(sizeof(ice::SimpleColor)));
    if (!instance->color)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for color");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    *instance->color = static_cast<ice::SimpleColor>(
      table_tuple[39].as<int>(ice::SimpleColor::col_black));
  }
  instance->measurement_status = table_tuple[40].as<ice::MeasurementStatus>(0);
  instance->metric_id = table_tuple[41].as<ice::OIDType>(0);
  strncpy(
    instance->metric_info_label_string,
    table_tuple[42].as<std::string>("").c_str(),
    ice::LONG_STRING_LEN);
  instance->metric_info_label_string[ice::LONG_STRING_LEN] = '\0';
  if (table_tuple[43].is_null() && table_tuple[44].is_null())
  {
    instance->substance = nullptr;
  }
  else
  {
    instance->substance = reinterpret_cast<ice::ExtNomenRef*>(
      DDS::Heap_malloc(sizeof(ice::ExtNomenRef)));
    if (!instance->substance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for substance");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->substance->nomenclature_id = table_tuple[43].as<
      ice::OIDType>(0);
    instance->substance->nomenclature_code = DDS::String_alloc(
      ice::LONG_STRING_LEN);
    if (!instance->substance->nomenclature_code)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for substance nomenclature code");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    strncpy(
      instance->substance->nomenclature_code,
      table_tuple[44].as<std::string>("").c_str(),
      ice::LONG_STRING_LEN);
    instance->substance->nomenclature_code[ice::LONG_STRING_LEN] = '\0';
  }
  strncpy(
    instance->substance_label_string,
    table_tuple[45].as<std::string>("").c_str(),
    ice::LONG_STRING_LEN);
  instance->substance_label_string[ice::LONG_STRING_LEN] = '\0';
  if (table_tuple[46].is_null() && table_tuple[47].is_null())
  {
    instance->nu_measure_range = nullptr;
  }
  else
  {
    instance->nu_measure_range = reinterpret_cast<ice::AbsoluteRange*>(
      DDS::Heap_malloc(sizeof(ice::AbsoluteRange)));
    if (!instance->nu_measure_range)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for numeric measure range");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->nu_measure_range->lower_value = table_tuple[46].as<
      ice::FLOATType>(0);
    instance->nu_measure_range->upper_value = table_tuple[47].as<
      ice::FLOATType>(0);
  }
  if (table_tuple[48].is_null() && table_tuple[49].is_null())
  {
    instance->nu_physiological_range = nullptr;
  }
  else
  {
    instance->nu_physiological_range = reinterpret_cast<ice::AbsoluteRange*>(
      DDS::Heap_malloc(sizeof(ice::AbsoluteRange)));
    if (!instance->nu_physiological_range)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for numeric physiological range");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->nu_physiological_range->lower_value = table_tuple[48].as<
      ice::FLOATType>(0);
    instance->nu_physiological_range->upper_value = table_tuple[49].as<
      ice::FLOATType>(0);
  }
  if (table_tuple[50].is_null() && table_tuple[51].is_null())
  {
    instance->display_resolution = nullptr;
  }
  else
  {
    instance->display_resolution = reinterpret_cast<ice::DispResolution*>(
      DDS::Heap_malloc(sizeof(ice::DispResolution)));
    if (!instance->display_resolution)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for display resolution");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
      table_tuple[50].as<std::string>(""),
      &instance->display_resolution->pre_point);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ConvertPostgresByteaHexToICEINTU8(
      table_tuple[51].as<std::string>(""),
      &instance->display_resolution->post_point);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
  }
  if (table_tuple[52].is_null())
  {
    instance->accuracy = nullptr;
  }
  else
  {
    instance->accuracy = reinterpret_cast<ice::FLOATType*>(
      DDS::Heap_malloc(sizeof(ice::FLOATType)));
    if (!instance->accuracy)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for accuracy");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    *instance->accuracy = table_tuple[52].as<ice::FLOATType>(0);
  }
  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ParseNumericObservedValueResultTuple(
  ice::NumericObservedValue* instance,
  const pqxx::result::tuple& table_tuple)
{
  static const char* sfn = "Parser::ParseNumericObservedValueResultTuple() ";
  if (instance == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument instance is a null pointer.");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }

  if (table_tuple.size() < kExpectedNumericContextsTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table tuple contains "
      << table_tuple.size() << " columns, but this function requires "
      << kExpectedNumericContextsTableColumnCount << " columns to parse "
      "successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  strncpy(
    instance->ice_id,
    table_tuple[2].as<std::string>("").c_str(),
    ice::MAX_LEN_ICE_ID);
  instance->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  instance->handle = table_tuple[3].as<ice::HANDLE>(0);
  instance->parent_handle = table_tuple[4].as<ice::HANDLE>(0);
  instance->source_timestamp.seconds = table_tuple[5].as<long>(0);
  instance->source_timestamp.nanoseconds = table_tuple[6].as<long>(0);
  instance->type.partition = static_cast<ice::NomPartition>(
    table_tuple[7].as<int>(ice::NomPartition::nom_part_unspec));
  instance->type.code = table_tuple[8].as<ice::OIDType>(0);
  instance->context_seq_number = table_tuple[9].as<long>(0);
  instance->nu_observed_value.unit_code = table_tuple[22].as<ice::OIDType>(0);
  instance->nu_observed_value.state = table_tuple[40].as<
    ice::MeasurementStatus>(0);
  instance->nu_observed_value.metric_id = table_tuple[41].as<ice::OIDType>(0);
  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ReadFromEnumerationTable()
{
  static const char* sfn = "Parser::ReadFromEnumerationTable() ";

  if (_database_connection == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Database is not connected");
    return DicesRcDriver::DATABASE_CONNECTION_FAILURE;
  }

  std::string column_names =
    kHeaderColumnNames + ", " + kTopColumnNames + ", " + kVMOColumnNames
    + ", " + kMetricContextColumnNames + ", " + kEnumerationContextColumnNames;

  pqxx::result table_result;
  try
  {
    pqxx::work database_work(*_database_connection);
    table_result = database_work.exec(
      "SELECT " + column_names + " FROM "
      + std::string(kTableEnumeration) + ";");
    database_work.commit();
  }
  catch (const std::exception &ex)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to read the "
      << kTableEnumeration << " table from the database. " << ex.what());
    return DicesRcDriver::DATABASE_READ_TABLE_FAILURE;
  }

  if (table_result.columns() < kExpectedEnumContextsTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table result contains "
      << table_result.columns() << " columns, but this function requires "
      << kExpectedEnumContextsTableColumnCount << " columns to parse "
      "successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  int meas_count = 0;
  int calc_count = 0;
  int sett_count = 0;
  for (int ix = 0; ix < table_result.size(); ix++)
  {
    ice::MetricCategory category = static_cast<ice::MetricCategory>(
      table_result[ix][12].as<int>(ice::MetricCategory::mcat_unspec));
    switch (category)
    {
      case ice::MetricCategory::auto_measurement:
      case ice::MetricCategory::manual_measurement:
        meas_count++;
        break;
      case ice::MetricCategory::auto_calculation:
      case ice::MetricCategory::manual_calculation:
        calc_count++;
        break;
      case ice::MetricCategory::auto_setting:
      case ice::MetricCategory::manual_setting:
        sett_count++;
        break;
      case ice::MetricCategory::mcat_unspec:
      default:
        LOG4CPLUS_WARN(root_logger, sfn << "Cannot determine from "
          "MetricCategory (" << static_cast<int>(category) << ") if "
          "enumeration is measurement, calculation, and setting.");
        break;
    }
  }

  try
  {
    _enumeration_meas_context_response_instance_list.resize(meas_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "EnumerationContext measurement instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  try
  {
    _enumeration_meas_observed_value_response_instance_list.resize(meas_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "EnumerationObservedValue measurement instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  try
  {
    _enumeration_calc_context_response_instance_list.resize(calc_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "EnumerationContext calculation instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  try
  {
    _enumeration_calc_observed_value_response_instance_list.resize(calc_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "EnumerationObservedValue calculation instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  try
  {
    _enumeration_sett_context_response_instance_list.resize(sett_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "EnumerationContext setting instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  try
  {
    _enumeration_sett_observed_value_response_instance_list.resize(sett_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "EnumerationObservedValue setting instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  // Use counters as indexes now.
  meas_count = 0;
  calc_count = 0;
  sett_count = 0;
  for (int ix = 0; ix < table_result.size(); ix++)
  {
    ice::EnumerationContext* enum_context_instance =
      ice::EnumerationContextTypeSupport::create_data();
    if (!enum_context_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for "
        "EnumerationContext");
      return DicesRcDriver::ENUMERATION_CONTEXT_INSTANCE_CREATE_FAILURE;
    }
    ice::EnumerationObservedValue* enum_obs_val_instance =
      ice::EnumerationObservedValueTypeSupport::create_data();
    if (!enum_obs_val_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for "
        "EnumerationObservedValue");
      DDS::ReturnCode_t retcode = ice::EnumerationContextTypeSupport::
        delete_data(enum_context_instance);
      if (retcode != DDS::RETCODE_OK)
      {
        LOG4CPLUS_WARN(root_logger, sfn << "Failed to delete_data() for "
          "EnumerationContext instance.");
      }
      enum_context_instance = nullptr;
      return DicesRcDriver::ENUMERATION_OBSERVED_VALUE_INSTANCE_CREATE_FAILURE;
    }

    ice::MetricCategory category = static_cast<ice::MetricCategory>(
      table_result[ix][12].as<int>(ice::MetricCategory::mcat_unspec));
    switch (category)
    {
      case ice::MetricCategory::auto_measurement:
      case ice::MetricCategory::manual_measurement:
      {
        _enumeration_meas_context_response_instance_list.at(meas_count).
          second = enum_context_instance;
        _enumeration_meas_observed_value_response_instance_list.at(meas_count).
          second = enum_obs_val_instance;

        DicesRcDriver status = ParseEnumerationContextResultTuple(
          _enumeration_meas_context_response_instance_list.at(meas_count).second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _enumeration_meas_context_response_instance_list.at(meas_count).
          first = DicesRcDriver::OK;

        status = ParseEnumerationObservedValueResultTuple(
          _enumeration_meas_observed_value_response_instance_list.
          at(meas_count).second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _enumeration_meas_observed_value_response_instance_list.at(meas_count).
          first = DicesRcDriver::NO_NEW_DATA;

        meas_count++;
      }
        break;
      case ice::MetricCategory::auto_calculation:
      case ice::MetricCategory::manual_calculation:
      {
        _enumeration_calc_context_response_instance_list.at(calc_count).
          second = enum_context_instance;
        _enumeration_calc_observed_value_response_instance_list.at(calc_count).
          second = enum_obs_val_instance;

        DicesRcDriver status = ParseEnumerationContextResultTuple(
          _enumeration_calc_context_response_instance_list.at(calc_count)
          .second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _enumeration_calc_context_response_instance_list.at(calc_count).
          first = DicesRcDriver::OK;

        status = ParseEnumerationObservedValueResultTuple(
          _enumeration_calc_observed_value_response_instance_list.
          at(calc_count).second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _enumeration_calc_observed_value_response_instance_list.at(calc_count).
          first = DicesRcDriver::NO_NEW_DATA;

        calc_count++;
      }
        break;
      case ice::MetricCategory::auto_setting:
      case ice::MetricCategory::manual_setting:
      {
        _enumeration_sett_context_response_instance_list.at(sett_count).
          second = enum_context_instance;
        _enumeration_sett_observed_value_response_instance_list.at(sett_count).
          second = enum_obs_val_instance;

        DicesRcDriver status = ParseEnumerationContextResultTuple(
          _enumeration_sett_context_response_instance_list.
          at(sett_count).second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _enumeration_sett_context_response_instance_list.at(sett_count).
          first = DicesRcDriver::OK;

        status = ParseEnumerationObservedValueResultTuple(
          _enumeration_sett_observed_value_response_instance_list.
          at(sett_count).second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _enumeration_sett_observed_value_response_instance_list.at(sett_count).
          first = DicesRcDriver::NO_NEW_DATA;

        sett_count++;
      }
        break;
      case ice::MetricCategory::mcat_unspec:
      default:
      {
        LOG4CPLUS_WARN(root_logger, sfn << "Cannot determine from "
          "MetricCategory (" << static_cast<int>(category) << ") if "
          "enumeration is measurement, calculation, and setting.");

        DDS::ReturnCode_t retcode = ice::EnumerationContextTypeSupport::
          delete_data(enum_context_instance);
        if (retcode != DDS::RETCODE_OK)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to delete_data() for "
            "EnumerationContext instance.");
        }
        enum_context_instance = nullptr;

        retcode = ice::EnumerationObservedValueTypeSupport::
          delete_data(enum_obs_val_instance);
        if (retcode != DDS::RETCODE_OK)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to delete_data() for "
            "EnumerationObservedValue instance.");
        }
        enum_obs_val_instance = nullptr;
      }
        break;
    }
  }
  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ParseEnumerationContextResultTuple(
  ice::EnumerationContext* instance,
  const pqxx::result::tuple& table_tuple)
{
  static const char* sfn = "Parser::ParseEnumerationContextResultTuple() ";
  if (instance == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument instance is a null pointer.");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }

  if (table_tuple.size() < kExpectedEnumContextsTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table tuple contains "
      << table_tuple.size() << " columns, but this function requires "
      << kExpectedEnumContextsTableColumnCount << " columns to parse "
      "successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  strncpy(
    instance->ice_id,
    table_tuple[2].as<std::string>("").c_str(),
    ice::MAX_LEN_ICE_ID);
  instance->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  instance->handle = table_tuple[3].as<ice::HANDLE>(0);
  instance->parent_handle = table_tuple[4].as<ice::HANDLE>(0);
  instance->source_timestamp.seconds = table_tuple[5].as<long>(0);
  instance->source_timestamp.nanoseconds = table_tuple[6].as<long>(0);
  instance->type.partition = static_cast<ice::NomPartition>(
    table_tuple[7].as<int>(ice::NomPartition::nom_part_unspec));
  instance->type.code = table_tuple[8].as<ice::OIDType>(0);
  instance->context_seq_number = table_tuple[9].as<long>(0);
  instance->metric_specification.update_period.seconds =
    table_tuple[10].as<long>(0);
  instance->metric_specification.update_period.nanoseconds =
    table_tuple[11].as<long>(0);
  instance->metric_specification.category = static_cast<ice::MetricCategory>(
    table_tuple[12].as<int>(ice::MetricCategory::mcat_unspec));
  instance->metric_specification.access = table_tuple[13].as<
    ice::MetricAccess>(0);
  instance->metric_specification.relevance = table_tuple[14].as<
    ice::MetricRelevance>(0);
  if (table_tuple[15].is_null() && table_tuple[16].is_null())
  {
    instance->max_delay_time = nullptr;
  }
  else
  {
    instance->max_delay_time =
      reinterpret_cast<ice::Duration*>(DDS::Heap_malloc(sizeof(ice::Duration)));
    if (!instance->max_delay_time)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for max delay time");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->max_delay_time->seconds = table_tuple[15].as<long>(0);
    instance->max_delay_time->nanoseconds = table_tuple[16].as<long>(0);
  }
  strncpy(
    instance->vmo_label_string,
    table_tuple[17].as<std::string>("").c_str(),
    ice::LONG_STRING_LEN);
  instance->vmo_label_string[ice::LONG_STRING_LEN] = '\0';
  // VmoSourceList
  // NOTE: If any fields are null, then the VmoSourceList sequence will be
  // empty.
  if (!table_tuple[18].is_null()
    && !table_tuple[19].is_null()
    && !table_tuple[20].is_null())
  {
    std::string vmo_src_list_vmo_type_str = table_tuple[18].
      as<std::string>("");
    std::string vmo_src_list_context_id_str = table_tuple[19].
      as<std::string>("");
    std::string vmo_src_list_handle_str = table_tuple[20].
      as<std::string>("");
    std::vector < std::pair < ice::INTU16, bool>> vmo_src_list_vmo_type_vect;
    std::vector < std::pair < ice::INTU16, bool>> vmo_src_list_context_id_vect;
    std::vector < std::pair < ice::INTU16, bool>> vmo_src_list_handle_vect;
    DicesRcDriver status = ParseCSVToArray(
      &vmo_src_list_vmo_type_vect,
      vmo_src_list_vmo_type_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(
      &vmo_src_list_context_id_vect,
      vmo_src_list_context_id_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(
      &vmo_src_list_handle_vect,
      vmo_src_list_handle_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    if (vmo_src_list_vmo_type_vect.size() != vmo_src_list_context_id_vect.size()
      || vmo_src_list_vmo_type_vect.size() != vmo_src_list_handle_vect.size())
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "To set ice::VmoSourceList "
        "sequence, vmo_type, context_id, and handle must have the "
        "same number of elements");
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < vmo_src_list_vmo_type_vect.size(); iy++)
    {
      if (!vmo_src_list_vmo_type_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::VmoSourceEntry, "
          "vmo_type data member is not optional, therefore null is not an "
          "acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < vmo_src_list_context_id_vect.size(); iy++)
    {
      if (!vmo_src_list_context_id_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::GLBHANDLE, "
          "context_id data member is not optional, therefore null is not "
          "an acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < vmo_src_list_handle_vect.size(); iy++)
    {
      if (!vmo_src_list_handle_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::GLBHANDLE, "
          "handle data member is not optional, therefore null is not "
          "an acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->vmo_source_list.ensure_length(
      vmo_src_list_vmo_type_vect.size(),
      vmo_src_list_vmo_type_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::VmoSourceList DDS sequence with length: "
        << vmo_src_list_vmo_type_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < vmo_src_list_vmo_type_vect.size(); iy++)
    {
      instance->vmo_source_list[iy].vmo_type = static_cast<ice::OIDType>(
        vmo_src_list_vmo_type_vect.at(iy).first);
    }
    for (int iy = 0; iy < vmo_src_list_context_id_vect.size(); iy++)
    {
      instance->vmo_source_list[iy].glb_handle.context_id =
        static_cast<ice::MdsContext>(vmo_src_list_context_id_vect.at(iy).
        first);
    }
    for (int iy = 0; iy < vmo_src_list_handle_vect.size(); iy++)
    {
      instance->vmo_source_list[iy].glb_handle.handle =
        static_cast<ice::HANDLE>(vmo_src_list_handle_vect.at(iy).first);
    }
  }
  // MetricSourceList
  // NOTE: If any fields are null, then the MetricSourceList sequence will be
  // empty.
  if (!table_tuple[21].is_null())
  {
    std::string metric_source_list_str = table_tuple[21].
      as<std::string>("");
    std::vector < std::pair < ice::INTU16, bool>> metric_source_list_vect;
    DicesRcDriver status = ParseCSVToArray(
      &metric_source_list_vect,
      metric_source_list_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    for (int iy = 0; iy < metric_source_list_vect.size(); iy++)
    {
      if (!metric_source_list_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::MetricSourceList, "
          "each element is an ice::OIDType and is not optional, therefore "
          "null is not an acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->metric_source_list.ensure_length(
      metric_source_list_vect.size(),
      metric_source_list_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::MetricSourceList DDS sequence with length: "
        << metric_source_list_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < metric_source_list_vect.size(); iy++)
    {
      instance->metric_source_list[iy] = static_cast<ice::OIDType>(
        metric_source_list_vect.at(iy).first);
    }
  }
  instance->unit_code = table_tuple[22].as<ice::OIDType>(0);
  strncpy(
    instance->unit_label_string,
    table_tuple[23].as<std::string>("").c_str(),
    ice::LONG_STRING_LEN);
  instance->unit_label_string[ice::LONG_STRING_LEN] = '\0';
  // SiteList msmt_site_list
  // NOTE: If any fields are null, then the SiteList sequence will be
  // empty.
  if (!table_tuple[24].is_null())
  {
    std::string msmt_site_list_str = table_tuple[24].
      as<std::string>("");
    std::vector < std::pair < ice::INTU16, bool>>msmt_site_list_vect;
    DicesRcDriver status = ParseCSVToArray(
      &msmt_site_list_vect,
      msmt_site_list_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    for (int iy = 0; iy < msmt_site_list_vect.size(); iy++)
    {
      if (!msmt_site_list_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::SiteList "
          "(msmt_site_list), each element is an ice::OIDType and is not "
          "optional, therefore null is not an acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->msmt_site_list.ensure_length(
      msmt_site_list_vect.size(),
      msmt_site_list_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::SiteList (msmt_site_list) DDS sequence with length: "
        << msmt_site_list_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < msmt_site_list_vect.size(); iy++)
    {
      instance->msmt_site_list[iy] = static_cast<ice::OIDType>(
        msmt_site_list_vect.at(iy).first);
    }
  }
  // SiteList body_site_list
  // NOTE: If any fields are null, then the SiteList sequence will be
  // empty.
  if (!table_tuple[25].is_null())
  {
    std::string body_site_list_str = table_tuple[25].
      as<std::string>("");
    std::vector < std::pair < ice::INTU16, bool>>body_site_list_vect;
    DicesRcDriver status = ParseCSVToArray(
      &body_site_list_vect,
      body_site_list_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    for (int iy = 0; iy < body_site_list_vect.size(); iy++)
    {
      if (!body_site_list_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::SiteList "
          "(body_site_list), each element is an ice::OIDType and is not "
          "optional, therefore null is not an acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->body_site_list.ensure_length(
      body_site_list_vect.size(),
      body_site_list_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::SiteList (body_site_list) DDS sequence with length: "
        << body_site_list_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < body_site_list_vect.size(); iy++)
    {
      instance->body_site_list[iy] = static_cast<ice::OIDType>(
        body_site_list_vect.at(iy).first);
    }
  }
  instance->metric_status = table_tuple[26].as<ice::MetricStatus>(0);
  if (table_tuple[27].is_null() && table_tuple[28].is_null())
  {
    instance->measure_period = nullptr;
  }
  else
  {
    instance->measure_period =
      reinterpret_cast<ice::MetricMeasure*>(DDS::Heap_malloc(
      sizeof(ice::MetricMeasure)));
    if (!instance->measure_period)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for measure period");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->measure_period->value = table_tuple[27].as<ice::FLOATType>(0);
    instance->measure_period->unit_code = table_tuple[28].as<
      ice::OIDType>(0);
  }
  if (table_tuple[29].is_null() && table_tuple[30].is_null())
  {
    instance->averaging_period = nullptr;
  }
  else
  {
    instance->averaging_period =
      reinterpret_cast<ice::MetricMeasure*>(DDS::Heap_malloc(
      sizeof(ice::MetricMeasure)));
    if (!instance->averaging_period)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for averaging period");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->averaging_period->value = table_tuple[29].as<
      ice::FLOATType>(0);
    instance->averaging_period->unit_code = table_tuple[30].as<
      ice::OIDType>(0);
  }
  if (table_tuple[31].is_null() && table_tuple[32].is_null())
  {
    instance->start_time = nullptr;
  }
  else
  {
    instance->start_time =
      reinterpret_cast<ice::Timespec*>(DDS::Heap_malloc(
      sizeof(ice::Timespec)));
    if (!instance->start_time)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for start time");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->start_time->seconds = table_tuple[31].as<long>(0);
    instance->start_time->nanoseconds = table_tuple[32].as<long>(0);
  }
  if (table_tuple[33].is_null() && table_tuple[34].is_null())
  {
    instance->stop_time = nullptr;
  }
  else
  {
    instance->stop_time =
      reinterpret_cast<ice::Timespec*>(DDS::Heap_malloc(
      sizeof(ice::Timespec)));
    if (!instance->stop_time)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for stop time");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->stop_time->seconds = table_tuple[33].as<long>(0);
    instance->stop_time->nanoseconds = table_tuple[34].as<long>(0);
  }
  // MetricCalibration
  // NOTE: If any fields are null, then the MetricCalibration sequence will be
  // empty.
  if (!table_tuple[35].is_null()
    && !table_tuple[36].is_null()
    && !table_tuple[37].is_null()
    && !table_tuple[38].is_null())
  {
    std::string metric_cal_type_str = table_tuple[35].
      as<std::string>("");
    std::string metric_cal_state_str = table_tuple[36].
      as<std::string>("");
    std::string metric_cal_time_secs_str = table_tuple[37].
      as<std::string>("");
    std::string metric_cal_time_nsecs_str = table_tuple[38].
      as<std::string>("");
    std::vector < std::pair < ice::INT32, bool>>metric_cal_type_vect;
    std::vector < std::pair < ice::INT32, bool>>metric_cal_state_vect;
    std::vector < std::pair < ice::INT32, bool>>metric_cal_time_secs_vect;
    std::vector < std::pair < ice::INT32, bool>>metric_cal_time_nsecs_vect;
    DicesRcDriver status = ParseCSVToArray(
      &metric_cal_type_vect,
      metric_cal_type_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(
      &metric_cal_state_vect,
      metric_cal_state_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(
      &metric_cal_time_secs_vect,
      metric_cal_time_secs_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(
      &metric_cal_time_nsecs_vect,
      metric_cal_time_nsecs_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    if (metric_cal_type_vect.size() != metric_cal_state_vect.size()
      || metric_cal_type_vect.size() != metric_cal_time_secs_vect.size()
      || metric_cal_type_vect.size() != metric_cal_time_nsecs_vect.size())
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "To set ice::MetricCalibration "
        "sequence, cal_type, cal_state, cal_time_seconds, and "
        "cal_time_nanoseconds must have the same number of elements");
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < metric_cal_type_vect.size(); iy++)
    {
      if (!metric_cal_type_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::MetricCalEntry, "
          "cal_type is not optional, therefore null is not an acceptable "
          "value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < metric_cal_state_vect.size(); iy++)
    {
      if (!metric_cal_state_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::MetricCalEntry, "
          "cal_state is not optional, therefore null is not an acceptable "
          "value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < metric_cal_time_secs_vect.size(); iy++)
    {
      if (!metric_cal_time_secs_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::Timespec, "
          "seconds is not optional, therefore null is not an acceptable "
          "value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < metric_cal_time_nsecs_vect.size(); iy++)
    {
      if (!metric_cal_time_nsecs_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::Timespec, "
          "nanoseconds is not optional, therefore null is not an acceptable "
          "value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->metric_calibration.ensure_length(
      metric_cal_type_vect.size(),
      metric_cal_type_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::MetricCalibration DDS sequence with length: "
        << metric_cal_type_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < metric_cal_type_vect.size(); iy++)
    {
      instance->metric_calibration[iy].cal_type =
        static_cast<ice::MetricCalType>(metric_cal_type_vect.at(iy).first);
    }
    for (int iy = 0; iy < metric_cal_state_vect.size(); iy++)
    {
      instance->metric_calibration[iy].cal_state =
        static_cast<ice::MetricCalState>(metric_cal_state_vect.at(iy).first);
    }
    for (int iy = 0; iy < metric_cal_time_secs_vect.size(); iy++)
    {
      instance->metric_calibration[iy].cal_time.seconds =
        static_cast<DDS::Long>(metric_cal_time_secs_vect.at(iy).first);
    }
    for (int iy = 0; iy < metric_cal_time_nsecs_vect.size(); iy++)
    {
      instance->metric_calibration[iy].cal_time.nanoseconds =
        static_cast<DDS::Long>(metric_cal_time_nsecs_vect.at(iy).first);
    }
  }
  if (table_tuple[39].is_null())
  {
    instance->color = nullptr;
  }
  else
  {
    instance->color = reinterpret_cast<ice::SimpleColor*>(
      DDS::Heap_malloc(sizeof(ice::SimpleColor)));
    if (!instance->color)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for color");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    *instance->color = static_cast<ice::SimpleColor>(
      table_tuple[39].as<int>(ice::SimpleColor::col_black));
  }
  instance->measurement_status = table_tuple[40].as<ice::MeasurementStatus>(0);
  instance->metric_id = table_tuple[41].as<ice::OIDType>(0);
  strncpy(
    instance->metric_info_label_string,
    table_tuple[42].as<std::string>("").c_str(),
    ice::LONG_STRING_LEN);
  instance->metric_info_label_string[ice::LONG_STRING_LEN] = '\0';
  if (table_tuple[43].is_null() && table_tuple[44].is_null())
  {
    instance->substance = nullptr;
  }
  else
  {
    instance->substance = reinterpret_cast<ice::ExtNomenRef*>(
      DDS::Heap_malloc(sizeof(ice::ExtNomenRef)));
    if (!instance->substance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for substance");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->substance->nomenclature_id = table_tuple[43].as<
      ice::OIDType>(0);
    instance->substance->nomenclature_code = DDS::String_alloc(
      ice::LONG_STRING_LEN);
    if (!instance->substance->nomenclature_code)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for substance nomenclature code");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    strncpy(
      instance->substance->nomenclature_code,
      table_tuple[44].as<std::string>("").c_str(),
      ice::LONG_STRING_LEN);
    instance->substance->nomenclature_code[ice::LONG_STRING_LEN] = '\0';
  }
  strncpy(
    instance->substance_label_string,
    table_tuple[45].as<std::string>("").c_str(),
    ice::LONG_STRING_LEN);
  instance->substance_label_string[ice::LONG_STRING_LEN] = '\0';
  // EnumMsmtRange
  // NOTE: If any fields are null, then the EnumMsmtRange sequence will be
  // empty.
  if (!table_tuple[46].is_null())
  {
    std::string msmt_range_str = table_tuple[46].as<std::string>("");
    std::vector < std::pair < ice::INTU16, bool>>msmt_range_vect;
    DicesRcDriver status = ParseCSVToArray(
      &msmt_range_vect,
      msmt_range_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    for (int iy = 0; iy < msmt_range_vect.size(); iy++)
    {
      if (!msmt_range_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::EnumMsmtRange, "
          "each element is an ice::OIDType and is not optional, therefore "
          "null is not an acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->enum_measure_range.ensure_length(
      msmt_range_vect.size(),
      msmt_range_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::EnumMsmtRange DDS sequence with length: "
        << msmt_range_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < msmt_range_vect.size(); iy++)
    {
      instance->enum_measure_range[iy] = static_cast<ice::OIDType>(
        msmt_range_vect.at(iy).first);
    }
  }
  if (table_tuple[47].is_null())
  {
    instance->enum_measure_range_bits = nullptr;
  }
  else
  {
    instance->enum_measure_range_bits = reinterpret_cast<ice::BITS32*>(
      DDS::Heap_malloc(sizeof(ice::BITS32)));
    if (!instance->enum_measure_range_bits)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for enum measure range bits");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    *instance->enum_measure_range_bits = table_tuple[47].as<ice::BITS32>(0);
  }
  // EnumMsmtRangeLabels
  // NOTE: If any fields are null, then the EnumMsmtRangeLabels sequence will
  // be empty.
  if (!table_tuple[48].is_null()
    && !table_tuple[49].is_null())
  {
    // TODO: How do we parse union, field 48?
    std::string label_str = table_tuple[49].as<std::string>("");
    std::vector < std::pair < std::string, bool>>label_vect;
    DicesRcDriver status = ParseCSVToArray(&label_vect, label_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    // TODO make sure sizes of vectors are the same
    // TODO check value vector for null elements
    // NOTE: If a label string is marked with null, then an empty
    // string is stored in the string. This is because label is not
    // optional in ice::EnumMsmtRangeLabel.
    if (instance->enum_measure_range_labels.ensure_length(
      label_vect.size(),
      label_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::EnumMsmtRangeLabels DDS sequence with length: "
        << label_vect.size());
      return DicesRcDriver::FAIL;
    }
    // TODO Store value
    for (int iy = 0; iy < label_vect.size(); iy++)
    {
      strncpy(
      instance->enum_measure_range_labels[iy].label,
        label_vect.at(iy).first.c_str(),
        ice::LONG_STRING_LEN);
      instance->enum_measure_range_labels[iy].label[
        ice::LONG_STRING_LEN] = '\0';
    }
  }

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ParseEnumerationObservedValueResultTuple(
  ice::EnumerationObservedValue* instance,
  const pqxx::result::tuple& table_tuple)
{
  static const char* sfn = "Parser::ParseEnumerationObservedValueResultTuple() ";
  if (instance == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument instance is a null pointer.");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }

  if (table_tuple.size() < kExpectedEnumContextsTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table tuple contains "
      << table_tuple.size() << " columns, but this function requires "
      << kExpectedEnumContextsTableColumnCount << " columns to parse "
      "successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  strncpy(
    instance->ice_id,
    table_tuple[2].as<std::string>("").c_str(),
    ice::MAX_LEN_ICE_ID);
  instance->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  instance->handle = table_tuple[3].as<ice::HANDLE>(0);
  instance->parent_handle = table_tuple[4].as<ice::HANDLE>(0);
  instance->source_timestamp.seconds = table_tuple[5].as<long>(0);
  instance->source_timestamp.nanoseconds = table_tuple[6].as<long>(0);
  instance->type.partition = static_cast<ice::NomPartition>(
    table_tuple[7].as<int>(ice::NomPartition::nom_part_unspec));
  instance->type.code = table_tuple[8].as<ice::OIDType>(0);
  instance->context_seq_number = table_tuple[9].as<long>(0);
  instance->enum_observed_value.state = table_tuple[40].as<
    ice::MeasurementStatus>(0);
  instance->enum_observed_value.metric_id = table_tuple[41].as<
    ice::OIDType>(0);

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ReadFromRTSATable()
{
  static const char* sfn = "Parser::ReadFromRTSATable() ";

  if (_database_connection == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Database is not connected");
    return DicesRcDriver::DATABASE_CONNECTION_FAILURE;
  }

  std::string column_names =
    kHeaderColumnNames + ", " + kTopColumnNames + ", " + kVMOColumnNames
    + ", " + kMetricContextColumnNames + ", " + kSampleArrayContextColumnNames
    + ", " + kRTSAContextColumnNames;
  pqxx::result table_result;
  try
  {
    pqxx::work database_work(*_database_connection);
    table_result = database_work.exec(
      "SELECT " + column_names + " FROM " + std::string(kTableRTSA) + ";");
    database_work.commit();
  }
  catch (const std::exception &ex)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to read the "
      << kTableRTSA << " table from the database. " << ex.what());
    return DicesRcDriver::DATABASE_READ_TABLE_FAILURE;
  }

  if (table_result.columns() < kExpectedRTSAContextsTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table result contains "
      << table_result.columns() << " columns, but this function requires "
      << kExpectedRTSAContextsTableColumnCount << " columns to parse "
      "successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  int meas_count = 0;
  int calc_count = 0;
  int sett_count = 0;
  for (int ix = 0; ix < table_result.size(); ix++)
  {
    ice::MetricCategory category = static_cast<ice::MetricCategory>(
      table_result[ix][12].as<int>(ice::MetricCategory::mcat_unspec));
    switch (category)
    {
      case ice::MetricCategory::auto_measurement:
      case ice::MetricCategory::manual_measurement:
        meas_count++;
        break;
      case ice::MetricCategory::auto_calculation:
      case ice::MetricCategory::manual_calculation:
        calc_count++;
        break;
      case ice::MetricCategory::auto_setting:
      case ice::MetricCategory::manual_setting:
        sett_count++;
        break;
      case ice::MetricCategory::mcat_unspec:
      default:
        LOG4CPLUS_WARN(root_logger, sfn << "Cannot determine from "
          "MetricCategory (" << static_cast<int>(category) << ") if "
          "enumeration is measurement, calculation, and setting.");
        break;
    }
  }

  try
  {
    _rtsa_meas_context_response_instance_list.resize(meas_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "RTSAContext measurement instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  try
  {
    _rtsa_meas_observed_value_response_instance_list.resize(meas_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "RTSAObservedValue measurement instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  try
  {
    _rtsa_calc_context_response_instance_list.resize(calc_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "RTSAContext calculation instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  try
  {
    _rtsa_calc_observed_value_response_instance_list.resize(calc_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "RTSAObservedValue calculation instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  try
  {
    _rtsa_sett_context_response_instance_list.resize(sett_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "RTSAContext setting instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  try
  {
    _rtsa_sett_observed_value_response_instance_list.resize(sett_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "RTSAObservedValue setting instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  // Use counters as indexes now.
  meas_count = 0;
  calc_count = 0;
  sett_count = 0;
  for (int ix = 0; ix < table_result.size(); ix++)
  {
    ice::RTSAContext* rtsa_context_instance =
      ice::RTSAContextTypeSupport::create_data();
    if (!rtsa_context_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for "
        "RTSAContext");
      return DicesRcDriver::RTSA_CONTEXT_INSTANCE_CREATE_FAILURE;
    }
    ice::RTSAObservedValue* rtsa_obs_val_instance =
      ice::RTSAObservedValueTypeSupport::create_data();
    if (!rtsa_obs_val_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for "
        "RTSAObservedValue");
      DDS::ReturnCode_t retcode = ice::RTSAContextTypeSupport::
        delete_data(rtsa_context_instance);
      if (retcode != DDS::RETCODE_OK)
      {
        LOG4CPLUS_WARN(root_logger, sfn << "Failed to delete_data() for "
          "RTSAContext instance");
      }
      rtsa_context_instance = nullptr;
      return DicesRcDriver::RTSA_OBSERVED_VALUE_INSTANCE_CREATE_FAILURE;
    }

    ice::MetricCategory category = static_cast<ice::MetricCategory>(
      table_result[ix][12].as<int>(ice::MetricCategory::mcat_unspec));
    switch (category)
    {
      case ice::MetricCategory::auto_measurement:
      case ice::MetricCategory::manual_measurement:
      {
        _rtsa_meas_context_response_instance_list.at(meas_count).
          second = rtsa_context_instance;
        _rtsa_meas_observed_value_response_instance_list.at(meas_count).
          second = rtsa_obs_val_instance;

        DicesRcDriver status = ParseRTSAContextResultTuple(
          _rtsa_meas_context_response_instance_list.at(meas_count).second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _rtsa_meas_context_response_instance_list.at(meas_count).
          first = DicesRcDriver::OK;

        status = ParseRTSAObservedValueResultTuple(
          _rtsa_meas_observed_value_response_instance_list.at(meas_count).
          second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _rtsa_meas_observed_value_response_instance_list.at(meas_count).
          first = DicesRcDriver::NO_NEW_DATA;

        meas_count++;
      }
        break;
      case ice::MetricCategory::auto_calculation:
      case ice::MetricCategory::manual_calculation:
      {
        _rtsa_calc_context_response_instance_list.at(calc_count).
          second = rtsa_context_instance;
        _rtsa_calc_observed_value_response_instance_list.at(calc_count).
          second = rtsa_obs_val_instance;

        DicesRcDriver status = ParseRTSAContextResultTuple(
          _rtsa_calc_context_response_instance_list.at(calc_count).second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _rtsa_calc_context_response_instance_list.at(calc_count).
          first = DicesRcDriver::OK;

        status = ParseRTSAObservedValueResultTuple(
          _rtsa_calc_observed_value_response_instance_list.at(calc_count).
          second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _rtsa_calc_observed_value_response_instance_list.at(calc_count).
          first = DicesRcDriver::NO_NEW_DATA;

        calc_count++;
      }
        break;
      case ice::MetricCategory::auto_setting:
      case ice::MetricCategory::manual_setting:
      {
        _rtsa_sett_context_response_instance_list.at(sett_count).
          second = rtsa_context_instance;
        _rtsa_sett_observed_value_response_instance_list.at(sett_count).
          second = rtsa_obs_val_instance;

        DicesRcDriver status = ParseRTSAContextResultTuple(
          _rtsa_sett_context_response_instance_list.at(sett_count).second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _rtsa_sett_context_response_instance_list.at(sett_count).
          first = DicesRcDriver::OK;

        status = ParseRTSAObservedValueResultTuple(
          _rtsa_sett_observed_value_response_instance_list.at(sett_count).second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _rtsa_sett_observed_value_response_instance_list.at(sett_count).
          first = DicesRcDriver::NO_NEW_DATA;

        sett_count++;
      }
        break;
      case ice::MetricCategory::mcat_unspec:
      default:
      {
        LOG4CPLUS_WARN(root_logger, sfn << "Cannot determine from "
          "MetricCategory (" << static_cast<int>(category) << ") if "
          "enumeration is measurement, calculation, and setting.");

        DDS::ReturnCode_t retcode = ice::RTSAContextTypeSupport::
          delete_data(rtsa_context_instance);
        if (retcode != DDS::RETCODE_OK)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to delete_data() for "
            "RTSAContext instance");
        }
        rtsa_context_instance = nullptr;

        retcode = ice::RTSAObservedValueTypeSupport::
          delete_data(rtsa_obs_val_instance);
        if (retcode != DDS::RETCODE_OK)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to delete_data() for "
            "RTSAObservedValue instance");
        }
        rtsa_obs_val_instance = nullptr;
      }
        break;
    }
  }
  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ParseRTSAContextResultTuple(
  ice::RTSAContext* instance,
  const pqxx::result::tuple& table_tuple)
{
  static const char* sfn = "Parser::ParseRTSAContextResultTuple() ";
  if (instance == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument instance is a null pointer.");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }

  if (table_tuple.size() < kExpectedRTSAContextsTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table tuple contains "
      << table_tuple.size() << " columns, but this function requires "
      << kExpectedRTSAContextsTableColumnCount << " columns to parse "
      "successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  strncpy(
    instance->ice_id,
    table_tuple[2].as<std::string>("").c_str(),
    ice::MAX_LEN_ICE_ID);
  instance->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  instance->handle = table_tuple[3].as<ice::HANDLE>(0);
  instance->parent_handle = table_tuple[4].as<ice::HANDLE>(0);
  instance->source_timestamp.seconds = table_tuple[5].as<long>(0);
  instance->source_timestamp.nanoseconds = table_tuple[6].as<long>(0);
  instance->type.partition = static_cast<ice::NomPartition>(
    table_tuple[7].as<int>(ice::NomPartition::nom_part_unspec));
  instance->type.code = table_tuple[8].as<ice::OIDType>(0);
  instance->context_seq_number = table_tuple[9].as<long>(0);
  instance->metric_specification.update_period.seconds =
    table_tuple[10].as<long>(0);
  instance->metric_specification.update_period.nanoseconds =
    table_tuple[11].as<long>(0);
  instance->metric_specification.category = static_cast<ice::MetricCategory>(
    table_tuple[12].as<int>(ice::MetricCategory::mcat_unspec));
  instance->metric_specification.access = table_tuple[13].as<
    ice::MetricAccess>(0);
  instance->metric_specification.relevance = table_tuple[14].as<
    ice::MetricRelevance>(0);
  if (table_tuple[15].is_null() && table_tuple[16].is_null())
  {
    instance->max_delay_time = nullptr;
  }
  else
  {
    instance->max_delay_time =
      reinterpret_cast<ice::Duration*>(DDS::Heap_malloc(sizeof(ice::Duration)));
    if (!instance->max_delay_time)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for max delay time");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->max_delay_time->seconds = table_tuple[15].as<long>(0);
    instance->max_delay_time->nanoseconds = table_tuple[16].as<long>(0);
  }
  strncpy(
    instance->vmo_label_string,
    table_tuple[17].as<std::string>("").c_str(),
    ice::LONG_STRING_LEN);
  instance->vmo_label_string[ice::LONG_STRING_LEN] = '\0';
  // VmoSourceList
  // NOTE: If any fields are null, then the VmoSourceList sequence will be
  // empty.
  if (!table_tuple[18].is_null()
    && !table_tuple[19].is_null()
    && !table_tuple[20].is_null())
  {
    std::string vmo_src_list_vmo_type_str = table_tuple[18].
      as<std::string>("");
    std::string vmo_src_list_context_id_str = table_tuple[19].
      as<std::string>("");
    std::string vmo_src_list_handle_str = table_tuple[20].
      as<std::string>("");
    std::vector < std::pair < ice::INTU16, bool>> vmo_src_list_vmo_type_vect;
    std::vector < std::pair < ice::INTU16, bool>> vmo_src_list_context_id_vect;
    std::vector < std::pair < ice::INTU16, bool>> vmo_src_list_handle_vect;
    DicesRcDriver status = ParseCSVToArray(
      &vmo_src_list_vmo_type_vect,
      vmo_src_list_vmo_type_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(
      &vmo_src_list_context_id_vect,
      vmo_src_list_context_id_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(
      &vmo_src_list_handle_vect,
      vmo_src_list_handle_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    if (vmo_src_list_vmo_type_vect.size() != vmo_src_list_context_id_vect.size()
      || vmo_src_list_vmo_type_vect.size() != vmo_src_list_handle_vect.size())
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "To set ice::VmoSourceList "
        "sequence, vmo_type, context_id, and handle must have the "
        "same number of elements");
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < vmo_src_list_vmo_type_vect.size(); iy++)
    {
      if (!vmo_src_list_vmo_type_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::VmoSourceEntry, "
          "vmo_type data member is not optional, therefore null is not an "
          "acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < vmo_src_list_context_id_vect.size(); iy++)
    {
      if (!vmo_src_list_context_id_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::GLBHANDLE, "
          "context_id data member is not optional, therefore null is not "
          "an acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < vmo_src_list_handle_vect.size(); iy++)
    {
      if (!vmo_src_list_handle_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::GLBHANDLE, "
          "handle data member is not optional, therefore null is not "
          "an acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->vmo_source_list.ensure_length(
      vmo_src_list_vmo_type_vect.size(),
      vmo_src_list_vmo_type_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::VmoSourceList DDS sequence with length: "
        << vmo_src_list_vmo_type_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < vmo_src_list_vmo_type_vect.size(); iy++)
    {
      instance->vmo_source_list[iy].vmo_type = static_cast<ice::OIDType>(
        vmo_src_list_vmo_type_vect.at(iy).first);
    }
    for (int iy = 0; iy < vmo_src_list_context_id_vect.size(); iy++)
    {
      instance->vmo_source_list[iy].glb_handle.context_id =
        static_cast<ice::MdsContext>(vmo_src_list_context_id_vect.at(iy).
        first);
    }
    for (int iy = 0; iy < vmo_src_list_handle_vect.size(); iy++)
    {
      instance->vmo_source_list[iy].glb_handle.handle =
        static_cast<ice::HANDLE>(vmo_src_list_handle_vect.at(iy).first);
    }
  }
  // MetricSourceList
  // NOTE: If any fields are null, then the MetricSourceList sequence will be
  // empty.
  if (!table_tuple[21].is_null())
  {
    std::string metric_source_list_str = table_tuple[21].
      as<std::string>("");
    std::vector < std::pair < ice::INTU16, bool>> metric_source_list_vect;
    DicesRcDriver status = ParseCSVToArray(
      &metric_source_list_vect,
      metric_source_list_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    for (int iy = 0; iy < metric_source_list_vect.size(); iy++)
    {
      if (!metric_source_list_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::MetricSourceList, "
          "each element is an ice::OIDType and is not optional, therefore "
          "null is not an acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->metric_source_list.ensure_length(
      metric_source_list_vect.size(),
      metric_source_list_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::MetricSourceList DDS sequence with length: "
        << metric_source_list_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < metric_source_list_vect.size(); iy++)
    {
      instance->metric_source_list[iy] = static_cast<ice::OIDType>(
        metric_source_list_vect.at(iy).first);
    }
  }
  instance->unit_code = table_tuple[22].as<ice::OIDType>(0);
  strncpy(
    instance->unit_label_string,
    table_tuple[23].as<std::string>("").c_str(),
    ice::LONG_STRING_LEN);
  instance->unit_label_string[ice::LONG_STRING_LEN] = '\0';
  // SiteList msmt_site_list
  // NOTE: If any fields are null, then the SiteList sequence will be
  // empty.
  if (!table_tuple[24].is_null())
  {
    std::string msmt_site_list_str = table_tuple[24].
      as<std::string>("");
    std::vector < std::pair < ice::INTU16, bool>>msmt_site_list_vect;
    DicesRcDriver status = ParseCSVToArray(
      &msmt_site_list_vect,
      msmt_site_list_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    for (int iy = 0; iy < msmt_site_list_vect.size(); iy++)
    {
      if (!msmt_site_list_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::SiteList "
          "(msmt_site_list), each element is an ice::OIDType and is not "
          "optional, therefore null is not an acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->msmt_site_list.ensure_length(
      msmt_site_list_vect.size(),
      msmt_site_list_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::SiteList (msmt_site_list) DDS sequence with length: "
        << msmt_site_list_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < msmt_site_list_vect.size(); iy++)
    {
      instance->msmt_site_list[iy] = static_cast<ice::OIDType>(
        msmt_site_list_vect.at(iy).first);
    }
  }
  // SiteList body_site_list
  // NOTE: If any fields are null, then the SiteList sequence will be
  // empty.
  if (!table_tuple[25].is_null())
  {
    std::string body_site_list_str = table_tuple[25].
      as<std::string>("");
    std::vector < std::pair < ice::INTU16, bool>>body_site_list_vect;
    DicesRcDriver status = ParseCSVToArray(
      &body_site_list_vect,
      body_site_list_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    for (int iy = 0; iy < body_site_list_vect.size(); iy++)
    {
      if (!body_site_list_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::SiteList "
          "(body_site_list), each element is an ice::OIDType and is not "
          "optional, therefore null is not an acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->body_site_list.ensure_length(
      body_site_list_vect.size(),
      body_site_list_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::SiteList (body_site_list) DDS sequence with length: "
        << body_site_list_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < body_site_list_vect.size(); iy++)
    {
      instance->body_site_list[iy] = static_cast<ice::OIDType>(
        body_site_list_vect.at(iy).first);
    }
  }
  instance->metric_status = table_tuple[26].as<ice::MetricStatus>(0);
  if (table_tuple[27].is_null() && table_tuple[28].is_null())
  {
    instance->measure_period = nullptr;
  }
  else
  {
    instance->measure_period =
      reinterpret_cast<ice::MetricMeasure*>(DDS::Heap_malloc(sizeof(
      ice::MetricMeasure)));
    if (!instance->measure_period)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for measure period");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->measure_period->value = table_tuple[27].as<ice::FLOATType>(0);
    instance->measure_period->unit_code = table_tuple[28].as<
      ice::OIDType>(0);
  }
  if (table_tuple[29].is_null() && table_tuple[30].is_null())
  {
    instance->averaging_period = nullptr;
  }
  else
  {
    instance->averaging_period =
      reinterpret_cast<ice::MetricMeasure*>(DDS::Heap_malloc(sizeof(
      ice::MetricMeasure)));
    if (!instance->averaging_period)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for averaging period");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->averaging_period->value = table_tuple[29].as<
      ice::FLOATType>(0);
    instance->averaging_period->unit_code = table_tuple[30].as<
      ice::OIDType>(0);
  }
  if (table_tuple[31].is_null() && table_tuple[32].is_null())
  {
    instance->start_time = nullptr;
  }
  else
  {
    instance->start_time =
      reinterpret_cast<ice::Timespec*>(DDS::Heap_malloc(sizeof(
      ice::Timespec)));
    if (!instance->start_time)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for start time");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->start_time->seconds = table_tuple[31].as<long>(0);
    instance->start_time->nanoseconds = table_tuple[32].as<long>(0);
  }
  if (table_tuple[33].is_null() && table_tuple[34].is_null())
  {
    instance->stop_time = nullptr;
  }
  else
  {
    instance->stop_time =
      reinterpret_cast<ice::Timespec*>(DDS::Heap_malloc(sizeof(
      ice::Timespec)));
    if (!instance->stop_time)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for stop time");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->stop_time->seconds = table_tuple[33].as<long>(0);
    instance->stop_time->nanoseconds = table_tuple[34].as<long>(0);
  }
  // MetricCalibration
  // NOTE: If any fields are null, then the MetricCalibration sequence will be
  // empty.
  if (!table_tuple[35].is_null()
    && !table_tuple[36].is_null()
    && !table_tuple[37].is_null()
    && !table_tuple[38].is_null())
  {
    std::string metric_cal_type_str = table_tuple[35].
      as<std::string>("");
    std::string metric_cal_state_str = table_tuple[36].
      as<std::string>("");
    std::string metric_cal_time_secs_str = table_tuple[37].
      as<std::string>("");
    std::string metric_cal_time_nsecs_str = table_tuple[38].
      as<std::string>("");
    std::vector < std::pair < ice::INT32, bool>>metric_cal_type_vect;
    std::vector < std::pair < ice::INT32, bool>>metric_cal_state_vect;
    std::vector < std::pair < ice::INT32, bool>>metric_cal_time_secs_vect;
    std::vector < std::pair < ice::INT32, bool>>metric_cal_time_nsecs_vect;
    DicesRcDriver status = ParseCSVToArray(
      &metric_cal_type_vect,
      metric_cal_type_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(
      &metric_cal_state_vect,
      metric_cal_state_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(
      &metric_cal_time_secs_vect,
      metric_cal_time_secs_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(
      &metric_cal_time_nsecs_vect,
      metric_cal_time_nsecs_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    if (metric_cal_type_vect.size() != metric_cal_state_vect.size()
      || metric_cal_type_vect.size() != metric_cal_time_secs_vect.size()
      || metric_cal_type_vect.size() != metric_cal_time_nsecs_vect.size())
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "To set ice::MetricCalibration "
        "sequence, cal_type, cal_state, cal_time_seconds, and "
        "cal_time_nanoseconds must have the same number of elements");
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < metric_cal_type_vect.size(); iy++)
    {
      if (!metric_cal_type_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::MetricCalEntry, "
          "cal_type is not optional, therefore null is not an acceptable "
          "value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < metric_cal_state_vect.size(); iy++)
    {
      if (!metric_cal_state_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::MetricCalEntry, "
          "cal_state is not optional, therefore null is not an acceptable "
          "value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < metric_cal_time_secs_vect.size(); iy++)
    {
      if (!metric_cal_time_secs_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::Timespec, "
          "seconds is not optional, therefore null is not an acceptable "
          "value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < metric_cal_time_nsecs_vect.size(); iy++)
    {
      if (!metric_cal_time_nsecs_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::Timespec, "
          "nanoseconds is not optional, therefore null is not an acceptable "
          "value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->metric_calibration.ensure_length(
      metric_cal_type_vect.size(),
      metric_cal_type_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::MetricCalibration DDS sequence with length: "
        << metric_cal_type_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < metric_cal_type_vect.size(); iy++)
    {
      instance->metric_calibration[iy].cal_type =
        static_cast<ice::MetricCalType>(metric_cal_type_vect.at(iy).first);
    }
    for (int iy = 0; iy < metric_cal_state_vect.size(); iy++)
    {
      instance->metric_calibration[iy].cal_state =
        static_cast<ice::MetricCalState>(metric_cal_state_vect.at(iy).first);
    }
    for (int iy = 0; iy < metric_cal_time_secs_vect.size(); iy++)
    {
      instance->metric_calibration[iy].cal_time.seconds =
        static_cast<DDS::Long>(metric_cal_time_secs_vect.at(iy).first);
    }
    for (int iy = 0; iy < metric_cal_time_nsecs_vect.size(); iy++)
    {
      instance->metric_calibration[iy].cal_time.nanoseconds =
        static_cast<DDS::Long>(metric_cal_time_nsecs_vect.at(iy).first);
    }
  }
  if (table_tuple[39].is_null())
  {
    instance->color = nullptr;
  }
  else
  {
    instance->color = reinterpret_cast<ice::SimpleColor*>(
      DDS::Heap_malloc(sizeof(ice::SimpleColor)));
    if (!instance->color)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for color");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    *instance->color = static_cast<ice::SimpleColor>(
      table_tuple[39].as<int>(ice::SimpleColor::col_black));
  }
  instance->measurement_status = table_tuple[40].as<ice::MeasurementStatus>(0);
  instance->metric_id = table_tuple[41].as<ice::OIDType>(0);
  strncpy(
    instance->metric_info_label_string,
    table_tuple[42].as<std::string>("").c_str(),
    ice::LONG_STRING_LEN);
  instance->metric_info_label_string[ice::LONG_STRING_LEN] = '\0';
  if (table_tuple[43].is_null() && table_tuple[44].is_null())
  {
    instance->substance = nullptr;
  }
  else
  {
    instance->substance = reinterpret_cast<ice::ExtNomenRef*>(
      DDS::Heap_malloc(sizeof(ice::ExtNomenRef)));
    if (!instance->substance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for substance");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->substance->nomenclature_id = table_tuple[43].as<
      ice::OIDType>(0);
    instance->substance->nomenclature_code = DDS::String_alloc(
      ice::LONG_STRING_LEN);
    if (!instance->substance->nomenclature_code)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for substance nomenclature code");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    strncpy(
      instance->substance->nomenclature_code,
      table_tuple[44].as<std::string>("").c_str(),
      ice::LONG_STRING_LEN);
    instance->substance->nomenclature_code[ice::LONG_STRING_LEN] = '\0';
  }
  strncpy(
    instance->substance_label_string,
    table_tuple[45].as<std::string>("").c_str(),
    ice::LONG_STRING_LEN);
  instance->substance_label_string[ice::LONG_STRING_LEN] = '\0';
  instance->sa_specification.array_size = table_tuple[46].as<ice::INTU16>(0);
  if (table_tuple[47].is_null()
    && table_tuple[48].is_null()
    && table_tuple[49].is_null())
  {
    instance->sa_specification.sample_type = nullptr;
  }
  else
  {
    instance->sa_specification.sample_type = reinterpret_cast<ice::SampleType*>(
      DDS::Heap_malloc(sizeof(ice::SampleType)));
    if (!instance->sa_specification.sample_type)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for sa specification sample type");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
      table_tuple[47].as<std::string>(""),
      &instance->sa_specification.sample_type->sample_size);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ConvertPostgresByteaHexToICEINTU8(
      table_tuple[48].as<std::string>(""),
      &instance->sa_specification.sample_type->significant_bits);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ConvertPostgresByteaHexToICEINTU8(
      table_tuple[49].as<std::string>(""),
      &instance->sa_specification.sample_type->signed_samples);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
  }
  instance->sa_specification.flags = table_tuple[50].as<ice::SaFlags>(0);
  if (table_tuple[51].is_null())
  {
    instance->compression = nullptr;
  }
  else
  {
    instance->compression = reinterpret_cast<ice::PrivateOid*>(
      DDS::Heap_malloc(sizeof(ice::PrivateOid)));
    if (!instance->compression)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for compression");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    *instance->compression = table_tuple[51].as<ice::PrivateOid>(0);
  }
  // MarkerListSaVal
  // NOTE: If any fields are null, then the MarkerListSaVal sequence will be
  // empty.
  if (table_tuple[52].is_null()
    && table_tuple[53].is_null())
  {
    instance->sa_marker_list = nullptr;
  }
  else
  {
    instance->sa_marker_list = reinterpret_cast<ice::MarkerListSaVal*>(
      DDS::Heap_malloc(sizeof(ice::MarkerListSaVal)));
    if (!instance->sa_marker_list)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for ice::MarkerListSaVal");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    std::string marker_id_str = table_tuple[52].as<std::string>("");
    std::string marker_val_str = table_tuple[53].as<std::string>("");
    std::vector < std::pair < ice::INTU16, bool>>marker_id_vect;
    std::vector < std::pair < ice::INTU32, bool>>marker_val_vect;
    DicesRcDriver status = ParseCSVToArray(&marker_id_vect, marker_id_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(&marker_val_vect, marker_val_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    if (marker_id_vect.size() != marker_val_vect.size())
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "To set ice::MarkerListSaVal "
        "sequence, marker_id, and marker_val must have the same number of "
        "elements");
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < marker_id_vect.size(); iy++)
    {
      if (!marker_id_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::MarkerEntrySaVal, "
          "marker_id is not optional, therefore null is not an acceptable "
          "value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < marker_val_vect.size(); iy++)
    {
      if (!marker_val_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::MarkerEntrySaVal, "
          "marker_val is not optional, therefore null is not an acceptable "
          "value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->metric_calibration.ensure_length(
      marker_id_vect.size(),
      marker_id_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::MarkerListSaVal DDS sequence with length: "
        << marker_id_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < marker_id_vect.size(); iy++)
    {
      instance->sa_marker_list->operator[](iy).marker_id =
        static_cast<ice::OIDType>(marker_id_vect.at(iy).first);
    }
    for (int iy = 0; iy < marker_val_vect.size(); iy++)
    {
      instance->sa_marker_list->operator[](iy).marker_val =
        static_cast<ice::INTU32>(marker_val_vect.at(iy).first);
    }
  }
  instance->scale_and_range_specification.lower_absolute_value =
    table_tuple[54].as<ice::FLOATType>(0);
  instance->scale_and_range_specification.upper_absolute_value =
    table_tuple[55].as<ice::FLOATType>(0);
  instance->scale_and_range_specification.lower_scaled_value =
    table_tuple[56].as<ice::INTU32>(0);
  instance->scale_and_range_specification.upper_scaled_value =
    table_tuple[57].as<ice::INTU32>(0);
  if (table_tuple[58].is_null() && table_tuple[59].is_null())
  {
    instance->sa_physiological_range = nullptr;
  }
  else
  {
    instance->sa_physiological_range = reinterpret_cast<ice::ScaledRange*>(
      DDS::Heap_malloc(sizeof(ice::ScaledRange)));
    if (!instance->sa_physiological_range)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for sa physiological range");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->sa_physiological_range->lower_scaled_value =
      table_tuple[58].as<ice::INTU32>(0);
    instance->sa_physiological_range->upper_scaled_value =
      table_tuple[59].as<ice::INTU32>(0);
  }
  // SaVisualGrid
  // NOTE: If any fields are null, then the SaVisualGrid sequence will be
  // empty.
  if (!table_tuple[60].is_null()
    && !table_tuple[61].is_null()
    && !table_tuple[62].is_null())
  {
    std::string abs_val_str = table_tuple[60].as<std::string>("");
    std::string scaled_val_str = table_tuple[61].as<std::string>("");
    std::string level_str = table_tuple[62].as<std::string>("");
    std::vector < std::pair < ice::FLOATType, bool>>abs_val_vect;
    std::vector < std::pair < ice::INTU32, bool>>scaled_val_vect;
    std::vector < std::pair < ice::INTU16, bool>>level_vect;
    DicesRcDriver status = ParseCSVToArray(&abs_val_vect, abs_val_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(&scaled_val_vect, scaled_val_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(&level_vect, level_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    if (abs_val_vect.size() != scaled_val_vect.size()
      || abs_val_vect.size() != level_vect.size())
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "To set ice::SaVisualGrid "
        "sequence, absolute_value, scaled_value, and level must have the "
        "same number of elements");
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < abs_val_vect.size(); iy++)
    {
      if (!abs_val_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::SaGridEntry, "
          "absolute_value is not optional, therefore null is not an "
          "acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < scaled_val_vect.size(); iy++)
    {
      if (!scaled_val_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::SaGridEntry, "
          "scaled_value is not optional, therefore null is not an acceptable "
          "value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < level_vect.size(); iy++)
    {
      if (!level_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::SaGridEntry, "
          "level is not optional, therefore null is not an acceptable "
          "value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->visual_grid.ensure_length(
      abs_val_vect.size(),
      abs_val_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::SaVisualGrid DDS sequence with length: "
        << abs_val_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < abs_val_vect.size(); iy++)
    {
      instance->visual_grid[iy].absolute_value = static_cast<ice::FLOATType>(
        abs_val_vect.at(iy).first);
    }
    for (int iy = 0; iy < scaled_val_vect.size(); iy++)
    {
      instance->visual_grid[iy].scaled_value = static_cast<ice::INTU32>(
        scaled_val_vect.at(iy).first);
    }
    for (int iy = 0; iy < level_vect.size(); iy++)
    {
      instance->visual_grid[iy].level = static_cast<ice::INTU16>(
        level_vect.at(iy).first);
    }
  }
  if (table_tuple[63].is_null() && table_tuple[64].is_null()
    && table_tuple[65].is_null() && table_tuple[66].is_null()
    && table_tuple[67].is_null())
  {
    instance->sa_calibration_data = nullptr;
  }
  else
  {
    instance->sa_calibration_data = reinterpret_cast<ice::SaCalData*>(
      DDS::Heap_malloc(sizeof(ice::SaCalData)));
    if (!instance->sa_calibration_data)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for sa calibration data");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->sa_calibration_data->lower_absolute_value =
      table_tuple[63].as<ice::FLOATType>(0);
    instance->sa_calibration_data->upper_absolute_value =
      table_tuple[64].as<ice::FLOATType>(0);
    instance->sa_calibration_data->lower_scaled_value =
      table_tuple[65].as<ice::INTU32>(0);
    instance->sa_calibration_data->upper_scaled_value =
      table_tuple[66].as<ice::INTU32>(0);
    instance->sa_calibration_data->increment =
      table_tuple[67].as<ice::INTU32>(0);
    instance->sa_calibration_data->cal_type = static_cast<
      ice::SaCalDataType>(table_tuple[68].as<int>(ice::SaCalDataType::bar));
  }
  // SaFilterSpec
  // NOTE: If any fields are null, then the SaFilterSpec sequence will be
  // empty.
  if (!table_tuple[69].is_null()
    && !table_tuple[70].is_null()
    && !table_tuple[71].is_null())
  {
    std::string filter_type_str = table_tuple[69].as<std::string>("");
    std::string filter_freq_str = table_tuple[70].as<std::string>("");
    std::string filter_order_str = table_tuple[71].as<std::string>("");
    std::vector < std::pair < ice::INT32, bool>>filter_type_vect;
    std::vector < std::pair < ice::FLOATType, bool>>filter_freq_vect;
    std::vector < std::pair < ice::INT16, bool>>filter_order_vect;
    DicesRcDriver status = ParseCSVToArray(&filter_type_vect, filter_type_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(&filter_freq_vect, filter_freq_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(&filter_order_vect, filter_order_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    if (filter_type_vect.size() != filter_freq_vect.size()
      || filter_type_vect.size() != filter_order_vect.size())
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "To set ice::SaFilterSpec "
        "sequence, filter_type, filter_frequency, and filter_order must "
        "have the same number of elements");
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < filter_type_vect.size(); iy++)
    {
      if (!filter_type_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::SaFilterEntry, "
          "filter_type is not optional, therefore null is not an "
          "acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < filter_freq_vect.size(); iy++)
    {
      if (!filter_freq_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::SaFilterEntry, "
          "filter_frequency is not optional, therefore null is not an "
          "acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < filter_order_vect.size(); iy++)
    {
      if (!filter_order_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::SaFilterEntry, "
          "filter_order is not optional, therefore null is not an acceptable "
          "value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->filter_specification.ensure_length(
      filter_type_vect.size(),
      filter_type_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::SaFilterSpec DDS sequence with length: "
        << filter_type_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < filter_type_vect.size(); iy++)
    {
      instance->filter_specification[iy].filter_type =
        static_cast<ice::SaFilterType>(filter_type_vect.at(iy).first);
    }
    for (int iy = 0; iy < filter_freq_vect.size(); iy++)
    {
      instance->filter_specification[iy].filter_frequency =
        static_cast<ice::FLOATType>(filter_freq_vect.at(iy).first);
    }
    for (int iy = 0; iy < filter_order_vect.size(); iy++)
    {
      instance->filter_specification[iy].filter_order =
        static_cast<ice::INT16>(filter_order_vect.at(iy).first);
    }
  }
  strncpy(
    instance->filter_label_string,
    table_tuple[72].as<std::string>("").c_str(),
    ice::LONG_STRING_LEN);
  instance->filter_label_string[ice::LONG_STRING_LEN] = '\0';
  if (table_tuple[73].is_null() && table_tuple[74].is_null())
  {
    instance->sa_signal_frequency = nullptr;
  }
  else
  {
    instance->sa_signal_frequency = reinterpret_cast<ice::SaSignalFrequency*>(
      DDS::Heap_malloc(sizeof(ice::SaSignalFrequency)));
    if (!instance->sa_signal_frequency)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for sa signal frequency");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->sa_signal_frequency->low_edge_freq = table_tuple[73].as<
      ice::FLOATType>(0);
    instance->sa_signal_frequency->high_edge_freq = table_tuple[74].as<
      ice::FLOATType>(0);
  }
  if (table_tuple[75].is_null())
  {
    instance->sa_measure_resolution = nullptr;
  }
  else
  {
    instance->sa_measure_resolution = reinterpret_cast<ice::FLOATType*>(
      DDS::Heap_malloc(sizeof(ice::FLOATType)));
    if (!instance->sa_measure_resolution)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for sa measure resolution");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    *instance->sa_measure_resolution = table_tuple[75].as<ice::FLOATType>(0);
  }
  instance->sample_period.seconds = table_tuple[76].as<long>(0);
  instance->sample_period.nanoseconds = table_tuple[77].as<long>(0);
  if (table_tuple[78].is_null() && table_tuple[79].is_null())
  {
    instance->sweep_speed = nullptr;
  }
  else
  {
    instance->sweep_speed = reinterpret_cast<ice::MetricMeasure*>(
      DDS::Heap_malloc(sizeof(ice::MetricMeasure)));
    if (!instance->sweep_speed)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for sweep speed");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->sweep_speed->value = table_tuple[78].as<ice::FLOATType>(0);
    instance->sweep_speed->unit_code = table_tuple[79].as<ice::OIDType>(0);
  }
  if (table_tuple[80].is_null() && table_tuple[81].is_null())
  {
    instance->average_reporting_delay = nullptr;
  }
  else
  {
    instance->average_reporting_delay = reinterpret_cast<ice::Duration*>(
      DDS::Heap_malloc(sizeof(ice::Duration)));
    if (!instance->average_reporting_delay)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for average reporting delay");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->average_reporting_delay->seconds = table_tuple[80].as<long>(0);
    instance->average_reporting_delay->nanoseconds = table_tuple[81].as<long>(0);
  }
  if (table_tuple[82].is_null() && table_tuple[83].is_null())
  {
    instance->sample_time_sync = nullptr;
  }
  else
  {
    instance->sample_time_sync = reinterpret_cast<ice::Duration*>(
      DDS::Heap_malloc(sizeof(ice::Duration)));
    if (!instance->sample_time_sync)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
        "for sample time sync");
      return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
    }
    instance->sample_time_sync->seconds = table_tuple[82].as<long>(0);
    instance->sample_time_sync->nanoseconds = table_tuple[83].as<long>(0);
  }
  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ParseRTSAObservedValueResultTuple(
  ice::RTSAObservedValue* instance,
  const pqxx::result::tuple& table_tuple)
{
  static const char* sfn = "Parser::ParseRTSAObservedValueResultTuple() ";
  if (instance == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument instance is a null pointer.");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }

  if (table_tuple.size() < kExpectedRTSAContextsTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table tuple contains "
      << table_tuple.size() << " columns, but this function requires "
      << kExpectedRTSAContextsTableColumnCount << " columns to parse "
      "successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  strncpy(
    instance->ice_id,
    table_tuple[2].as<std::string>("").c_str(),
    ice::MAX_LEN_ICE_ID);
  instance->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  instance->handle = table_tuple[3].as<ice::HANDLE>(0);
  instance->parent_handle = table_tuple[4].as<ice::HANDLE>(0);
  instance->source_timestamp.seconds = table_tuple[5].as<long>(0);
  instance->source_timestamp.nanoseconds = table_tuple[6].as<long>(0);
  instance->type.partition = static_cast<ice::NomPartition>(
    table_tuple[7].as<int>(ice::NomPartition::nom_part_unspec));
  instance->type.code = table_tuple[8].as<ice::OIDType>(0);
  instance->context_seq_number = table_tuple[9].as<long>(0);
  instance->sa_observed_value.state = table_tuple[40].as<
    ice::MeasurementStatus>(0);
  instance->sa_observed_value.metric_id = table_tuple[41].as<ice::OIDType>(0);

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ReadFromAlarmsTable()
{
  static const char* sfn = "Parser::ReadFromAlarmsTable() ";

  if (_database_connection == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Database is not connected");
    return DicesRcDriver::DATABASE_CONNECTION_FAILURE;
  }

  std::string column_names =
    kHeaderColumnNames + ", " + kTopColumnNames + ", " + kVMOColumnNames
    + ", " + kAlarmContextColumnNames;
  pqxx::result table_result;
  try
  {
    pqxx::work database_work(*_database_connection);
    table_result = database_work.exec(
      "SELECT " + column_names + " FROM " + std::string(kTableAlarms) + ";");
    database_work.commit();
  }
  catch (const std::exception &ex)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to read the "
      << kTableAlarms << " table from the database. " << ex.what());
    return DicesRcDriver::DATABASE_READ_TABLE_FAILURE;
  }

  if (table_result.columns() < kExpectedAlarmsTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table result contains "
      << table_result.columns() << " columns, but this function requires "
      << kExpectedAlarmsTableColumnCount << " columns to parse "
      "successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  int phys_count = 0;
  int tech_count = 0;
  for (int ix = 0; ix < table_result.size(); ix++)
  {
    if (table_result[ix][21].is_null())
    {
      LOG4CPLUS_WARN(root_logger, sfn << "alarm_condition type is not set. "
        "Setting ice::SignalConditionType::technical_alarm_signal by default");
    }
    ice::SignalConditionType type = static_cast<ice::SignalConditionType>(
      table_result[ix][21].as<int>(
      kDefaultSignalCondition));
    switch (type)
    {
      case ice::SignalConditionType::physiological_alarm_signal:
        phys_count++;
        break;
      case ice::SignalConditionType::technical_alarm_signal:
        tech_count++;
        break;
      default:
        LOG4CPLUS_WARN(root_logger, sfn << "Cannot determine from "
          "SignalConditionType (" << static_cast<int>(type) << ") if alarm "
          "is physiological or technical.");
        break;
    }
  }

  try
  {
    _physiological_alarm_context_response_instance_list.resize(phys_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "physiological AlarmContext instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  try
  {
    _physiological_alarm_signal_response_instance_list.resize(phys_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "physiological AlarmSignal instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  try
  {
    _technical_alarm_context_response_instance_list.resize(tech_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "technical AlarmContext instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  try
  {
    _technical_alarm_signal_response_instance_list.resize(tech_count);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "technical AlarmSignal instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  // Use counters as indexes now.
  phys_count = 0;
  tech_count = 0;
  for (int ix = 0; ix < table_result.size(); ix++)
  {
    ice::AlarmContext* alarm_context_instance =
      ice::AlarmContextTypeSupport::create_data();
    if (!alarm_context_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for "
        "AlarmContext");
      return DicesRcDriver::ALARM_CONTEXT_INSTANCE_CREATE_FAILURE;
    }
    ice::AlarmSignal* alarm_signal_instance =
      ice::AlarmSignalTypeSupport::create_data();
    if (!alarm_signal_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for "
        "AlarmSignal");
      DDS::ReturnCode_t retcode = ice::AlarmContextTypeSupport::
        delete_data(alarm_context_instance);
      if (retcode != DDS::RETCODE_OK)
      {
        LOG4CPLUS_WARN(root_logger, sfn << "Failed to delete_data() for "
          "AlarmContext");
      }
      alarm_context_instance = nullptr;
      return DicesRcDriver::ALARM_SIGNAL_INSTANCE_CREATE_FAILURE;
    }

    if (table_result[ix][21].is_null())
    {
      LOG4CPLUS_WARN(root_logger, sfn << "alarm_condition type is not set. "
        "Setting ice::SignalConditionType::technical_alarm_signal by default");
    }
    ice::SignalConditionType type = static_cast<ice::SignalConditionType>(
      table_result[ix][21].as<int>(
      kDefaultSignalCondition));
    switch (type)
    {
      case ice::SignalConditionType::physiological_alarm_signal:
      {
        _physiological_alarm_context_response_instance_list.at(phys_count).
          second = alarm_context_instance;
        _physiological_alarm_signal_response_instance_list.at(phys_count).
          second = alarm_signal_instance;

        DicesRcDriver status = ParseAlarmContextResultTuple(
          _physiological_alarm_context_response_instance_list.at(phys_count).
          second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _physiological_alarm_context_response_instance_list.at(phys_count).
          first = DicesRcDriver::OK;

        status = ParseAlarmSignalResultTuple(
          _physiological_alarm_signal_response_instance_list.at(phys_count).
          second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _physiological_alarm_signal_response_instance_list.at(phys_count).
          first = DicesRcDriver::NO_NEW_DATA;

        phys_count++;
      }
        break;
      case ice::SignalConditionType::technical_alarm_signal:
      {
        _technical_alarm_context_response_instance_list.at(tech_count).
          second = alarm_context_instance;
        _technical_alarm_signal_response_instance_list.at(tech_count).
          second = alarm_signal_instance;

        DicesRcDriver status = ParseAlarmContextResultTuple(
          _technical_alarm_context_response_instance_list.at(tech_count).
          second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _technical_alarm_context_response_instance_list.at(tech_count).
          first = DicesRcDriver::OK;

        status = ParseAlarmSignalResultTuple(
          _technical_alarm_signal_response_instance_list.at(tech_count).
          second,
          table_result[ix]);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        _technical_alarm_signal_response_instance_list.at(tech_count).
          first = DicesRcDriver::NO_NEW_DATA;

        tech_count++;
      }
        break;
      default:
      {
        LOG4CPLUS_WARN(root_logger, sfn << "Cannot determine from "
          "SignalConditionType (" << static_cast<int>(type) << ") if alarm "
          "is physiological or technical.");

        DDS::ReturnCode_t retcode = ice::AlarmContextTypeSupport::
          delete_data(alarm_context_instance);
        if (retcode != DDS::RETCODE_OK)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to delete_data() for "
            "AlarmContext");
        }
        alarm_context_instance = nullptr;

        retcode = ice::AlarmSignalTypeSupport::
          delete_data(alarm_signal_instance);
        if (retcode != DDS::RETCODE_OK)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to delete_data() for "
            "AlarmSignal");
        }
        alarm_signal_instance = nullptr;
      }
        break;
    }
  }
  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ParseAlarmContextResultTuple(
  ice::AlarmContext* instance,
  const pqxx::result::tuple& table_tuple)
{
  static const char* sfn = "Parser::ParseAlarmContextResultTuple() ";
  if (instance == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument instance is a null "
      "pointer.");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }

  if (table_tuple.size() < kExpectedAlarmsTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table tuple contains "
      << table_tuple.size() << " columns, but this function requires "
      << kExpectedAlarmsTableColumnCount << " columns to parse "
      "successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  strncpy(
    instance->ice_id,
    table_tuple[2].as<std::string>("").c_str(),
    ice::MAX_LEN_ICE_ID);
  instance->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  instance->handle = table_tuple[3].as<ice::HANDLE>(0);
  instance->parent_handle = table_tuple[4].as<ice::HANDLE>(0);
  instance->source_timestamp.seconds = table_tuple[5].as<long>(0);
  instance->source_timestamp.nanoseconds = table_tuple[6].as<long>(0);
  instance->type.partition = static_cast<ice::NomPartition>(
    table_tuple[7].as<int>(ice::NomPartition::nom_part_unspec));
  instance->type.code = table_tuple[8].as<ice::OIDType>(0);
  instance->alarm_source = table_tuple[9].as<ice::OIDType>(0);
  instance->context_seq_number = table_tuple[10].as<long>(0);
  strncpy(
    instance->event_message,
    table_tuple[11].as<std::string>("").c_str(),
    ice::LONG_STRING_LEN);
  instance->event_message[ice::LONG_STRING_LEN] = '\0';
  instance->initial_priority = static_cast<ice::AlarmInitialPriority>(
    table_tuple[12].as<int>(ice::AlarmInitialPriority::no_priority_provided));
  instance->latch = static_cast<ice::LatchingType>(
    table_tuple[13].as<int>(ice::LatchingType::non_latching));
  instance->alarm_condition_seconds = table_tuple[14].as<ice::INT32>(0);
  instance->alarm_signal_generation_delay = table_tuple[15].as<ice::INT32>(0);
  instance->alarm_signal_inactivation_state = static_cast<
    ice::AlarmSignalInactivationState>(table_tuple[16].as<int>(
    ice::AlarmSignalInactivationState::si_none));
  instance->auditory_alarm_signal_set.tbd = table_tuple[17].as<ice::INT32>(0);
  instance->alarm_paused_seconds = table_tuple[18].as<ice::INT32>(0);
  instance->audio_paused_seconds = table_tuple[19].as<ice::INT32>(0);
  instance->alarm_acknowledge_seconds = table_tuple[20].as<ice::INT32>(0);
  instance->alarm_condition.type = static_cast<ice::SignalConditionType>(
    table_tuple[21].as<int>(kDefaultSignalCondition));
  instance->alarm_condition.limit.type = static_cast<ice::LimitType>(
    table_tuple[22].as<int>(ice::LimitType::not_a_limit));
  instance->alarm_condition.limit.value = table_tuple[23].as<float>(0);
  instance->alarm_condition.alarm_code = table_tuple[24].as<ice::OIDType>(0);
  instance->alarm_condition.unit_code = table_tuple[25].as<ice::OIDType>(0);
  // AlarmParameterList
  // NOTE: If any fields are null, then the AlarmParameterList sequence will
  // be empty.
  if (!table_tuple[26].is_null())
  {
    std::string alarm_par_str = table_tuple[26].as<std::string>("");
    std::vector < std::pair < ice::INTU16, bool>>alarm_par_vect;
    DicesRcDriver status = ParseCSVToArray(&alarm_par_vect, alarm_par_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    for (int iy = 0; iy < alarm_par_vect.size(); iy++)
    {
      if (!alarm_par_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In ice::AlarmParameterList, "
          " each element is an ice::OIDType and is not "
          "optional, therefore null is not an acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->alarm_parameters.ensure_length(
      alarm_par_vect.size(),
      alarm_par_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::AlarmParameterList DDS sequence with length: "
        << alarm_par_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < alarm_par_vect.size(); iy++)
    {
      instance->alarm_parameters[iy] = static_cast<ice::OIDType>(
        alarm_par_vect.at(iy).first);
    }
  }
  instance->alarm_preset_list.tbd = table_tuple[27].as<ice::INT32>(0);
  // AlarmEscalationStateList
  // NOTE: If any fields are null, then the AlarmEscalationStateList sequence
  // will be empty.
  if (!table_tuple[28].is_null()
    && !table_tuple[29].is_null())
  {
    std::string type_str = table_tuple[28].as<std::string>("");
    std::string path_str = table_tuple[29].as<std::string>("");
    std::vector < std::pair < ice::INT32, bool>>type_vect;
    std::vector < std::pair < ice::INT32, bool>>path_vect;
    DicesRcDriver status = ParseCSVToArray(&type_vect, type_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    status = ParseCSVToArray(&path_vect, path_str);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
        DicesRcDriverToString(status));
      return status;
    }
    if (type_vect.size() != path_vect.size())
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "To set "
        "ice::AlarmEscalationStateList sequence, type, and path must have "
        "the same number of elements");
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < type_vect.size(); iy++)
    {
      if (!type_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In "
          "ice::AlarmEscalationStateEntry, type is not optional, therefore "
          "null is not an acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    for (int iy = 0; iy < path_vect.size(); iy++)
    {
      if (!path_vect.at(iy).second)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "In "
          "ice::AlarmEscalationStateEntry, path is not optional, therefore "
          "null is not an acceptable value.");
        return DicesRcDriver::FAIL;
      }
    }
    if (instance->escalation_list.ensure_length(
      type_vect.size(),
      type_vect.size()) == false)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
        "ice::AlarmEscalationStateList DDS sequence with length: "
        << type_vect.size());
      return DicesRcDriver::FAIL;
    }
    for (int iy = 0; iy < type_vect.size(); iy++)
    {
      instance->escalation_list[iy].type =
        static_cast<ice::AlarmEscalationType>(type_vect.at(iy).first);
    }
    for (int iy = 0; iy < path_vect.size(); iy++)
    {
      instance->escalation_list[iy].path =
        static_cast<ice::AlarmEscalationPath>(path_vect.at(iy).first);
    }
  }
  instance->visual_alarm_characteristics.type = static_cast<
    ice::VisualAlarmSignalType>(table_tuple[30].as<int>(
    ice::VisualAlarmSignalType::operator_position));
  instance->auditory_reminder_signal_seconds = table_tuple[31].as<ice::INT32>(0);
  instance->auditory_alarm_signal_db = table_tuple[32].as<ice::INT32>(0);

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ParseAlarmSignalResultTuple(
  ice::AlarmSignal* instance,
  const pqxx::result::tuple& table_tuple)
{
  static const char* sfn = "Parser::ParseAlarmSignalResultTuple() ";
  if (instance == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument instance is a null "
      "pointer.");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }

  if (table_tuple.size() < kExpectedAlarmsTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table tuple contains "
      << table_tuple.size() << " columns, but this function requires "
      << kExpectedAlarmsTableColumnCount << " columns to parse "
      "successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  strncpy(
    instance->ice_id,
    table_tuple[2].as<std::string>("").c_str(),
    ice::MAX_LEN_ICE_ID);
  instance->ice_id[ice::MAX_LEN_ICE_ID] = '\0';
  instance->handle = table_tuple[3].as<ice::HANDLE>(0);
  instance->parent_handle = table_tuple[4].as<ice::HANDLE>(0);
  instance->source_timestamp.seconds = table_tuple[5].as<long>(0);
  instance->source_timestamp.nanoseconds = table_tuple[6].as<long>(0);
  instance->type.partition = static_cast<ice::NomPartition>(
    table_tuple[7].as<int>(ice::NomPartition::nom_part_unspec));
  instance->type.code = table_tuple[8].as<ice::OIDType>(0);
  instance->alarm_source = table_tuple[9].as<ice::OIDType>(0);
  instance->context_seq_number = table_tuple[10].as<long>(0);
  instance->initial_priority = static_cast<ice::AlarmInitialPriority>(
    table_tuple[12].as<int>(ice::AlarmInitialPriority::no_priority_provided));
  instance->latch = static_cast<ice::LatchingType>(
    table_tuple[13].as<int>(ice::LatchingType::non_latching));

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ReadFromPatientIdentificationTable()
{
  static const char* sfn = "Parser::ReadFromPatientIdentificationTable() ";

  if (!_database_connection)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Database is not connected");
    return DicesRcDriver::DATABASE_CONNECTION_FAILURE;
  }

  std::string column_names =
    kHeaderColumnNames + ", " + kTopColumnNames + ", "
    + kPatientIdentificationColumnNames;
  pqxx::result table_result;
  try
  {
    pqxx::work database_work(*_database_connection);
    table_result = database_work.exec(
      "SELECT " + column_names + " FROM " +
      std::string(kTablePatientIdentification) + ";");
    database_work.commit();
  }
  catch (const std::exception &ex)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to read the "
      << kTablePatientIdentification << " table from the database. "
      << ex.what());
    return DicesRcDriver::DATABASE_READ_TABLE_FAILURE;
  }

  if (table_result.columns() < kExpectedPatientIdentificationTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table result contains "
      << table_result.columns() << " columns, but this function requires "
      << kExpectedPatientIdentificationTableColumnCount << " columns to parse "
      "successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  try
  {
    _patient_identification_response_instance_list.resize(table_result.size());
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "PatientIdentification instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  for (int ix = 0; ix < table_result.size(); ix++)
  {
    ice::PatientIdentification* pat_ident_instance =
      ice::PatientIdentificationTypeSupport::create_data();
    if (!pat_ident_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for "
        "PatientIdentification");
      return DicesRcDriver::PATIENT_IDENTIFICATION_INSTANCE_CREATE_FAILURE;
    }
    _patient_identification_response_instance_list.at(ix).second =
      pat_ident_instance;

    strncpy(
      _patient_identification_response_instance_list.at(ix).second->ice_id,
      table_result[ix][2].as<std::string>("").c_str(),
      ice::MAX_LEN_ICE_ID);
    _patient_identification_response_instance_list.at(ix).second->ice_id[
      ice::MAX_LEN_ICE_ID] = '\0';
    _patient_identification_response_instance_list.at(ix).second->handle =
      table_result[ix][3].as<ice::HANDLE>(0);
    _patient_identification_response_instance_list.at(ix).second->
      parent_handle = table_result[ix][4].as<ice::HANDLE>(0);
    _patient_identification_response_instance_list.at(ix).second->
      source_timestamp.seconds = table_result[ix][5].as<long>(0);
    _patient_identification_response_instance_list.at(ix).second->
      source_timestamp.nanoseconds = table_result[ix][6].as<long>(0);
    strncpy(
      _patient_identification_response_instance_list.at(ix).second->given_name,
      table_result[ix][7].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _patient_identification_response_instance_list.at(ix).second->given_name[
      ice::SHORT_STRING_LEN] = '\0';
    strncpy(
      _patient_identification_response_instance_list.at(ix).second->
      family_name,
      table_result[ix][8].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _patient_identification_response_instance_list.at(ix).second->family_name[
      ice::SHORT_STRING_LEN] = '\0';
    strncpy(
      _patient_identification_response_instance_list.at(ix).second->
      middle_name,
      table_result[ix][9].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _patient_identification_response_instance_list.at(ix).second->middle_name[
      ice::SHORT_STRING_LEN] = '\0';
    if (table_result[ix][10].is_null()
      && table_result[ix][11].is_null()
      && table_result[ix][12].is_null()
      && table_result[ix][13].is_null())
    {
      _patient_identification_response_instance_list.at(ix).second->
        date_of_birth = nullptr;
    }
    else
    {
      _patient_identification_response_instance_list.at(ix).second->
        date_of_birth = reinterpret_cast<ice::Date*>(DDS::Heap_malloc(sizeof(
        ice::Date)));
      if (!_patient_identification_response_instance_list.at(ix).second->
        date_of_birth)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::Date");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][10].as<std::string>(""),
        &_patient_identification_response_instance_list.at(ix).second->
        date_of_birth->century);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][11].as<std::string>(""),
        &_patient_identification_response_instance_list.at(ix).second->
        date_of_birth->year);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][12].as<std::string>(""),
        &_patient_identification_response_instance_list.at(ix).second->
        date_of_birth->month);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][13].as<std::string>(""),
        &_patient_identification_response_instance_list.at(ix).second->
        date_of_birth->day);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
    }
    strncpy(
      _patient_identification_response_instance_list.at(ix).second->
      patient_id,
      table_result[ix][14].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _patient_identification_response_instance_list.at(ix).second->
      patient_id[ice::MEDIUM_STRING_LEN] = '\0';
    strncpy(
      _patient_identification_response_instance_list.at(ix).second->
      patient_id_provenance,
      table_result[ix][15].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _patient_identification_response_instance_list.at(ix).second->
      patient_id_provenance[ice::MEDIUM_STRING_LEN] = '\0';
    _patient_identification_response_instance_list.at(ix).second->verified =
      static_cast<ice::BOOL>(table_result[ix][16].as<bool>(false));
    _patient_identification_response_instance_list.at(ix).second->
      pat_admit_state = static_cast<ice::PatAdmitState>(
      table_result[ix][17].as<int>(0));
    _patient_identification_response_instance_list.at(ix).second->
      pat_episode_id = table_result[ix][18].as<ice::PatEpisode>(0);
    _patient_identification_response_instance_list.at(ix).second->
      episode_start.seconds = table_result[ix][19].as<long>(0);
    _patient_identification_response_instance_list.at(ix).second->
      episode_start.nanoseconds = table_result[ix][20].as<long>(0);
  }

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ReadFromPatientIdentificationReqTable()
{
  static const char* sfn = "Parser::ReadFromPatientIdentificationReqTable() ";

  if (!_database_connection)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Database is not connected");
    return DicesRcDriver::DATABASE_CONNECTION_FAILURE;
  }

  std::string column_names =
    kHeaderColumnNames + ", " + kTopColumnNames + ", "
    + kPatientIdentificationColumnNames;
  pqxx::result table_result;
  try
  {
    pqxx::work database_work(*_database_connection);
    table_result = database_work.exec(
      "SELECT " + column_names + " FROM " +
      std::string(kTablePatientIdentificationReq) + ";");
    database_work.commit();
  }
  catch (const std::exception &ex)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to read the "
      << kTablePatientIdentificationReq << " table from the database. "
      << ex.what());
    return DicesRcDriver::DATABASE_READ_TABLE_FAILURE;
  }

  if (table_result.columns() < kExpectedPatientIdentificationTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table result contains "
      << table_result.columns() << " columns, but this function requires "
      << kExpectedPatientIdentificationTableColumnCount << " columns to parse "
      "successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  try
  {
    _patient_identification_req_response_instance_list.resize(table_result.size());
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "PatientIdentification instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  for (int ix = 0; ix < table_result.size(); ix++)
  {
    ice::PatientIdentification* pat_ident_instance =
      ice::PatientIdentificationTypeSupport::create_data();
    if (!pat_ident_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for "
        "PatientIdentification");
      return DicesRcDriver::PATIENT_IDENTIFICATION_INSTANCE_CREATE_FAILURE;
    }
    _patient_identification_req_response_instance_list.at(ix).second =
      pat_ident_instance;

    strncpy(
      _patient_identification_req_response_instance_list.at(ix).second->ice_id,
      table_result[ix][2].as<std::string>("").c_str(),
      ice::MAX_LEN_ICE_ID);
    _patient_identification_req_response_instance_list.at(ix).second->ice_id[
      ice::MAX_LEN_ICE_ID] = '\0';
    _patient_identification_req_response_instance_list.at(ix).second->handle =
      table_result[ix][3].as<ice::HANDLE>(0);
    _patient_identification_req_response_instance_list.at(ix).second->
      parent_handle = table_result[ix][4].as<ice::HANDLE>(0);
    _patient_identification_req_response_instance_list.at(ix).second->
      source_timestamp.seconds = table_result[ix][5].as<long>(0);
    _patient_identification_req_response_instance_list.at(ix).second->
      source_timestamp.nanoseconds = table_result[ix][6].as<long>(0);
    strncpy(
      _patient_identification_req_response_instance_list.at(ix).second->given_name,
      table_result[ix][7].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _patient_identification_req_response_instance_list.at(ix).second->given_name[
      ice::SHORT_STRING_LEN] = '\0';
    strncpy(
      _patient_identification_req_response_instance_list.at(ix).second->
      family_name,
      table_result[ix][8].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _patient_identification_req_response_instance_list.at(ix).second->family_name[
      ice::SHORT_STRING_LEN] = '\0';
    strncpy(
      _patient_identification_req_response_instance_list.at(ix).second->
      middle_name,
      table_result[ix][9].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _patient_identification_req_response_instance_list.at(ix).second->middle_name[
      ice::SHORT_STRING_LEN] = '\0';
    if (table_result[ix][10].is_null()
      && table_result[ix][11].is_null()
      && table_result[ix][12].is_null()
      && table_result[ix][13].is_null())
    {
      _patient_identification_req_response_instance_list.at(ix).second->
        date_of_birth = nullptr;
    }
    else
    {
      _patient_identification_req_response_instance_list.at(ix).second->
        date_of_birth = reinterpret_cast<ice::Date*>(DDS::Heap_malloc(sizeof(
        ice::Date)));
      if (!_patient_identification_req_response_instance_list.at(ix).second->
        date_of_birth)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::Date");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][10].as<std::string>(""),
        &_patient_identification_req_response_instance_list.at(ix).second->
        date_of_birth->century);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][11].as<std::string>(""),
        &_patient_identification_req_response_instance_list.at(ix).second->
        date_of_birth->year);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][12].as<std::string>(""),
        &_patient_identification_req_response_instance_list.at(ix).second->
        date_of_birth->month);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][13].as<std::string>(""),
        &_patient_identification_req_response_instance_list.at(ix).second->
        date_of_birth->day);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
    }
    strncpy(
      _patient_identification_req_response_instance_list.at(ix).second->
      patient_id,
      table_result[ix][14].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _patient_identification_req_response_instance_list.at(ix).second->
      patient_id[ice::MEDIUM_STRING_LEN] = '\0';
    strncpy(
      _patient_identification_req_response_instance_list.at(ix).second->
      patient_id_provenance,
      table_result[ix][15].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _patient_identification_req_response_instance_list.at(ix).second->
      patient_id_provenance[ice::MEDIUM_STRING_LEN] = '\0';
    _patient_identification_req_response_instance_list.at(ix).second->verified =
      static_cast<ice::BOOL>(table_result[ix][16].as<bool>(false));
    _patient_identification_req_response_instance_list.at(ix).second->
      pat_admit_state = static_cast<ice::PatAdmitState>(
      table_result[ix][17].as<int>(0));
    _patient_identification_req_response_instance_list.at(ix).second->
      pat_episode_id = table_result[ix][18].as<ice::PatEpisode>(0);
    _patient_identification_req_response_instance_list.at(ix).second->
      episode_start.seconds = table_result[ix][19].as<long>(0);
    _patient_identification_req_response_instance_list.at(ix).second->
      episode_start.nanoseconds = table_result[ix][20].as<long>(0);
  }

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ReadFromPatientDemographicsTable()
{
  static const char* sfn = "Parser::ReadFromPatientDemographicsTable() ";

  if (!_database_connection)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Database is not connected");
    return DicesRcDriver::DATABASE_CONNECTION_FAILURE;
  }

  std::string column_names =
    kHeaderColumnNames + ", " + kTopColumnNames + ", "
    + kPatientDemographicsColumnNames;
  pqxx::result table_result;
  try
  {
    pqxx::work database_work(*_database_connection);
    table_result = database_work.exec(
      "SELECT " + column_names + " FROM " +
      std::string(kTablePatientDemographics) + ";");
    database_work.commit();
  }
  catch (const std::exception &ex)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to read the "
      << kTablePatientDemographics << " table from the database. "
      << ex.what());
    return DicesRcDriver::DATABASE_READ_TABLE_FAILURE;
  }

  if (table_result.columns() < kExpectedPatientDemographicsTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table result contains "
      << table_result.columns() << " columns, but this function requires "
      << kExpectedPatientDemographicsTableColumnCount << " columns to parse "
      "successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  try
  {
    _patient_demographics_response_instance_list.resize(table_result.size());
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "PatientDemographics instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  for (int ix = 0; ix < table_result.size(); ix++)
  {
    ice::PatientDemographics* pat_demo_instance =
      ice::PatientDemographicsTypeSupport::create_data();
    if (!pat_demo_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for "
        "PatientDemographics");
      return DicesRcDriver::PATIENT_DEMOGRAPHICS_INSTANCE_CREATE_FAILURE;
    }
    _patient_demographics_response_instance_list.at(ix).second =
      pat_demo_instance;

    strncpy(
      _patient_demographics_response_instance_list.at(ix).second->ice_id,
      table_result[ix][0].as<std::string>("").c_str(),
      ice::MAX_LEN_ICE_ID);
    _patient_demographics_response_instance_list.at(ix).second->ice_id[
      ice::MAX_LEN_ICE_ID] = '\0';
    _patient_demographics_response_instance_list.at(ix).second->handle =
      table_result[ix][3].as<ice::HANDLE>(0);
    _patient_demographics_response_instance_list.at(ix).second->
      parent_handle = table_result[ix][4].as<ice::HANDLE>(0);
    _patient_demographics_response_instance_list.at(ix).second->
      source_timestamp.seconds = table_result[ix][5].as<long>(0);
    _patient_demographics_response_instance_list.at(ix).second->
      source_timestamp.nanoseconds = table_result[ix][6].as<long>(0);
    if (table_result[ix][7].is_null())
    {
      _patient_demographics_response_instance_list.at(ix).second->sex =
        nullptr;
    }
    else
    {
      _patient_demographics_response_instance_list.at(ix).second->sex =
        reinterpret_cast<ice::PatientSex*>(DDS::Heap_malloc(
        sizeof(ice::PatientSex)));
      if (!_patient_demographics_response_instance_list.at(ix).second->sex)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::PatientSex");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      *_patient_demographics_response_instance_list.at(ix).second->sex =
        static_cast<ice::PatientSex>(table_result[ix][7].as<int>(0));
    }
    if (table_result[ix][8].is_null())
    {
      _patient_demographics_response_instance_list.at(ix).second->gender =
        nullptr;
    }
    else
    {
      _patient_demographics_response_instance_list.at(ix).second->gender =
        reinterpret_cast<ice::PatientGender*>(DDS::Heap_malloc(
        sizeof(ice::PatientGender)));
      if (!_patient_demographics_response_instance_list.at(ix).second->gender)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::PatientGender");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      *_patient_demographics_response_instance_list.at(ix).second->gender =
        static_cast<ice::PatientGender>(table_result[ix][8].as<int>(0));
    }
    if (table_result[ix][9].is_null() && table_result[ix][10].is_null())
    {
      _patient_demographics_response_instance_list.at(ix).second->race =
        nullptr;
    }
    else
    {
      _patient_demographics_response_instance_list.at(ix).second->race =
        reinterpret_cast<ice::PatientRace*>(DDS::Heap_malloc(
        sizeof(ice::PatientRace)));
      if (!_patient_demographics_response_instance_list.at(ix).second->race)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::PatientRace");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      _patient_demographics_response_instance_list.at(ix).second->
        race->provenance = DDS::String_alloc(
        ice::SHORT_STRING_LEN);
      if (!_patient_demographics_response_instance_list.at(ix).second->
        race->provenance)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::PatientRace provenance string");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      _patient_demographics_response_instance_list.at(ix).second->race->race_type =
        static_cast<ice::RaceType>(table_result[ix][9].as<int>(0));
      strncpy(
        _patient_demographics_response_instance_list.at(ix).second->
        race->provenance,
        table_result[ix][10].as<std::string>("").c_str(),
        ice::SHORT_STRING_LEN);
      _patient_demographics_response_instance_list.at(ix).second->
        race->provenance[ice::SHORT_STRING_LEN] = '\0';
    }
    if (table_result[ix][11].is_null())
    {
      _patient_demographics_response_instance_list.at(ix).second->
        patient_type = nullptr;
    }
    else
    {
      _patient_demographics_response_instance_list.at(ix).second->
        patient_type = reinterpret_cast<ice::PatientType*>(DDS::Heap_malloc(
        sizeof(ice::PatientType)));
      if (!_patient_demographics_response_instance_list.at(ix).second->
        patient_type)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::PatientType");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      *_patient_demographics_response_instance_list.at(ix).second->
        patient_type = static_cast<ice::PatientType>(
        table_result[ix][11].as<int>(0));
    }
    if (table_result[ix][12].is_null() && table_result[ix][13].is_null())
    {
      _patient_demographics_response_instance_list.at(ix).second->
        chronological_age = nullptr;
    }
    else
    {
      _patient_demographics_response_instance_list.at(ix).second->
        chronological_age = reinterpret_cast<ice::PatMeasure*>(
        DDS::Heap_malloc(sizeof(ice::PatMeasure)));
      if (!_patient_demographics_response_instance_list.at(ix).second->
        chronological_age)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for chronological_age ice::PatMeasure");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      _patient_demographics_response_instance_list.at(ix).second->
        chronological_age->value = table_result[ix][12].as<ice::FLOATType>(0);
      _patient_demographics_response_instance_list.at(ix).second->
        chronological_age->m_unit = table_result[ix][13].as<ice::OIDType>(0);
    }
    if (table_result[ix][14].is_null() && table_result[ix][15].is_null())
    {
      _patient_demographics_response_instance_list.at(ix).second->
        patient_height = nullptr;
    }
    else
    {
      _patient_demographics_response_instance_list.at(ix).second->
        patient_height = reinterpret_cast<ice::PatMeasure*>(
        DDS::Heap_malloc(sizeof(ice::PatMeasure)));
      if (!_patient_demographics_response_instance_list.at(ix).second->
        patient_height)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for patient_height ice::PatMeasure");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      _patient_demographics_response_instance_list.at(ix).second->
        patient_height->value = table_result[ix][14].as<ice::FLOATType>(0);
      _patient_demographics_response_instance_list.at(ix).second->
        patient_height->m_unit = table_result[ix][15].as<ice::OIDType>(0);
    }
    if (table_result[ix][16].is_null() && table_result[ix][17].is_null())
    {
      _patient_demographics_response_instance_list.at(ix).second->
        patient_weight = nullptr;
    }
    else
    {
      _patient_demographics_response_instance_list.at(ix).second->
        patient_weight = reinterpret_cast<ice::PatMeasure*>(
        DDS::Heap_malloc(sizeof(ice::PatMeasure)));
      if (!_patient_demographics_response_instance_list.at(ix).second->
        patient_weight)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for patient_weight ice::PatMeasure");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      _patient_demographics_response_instance_list.at(ix).second->
        patient_weight->value = table_result[ix][16].as<ice::FLOATType>(0);
      _patient_demographics_response_instance_list.at(ix).second->
        patient_weight->m_unit = table_result[ix][17].as<ice::OIDType>(0);
    }

    if (table_result[ix][18].is_null()
      && table_result[ix][19].is_null()
      && table_result[ix][20].is_null()
      && table_result[ix][21].is_null()
      && table_result[ix][22].is_null()
      && table_result[ix][23].is_null()
      && table_result[ix][24].is_null()
      && table_result[ix][25].is_null()
      && table_result[ix][26].is_null()
      && table_result[ix][27].is_null()
      && table_result[ix][28].is_null()
      && table_result[ix][29].is_null()
      && table_result[ix][30].is_null()
      && table_result[ix][31].is_null()
      && table_result[ix][32].is_null()
      && table_result[ix][33].is_null()
      && table_result[ix][34].is_null()
      && table_result[ix][35].is_null()
      && table_result[ix][36].is_null()
      && table_result[ix][37].is_null()
      && table_result[ix][38].is_null()
      && table_result[ix][39].is_null()
      && table_result[ix][40].is_null())
    {
      _patient_demographics_response_instance_list.at(ix).second->neonatal
        = nullptr;
    }
    else
    {
      _patient_demographics_response_instance_list.at(ix).second->
        neonatal = reinterpret_cast<ice::NeonatalPatientInfo*>(
        DDS::Heap_malloc(sizeof(ice::NeonatalPatientInfo)));
      if (!_patient_demographics_response_instance_list.at(ix).second->
        neonatal)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::NeonatalPatientInfo");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      if (table_result[ix][18].is_null() && table_result[ix][19].is_null())
      {
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->gestational_age = nullptr;
      }
      else
      {
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->gestational_age = reinterpret_cast<ice::PatMeasure*>(
          DDS::Heap_malloc(sizeof(ice::PatMeasure)));
        if (!_patient_demographics_response_instance_list.at(ix).second->
          neonatal->gestational_age)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for neonatal gestational_age ice::PatMeasure");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->gestational_age->value = table_result[ix][18].as<
          ice::FLOATType>(0);
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->gestational_age->m_unit = table_result[ix][19].as<
          ice::OIDType>(0);
      }
      if (table_result[ix][20].is_null() && table_result[ix][21].is_null())
      {
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->patient_birth_length = nullptr;
      }
      else
      {
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->patient_birth_length = reinterpret_cast<ice::PatMeasure*>(
          DDS::Heap_malloc(sizeof(ice::PatMeasure)));
        if (!_patient_demographics_response_instance_list.at(ix).second->
          neonatal->patient_birth_length)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for neonatal patient_birth_length ice::PatMeasure");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->patient_birth_length->value = table_result[ix][20].as<
          ice::FLOATType>(0);
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->patient_birth_length->m_unit = table_result[ix][21].as<
          ice::OIDType>(0);
      }
      if (table_result[ix][22].is_null() && table_result[ix][23].is_null())
      {
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->patient_birth_weight = nullptr;
      }
      else
      {
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->patient_birth_weight = reinterpret_cast<ice::PatMeasure*>(
          DDS::Heap_malloc(sizeof(ice::PatMeasure)));
        if (!_patient_demographics_response_instance_list.at(ix).second->
          neonatal->patient_birth_weight)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for neonatal patient_birth_weight ice::PatMeasure");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->patient_birth_weight->value = table_result[ix][22].as<
          ice::FLOATType>(0);
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->patient_birth_weight->m_unit = table_result[ix][23].as<
          ice::OIDType>(0);
      }
      if (table_result[ix][24].is_null() && table_result[ix][25].is_null())
      {
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->patient_head_circumference = nullptr;
      }
      else
      {
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->patient_head_circumference = reinterpret_cast<
          ice::PatMeasure*>(DDS::Heap_malloc(sizeof(ice::PatMeasure)));
        if (!_patient_demographics_response_instance_list.at(ix).second->
          neonatal->patient_head_circumference)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for neonatal patient_head_circumference ice::PatMeasure");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->patient_head_circumference->value =
          table_result[ix][24].as<ice::FLOATType>(0);
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->patient_head_circumference->m_unit =
          table_result[ix][25].as<ice::OIDType>(0);
      }
      if (table_result[ix][26].is_null()
        && table_result[ix][27].is_null()
        && table_result[ix][28].is_null()
        && table_result[ix][29].is_null()
        && table_result[ix][30].is_null()
        && table_result[ix][31].is_null()
        && table_result[ix][32].is_null()
        && table_result[ix][33].is_null()
        && table_result[ix][34].is_null()
        && table_result[ix][35].is_null()
        && table_result[ix][36].is_null()
        && table_result[ix][37].is_null()
        && table_result[ix][38].is_null()
        && table_result[ix][39].is_null())
      {
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id = nullptr;
      }
      else
      {
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id = reinterpret_cast<
          ice::PatientIdentification*>(DDS::Heap_malloc(
          sizeof(ice::PatientIdentification)));
        if (!_patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for neonatal mother_patient_id ice::PatientIdentification");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->given_name = DDS::String_alloc(
          ice::SHORT_STRING_LEN);
        if (!_patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->given_name)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for given_name string");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->family_name = DDS::String_alloc(
          ice::SHORT_STRING_LEN);
        if (!_patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->family_name)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for family_name string");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->middle_name = DDS::String_alloc(
          ice::SHORT_STRING_LEN);
        if (!_patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->middle_name)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for middle_name string");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->patient_id = DDS::String_alloc(
          ice::MEDIUM_STRING_LEN);
        if (!_patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->patient_id)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for patient_id string");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->patient_id_provenance =
          DDS::String_alloc(ice::MEDIUM_STRING_LEN);
        if (!_patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->patient_id_provenance)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for patient_id_provenance string");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }

        strncpy(
          _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->given_name,
          table_result[ix][26].as<std::string>("").c_str(),
          ice::SHORT_STRING_LEN);
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->given_name[
          ice::SHORT_STRING_LEN] = '\0';
        strncpy(
          _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->family_name,
          table_result[ix][27].as<std::string>("").c_str(),
          ice::SHORT_STRING_LEN);
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->family_name[
          ice::SHORT_STRING_LEN] = '\0';
        strncpy(
          _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->middle_name,
          table_result[ix][28].as<std::string>("").c_str(),
          ice::SHORT_STRING_LEN);
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->middle_name[
          ice::SHORT_STRING_LEN] = '\0';

        if (table_result[ix][29].is_null()
          && table_result[ix][30].is_null()
          && table_result[ix][31].is_null()
          && table_result[ix][32].is_null())
        {
          _patient_demographics_response_instance_list.at(ix).second->
            neonatal->mother_patient_id->date_of_birth = nullptr;
        }
        else
        {
          _patient_demographics_response_instance_list.at(ix).second->
            neonatal->mother_patient_id->date_of_birth =
            reinterpret_cast<ice::Date*>(DDS::Heap_malloc(sizeof(ice::Date)));
          if (!_patient_demographics_response_instance_list.at(ix).second->
            neonatal->mother_patient_id->date_of_birth)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
              "for ice::Date");
            return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
          }
          DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
            table_result[ix][29].as<std::string>(""),
            &_patient_demographics_response_instance_list.at(ix).second->
            neonatal->mother_patient_id->date_of_birth->century);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }
          status = ConvertPostgresByteaHexToICEINTU8(
            table_result[ix][30].as<std::string>(""),
            &_patient_demographics_response_instance_list.at(ix).second->
            neonatal->mother_patient_id->date_of_birth->year);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }
          status = ConvertPostgresByteaHexToICEINTU8(
            table_result[ix][31].as<std::string>(""),
            &_patient_demographics_response_instance_list.at(ix).second->
            neonatal->mother_patient_id->date_of_birth->month);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }
          status = ConvertPostgresByteaHexToICEINTU8(
            table_result[ix][32].as<std::string>(""),
            &_patient_demographics_response_instance_list.at(ix).second->
            neonatal->mother_patient_id->date_of_birth->day);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }
        }
        strncpy(
          _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->patient_id,
          table_result[ix][33].as<std::string>("").c_str(),
          ice::MEDIUM_STRING_LEN);
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->patient_id[
          ice::MEDIUM_STRING_LEN] = '\0';
        strncpy(
          _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->patient_id_provenance,
          table_result[ix][34].as<std::string>("").c_str(),
          ice::MEDIUM_STRING_LEN);
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->patient_id_provenance[
          ice::MEDIUM_STRING_LEN] = '\0';
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->verified =
          static_cast<ice::BOOL>(table_result[ix][35].as<bool>(false));
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->pat_admit_state =
          static_cast<ice::PatAdmitState>(table_result[ix][36].as<int>(0));
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->pat_episode_id =
          table_result[ix][37].as<ice::PatEpisode>(0);
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->episode_start.seconds =
          table_result[ix][38].as<long>(0);
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->episode_start.nanoseconds =
          table_result[ix][39].as<long>(0);
      }
      if (table_result[ix][40].is_null())
      {
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_name = nullptr;
      }
      else
      {
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_name = DDS::String_alloc(
          ice::LONG_STRING_LEN);
        if (!_patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_name)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for neonatal mother_name string");

          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }
        strncpy(
          _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_name,
          table_result[ix][40].as<std::string>("").c_str(),
          ice::LONG_STRING_LEN);
        _patient_demographics_response_instance_list.at(ix).second->
          neonatal->mother_name[ice::LONG_STRING_LEN] = '\0';
      }
    }
  }

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ReadFromPatientDemographicsReqTable()
{
  static const char* sfn = "Parser::ReadFromPatientDemographicsReqTable() ";

  if (!_database_connection)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Database is not connected");
    return DicesRcDriver::DATABASE_CONNECTION_FAILURE;
  }

  std::string column_names =
    kHeaderColumnNames + ", " + kTopColumnNames + ", "
    + kPatientDemographicsColumnNames;
  pqxx::result table_result;
  try
  {
    pqxx::work database_work(*_database_connection);
    table_result = database_work.exec(
      "SELECT " + column_names + " FROM " +
      std::string(kTablePatientDemographicsReq) + ";");
    database_work.commit();
  }
  catch (const std::exception &ex)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to read the "
      << kTablePatientDemographicsReq << " table from the database. "
      << ex.what());
    return DicesRcDriver::DATABASE_READ_TABLE_FAILURE;
  }

  if (table_result.columns() < kExpectedPatientDemographicsTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table result contains "
      << table_result.columns() << " columns, but this function requires "
      << kExpectedPatientDemographicsTableColumnCount << " columns to parse "
      "successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  try
  {
    _patient_demographics_req_response_instance_list.resize(table_result.size());
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "PatientDemographics instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  for (int ix = 0; ix < table_result.size(); ix++)
  {
    ice::PatientDemographics* pat_demo_instance =
      ice::PatientDemographicsTypeSupport::create_data();
    if (!pat_demo_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for "
        "PatientDemographics");
      return DicesRcDriver::PATIENT_DEMOGRAPHICS_INSTANCE_CREATE_FAILURE;
    }
    _patient_demographics_req_response_instance_list.at(ix).second =
      pat_demo_instance;

    strncpy(
      _patient_demographics_req_response_instance_list.at(ix).second->ice_id,
      table_result[ix][0].as<std::string>("").c_str(),
      ice::MAX_LEN_ICE_ID);
    _patient_demographics_req_response_instance_list.at(ix).second->ice_id[
      ice::MAX_LEN_ICE_ID] = '\0';
    _patient_demographics_req_response_instance_list.at(ix).second->handle =
      table_result[ix][3].as<ice::HANDLE>(0);
    _patient_demographics_req_response_instance_list.at(ix).second->
      parent_handle = table_result[ix][4].as<ice::HANDLE>(0);
    _patient_demographics_req_response_instance_list.at(ix).second->
      source_timestamp.seconds = table_result[ix][5].as<long>(0);
    _patient_demographics_req_response_instance_list.at(ix).second->
      source_timestamp.nanoseconds = table_result[ix][6].as<long>(0);
    if (table_result[ix][7].is_null())
    {
      _patient_demographics_req_response_instance_list.at(ix).second->sex =
        nullptr;
    }
    else
    {
      _patient_demographics_req_response_instance_list.at(ix).second->sex =
        reinterpret_cast<ice::PatientSex*>(DDS::Heap_malloc(
        sizeof(ice::PatientSex)));
      if (!_patient_demographics_req_response_instance_list.at(ix).second->sex)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::PatientSex");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      *_patient_demographics_req_response_instance_list.at(ix).second->sex =
        static_cast<ice::PatientSex>(table_result[ix][7].as<int>(0));
    }
    if (table_result[ix][8].is_null())
    {
      _patient_demographics_req_response_instance_list.at(ix).second->gender =
        nullptr;
    }
    else
    {
      _patient_demographics_req_response_instance_list.at(ix).second->gender =
        reinterpret_cast<ice::PatientGender*>(DDS::Heap_malloc(
        sizeof(ice::PatientGender)));
      if (!_patient_demographics_req_response_instance_list.at(ix).second->gender)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::PatientGender");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      *_patient_demographics_req_response_instance_list.at(ix).second->gender =
        static_cast<ice::PatientGender>(table_result[ix][8].as<int>(0));
    }
    if (table_result[ix][9].is_null() && table_result[ix][10].is_null())
    {
      _patient_demographics_req_response_instance_list.at(ix).second->race =
        nullptr;
    }
    else
    {
      _patient_demographics_req_response_instance_list.at(ix).second->race =
        reinterpret_cast<ice::PatientRace*>(DDS::Heap_malloc(
        sizeof(ice::PatientRace)));
      if (!_patient_demographics_req_response_instance_list.at(ix).second->race)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::PatientRace");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      _patient_demographics_req_response_instance_list.at(ix).second->
        race->provenance = DDS::String_alloc(
        ice::SHORT_STRING_LEN);
      if (!_patient_demographics_req_response_instance_list.at(ix).second->
        race->provenance)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::PatientRace provenance string");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      _patient_demographics_req_response_instance_list.at(ix).second->race->race_type =
        static_cast<ice::RaceType>(table_result[ix][9].as<int>(0));
      strncpy(
        _patient_demographics_req_response_instance_list.at(ix).second->
        race->provenance,
        table_result[ix][10].as<std::string>("").c_str(),
        ice::SHORT_STRING_LEN);
      _patient_demographics_req_response_instance_list.at(ix).second->
        race->provenance[ice::SHORT_STRING_LEN] = '\0';
    }
    if (table_result[ix][11].is_null())
    {
      _patient_demographics_req_response_instance_list.at(ix).second->
        patient_type = nullptr;
    }
    else
    {
      _patient_demographics_req_response_instance_list.at(ix).second->
        patient_type = reinterpret_cast<ice::PatientType*>(DDS::Heap_malloc(
        sizeof(ice::PatientType)));
      if (!_patient_demographics_req_response_instance_list.at(ix).second->
        patient_type)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::PatientType");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      *_patient_demographics_req_response_instance_list.at(ix).second->
        patient_type = static_cast<ice::PatientType>(
        table_result[ix][11].as<int>(0));
    }
    if (table_result[ix][12].is_null() && table_result[ix][13].is_null())
    {
      _patient_demographics_req_response_instance_list.at(ix).second->
        chronological_age = nullptr;
    }
    else
    {
      _patient_demographics_req_response_instance_list.at(ix).second->
        chronological_age = reinterpret_cast<ice::PatMeasure*>(
        DDS::Heap_malloc(sizeof(ice::PatMeasure)));
      if (!_patient_demographics_req_response_instance_list.at(ix).second->
        chronological_age)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for chronological_age ice::PatMeasure");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      _patient_demographics_req_response_instance_list.at(ix).second->
        chronological_age->value = table_result[ix][12].as<ice::FLOATType>(0);
      _patient_demographics_req_response_instance_list.at(ix).second->
        chronological_age->m_unit = table_result[ix][13].as<ice::OIDType>(0);
    }
    if (table_result[ix][14].is_null() && table_result[ix][15].is_null())
    {
      _patient_demographics_req_response_instance_list.at(ix).second->
        patient_height = nullptr;
    }
    else
    {
      _patient_demographics_req_response_instance_list.at(ix).second->
        patient_height = reinterpret_cast<ice::PatMeasure*>(
        DDS::Heap_malloc(sizeof(ice::PatMeasure)));
      if (!_patient_demographics_req_response_instance_list.at(ix).second->
        patient_height)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for patient_height ice::PatMeasure");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      _patient_demographics_req_response_instance_list.at(ix).second->
        patient_height->value = table_result[ix][14].as<ice::FLOATType>(0);
      _patient_demographics_req_response_instance_list.at(ix).second->
        patient_height->m_unit = table_result[ix][15].as<ice::OIDType>(0);
    }
    if (table_result[ix][16].is_null() && table_result[ix][17].is_null())
    {
      _patient_demographics_req_response_instance_list.at(ix).second->
        patient_weight = nullptr;
    }
    else
    {
      _patient_demographics_req_response_instance_list.at(ix).second->
        patient_weight = reinterpret_cast<ice::PatMeasure*>(
        DDS::Heap_malloc(sizeof(ice::PatMeasure)));
      if (!_patient_demographics_req_response_instance_list.at(ix).second->
        patient_weight)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for patient_weight ice::PatMeasure");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      _patient_demographics_req_response_instance_list.at(ix).second->
        patient_weight->value = table_result[ix][16].as<ice::FLOATType>(0);
      _patient_demographics_req_response_instance_list.at(ix).second->
        patient_weight->m_unit = table_result[ix][17].as<ice::OIDType>(0);
    }

    if (table_result[ix][18].is_null()
      && table_result[ix][19].is_null()
      && table_result[ix][20].is_null()
      && table_result[ix][21].is_null()
      && table_result[ix][22].is_null()
      && table_result[ix][23].is_null()
      && table_result[ix][24].is_null()
      && table_result[ix][25].is_null()
      && table_result[ix][26].is_null()
      && table_result[ix][27].is_null()
      && table_result[ix][28].is_null()
      && table_result[ix][29].is_null()
      && table_result[ix][30].is_null()
      && table_result[ix][31].is_null()
      && table_result[ix][32].is_null()
      && table_result[ix][33].is_null()
      && table_result[ix][34].is_null()
      && table_result[ix][35].is_null()
      && table_result[ix][36].is_null()
      && table_result[ix][37].is_null()
      && table_result[ix][38].is_null()
      && table_result[ix][39].is_null()
      && table_result[ix][40].is_null())
    {
      _patient_demographics_req_response_instance_list.at(ix).second->neonatal
        = nullptr;
    }
    else
    {
      _patient_demographics_req_response_instance_list.at(ix).second->
        neonatal = reinterpret_cast<ice::NeonatalPatientInfo*>(
        DDS::Heap_malloc(sizeof(ice::NeonatalPatientInfo)));
      if (!_patient_demographics_req_response_instance_list.at(ix).second->
        neonatal)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::NeonatalPatientInfo");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      if (table_result[ix][18].is_null() && table_result[ix][19].is_null())
      {
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->gestational_age = nullptr;
      }
      else
      {
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->gestational_age = reinterpret_cast<ice::PatMeasure*>(
          DDS::Heap_malloc(sizeof(ice::PatMeasure)));
        if (!_patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->gestational_age)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for neonatal gestational_age ice::PatMeasure");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->gestational_age->value = table_result[ix][18].as<
          ice::FLOATType>(0);
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->gestational_age->m_unit = table_result[ix][19].as<
          ice::OIDType>(0);
      }
      if (table_result[ix][20].is_null() && table_result[ix][21].is_null())
      {
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->patient_birth_length = nullptr;
      }
      else
      {
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->patient_birth_length = reinterpret_cast<ice::PatMeasure*>(
          DDS::Heap_malloc(sizeof(ice::PatMeasure)));
        if (!_patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->patient_birth_length)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for neonatal patient_birth_length ice::PatMeasure");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->patient_birth_length->value = table_result[ix][20].as<
          ice::FLOATType>(0);
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->patient_birth_length->m_unit = table_result[ix][21].as<
          ice::OIDType>(0);
      }
      if (table_result[ix][22].is_null() && table_result[ix][23].is_null())
      {
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->patient_birth_weight = nullptr;
      }
      else
      {
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->patient_birth_weight = reinterpret_cast<ice::PatMeasure*>(
          DDS::Heap_malloc(sizeof(ice::PatMeasure)));
        if (!_patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->patient_birth_weight)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for neonatal patient_birth_weight ice::PatMeasure");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->patient_birth_weight->value = table_result[ix][22].as<
          ice::FLOATType>(0);
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->patient_birth_weight->m_unit = table_result[ix][23].as<
          ice::OIDType>(0);
      }
      if (table_result[ix][24].is_null() && table_result[ix][25].is_null())
      {
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->patient_head_circumference = nullptr;
      }
      else
      {
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->patient_head_circumference = reinterpret_cast<
          ice::PatMeasure*>(DDS::Heap_malloc(sizeof(ice::PatMeasure)));
        if (!_patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->patient_head_circumference)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for neonatal patient_head_circumference ice::PatMeasure");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->patient_head_circumference->value =
          table_result[ix][24].as<ice::FLOATType>(0);
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->patient_head_circumference->m_unit =
          table_result[ix][25].as<ice::OIDType>(0);
      }
      if (table_result[ix][26].is_null()
        && table_result[ix][27].is_null()
        && table_result[ix][28].is_null()
        && table_result[ix][29].is_null()
        && table_result[ix][30].is_null()
        && table_result[ix][31].is_null()
        && table_result[ix][32].is_null()
        && table_result[ix][33].is_null()
        && table_result[ix][34].is_null()
        && table_result[ix][35].is_null()
        && table_result[ix][36].is_null()
        && table_result[ix][37].is_null()
        && table_result[ix][38].is_null()
        && table_result[ix][39].is_null())
      {
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id = nullptr;
      }
      else
      {
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id = reinterpret_cast<
          ice::PatientIdentification*>(DDS::Heap_malloc(
          sizeof(ice::PatientIdentification)));
        if (!_patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for neonatal mother_patient_id ice::PatientIdentification");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->given_name = DDS::String_alloc(
          ice::SHORT_STRING_LEN);
        if (!_patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->given_name)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for given_name string");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->family_name = DDS::String_alloc(
          ice::SHORT_STRING_LEN);
        if (!_patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->family_name)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for family_name string");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->middle_name = DDS::String_alloc(
          ice::SHORT_STRING_LEN);
        if (!_patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->middle_name)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for middle_name string");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->patient_id = DDS::String_alloc(
          ice::MEDIUM_STRING_LEN);
        if (!_patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->patient_id)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for patient_id string");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->patient_id_provenance =
          DDS::String_alloc(ice::MEDIUM_STRING_LEN);
        if (!_patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->patient_id_provenance)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for patient_id_provenance string");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }

        strncpy(
          _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->given_name,
          table_result[ix][26].as<std::string>("").c_str(),
          ice::SHORT_STRING_LEN);
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->given_name[
          ice::SHORT_STRING_LEN] = '\0';
        strncpy(
          _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->family_name,
          table_result[ix][27].as<std::string>("").c_str(),
          ice::SHORT_STRING_LEN);
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->family_name[
          ice::SHORT_STRING_LEN] = '\0';
        strncpy(
          _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->middle_name,
          table_result[ix][28].as<std::string>("").c_str(),
          ice::SHORT_STRING_LEN);
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->middle_name[
          ice::SHORT_STRING_LEN] = '\0';

        if (table_result[ix][29].is_null()
          && table_result[ix][30].is_null()
          && table_result[ix][31].is_null()
          && table_result[ix][32].is_null())
        {
          _patient_demographics_req_response_instance_list.at(ix).second->
            neonatal->mother_patient_id->date_of_birth = nullptr;
        }
        else
        {
          _patient_demographics_req_response_instance_list.at(ix).second->
            neonatal->mother_patient_id->date_of_birth =
            reinterpret_cast<ice::Date*>(DDS::Heap_malloc(sizeof(ice::Date)));
          if (!_patient_demographics_req_response_instance_list.at(ix).second->
            neonatal->mother_patient_id->date_of_birth)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
              "for ice::Date");
            return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
          }
          DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
            table_result[ix][29].as<std::string>(""),
            &_patient_demographics_req_response_instance_list.at(ix).second->
            neonatal->mother_patient_id->date_of_birth->century);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }
          status = ConvertPostgresByteaHexToICEINTU8(
            table_result[ix][30].as<std::string>(""),
            &_patient_demographics_req_response_instance_list.at(ix).second->
            neonatal->mother_patient_id->date_of_birth->year);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }
          status = ConvertPostgresByteaHexToICEINTU8(
            table_result[ix][31].as<std::string>(""),
            &_patient_demographics_req_response_instance_list.at(ix).second->
            neonatal->mother_patient_id->date_of_birth->month);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }
          status = ConvertPostgresByteaHexToICEINTU8(
            table_result[ix][32].as<std::string>(""),
            &_patient_demographics_req_response_instance_list.at(ix).second->
            neonatal->mother_patient_id->date_of_birth->day);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }
        }
        strncpy(
          _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->patient_id,
          table_result[ix][33].as<std::string>("").c_str(),
          ice::MEDIUM_STRING_LEN);
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->patient_id[
          ice::MEDIUM_STRING_LEN] = '\0';
        strncpy(
          _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->patient_id_provenance,
          table_result[ix][34].as<std::string>("").c_str(),
          ice::MEDIUM_STRING_LEN);
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->patient_id_provenance[
          ice::MEDIUM_STRING_LEN] = '\0';
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->verified =
          static_cast<ice::BOOL>(table_result[ix][35].as<bool>(false));
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->pat_admit_state =
          static_cast<ice::PatAdmitState>(table_result[ix][36].as<int>(0));
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->pat_episode_id =
          table_result[ix][37].as<ice::PatEpisode>(0);
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->episode_start.seconds =
          table_result[ix][38].as<long>(0);
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_patient_id->episode_start.nanoseconds =
          table_result[ix][39].as<long>(0);
      }
      if (table_result[ix][40].is_null())
      {
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_name = nullptr;
      }
      else
      {
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_name = DDS::String_alloc(
          ice::LONG_STRING_LEN);
        if (!_patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_name)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for neonatal mother_name string");

          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }
        strncpy(
          _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_name,
          table_result[ix][40].as<std::string>("").c_str(),
          ice::LONG_STRING_LEN);
        _patient_demographics_req_response_instance_list.at(ix).second->
          neonatal->mother_name[ice::LONG_STRING_LEN] = '\0';
      }
    }
  }

  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ReadFromAllergyTable()
{
  static const char* sfn = "Parser::ReadFromAllergyTable() ";

  if (_database_connection == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Database is not connected");
    return DicesRcDriver::DATABASE_CONNECTION_FAILURE;
  }

  std::string column_names = kHeaderColumnNames
    + ", " + kTopColumnNames
    + ", " + kAllergyColumnNames;
  pqxx::result table_result;
  try
  {
    pqxx::work database_work(*_database_connection);
    table_result = database_work.exec(
      "SELECT " + column_names + " FROM " + std::string(kTableAllergy) + ";");
    database_work.commit();
  }
  catch (const std::exception &ex)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to read the " << kTableAllergy
      << " table from the database. " << ex.what());
    return DicesRcDriver::DATABASE_READ_TABLE_FAILURE;
  }

  if (table_result.columns() < kExpectedAllergyTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table result contains "
      << table_result.columns() << " columns, but this function requires "
      << kExpectedAllergyTableColumnCount << " columns to parse successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  try
  {
    _allergy_response_instance_list.resize(table_result.size());
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "allergy instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  for (int ix = 0; ix < table_result.size(); ix++)
  {
    ice::Allergy* allergy_instance = ice::AllergyTypeSupport::create_data();
    if (!allergy_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for "
        "Allergy");
      return DicesRcDriver::ALLERGY_INSTANCE_CREATE_FAILURE;
    }
    _allergy_response_instance_list.at(ix).second = allergy_instance;

    strncpy(
      _allergy_response_instance_list.at(ix).second->ice_id,
      table_result[ix][2].as<std::string>("").c_str(),
      ice::MAX_LEN_ICE_ID);
    _allergy_response_instance_list.at(ix).second->ice_id[
      ice::MAX_LEN_ICE_ID] = '\0';

    _allergy_response_instance_list.at(ix).second->handle =
      table_result[ix][3].as<ice::HANDLE>(0);

    _allergy_response_instance_list.at(ix).second->parent_handle =
      table_result[ix][4].as<ice::HANDLE>(0);

    _allergy_response_instance_list.at(ix).second->source_timestamp.
      seconds = table_result[ix][5].as<long>(0);
    _allergy_response_instance_list.at(ix).second->source_timestamp.
      nanoseconds = table_result[ix][6].as<long>(0);

    strncpy(
      _allergy_response_instance_list.at(ix).second->patient_id.given_name,
      table_result[ix][7].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _allergy_response_instance_list.at(ix).second->patient_id.given_name[
      ice::SHORT_STRING_LEN] = '\0';
    strncpy(
      _allergy_response_instance_list.at(ix).second->patient_id.family_name,
      table_result[ix][8].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _allergy_response_instance_list.at(ix).second->patient_id.family_name[
      ice::SHORT_STRING_LEN] = '\0';
    strncpy(
      _allergy_response_instance_list.at(ix).second->patient_id.middle_name,
      table_result[ix][9].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _allergy_response_instance_list.at(ix).second->patient_id.middle_name[
      ice::SHORT_STRING_LEN] = '\0';

    if (table_result[ix][10].is_null()
      && table_result[ix][11].is_null()
      && table_result[ix][12].is_null()
      && table_result[ix][13].is_null())
    {
      _allergy_response_instance_list.at(ix).second->patient_id.
        date_of_birth = nullptr;
    }
    else
    {
      _allergy_response_instance_list.at(ix).second->patient_id.
        date_of_birth = reinterpret_cast<ice::Date*>(DDS::Heap_malloc(sizeof(
        ice::Date)));
      if (!_allergy_response_instance_list.at(ix).second->patient_id.
        date_of_birth)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::Date");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][10].as<std::string>(""),
        &_allergy_response_instance_list.at(ix).second->patient_id.
        date_of_birth->century);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][11].as<std::string>(""),
        &_allergy_response_instance_list.at(ix).second->patient_id.
        date_of_birth->year);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][12].as<std::string>(""),
        &_allergy_response_instance_list.at(ix).second->patient_id.
        date_of_birth->month);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][13].as<std::string>(""),
        &_allergy_response_instance_list.at(ix).second->patient_id.
        date_of_birth->day);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
    }
    strncpy(
      _allergy_response_instance_list.at(ix).second->patient_id.patient_id,
      table_result[ix][14].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _allergy_response_instance_list.at(ix).second->patient_id.patient_id[
      ice::MEDIUM_STRING_LEN] = '\0';
    strncpy(
      _allergy_response_instance_list.at(ix).second->patient_id.
      patient_id_provenance,
      table_result[ix][15].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _allergy_response_instance_list.at(ix).second->patient_id.
      patient_id_provenance[ice::MEDIUM_STRING_LEN] = '\0';
    _allergy_response_instance_list.at(ix).second->patient_id.verified =
      static_cast<ice::BOOL>(table_result[ix][16].as<bool>(false));
    _allergy_response_instance_list.at(ix).second->patient_id.
      pat_admit_state = static_cast<ice::PatAdmitState>(
      table_result[ix][17].as<int>(0));
    _allergy_response_instance_list.at(ix).second->patient_id.
      pat_episode_id = table_result[ix][18].as<ice::PatEpisode>(0);
    _allergy_response_instance_list.at(ix).second->patient_id.
      episode_start.seconds = table_result[ix][19].as<long>(0);
    _allergy_response_instance_list.at(ix).second->patient_id.
      episode_start.nanoseconds = table_result[ix][20].as<long>(0);
    _allergy_response_instance_list.at(ix).second->adverse_event_count =
      table_result[ix][21].as<ice::INTU16>(0);
    // AdverseEventList
    // NOTE: If any fields are null, then SystemSpec sequence will be empty.
    if (!table_result[ix][22].is_null()
      && !table_result[ix][23].is_null()
      && !table_result[ix][24].is_null()
      && !table_result[ix][25].is_null()
      && !table_result[ix][26].is_null()
      && !table_result[ix][27].is_null()
      && !table_result[ix][28].is_null()
      && !table_result[ix][29].is_null()
      && !table_result[ix][30].is_null()
      && !table_result[ix][31].is_null())
    {
      std::string adv_event_date_century_str = table_result[ix][22].
        as<std::string>("");
      std::string adv_event_date_year_str = table_result[ix][23].
        as<std::string>("");
      std::string adv_event_date_month_str = table_result[ix][24].
        as<std::string>("");
      std::string adv_event_date_day_str = table_result[ix][25].
        as<std::string>("");
      std::string adv_event_type_str = table_result[ix][26].
        as<std::string>("");
      std::string code_sys_id_str = table_result[ix][27].
        as<std::string>("");
      std::string code_sys_name_str = table_result[ix][28].
        as<std::string>("");
      std::string code_code_str = table_result[ix][29].
        as<std::string>("");
      std::string code_label_str = table_result[ix][30].
        as<std::string>("");
      std::string free_text_product_str = table_result[ix][31].
        as<std::string>("");

      std::vector < std::pair < std::string, bool>>
        adv_event_date_century_vect;
      std::vector < std::pair < std::string, bool>>
        adv_event_date_year_vect;
      std::vector < std::pair < std::string, bool>>
        adv_event_date_month_vect;
      std::vector < std::pair < std::string, bool>>
        adv_event_date_day_vect;
      std::vector < std::pair < ice::INT32, bool>>
        adv_event_type_vect;
      std::vector < std::pair < std::string, bool>>
        code_sys_id_vect;
      std::vector < std::pair < std::string, bool>>
        code_sys_name_vect;
      std::vector < std::pair < std::string, bool>>
        code_code_vect;
      std::vector < std::pair < std::string, bool>>
        code_label_vect;
      std::vector < std::pair < std::string, bool>>
        free_text_product_vect;

      DicesRcDriver status = ParseCSVToArray(
        &adv_event_date_century_vect,
        adv_event_date_century_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &adv_event_date_year_vect,
        adv_event_date_year_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &adv_event_date_month_vect,
        adv_event_date_month_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &adv_event_date_day_vect,
        adv_event_date_day_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &adv_event_type_vect,
        adv_event_type_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &code_sys_id_vect,
        code_sys_id_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &code_sys_name_vect,
        code_sys_name_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &code_code_vect,
        code_code_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &code_label_vect,
        code_label_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &free_text_product_vect,
        free_text_product_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }

      // Compare first vector size against all other vector sizes.
      if (adv_event_date_century_vect.size() != adv_event_date_year_vect.size()
        || adv_event_date_century_vect.size() != adv_event_date_month_vect.size()
        || adv_event_date_century_vect.size() != adv_event_date_day_vect.size()
        || adv_event_date_century_vect.size() != adv_event_type_vect.size()
        || adv_event_date_century_vect.size() != code_sys_id_vect.size()
        || adv_event_date_century_vect.size() != code_sys_name_vect.size()
        || adv_event_date_century_vect.size() != code_code_vect.size()
        || adv_event_date_century_vect.size() != code_label_vect.size()
        || adv_event_date_century_vect.size() != free_text_product_vect.size())
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "To set ice::AdverseEventList "
          "sequence, attributes must have the same number of elements.");
        return DicesRcDriver::FAIL;
      }

      for (int iy = 0; iy < adv_event_date_century_vect.size(); iy++)
      {
        if (!adv_event_date_century_vect.at(iy).second)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "In ice::Date, "
            "century data member is not optional, therefore null is "
            "not an acceptable value.");
          return DicesRcDriver::FAIL;
        }
      }
      for (int iy = 0; iy < adv_event_date_year_vect.size(); iy++)
      {
        if (!adv_event_date_year_vect.at(iy).second)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "In ice::Date, "
            "year data member is not optional, therefore null is "
            "not an acceptable value.");
          return DicesRcDriver::FAIL;
        }
      }
      for (int iy = 0; iy < adv_event_date_month_vect.size(); iy++)
      {
        if (!adv_event_date_month_vect.at(iy).second)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "In ice::Date, "
            "month data member is not optional, therefore null is "
            "not an acceptable value.");
          return DicesRcDriver::FAIL;
        }
      }
      for (int iy = 0; iy < adv_event_date_day_vect.size(); iy++)
      {
        if (!adv_event_date_day_vect.at(iy).second)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "In ice::Date, "
            "day data member is not optional, therefore null is "
            "not an acceptable value.");
          return DicesRcDriver::FAIL;
        }
      }
      for (int iy = 0; iy < adv_event_type_vect.size(); iy++)
      {
        if (!adv_event_type_vect.at(iy).second)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "In ice::AdverseEventEntry, "
            "adverse_event_type data member is not optional, therefore null "
            "is not an acceptable value.");
          return DicesRcDriver::FAIL;
        }
      }
      // NOTE: If received a null string for a DDS string which is not
      // optional, an empty string is stored in DDS instance.
      if (_allergy_response_instance_list.at(ix).second->adverse_events.
        ensure_length(
        adv_event_date_century_vect.size(),
        adv_event_date_century_vect.size()) == false)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
          "ice::AdverseEventList DDS sequence with length: "
          << adv_event_date_century_vect.size());
        return DicesRcDriver::FAIL;
      }
      for (int iy = 0; iy < adv_event_date_century_vect.size(); iy++)
      {
        DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
          adv_event_date_century_vect.at(iy).first,
          & _allergy_response_instance_list.at(ix).second->
          adverse_events[iy].adverse_event_date.century);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
      }
      for (int iy = 0; iy < adv_event_date_year_vect.size(); iy++)
      {
        DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
          adv_event_date_year_vect.at(iy).first,
          & _allergy_response_instance_list.at(ix).second->
          adverse_events[iy].adverse_event_date.year);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
      }
      for (int iy = 0; iy < adv_event_date_month_vect.size(); iy++)
      {
        DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
          adv_event_date_month_vect.at(iy).first,
          & _allergy_response_instance_list.at(ix).second->
          adverse_events[iy].adverse_event_date.month);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
      }
      for (int iy = 0; iy < adv_event_date_day_vect.size(); iy++)
      {
        DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
          adv_event_date_day_vect.at(iy).first,
          &_allergy_response_instance_list.at(ix).second->
          adverse_events[iy].adverse_event_date.day);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
      }
      for (int iy = 0; iy < adv_event_type_vect.size(); iy++)
      {
        _allergy_response_instance_list.at(ix).second->adverse_events[iy].
          adverse_event_type = static_cast<ice::AdverseEventType>(
          adv_event_type_vect.at(iy).first);
      }
      for (int iy = 0; iy < code_sys_id_vect.size(); iy++)
      {
        _allergy_response_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code_system_pair.code_system_identifier =
          DDS::String_alloc(ice::MEDIUM_STRING_LEN);
        if (!_allergy_response_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code_system_pair.code_system_identifier)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for DDS String code_system_identifier");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }

        strncpy(
          _allergy_response_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code_system_pair.code_system_identifier,
          code_sys_id_vect.at(iy).first.c_str(),
          ice::MEDIUM_STRING_LEN);
        _allergy_response_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code_system_pair.code_system_identifier[
          ice::MEDIUM_STRING_LEN] = '\0';
      }
      for (int iy = 0; iy < code_sys_name_vect.size(); iy++)
      {
        _allergy_response_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code_system_pair.code_system_name =
          DDS::String_alloc(ice::MEDIUM_STRING_LEN);
        if (!_allergy_response_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code_system_pair.code_system_name)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for DDS String code_system_name");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }

        strncpy(
          _allergy_response_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code_system_pair.code_system_name,
          code_sys_name_vect.at(iy).first.c_str(),
          ice::MEDIUM_STRING_LEN);
        _allergy_response_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code_system_pair.code_system_name[
          ice::MEDIUM_STRING_LEN] = '\0';
      }
      for (int iy = 0; iy < code_code_vect.size(); iy++)
      {
        _allergy_response_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code =
          DDS::String_alloc(ice::SHORT_STRING_LEN);
        if (!_allergy_response_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for DDS String code");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }

        strncpy(
          _allergy_response_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code,
          code_code_vect.at(iy).first.c_str(),
          ice::SHORT_STRING_LEN);
        _allergy_response_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code[ice::SHORT_STRING_LEN] = '\0';
      }
      for (int iy = 0; iy < code_label_vect.size(); iy++)
      {
        _allergy_response_instance_list.at(ix).second->adverse_events[iy].
          coded_product.label =
          DDS::String_alloc(ice::MEDIUM_STRING_LEN);
        if (!_allergy_response_instance_list.at(ix).second->adverse_events[iy].
          coded_product.label)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for DDS String label");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }

        strncpy(
          _allergy_response_instance_list.at(ix).second->adverse_events[iy].
          coded_product.label,
          code_label_vect.at(iy).first.c_str(),
          ice::MEDIUM_STRING_LEN);
        _allergy_response_instance_list.at(ix).second->adverse_events[iy].
          coded_product.label[ice::MEDIUM_STRING_LEN] = '\0';
      }
      for (int iy = 0; iy < free_text_product_vect.size(); iy++)
      {
        _allergy_response_instance_list.at(ix).second->adverse_events[iy].
          free_text_product =
          DDS::String_alloc(ice::LONGLONG_STRING_LEN);
        if (!_allergy_response_instance_list.at(ix).second->adverse_events[iy].
          free_text_product)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for DDS String free_text_product");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }

        strncpy(
          _allergy_response_instance_list.at(ix).second->adverse_events[iy].
          free_text_product,
          free_text_product_vect.at(iy).first.c_str(),
          ice::LONGLONG_STRING_LEN);
        _allergy_response_instance_list.at(ix).second->adverse_events[iy].
          free_text_product[ice::LONGLONG_STRING_LEN] = '\0';
      }

      if (!table_result[ix][32].is_null()
        && !table_result[ix][33].is_null()
        && !table_result[ix][34].is_null()
        && !table_result[ix][35].is_null()
        && !table_result[ix][36].is_null()
        && !table_result[ix][37].is_null()
        && !table_result[ix][38].is_null())
      {
        std::string reactions_sys_id = table_result[ix][32].
          as<std::string>("");
        std::string reactions_sys_name = table_result[ix][33].
          as<std::string>("");
        std::string reactions_code = table_result[ix][34].
          as<std::string>("");
        std::string reactions_label = table_result[ix][35].
          as<std::string>("");
        std::string reactions_free_txt = table_result[ix][36].
          as<std::string>("");
        std::string reactions_severity = table_result[ix][37].
          as<std::string>("");
        std::string reactions_free_txt_severity = table_result[ix][38].
          as<std::string>("");

        std::vector<std::pair<std::string, std::vector<unsigned int>>>
          reactions_sys_id_vect;
        std::vector<std::pair<std::string, std::vector<unsigned int>>>
          reactions_sys_name_vect;
        std::vector<std::pair<std::string, std::vector<unsigned int>>>
          reactions_code_vect;
        std::vector<std::pair<std::string, std::vector<unsigned int>>>
          reactions_label_vect;
        std::vector<std::pair<std::string, std::vector<unsigned int>>>
          reactions_free_txt_vect;
        std::vector<std::pair<std::string, std::vector<unsigned int>>>
          reactions_severity_vect;
        std::vector<std::pair<std::string, std::vector<unsigned int>>>
          reactions_free_txt_severity_vect;

        status = ParseCSVSequences(
          &reactions_sys_id_vect,
          reactions_sys_id);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        status = ParseCSVSequences(
          &reactions_sys_name_vect,
          reactions_sys_name);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        status = ParseCSVSequences(
          &reactions_code_vect,
          reactions_code);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        status = ParseCSVSequences(
          &reactions_label_vect,
          reactions_label);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        status = ParseCSVSequences(
          &reactions_free_txt_vect,
          reactions_free_txt);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        status = ParseCSVSequences(
          &reactions_severity_vect,
          reactions_severity);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        status = ParseCSVSequences(
          &reactions_free_txt_severity_vect,
          reactions_free_txt_severity);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }

        if (reactions_sys_id_vect.size() != reactions_sys_name_vect.size()
          || reactions_sys_id_vect.size() != reactions_code_vect.size()
          || reactions_sys_id_vect.size() != reactions_label_vect.size()
          || reactions_sys_id_vect.size() != reactions_free_txt_vect.size()
          || reactions_sys_id_vect.size() != reactions_severity_vect.size()
          || reactions_sys_id_vect.size() != reactions_free_txt_severity_vect.size())
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "The number of sequences should "
            "be the same for each ReactionList entry");
          return DicesRcDriver::FAIL;
        }

        for (int iy = 0; iy < reactions_sys_id_vect.size(); iy++)
        {
          if (reactions_sys_id_vect.at(iy).second.size() != 1
            || reactions_sys_name_vect.at(iy).second.size() != 1
            || reactions_code_vect.at(iy).second.size() != 1
            || reactions_label_vect.at(iy).second.size() != 1
            || reactions_free_txt_vect.at(iy).second.size() != 1
            || reactions_severity_vect.at(iy).second.size() != 1
            || reactions_free_txt_severity_vect.at(iy).second.size() != 1)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "The ReactionList sequence "
              "depth should be one.");
            return DicesRcDriver::FAIL;
          }
        }

        // Ensure length of sequences. If null is found and element is not
        // a string data type, the Reaction list sequences length should be
        // set to zero.
        for (int iy = 0; iy < reactions_sys_id_vect.size(); iy++)
        {
          std::vector < std::pair < std::string, bool>>
            reactions_sys_id_sub_vect;
          std::vector < std::pair < std::string, bool>>
            reactions_sys_name_sub_vect;
          std::vector < std::pair < std::string, bool>>
            reactions_code_sub_vect;
          std::vector < std::pair < std::string, bool>>
            reactions_label_sub_vect;
          std::vector < std::pair < std::string, bool>>
            reactions_free_txt_sub_vect;
          std::vector < std::pair < ice::INT32, bool>>
            reactions_severity_sub_vect;
          std::vector < std::pair < std::string, bool>>
            reactions_free_txt_severity_sub_vect;

          DicesRcDriver status = ParseCSVToArray(
            &reactions_sys_id_sub_vect,
            reactions_sys_id_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }
          status = ParseCSVToArray(
            &reactions_sys_name_sub_vect,
            reactions_sys_name_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }
          status = ParseCSVToArray(
            &reactions_code_sub_vect,
            reactions_code_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }
          status = ParseCSVToArray(
            &reactions_label_sub_vect,
            reactions_label_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }
          status = ParseCSVToArray(
            &reactions_free_txt_sub_vect,
            reactions_free_txt_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }
          status = ParseCSVToArray(
            &reactions_severity_sub_vect,
            reactions_severity_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }
          status = ParseCSVToArray(
            &reactions_free_txt_severity_sub_vect,
            reactions_free_txt_severity_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }

          for (int iz = 0; iz < reactions_severity_sub_vect.size(); iz++)
          {
            unsigned int adv_index = reactions_sys_id_vect.at(iy).second.at(0);
            int reaction_list_length = 0;
            if (!reactions_severity_sub_vect.at(iz).second)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Found an null element in "
                "reaction coded severity. Allergy instance at position "
                << ix << " contains a Reaction list adverse_events[" << adv_index
                << "].reactions which will be empty");
              reaction_list_length = 0;
            }
            else
            {
              reaction_list_length = reactions_severity_sub_vect.size();
            }

            if (_allergy_response_instance_list.at(ix).second->
              adverse_events[adv_index].reactions.ensure_length(
              reaction_list_length, reaction_list_length) == false)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
                "ice::ReactionList DDS sequence with length: "
                << reactions_severity_sub_vect.size());
              return DicesRcDriver::FAIL;
            }
          }
        }

        for (int iy = 0; iy < reactions_sys_id_vect.size(); iy++)
        {
          std::vector < std::pair < std::string, bool>>
            reactions_sys_id_sub_vect;

          DicesRcDriver status = ParseCSVToArray(
            &reactions_sys_id_sub_vect,
            reactions_sys_id_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }

          unsigned int adv_index = reactions_sys_id_vect.at(iy).second.at(0);

          if (!_allergy_response_instance_list.at(ix).second->
            adverse_events[adv_index].reactions.length()) continue;

          for (int iz = 0; iz < reactions_sys_id_sub_vect.size(); iz++)
          {
            _allergy_response_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.code_system_pair.code_system_identifier =
              DDS::String_alloc(ice::MEDIUM_STRING_LEN);
            if (!_allergy_response_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.code_system_pair.code_system_identifier)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
                "for DDS String code_system_identifier");
              return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
            }

            strncpy(
              _allergy_response_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.code_system_pair.code_system_identifier,
              reactions_sys_id_sub_vect.at(iz).first.c_str(),
              ice::MEDIUM_STRING_LEN);
            _allergy_response_instance_list.at(ix).second->adverse_events
              [adv_index].reactions[iz].coded_reaction.
              code_system_pair.code_system_identifier[
              ice::MEDIUM_STRING_LEN] = '\0';
          }
        }
        for (int iy = 0; iy < reactions_sys_name_vect.size(); iy++)
        {
          std::vector < std::pair < std::string, bool>>
            reactions_sys_name_sub_vect;

          DicesRcDriver status = ParseCSVToArray(
            &reactions_sys_name_sub_vect,
            reactions_sys_name_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }

          unsigned int adv_index = reactions_sys_id_vect.at(iy).second.at(0);

          if (!_allergy_response_instance_list.at(ix).second->
            adverse_events[adv_index].reactions.length()) continue;

          for (int iz = 0; iz < reactions_sys_name_sub_vect.size(); iz++)
          {
            _allergy_response_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.code_system_pair.code_system_name =
              DDS::String_alloc(ice::MEDIUM_STRING_LEN);
            if (!_allergy_response_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.code_system_pair.code_system_name)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
                "for DDS String code_system_name");
              return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
            }

            strncpy(
              _allergy_response_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.code_system_pair.code_system_name,
              reactions_sys_name_sub_vect.at(iz).first.c_str(),
              ice::MEDIUM_STRING_LEN);
            _allergy_response_instance_list.at(ix).second->adverse_events
              [adv_index].reactions[iz].coded_reaction.
              code_system_pair.code_system_name[
              ice::MEDIUM_STRING_LEN] = '\0';
          }
        }
        for (int iy = 0; iy < reactions_code_vect.size(); iy++)
        {
          std::vector < std::pair < std::string, bool>>
            reactions_code_sub_vect;

          DicesRcDriver status = ParseCSVToArray(
            &reactions_code_sub_vect,
            reactions_code_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }

          unsigned int adv_index = reactions_code_vect.at(iy).second.at(0);

          if (!_allergy_response_instance_list.at(ix).second->
            adverse_events[adv_index].reactions.length()) continue;

          for (int iz = 0; iz < reactions_code_sub_vect.size(); iz++)
          {
            _allergy_response_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.code =
              DDS::String_alloc(ice::SHORT_STRING_LEN);
            if (!_allergy_response_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.code)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
                "for DDS String code");
              return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
            }

            strncpy(
              _allergy_response_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.code,
              reactions_code_sub_vect.at(iz).first.c_str(),
              ice::SHORT_STRING_LEN);
            _allergy_response_instance_list.at(ix).second->adverse_events
              [adv_index].reactions[iz].coded_reaction.
              code[ice::SHORT_STRING_LEN] = '\0';
          }
        }
        for (int iy = 0; iy < reactions_label_vect.size(); iy++)
        {
          std::vector < std::pair < std::string, bool>>
            reactions_label_sub_vect;

          DicesRcDriver status = ParseCSVToArray(
            &reactions_label_sub_vect,
            reactions_label_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }

          unsigned int adv_index = reactions_code_vect.at(iy).second.at(0);

          if (!_allergy_response_instance_list.at(ix).second->
            adverse_events[adv_index].reactions.length()) continue;

          for (int iz = 0; iz < reactions_label_sub_vect.size(); iz++)
          {
            _allergy_response_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.label =
              DDS::String_alloc(ice::MEDIUM_STRING_LEN);
            if (!_allergy_response_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.label)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
                "for DDS String label");
              return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
            }
            strncpy(
              _allergy_response_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.label,
              reactions_label_sub_vect.at(iz).first.c_str(),
              ice::MEDIUM_STRING_LEN);
            _allergy_response_instance_list.at(ix).second->adverse_events
              [adv_index].reactions[iz].coded_reaction.
              label[ice::MEDIUM_STRING_LEN] = '\0';
          }
        }
        for (int iy = 0; iy < reactions_free_txt_vect.size(); iy++)
        {
          std::vector < std::pair < std::string, bool>>
            reactions_free_txt_sub_vect;

          DicesRcDriver status = ParseCSVToArray(
            &reactions_free_txt_sub_vect,
            reactions_free_txt_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }

          unsigned int adv_index = reactions_free_txt_vect.at(iy).second.at(0);

          if (!_allergy_response_instance_list.at(ix).second->
            adverse_events[adv_index].reactions.length()) continue;

          for (int iz = 0; iz < reactions_free_txt_sub_vect.size(); iz++)
          {
            _allergy_response_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              free_text_reaction =
              DDS::String_alloc(ice::LONGLONG_STRING_LEN);
            if (!_allergy_response_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              free_text_reaction)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
                "for DDS String label");
              return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
            }
            strncpy(
              _allergy_response_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              free_text_reaction,
              reactions_free_txt_sub_vect.at(iz).first.c_str(),
              ice::LONGLONG_STRING_LEN);
            _allergy_response_instance_list.at(ix).second->adverse_events
              [adv_index].reactions[iz].free_text_reaction
              [ice::LONGLONG_STRING_LEN] = '\0';
          }
        }
        for (int iy = 0; iy < reactions_severity_vect.size(); iy++)
        {
          std::vector < std::pair < ice::INT32, bool>>
            reactions_severity_sub_vect;

          DicesRcDriver status = ParseCSVToArray(
            &reactions_severity_sub_vect,
            reactions_severity_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }

          unsigned int adv_index = reactions_severity_vect.at(iy).second.at(0);

          if (!_allergy_response_instance_list.at(ix).second->
            adverse_events[adv_index].reactions.length()) continue;

          for (int iz = 0; iz < reactions_severity_sub_vect.size(); iz++)
          {
            _allergy_response_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].severity.
              coded_severity = static_cast<ice::CodedSeverityType>(
              reactions_severity_sub_vect.at(iz).first);
          }
        }
        for (int iy = 0; iy < reactions_free_txt_severity_vect.size(); iy++)
        {
          std::vector < std::pair < std::string, bool>>
            reactions_free_txt_severity_sub_vect;

          DicesRcDriver status = ParseCSVToArray(
            &reactions_free_txt_severity_sub_vect,
            reactions_free_txt_severity_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }

          unsigned int adv_index = reactions_free_txt_severity_vect.at(iy).second.at(0);

          if (!_allergy_response_instance_list.at(ix).second->
            adverse_events[adv_index].reactions.length()) continue;

          for (int iz = 0; iz < reactions_free_txt_severity_sub_vect.size(); iz++)
          {
            _allergy_response_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].severity.
              free_text_severity =
              DDS::String_alloc(ice::LONGLONG_STRING_LEN);
            if (!_allergy_response_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].severity.
              free_text_severity)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
                "for DDS String free_text_severity");
              return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
            }
            strncpy(
              _allergy_response_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].severity.
              free_text_severity,
              reactions_free_txt_severity_sub_vect.at(iz).first.c_str(),
              ice::LONGLONG_STRING_LEN);
            _allergy_response_instance_list.at(ix).second->adverse_events
              [adv_index].reactions[iz].severity.
              free_text_severity[ice::LONGLONG_STRING_LEN] = '\0';
          }
        }
      }
    }
  }
  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ReadFromAllergyReqTable()
{
  static const char* sfn = "Parser::ReadFromAllergyReqTable() ";

  if (_database_connection == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Database is not connected");
    return DicesRcDriver::DATABASE_CONNECTION_FAILURE;
  }

  std::string column_names = kHeaderColumnNames
    + ", " + kTopColumnNames
    + ", " + kAllergyColumnNames;
  pqxx::result table_result;
  try
  {
    pqxx::work database_work(*_database_connection);
    table_result = database_work.exec(
      "SELECT " + column_names + " FROM " + std::string(kTableAllergyReq) + ";");
    database_work.commit();
  }
  catch (const std::exception &ex)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to read the " << kTableAllergyReq
      << " table from the database. " << ex.what());
    return DicesRcDriver::DATABASE_READ_TABLE_FAILURE;
  }

  if (table_result.columns() < kExpectedAllergyTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table result contains "
      << table_result.columns() << " columns, but this function requires "
      << kExpectedAllergyTableColumnCount << " columns to parse successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  try
  {
    _allergy_req_command_instance_list.resize(table_result.size());
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "allergy request instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  for (int ix = 0; ix < table_result.size(); ix++)
  {
    ice::Allergy* allergy_instance = ice::AllergyTypeSupport::create_data();
    if (!allergy_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for "
        "Allergy");
      return DicesRcDriver::ALLERGY_INSTANCE_CREATE_FAILURE;
    }
    _allergy_req_command_instance_list.at(ix).second = allergy_instance;

    strncpy(
      _allergy_req_command_instance_list.at(ix).second->ice_id,
      table_result[ix][2].as<std::string>("").c_str(),
      ice::MAX_LEN_ICE_ID);
    _allergy_req_command_instance_list.at(ix).second->ice_id[
      ice::MAX_LEN_ICE_ID] = '\0';

    _allergy_req_command_instance_list.at(ix).second->handle =
      table_result[ix][3].as<ice::HANDLE>(0);

    _allergy_req_command_instance_list.at(ix).second->parent_handle =
      table_result[ix][4].as<ice::HANDLE>(0);

    _allergy_req_command_instance_list.at(ix).second->source_timestamp.
      seconds = table_result[ix][5].as<long>(0);
    _allergy_req_command_instance_list.at(ix).second->source_timestamp.
      nanoseconds = table_result[ix][6].as<long>(0);

    strncpy(
      _allergy_req_command_instance_list.at(ix).second->patient_id.given_name,
      table_result[ix][7].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _allergy_req_command_instance_list.at(ix).second->patient_id.given_name[
      ice::SHORT_STRING_LEN] = '\0';
    strncpy(
      _allergy_req_command_instance_list.at(ix).second->patient_id.family_name,
      table_result[ix][8].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _allergy_req_command_instance_list.at(ix).second->patient_id.family_name[
      ice::SHORT_STRING_LEN] = '\0';
    strncpy(
      _allergy_req_command_instance_list.at(ix).second->patient_id.middle_name,
      table_result[ix][9].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _allergy_req_command_instance_list.at(ix).second->patient_id.middle_name[
      ice::SHORT_STRING_LEN] = '\0';

    if (table_result[ix][10].is_null()
      && table_result[ix][11].is_null()
      && table_result[ix][12].is_null()
      && table_result[ix][13].is_null())
    {
      _allergy_req_command_instance_list.at(ix).second->patient_id.
        date_of_birth = nullptr;
    }
    else
    {
      _allergy_req_command_instance_list.at(ix).second->patient_id.
        date_of_birth = reinterpret_cast<ice::Date*>(DDS::Heap_malloc(sizeof(
        ice::Date)));
      if (!_allergy_req_command_instance_list.at(ix).second->patient_id.
        date_of_birth)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::Date");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][10].as<std::string>(""),
        &_allergy_req_command_instance_list.at(ix).second->patient_id.
        date_of_birth->century);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][11].as<std::string>(""),
        &_allergy_req_command_instance_list.at(ix).second->patient_id.
        date_of_birth->year);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][12].as<std::string>(""),
        &_allergy_req_command_instance_list.at(ix).second->patient_id.
        date_of_birth->month);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][13].as<std::string>(""),
        &_allergy_req_command_instance_list.at(ix).second->patient_id.
        date_of_birth->day);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
    }
    strncpy(
      _allergy_req_command_instance_list.at(ix).second->patient_id.patient_id,
      table_result[ix][14].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _allergy_req_command_instance_list.at(ix).second->patient_id.patient_id[
      ice::MEDIUM_STRING_LEN] = '\0';
    strncpy(
      _allergy_req_command_instance_list.at(ix).second->patient_id.
      patient_id_provenance,
      table_result[ix][15].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _allergy_req_command_instance_list.at(ix).second->patient_id.
      patient_id_provenance[ice::MEDIUM_STRING_LEN] = '\0';
    _allergy_req_command_instance_list.at(ix).second->patient_id.verified =
      static_cast<ice::BOOL>(table_result[ix][16].as<bool>(false));
    _allergy_req_command_instance_list.at(ix).second->patient_id.
      pat_admit_state = static_cast<ice::PatAdmitState>(
      table_result[ix][17].as<int>(0));
    _allergy_req_command_instance_list.at(ix).second->patient_id.
      pat_episode_id = table_result[ix][18].as<ice::PatEpisode>(0);
    _allergy_req_command_instance_list.at(ix).second->patient_id.
      episode_start.seconds = table_result[ix][19].as<long>(0);
    _allergy_req_command_instance_list.at(ix).second->patient_id.
      episode_start.nanoseconds = table_result[ix][20].as<long>(0);
    _allergy_req_command_instance_list.at(ix).second->adverse_event_count =
      table_result[ix][21].as<ice::INTU16>(0);
    // AdverseEventList
    // NOTE: If any fields are null, then SystemSpec sequence will be empty.
    if (table_result[ix][22].is_null() == false
      && table_result[ix][23].is_null() == false
      && table_result[ix][24].is_null() == false
      && table_result[ix][25].is_null() == false
      && table_result[ix][26].is_null() == false
      && table_result[ix][27].is_null() == false
      && table_result[ix][28].is_null() == false
      && table_result[ix][29].is_null() == false
      && table_result[ix][30].is_null() == false
      && table_result[ix][31].is_null() == false)
    {
      std::string adv_event_date_century_str = table_result[ix][22].
        as<std::string>("");
      std::string adv_event_date_year_str = table_result[ix][23].
        as<std::string>("");
      std::string adv_event_date_month_str = table_result[ix][24].
        as<std::string>("");
      std::string adv_event_date_day_str = table_result[ix][25].
        as<std::string>("");
      std::string adv_event_type_str = table_result[ix][26].
        as<std::string>("");
      std::string code_sys_id_str = table_result[ix][27].
        as<std::string>("");
      std::string code_sys_name_str = table_result[ix][28].
        as<std::string>("");
      std::string code_code_str = table_result[ix][29].
        as<std::string>("");
      std::string code_label_str = table_result[ix][30].
        as<std::string>("");
      std::string free_text_product_str = table_result[ix][31].
        as<std::string>("");

      std::vector < std::pair < std::string, bool>>
        adv_event_date_century_vect;
      std::vector < std::pair < std::string, bool>>
        adv_event_date_year_vect;
      std::vector < std::pair < std::string, bool>>
        adv_event_date_month_vect;
      std::vector < std::pair < std::string, bool>>
        adv_event_date_day_vect;
      std::vector < std::pair < ice::INT32, bool>>
        adv_event_type_vect;
      std::vector < std::pair < std::string, bool>>
        code_sys_id_vect;
      std::vector < std::pair < std::string, bool>>
        code_sys_name_vect;
      std::vector < std::pair < std::string, bool>>
        code_code_vect;
      std::vector < std::pair < std::string, bool>>
        code_label_vect;
      std::vector < std::pair < std::string, bool>>
        free_text_product_vect;

      DicesRcDriver status = ParseCSVToArray(
        &adv_event_date_century_vect,
        adv_event_date_century_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &adv_event_date_year_vect,
        adv_event_date_year_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &adv_event_date_month_vect,
        adv_event_date_month_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &adv_event_date_day_vect,
        adv_event_date_day_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &adv_event_type_vect,
        adv_event_type_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &code_sys_id_vect,
        code_sys_id_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &code_sys_name_vect,
        code_sys_name_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &code_code_vect,
        code_code_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &code_label_vect,
        code_label_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &free_text_product_vect,
        free_text_product_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }

      // Compare first vector size against all other vector sizes.
      if (adv_event_date_century_vect.size() != adv_event_date_year_vect.size()
        || adv_event_date_century_vect.size() != adv_event_date_month_vect.size()
        || adv_event_date_century_vect.size() != adv_event_date_day_vect.size()
        || adv_event_date_century_vect.size() != adv_event_type_vect.size()
        || adv_event_date_century_vect.size() != code_sys_id_vect.size()
        || adv_event_date_century_vect.size() != code_sys_name_vect.size()
        || adv_event_date_century_vect.size() != code_code_vect.size()
        || adv_event_date_century_vect.size() != code_label_vect.size()
        || adv_event_date_century_vect.size() != free_text_product_vect.size())
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "To set ice::AdverseEventList "
          "sequence, attributes must have the same number of elements.");
        return DicesRcDriver::FAIL;
      }

      for (int iy = 0; iy < adv_event_date_century_vect.size(); iy++)
      {
        if (!adv_event_date_century_vect.at(iy).second)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "In ice::Date, "
            "century data member is not optional, therefore null is "
            "not an acceptable value.");
          return DicesRcDriver::FAIL;
        }
      }
      for (int iy = 0; iy < adv_event_date_year_vect.size(); iy++)
      {
        if (!adv_event_date_year_vect.at(iy).second)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "In ice::Date, "
            "year data member is not optional, therefore null is "
            "not an acceptable value.");
          return DicesRcDriver::FAIL;
        }
      }
      for (int iy = 0; iy < adv_event_date_month_vect.size(); iy++)
      {
        if (!adv_event_date_month_vect.at(iy).second)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "In ice::Date, "
            "month data member is not optional, therefore null is "
            "not an acceptable value.");
          return DicesRcDriver::FAIL;
        }
      }
      for (int iy = 0; iy < adv_event_date_day_vect.size(); iy++)
      {
        if (!adv_event_date_day_vect.at(iy).second)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "In ice::Date, "
            "day data member is not optional, therefore null is "
            "not an acceptable value.");
          return DicesRcDriver::FAIL;
        }
      }
      for (int iy = 0; iy < adv_event_type_vect.size(); iy++)
      {
        if (!adv_event_type_vect.at(iy).second)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "In ice::AdverseEventEntry, "
            "adverse_event_type data member is not optional, therefore null "
            "is not an acceptable value.");
          return DicesRcDriver::FAIL;
        }
      }
      // NOTE: If received a null string for a DDS string which is not
      // optional, an empty string is stored in DDS instance.
      if (_allergy_req_command_instance_list.at(ix).second->adverse_events.
        ensure_length(
        adv_event_date_century_vect.size(),
        adv_event_date_century_vect.size()) == false)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
          "ice::AdverseEventList DDS sequence with length: "
          << adv_event_date_century_vect.size());
        return DicesRcDriver::FAIL;
      }
      for (int iy = 0; iy < adv_event_date_century_vect.size(); iy++)
      {
        DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
          adv_event_date_century_vect.at(iy).first,
          & _allergy_req_command_instance_list.at(ix).second->
          adverse_events[iy].adverse_event_date.century);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
      }
      for (int iy = 0; iy < adv_event_date_year_vect.size(); iy++)
      {
        DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
          adv_event_date_year_vect.at(iy).first,
          & _allergy_req_command_instance_list.at(ix).second->
          adverse_events[iy].adverse_event_date.year);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
      }
      for (int iy = 0; iy < adv_event_date_month_vect.size(); iy++)
      {
        DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
          adv_event_date_month_vect.at(iy).first,
          & _allergy_req_command_instance_list.at(ix).second->
          adverse_events[iy].adverse_event_date.month);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
      }
      for (int iy = 0; iy < adv_event_date_day_vect.size(); iy++)
      {
        DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
          adv_event_date_day_vect.at(iy).first,
          &_allergy_req_command_instance_list.at(ix).second->
          adverse_events[iy].adverse_event_date.day);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
      }
      for (int iy = 0; iy < adv_event_type_vect.size(); iy++)
      {
        _allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          adverse_event_type = static_cast<ice::AdverseEventType>(
          adv_event_type_vect.at(iy).first);
      }
      for (int iy = 0; iy < code_sys_id_vect.size(); iy++)
      {
        _allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code_system_pair.code_system_identifier =
          DDS::String_alloc(ice::MEDIUM_STRING_LEN);
        if (!_allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code_system_pair.code_system_identifier)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for DDS String code_system_identifier");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }

        strncpy(
          _allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code_system_pair.code_system_identifier,
          code_sys_id_vect.at(iy).first.c_str(),
          ice::MEDIUM_STRING_LEN);
        _allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code_system_pair.code_system_identifier[
          ice::MEDIUM_STRING_LEN] = '\0';
      }
      for (int iy = 0; iy < code_sys_name_vect.size(); iy++)
      {
        _allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code_system_pair.code_system_name =
          DDS::String_alloc(ice::MEDIUM_STRING_LEN);
        if (!_allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code_system_pair.code_system_name)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for DDS String code_system_name");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }

        strncpy(
          _allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code_system_pair.code_system_name,
          code_sys_name_vect.at(iy).first.c_str(),
          ice::MEDIUM_STRING_LEN);
        _allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code_system_pair.code_system_name[
          ice::MEDIUM_STRING_LEN] = '\0';
      }
      for (int iy = 0; iy < code_code_vect.size(); iy++)
      {
        _allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code =
          DDS::String_alloc(ice::SHORT_STRING_LEN);
        if (!_allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for DDS String code");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }

        strncpy(
          _allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code,
          code_code_vect.at(iy).first.c_str(),
          ice::SHORT_STRING_LEN);
        _allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          coded_product.code[ice::SHORT_STRING_LEN] = '\0';
      }
      for (int iy = 0; iy < code_label_vect.size(); iy++)
      {
        _allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          coded_product.label =
          DDS::String_alloc(ice::MEDIUM_STRING_LEN);
        if (!_allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          coded_product.label)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for DDS String label");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }

        strncpy(
          _allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          coded_product.label,
          code_label_vect.at(iy).first.c_str(),
          ice::MEDIUM_STRING_LEN);
        _allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          coded_product.label[ice::MEDIUM_STRING_LEN] = '\0';
      }
      for (int iy = 0; iy < free_text_product_vect.size(); iy++)
      {
        _allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          free_text_product =
          DDS::String_alloc(ice::LONGLONG_STRING_LEN);
        if (!_allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          free_text_product)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
            "for DDS String free_text_product");
          return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
        }

        strncpy(
          _allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          free_text_product,
          free_text_product_vect.at(iy).first.c_str(),
          ice::LONGLONG_STRING_LEN);
        _allergy_req_command_instance_list.at(ix).second->adverse_events[iy].
          free_text_product[ice::LONGLONG_STRING_LEN] = '\0';
      }

      if (table_result[ix][32].is_null() == false
        && table_result[ix][33].is_null() == false
        && table_result[ix][34].is_null() == false
        && table_result[ix][35].is_null() == false
        && table_result[ix][36].is_null() == false
        && table_result[ix][37].is_null() == false
        && table_result[ix][38].is_null() == false)
      {
        std::string reactions_sys_id = table_result[ix][32].
          as<std::string>("");
        std::string reactions_sys_name = table_result[ix][33].
          as<std::string>("");
        std::string reactions_code = table_result[ix][34].
          as<std::string>("");
        std::string reactions_label = table_result[ix][35].
          as<std::string>("");
        std::string reactions_free_txt = table_result[ix][36].
          as<std::string>("");
        std::string reactions_severity = table_result[ix][37].
          as<std::string>("");
        std::string reactions_free_txt_severity = table_result[ix][38].
          as<std::string>("");

        std::vector<std::pair<std::string, std::vector<unsigned int>>>
          reactions_sys_id_vect;
        std::vector<std::pair<std::string, std::vector<unsigned int>>>
          reactions_sys_name_vect;
        std::vector<std::pair<std::string, std::vector<unsigned int>>>
          reactions_code_vect;
        std::vector<std::pair<std::string, std::vector<unsigned int>>>
          reactions_label_vect;
        std::vector<std::pair<std::string, std::vector<unsigned int>>>
          reactions_free_txt_vect;
        std::vector<std::pair<std::string, std::vector<unsigned int>>>
          reactions_severity_vect;
        std::vector<std::pair<std::string, std::vector<unsigned int>>>
          reactions_free_txt_severity_vect;

        status = ParseCSVSequences(
          &reactions_sys_id_vect,
          reactions_sys_id);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        status = ParseCSVSequences(
          &reactions_sys_name_vect,
          reactions_sys_name);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        status = ParseCSVSequences(
          &reactions_code_vect,
          reactions_code);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        status = ParseCSVSequences(
          &reactions_label_vect,
          reactions_label);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        status = ParseCSVSequences(
          &reactions_free_txt_vect,
          reactions_free_txt);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        status = ParseCSVSequences(
          &reactions_severity_vect,
          reactions_severity);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }
        status = ParseCSVSequences(
          &reactions_free_txt_severity_vect,
          reactions_free_txt_severity);
        if (status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
            DicesRcDriverToString(status));
          return status;
        }

        if (reactions_sys_id_vect.size() != reactions_sys_name_vect.size()
          || reactions_sys_id_vect.size() != reactions_code_vect.size()
          || reactions_sys_id_vect.size() != reactions_label_vect.size()
          || reactions_sys_id_vect.size() != reactions_free_txt_vect.size()
          || reactions_sys_id_vect.size() != reactions_severity_vect.size()
          || reactions_sys_id_vect.size() != reactions_free_txt_severity_vect.size())
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "The number of sequences should "
            "be the same for each ReactionList entry");
          return DicesRcDriver::FAIL;
        }

        for (int iy = 0; iy < reactions_sys_id_vect.size(); iy++)
        {
          if (reactions_sys_id_vect.at(iy).second.size() != 1
            || reactions_sys_name_vect.at(iy).second.size() != 1
            || reactions_code_vect.at(iy).second.size() != 1
            || reactions_label_vect.at(iy).second.size() != 1
            || reactions_free_txt_vect.at(iy).second.size() != 1
            || reactions_severity_vect.at(iy).second.size() != 1
            || reactions_free_txt_severity_vect.at(iy).second.size() != 1)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "The ReactionList sequence "
              "depth should be one.");
            return DicesRcDriver::FAIL;
          }
        }

        // Ensure length of sequences. If null is found and element is not
        // a string data type, the Reaction list sequences length should be
        // set to zero.
        for (int iy = 0; iy < reactions_sys_id_vect.size(); iy++)
        {
          std::vector < std::pair < std::string, bool>>
            reactions_sys_id_sub_vect;
          std::vector < std::pair < std::string, bool>>
            reactions_sys_name_sub_vect;
          std::vector < std::pair < std::string, bool>>
            reactions_code_sub_vect;
          std::vector < std::pair < std::string, bool>>
            reactions_label_sub_vect;
          std::vector < std::pair < std::string, bool>>
            reactions_free_txt_sub_vect;
          std::vector < std::pair < ice::INT32, bool>>
            reactions_severity_sub_vect;
          std::vector < std::pair < std::string, bool>>
            reactions_free_txt_severity_sub_vect;

          DicesRcDriver status = ParseCSVToArray(
            &reactions_sys_id_sub_vect,
            reactions_sys_id_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }
          status = ParseCSVToArray(
            &reactions_sys_name_sub_vect,
            reactions_sys_name_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }
          status = ParseCSVToArray(
            &reactions_code_sub_vect,
            reactions_code_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }
          status = ParseCSVToArray(
            &reactions_label_sub_vect,
            reactions_label_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }
          status = ParseCSVToArray(
            &reactions_free_txt_sub_vect,
            reactions_free_txt_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }
          status = ParseCSVToArray(
            &reactions_severity_sub_vect,
            reactions_severity_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }
          status = ParseCSVToArray(
            &reactions_free_txt_severity_sub_vect,
            reactions_free_txt_severity_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }

          for (int iz = 0; iz < reactions_severity_sub_vect.size(); iz++)
          {
            unsigned int adv_index = reactions_sys_id_vect.at(iy).second.at(0);
            int reaction_list_length = 0;
            if (!reactions_severity_sub_vect.at(iz).second)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Found an null element in "
                "reaction coded severity. Allergy instance at position "
                << ix << " contains a Reaction list adverse_events[" << adv_index
                << "].reactions which will be empty");
              reaction_list_length = 0;
            }
            else
            {
              reaction_list_length = reactions_severity_sub_vect.size();
            }

            if (_allergy_req_command_instance_list.at(ix).second->
              adverse_events[adv_index].reactions.ensure_length(
              reaction_list_length, reaction_list_length) == false)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
                "ice::ReactionList DDS sequence with length: "
                << reactions_severity_sub_vect.size());
              return DicesRcDriver::FAIL;
            }
          }
        }

        for (int iy = 0; iy < reactions_sys_id_vect.size(); iy++)
        {
          std::vector < std::pair < std::string, bool>>
            reactions_sys_id_sub_vect;

          DicesRcDriver status = ParseCSVToArray(
            &reactions_sys_id_sub_vect,
            reactions_sys_id_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }

          unsigned int adv_index = reactions_sys_id_vect.at(iy).second.at(0);

          if (!_allergy_req_command_instance_list.at(ix).second->
            adverse_events[adv_index].reactions.length()) continue;

          for (int iz = 0; iz < reactions_sys_id_sub_vect.size(); iz++)
          {
            _allergy_req_command_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.code_system_pair.code_system_identifier =
              DDS::String_alloc(ice::MEDIUM_STRING_LEN);
            if (!_allergy_req_command_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.code_system_pair.code_system_identifier)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
                "for DDS String code_system_identifier");
              return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
            }

            strncpy(
              _allergy_req_command_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.code_system_pair.code_system_identifier,
              reactions_sys_id_sub_vect.at(iz).first.c_str(),
              ice::MEDIUM_STRING_LEN);
            _allergy_req_command_instance_list.at(ix).second->adverse_events
              [adv_index].reactions[iz].coded_reaction.
              code_system_pair.code_system_identifier[
              ice::MEDIUM_STRING_LEN] = '\0';
          }
        }
        for (int iy = 0; iy < reactions_sys_name_vect.size(); iy++)
        {
          std::vector < std::pair < std::string, bool>>
            reactions_sys_name_sub_vect;

          DicesRcDriver status = ParseCSVToArray(
            &reactions_sys_name_sub_vect,
            reactions_sys_name_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }

          unsigned int adv_index = reactions_sys_id_vect.at(iy).second.at(0);

          if (!_allergy_req_command_instance_list.at(ix).second->
            adverse_events[adv_index].reactions.length()) continue;

          for (int iz = 0; iz < reactions_sys_name_sub_vect.size(); iz++)
          {
            _allergy_req_command_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.code_system_pair.code_system_name =
              DDS::String_alloc(ice::MEDIUM_STRING_LEN);
            if (!_allergy_req_command_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.code_system_pair.code_system_name)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
                "for DDS String code_system_name");
              return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
            }

            strncpy(
              _allergy_req_command_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.code_system_pair.code_system_name,
              reactions_sys_name_sub_vect.at(iz).first.c_str(),
              ice::MEDIUM_STRING_LEN);
            _allergy_req_command_instance_list.at(ix).second->adverse_events
              [adv_index].reactions[iz].coded_reaction.
              code_system_pair.code_system_name[
              ice::MEDIUM_STRING_LEN] = '\0';
          }
        }
        for (int iy = 0; iy < reactions_code_vect.size(); iy++)
        {
          std::vector < std::pair < std::string, bool>>
            reactions_code_sub_vect;

          DicesRcDriver status = ParseCSVToArray(
            &reactions_code_sub_vect,
            reactions_code_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }

          unsigned int adv_index = reactions_code_vect.at(iy).second.at(0);

          if (!_allergy_req_command_instance_list.at(ix).second->
            adverse_events[adv_index].reactions.length()) continue;

          for (int iz = 0; iz < reactions_code_sub_vect.size(); iz++)
          {
            _allergy_req_command_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.code =
              DDS::String_alloc(ice::SHORT_STRING_LEN);
            if (!_allergy_req_command_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.code)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
                "for DDS String code");
              return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
            }

            strncpy(
              _allergy_req_command_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.code,
              reactions_code_sub_vect.at(iz).first.c_str(),
              ice::SHORT_STRING_LEN);
            _allergy_req_command_instance_list.at(ix).second->adverse_events
              [adv_index].reactions[iz].coded_reaction.
              code[ice::SHORT_STRING_LEN] = '\0';
          }
        }
        for (int iy = 0; iy < reactions_label_vect.size(); iy++)
        {
          std::vector < std::pair < std::string, bool>>
            reactions_label_sub_vect;

          DicesRcDriver status = ParseCSVToArray(
            &reactions_label_sub_vect,
            reactions_label_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }

          unsigned int adv_index = reactions_code_vect.at(iy).second.at(0);

          if (!_allergy_req_command_instance_list.at(ix).second->
            adverse_events[adv_index].reactions.length()) continue;

          for (int iz = 0; iz < reactions_label_sub_vect.size(); iz++)
          {
            _allergy_req_command_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.label =
              DDS::String_alloc(ice::MEDIUM_STRING_LEN);
            if (!_allergy_req_command_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.label)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
                "for DDS String label");
              return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
            }
            strncpy(
              _allergy_req_command_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              coded_reaction.label,
              reactions_label_sub_vect.at(iz).first.c_str(),
              ice::MEDIUM_STRING_LEN);
            _allergy_req_command_instance_list.at(ix).second->adverse_events
              [adv_index].reactions[iz].coded_reaction.
              label[ice::MEDIUM_STRING_LEN] = '\0';
          }
        }
        for (int iy = 0; iy < reactions_free_txt_vect.size(); iy++)
        {
          std::vector < std::pair < std::string, bool>>
            reactions_free_txt_sub_vect;

          DicesRcDriver status = ParseCSVToArray(
            &reactions_free_txt_sub_vect,
            reactions_free_txt_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }

          unsigned int adv_index = reactions_free_txt_vect.at(iy).second.at(0);

          if (!_allergy_req_command_instance_list.at(ix).second->
            adverse_events[adv_index].reactions.length()) continue;

          for (int iz = 0; iz < reactions_free_txt_sub_vect.size(); iz++)
          {
            _allergy_req_command_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              free_text_reaction =
              DDS::String_alloc(ice::LONGLONG_STRING_LEN);
            if (!_allergy_req_command_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              free_text_reaction)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
                "for DDS String label");
              return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
            }
            strncpy(
              _allergy_req_command_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].
              free_text_reaction,
              reactions_free_txt_sub_vect.at(iz).first.c_str(),
              ice::LONGLONG_STRING_LEN);
            _allergy_req_command_instance_list.at(ix).second->adverse_events
              [adv_index].reactions[iz].free_text_reaction
              [ice::LONGLONG_STRING_LEN] = '\0';
          }
        }
        for (int iy = 0; iy < reactions_severity_vect.size(); iy++)
        {
          std::vector < std::pair < ice::INT32, bool>>
            reactions_severity_sub_vect;

          DicesRcDriver status = ParseCSVToArray(
            &reactions_severity_sub_vect,
            reactions_severity_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }

          unsigned int adv_index = reactions_severity_vect.at(iy).second.at(0);

          if (!_allergy_req_command_instance_list.at(ix).second->
            adverse_events[adv_index].reactions.length()) continue;

          for (int iz = 0; iz < reactions_severity_sub_vect.size(); iz++)
          {
            _allergy_req_command_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].severity.
              coded_severity = static_cast<ice::CodedSeverityType>(
              reactions_severity_sub_vect.at(iz).first);
          }
        }
        for (int iy = 0; iy < reactions_free_txt_severity_vect.size(); iy++)
        {
          std::vector < std::pair < std::string, bool>>
            reactions_free_txt_severity_sub_vect;

          DicesRcDriver status = ParseCSVToArray(
            &reactions_free_txt_severity_sub_vect,
            reactions_free_txt_severity_vect.at(iy).first);
          if (status != DicesRcDriver::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
              DicesRcDriverToString(status));
            return status;
          }

          unsigned int adv_index = reactions_free_txt_severity_vect.at(iy).second.at(0);

          if (!_allergy_req_command_instance_list.at(ix).second->
            adverse_events[adv_index].reactions.length()) continue;

          for (int iz = 0; iz < reactions_free_txt_severity_sub_vect.size(); iz++)
          {
            _allergy_req_command_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].severity.
              free_text_severity =
              DDS::String_alloc(ice::LONGLONG_STRING_LEN);
            if (!_allergy_req_command_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].severity.
              free_text_severity)
            {
              LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
                "for DDS String free_text_severity");
              return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
            }
            strncpy(
              _allergy_req_command_instance_list.at(ix).second->
              adverse_events[adv_index].reactions[iz].severity.
              free_text_severity,
              reactions_free_txt_severity_sub_vect.at(iz).first.c_str(),
              ice::LONGLONG_STRING_LEN);
            _allergy_req_command_instance_list.at(ix).second->adverse_events
              [adv_index].reactions[iz].severity.
              free_text_severity[ice::LONGLONG_STRING_LEN] = '\0';
          }
        }
      }
    }
  }
  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ReadFromPatientMedicationTable()
{
  static const char* sfn = "Parser::ReadFromPatientMedicationTable() ";

  if (_database_connection == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Database is not connected");
    return DicesRcDriver::DATABASE_CONNECTION_FAILURE;
  }

  std::string column_names = kHeaderColumnNames
    + ", " + kTopColumnNames
    + ", " + kPatientMedicationColumnNames;
  pqxx::result table_result;
  try
  {
    pqxx::work database_work(*_database_connection);
    table_result = database_work.exec(
      "SELECT " + column_names + " FROM " + std::string(kTablePatientMedication) + ";");
    database_work.commit();
  }
  catch (const std::exception &ex)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to read the " << kTablePatientMedication
      << " table from the database. " << ex.what());
    return DicesRcDriver::DATABASE_READ_TABLE_FAILURE;
  }

  if (table_result.columns() < kExpectedPatientMedicationTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table result contains "
      << table_result.columns() << " columns, but this function requires "
      << kExpectedPatientMedicationTableColumnCount << " columns to parse successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  try
  {
    _patient_medication_response_instance_list.resize(table_result.size());
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "medication instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  for (int ix = 0; ix < table_result.size(); ix++)
  {
    expr::PatientMedication* medication_instance = expr::PatientMedicationTypeSupport::
      create_data();
    if (!medication_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for "
        "Medication");
      return DicesRcDriver::PATIENT_MEDICATION_INSTANCE_CREATE_FAILURE;
    }
    _patient_medication_response_instance_list.at(ix).second = medication_instance;

    strncpy(
      _patient_medication_response_instance_list.at(ix).second->ice_id,
      table_result[ix][2].as<std::string>("").c_str(),
      ice::MAX_LEN_ICE_ID);
    _patient_medication_response_instance_list.at(ix).second->ice_id[
      ice::MAX_LEN_ICE_ID] = '\0';

    _patient_medication_response_instance_list.at(ix).second->handle =
      table_result[ix][3].as<ice::HANDLE>(0);

    _patient_medication_response_instance_list.at(ix).second->parent_handle =
      table_result[ix][4].as<ice::HANDLE>(0);

    _patient_medication_response_instance_list.at(ix).second->source_timestamp.
      seconds = table_result[ix][5].as<long>(0);
    _patient_medication_response_instance_list.at(ix).second->source_timestamp.
      nanoseconds = table_result[ix][6].as<long>(0);

    strncpy(
      _patient_medication_response_instance_list.at(ix).second->
      patient_identification.given_name,
      table_result[ix][7].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _patient_medication_response_instance_list.at(ix).second->
      patient_identification.given_name[ice::SHORT_STRING_LEN] = '\0';
    strncpy(
      _patient_medication_response_instance_list.at(ix).second->
      patient_identification.family_name,
      table_result[ix][8].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _patient_medication_response_instance_list.at(ix).second->
      patient_identification.family_name[ice::SHORT_STRING_LEN] = '\0';
    strncpy(
      _patient_medication_response_instance_list.at(ix).second->
      patient_identification.middle_name,
      table_result[ix][9].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _patient_medication_response_instance_list.at(ix).second->
      patient_identification.middle_name[ice::SHORT_STRING_LEN] = '\0';

    if (table_result[ix][10].is_null()
      && table_result[ix][11].is_null()
      && table_result[ix][12].is_null()
      && table_result[ix][13].is_null())
    {
      _patient_medication_response_instance_list.at(ix).second->
        patient_identification.date_of_birth = nullptr;
    }
    else
    {
      _patient_medication_response_instance_list.at(ix).second->
        patient_identification.date_of_birth = reinterpret_cast<ice::Date*>(
        DDS::Heap_malloc(sizeof(ice::Date)));
      if (!_patient_medication_response_instance_list.at(ix).second->
        patient_identification.date_of_birth)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::Date");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][10].as<std::string>(""),
        &_patient_medication_response_instance_list.at(ix).second->
        patient_identification.date_of_birth->century);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][11].as<std::string>(""),
        &_patient_medication_response_instance_list.at(ix).second->
        patient_identification.date_of_birth->year);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][12].as<std::string>(""),
        &_patient_medication_response_instance_list.at(ix).second->
        patient_identification.date_of_birth->month);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][13].as<std::string>(""),
        &_patient_medication_response_instance_list.at(ix).second->
        patient_identification.date_of_birth->day);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
    }
    strncpy(
      _patient_medication_response_instance_list.at(ix).second->
      patient_identification.patient_id,
      table_result[ix][14].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _patient_medication_response_instance_list.at(ix).second->
      patient_identification.patient_id[ice::MEDIUM_STRING_LEN] = '\0';
    strncpy(
      _patient_medication_response_instance_list.at(ix).second->
      patient_identification.patient_id_provenance,
      table_result[ix][15].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _patient_medication_response_instance_list.at(ix).second->
      patient_identification.patient_id_provenance[ice::MEDIUM_STRING_LEN] =
      '\0';
    _patient_medication_response_instance_list.at(ix).second->
      patient_identification.verified = static_cast<ice::BOOL>(
      table_result[ix][16].as<bool>(false));
    _patient_medication_response_instance_list.at(ix).second->
      patient_identification.pat_admit_state = static_cast<ice::PatAdmitState>(
      table_result[ix][17].as<int>(0));
    _patient_medication_response_instance_list.at(ix).second->
      patient_identification.pat_episode_id = table_result[ix][18].
      as<ice::PatEpisode>(0);
    _patient_medication_response_instance_list.at(ix).second->
      patient_identification.episode_start.seconds = table_result[ix][19].
      as<long>(0);
    _patient_medication_response_instance_list.at(ix).second->
      patient_identification.episode_start.nanoseconds = table_result[ix][20].
      as<long>(0);

    _patient_medication_response_instance_list.at(ix).second->
      medication_count = table_result[ix][21].as<ice::INTU16>(0);

    // MedicationList
    if (!table_result[ix][22].is_null()
      && !table_result[ix][23].is_null())
    {
      std::string medication_name_str = table_result[ix][22].
        as<std::string>("");
      std::string medication_dose_str = table_result[ix][23].
        as<std::string>("");

      std::vector < std::pair < std::string, bool>>
        medication_name_vect;
      std::vector < std::pair < std::string, bool>>
        medication_dose_vect;

      DicesRcDriver status = ParseCSVToArray(
        &medication_name_vect,
        medication_name_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &medication_dose_vect,
        medication_dose_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }

      // Make sure we have the same number of names and doses in CSV
      if (medication_dose_vect.size() != medication_name_vect.size())
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "To set expr::MedicationList "
          "sequence, attributes must have the same number of elements.");
        return DicesRcDriver::FAIL;
      }

      if (!_patient_medication_response_instance_list.at(ix).second->
        medication_list.ensure_length(
        medication_name_vect.size(),
        medication_name_vect.size()))
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
          "expr::MedicationList sequence. Length: "
          << medication_name_vect.size());
        return DicesRcDriver::FAIL;
      }

      for (int iy = 0; iy < medication_name_vect.size(); iy++)
      {
        strncpy(
          _patient_medication_response_instance_list.at(ix).second->
          medication_list[iy].name,
          medication_name_vect.at(iy).first.c_str(),
          ice::LONG_STRING_LEN);
        _patient_medication_response_instance_list.at(ix).second->
          medication_list[iy].name[ice::LONG_STRING_LEN] = '\0';
      }
      for (int iy = 0; iy < medication_dose_vect.size(); iy++)
      {
        strncpy(
          _patient_medication_response_instance_list.at(ix).second->
          medication_list[iy].dose,
          medication_dose_vect.at(iy).first.c_str(),
          ice::LONG_STRING_LEN);
        _patient_medication_response_instance_list.at(ix).second->
          medication_list[iy].dose[ice::LONG_STRING_LEN] = '\0';
      }
    }
  }
  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ReadFromPatientMedicationReqTable()
{
  static const char* sfn = "Parser::ReadFromPatientMedicationReqTable() ";

  if (_database_connection == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Database is not connected");
    return DicesRcDriver::DATABASE_CONNECTION_FAILURE;
  }

  std::string column_names = kHeaderColumnNames
    + ", " + kTopColumnNames
    + ", " + kPatientMedicationColumnNames;
  pqxx::result table_result;
  try
  {
    pqxx::work database_work(*_database_connection);
    table_result = database_work.exec(
      "SELECT " + column_names + " FROM " + std::string(kTablePatientMedicationReq) + ";");
    database_work.commit();
  }
  catch (const std::exception &ex)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to read the " << kTablePatientMedicationReq
      << " table from the database. " << ex.what());
    return DicesRcDriver::DATABASE_READ_TABLE_FAILURE;
  }

  if (table_result.columns() < kExpectedPatientMedicationTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table result contains "
      << table_result.columns() << " columns, but this function requires "
      << kExpectedPatientMedicationTableColumnCount << " columns to parse successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  try
  {
    _patient_medication_req_command_instance_list.resize(table_result.size());
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "medication req instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  for (int ix = 0; ix < table_result.size(); ix++)
  {
    expr::PatientMedication* medication_instance = expr::PatientMedicationTypeSupport::
      create_data();
    if (!medication_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for "
        "Medication");
      return DicesRcDriver::PATIENT_MEDICATION_INSTANCE_CREATE_FAILURE;
    }
    _patient_medication_req_command_instance_list.at(ix).second = medication_instance;

    strncpy(
      _patient_medication_req_command_instance_list.at(ix).second->ice_id,
      table_result[ix][2].as<std::string>("").c_str(),
      ice::MAX_LEN_ICE_ID);
    _patient_medication_req_command_instance_list.at(ix).second->ice_id[
      ice::MAX_LEN_ICE_ID] = '\0';

    _patient_medication_req_command_instance_list.at(ix).second->handle =
      table_result[ix][3].as<ice::HANDLE>(0);

    _patient_medication_req_command_instance_list.at(ix).second->parent_handle =
      table_result[ix][4].as<ice::HANDLE>(0);

    _patient_medication_req_command_instance_list.at(ix).second->source_timestamp.
      seconds = table_result[ix][5].as<long>(0);
    _patient_medication_req_command_instance_list.at(ix).second->source_timestamp.
      nanoseconds = table_result[ix][6].as<long>(0);

    strncpy(
      _patient_medication_req_command_instance_list.at(ix).second->
      patient_identification.given_name,
      table_result[ix][7].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _patient_medication_req_command_instance_list.at(ix).second->
      patient_identification.given_name[ice::SHORT_STRING_LEN] = '\0';
    strncpy(
      _patient_medication_req_command_instance_list.at(ix).second->
      patient_identification.family_name,
      table_result[ix][8].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _patient_medication_req_command_instance_list.at(ix).second->
      patient_identification.family_name[ice::SHORT_STRING_LEN] = '\0';
    strncpy(
      _patient_medication_req_command_instance_list.at(ix).second->
      patient_identification.middle_name,
      table_result[ix][9].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _patient_medication_req_command_instance_list.at(ix).second->
      patient_identification.middle_name[ice::SHORT_STRING_LEN] = '\0';

    if (table_result[ix][10].is_null()
      && table_result[ix][11].is_null()
      && table_result[ix][12].is_null()
      && table_result[ix][13].is_null())
    {
      _patient_medication_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth = nullptr;
    }
    else
    {
      _patient_medication_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth = reinterpret_cast<ice::Date*>(
        DDS::Heap_malloc(sizeof(ice::Date)));
      if (!_patient_medication_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::Date");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][10].as<std::string>(""),
        &_patient_medication_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth->century);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][11].as<std::string>(""),
        &_patient_medication_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth->year);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][12].as<std::string>(""),
        &_patient_medication_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth->month);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][13].as<std::string>(""),
        &_patient_medication_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth->day);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
    }
    strncpy(
      _patient_medication_req_command_instance_list.at(ix).second->
      patient_identification.patient_id,
      table_result[ix][14].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _patient_medication_req_command_instance_list.at(ix).second->
      patient_identification.patient_id[ice::MEDIUM_STRING_LEN] = '\0';
    strncpy(
      _patient_medication_req_command_instance_list.at(ix).second->
      patient_identification.patient_id_provenance,
      table_result[ix][15].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _patient_medication_req_command_instance_list.at(ix).second->
      patient_identification.patient_id_provenance[ice::MEDIUM_STRING_LEN] =
      '\0';
    _patient_medication_req_command_instance_list.at(ix).second->
      patient_identification.verified = static_cast<ice::BOOL>(
      table_result[ix][16].as<bool>(false));
    _patient_medication_req_command_instance_list.at(ix).second->
      patient_identification.pat_admit_state = static_cast<ice::PatAdmitState>(
      table_result[ix][17].as<int>(0));
    _patient_medication_req_command_instance_list.at(ix).second->
      patient_identification.pat_episode_id = table_result[ix][18].
      as<ice::PatEpisode>(0);
    _patient_medication_req_command_instance_list.at(ix).second->
      patient_identification.episode_start.seconds = table_result[ix][19].
      as<long>(0);
    _patient_medication_req_command_instance_list.at(ix).second->
      patient_identification.episode_start.nanoseconds = table_result[ix][20].
      as<long>(0);

    _patient_medication_req_command_instance_list.at(ix).second->
      medication_count = table_result[ix][21].as<ice::INTU16>(0);

    // MedicationList
    if (!table_result[ix][22].is_null()
      && !table_result[ix][23].is_null())
    {
      std::string medication_name_str = table_result[ix][22].
        as<std::string>("");
      std::string medication_dose_str = table_result[ix][23].
        as<std::string>("");

      std::vector < std::pair < std::string, bool>>
        medication_name_vect;
      std::vector < std::pair < std::string, bool>>
        medication_dose_vect;

      DicesRcDriver status = ParseCSVToArray(
        &medication_name_vect,
        medication_name_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ParseCSVToArray(
        &medication_dose_vect,
        medication_dose_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }

      // Make sure we have the same number of names and doses in CSV
      if (medication_dose_vect.size() != medication_name_vect.size())
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "To set expr::MedicationList "
          "sequence, attributes must have the same number of elements.");
        return DicesRcDriver::FAIL;
      }

      if (!_patient_medication_req_command_instance_list.at(ix).second->
        medication_list.ensure_length(
        medication_name_vect.size(),
        medication_name_vect.size()))
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
          "expr::MedicationList sequence. Length: "
          << medication_name_vect.size());
        return DicesRcDriver::FAIL;
      }

      for (int iy = 0; iy < medication_name_vect.size(); iy++)
      {
        strncpy(
          _patient_medication_req_command_instance_list.at(ix).second->
          medication_list[iy].name,
          medication_name_vect.at(iy).first.c_str(),
          ice::LONG_STRING_LEN);
        _patient_medication_req_command_instance_list.at(ix).second->
          medication_list[iy].name[ice::LONG_STRING_LEN] = '\0';
      }
      for (int iy = 0; iy < medication_dose_vect.size(); iy++)
      {
        strncpy(
          _patient_medication_req_command_instance_list.at(ix).second->
          medication_list[iy].dose,
          medication_dose_vect.at(iy).first.c_str(),
          ice::LONG_STRING_LEN);
        _patient_medication_req_command_instance_list.at(ix).second->
          medication_list[iy].dose[ice::LONG_STRING_LEN] = '\0';
      }
    }
  }
  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ReadFromDxHistoryTable()
{
  static const char* sfn = "Parser::ReadFromDxHistoryTable() ";

  if (_database_connection == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Database is not connected");
    return DicesRcDriver::DATABASE_CONNECTION_FAILURE;
  }

  std::string column_names = kHeaderColumnNames
    + ", " + kTopColumnNames
    + ", " + kDxHistoryColumnNames;
  pqxx::result table_result;
  try
  {
    pqxx::work database_work(*_database_connection);
    table_result = database_work.exec(
      "SELECT " + column_names + " FROM " + std::string(kTableDxHistory) + ";");
    database_work.commit();
  }
  catch (const std::exception &ex)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to read the " << kTableDxHistory
      << " table from the database. " << ex.what());
    return DicesRcDriver::DATABASE_READ_TABLE_FAILURE;
  }

  if (table_result.columns() < kExpectedDxHistoryTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table result contains "
      << table_result.columns() << " columns, but this function requires "
      << kExpectedDxHistoryTableColumnCount << " columns to parse successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  try
  {
    _dxhistory_response_instance_list.resize(table_result.size());
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "dx history instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  for (int ix = 0; ix < table_result.size(); ix++)
  {
    expr::DxHistory* dx_history_instance = expr::DxHistoryTypeSupport::
      create_data();
    if (!dx_history_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for "
        "DxHistory");
      return DicesRcDriver::DXHISTORY_INSTANCE_CREATE_FAILURE;
    }
    _dxhistory_response_instance_list.at(ix).second = dx_history_instance;

    strncpy(
      _dxhistory_response_instance_list.at(ix).second->ice_id,
      table_result[ix][2].as<std::string>("").c_str(),
      ice::MAX_LEN_ICE_ID);
    _dxhistory_response_instance_list.at(ix).second->ice_id[
      ice::MAX_LEN_ICE_ID] = '\0';

    _dxhistory_response_instance_list.at(ix).second->handle =
      table_result[ix][3].as<ice::HANDLE>(0);

    _dxhistory_response_instance_list.at(ix).second->parent_handle =
      table_result[ix][4].as<ice::HANDLE>(0);

    _dxhistory_response_instance_list.at(ix).second->source_timestamp.
      seconds = table_result[ix][5].as<long>(0);
    _dxhistory_response_instance_list.at(ix).second->source_timestamp.
      nanoseconds = table_result[ix][6].as<long>(0);

    strncpy(
      _dxhistory_response_instance_list.at(ix).second->health_problem,
      table_result[ix][7].as<std::string>("").c_str(),
      ice::LONG_STRING_LEN);
    _dxhistory_response_instance_list.at(ix).second->health_problem[
      ice::LONG_STRING_LEN] = '\0';
    strncpy(
      _dxhistory_response_instance_list.at(ix).second->recent_procedure,
      table_result[ix][8].as<std::string>("").c_str(),
      ice::LONG_STRING_LEN);
    _dxhistory_response_instance_list.at(ix).second->recent_procedure[
      ice::LONG_STRING_LEN] = '\0';

    strncpy(
      _dxhistory_response_instance_list.at(ix).second->
      patient_identification.given_name,
      table_result[ix][9].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _dxhistory_response_instance_list.at(ix).second->
      patient_identification.given_name[ice::SHORT_STRING_LEN] = '\0';
    strncpy(
      _dxhistory_response_instance_list.at(ix).second->
      patient_identification.family_name,
      table_result[ix][10].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _dxhistory_response_instance_list.at(ix).second->
      patient_identification.family_name[ice::SHORT_STRING_LEN] = '\0';
    strncpy(
      _dxhistory_response_instance_list.at(ix).second->
      patient_identification.middle_name,
      table_result[ix][11].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _dxhistory_response_instance_list.at(ix).second->
      patient_identification.middle_name[ice::SHORT_STRING_LEN] = '\0';

    if (table_result[ix][12].is_null()
      && table_result[ix][13].is_null()
      && table_result[ix][14].is_null()
      && table_result[ix][15].is_null())
    {
      _dxhistory_response_instance_list.at(ix).second->
        patient_identification.date_of_birth = nullptr;
    }
    else
    {
      _dxhistory_response_instance_list.at(ix).second->
        patient_identification.date_of_birth = reinterpret_cast<ice::Date*>(
        DDS::Heap_malloc(sizeof(ice::Date)));
      if (!_dxhistory_response_instance_list.at(ix).second->
        patient_identification.date_of_birth)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::Date");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][12].as<std::string>(""),
        &_dxhistory_response_instance_list.at(ix).second->
        patient_identification.date_of_birth->century);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][13].as<std::string>(""),
        &_dxhistory_response_instance_list.at(ix).second->
        patient_identification.date_of_birth->year);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][14].as<std::string>(""),
        &_dxhistory_response_instance_list.at(ix).second->
        patient_identification.date_of_birth->month);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][15].as<std::string>(""),
        &_dxhistory_response_instance_list.at(ix).second->
        patient_identification.date_of_birth->day);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
    }
    strncpy(
      _dxhistory_response_instance_list.at(ix).second->
      patient_identification.patient_id,
      table_result[ix][16].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _dxhistory_response_instance_list.at(ix).second->
      patient_identification.patient_id[ice::MEDIUM_STRING_LEN] = '\0';
    strncpy(
      _dxhistory_response_instance_list.at(ix).second->
      patient_identification.patient_id_provenance,
      table_result[ix][17].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _dxhistory_response_instance_list.at(ix).second->
      patient_identification.patient_id_provenance[ice::MEDIUM_STRING_LEN] =
      '\0';
    _dxhistory_response_instance_list.at(ix).second->
      patient_identification.verified = static_cast<ice::BOOL>(
      table_result[ix][18].as<bool>(false));
    _dxhistory_response_instance_list.at(ix).second->
      patient_identification.pat_admit_state = static_cast<ice::PatAdmitState>(
      table_result[ix][19].as<int>(0));
    _dxhistory_response_instance_list.at(ix).second->
      patient_identification.pat_episode_id = table_result[ix][20].
      as<ice::PatEpisode>(0);
    _dxhistory_response_instance_list.at(ix).second->
      patient_identification.episode_start.seconds = table_result[ix][21].
      as<long>(0);
    _dxhistory_response_instance_list.at(ix).second->
      patient_identification.episode_start.nanoseconds = table_result[ix][22].
      as<long>(0);

    _dxhistory_response_instance_list.at(ix).second->problem_count =
      table_result[ix][23].as<ice::INTU16>(0);

    if (!table_result[ix][24].is_null())
    {
      std::string problem_list_str = table_result[ix][24].as<std::string>("");
      std::vector < std::pair < std::string, bool>> problem_list_vect;

      DicesRcDriver status = ParseCSVToArray(
        &problem_list_vect,
        problem_list_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }

      if (!_dxhistory_response_instance_list.at(ix).second->
        problem_list.ensure_length(
        problem_list_vect.size(),
        problem_list_vect.size()))
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
          "sequence of strings. Length: "
          << problem_list_vect.size());
        return DicesRcDriver::FAIL;
      }

      for (int iy = 0; iy < problem_list_vect.size(); iy++)
      {
        strncpy(
          _dxhistory_response_instance_list.at(ix).second->
          problem_list[iy],
          problem_list_vect.at(iy).first.c_str(),
          ice::LONG_STRING_LEN);
        _dxhistory_response_instance_list.at(ix).second->
          problem_list[iy][ice::LONG_STRING_LEN] = '\0';
      }
    }

    strncpy(
      _dxhistory_response_instance_list.at(ix).second->
      recent_procedures,
      table_result[ix][25].as<std::string>("").c_str(),
      ice::LONG_STRING_LEN);
    _dxhistory_response_instance_list.at(ix).second->
      recent_procedures[ice::LONG_STRING_LEN] = '\0';
  }
  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ReadFromDxHistoryReqTable()
{
  static const char* sfn = "Parser::ReadFromDxHistoryReqTable() ";

  if (_database_connection == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Database is not connected");
    return DicesRcDriver::DATABASE_CONNECTION_FAILURE;
  }

  std::string column_names = kHeaderColumnNames
    + ", " + kTopColumnNames
    + ", " + kDxHistoryColumnNames;
  pqxx::result table_result;
  try
  {
    pqxx::work database_work(*_database_connection);
    table_result = database_work.exec(
      "SELECT " + column_names + " FROM " + std::string(kTableDxHistoryReq) + ";");
    database_work.commit();
  }
  catch (const std::exception &ex)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to read the " << kTableDxHistoryReq
      << " table from the database. " << ex.what());
    return DicesRcDriver::DATABASE_READ_TABLE_FAILURE;
  }

  if (table_result.columns() < kExpectedDxHistoryTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table result contains "
      << table_result.columns() << " columns, but this function requires "
      << kExpectedDxHistoryTableColumnCount << " columns to parse successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  try
  {
    _dxhistory_req_command_instance_list.resize(table_result.size());
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "dx history instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  for (int ix = 0; ix < table_result.size(); ix++)
  {
    expr::DxHistory* dx_history_instance = expr::DxHistoryTypeSupport::
      create_data();
    if (!dx_history_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for "
        "DxHistory");
      return DicesRcDriver::DXHISTORY_INSTANCE_CREATE_FAILURE;
    }
    _dxhistory_req_command_instance_list.at(ix).second = dx_history_instance;

    strncpy(
      _dxhistory_req_command_instance_list.at(ix).second->ice_id,
      table_result[ix][2].as<std::string>("").c_str(),
      ice::MAX_LEN_ICE_ID);
    _dxhistory_req_command_instance_list.at(ix).second->ice_id[
      ice::MAX_LEN_ICE_ID] = '\0';

    _dxhistory_req_command_instance_list.at(ix).second->handle =
      table_result[ix][3].as<ice::HANDLE>(0);

    _dxhistory_req_command_instance_list.at(ix).second->parent_handle =
      table_result[ix][4].as<ice::HANDLE>(0);

    _dxhistory_req_command_instance_list.at(ix).second->source_timestamp.
      seconds = table_result[ix][5].as<long>(0);
    _dxhistory_req_command_instance_list.at(ix).second->source_timestamp.
      nanoseconds = table_result[ix][6].as<long>(0);

    strncpy(
      _dxhistory_req_command_instance_list.at(ix).second->health_problem,
      table_result[ix][7].as<std::string>("").c_str(),
      ice::LONG_STRING_LEN);
    _dxhistory_req_command_instance_list.at(ix).second->health_problem[
      ice::LONG_STRING_LEN] = '\0';
    strncpy(
      _dxhistory_req_command_instance_list.at(ix).second->recent_procedure,
      table_result[ix][8].as<std::string>("").c_str(),
      ice::LONG_STRING_LEN);
    _dxhistory_req_command_instance_list.at(ix).second->recent_procedure[
      ice::LONG_STRING_LEN] = '\0';

    strncpy(
      _dxhistory_req_command_instance_list.at(ix).second->
      patient_identification.given_name,
      table_result[ix][9].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _dxhistory_req_command_instance_list.at(ix).second->
      patient_identification.given_name[ice::SHORT_STRING_LEN] = '\0';
    strncpy(
      _dxhistory_req_command_instance_list.at(ix).second->
      patient_identification.family_name,
      table_result[ix][10].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _dxhistory_req_command_instance_list.at(ix).second->
      patient_identification.family_name[ice::SHORT_STRING_LEN] = '\0';
    strncpy(
      _dxhistory_req_command_instance_list.at(ix).second->
      patient_identification.middle_name,
      table_result[ix][11].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _dxhistory_req_command_instance_list.at(ix).second->
      patient_identification.middle_name[ice::SHORT_STRING_LEN] = '\0';

    if (table_result[ix][12].is_null()
      && table_result[ix][13].is_null()
      && table_result[ix][14].is_null()
      && table_result[ix][15].is_null())
    {
      _dxhistory_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth = nullptr;
    }
    else
    {
      _dxhistory_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth = reinterpret_cast<ice::Date*>(
        DDS::Heap_malloc(sizeof(ice::Date)));
      if (!_dxhistory_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::Date");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][12].as<std::string>(""),
        &_dxhistory_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth->century);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][13].as<std::string>(""),
        &_dxhistory_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth->year);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][14].as<std::string>(""),
        &_dxhistory_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth->month);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][15].as<std::string>(""),
        &_dxhistory_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth->day);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
    }
    strncpy(
      _dxhistory_req_command_instance_list.at(ix).second->
      patient_identification.patient_id,
      table_result[ix][16].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _dxhistory_req_command_instance_list.at(ix).second->
      patient_identification.patient_id[ice::MEDIUM_STRING_LEN] = '\0';
    strncpy(
      _dxhistory_req_command_instance_list.at(ix).second->
      patient_identification.patient_id_provenance,
      table_result[ix][17].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _dxhistory_req_command_instance_list.at(ix).second->
      patient_identification.patient_id_provenance[ice::MEDIUM_STRING_LEN] =
      '\0';
    _dxhistory_req_command_instance_list.at(ix).second->
      patient_identification.verified = static_cast<ice::BOOL>(
      table_result[ix][18].as<bool>(false));
    _dxhistory_req_command_instance_list.at(ix).second->
      patient_identification.pat_admit_state = static_cast<ice::PatAdmitState>(
      table_result[ix][19].as<int>(0));
    _dxhistory_req_command_instance_list.at(ix).second->
      patient_identification.pat_episode_id = table_result[ix][20].
      as<ice::PatEpisode>(0);
    _dxhistory_req_command_instance_list.at(ix).second->
      patient_identification.episode_start.seconds = table_result[ix][21].
      as<long>(0);
    _dxhistory_req_command_instance_list.at(ix).second->
      patient_identification.episode_start.nanoseconds = table_result[ix][22].
      as<long>(0);

    _dxhistory_req_command_instance_list.at(ix).second->problem_count =
      table_result[ix][23].as<ice::INTU16>(0);

    if (!table_result[ix][24].is_null())
    {
      std::string problem_list_str = table_result[ix][24].as<std::string>("");
      std::vector < std::pair < std::string, bool>> problem_list_vect;

      DicesRcDriver status = ParseCSVToArray(
        &problem_list_vect,
        problem_list_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }

      if (!_dxhistory_req_command_instance_list.at(ix).second->
        problem_list.ensure_length(
        problem_list_vect.size(),
        problem_list_vect.size()))
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
          "sequence of strings. Length: "
          << problem_list_vect.size());
        return DicesRcDriver::FAIL;
      }

      for (int iy = 0; iy < problem_list_vect.size(); iy++)
      {
        strncpy(
          _dxhistory_req_command_instance_list.at(ix).second->
          problem_list[iy],
          problem_list_vect.at(iy).first.c_str(),
          ice::LONG_STRING_LEN);
        _dxhistory_req_command_instance_list.at(ix).second->
          problem_list[iy][ice::LONG_STRING_LEN] = '\0';
      }
    }

    strncpy(
      _dxhistory_req_command_instance_list.at(ix).second->
      recent_procedures,
      table_result[ix][25].as<std::string>("").c_str(),
      ice::LONG_STRING_LEN);
    _dxhistory_req_command_instance_list.at(ix).second->
      recent_procedures[ice::LONG_STRING_LEN] = '\0';
  }
  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ReadFromDiagnosisTable()
{
  static const char* sfn = "Parser::ReadFromDiagnosisTable() ";

  if (_database_connection == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Database is not connected");
    return DicesRcDriver::DATABASE_CONNECTION_FAILURE;
  }

  std::string column_names = kHeaderColumnNames
    + ", " + kTopColumnNames
    + ", " + kDiagnosisColumnNames;
  pqxx::result table_result;
  try
  {
    pqxx::work database_work(*_database_connection);
    table_result = database_work.exec(
      "SELECT " + column_names + " FROM " + std::string(kTableDiagnosis) + ";");
    database_work.commit();
  }
  catch (const std::exception &ex)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to read the " << kTableDiagnosis
      << " table from the database. " << ex.what());
    return DicesRcDriver::DATABASE_READ_TABLE_FAILURE;
  }

  if (table_result.columns() < kExpectedDiagnosisTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table result contains "
      << table_result.columns() << " columns, but this function requires "
      << kExpectedDiagnosisTableColumnCount << " columns to parse successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  try
  {
    _diagnosis_response_instance_list.resize(table_result.size());
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "diagnosis instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  for (int ix = 0; ix < table_result.size(); ix++)
  {
    expr::Diagnosis* diagnosis_instance = expr::DiagnosisTypeSupport::
      create_data();
    if (!diagnosis_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for "
        "Diagnosis");
      return DicesRcDriver::DIAGNOSIS_INSTANCE_CREATE_FAILURE;
    }
    _diagnosis_response_instance_list.at(ix).second = diagnosis_instance;

    strncpy(
      _diagnosis_response_instance_list.at(ix).second->ice_id,
      table_result[ix][2].as<std::string>("").c_str(),
      ice::MAX_LEN_ICE_ID);
    _diagnosis_response_instance_list.at(ix).second->ice_id[
      ice::MAX_LEN_ICE_ID] = '\0';

    _diagnosis_response_instance_list.at(ix).second->handle =
      table_result[ix][3].as<ice::HANDLE>(0);

    _diagnosis_response_instance_list.at(ix).second->parent_handle =
      table_result[ix][4].as<ice::HANDLE>(0);

    _diagnosis_response_instance_list.at(ix).second->source_timestamp.
      seconds = table_result[ix][5].as<long>(0);
    _diagnosis_response_instance_list.at(ix).second->source_timestamp.
      nanoseconds = table_result[ix][6].as<long>(0);

    strncpy(
      _diagnosis_response_instance_list.at(ix).second->diagnosis,
      table_result[ix][7].as<std::string>("").c_str(),
      ice::LONG_STRING_LEN);
    _diagnosis_response_instance_list.at(ix).second->diagnosis[
      ice::LONG_STRING_LEN] = '\0';
    if (!table_result[ix][8].is_null())
    {
      std::string procedure_list_str = table_result[ix][8].as<std::string>("");
      std::vector < std::pair < std::string, bool>> procedure_list_vect;

      DicesRcDriver status = ParseCSVToArray(
        &procedure_list_vect,
        procedure_list_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }

      if (!_diagnosis_response_instance_list.at(ix).second->
        procedure_list.ensure_length(
        procedure_list_vect.size(),
        procedure_list_vect.size()))
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
          "sequence of strings. Length: "
          << procedure_list_vect.size());
        return DicesRcDriver::FAIL;
      }

      for (int iy = 0; iy < procedure_list_vect.size(); iy++)
      {
        strncpy(
          _diagnosis_response_instance_list.at(ix).second->
          procedure_list[iy],
          procedure_list_vect.at(iy).first.c_str(),
          ice::LONG_STRING_LEN);
        _diagnosis_response_instance_list.at(ix).second->
          procedure_list[iy][ice::LONG_STRING_LEN] = '\0';
      }
    }
    strncpy(
      _diagnosis_response_instance_list.at(ix).second->physician,
      table_result[ix][9].as<std::string>("").c_str(),
      ice::LONG_STRING_LEN);
    _diagnosis_response_instance_list.at(ix).second->physician[
      ice::LONG_STRING_LEN] = '\0';

    strncpy(
      _diagnosis_response_instance_list.at(ix).second->
      patient_identification.given_name,
      table_result[ix][10].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _diagnosis_response_instance_list.at(ix).second->
      patient_identification.given_name[ice::SHORT_STRING_LEN] = '\0';
    strncpy(
      _diagnosis_response_instance_list.at(ix).second->
      patient_identification.family_name,
      table_result[ix][11].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _diagnosis_response_instance_list.at(ix).second->
      patient_identification.family_name[ice::SHORT_STRING_LEN] = '\0';
    strncpy(
      _diagnosis_response_instance_list.at(ix).second->
      patient_identification.middle_name,
      table_result[ix][12].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _diagnosis_response_instance_list.at(ix).second->
      patient_identification.middle_name[ice::SHORT_STRING_LEN] = '\0';

    if (table_result[ix][13].is_null()
      && table_result[ix][14].is_null()
      && table_result[ix][15].is_null()
      && table_result[ix][16].is_null())
    {
      _diagnosis_response_instance_list.at(ix).second->
        patient_identification.date_of_birth = nullptr;
    }
    else
    {
      _diagnosis_response_instance_list.at(ix).second->
        patient_identification.date_of_birth = reinterpret_cast<ice::Date*>(
        DDS::Heap_malloc(sizeof(ice::Date)));
      if (!_diagnosis_response_instance_list.at(ix).second->
        patient_identification.date_of_birth)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::Date");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][13].as<std::string>(""),
        &_diagnosis_response_instance_list.at(ix).second->
        patient_identification.date_of_birth->century);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][14].as<std::string>(""),
        &_diagnosis_response_instance_list.at(ix).second->
        patient_identification.date_of_birth->year);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][15].as<std::string>(""),
        &_diagnosis_response_instance_list.at(ix).second->
        patient_identification.date_of_birth->month);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][16].as<std::string>(""),
        &_diagnosis_response_instance_list.at(ix).second->
        patient_identification.date_of_birth->day);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
    }
    strncpy(
      _diagnosis_response_instance_list.at(ix).second->
      patient_identification.patient_id,
      table_result[ix][17].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _diagnosis_response_instance_list.at(ix).second->
      patient_identification.patient_id[ice::MEDIUM_STRING_LEN] = '\0';
    strncpy(
      _diagnosis_response_instance_list.at(ix).second->
      patient_identification.patient_id_provenance,
      table_result[ix][18].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _diagnosis_response_instance_list.at(ix).second->
      patient_identification.patient_id_provenance[ice::MEDIUM_STRING_LEN] =
      '\0';
    _diagnosis_response_instance_list.at(ix).second->
      patient_identification.verified = static_cast<ice::BOOL>(
      table_result[ix][19].as<bool>(false));
    _diagnosis_response_instance_list.at(ix).second->
      patient_identification.pat_admit_state = static_cast<ice::PatAdmitState>(
      table_result[ix][20].as<int>(0));
    _diagnosis_response_instance_list.at(ix).second->
      patient_identification.pat_episode_id = table_result[ix][21].
      as<ice::PatEpisode>(0);
    _diagnosis_response_instance_list.at(ix).second->
      patient_identification.episode_start.seconds = table_result[ix][22].
      as<long>(0);
    _diagnosis_response_instance_list.at(ix).second->
      patient_identification.episode_start.nanoseconds = table_result[ix][23].
      as<long>(0);
  }
  return DicesRcDriver::OK;
}

DicesRcDriver Parser::ReadFromDiagnosisReqTable()
{
  static const char* sfn = "Parser::ReadFromDiagnosisReqTable() ";

  if (_database_connection == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Database is not connected");
    return DicesRcDriver::DATABASE_CONNECTION_FAILURE;
  }

  std::string column_names = kHeaderColumnNames
    + ", " + kTopColumnNames
    + ", " + kDiagnosisColumnNames;
  pqxx::result table_result;
  try
  {
    pqxx::work database_work(*_database_connection);
    table_result = database_work.exec(
      "SELECT " + column_names + " FROM " + std::string(kTableDiagnosisReq) + ";");
    database_work.commit();
  }
  catch (const std::exception &ex)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to read the " << kTableDiagnosisReq
      << " table from the database. " << ex.what());
    return DicesRcDriver::DATABASE_READ_TABLE_FAILURE;
  }

  if (table_result.columns() < kExpectedDiagnosisTableColumnCount)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "The table result contains "
      << table_result.columns() << " columns, but this function requires "
      << kExpectedDiagnosisTableColumnCount << " columns to parse successfully.");
    return DicesRcDriver::DATABASE_NOT_ENOUGH_TABLE_COLUMNS_FAILURE;
  }

  try
  {
    _diagnosis_req_command_instance_list.resize(table_result.size());
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "diagnosis instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }

  for (int ix = 0; ix < table_result.size(); ix++)
  {
    expr::Diagnosis* diagnosis_instance = expr::DiagnosisTypeSupport::
      create_data();
    if (!diagnosis_instance)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create_data() for "
        "Diagnosis");
      return DicesRcDriver::DIAGNOSIS_INSTANCE_CREATE_FAILURE;
    }
    _diagnosis_req_command_instance_list.at(ix).second = diagnosis_instance;

    strncpy(
      _diagnosis_req_command_instance_list.at(ix).second->ice_id,
      table_result[ix][2].as<std::string>("").c_str(),
      ice::MAX_LEN_ICE_ID);
    _diagnosis_req_command_instance_list.at(ix).second->ice_id[
      ice::MAX_LEN_ICE_ID] = '\0';

    _diagnosis_req_command_instance_list.at(ix).second->handle =
      table_result[ix][3].as<ice::HANDLE>(0);

    _diagnosis_req_command_instance_list.at(ix).second->parent_handle =
      table_result[ix][4].as<ice::HANDLE>(0);

    _diagnosis_req_command_instance_list.at(ix).second->source_timestamp.
      seconds = table_result[ix][5].as<long>(0);
    _diagnosis_req_command_instance_list.at(ix).second->source_timestamp.
      nanoseconds = table_result[ix][6].as<long>(0);

    strncpy(
      _diagnosis_req_command_instance_list.at(ix).second->diagnosis,
      table_result[ix][7].as<std::string>("").c_str(),
      ice::LONG_STRING_LEN);
    _diagnosis_req_command_instance_list.at(ix).second->diagnosis[
      ice::LONG_STRING_LEN] = '\0';
    if (!table_result[ix][8].is_null())
    {
      std::string procedure_list_str = table_result[ix][8].as<std::string>("");
      std::vector < std::pair < std::string, bool>> procedure_list_vect;

      DicesRcDriver status = ParseCSVToArray(
        &procedure_list_vect,
        procedure_list_str);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }

      if (!_diagnosis_req_command_instance_list.at(ix).second->
        procedure_list.ensure_length(
        procedure_list_vect.size(),
        procedure_list_vect.size()))
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to ensure length of "
          "sequence of strings. Length: "
          << procedure_list_vect.size());
        return DicesRcDriver::FAIL;
      }

      for (int iy = 0; iy < procedure_list_vect.size(); iy++)
      {
        strncpy(
          _diagnosis_req_command_instance_list.at(ix).second->
          procedure_list[iy],
          procedure_list_vect.at(iy).first.c_str(),
          ice::LONG_STRING_LEN);
        _diagnosis_req_command_instance_list.at(ix).second->
          procedure_list[iy][ice::LONG_STRING_LEN] = '\0';
      }
    }
    strncpy(
      _diagnosis_req_command_instance_list.at(ix).second->physician,
      table_result[ix][9].as<std::string>("").c_str(),
      ice::LONG_STRING_LEN);
    _diagnosis_req_command_instance_list.at(ix).second->physician[
      ice::LONG_STRING_LEN] = '\0';

    strncpy(
      _diagnosis_req_command_instance_list.at(ix).second->
      patient_identification.given_name,
      table_result[ix][10].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _diagnosis_req_command_instance_list.at(ix).second->
      patient_identification.given_name[ice::SHORT_STRING_LEN] = '\0';
    strncpy(
      _diagnosis_req_command_instance_list.at(ix).second->
      patient_identification.family_name,
      table_result[ix][11].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _diagnosis_req_command_instance_list.at(ix).second->
      patient_identification.family_name[ice::SHORT_STRING_LEN] = '\0';
    strncpy(
      _diagnosis_req_command_instance_list.at(ix).second->
      patient_identification.middle_name,
      table_result[ix][12].as<std::string>("").c_str(),
      ice::SHORT_STRING_LEN);
    _diagnosis_req_command_instance_list.at(ix).second->
      patient_identification.middle_name[ice::SHORT_STRING_LEN] = '\0';

    if (table_result[ix][13].is_null()
      && table_result[ix][14].is_null()
      && table_result[ix][15].is_null()
      && table_result[ix][16].is_null())
    {
      _diagnosis_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth = nullptr;
    }
    else
    {
      _diagnosis_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth = reinterpret_cast<ice::Date*>(
        DDS::Heap_malloc(sizeof(ice::Date)));
      if (!_diagnosis_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for ice::Date");
        return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
      }
      DicesRcDriver status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][13].as<std::string>(""),
        &_diagnosis_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth->century);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][14].as<std::string>(""),
        &_diagnosis_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth->year);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][15].as<std::string>(""),
        &_diagnosis_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth->month);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
      status = ConvertPostgresByteaHexToICEINTU8(
        table_result[ix][16].as<std::string>(""),
        &_diagnosis_req_command_instance_list.at(ix).second->
        patient_identification.date_of_birth->day);
      if (status != DicesRcDriver::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::
          DicesRcDriverToString(status));
        return status;
      }
    }
    strncpy(
      _diagnosis_req_command_instance_list.at(ix).second->
      patient_identification.patient_id,
      table_result[ix][17].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _diagnosis_req_command_instance_list.at(ix).second->
      patient_identification.patient_id[ice::MEDIUM_STRING_LEN] = '\0';
    strncpy(
      _diagnosis_req_command_instance_list.at(ix).second->
      patient_identification.patient_id_provenance,
      table_result[ix][18].as<std::string>("").c_str(),
      ice::MEDIUM_STRING_LEN);
    _diagnosis_req_command_instance_list.at(ix).second->
      patient_identification.patient_id_provenance[ice::MEDIUM_STRING_LEN] =
      '\0';
    _diagnosis_req_command_instance_list.at(ix).second->
      patient_identification.verified = static_cast<ice::BOOL>(
      table_result[ix][19].as<bool>(false));
    _diagnosis_req_command_instance_list.at(ix).second->
      patient_identification.pat_admit_state = static_cast<ice::PatAdmitState>(
      table_result[ix][20].as<int>(0));
    _diagnosis_req_command_instance_list.at(ix).second->
      patient_identification.pat_episode_id = table_result[ix][21].
      as<ice::PatEpisode>(0);
    _diagnosis_req_command_instance_list.at(ix).second->
      patient_identification.episode_start.seconds = table_result[ix][22].
      as<long>(0);
    _diagnosis_req_command_instance_list.at(ix).second->
      patient_identification.episode_start.nanoseconds = table_result[ix][23].
      as<long>(0);
  }
  return DicesRcDriver::OK;
}

template <typename ICETYPE>
DicesRcDriver Parser::GetInstanceToPublish(
  const std::vector<std::pair<DicesRcDriver, ICETYPE*>>& instance_list,
  ICETYPE** instance,
  int* index,
  const char* sfn)
{
  if (instance == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Attempt to pass "
      "null into required parameter instance");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }
  if (index == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Attempt to pass "
      "null into required parameter index");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }
  for (*index = 0; *index < instance_list.size(); (*index)++)
  {
    if (instance_list[*index].first == DicesRcDriver::OK)
    {
      *instance = instance_list[*index].second;
      return DicesRcDriver::OK;
    }
  }
  return DicesRcDriver::NO_NEW_DATA;
}

template DicesRcDriver Parser::GetInstanceToPublish<ice::PatientIdentification>(
  const std::vector<std::pair<DicesRcDriver, ice::PatientIdentification*>>& instance_list,
  ice::PatientIdentification** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<ice::PatientDemographics>(
  const std::vector<std::pair<DicesRcDriver, ice::PatientDemographics*>>& instance_list,
  ice::PatientDemographics** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<ice::AlarmSignal>(
  const std::vector<std::pair<DicesRcDriver, ice::AlarmSignal*>>& instance_list,
  ice::AlarmSignal** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<ice::InformationSignal>(
  const std::vector<std::pair<DicesRcDriver, ice::InformationSignal*>>& instance_list,
  ice::InformationSignal** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<ice::ReminderSignal>(
  const std::vector<std::pair<DicesRcDriver, ice::ReminderSignal*>>& instance_list,
  ice::ReminderSignal** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<ice::AlarmContext>(
  const std::vector<std::pair<DicesRcDriver, ice::AlarmContext*>>& instance_list,
  ice::AlarmContext** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<ice::DSAContext>(
  const std::vector<std::pair<DicesRcDriver, ice::DSAContext*>>& instance_list,
  ice::DSAContext** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<ice::DSAObservedValue>(
  const std::vector<std::pair<DicesRcDriver, ice::DSAObservedValue*>>& instance_list,
  ice::DSAObservedValue** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<ice::EnumerationContext>(
  const std::vector<std::pair<DicesRcDriver, ice::EnumerationContext*>>& instance_list,
  ice::EnumerationContext** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<ice::EnumerationObservedValue>(
  const std::vector<std::pair<DicesRcDriver, ice::EnumerationObservedValue*>>& instance_list,
  ice::EnumerationObservedValue** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<ice::MDS>(
  const std::vector<std::pair<DicesRcDriver, ice::MDS*>>& instance_list,
  ice::MDS** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<ice::VMD>(
  const std::vector<std::pair<DicesRcDriver, ice::VMD*>>& instance_list,
  ice::VMD** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<ice::NumericContext>(
  const std::vector<std::pair<DicesRcDriver, ice::NumericContext*>>& instance_list,
  ice::NumericContext** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<ice::NumericObservedValue>(
  const std::vector<std::pair<DicesRcDriver, ice::NumericObservedValue*>>& instance_list,
  ice::NumericObservedValue** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<ice::RTSAContext>(
  const std::vector<std::pair<DicesRcDriver, ice::RTSAContext*>>& instance_list,
  ice::RTSAContext** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<ice::RTSAObservedValue>(
  const std::vector<std::pair<DicesRcDriver, ice::RTSAObservedValue*>>& instance_list,
  ice::RTSAObservedValue** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<ice::TSAContext>(
  const std::vector<std::pair<DicesRcDriver, ice::TSAContext*>>& instance_list,
  ice::TSAContext** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<ice::TSAObservedValue>(
  const std::vector<std::pair<DicesRcDriver, ice::TSAObservedValue*>>& instance_list,
  ice::TSAObservedValue** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<ice::Allergy>(
  const std::vector<std::pair<DicesRcDriver, ice::Allergy*>>& instance_list,
  ice::Allergy** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<expr::Diagnosis>(
  const std::vector<std::pair<DicesRcDriver, expr::Diagnosis*>>& instance_list,
  expr::Diagnosis** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<expr::DxHistory>(
  const std::vector<std::pair<DicesRcDriver, expr::DxHistory*>>& instance_list,
  expr::DxHistory** instance,
  int* index,
  const char* sfn);
template DicesRcDriver Parser::GetInstanceToPublish<expr::PatientMedication>(
  const std::vector<std::pair<DicesRcDriver, expr::PatientMedication*>>& instance_list,
  expr::PatientMedication** instance,
  int* index,
  const char* sfn);

DicesRcDriver Parser::GetPatientIdentificationReqToPublish(ice::PatientIdentification** instance, int* index)
{
  static const char* sfn = "Parser::GetPatientIdentificationReqToPublish ";
  return GetInstanceToPublish<ice::PatientIdentification>(_patient_identification_req_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetPatientDemographicsReqToPublish(ice::PatientDemographics** instance, int* index)
{
  static const char* sfn = "Parser::GetPatientDemographicsReqToPublish ";
  return GetInstanceToPublish<ice::PatientDemographics>(_patient_demographics_req_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetTechAlarmSignalToPublish(ice::AlarmSignal** instance, int* index)
{
  static const char* sfn = "Parser::GetTechAlarmSignalToPublish ";
  return GetInstanceToPublish<ice::AlarmSignal>(_technical_alarm_signal_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetPhysAlarmSignalToPublish(ice::AlarmSignal** instance, int* index)
{
  static const char* sfn = "Parser::GetPhysAlarmSignalToPublish ";
  return GetInstanceToPublish<ice::AlarmSignal>(_physiological_alarm_signal_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetInformationSignalToPublish(ice::InformationSignal** instance, int* index)
{
  static const char* sfn = "Parser::GetInformationSignalToPublish ";
  return GetInstanceToPublish<ice::InformationSignal>(_information_signal_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetReminderSignalToPublish(ice::ReminderSignal** instance, int* index)
{
  static const char* sfn = "Parser::GetReminderSignalToPublish ";
  return GetInstanceToPublish<ice::ReminderSignal>(_reminder_signal_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetTechAlarmContextToPublish(ice::AlarmContext** instance, int* index)
{
  static const char* sfn = "Parser::GetTechAlarmContextToPublish ";
  return GetInstanceToPublish<ice::AlarmContext>(_technical_alarm_context_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetPhysAlarmContextToPublish(ice::AlarmContext** instance, int* index)
{
  static const char* sfn = "Parser::GetPhysAlarmContextToPublish ";
  return GetInstanceToPublish<ice::AlarmContext>(_physiological_alarm_context_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetDSAMeasContextToPublish(ice::DSAContext** instance, int* index)
{
  static const char* sfn = "Parser::GetDSAMeasContextToPublish ";
  return GetInstanceToPublish<ice::DSAContext>(_dsa_meas_context_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetDSAMeasObservedValueToPublish(ice::DSAObservedValue** instance, int* index)
{
  static const char* sfn = "Parser::GetDSAMeasObservedValueToPublish ";
  return GetInstanceToPublish<ice::DSAObservedValue>(_dsa_meas_observed_value_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetDSACalcContextToPublish(ice::DSAContext** instance, int* index)
{
  static const char* sfn = "Parser::GetDSACalcContextToPublish ";
  return GetInstanceToPublish<ice::DSAContext>(_dsa_calc_context_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetDSACalcObservedValueToPublish(ice::DSAObservedValue** instance, int* index)
{
  static const char* sfn = "Parser::GetDSACalcObservedValueToPublish ";
  return GetInstanceToPublish<ice::DSAObservedValue>(_dsa_calc_observed_value_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetDSASettContextToPublish(ice::DSAContext** instance, int* index)
{
  static const char* sfn = "Parser::GetDSASettContextToPublish ";
  return GetInstanceToPublish<ice::DSAContext>(_dsa_sett_context_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetDSASettObservedValueToPublish(ice::DSAObservedValue** instance, int* index)
{
  static const char* sfn = "Parser::GetDSASettObservedValueToPublish ";
  return GetInstanceToPublish<ice::DSAObservedValue>(_dsa_sett_observed_value_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetEnumerationMeasContextToPublish(ice::EnumerationContext** instance, int* index)
{
  static const char* sfn = "Parser::GetEnumerationMeasContextToPublish ";
  return GetInstanceToPublish<ice::EnumerationContext>(_enumeration_meas_context_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetEnumerationMeasObservedValueToPublish(ice::EnumerationObservedValue** instance, int* index)
{
  static const char* sfn = "Parser::GetEnumerationMeasObservedValueToPublish ";
  return GetInstanceToPublish<ice::EnumerationObservedValue>(_enumeration_meas_observed_value_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetEnumerationCalcContextToPublish(ice::EnumerationContext** instance, int* index)
{
  static const char* sfn = "Parser::GetEnumerationCalcContextToPublish ";
  return GetInstanceToPublish<ice::EnumerationContext>(_enumeration_calc_context_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetEnumerationCalcObservedValueToPublish(ice::EnumerationObservedValue** instance, int* index)
{
  static const char* sfn = "Parser::GetEnumerationCalcObservedValueToPublish ";
  return GetInstanceToPublish<ice::EnumerationObservedValue>(_enumeration_calc_observed_value_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetEnumerationSettContextToPublish(ice::EnumerationContext** instance, int* index)
{
  static const char* sfn = "Parser::GetEnumerationSettContextToPublish ";
  return GetInstanceToPublish<ice::EnumerationContext>(_enumeration_sett_context_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetEnumerationSettObservedValueToPublish(ice::EnumerationObservedValue** instance, int* index)
{
  static const char* sfn = "Parser::GetEnumerationSettObservedValueToPublish ";
  return GetInstanceToPublish<ice::EnumerationObservedValue>(_enumeration_sett_observed_value_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetMDSToPublish(ice::MDS** instance, int* index)
{
  static const char* sfn = "Parser::GetMDSToPublish ";
  return GetInstanceToPublish<ice::MDS>(_mds_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetVMDToPublish(ice::VMD** instance, int* index)
{
  static const char* sfn = "Parser::GetVMDToPublish ";
  return GetInstanceToPublish<ice::VMD>(_vmd_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetNumericMeasContextToPublish(ice::NumericContext** instance, int* index)
{
  static const char* sfn = "Parser::GetNumericMeasContextToPublish ";
  return GetInstanceToPublish<ice::NumericContext>(_numeric_meas_context_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetNumericMeasObservedValueToPublish(ice::NumericObservedValue** instance, int* index)
{
  static const char* sfn = "Parser::GetNumericMeasObservedValueToPublish ";
  return GetInstanceToPublish<ice::NumericObservedValue>(_numeric_meas_observed_value_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetNumericCalcContextToPublish(ice::NumericContext** instance, int* index)
{
  static const char* sfn = "Parser::GetNumericCalcContextToPublish ";
  return GetInstanceToPublish<ice::NumericContext>(_numeric_calc_context_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetNumericCalcObservedValueToPublish(ice::NumericObservedValue** instance, int* index)
{
  static const char* sfn = "Parser::GetNumericCalcObservedValueToPublish ";
  return GetInstanceToPublish<ice::NumericObservedValue>(_numeric_calc_observed_value_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetNumericSettContextToPublish(ice::NumericContext** instance, int* index)
{
  static const char* sfn = "Parser::GetNumericSettContextToPublish ";
  return GetInstanceToPublish<ice::NumericContext>(_numeric_sett_context_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetNumericSettObservedValueToPublish(ice::NumericObservedValue** instance, int* index)
{
  static const char* sfn = "Parser::GetNumericSettObservedValueToPublish ";
  return GetInstanceToPublish<ice::NumericObservedValue>(_numeric_sett_observed_value_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetRTSAMeasContextToPublish(ice::RTSAContext** instance, int* index)
{
  static const char* sfn = "Parser::GetRTSAMeasContextToPublish ";
  return GetInstanceToPublish<ice::RTSAContext>(_rtsa_meas_context_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetRTSAMeasObservedValueToPublish(ice::RTSAObservedValue** instance, int* index)
{
  static const char* sfn = "Parser::GetRTSAMeasObservedValueToPublish ";
  return GetInstanceToPublish<ice::RTSAObservedValue>(_rtsa_meas_observed_value_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetRTSACalcContextToPublish(ice::RTSAContext** instance, int* index)
{
  static const char* sfn = "Parser::GetRTSACalcContextToPublish ";
  return GetInstanceToPublish<ice::RTSAContext>(_rtsa_calc_context_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetRTSACalcObservedValueToPublish(ice::RTSAObservedValue** instance, int* index)
{
  static const char* sfn = "Parser::GetRTSACalcObservedValueToPublish ";
  return GetInstanceToPublish<ice::RTSAObservedValue>(_rtsa_calc_observed_value_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetRTSASettContextToPublish(ice::RTSAContext** instance, int* index)
{
  static const char* sfn = "Parser::GetRTSASettContextToPublish ";
  return GetInstanceToPublish<ice::RTSAContext>(_rtsa_sett_context_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetRTSASettObservedValueToPublish(ice::RTSAObservedValue** instance, int* index)
{
  static const char* sfn = "Parser::GetRTSASettObservedValueToPublish ";
  return GetInstanceToPublish<ice::RTSAObservedValue>(_rtsa_sett_observed_value_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetTSAMeasContextToPublish(ice::TSAContext** instance, int* index)
{
  static const char* sfn = "Parser::GetTSAMeasContextToPublish ";
  return GetInstanceToPublish<ice::TSAContext>(_tsa_meas_context_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetTSAMeasObservedValueToPublish(ice::TSAObservedValue** instance, int* index)
{
  static const char* sfn = "Parser::GetTSAMeasObservedValueToPublish ";
  return GetInstanceToPublish<ice::TSAObservedValue>(_tsa_meas_observed_value_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetTSACalcContextToPublish(ice::TSAContext** instance, int* index)
{
  static const char* sfn = "Parser::GetTSACalcContextToPublish ";
  return GetInstanceToPublish<ice::TSAContext>(_tsa_calc_context_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetTSACalcObservedValueToPublish(ice::TSAObservedValue** instance, int* index)
{
  static const char* sfn = "Parser::GetTSACalcObservedValueToPublish ";
  return GetInstanceToPublish<ice::TSAObservedValue>(_tsa_calc_observed_value_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetTSASettContextToPublish(ice::TSAContext** instance, int* index)
{
  static const char* sfn = "Parser::GetTSASettContextToPublish ";
  return GetInstanceToPublish<ice::TSAContext>(_tsa_sett_context_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetTSASettObservedValueToPublish(ice::TSAObservedValue** instance, int* index)
{
  static const char* sfn = "Parser::GetTSASettObservedValueToPublish ";
  return GetInstanceToPublish<ice::TSAObservedValue>(_tsa_sett_observed_value_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetPatientIdentificationToPublish(ice::PatientIdentification** instance, int* index)
{
  static const char* sfn = "Parser::GetPatientIdentificationToPublish ";
  return GetInstanceToPublish<ice::PatientIdentification>(_patient_identification_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetPatientDemographicsToPublish(ice::PatientDemographics** instance, int* index)
{
  static const char* sfn = "Parser::GetPatientDemographicsToPublish ";
  return GetInstanceToPublish<ice::PatientDemographics>(_patient_demographics_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetAllergyToPublish(ice::Allergy** instance, int* index)
{
  static const char* sfn = "Parser::GetAllergyToPublish ";
  return GetInstanceToPublish<ice::Allergy>(_allergy_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetDiagnosisToPublish(expr::Diagnosis** instance, int* index)
{
  static const char* sfn = "Parser::GetDiagnosisToPublish ";
  return GetInstanceToPublish<expr::Diagnosis>(_diagnosis_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetDxHistoryToPublish(expr::DxHistory** instance, int* index)
{
  static const char* sfn = "Parser::GetDxHistoryToPublish ";
  return GetInstanceToPublish<expr::DxHistory>(_dxhistory_response_instance_list, instance, index, sfn);
}

DicesRcDriver Parser::GetMedicationToPublish(expr::PatientMedication** instance, int* index)
{
  static const char* sfn = "Parser::GetMedicationToPublish ";
  return GetInstanceToPublish<expr::PatientMedication>(_patient_medication_response_instance_list, instance, index, sfn);
}

template <typename ICETYPE>
DicesRcDriver Parser::SetInstanceAsPublished(
  std::vector<std::pair<DicesRcDriver, ICETYPE*>>* instance_list,
  int index,
  const char* sfn)
{
  if (instance_list == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Attempt to pass "
      "null into required parameter instance_list");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }
  if (index >= instance_list->size())
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Attempt to access "
      "invalid parameter " << index);
    return DicesRcDriver::PARAMETER_RANGE_FAILURE;
  }
  if (instance_list->at(index).first != DicesRcDriver::OK)
  {
    DicesRcDriver rc = instance_list->at(index).first;
    LOG4CPLUS_WARN(root_logger, sfn << "Setting non-OK code "
      << DicesRcDriverStatusMessage::DicesRcDriverToString(rc)
      << " to NO NEW DATA for parameter " << index
      << ", implying non-ready parameter was published.");
  }
  instance_list->at(index).first = DicesRcDriver::NO_NEW_DATA;
  return DicesRcDriver::OK;
}

template DicesRcDriver Parser::SetInstanceAsPublished<ice::PatientIdentification>(
  std::vector<std::pair<DicesRcDriver, ice::PatientIdentification*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<ice::PatientDemographics>(
  std::vector<std::pair<DicesRcDriver, ice::PatientDemographics*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<ice::AlarmSignal>(
  std::vector<std::pair<DicesRcDriver, ice::AlarmSignal*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<ice::InformationSignal>(
  std::vector<std::pair<DicesRcDriver, ice::InformationSignal*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<ice::ReminderSignal>(
  std::vector<std::pair<DicesRcDriver, ice::ReminderSignal*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<ice::AlarmContext>(
  std::vector<std::pair<DicesRcDriver, ice::AlarmContext*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<ice::DSAContext>(
  std::vector<std::pair<DicesRcDriver, ice::DSAContext*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<ice::DSAObservedValue>(
  std::vector<std::pair<DicesRcDriver, ice::DSAObservedValue*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<ice::EnumerationContext>(
  std::vector<std::pair<DicesRcDriver, ice::EnumerationContext*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<ice::EnumerationObservedValue>(
  std::vector<std::pair<DicesRcDriver, ice::EnumerationObservedValue*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<ice::MDS>(
  std::vector<std::pair<DicesRcDriver, ice::MDS*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<ice::VMD>(
  std::vector<std::pair<DicesRcDriver, ice::VMD*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<ice::NumericContext>(
  std::vector<std::pair<DicesRcDriver, ice::NumericContext*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<ice::NumericObservedValue>(
  std::vector<std::pair<DicesRcDriver, ice::NumericObservedValue*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<ice::RTSAContext>(
  std::vector<std::pair<DicesRcDriver, ice::RTSAContext*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<ice::RTSAObservedValue>(
  std::vector<std::pair<DicesRcDriver, ice::RTSAObservedValue*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<ice::TSAContext>(
  std::vector<std::pair<DicesRcDriver, ice::TSAContext*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<ice::TSAObservedValue>(
  std::vector<std::pair<DicesRcDriver, ice::TSAObservedValue*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<ice::Allergy>(
  std::vector<std::pair<DicesRcDriver, ice::Allergy*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<expr::Diagnosis>(
  std::vector<std::pair<DicesRcDriver, expr::Diagnosis*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<expr::DxHistory>(
  std::vector<std::pair<DicesRcDriver, expr::DxHistory*>>* instance_list,
  int index,
  const char* sfn);
template DicesRcDriver Parser::SetInstanceAsPublished<expr::PatientMedication>(
  std::vector<std::pair<DicesRcDriver, expr::PatientMedication*>>* instance_list,
  int index,
  const char* sfn);

DicesRcDriver Parser::SetPatientIdentificationReqAsPublished(int index)
{
  static const char* sfn = "Parser::SetPatientIdentificationReqAsPublished ";
  return SetInstanceAsPublished<ice::PatientIdentification>(&_patient_identification_req_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetPatientDemographicsReqAsPublished(int index)
{
  static const char* sfn = "Parser::SetPatientDemographicsReqAsPublished ";
  return SetInstanceAsPublished<ice::PatientDemographics>(&_patient_demographics_req_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetTechAlarmSignalAsPublished(int index)
{
  static const char* sfn = "Parser::SetTechAlarmSignalAsPublished ";
  return SetInstanceAsPublished<ice::AlarmSignal>(&_technical_alarm_signal_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetPhysAlarmSignalAsPublished(int index)
{
  static const char* sfn = "Parser::SetPhysAlarmSignalAsPublished ";
  return SetInstanceAsPublished<ice::AlarmSignal>(&_physiological_alarm_signal_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetInformationSignalAsPublished(int index)
{
  static const char* sfn = "Parser::SetInformationSignalAsPublished ";
  return SetInstanceAsPublished<ice::InformationSignal>(&_information_signal_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetReminderSignalAsPublished(int index)
{
  static const char* sfn = "Parser::SetReminderSignalAsPublished ";
  return SetInstanceAsPublished<ice::ReminderSignal>(&_reminder_signal_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetTechAlarmContextAsPublished(int index)
{
  static const char* sfn = "Parser::SetTechAlarmContextAsPublished ";
  return SetInstanceAsPublished<ice::AlarmContext>(&_technical_alarm_context_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetPhysAlarmContextAsPublished(int index)
{
  static const char* sfn = "Parser::SetPhysAlarmContextAsPublished ";
  return SetInstanceAsPublished<ice::AlarmContext>(&_physiological_alarm_context_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetDSAMeasContextAsPublished(int index)
{
  static const char* sfn = "Parser::SetDSAMeasContextAsPublished ";
  return SetInstanceAsPublished<ice::DSAContext>(&_dsa_meas_context_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetDSAMeasObservedValueAsPublished(int index)
{
  static const char* sfn = "Parser::SetDSAMeasObservedValueAsPublished ";
  return SetInstanceAsPublished<ice::DSAObservedValue>(&_dsa_meas_observed_value_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetDSACalcContextAsPublished(int index)
{
  static const char* sfn = "Parser::SetDSACalcContextAsPublished ";
  return SetInstanceAsPublished<ice::DSAContext>(&_dsa_calc_context_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetDSACalcObservedValueAsPublished(int index)
{
  static const char* sfn = "Parser::SetDSACalcObservedValueAsPublished ";
  return SetInstanceAsPublished<ice::DSAObservedValue>(&_dsa_calc_observed_value_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetDSASettContextAsPublished(int index)
{
  static const char* sfn = "Parser::SetDSASettContextAsPublished ";
  return SetInstanceAsPublished<ice::DSAContext>(&_dsa_sett_context_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetDSASettObservedValueAsPublished(int index)
{
  static const char* sfn = "Parser::SetDSASettObservedValueAsPublished ";
  return SetInstanceAsPublished<ice::DSAObservedValue>(&_dsa_sett_observed_value_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetEnumerationMeasContextAsPublished(int index)
{
  static const char* sfn = "Parser::SetEnumerationMeasContextAsPublished ";
  return SetInstanceAsPublished<ice::EnumerationContext>(&_enumeration_meas_context_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetEnumerationMeasObservedValueAsPublished(int index)
{
  static const char* sfn = "Parser::SetEnumerationMeasObservedValueAsPublished ";
  return SetInstanceAsPublished<ice::EnumerationObservedValue>(&_enumeration_meas_observed_value_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetEnumerationCalcContextAsPublished(int index)
{
  static const char* sfn = "Parser::SetEnumerationCalcContextAsPublished ";
  return SetInstanceAsPublished<ice::EnumerationContext>(&_enumeration_calc_context_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetEnumerationCalcObservedValueAsPublished(int index)
{
  static const char* sfn = "Parser::SetEnumerationCalcObservedValueAsPublished ";
  return SetInstanceAsPublished<ice::EnumerationObservedValue>(&_enumeration_calc_observed_value_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetEnumerationSettContextAsPublished(int index)
{
  static const char* sfn = "Parser::SetEnumerationSettContextAsPublished ";
  return SetInstanceAsPublished<ice::EnumerationContext>(&_enumeration_sett_context_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetEnumerationSettObservedValueAsPublished(int index)
{
  static const char* sfn = "Parser::SetEnumerationSettObservedValueAsPublished ";
  return SetInstanceAsPublished<ice::EnumerationObservedValue>(&_enumeration_sett_observed_value_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetMDSAsPublished(int index)
{
  static const char* sfn = "Parser::SetMDSAsPublished ";
  return SetInstanceAsPublished<ice::MDS>(&_mds_instance_list, index, sfn);
}

DicesRcDriver Parser::SetVMDAsPublished(int index)
{
  static const char* sfn = "Parser::SetVMDAsPublished ";
  return SetInstanceAsPublished<ice::VMD>(&_vmd_instance_list, index, sfn);
}

DicesRcDriver Parser::SetNumericMeasContextAsPublished(int index)
{
  static const char* sfn = "Parser::SetNumericMeasContextAsPublished ";
  return SetInstanceAsPublished<ice::NumericContext>(&_numeric_meas_context_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetNumericMeasObservedValueAsPublished(int index)
{
  static const char* sfn = "Parser::SetNumericMeasObservedValueAsPublished ";
  return SetInstanceAsPublished<ice::NumericObservedValue>(&_numeric_meas_observed_value_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetNumericCalcContextAsPublished(int index)
{
  static const char* sfn = "Parser::SetNumericCalcContextAsPublished ";
  return SetInstanceAsPublished<ice::NumericContext>(&_numeric_calc_context_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetNumericCalcObservedValueAsPublished(int index)
{
  static const char* sfn = "Parser::SetNumericCalcObservedValueAsPublished ";
  return SetInstanceAsPublished<ice::NumericObservedValue>(&_numeric_calc_observed_value_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetNumericSettContextAsPublished(int index)
{
  static const char* sfn = "Parser::SetNumericSettContextAsPublished ";
  return SetInstanceAsPublished<ice::NumericContext>(&_numeric_sett_context_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetNumericSettObservedValueAsPublished(int index)
{
  static const char* sfn = "Parser::SetNumericSettObservedValueAsPublished ";
  return SetInstanceAsPublished<ice::NumericObservedValue>(&_numeric_sett_observed_value_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetRTSAMeasContextAsPublished(int index)
{
  static const char* sfn = "Parser::SetRTSAMeasContextAsPublished ";
  return SetInstanceAsPublished<ice::RTSAContext>(&_rtsa_meas_context_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetRTSAMeasObservedValueAsPublished(int index)
{
  static const char* sfn = "Parser::SetRTSAMeasObservedValueAsPublished ";
  return SetInstanceAsPublished<ice::RTSAObservedValue>(&_rtsa_meas_observed_value_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetRTSACalcContextAsPublished(int index)
{
  static const char* sfn = "Parser::SetRTSACalcContextAsPublished ";
  return SetInstanceAsPublished<ice::RTSAContext>(&_rtsa_calc_context_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetRTSACalcObservedValueAsPublished(int index)
{
  static const char* sfn = "Parser::SetRTSACalcObservedValueAsPublished ";
  return SetInstanceAsPublished<ice::RTSAObservedValue>(&_rtsa_calc_observed_value_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetRTSASettContextAsPublished(int index)
{
  static const char* sfn = "Parser::SetRTSASettContextAsPublished ";
  return SetInstanceAsPublished<ice::RTSAContext>(&_rtsa_sett_context_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetRTSASettObservedValueAsPublished(int index)
{
  static const char* sfn = "Parser::SetRTSASettObservedValueAsPublished ";
  return SetInstanceAsPublished<ice::RTSAObservedValue>(&_rtsa_sett_observed_value_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetTSAMeasContextAsPublished(int index)
{
  static const char* sfn = "Parser::SetTSAMeasContextAsPublished ";
  return SetInstanceAsPublished<ice::TSAContext>(&_tsa_meas_context_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetTSAMeasObservedValueAsPublished(int index)
{
  static const char* sfn = "Parser::SetTSAMeasObservedValueAsPublished ";
  return SetInstanceAsPublished<ice::TSAObservedValue>(&_tsa_meas_observed_value_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetTSACalcContextAsPublished(int index)
{
  static const char* sfn = "Parser::SetTSACalcContextAsPublished ";
  return SetInstanceAsPublished<ice::TSAContext>(&_tsa_calc_context_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetTSACalcObservedValueAsPublished(int index)
{
  static const char* sfn = "Parser::SetTSACalcObservedValueAsPublished ";
  return SetInstanceAsPublished<ice::TSAObservedValue>(&_tsa_calc_observed_value_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetTSASettContextAsPublished(int index)
{
  static const char* sfn = "Parser::SetTSASettContextAsPublished ";
  return SetInstanceAsPublished<ice::TSAContext>(&_tsa_sett_context_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetTSASettObservedValueAsPublished(int index)
{
  static const char* sfn = "Parser::SetTSASettObservedValueAsPublished ";
  return SetInstanceAsPublished<ice::TSAObservedValue>(&_tsa_sett_observed_value_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetPatientIdentificationAsPublished(int index)
{
  static const char* sfn = "Parser::SetPatientIdentificationAsPublished ";
  return SetInstanceAsPublished<ice::PatientIdentification>(&_patient_identification_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetPatientDemographicsAsPublished(int index)
{
  static const char* sfn = "Parser::SetPatientDemographicsAsPublished ";
  return SetInstanceAsPublished<ice::PatientDemographics>(&_patient_demographics_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetAllergyAsPublished(int index)
{
  static const char* sfn = "Parser::SetAllergyAsPublished ";
  return SetInstanceAsPublished<ice::Allergy>(&_allergy_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetDiagnosisAsPublished(int index)
{
  static const char* sfn = "Parser::SetDiagnosisAsPublished ";
  return SetInstanceAsPublished<expr::Diagnosis>(&_diagnosis_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetDxHistoryAsPublished(int index)
{
  static const char* sfn = "Parser::SetDxHistoryAsPublished ";
  return SetInstanceAsPublished<expr::DxHistory>(&_dxhistory_response_instance_list, index, sfn);
}

DicesRcDriver Parser::SetMedicationAsPublished(int index)
{
  static const char* sfn = "Parser::SetMedicationAsPublished ";
  return SetInstanceAsPublished<expr::PatientMedication>(&_patient_medication_response_instance_list, index, sfn);
}

template <typename ICETYPE>
DicesRcDriver Parser::AddInstanceCommand(
  std::vector<std::pair<DicesRcDriver, ICETYPE*>>* instance_list,
  const ICETYPE* instance,
  const char* sfn)
{
  if (instance_list == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Attempt to pass "
      "null into required parameter instance_list");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }
  if (instance == nullptr)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Attempt to pass "
      "null into required parameter instance");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }
  for (auto &pair : *instance_list)
  {
    // TODO: We're currently not doing anything with the commands.  I am writing
    // this under the assumption (VERIFY PLEASE) that completed commands will be
    // deleted and nulled in the command instance lists, partly as it would be
    // difficult to delete properly from here the way the template is written
    // (needing to make a call to ICETYPETypeSupport).  If for some reason a
    // command is NO_NEW_DATA but still in the instance list, its location in
    // the list will NOT be overwritten, until it is deleted and nulled.
    if (pair.first == DicesRcDriver::NO_NEW_DATA && pair.second == nullptr)
    {
      pair.first = DicesRcDriver::OK;
      pair.second = const_cast<ICETYPE*>(instance);
      return DicesRcDriver::OK;
    }
  }
  try
  {
    instance_list->resize(instance_list->size() + 1);
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception reserving memory for "
      "instance list: " << ex.what());
    return DicesRcDriver::MEMORY_ALLOCATION_FAILURE;
  }
  instance_list->back().first = DicesRcDriver::OK;
  instance_list->back().second = const_cast<ICETYPE*>(instance);
  return DicesRcDriver::OK;
}

template DicesRcDriver Parser::AddInstanceCommand<ice::AlarmContext>(
  std::vector<std::pair<DicesRcDriver, ice::AlarmContext*>>* instance_list,
  const ice::AlarmContext* instance,
  const char* sfn);
template DicesRcDriver Parser::AddInstanceCommand<ice::DSAContext>(
  std::vector<std::pair<DicesRcDriver, ice::DSAContext*>>* instance_list,
  const ice::DSAContext* instance,
  const char* sfn);
template DicesRcDriver Parser::AddInstanceCommand<ice::EnumerationContext>(
  std::vector<std::pair<DicesRcDriver, ice::EnumerationContext*>>* instance_list,
  const ice::EnumerationContext* instance,
  const char* sfn);
template DicesRcDriver Parser::AddInstanceCommand<ice::EnumerationObservedValue>(
  std::vector<std::pair<DicesRcDriver, ice::EnumerationObservedValue*>>* instance_list,
  const ice::EnumerationObservedValue* instance,
  const char* sfn);
template DicesRcDriver Parser::AddInstanceCommand<ice::NumericContext>(
  std::vector<std::pair<DicesRcDriver, ice::NumericContext*>>* instance_list,
  const ice::NumericContext* instance,
  const char* sfn);
template DicesRcDriver Parser::AddInstanceCommand<ice::NumericObservedValue>(
  std::vector<std::pair<DicesRcDriver, ice::NumericObservedValue*>>* instance_list,
  const ice::NumericObservedValue* instance,
  const char* sfn);
template DicesRcDriver Parser::AddInstanceCommand<ice::RTSAContext>(
  std::vector<std::pair<DicesRcDriver, ice::RTSAContext*>>* instance_list,
  const ice::RTSAContext* instance,
  const char* sfn);
template DicesRcDriver Parser::AddInstanceCommand<ice::TSAContext>(
  std::vector<std::pair<DicesRcDriver, ice::TSAContext*>>* instance_list,
  const ice::TSAContext* instance,
  const char* sfn);
template DicesRcDriver Parser::AddInstanceCommand<ice::PatientIdentification>(
  std::vector<std::pair<DicesRcDriver, ice::PatientIdentification*>>* instance_list,
  const ice::PatientIdentification* instance,
  const char* sfn);

DicesRcDriver Parser::AddPhysAlarmContextCommand(const ice::AlarmContext* instance)
{
  static const char* sfn = "Parser::AddPhysAlarmContextCommand ";
  return AddInstanceCommand<ice::AlarmContext>(&_physiological_alarm_context_req_command_instance_list, instance, sfn);
}

DicesRcDriver Parser::AddTechAlarmContextCommand(const ice::AlarmContext* instance)
{
  static const char* sfn = "Parser::AddTechAlarmContextCommand ";
  return AddInstanceCommand<ice::AlarmContext>(&_technical_alarm_context_req_command_instance_list, instance, sfn);
}

DicesRcDriver Parser::AddDSAMeasContextCommand(const ice::DSAContext* instance)
{
  static const char* sfn = "Parser::AddDSAMeasContextCommand ";
  return AddInstanceCommand<ice::DSAContext>(&_dsa_meas_context_req_command_instance_list, instance, sfn);
}

DicesRcDriver Parser::AddDSACalcContextCommand(const ice::DSAContext* instance)
{
  static const char* sfn = "Parser::AddDSACalcContextCommand ";
  return AddInstanceCommand<ice::DSAContext>(&_dsa_calc_context_req_command_instance_list, instance, sfn);
}

DicesRcDriver Parser::AddDSASettContextCommand(const ice::DSAContext* instance)
{
  static const char* sfn = "Parser::AddDSASettContextCommand ";
  return AddInstanceCommand<ice::DSAContext>(&_dsa_sett_context_req_command_instance_list, instance, sfn);
}

DicesRcDriver Parser::AddEnumerationMeasContextCommand(const ice::EnumerationContext* instance)
{
  static const char* sfn = "Parser::AddEnumerationMeasContextCommand ";
  return AddInstanceCommand<ice::EnumerationContext>(&_enumeration_meas_context_req_command_instance_list, instance, sfn);
}

DicesRcDriver Parser::AddEnumerationCalcContextCommand(const ice::EnumerationContext* instance)
{
  static const char* sfn = "Parser::AddEnumerationCalcContextCommand ";
  return AddInstanceCommand<ice::EnumerationContext>(&_enumeration_calc_context_req_command_instance_list, instance, sfn);
}

DicesRcDriver Parser::AddEnumerationSettContextCommand(const ice::EnumerationContext* instance)
{
  static const char* sfn = "Parser::AddEnumerationSettContextCommand ";
  return AddInstanceCommand<ice::EnumerationContext>(&_enumeration_sett_context_req_command_instance_list, instance, sfn);
}

DicesRcDriver Parser::AddEnumerationSettObservedValueCommand(const ice::EnumerationObservedValue* instance)
{
  static const char* sfn = "Parser::AddEnumerationSettObservedValueCommand ";
  return AddInstanceCommand<ice::EnumerationObservedValue>(&_enumeration_sett_observed_value_req_command_instance_list, instance, sfn);
}

DicesRcDriver Parser::AddNumericMeasContextCommand(const ice::NumericContext* instance)
{
  static const char* sfn = "Parser::AddNumericMeasContextCommand ";
  return AddInstanceCommand<ice::NumericContext>(&_numeric_meas_context_req_command_instance_list, instance, sfn);
}

DicesRcDriver Parser::AddNumericCalcContextCommand(const ice::NumericContext* instance)
{
  static const char* sfn = "Parser::AddNumericCalcContextCommand ";
  return AddInstanceCommand<ice::NumericContext>(&_numeric_calc_context_req_command_instance_list, instance, sfn);
}

DicesRcDriver Parser::AddNumericSettContextCommand(const ice::NumericContext* instance)
{
  static const char* sfn = "Parser::AddNumericSettContextCommand ";
  return AddInstanceCommand<ice::NumericContext>(&_numeric_sett_context_req_command_instance_list, instance, sfn);
}

DicesRcDriver Parser::AddNumericSettObservedValueCommand(const ice::NumericObservedValue* instance)
{
  static const char* sfn = "Parser::AddNumericSettObservedValueCommand ";
  return AddInstanceCommand<ice::NumericObservedValue>(&_numeric_sett_observed_value_req_command_instance_list, instance, sfn);
}

DicesRcDriver Parser::AddRTSAMeasContextCommand(const ice::RTSAContext* instance)
{
  static const char* sfn = "Parser::AddRTSAMeasContextCommand ";
  return AddInstanceCommand<ice::RTSAContext>(&_rtsa_meas_context_req_command_instance_list, instance, sfn);
}

DicesRcDriver Parser::AddRTSACalcContextCommand(const ice::RTSAContext* instance)
{
  static const char* sfn = "Parser::AddRTSACalcContextCommand ";
  return AddInstanceCommand<ice::RTSAContext>(&_rtsa_calc_context_req_command_instance_list, instance, sfn);
}

DicesRcDriver Parser::AddRTSASettContextCommand(const ice::RTSAContext* instance)
{
  static const char* sfn = "Parser::AddRTSASettContextCommand ";
  return AddInstanceCommand<ice::RTSAContext>(&_rtsa_sett_context_req_command_instance_list, instance, sfn);
}

DicesRcDriver Parser::AddTSAMeasContextCommand(const ice::TSAContext* instance)
{
  static const char* sfn = "Parser::AddTSAMeasContextCommand ";
  return AddInstanceCommand<ice::TSAContext>(&_tsa_meas_context_req_command_instance_list, instance, sfn);
}

DicesRcDriver Parser::AddTSACalcContextCommand(const ice::TSAContext* instance)
{
  static const char* sfn = "Parser::AddTSACalcContextCommand ";
  return AddInstanceCommand<ice::TSAContext>(&_tsa_calc_context_req_command_instance_list, instance, sfn);
}

DicesRcDriver Parser::AddTSASettContextCommand(const ice::TSAContext* instance)
{
  static const char* sfn = "Parser::AddTSASettContextCommand ";
  return AddInstanceCommand<ice::TSAContext>(&_tsa_sett_context_req_command_instance_list, instance, sfn);
}

DicesRcDriver Parser::AddPatientIdentificationCommand(const ice::PatientIdentification* instance)
{
  static const char* sfn = "Parser::AddPatientIdentificationCommand ";
  return AddInstanceCommand<ice::PatientIdentification>(&_patient_identification_req_command_instance_list, instance, sfn);
}
DicesRcDriver Parser::AddDeviceDriverStateCommand(const docbox::DeviceDriverState* instance)
{
  static const char* sfn = "Parser::AddDeviceDriverStateCommand ";
  return AddInstanceCommand<docbox::DeviceDriverState>(&_device_driver_state_req_command_instance_list, instance, sfn);
}

DicesRcDriver Parser::AddAllergyCommand(const ice::Allergy *instance)
{
  static const char* sfn = "Parser::AddAllergyCommand ";
  return AddInstanceCommand<ice::Allergy>(&_allergy_command_instance_list, instance, sfn);
}
