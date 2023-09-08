/*
 * File:   bus_comm.h
 * Author: Robert England
 *
 * Created on November 17, 2014
 * Last Modified on November 17, 2014
 */

#ifndef BUS_COMM_H
#define	BUS_COMM_H

#include <vector>
#include "dices_device_driver_status_handler.h"

enum class DicesRcDriver;
class Parser;

class DDSDomainParticipant;
class DDSPublisher;
class DDSSubscriber;

namespace ice
{
  class PatientIdentificationDataWriter;
  class PatientDemographicsDataWriter;

  class AlarmSignalDataWriter;
  class InformationSignalDataWriter;
  class ReminderSignalDataWriter;
  class AlarmContextDataWriter;

  class DSAContextDataWriter;
  class DSAObservedValueDataWriter;

  class EnumerationContextDataWriter;
  class EnumerationObservedValueDataWriter;

  class MDSDataWriter;
  class VMDDataWriter;

  class NumericContextDataWriter;
  class NumericObservedValueDataWriter;

  class RTSAContextDataWriter;
  class RTSAObservedValueDataWriter;

  class TSAContextDataWriter;
  class TSAObservedValueDataWriter;

  class AllergyDataWriter;
  class AllergyDataReader;

  class PatientDemographicsDataReader;

  class AlarmContextDataReader;

  class DSAContextDataReader;

  class EnumerationContextDataReader;
  class EnumerationObservedValueDataReader;

  class NumericContextDataReader;
  class NumericObservedValueDataReader;

  class RTSAContextDataReader;

class TSAContextDataReader;

class PatientIdentificationDataReader;
}

namespace expr
{
class DiagnosisDataWriter;
class DxHistoryDataWriter;
class PatientMedicationDataWriter;
}

namespace docbox
{
class DeviceDriverStateDataReader;
}

class BusComm
{
 public:
  BusComm(Parser* parser);
  virtual ~BusComm() {};

  DicesRcDriver InitDDSObjects();
  DicesRcDriver Associate();
  DicesRcDriver ReadFromBus();
  DicesRcDriver WriteToBus();
  DicesRcDriver ShutdownDDSObjects();
  DicesRcDriver PublishDeviceDriverStateError();

 private:
  // Disallow use of implicitly generated member functions:
  BusComm(const BusComm& orig);
  BusComm &operator=(const BusComm& orig);

  DicesRcDriver SetContentFilters();

  Parser* _parser;

  DicesDeviceDriverStatusHandler _driver_status_handler;

  DDSDomainParticipant* _participant;
  DDSPublisher* _publisher;
  DDSSubscriber* _subscriber;

  ice::PatientIdentificationDataWriter* _patient_identification_req_data_writer;
  ice::PatientDemographicsDataWriter* _patient_demographics_req_data_writer;

  ice::AlarmSignalDataWriter* _physiological_alarm_signal_data_writer;
  ice::AlarmSignalDataWriter* _technical_alarm_signal_data_writer;
  ice::InformationSignalDataWriter* _information_signal_data_writer;
  ice::ReminderSignalDataWriter* _reminder_signal_data_writer;
  ice::AlarmContextDataWriter* _physiological_alarm_context_data_writer;
  ice::AlarmContextDataWriter* _technical_alarm_context_data_writer;

  ice::DSAContextDataWriter* _dsa_meas_context_data_writer;
  ice::DSAObservedValueDataWriter* _dsa_meas_observed_value_data_writer;
  ice::DSAContextDataWriter* _dsa_calc_context_data_writer;
  ice::DSAObservedValueDataWriter* _dsa_calc_observed_value_data_writer;
  ice::DSAContextDataWriter* _dsa_sett_context_data_writer;
  ice::DSAObservedValueDataWriter* _dsa_sett_observed_value_data_writer;

  ice::EnumerationContextDataWriter* _enumeration_meas_context_data_writer;
  ice::EnumerationObservedValueDataWriter* _enumeration_meas_observed_value_data_writer;
  ice::EnumerationContextDataWriter* _enumeration_calc_context_data_writer;
  ice::EnumerationObservedValueDataWriter* _enumeration_calc_observed_value_data_writer;
  ice::EnumerationContextDataWriter* _enumeration_sett_context_data_writer;
  ice::EnumerationObservedValueDataWriter* _enumeration_sett_observed_value_data_writer;

  ice::MDSDataWriter* _mds_data_writer;
  ice::VMDDataWriter* _vmd_data_writer;

  ice::NumericContextDataWriter* _numeric_meas_context_data_writer;
  ice::NumericObservedValueDataWriter* _numeric_meas_observed_value_data_writer;
  ice::NumericContextDataWriter* _numeric_calc_context_data_writer;
  ice::NumericObservedValueDataWriter* _numeric_calc_observed_value_data_writer;
  ice::NumericContextDataWriter* _numeric_sett_context_data_writer;
  ice::NumericObservedValueDataWriter* _numeric_sett_observed_value_data_writer;

  ice::RTSAContextDataWriter* _rtsa_meas_context_data_writer;
  ice::RTSAObservedValueDataWriter* _rtsa_meas_observed_value_data_writer;
  ice::RTSAContextDataWriter* _rtsa_calc_context_data_writer;
  ice::RTSAObservedValueDataWriter* _rtsa_calc_observed_value_data_writer;
  ice::RTSAContextDataWriter* _rtsa_sett_context_data_writer;
  ice::RTSAObservedValueDataWriter* _rtsa_sett_observed_value_data_writer;

  ice::TSAContextDataWriter* _tsa_meas_context_data_writer;
  ice::TSAObservedValueDataWriter* _tsa_meas_observed_value_data_writer;
  ice::TSAContextDataWriter* _tsa_calc_context_data_writer;
  ice::TSAObservedValueDataWriter* _tsa_calc_observed_value_data_writer;
  ice::TSAContextDataWriter* _tsa_sett_context_data_writer;
  ice::TSAObservedValueDataWriter* _tsa_sett_observed_value_data_writer;

  ice::PatientIdentificationDataWriter* _patient_identification_data_writer;
  ice::PatientDemographicsDataWriter* _patient_demographics_data_writer;
  ice::PatientDemographicsDataWriter* _patient_demographics_data_req_writer;
  ice::AllergyDataWriter* _allergy_data_writer;
  ice::AllergyDataWriter* _allergy_data_req_writer;
  expr::DiagnosisDataWriter* _diagnosis_data_writer;
  expr::DiagnosisDataWriter* _diagnosis_data_req_writer;
  expr::DxHistoryDataWriter* _dxhistory_data_writer;
  expr::DxHistoryDataWriter* _dxhistory_data_req_writer;
  expr::PatientMedicationDataWriter* _patient_medication_data_writer;
  expr::PatientMedicationDataWriter* _patient_medication_data_req_writer;

  ice::PatientDemographicsDataReader* _patient_demographics_req_data_reader;
  ice::AllergyDataReader *_allergy_data_reader;

  ice::AlarmContextDataReader* _physiological_alarm_context_req_data_reader;
  ice::AlarmContextDataReader* _technical_alarm_context_req_data_reader;

  ice::DSAContextDataReader* _dsa_meas_context_req_data_reader;
  ice::DSAContextDataReader* _dsa_calc_context_req_data_reader;
  ice::DSAContextDataReader* _dsa_sett_context_req_data_reader;

  ice::EnumerationContextDataReader* _enumeration_meas_context_req_data_reader;
  ice::EnumerationContextDataReader* _enumeration_calc_context_req_data_reader;
  ice::EnumerationContextDataReader* _enumeration_sett_context_req_data_reader;
  ice::EnumerationObservedValueDataReader* _enumeration_sett_observed_value_req_data_reader;

  ice::NumericContextDataReader* _numeric_meas_context_req_data_reader;
  ice::NumericContextDataReader* _numeric_calc_context_req_data_reader;
  ice::NumericContextDataReader* _numeric_sett_context_req_data_reader;
  ice::NumericObservedValueDataReader* _numeric_sett_observed_value_req_data_reader;

  ice::RTSAContextDataReader* _rtsa_meas_context_req_data_reader;
  ice::RTSAContextDataReader* _rtsa_calc_context_req_data_reader;
  ice::RTSAContextDataReader* _rtsa_sett_context_req_data_reader;

  ice::TSAContextDataReader* _tsa_meas_context_req_data_reader;
  ice::TSAContextDataReader* _tsa_calc_context_req_data_reader;
  ice::TSAContextDataReader* _tsa_sett_context_req_data_reader;

  ice::PatientIdentificationDataReader* _patient_identification_req_data_reader;

  docbox::DeviceDriverStateDataReader* _device_driver_state_req_data_reader;
};

#endif	/* BUS_COMM_H */

