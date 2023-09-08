/*
 * File:   parser.h
 * Author: Robert England
 *
 * Created on November 17, 2014
 * Last Modified on November 17, 2014
 */

#ifndef PARSER_H
#define	PARSER_H

#include <string>
#include <vector>
#include <set>
#include <utility>
#include <cstdint>
#include <pqxx/pqxx>

#include "common.h"

enum class DicesRcDriver;
namespace ice
{
// TODO: Can't seem to get this forward declaration to work for some reason.
//class MdsContext;
class PatientIdentification;
class PatientDemographics;

class AlarmSignal;
class InformationSignal;
class ReminderSignal;
class AlarmContext;

class DSAContext;
class DSAObservedValue;

class EnumerationContext;
class EnumerationObservedValue;

class MDS;
class VMD;

class NumericContext;
class NumericObservedValue;

class RTSAContext;
class RTSAObservedValue;

class TSAContext;
class TSAObservedValue;

class Allergy;
}

namespace expr
{
class Diagnosis;
class DxHistory;
class Medication;
class PatientMedication;
}

namespace docbox
{
class DeviceDriverState;
}

enum class CreateWriterName
{
  DeviceDriverStateWriter = 0,
  PatientIdentificationReqWriter,
  PhysiologicalAlarmSignalWriter,
  TechnicalAlarmSignalWriter,
  InformationSignalWriter,
  ReminderSignalWriter,
  PhysiologicalAlarmContextWriter,
  TechnicalAlarmContextWriter,
  DSAMeasContextWriter,
  DSAMeasObservedValueWriter,
  DSACalcContextWriter,
  DSACalcObservedValueWriter,
  DSASettContextWriter,
  DSASettObservedValueWriter,
  EnumerationMeasContextWriter,
  EnumerationMeasObservedValueWriter,
  EnumerationCalcContextWriter,
  EnumerationCalcObservedValueWriter,
  EnumerationSettContextWriter,
  EnumerationSettObservedValueWriter,
  MDSWriter,
  VMDWriter,
  NumericMeasContextWriter,
  NumericMeasObservedValueWriter,
  NumericCalcContextWriter,
  NumericCalcObservedValueWriter,
  NumericSettContextWriter,
  NumericSettObservedValueWriter,
  RTSAMeasContextWriter,
  RTSAMeasObservedValueWriter,
  RTSACalcContextWriter,
  RTSACalcObservedValueWriter,
  RTSASettContextWriter,
  RTSASettObservedValueWriter,
  TSAMeasContextWriter,
  TSAMeasObservedValueWriter,
  TSACalcContextWriter,
  TSACalcObservedValueWriter,
  TSASettContextWriter,
  TSASettObservedValueWriter,
  PatientIdentificationWriter,
  PatientDemographicsWriter,
  PatientDemographicsReqWriter,
  AllergyWriter,
  AllergyReqWriter,
  DiagnosisWriter,
  DiagnosisReqWriter,
  DxHistoryWriter,
  DxHistoryReqWriter,
  PatientMedicationWriter,
  PatientMedicationReqWriter,
};

enum class CreateReaderName
{
  PatientDemographicsReqReaderCft = 0,
  PhysiologicalAlarmContextReqReaderCft,
  TechnicalAlarmContextReqReaderCft,
  DSAMeasContextReqReaderCft,
  DSACalcContextReqReaderCft,
  DSASettContextReqReaderCft,
  EnumerationMeasContextReqReaderCft,
  EnumerationCalcContextReqReaderCft,
  EnumerationSettContextReqReaderCft,
  EnumerationSettObservedValueReqReaderCft,
  NumericMeasContextReqReaderCft,
  NumericCalcContextReqReaderCft,
  NumericSettContextReqReaderCft,
  NumericSettObservedValueReqReaderCft,
  RTSAMeasContextReqReaderCft,
  RTSACalcContextReqReaderCft,
  RTSASettContextReqReaderCft,
  TSAMeasContextReqReaderCft,
  TSACalcContextReqReaderCft,
  TSASettContextReqReaderCft,
  PatientIdentificationReqReader,
  DeviceDriverStateReqReaderCft,
  // TODO Decide if these are also CFT readers on Patient ID
  AllergyReader,
  DiagnosisReader,
  DxHistoryReader,
  PatientMedicationReader,
  PatientDemographicsReader,
};

class Parser
{
 public:
  friend class ParserUnitTest;
  Parser(int max_command_length, int max_response_length) :
      _database_connection(nullptr),
      _max_command_length(max_command_length),
      _max_response_length(max_response_length),
      _command_length(0),
      _response_length(0),
      _raw_command(0),
      _raw_response(0) {};
  virtual ~Parser() {};

  std::set<CreateWriterName> get_create_writer_name_list();
  std::set<CreateReaderName> get_create_reader_name_list();

  DicesRcDriver set_ice_id(const std::string& ice_id);
  std::string get_ice_id();

  virtual DicesRcDriver AllocateMessageBuffers();
  virtual DicesRcDriver PopulateDDSInstances() = 0;
  virtual DicesRcDriver SetICEID();
  virtual DicesRcDriver ParseCommand() = 0;
  virtual DicesRcDriver ParseResponse() = 0;
  virtual DicesRcDriver GetHandshakeCmd() = 0;
  virtual DicesRcDriver ShutdownParser() = 0;
  DicesRcDriver DeallocateMessageBuffers();

  DicesRcDriver get_raw_command(uint8_t* buffer, int buf_length);
  DicesRcDriver set_raw_response(const uint8_t* buffer, int buf_length);
  int get_command_length() { return _command_length; };
  int get_response_length() { return _response_length; };
  int get_max_command_length() { return _max_command_length; };
  int get_max_response_length() { return _max_response_length; };

  DicesRcDriver GetPatientIdentificationReqToPublish(ice::PatientIdentification** instance, int* index);
  DicesRcDriver GetPatientDemographicsReqToPublish(ice::PatientDemographics** instance, int* index);
  DicesRcDriver GetTechAlarmSignalToPublish(ice::AlarmSignal** instance, int* index);
  DicesRcDriver GetPhysAlarmSignalToPublish(ice::AlarmSignal** instance, int* index);
  DicesRcDriver GetInformationSignalToPublish(ice::InformationSignal** instance, int* index);
  DicesRcDriver GetReminderSignalToPublish(ice::ReminderSignal** instance, int* index);
  DicesRcDriver GetTechAlarmContextToPublish(ice::AlarmContext** instance, int* index);
  DicesRcDriver GetPhysAlarmContextToPublish(ice::AlarmContext** instance, int* index);
  DicesRcDriver GetDSAMeasContextToPublish(ice::DSAContext** instance, int* index);
  DicesRcDriver GetDSAMeasObservedValueToPublish(ice::DSAObservedValue** instance, int* index);
  DicesRcDriver GetDSACalcContextToPublish(ice::DSAContext** instance, int* index);
  DicesRcDriver GetDSACalcObservedValueToPublish(ice::DSAObservedValue** instance, int* index);
  DicesRcDriver GetDSASettContextToPublish(ice::DSAContext** instance, int* index);
  DicesRcDriver GetDSASettObservedValueToPublish(ice::DSAObservedValue** instance, int* index);
  DicesRcDriver GetEnumerationMeasContextToPublish(ice::EnumerationContext** instance, int* index);
  DicesRcDriver GetEnumerationMeasObservedValueToPublish(ice::EnumerationObservedValue** instance, int* index);
  DicesRcDriver GetEnumerationCalcContextToPublish(ice::EnumerationContext** instance, int* index);
  DicesRcDriver GetEnumerationCalcObservedValueToPublish(ice::EnumerationObservedValue** instance, int* index);
  DicesRcDriver GetEnumerationSettContextToPublish(ice::EnumerationContext** instance, int* index);
  DicesRcDriver GetEnumerationSettObservedValueToPublish(ice::EnumerationObservedValue** instance, int* index);
  DicesRcDriver GetMDSToPublish(ice::MDS** instance, int* index);
  DicesRcDriver GetVMDToPublish(ice::VMD** instance, int* index);
  DicesRcDriver GetNumericMeasContextToPublish(ice::NumericContext** instance, int* index);
  DicesRcDriver GetNumericMeasObservedValueToPublish(ice::NumericObservedValue** instance, int* index);
  DicesRcDriver GetNumericCalcContextToPublish(ice::NumericContext** instance, int* index);
  DicesRcDriver GetNumericCalcObservedValueToPublish(ice::NumericObservedValue** instance, int* index);
  DicesRcDriver GetNumericSettContextToPublish(ice::NumericContext** instance, int* index);
  DicesRcDriver GetNumericSettObservedValueToPublish(ice::NumericObservedValue** instance, int* index);
  DicesRcDriver GetRTSAMeasContextToPublish(ice::RTSAContext** instance, int* index);
  DicesRcDriver GetRTSAMeasObservedValueToPublish(ice::RTSAObservedValue** instance, int* index);
  DicesRcDriver GetRTSACalcContextToPublish(ice::RTSAContext** instance, int* index);
  DicesRcDriver GetRTSACalcObservedValueToPublish(ice::RTSAObservedValue** instance, int* index);
  DicesRcDriver GetRTSASettContextToPublish(ice::RTSAContext** instance, int* index);
  DicesRcDriver GetRTSASettObservedValueToPublish(ice::RTSAObservedValue** instance, int* index);
  DicesRcDriver GetTSAMeasContextToPublish(ice::TSAContext** instance, int* index);
  DicesRcDriver GetTSAMeasObservedValueToPublish(ice::TSAObservedValue** instance, int* index);
  DicesRcDriver GetTSACalcContextToPublish(ice::TSAContext** instance, int* index);
  DicesRcDriver GetTSACalcObservedValueToPublish(ice::TSAObservedValue** instance, int* index);
  DicesRcDriver GetTSASettContextToPublish(ice::TSAContext** instance, int* index);
  DicesRcDriver GetTSASettObservedValueToPublish(ice::TSAObservedValue** instance, int* index);
  DicesRcDriver GetPatientIdentificationToPublish(ice::PatientIdentification** instance, int* index);
  DicesRcDriver GetPatientDemographicsToPublish(ice::PatientDemographics** instance, int* index);
  DicesRcDriver GetAllergyToPublish(ice::Allergy** instance, int* index);
  DicesRcDriver GetDiagnosisToPublish(expr::Diagnosis** instance, int* index);
  DicesRcDriver GetDxHistoryToPublish(expr::DxHistory** instance, int* index);
  DicesRcDriver GetMedicationToPublish(expr::PatientMedication** instance, int* index);

  DicesRcDriver SetPatientIdentificationReqAsPublished(int index);
  DicesRcDriver SetPatientDemographicsReqAsPublished(int index);
  DicesRcDriver SetTechAlarmSignalAsPublished(int index);
  DicesRcDriver SetPhysAlarmSignalAsPublished(int index);
  DicesRcDriver SetInformationSignalAsPublished(int index);
  DicesRcDriver SetReminderSignalAsPublished(int index);
  DicesRcDriver SetTechAlarmContextAsPublished(int index);
  DicesRcDriver SetPhysAlarmContextAsPublished(int index);
  DicesRcDriver SetDSAMeasContextAsPublished(int index);
  DicesRcDriver SetDSAMeasObservedValueAsPublished(int index);
  DicesRcDriver SetDSACalcContextAsPublished(int index);
  DicesRcDriver SetDSACalcObservedValueAsPublished(int index);
  DicesRcDriver SetDSASettContextAsPublished(int index);
  DicesRcDriver SetDSASettObservedValueAsPublished(int index);
  DicesRcDriver SetEnumerationMeasContextAsPublished(int index);
  DicesRcDriver SetEnumerationMeasObservedValueAsPublished(int index);
  DicesRcDriver SetEnumerationCalcContextAsPublished(int index);
  DicesRcDriver SetEnumerationCalcObservedValueAsPublished(int index);
  DicesRcDriver SetEnumerationSettContextAsPublished(int index);
  DicesRcDriver SetEnumerationSettObservedValueAsPublished(int index);
  DicesRcDriver SetMDSAsPublished(int index);
  DicesRcDriver SetVMDAsPublished(int index);
  DicesRcDriver SetNumericMeasContextAsPublished(int index);
  DicesRcDriver SetNumericMeasObservedValueAsPublished(int index);
  DicesRcDriver SetNumericCalcContextAsPublished(int index);
  DicesRcDriver SetNumericCalcObservedValueAsPublished(int index);
  DicesRcDriver SetNumericSettContextAsPublished(int index);
  DicesRcDriver SetNumericSettObservedValueAsPublished(int index);
  DicesRcDriver SetRTSAMeasContextAsPublished(int index);
  DicesRcDriver SetRTSAMeasObservedValueAsPublished(int index);
  DicesRcDriver SetRTSACalcContextAsPublished(int index);
  DicesRcDriver SetRTSACalcObservedValueAsPublished(int index);
  DicesRcDriver SetRTSASettContextAsPublished(int index);
  DicesRcDriver SetRTSASettObservedValueAsPublished(int index);
  DicesRcDriver SetTSAMeasContextAsPublished(int index);
  DicesRcDriver SetTSAMeasObservedValueAsPublished(int index);
  DicesRcDriver SetTSACalcContextAsPublished(int index);
  DicesRcDriver SetTSACalcObservedValueAsPublished(int index);
  DicesRcDriver SetTSASettContextAsPublished(int index);
  DicesRcDriver SetTSASettObservedValueAsPublished(int index);
  DicesRcDriver SetPatientIdentificationAsPublished(int index);
  DicesRcDriver SetPatientDemographicsAsPublished(int index);
  DicesRcDriver SetAllergyAsPublished(int index);
  DicesRcDriver SetDiagnosisAsPublished(int index);
  DicesRcDriver SetDxHistoryAsPublished(int index);
  DicesRcDriver SetMedicationAsPublished(int index);

  DicesRcDriver AddPhysAlarmContextCommand(const ice::AlarmContext* instance);
  DicesRcDriver AddTechAlarmContextCommand(const ice::AlarmContext* instance);
  DicesRcDriver AddDSAMeasContextCommand(const ice::DSAContext* instance);
  DicesRcDriver AddDSACalcContextCommand(const ice::DSAContext* instance);
  DicesRcDriver AddDSASettContextCommand(const ice::DSAContext* instance);
  DicesRcDriver AddEnumerationMeasContextCommand(const ice::EnumerationContext* instance);
  DicesRcDriver AddEnumerationCalcContextCommand(const ice::EnumerationContext* instance);
  DicesRcDriver AddEnumerationSettContextCommand(const ice::EnumerationContext* instance);
  DicesRcDriver AddEnumerationSettObservedValueCommand(const ice::EnumerationObservedValue* instance);
  DicesRcDriver AddNumericMeasContextCommand(const ice::NumericContext* instance);
  DicesRcDriver AddNumericCalcContextCommand(const ice::NumericContext* instance);
  DicesRcDriver AddNumericSettContextCommand(const ice::NumericContext* instance);
  DicesRcDriver AddNumericSettObservedValueCommand(const ice::NumericObservedValue* instance);
  DicesRcDriver AddRTSAMeasContextCommand(const ice::RTSAContext* instance);
  DicesRcDriver AddRTSACalcContextCommand(const ice::RTSAContext* instance);
  DicesRcDriver AddRTSASettContextCommand(const ice::RTSAContext* instance);
  DicesRcDriver AddTSAMeasContextCommand(const ice::TSAContext* instance);
  DicesRcDriver AddTSACalcContextCommand(const ice::TSAContext* instance);
  DicesRcDriver AddTSASettContextCommand(const ice::TSAContext* instance);
  DicesRcDriver AddPatientIdentificationCommand(const ice::PatientIdentification* instance);
  DicesRcDriver AddDeviceDriverStateCommand(const docbox::DeviceDriverState* instance);

  DicesRcDriver AddAllergyCommand(const ice::Allergy *instance);

 protected:

  DicesRcDriver ConnectToDatabase(
    const std::string& database_name,
    const std::string& database_user,
    const std::string& database_password,
    const std::string& database_host);
  DicesRcDriver DisconnectFromDatabase();
  DicesRcDriver ReadFromDatabase();

  std::set<CreateWriterName> _create_writer_name_list;
  std::set<CreateReaderName> _create_reader_name_list;
  pqxx::connection* _database_connection;
  uint8_t* _raw_command;
  uint8_t* _raw_response;
  int _command_length;
  int _response_length;
  int _max_command_length;
  int _max_response_length;
  std::string _ice_id;

  std::vector<std::pair<DicesRcDriver, ice::PatientIdentification*>> _patient_identification_req_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::PatientDemographics*>> _patient_demographics_req_response_instance_list;

  std::vector<std::pair<DicesRcDriver, ice::AlarmSignal*>> _physiological_alarm_signal_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::AlarmSignal*>> _technical_alarm_signal_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::InformationSignal*>> _information_signal_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::ReminderSignal*>> _reminder_signal_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::AlarmContext*>> _physiological_alarm_context_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::AlarmContext*>> _technical_alarm_context_response_instance_list;

  std::vector<std::pair<DicesRcDriver, ice::DSAContext*>> _dsa_meas_context_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::DSAObservedValue*>> _dsa_meas_observed_value_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::DSAContext*>> _dsa_calc_context_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::DSAObservedValue*>> _dsa_calc_observed_value_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::DSAContext*>> _dsa_sett_context_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::DSAObservedValue*>> _dsa_sett_observed_value_response_instance_list;

  std::vector<std::pair<DicesRcDriver, ice::EnumerationContext*>> _enumeration_meas_context_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::EnumerationObservedValue*>> _enumeration_meas_observed_value_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::EnumerationContext*>> _enumeration_calc_context_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::EnumerationObservedValue*>> _enumeration_calc_observed_value_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::EnumerationContext*>> _enumeration_sett_context_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::EnumerationObservedValue*>> _enumeration_sett_observed_value_response_instance_list;

  std::vector<std::pair<DicesRcDriver, ice::MDS*>> _mds_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::VMD*>> _vmd_instance_list;

  std::vector<std::pair<DicesRcDriver, ice::NumericContext*>> _numeric_meas_context_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::NumericObservedValue*>> _numeric_meas_observed_value_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::NumericContext*>> _numeric_calc_context_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::NumericObservedValue*>> _numeric_calc_observed_value_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::NumericContext*>> _numeric_sett_context_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::NumericObservedValue*>> _numeric_sett_observed_value_response_instance_list;

  std::vector<std::pair<DicesRcDriver, ice::RTSAContext*>> _rtsa_meas_context_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::RTSAObservedValue*>> _rtsa_meas_observed_value_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::RTSAContext*>> _rtsa_calc_context_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::RTSAObservedValue*>> _rtsa_calc_observed_value_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::RTSAContext*>> _rtsa_sett_context_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::RTSAObservedValue*>> _rtsa_sett_observed_value_response_instance_list;

  std::vector<std::pair<DicesRcDriver, ice::TSAContext*>> _tsa_meas_context_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::TSAObservedValue*>> _tsa_meas_observed_value_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::TSAContext*>> _tsa_calc_context_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::TSAObservedValue*>> _tsa_calc_observed_value_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::TSAContext*>> _tsa_sett_context_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::TSAObservedValue*>> _tsa_sett_observed_value_response_instance_list;

  std::vector<std::pair<DicesRcDriver, ice::PatientIdentification*>> _patient_identification_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::PatientDemographics*>> _patient_demographics_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::Allergy*>> _allergy_response_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::Allergy*>> _allergy_req_response_instance_list;
  std::vector<std::pair<DicesRcDriver, expr::Diagnosis*>> _diagnosis_response_instance_list;
  std::vector<std::pair<DicesRcDriver, expr::DxHistory*>> _dxhistory_response_instance_list;
  std::vector<std::pair<DicesRcDriver, expr::PatientMedication*>> _patient_medication_response_instance_list;

  std::vector<std::pair<DicesRcDriver, ice::Allergy*>> _allergy_command_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::Allergy*>> _allergy_req_command_instance_list;
  std::vector<std::pair<DicesRcDriver, expr::Diagnosis*>> _diagnosis_req_command_instance_list;
  std::vector<std::pair<DicesRcDriver, expr::DxHistory*>> _dxhistory_req_command_instance_list;
  std::vector<std::pair<DicesRcDriver, expr::PatientMedication*>> _patient_medication_req_command_instance_list;

  std::vector<std::pair<DicesRcDriver, ice::AlarmContext*>> _physiological_alarm_context_req_command_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::AlarmContext*>> _technical_alarm_context_req_command_instance_list;

  std::vector<std::pair<DicesRcDriver, ice::DSAContext*>> _dsa_meas_context_req_command_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::DSAContext*>> _dsa_calc_context_req_command_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::DSAContext*>> _dsa_sett_context_req_command_instance_list;

  std::vector<std::pair<DicesRcDriver, ice::EnumerationContext*>> _enumeration_meas_context_req_command_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::EnumerationContext*>> _enumeration_calc_context_req_command_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::EnumerationContext*>> _enumeration_sett_context_req_command_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::EnumerationObservedValue*>> _enumeration_sett_observed_value_req_command_instance_list;

  std::vector<std::pair<DicesRcDriver, ice::NumericContext*>> _numeric_meas_context_req_command_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::NumericContext*>> _numeric_calc_context_req_command_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::NumericContext*>> _numeric_sett_context_req_command_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::NumericObservedValue*>> _numeric_sett_observed_value_req_command_instance_list;

  std::vector<std::pair<DicesRcDriver, ice::RTSAContext*>> _rtsa_meas_context_req_command_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::RTSAContext*>> _rtsa_calc_context_req_command_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::RTSAContext*>> _rtsa_sett_context_req_command_instance_list;

  std::vector<std::pair<DicesRcDriver, ice::TSAContext*>> _tsa_meas_context_req_command_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::TSAContext*>> _tsa_calc_context_req_command_instance_list;
  std::vector<std::pair<DicesRcDriver, ice::TSAContext*>> _tsa_sett_context_req_command_instance_list;

  std::vector<std::pair<DicesRcDriver, ice::PatientIdentification*>> _patient_identification_req_command_instance_list;
  std::vector<std::pair<DicesRcDriver, docbox::DeviceDriverState*>> _device_driver_state_req_command_instance_list;

 private:
  // Disallow use of implicitly generated member functions:
  Parser(const Parser& orig);
  Parser &operator=(const Parser& orig);

  DicesRcDriver ConvertPostgresByteaHexToICEINTU8(
    const std::string& str_value,
    ice::INTU8* value);
  DicesRcDriver ReadFromMDSTable();
  DicesRcDriver ReadFromVMDTable();
  DicesRcDriver ReadFromNumericTable();
  DicesRcDriver ParseNumericContextResultTuple(
    ice::NumericContext* instance,
    const pqxx::result::tuple& table_tuple);
  DicesRcDriver ParseNumericObservedValueResultTuple(
    ice::NumericObservedValue* instance,
    const pqxx::result::tuple& table_tuple);
  DicesRcDriver ReadFromEnumerationTable();
  DicesRcDriver ParseEnumerationContextResultTuple(
    ice::EnumerationContext* instance,
    const pqxx::result::tuple& table_tuple);
  DicesRcDriver ParseEnumerationObservedValueResultTuple(
    ice::EnumerationObservedValue* instance,
    const pqxx::result::tuple& table_tuple);
  DicesRcDriver ReadFromRTSATable();
  DicesRcDriver ParseRTSAContextResultTuple(
    ice::RTSAContext* instance,
    const pqxx::result::tuple& table_tuple);
  DicesRcDriver ParseRTSAObservedValueResultTuple(
    ice::RTSAObservedValue* instance,
    const pqxx::result::tuple& table_tuple);
  DicesRcDriver ReadFromAlarmsTable();
  DicesRcDriver ParseAlarmContextResultTuple(
    ice::AlarmContext* instance,
    const pqxx::result::tuple& table_tuple);
  DicesRcDriver ParseAlarmSignalResultTuple(
    ice::AlarmSignal* instance,
    const pqxx::result::tuple& table_tuple);
  DicesRcDriver ReadFromPatientIdentificationTable();
  DicesRcDriver ReadFromPatientIdentificationReqTable();
  DicesRcDriver ReadFromPatientDemographicsTable();
  DicesRcDriver ReadFromPatientDemographicsReqTable();
  DicesRcDriver ReadFromAllergyTable();
  DicesRcDriver ReadFromAllergyReqTable();
  DicesRcDriver ReadFromPatientMedicationTable();
  DicesRcDriver ReadFromPatientMedicationReqTable();
  DicesRcDriver ReadFromDxHistoryTable();
  DicesRcDriver ReadFromDxHistoryReqTable();
  DicesRcDriver ReadFromDiagnosisTable();
  DicesRcDriver ReadFromDiagnosisReqTable();

  DicesRcDriver ParseCSVToArray(
    std::vector<std::pair<ice::FLOATType, bool>>*dest,
    const std::string& src);
  DicesRcDriver ParseCSVToArray(
    std::vector<std::pair<ice::INT32, bool>>*dest,
    const std::string& src);
  DicesRcDriver ParseCSVToArray(
    std::vector<std::pair<ice::INTU32, bool>>*dest,
    const std::string& src);
  DicesRcDriver ParseCSVToArray(
    std::vector<std::pair<ice::INT16, bool>>*dest,
    const std::string& src);
  DicesRcDriver ParseCSVToArray(
    std::vector<std::pair<ice::INTU16, bool>>*dest,
    const std::string& src);
  DicesRcDriver ParseCSVToArray(
    std::vector<std::pair<std::string, bool>>*dest,
    const std::string& src);

  DicesRcDriver ParseCSVSequences(
    std::vector<std::pair<std::string, std::vector<unsigned int>>>*dest,
    const std::string& src);

  template <typename ICETYPE>
  DicesRcDriver GetInstanceToPublish(
    const std::vector<std::pair<DicesRcDriver, ICETYPE*>>& instance_list,
    ICETYPE** instance,
    int* index,
    const char* sfn);
  template <typename ICETYPE>
  DicesRcDriver SetInstanceAsPublished(
    std::vector<std::pair<DicesRcDriver, ICETYPE*>>* instance_list,
    int index,
    const char* sfn);
  template <typename ICETYPE>
  DicesRcDriver AddInstanceCommand(
    std::vector<std::pair<DicesRcDriver, ICETYPE*>>* instance_list,
    const ICETYPE* instance,
    const char* sfn);
};

#endif	/* PARSER_H */

