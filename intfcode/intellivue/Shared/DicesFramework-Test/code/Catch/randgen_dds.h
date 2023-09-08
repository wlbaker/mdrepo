#ifndef RANDGEN_DDS_H
#define RANDGEN_DDS_H

#include "dds-db-util.h"

#include "rc-base-app.h"
#include "base-logger.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QStringList>
#include <QVariant>

static const char* kSequenceDelimiter = ":";

// Use this a lot for optionals
bool coinflip()
{
  return (rand() % 2) == 1;
}

void rand_gen(unsigned char* field)
{
  REQUIRE(field);
  *field = static_cast<unsigned char>(rand() % 256);
}

void rand_gen(ice::INT32* field)
{
  REQUIRE(field);
  *field = rand();
}

void rand_gen(ice::INTU16* field)
{
  REQUIRE(field);
  *field = rand() % 32768;
}

void rand_gen(bool* field)
{
  REQUIRE(field);
  *field = coinflip();
}

void rand_gen(float* field)
{
  REQUIRE(field);
  *field = static_cast<float>(rand()) / static_cast<float>(rand());
}

void rand_gen(DDS_Char** field, size_t max_len)
{
  REQUIRE(field);
  size_t len = rand() % max_len;
  for (int ix = 0; ix < max_len; ix++)
  {
    // TODO rengland 11 AUG 2017
    // This currently only uses capital letters.  I was having issues getting the
    // tests to work properly with some of the symbol characters; we should evaluate
    // if any of these issues imply deeper problems.
    (*field)[ix] = rand() % 26 + 65;
  }
  (*field)[len] = '\0';
  (*field)[max_len] = '\0';
}

void rand_gen(DDS_Char** field, size_t max_len, bool optional)
{
  REQUIRE(field);
  if (optional)
  {
    if (coinflip())
    {
      *field = nullptr;
      return;
    }
    *field = DDS::String_alloc(max_len);
    REQUIRE(*field);
  }
  rand_gen(field, max_len);
}

void rand_gen(DDS_StringSeq* field, size_t max_len)
{
  // Magic number, can't find a coded max sequence length anywhere so
  // I'm (rengland) using DDS' default max.
  static const DDS_Long kMaxStrings = 100;
  REQUIRE(field != nullptr);
  DDS_Long seq_len = static_cast<DDS_Long>(rand() % kMaxStrings + 1);
  REQUIRE(field->ensure_length(seq_len, kMaxStrings));
  for (int ix = 0; ix < seq_len; ix++)
  {
    (*field)[ix] = DDS::String_alloc(max_len);
    REQUIRE((*field)[ix]);
    rand_gen(&(*field)[ix], max_len);
  }
}

// *****************
// **** common ****
// *****************

// Required field - ice::Date
void rand_gen(ice::Date* field)
{
  REQUIRE(field != nullptr);
  rand_gen(&field->century);
  rand_gen(&field->year);
  rand_gen(&field->month);
  rand_gen(&field->day);
}

// Optional field - ice::Date
void rand_gen(ice::Date** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::Date*>(DDS::Heap_malloc(sizeof (ice::Date)));
    REQUIRE(*field_ptr);
    rand_gen(*field_ptr);
  }
}

// Required field - ice::Timespec
void rand_gen(ice::Timespec* field)
{
  REQUIRE(field != nullptr);
  rand_gen(&field->seconds);
  rand_gen(&field->nanoseconds);
}

// Optional field - ice::Timespec
void rand_gen(ice::Timespec** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::Timespec*>(DDS::Heap_malloc(sizeof (ice::Timespec)));
    REQUIRE(*field_ptr);
    rand_gen(*field_ptr);
  }
}

// Required field - ice::CT_decimal
void rand_gen(ice::CT_decimal* field)
{
  REQUIRE(field != nullptr);
  rand_gen(&field->value);
  rand_gen(&field->presentation_precision);
}

// Optional field - ice::CT_decimal
void rand_gen(ice::CT_decimal** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::CT_decimal*>(DDS::Heap_malloc(sizeof (ice::CT_decimal)));
    REQUIRE(*field_ptr);
    rand_gen(*field_ptr);
  }
}

// Required field - ice::Coding
void rand_gen(ice::Coding* field)
{
  REQUIRE(field != nullptr);
  rand_gen(&field->system, ice::MAXLEN_CT_URI);
  rand_gen(&field->version, ice::MEDIUM_STRING_LEN);
  rand_gen(&field->code_, ice::MAXLEN_CT_CODE);
  rand_gen(&field->display, ice::MEDIUM_STRING_LEN);
  field->user_selected = static_cast<ice::CT_boolean>(coinflip());
}

// Optional field - ice::Coding
void rand_gen(ice::Coding** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::Coding*>(DDS::Heap_malloc(sizeof (ice::Coding)));
    REQUIRE(*field_ptr);
    (*field_ptr)->system = DDS::String_alloc(ice::MAXLEN_CT_URI);
    REQUIRE((*field_ptr)->system);
    (*field_ptr)->version = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->version);
    (*field_ptr)->code_ = DDS::String_alloc(ice::MAXLEN_CT_CODE);
    REQUIRE((*field_ptr)->code_);
    (*field_ptr)->display = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->display);
    rand_gen(*field_ptr);
  }
}

// Required field - ice::CodeableConcept
void rand_gen(ice::CodeableConcept* field)
{
  REQUIRE(field != nullptr);
  rand_gen(&field->coding);
  rand_gen(&field->text, ice::LONGLONG_STRING_LEN);
}

// Optional field - ice::CodeableConcept
void rand_gen(ice::CodeableConcept** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::CodeableConcept*>(DDS::Heap_malloc(sizeof (ice::CodeableConcept)));
    REQUIRE(*field_ptr);
    (*field_ptr)->coding.system = DDS::String_alloc(ice::MAXLEN_CT_URI);
    REQUIRE((*field_ptr)->coding.system);
    (*field_ptr)->coding.version = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->coding.version);
    (*field_ptr)->coding.code_ = DDS::String_alloc(ice::MAXLEN_CT_CODE);
    REQUIRE((*field_ptr)->coding.code_);
    (*field_ptr)->coding.display = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->coding.display);
    (*field_ptr)->text = DDS::String_alloc(ice::LONGLONG_STRING_LEN);
    REQUIRE((*field_ptr)->text);
    rand_gen(*field_ptr);
  }
}

// Required field - ice::SimpleQuantity
void rand_gen(ice::SimpleQuantity* field)
{
  REQUIRE(field != nullptr);
  rand_gen(&field->value);
  rand_gen(&field->unit, ice::MEDIUM_STRING_LEN);
  rand_gen(&field->system, ice::MAXLEN_CT_URI);
  rand_gen(&field->code_, ice::MAXLEN_CT_CODE);
}

// Optional field - ice::SimpleQuantity
void rand_gen(ice::SimpleQuantity** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::SimpleQuantity*>(DDS::Heap_malloc(sizeof (ice::SimpleQuantity)));
    REQUIRE(*field_ptr);
    (*field_ptr)->unit = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->unit);
    (*field_ptr)->system = DDS::String_alloc(ice::MAXLEN_CT_URI);
    REQUIRE((*field_ptr)->system);
    (*field_ptr)->code_ = DDS::String_alloc(ice::MAXLEN_CT_CODE);
    REQUIRE((*field_ptr)->code_);
    rand_gen(*field_ptr);
  }
}

// Required field - ice::Quantity
void rand_gen(ice::Quantity* field)
{
  REQUIRE(field != nullptr);
  rand_gen(static_cast<ice::SimpleQuantity*>(field));
  rand_gen(&field->comparator, ice::TINY_STRING_LEN);
}

// Optional field - ice::Quantity
void rand_gen(ice::Quantity** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::Quantity*>(DDS::Heap_malloc(sizeof (ice::Quantity)));
    REQUIRE(*field_ptr);
    (*field_ptr)->unit = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->unit);
    (*field_ptr)->system = DDS::String_alloc(ice::MAXLEN_CT_URI);
    REQUIRE((*field_ptr)->system);
    (*field_ptr)->code_ = DDS::String_alloc(ice::MAXLEN_CT_CODE);
    REQUIRE((*field_ptr)->code_);
    (*field_ptr)->comparator = DDS::String_alloc(ice::TINY_STRING_LEN);
    REQUIRE((*field_ptr)->comparator);
    rand_gen(*field_ptr);
  }
}

// Required field - ice::Range
void rand_gen(ice::Range* field)
{
  REQUIRE(field != nullptr);
  rand_gen(&field->low);
  rand_gen(&field->high);
}

// Optional field - ice::Range
void rand_gen(ice::Range** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::Range*>(DDS::Heap_malloc(sizeof (ice::Range)));
    REQUIRE(*field_ptr);
    (*field_ptr)->low.unit = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->low.unit);
    (*field_ptr)->low.system = DDS::String_alloc(ice::MAXLEN_CT_URI);
    REQUIRE((*field_ptr)->low.system);
    (*field_ptr)->low.code_ = DDS::String_alloc(ice::MAXLEN_CT_CODE);
    REQUIRE((*field_ptr)->low.code_);
    (*field_ptr)->high.unit = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->high.unit);
    (*field_ptr)->high.system = DDS::String_alloc(ice::MAXLEN_CT_URI);
    REQUIRE((*field_ptr)->high.system);
    (*field_ptr)->high.code_ = DDS::String_alloc(ice::MAXLEN_CT_CODE);
    REQUIRE((*field_ptr)->high.code_);
    rand_gen(*field_ptr);
  }
}

// Required field - ice::Ratio
void rand_gen(ice::Ratio* field)
{
  REQUIRE(field != nullptr);
  rand_gen(&field->numerator);
  rand_gen(&field->denominator);
}

// Optional field - ice::Ratio
void rand_gen(ice::Ratio** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::Ratio*>(DDS::Heap_malloc(sizeof (ice::Ratio)));
    REQUIRE(*field_ptr);
    (*field_ptr)->numerator.unit = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->numerator.unit);
    (*field_ptr)->numerator.system = DDS::String_alloc(ice::MAXLEN_CT_URI);
    REQUIRE((*field_ptr)->numerator.system);
    (*field_ptr)->numerator.code_ = DDS::String_alloc(ice::MAXLEN_CT_CODE);
    REQUIRE((*field_ptr)->numerator.code_);
    (*field_ptr)->numerator.comparator = DDS::String_alloc(ice::TINY_STRING_LEN);
    REQUIRE((*field_ptr)->numerator.comparator);
    (*field_ptr)->denominator.unit = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->denominator.unit);
    (*field_ptr)->denominator.system = DDS::String_alloc(ice::MAXLEN_CT_URI);
    REQUIRE((*field_ptr)->denominator.system);
    (*field_ptr)->denominator.code_ = DDS::String_alloc(ice::MAXLEN_CT_CODE);
    REQUIRE((*field_ptr)->denominator.code_);
    (*field_ptr)->denominator.comparator = DDS::String_alloc(ice::TINY_STRING_LEN);
    REQUIRE((*field_ptr)->denominator.comparator);
    rand_gen(*field_ptr);
  }
}

// Required field - ice::Period
void rand_gen(ice::Period* field)
{
  REQUIRE(field != nullptr);
  rand_gen(&field->start, ice::MAXLEN_CT_DATETIME, true);
  rand_gen(&field->end, ice::MAXLEN_CT_DATETIME, true);
}

// Optional field - ice::Period
void rand_gen(ice::Period** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::Period*>(DDS::Heap_malloc(sizeof (ice::Period)));
    REQUIRE(*field_ptr);
    rand_gen(*field_ptr);
  }
}

// Union enum - ice::EffectiveTimeType
void rand_gen(ice::EffectiveTimeType* field)
{
  REQUIRE(field != nullptr);
  *field = static_cast<ice::EffectiveTimeType>(rand() % 2);
}

// Required field - ice::EffectiveTime
void rand_gen(ice::EffectiveTime* field)
{
  REQUIRE(field != nullptr);
  rand_gen(&field->_d);
  switch (field->_d)
  {
  case ice::EffectiveTimeType::et_period:
    rand_gen(&field->_u.period);
    return;
  case ice::EffectiveTimeType::et_datetime:
  default:
    rand_gen(&field->_u.datetime, ice::MAXLEN_CT_DATETIME);
    return;
  }
}

// Optional field - ice::EffectiveTime
void rand_gen(ice::EffectiveTime** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::EffectiveTime*>(DDS::Heap_malloc(sizeof (ice::EffectiveTime)));
    REQUIRE(*field_ptr);
    (*field_ptr)->_u.period.start = DDS::String_alloc(ice::MAXLEN_CT_DATETIME);
    REQUIRE((*field_ptr)->_u.period.start);
    (*field_ptr)->_u.period.end = DDS::String_alloc(ice::MAXLEN_CT_DATETIME);
    REQUIRE((*field_ptr)->_u.period.end);
    (*field_ptr)->_u.datetime = DDS::String_alloc(ice::MAXLEN_CT_DATETIME);
    REQUIRE((*field_ptr)->_u.datetime);
    rand_gen(*field_ptr);
  }
}

// *****************
// **** patdemo ****
// *****************

// Enum - ice::PatientType
void rand_gen(ice::PatientType* field)
{
  REQUIRE(field != nullptr);
  *field = static_cast<ice::PatientType>(rand() % 4);
}

// Optional enum - ice::PatientType
void rand_gen(ice::PatientType** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::PatientType*>(DDS::Heap_malloc(sizeof (ice::PatientType)));
    REQUIRE(*field_ptr);
    rand_gen(*field_ptr);
  }
}

// Enum - ice::PatientSex
void rand_gen(ice::PatientSex* field)
{
  REQUIRE(field != nullptr);
  *field = static_cast<ice::PatientSex>(rand() % 4);
  if (*field > 2) *field = ice::PatientSex::sex_unspecified;
}

// Optional enum - ice::PatientSex
void rand_gen(ice::PatientSex** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::PatientSex*>(DDS::Heap_malloc(sizeof (ice::PatientSex)));
    REQUIRE(*field_ptr);
    rand_gen(*field_ptr);
  }
}

// Enum - ice::PatientGender
void rand_gen(ice::PatientGender* field)
{
  REQUIRE(field != nullptr);
  *field = static_cast<ice::PatientGender>(rand() % 4);
  if (*field > 2) *field = ice::PatientGender::gender_unspecified;
}

// Optional enum - ice::PatientGender
void rand_gen(ice::PatientGender** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::PatientGender*>(DDS::Heap_malloc(sizeof (ice::PatientGender)));
    REQUIRE(*field_ptr);
    rand_gen(*field_ptr);
  }
}

// Required field - ice::PatMeasure
void rand_gen(ice::PatMeasure* field)
{
  REQUIRE(field != nullptr);
  rand_gen(&field->value);
  rand_gen(&field->m_unit);
}

// Optional field - ice::PatMeasure
void rand_gen(ice::PatMeasure** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::PatMeasure*>(DDS::Heap_malloc(sizeof (ice::PatMeasure)));
    REQUIRE(*field_ptr);
    rand_gen(*field_ptr);
  }
}

// Enum - ice::RaceType
void rand_gen(ice::RaceType* field)
{
  REQUIRE(field != nullptr);
  *field = static_cast<ice::RaceType>(rand() % 7);
}

// Optional enum - ice::RaceType
void rand_gen(ice::RaceType** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::RaceType*>(DDS::Heap_malloc(sizeof (ice::RaceType)));
    REQUIRE(*field_ptr);
    rand_gen(*field_ptr);
  }
}

// Required field - ice::PatientRace
void rand_gen(ice::PatientRace* field)
{
  REQUIRE(field != nullptr);
  rand_gen(&field->race_type);
  rand_gen(&field->provenance, ice::SHORT_STRING_LEN);
}

// Optional field - ice::PatientRace
void rand_gen(ice::PatientRace** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::PatientRace*>(DDS::Heap_malloc(sizeof (ice::PatientRace)));
    REQUIRE(*field_ptr);
    (*field_ptr)->provenance = DDS::String_alloc(ice::SHORT_STRING_LEN);
    REQUIRE((*field_ptr)->provenance);
    rand_gen(*field_ptr);
  }
}

// Enum - ice::PatAdmitState
void rand_gen(ice::PatAdmitState* field)
{
  REQUIRE(field != nullptr);
  *field = static_cast<ice::PatAdmitState>(rand() % 5);
  if (*field == 3) *field = ice::PatAdmitState::readmit;
  if (*field == 4) *field = ice::PatAdmitState::discharged;
}

// Optional enum - ice::PatAdmitState
void rand_gen(ice::PatAdmitState** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::PatAdmitState*>(DDS::Heap_malloc(sizeof (ice::PatAdmitState)));
    REQUIRE(*field_ptr);
    rand_gen(*field_ptr);
  }
}

// Top-level object/Required field - ice::PatientIdentification
void rand_gen(ice::PatientIdentification* field)
{
  REQUIRE(field != nullptr);
  // Set Top and GUIDs by hand for now.
  rand_gen(&field->given_name, ice::SHORT_STRING_LEN);
  rand_gen(&field->family_name, ice::SHORT_STRING_LEN);
  rand_gen(&field->middle_name, ice::SHORT_STRING_LEN);
  rand_gen(&field->date_of_birth);
  rand_gen(&field->patient_id, ice::MEDIUM_STRING_LEN);
  rand_gen(&field->patient_id_provenance, ice::MEDIUM_STRING_LEN);
  field->verified = static_cast<ice::CT_boolean>(coinflip());
  rand_gen(&field->pat_admit_state);
  rand_gen(&field->pat_episode_id);
  rand_gen(&field->episode_start);
}

// Optional field - ice::PatientIdentification
void rand_gen(ice::PatientIdentification** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::PatientIdentification*>(DDS::Heap_malloc(sizeof (ice::PatientIdentification)));
    REQUIRE(*field_ptr);
    (*field_ptr)->given_name = DDS::String_alloc(ice::SHORT_STRING_LEN);
    REQUIRE((*field_ptr)->given_name);
    (*field_ptr)->family_name = DDS::String_alloc(ice::SHORT_STRING_LEN);
    REQUIRE((*field_ptr)->family_name);
    (*field_ptr)->middle_name = DDS::String_alloc(ice::SHORT_STRING_LEN);
    REQUIRE((*field_ptr)->middle_name);
    (*field_ptr)->patient_id = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->patient_id);
    (*field_ptr)->patient_id_provenance = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->patient_id_provenance);
    rand_gen(*field_ptr);
  }
}

// Top-level object - ice::PatientIdentificationError
void rand_gen(ice::PatientIdentificationError* field)
{
  REQUIRE(field != nullptr);
  // Set Top and GUIDs by hand for now.
  rand_gen(&field->patient_id, ice::MEDIUM_STRING_LEN);
  rand_gen(&field->provenance, ice::MEDIUM_STRING_LEN);
  rand_gen(&field->pat_episode_id);
  rand_gen(&field->error, ice::LONGLONG_STRING_LEN);
}

// Required field - ice::NeonatalPatientInfo
void rand_gen(ice::NeonatalPatientInfo* field)
{
  REQUIRE(field != nullptr);
  rand_gen(&field->gestational_age);
  rand_gen(&field->patient_birth_length);
  rand_gen(&field->patient_birth_weight);
  rand_gen(&field->patient_head_circumference);
  rand_gen(&field->mother_patient_id);
  rand_gen(&field->mother_name, ice::LONG_STRING_LEN);
}

// Optional field - ice::NeonatalPatientInfo
void rand_gen(ice::NeonatalPatientInfo** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::NeonatalPatientInfo*>(DDS::Heap_malloc(sizeof (ice::NeonatalPatientInfo)));
    REQUIRE(*field_ptr);
    (*field_ptr)->mother_name = DDS::String_alloc(ice::LONG_STRING_LEN);
    REQUIRE((*field_ptr)->mother_name);
    rand_gen(*field_ptr);
  }
}

// Top-level object - ice::PatientDemographics
void rand_gen(ice::PatientDemographics* field)
{
  REQUIRE(field != nullptr);
  // Set Top and GUIDs by hand for now.
  rand_gen(&field->sex);
  rand_gen(&field->gender);
  rand_gen(&field->race);
  rand_gen(&field->patient_type);
  rand_gen(&field->chronological_age);
  rand_gen(&field->patient_height);
  rand_gen(&field->patient_weight);
  rand_gen(&field->neonatal);
}

// *********************
// **** diagnostics ****
// *********************

// Required field - ice::Specimen
void rand_gen(ice::Specimen* field)
{
  REQUIRE(field != nullptr);
  rand_gen(&field->id, ice::MEDIUM_STRING_LEN);
  rand_gen(&field->type);
  rand_gen(&field->collected_time, ice::MAXLEN_CT_DATETIME);
  rand_gen(&field->received_time, ice::MAXLEN_CT_DATETIME);
  rand_gen(&field->registered_time, ice::MAXLEN_CT_DATETIME);
}

// Optional field - ice::Specimen
void rand_gen(ice::Specimen** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::Specimen*>(DDS::Heap_malloc(sizeof (ice::Specimen)));
    REQUIRE(*field_ptr);
    (*field_ptr)->id = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->id);
    (*field_ptr)->collected_time = DDS::String_alloc(ice::MAXLEN_CT_DATETIME);
    REQUIRE((*field_ptr)->collected_time);
    (*field_ptr)->received_time = DDS::String_alloc(ice::MAXLEN_CT_DATETIME);
    REQUIRE((*field_ptr)->received_time);
    (*field_ptr)->registered_time = DDS::String_alloc(ice::MAXLEN_CT_DATETIME);
    REQUIRE((*field_ptr)->registered_time);
    rand_gen(*field_ptr);
  }
}

// Union enum - ice::ObservationValueType
void rand_gen(ice::ObservationValueType* field)
{
  REQUIRE(field != nullptr);
//  int val = rand() % 8;
//  if (val > 4) val += 2;
  int val = rand() % 7;
  if (val > 3) val += 3;
  *field = static_cast<ice::ObservationValueType>(val);
}

// Required field - ice::ObservationValue
void rand_gen(ice::ObservationValue* field)
{
  REQUIRE(field != nullptr);
  rand_gen(&field->_d);
  switch (field->_d)
  {
  case ice::ObservationValueType::ov_quantity:
    rand_gen(&field->_u.val_quantity);
    return;
  case ice::ObservationValueType::ov_codeableconcept:
    rand_gen(&field->_u.val_codeableconcept);
    return;
  case ice::ObservationValueType::ov_string:
    rand_gen(&field->_u.val_string, ice::LONG_STRING_LEN);
    return;
  case ice::ObservationValueType::ov_range:
    rand_gen(&field->_u.val_range);
    return;
  case ice::ObservationValueType::ov_ratio:
    rand_gen(&field->_u.val_ratio);
    return;
//  case ice::ObservationValueType::ov_sampleddata:
//    rand_gen(&field->_u.val_sampled_data);
//    return;
//  case ice::ObservationValueType::ov_attachment:
//    rand_gen(&field->_u.val_attachment);
//    return;
  case ice::ObservationValueType::ov_time:
    rand_gen(&field->_u.val_time, ice::MAXLEN_CT_TIME);
    return;
  case ice::ObservationValueType::ov_datetime:
    rand_gen(&field->_u.val_datetime, ice::MAXLEN_CT_DATETIME);
    return;
  case ice::ObservationValueType::ov_period:
  default:
    rand_gen(&field->_u.val_period);
  }
}

// Optional field - ice::ObservationValue
void rand_gen(ice::ObservationValue** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::ObservationValue*>(DDS::Heap_malloc(sizeof (ice::ObservationValue)));
    REQUIRE(*field_ptr);
    (*field_ptr)->_u.val_quantity.unit = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->_u.val_quantity.unit);
    (*field_ptr)->_u.val_quantity.system = DDS::String_alloc(ice::MAXLEN_CT_URI);
    REQUIRE((*field_ptr)->_u.val_quantity.system);
    (*field_ptr)->_u.val_quantity.code_ = DDS::String_alloc(ice::MAXLEN_CT_CODE);
    REQUIRE((*field_ptr)->_u.val_quantity.code_);
    (*field_ptr)->_u.val_quantity.comparator = DDS::String_alloc(ice::TINY_STRING_LEN);
    REQUIRE((*field_ptr)->_u.val_quantity.comparator);
    (*field_ptr)->_u.val_codeableconcept.coding.system = DDS::String_alloc(ice::MAXLEN_CT_URI);
    REQUIRE((*field_ptr)->_u.val_codeableconcept.coding.system);
    (*field_ptr)->_u.val_codeableconcept.coding.version = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->_u.val_codeableconcept.coding.version);
    (*field_ptr)->_u.val_codeableconcept.coding.code_ = DDS::String_alloc(ice::MAXLEN_CT_CODE);
    REQUIRE((*field_ptr)->_u.val_codeableconcept.coding.code_);
    (*field_ptr)->_u.val_codeableconcept.coding.display = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->_u.val_codeableconcept.coding.display);
    (*field_ptr)->_u.val_codeableconcept.text = DDS::String_alloc(ice::LONGLONG_STRING_LEN);
    REQUIRE((*field_ptr)->_u.val_codeableconcept.text);
    (*field_ptr)->_u.val_string = DDS::String_alloc(ice::LONG_STRING_LEN);
    REQUIRE((*field_ptr)->_u.val_string);
    (*field_ptr)->_u.val_range.low.unit = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->_u.val_range.low.unit);
    (*field_ptr)->_u.val_range.low.system = DDS::String_alloc(ice::MAXLEN_CT_URI);
    REQUIRE((*field_ptr)->_u.val_range.low.system);
    (*field_ptr)->_u.val_range.low.code_ = DDS::String_alloc(ice::MAXLEN_CT_CODE);
    REQUIRE((*field_ptr)->_u.val_range.low.code_);
    (*field_ptr)->_u.val_range.high.unit = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->_u.val_range.high.unit);
    (*field_ptr)->_u.val_range.high.system = DDS::String_alloc(ice::MAXLEN_CT_URI);
    REQUIRE((*field_ptr)->_u.val_range.high.system);
    (*field_ptr)->_u.val_range.high.code_ = DDS::String_alloc(ice::MAXLEN_CT_CODE);
    REQUIRE((*field_ptr)->_u.val_range.high.code_);
    (*field_ptr)->_u.val_ratio.numerator.unit = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->_u.val_ratio.numerator.unit);
    (*field_ptr)->_u.val_ratio.numerator.system = DDS::String_alloc(ice::MAXLEN_CT_URI);
    REQUIRE((*field_ptr)->_u.val_ratio.numerator.system);
    (*field_ptr)->_u.val_ratio.numerator.code_ = DDS::String_alloc(ice::MAXLEN_CT_CODE);
    REQUIRE((*field_ptr)->_u.val_ratio.numerator.code_);
    (*field_ptr)->_u.val_ratio.numerator.comparator = DDS::String_alloc(ice::TINY_STRING_LEN);
    REQUIRE((*field_ptr)->_u.val_ratio.numerator.comparator);
    (*field_ptr)->_u.val_ratio.denominator.unit = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->_u.val_ratio.denominator.unit);
    (*field_ptr)->_u.val_ratio.denominator.system = DDS::String_alloc(ice::MAXLEN_CT_URI);
    REQUIRE((*field_ptr)->_u.val_ratio.denominator.system);
    (*field_ptr)->_u.val_ratio.denominator.code_ = DDS::String_alloc(ice::MAXLEN_CT_CODE);
    REQUIRE((*field_ptr)->_u.val_ratio.denominator.code_);
    (*field_ptr)->_u.val_ratio.denominator.comparator = DDS::String_alloc(ice::TINY_STRING_LEN);
    REQUIRE((*field_ptr)->_u.val_ratio.denominator.comparator);
    (*field_ptr)->_u.val_time = DDS::String_alloc(ice::MAXLEN_CT_TIME);
    REQUIRE((*field_ptr)->_u.val_time);
    (*field_ptr)->_u.val_datetime = DDS::String_alloc(ice::MAXLEN_CT_DATETIME);
    REQUIRE((*field_ptr)->_u.val_datetime);
    rand_gen(*field_ptr);
  }
}

// Required field - ice::ReferenceRange
void rand_gen(ice::ReferenceRange* field)
{
  REQUIRE(field != nullptr);
  rand_gen(&field->low);
  rand_gen(&field->high);
  rand_gen(&field->type);
  rand_gen(&field->age);
  rand_gen(&field->text, ice::LONG_STRING_LEN, true);
}

// Optional field - ice::ReferenceRange
void rand_gen(ice::ReferenceRange** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::ReferenceRange*>(DDS::Heap_malloc(sizeof (ice::ReferenceRange)));
    REQUIRE(*field_ptr);
    rand_gen(*field_ptr);
  }
}

// Required field - ice::ObservationResult
void rand_gen(ice::ObservationResult* field)
{
  REQUIRE(field != nullptr);
  rand_gen(&field->code_);
  rand_gen(&field->value);
  rand_gen(&field->data_absent_reason);
  rand_gen(&field->reference_range);
}

// Optional field - ice::ObservationResult
void rand_gen(ice::ObservationResult** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::ObservationResult*>(DDS::Heap_malloc(sizeof (ice::ObservationResult)));
    REQUIRE(*field_ptr);
    (*field_ptr)->code_.coding.system = DDS::String_alloc(ice::MAXLEN_CT_URI);
    REQUIRE((*field_ptr)->code_.coding.system);
    (*field_ptr)->code_.coding.version = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->code_.coding.version);
    (*field_ptr)->code_.coding.code_ = DDS::String_alloc(ice::MAXLEN_CT_CODE);
    REQUIRE((*field_ptr)->code_.coding.code_);
    (*field_ptr)->code_.coding.display = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->code_.coding.display);
    (*field_ptr)->code_.text = DDS::String_alloc(ice::LONGLONG_STRING_LEN);
    REQUIRE((*field_ptr)->code_.text);
    rand_gen(*field_ptr);
  }
}

// Union enum - ice::PerfomerRole
void rand_gen(ice::PerfomerRole* field)
{
  REQUIRE(field != nullptr);
  *field = static_cast<ice::PerfomerRole>(rand() % 4);
}

// Required field - ice::Performer
void rand_gen(ice::Performer* field)
{
  REQUIRE(field != nullptr);
  rand_gen(&field->id, ice::MEDIUM_STRING_LEN);
  rand_gen(&field->name, ice::LONG_STRING_LEN);
  rand_gen(&field->role);
}

// Optional field - ice::Performer
void rand_gen(ice::Performer** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::Performer*>(DDS::Heap_malloc(sizeof (ice::Performer)));
    REQUIRE(*field_ptr);
    (*field_ptr)->id = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field_ptr)->id);
    (*field_ptr)->name = DDS::String_alloc(ice::LONG_STRING_LEN);
    REQUIRE((*field_ptr)->name);
    rand_gen(*field_ptr);
  }
}

// Required field - ice::PerformerSeq
void rand_gen(ice::PerformerSeq* field)
{
  // Magic number, can't find a coded max sequence length anywhere so
  // I'm (rengland) using DDS' default max.
  static const DDS_Long kMaxPerformers = 100;
  REQUIRE(field != nullptr);
  DDS_Long seq_len = static_cast<DDS_Long>(rand() % kMaxPerformers + 1);
  REQUIRE(field->ensure_length(seq_len, kMaxPerformers));
  for (int ix = 0; ix < seq_len; ix++)
  {
    (*field)[ix].id = DDS::String_alloc(ice::MEDIUM_STRING_LEN);
    REQUIRE((*field)[ix].id);
    (*field)[ix].name = DDS::String_alloc(ice::LONG_STRING_LEN);
    REQUIRE((*field)[ix].name);
    rand_gen(&(*field)[ix]);
  }
}

// Optional field - ice::PerformerSeq
void rand_gen(ice::PerformerSeq** field_ptr)
{
  REQUIRE(field_ptr);
  if (coinflip()) *field_ptr = nullptr;
  else
  {
    *field_ptr = reinterpret_cast<ice::PerformerSeq*>(DDS::Heap_malloc(sizeof (ice::PerformerSeq)));
    REQUIRE(*field_ptr);
    rand_gen(*field_ptr);
  }
}

// Top-level object - ice::Observation
void rand_gen(ice::Observation* field)
{
  REQUIRE(field != nullptr);
  // Set Top and GUIDs by hand for now.
  rand_gen(&field->observation_number);
  rand_gen(&field->component_count);
  rand_gen(&field->order_id, ice::MEDIUM_STRING_LEN, true);
  rand_gen(&field->status, ice::MAXLEN_CT_CODE);
  rand_gen(&field->category);
  rand_gen(&field->effective);
  rand_gen(&field->issued, ice::MAXLEN_CT_INSTANT, true);
  rand_gen(&field->subject, ice::MEDIUM_STRING_LEN, true);
  rand_gen(&field->specimen);
  rand_gen(&field->result);
}

// Top-level object - ice::ObservationComponent
void rand_gen(ice::ObservationComponent* field)
{
  REQUIRE(field != nullptr);
  // Set Top and GUIDs by hand for now.
  rand_gen(&field->component_number);
  rand_gen(&field->value);
}

// Top-level object - ice::DiagnosticReport
void rand_gen(ice::DiagnosticReport* field)
{
  REQUIRE(field != nullptr);
  // Set Top and GUIDs by hand for now.
  rand_gen(&field->observation_count);
  rand_gen(&field->status, ice::MAXLEN_CT_CODE);
  rand_gen(&field->category);
  rand_gen(&field->code_);
  rand_gen(&field->subject, ice::MEDIUM_STRING_LEN, true);
  rand_gen(&field->encounter_id, ice::MEDIUM_STRING_LEN, true);
  rand_gen(&field->effective);
  rand_gen(&field->issued, ice::MAXLEN_CT_INSTANT, true);
  rand_gen(&field->performer);
  rand_gen(&field->ordering_doctor_specialty, ice::MEDIUM_STRING_LEN, true);
}

// **************
// **** expr ****
// **************

// Top-level object - expr::Diagnosis
void rand_gen(expr::Diagnosis* field)
{
  REQUIRE(field != nullptr);
  // Set Top and GUIDs by hand for now.
  rand_gen(&field->diagnosis, ice::LONG_STRING_LEN);
  rand_gen(&field->procedure_list, ice::LONG_STRING_LEN);
  rand_gen(&field->physician, ice::LONG_STRING_LEN);
  rand_gen(&field->patient_identification);
}

// Top-level object - expr::DxHistory
void rand_gen(expr::DxHistory* field)
{
  REQUIRE(field != nullptr);
  // Set Top and GUIDs by hand for now.
  rand_gen(&field->health_problem, ice::LONG_STRING_LEN);
  rand_gen(&field->recent_procedure, ice::LONG_STRING_LEN);
  rand_gen(&field->patient_identification);
  rand_gen(&field->problem_count);
  rand_gen(&field->problem_list, ice::LONG_STRING_LEN);
  rand_gen(&field->recent_procedures, ice::LONG_STRING_LEN);
}

// Required field - ice::Medication
void rand_gen(expr::Medication* field)
{
  REQUIRE(field != nullptr);
  rand_gen(&field->name, ice::LONG_STRING_LEN);
  rand_gen(&field->dose, ice::LONG_STRING_LEN);
}

// Required field - ice::MedicationList
void rand_gen(expr::MedicationList* field)
{
  // Magic number, can't find a coded max sequence length anywhere so
  // I'm (rengland) using DDS' default max.
  static const DDS_Long kMaxMedications = 100;
  REQUIRE(field != nullptr);
  DDS_Long seq_len = static_cast<DDS_Long>(rand() % kMaxMedications + 1);
  REQUIRE(field->ensure_length(seq_len, kMaxMedications));
  for (int ix = 0; ix < seq_len; ix++)
  {
    (*field)[ix].name = DDS::String_alloc(ice::LONG_STRING_LEN);
    REQUIRE((*field)[ix].name);
    (*field)[ix].dose = DDS::String_alloc(ice::LONG_STRING_LEN);
    REQUIRE((*field)[ix].dose);
    rand_gen(&(*field)[ix]);
  }
}

// Top-level object - expr::PatientMedication
void rand_gen(expr::PatientMedication* field)
{
  REQUIRE(field != nullptr);
  // Set Top and GUIDs by hand for now.
  rand_gen(&field->patient_identification);
  rand_gen(&field->medication_count);
  rand_gen(&field->medication_list);
}

#endif // RANDGEN_DDS_H
