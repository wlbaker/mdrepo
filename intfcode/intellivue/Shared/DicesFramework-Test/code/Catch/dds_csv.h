#ifndef DDS_CSV_H
#define DDS_CSV_H

#include "dds-db-util.h"

#include "rc-base-app.h"
#include "base-logger.h"

#include "Utilities/DicesDDSUnionToString/uniontojson.h"
#include "Utilities/DicesOctetString/dices_octet_string.h"

#include <pqxx/pqxx>

//static const char* kSequenceDelimiter = ":";

std::string csv_n_nulls(pqxx::work* txn, int num)
{
  std::string result = "NULL";
  for (int ix = 0; ix < num - 1; ix++)
  {
    result += ", NULL";
  }
  return result;
}

std::string dds_to_csv(pqxx::work* txn, const unsigned char& field)
{
  return txn->quote(static_cast<unsigned int>(field));
}

std::string dds_to_csv(pqxx::work* txn, const ice::INT32& field)
{
  return txn->quote(field);
}

std::string dds_to_csv(pqxx::work* txn, const bool& field)
{
  return txn->quote(field);
}

std::string dds_to_csv(pqxx::work* txn, const float& field)
{
  return txn->quote(field);
}

std::string dds_to_csv(pqxx::work* txn, const DDS_Char* field)
{
  if (!field) return "NULL";
  return txn->quote(field);
}

std::string dds_to_csv(pqxx::work* txn, const DDS_StringSeq& field)
{
  std::string seq = field[0];
  for (int ix = 1; ix < field.length(); ix++)
  {
    seq += kSequenceDelimiter;
    seq += field[ix];
  }
  return txn->quote(seq);
}

// ****************
// **** common ****
// ****************

// Required field - ice::Timespec
std::string dds_to_csv(pqxx::work* txn, const ice::Timespec& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.seconds) + ", ";
  result += dds_to_csv(txn, field.nanoseconds);
  return result;
}

// Optional field - ice::Timespec
std::string dds_to_csv(pqxx::work* txn, const ice::Timespec* field_ptr)
{
  const int kNumCols = 2;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::Date
std::string dds_to_csv(pqxx::work* txn, const ice::Date& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.century) + ", ";
  result += dds_to_csv(txn, field.year) + ", ";
  result += dds_to_csv(txn, field.month) + ", ";
  result += dds_to_csv(txn, field.day);
  return result;
}

// Optional field - ice::Date
std::string dds_to_csv(pqxx::work* txn, const ice::Date* field_ptr)
{
  const int kNumCols = 4;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::HostId
std::string dds_to_csv(pqxx::work* txn, const ice::HostId& field)
{
  std::string result = "decode('";
  result += OctetArrayToHexString(const_cast<ice::OCTET*>(field), 6) + "', 'hex')";
  return result;
}

// Optional field - ice::HostId
std::string dds_to_csv(pqxx::work* txn, const ice::HostId* field_ptr)
{
  const int kNumCols = 1;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::GuidTimespec
std::string dds_to_csv(pqxx::work* txn, const ice::GuidTimespec& field)
{
  std::string result = "decode('";
  result += OctetArrayToHexString(const_cast<ice::OCTET*>(field.seconds), 4) + "', 'hex'), decode('";
  result += OctetArrayToHexString(const_cast<ice::OCTET*>(field.fraction), 2) + "', 'hex')";
  return result;
}

// Optional field - ice::GuidTimespec
std::string dds_to_csv(pqxx::work* txn, const ice::GuidTimespec* field_ptr)
{
  const int kNumCols = 2;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::GuidPrefix
std::string dds_to_csv(pqxx::work* txn, const ice::GuidPrefix& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.hostid) + ", ";
  result += dds_to_csv(txn, field.timestamp);
  return result;
}

// Optional field - ice::GuidPrefix
std::string dds_to_csv(pqxx::work* txn, const ice::GuidPrefix* field_ptr)
{
  const int kNumCols = 3;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::EntityId
std::string dds_to_csv(pqxx::work* txn, const ice::EntityId& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.kind_of_entity) + ", ";
  result += dds_to_csv(txn, field.entity_key);
  return result;
}

// Optional field - ice::EntityId
std::string dds_to_csv(pqxx::work* txn, const ice::EntityId* field_ptr)
{
  const int kNumCols = 2;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::GUID
std::string dds_to_csv(pqxx::work* txn, const ice::GUID& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.prefix) + ", ";
  result += dds_to_csv(txn, field.entity_id);
  return result;
}

// Optional field - ice::GUID
std::string dds_to_csv(pqxx::work* txn, const ice::GUID* field_ptr)
{
  const int kNumCols = 5;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// ice::Top
std::string dds_to_csv(pqxx::work* txn, const ice::Top& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.ice_id) + ", ";
  result += dds_to_csv(txn, field.handle) + ", ";
  result += dds_to_csv(txn, field.parent_handle) + ", ";
  result += dds_to_csv(txn, field.source_timestamp);
  return result;
}

// *****************
// **** commonc ****
// *****************

// Required field - ice::CT_decimal
std::string dds_to_csv(pqxx::work* txn, const ice::CT_decimal& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.value) + ", ";
  result += dds_to_csv(txn, field.presentation_precision);
  return result;
}

// Optional field - ice::CT_decimal
std::string dds_to_csv(pqxx::work* txn, const ice::CT_decimal* field_ptr)
{
  const int kNumCols = 2;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::Coding
std::string dds_to_csv(pqxx::work* txn, const ice::Coding& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.system) + ", ";
  result += dds_to_csv(txn, field.version) + ", ";
  result += dds_to_csv(txn, field.code_) + ", ";
  result += dds_to_csv(txn, field.display) + ", ";
  result += dds_to_csv(txn, field.user_selected);
  return result;
}

// Optional field - ice::Coding
std::string dds_to_csv(pqxx::work* txn, const ice::Coding* field_ptr)
{
  const int kNumCols = 5;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::CodeableConcept
std::string dds_to_csv(pqxx::work* txn, const ice::CodeableConcept& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.coding) + ", ";
  result += dds_to_csv(txn, field.text);
  return result;
}

// Optional field - ice::CodeableConcept
std::string dds_to_csv(pqxx::work* txn, const ice::CodeableConcept* field_ptr)
{
  const int kNumCols = 6;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::SimpleQuantity
std::string dds_to_csv(pqxx::work* txn, const ice::SimpleQuantity& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.value) + ", ";
  result += dds_to_csv(txn, field.unit) + ", ";
  result += dds_to_csv(txn, field.system) + ", ";
  result += dds_to_csv(txn, field.code_);
  return result;
}

// Optional field - ice::SimpleQuantity
std::string dds_to_csv(pqxx::work* txn, const ice::SimpleQuantity* field_ptr)
{
  const int kNumCols = 5;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::Quantity
std::string dds_to_csv(pqxx::work* txn, const ice::Quantity& field)
{
  std::string result = "";
  result += dds_to_csv(txn, static_cast<ice::SimpleQuantity>(field)) + ", ";
  result += dds_to_csv(txn, field.comparator);
  return result;
}

// Optional field - ice::Quantity
std::string dds_to_csv(pqxx::work* txn, const ice::Quantity* field_ptr)
{
  const int kNumCols = 6;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::Range
std::string dds_to_csv(pqxx::work* txn, const ice::Range& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.low) + ", ";
  result += dds_to_csv(txn, field.high);
  return result;
}

// Optional field - ice::Range
std::string dds_to_csv(pqxx::work* txn, const ice::Range* field_ptr)
{
  const int kNumCols = 10;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::Ratio
std::string dds_to_csv(pqxx::work* txn, const ice::Ratio& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.numerator) + ", ";
  result += dds_to_csv(txn, field.denominator);
  return result;
}

// Optional field - ice::Ratio
std::string dds_to_csv(pqxx::work* txn, const ice::Ratio* field_ptr)
{
  const int kNumCols = 12;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::Period
std::string dds_to_csv(pqxx::work* txn, const ice::Period& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.start) + ", ";
  result += dds_to_csv(txn, field.end);
  return result;
}

// Optional field - ice::Period
std::string dds_to_csv(pqxx::work* txn, const ice::Period* field_ptr)
{
  const int kNumCols = 2;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::EffectiveTime
std::string dds_to_csv(pqxx::work* txn, const ice::EffectiveTime& field)
{
  std::string result = "";
  UnionToJSON::EffectiveTimeToJSON(const_cast<ice::EffectiveTime*>(&field), &result);
  return txn->quote(result);
}

// Optional field - ice::EffectiveTime
std::string dds_to_csv(pqxx::work* txn, const ice::EffectiveTime* field_ptr)
{
  const int kNumCols = 1;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// *****************
// **** patdemo ****
// *****************

// Required field - ice::PatMeasure
std::string dds_to_csv(pqxx::work* txn, const ice::PatMeasure& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.value) + ", ";
  result += dds_to_csv(txn, field.m_unit);
  return result;
}

// Optional field - ice::PatMeasure
std::string dds_to_csv(pqxx::work* txn, const ice::PatMeasure* field_ptr)
{
  const int kNumCols = 2;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::PatientRace
std::string dds_to_csv(pqxx::work* txn, const ice::PatientRace& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.race_type) + ", ";
  result += dds_to_csv(txn, field.provenance);
  return result;
}

// Optional field - ice::PatientRace
std::string dds_to_csv(pqxx::work* txn, const ice::PatientRace* field_ptr)
{
  const int kNumCols = 2;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::PatientIdentification
// HACK rengland 2017 OCT 24
// PatientIdentification may be used as either a top-level object or as a field
// within another object.  Our recording service and translation table tool databases
// currently do not record or handle the inherited Top fields within the
// PatientIdentification instances within parent objects, so I need to only concern
// myself with those fields when the PatientIdentification instance is top-level.
std::string dds_to_csv(pqxx::work* txn, const ice::PatientIdentification& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.given_name) + ", ";
  result += dds_to_csv(txn, field.family_name) + ", ";
  result += dds_to_csv(txn, field.middle_name) + ", ";
  result += dds_to_csv(txn, field.date_of_birth) + ", ";
  result += dds_to_csv(txn, field.patient_id) + ", ";
  result += dds_to_csv(txn, field.patient_id_provenance) + ", ";
  result += dds_to_csv(txn, field.verified) + ", ";
  result += dds_to_csv(txn, field.pat_admit_state) + ", ";
  result += dds_to_csv(txn, field.pat_episode_id) + ", ";
  result += dds_to_csv(txn, field.episode_start);
  return result;
}

// Optional field - ice::PatientIdentification
std::string dds_to_csv(pqxx::work* txn, const ice::PatientIdentification* field_ptr)
{
  const int kNumCols = 19;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Top-level object - ice::PatientIdentification
std::string dds_to_csv(pqxx::work* txn, const ice::PatientIdentification& field, bool toplevel)
{
  std::string result = "";
  if (toplevel) result += dds_to_csv(txn, static_cast<ice::Top>(field)) + ", ";
  result += dds_to_csv(txn, field);
  return result;
}

// Top-level object - ice::PatientIdentificationError
std::string dds_to_csv(pqxx::work* txn, const ice::PatientIdentificationError& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.patient_id) + ", ";
  result += dds_to_csv(txn, field.provenance) + ", ";
  result += dds_to_csv(txn, field.pat_episode_id) + ", ";
  result += dds_to_csv(txn, field.error);
  return result;
}

// Required field - ice::NeonatalPatientInfo
std::string dds_to_csv(pqxx::work* txn, const ice::NeonatalPatientInfo& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.gestational_age) + ", ";
  result += dds_to_csv(txn, field.patient_birth_length) + ", ";
  result += dds_to_csv(txn, field.patient_birth_weight) + ", ";
  result += dds_to_csv(txn, field.patient_head_circumference) + ", ";
  result += dds_to_csv(txn, field.mother_patient_id) + ", ";
  result += dds_to_csv(txn, field.mother_name);
  return result;
}

// Optional field - ice::NeonatalPatientInfo
std::string dds_to_csv(pqxx::work* txn, const ice::NeonatalPatientInfo* field_ptr)
{
  const int kNumCols = 28;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Top-level object - ice::PatientDemographics
std::string dds_to_csv(pqxx::work* txn, const ice::PatientDemographics& field)
{
  std::string result = "";
  result += dds_to_csv(txn, static_cast<ice::Top>(field)) + ", ";
  result += dds_to_csv(txn, field.sex) + ", ";
  result += dds_to_csv(txn, field.gender) + ", ";
  result += dds_to_csv(txn, field.race) + ", ";
  result += dds_to_csv(txn, field.patient_type) + ", ";
  result += dds_to_csv(txn, field.chronological_age) + ", ";
  result += dds_to_csv(txn, field.patient_height) + ", ";
  result += dds_to_csv(txn, field.patient_weight) + ", ";
  result += dds_to_csv(txn, field.neonatal);
  return result;
}

// *********************
// **** diagnostics ****
// *********************

// Required field - ice::Specimen
std::string dds_to_csv(pqxx::work* txn, const ice::Specimen& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.id) + ", ";
  result += dds_to_csv(txn, field.type) + ", ";
  result += dds_to_csv(txn, field.collected_time) + ", ";
  result += dds_to_csv(txn, field.received_time) + ", ";
  result += dds_to_csv(txn, field.registered_time);
  return result;
}

// Optional field - ice::Specimen
std::string dds_to_csv(pqxx::work* txn, const ice::Specimen* field_ptr)
{
  const int kNumCols = 10;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::ObservationValue
std::string dds_to_csv(pqxx::work* txn, const ice::ObservationValue& field)
{
  std::string result = "";
  UnionToJSON::ObservationValueToJSON(const_cast<ice::ObservationValue*>(&field), &result);
  return txn->quote(result);
}

// Optional field - ice::ObservationValue
std::string dds_to_csv(pqxx::work* txn, const ice::ObservationValue* field_ptr)
{
  const int kNumCols = 1;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::ReferenceRange
std::string dds_to_csv(pqxx::work* txn, const ice::ReferenceRange& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.low) + ", ";
  result += dds_to_csv(txn, field.high) + ", ";
  result += dds_to_csv(txn, field.type) + ", ";
  result += dds_to_csv(txn, field.age) + ", ";
  result += dds_to_csv(txn, field.text);
  return result;
}

// Optional field - ice::ReferenceRange
std::string dds_to_csv(pqxx::work* txn, const ice::ReferenceRange* field_ptr)
{
  const int kNumCols = 27;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::ObservationResult
std::string dds_to_csv(pqxx::work* txn, const ice::ObservationResult& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.code_) + ", ";
  result += dds_to_csv(txn, field.value) + ", ";
  result += dds_to_csv(txn, field.data_absent_reason) + ", ";
  result += dds_to_csv(txn, field.interpretation) + ", ";
  result += dds_to_csv(txn, field.reference_range);
  return result;
}

// Optional field - ice::ObservationResult
std::string dds_to_csv(pqxx::work* txn, const ice::ObservationResult* field_ptr)
{
  const int kNumCols = 40;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::Performer
std::string dds_to_csv(pqxx::work* txn, const ice::Performer& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.id) + ", ";
  result += dds_to_csv(txn, field.name) + ", ";
  result += dds_to_csv(txn, field.role);
  return result;
}

// Optional field - ice::Performer
std::string dds_to_csv(pqxx::work* txn, const ice::Performer* field_ptr)
{
  const int kNumCols = 3;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Required field - ice::PerformerSeq
std::string dds_to_csv(pqxx::work* txn, const ice::PerformerSeq& field)
{
  std::string id = field[0].id;
  std::string name = field[0].name;
  std::string role = std::to_string(field[0].role);
  for (int ix = 1; ix < field.length(); ix++)
  {
    id += kSequenceDelimiter;
    id += field[ix].id;
    name += kSequenceDelimiter;
    name += field[ix].name;
    role += kSequenceDelimiter;
    role += std::to_string(field[ix].role);
  }
  std::string result = "";
  result += txn->quote(id) + ", ";
  result += txn->quote(name) + ", ";
  result += txn->quote(role);
  return result;
}

// Optional field - ice::PerformerSeq
std::string dds_to_csv(pqxx::work* txn, const ice::PerformerSeq* field_ptr)
{
  const int kNumCols = 3;
  if (!field_ptr) return csv_n_nulls(txn, kNumCols);
  return dds_to_csv(txn, *field_ptr);
}

// Top-level object - ice::Observation
std::string dds_to_csv(pqxx::work* txn, const ice::Observation& field)
{
  std::string result = "";
  result += dds_to_csv(txn, static_cast<ice::Top>(field)) + ", ";
  result += dds_to_csv(txn, field.report_id) + ", ";
  result += dds_to_csv(txn, field.id) + ", ";
  result += dds_to_csv(txn, field.observation_number) + ", ";
  result += dds_to_csv(txn, field.component_count) + ", ";
  result += dds_to_csv(txn, field.order_id) + ", ";
  result += dds_to_csv(txn, field.status) + ", ";
  result += dds_to_csv(txn, field.category) + ", ";
  result += dds_to_csv(txn, field.effective) + ", ";
  result += dds_to_csv(txn, field.issued) + ", ";
  result += dds_to_csv(txn, field.subject) + ", ";
  result += dds_to_csv(txn, field.method) + ", ";
  result += dds_to_csv(txn, field.specimen) + ", ";
  result += dds_to_csv(txn, field.result);
  return result;
}

// Top-level object - ice::ObservationComponent
std::string dds_to_csv(pqxx::work* txn, const ice::ObservationComponent& field)
{
  std::string result = "";
  result += dds_to_csv(txn, static_cast<ice::Top>(field)) + ", ";
  result += dds_to_csv(txn, field.observation_id) + ", ";
  result += dds_to_csv(txn, field.component_number) + ", ";
  result += dds_to_csv(txn, field.value);
  return result;
}

// Top-level object - ice::DiagnosticReport
std::string dds_to_csv(pqxx::work* txn, const ice::DiagnosticReport& field)
{
  std::string result = "";
  result += dds_to_csv(txn, static_cast<ice::Top>(field)) + ", ";
  result += dds_to_csv(txn, field.id) + ", ";
  result += dds_to_csv(txn, field.observation_count) + ", ";
  result += dds_to_csv(txn, field.status) + ", ";
  result += dds_to_csv(txn, field.category) + ", ";
  result += dds_to_csv(txn, field.code_) + ", ";
  result += dds_to_csv(txn, field.subject) + ", ";
  result += dds_to_csv(txn, field.encounter_id) + ", ";
  result += dds_to_csv(txn, field.effective) + ", ";
  result += dds_to_csv(txn, field.issued) + ", ";
  result += dds_to_csv(txn, field.performer) + ", ";
  result += dds_to_csv(txn, field.ordering_doctor_specialty);
  return result;
}

// **************
// **** expr ****
// **************

// Top-level object - expr::Diagnosis
std::string dds_to_csv(pqxx::work* txn, const expr::Diagnosis& field)
{
  std::string result = "";
  result += dds_to_csv(txn, static_cast<ice::Top>(field)) + ", ";
  result += dds_to_csv(txn, field.diagnosis) + ", ";
  result += dds_to_csv(txn, field.procedure_list) + ", ";
  result += dds_to_csv(txn, field.physician) + ", ";
  result += dds_to_csv(txn, field.patient_identification);
  return result;
}

// Top-level object - expr::DxHistory
std::string dds_to_csv(pqxx::work* txn, const expr::DxHistory& field)
{
  std::string result = "";
  result += dds_to_csv(txn, static_cast<ice::Top>(field)) + ", ";
  result += dds_to_csv(txn, field.health_problem) + ", ";
  result += dds_to_csv(txn, field.recent_procedure) + ", ";
  result += dds_to_csv(txn, field.patient_identification) + ", ";
  result += dds_to_csv(txn, field.problem_count) + ", ";
  result += dds_to_csv(txn, field.problem_list) + ", ";
  result += dds_to_csv(txn, field.recent_procedures);
  return result;
}

// Required field - expr::Medication
std::string dds_to_csv(pqxx::work* txn, const expr::Medication& field)
{
  std::string result = "";
  result += dds_to_csv(txn, field.name) + ", ";
  result += dds_to_csv(txn, field.dose);
  return result;
}

// Required field - expr::MedicationList
std::string dds_to_csv(pqxx::work* txn, const expr::MedicationList& field)
{
  std::string name = field[0].name;
  std::string dose = field[0].dose;
  for (int ix = 1; ix < field.length(); ix++)
  {
    name += kSequenceDelimiter;
    name += field[ix].name;
    dose += kSequenceDelimiter;
    dose += field[ix].dose;
  }
  std::string result = "";
  result += txn->quote(name) + ", ";
  result += txn->quote(dose);
  return result;
}

// Top-level object - expr::PatientMedication
std::string dds_to_csv(pqxx::work* txn, const expr::PatientMedication& field)
{
  std::string result = "";
  result += dds_to_csv(txn, static_cast<ice::Top>(field)) + ", ";
  result += dds_to_csv(txn, field.patient_identification) + ", ";
  result += dds_to_csv(txn, field.medication_count) + ", ";
  result += dds_to_csv(txn, field.medication_list);
  return result;
}

#endif // DDS_CSV_H
