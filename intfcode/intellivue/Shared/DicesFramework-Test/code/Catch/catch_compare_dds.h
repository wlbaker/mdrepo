#ifndef CATCH_COMPARE_DDS_H
#define CATCH_COMPARE_DDS_H

#include "catch.hpp"
#include "allergy.h"
#include "diagnostics.h"
#include "expr.h"

#include "dices_octet_string.h"

void CHECK_STR(DDS_Char* a, DDS_Char* b)
{
  std::string str_a = "";
  std::string str_b = "";
  if (a != nullptr) str_a.assign(a);
  if (b != nullptr) str_b.assign(b);
  CHECK(str_a == str_b);
}

// Begin: common.idl

void CHECK_IDL(ice::GLBHANDLE* a, ice::GLBHANDLE* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->context_id == b->context_id);
  CHECK(a->handle == b->handle);
}

void CHECK_IDL(ice::ManagedObjectId* a, ice::ManagedObjectId* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->m_obj_class == b->m_obj_class);
  CHECK_IDL(&a->m_obj_inst, &b->m_obj_inst);
}

void CHECK_IDL(ice::TYPE* a, ice::TYPE* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->partition == b->partition);
  CHECK(a->code == b->code);
}

void CHECK_IDL(ice::Timespec* a, ice::Timespec* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->seconds == b->seconds);
  CHECK(a->nanoseconds == b->nanoseconds);
}

void CHECK_IDL(ice::Duration* a, ice::Duration* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->seconds == b->seconds);
  CHECK(a->nanoseconds == b->nanoseconds);
}

void CHECK_IDL(ice::Date* a, ice::Date* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->century == b->century);
  CHECK(a->year == b->year);
  CHECK(a->month == b->month);
  CHECK(a->day == b->day);
}

void CHECK_IDL(ice::StringSpec* a, ice::StringSpec* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->str_max_len == b->str_max_len);
  CHECK(a->str_flags == b->str_flags);
}

void CHECK_IDL(ice::Locale* a, ice::Locale* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->language == b->language);
  CHECK(a->country == b->country);
  CHECK(a->charset == b->charset);
  CHECK_IDL(&a->str_spec, &b->str_spec);
}

void CHECK_IDL(ice::ExtNomenRef* a, ice::ExtNomenRef* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->nomenclature_id == b->nomenclature_id);
  CHECK_STR(a->nomenclature_code, b->nomenclature_code);
}

void CHECK_IDL(ice::SystemModel* a, ice::SystemModel* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_STR(a->manufacturer, b->manufacturer);
  CHECK_STR(a->model_number, b->model_number);
}

void CHECK_IDL(ice::ProdSpecEntry* a, ice::ProdSpecEntry* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->spec_type == b->spec_type);
  CHECK(a->component_id == b->component_id);
  CHECK_STR(a->prod_spec, b->prod_spec);
}

void CHECK_IDL(ice::ProductionSpec* a, ice::ProductionSpec* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->length() == b->length());
  for (size_t ix = 0; ix < a->length() && ix < b->length(); ix++)
  {
    CHECK_IDL(const_cast<ice::ProdSpecEntry*>(&a->get_at(ix)),
              const_cast<ice::ProdSpecEntry*>(&b->get_at(ix)));
  }
}

void CHECK_IDL(ice::CurLimAlVal* a, ice::CurLimAlVal* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->lower == b->lower);
  CHECK(a->upper == b->upper);
}

void CHECK_IDL(ice::EventReport* a, ice::EventReport* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->object_class == b->object_class);
  CHECK(a->object_instance == b->object_instance);
}

void CHECK_IDL(ice::HostId* a, ice::HostId* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(OctetArrayToHexString(*a, 6) == OctetArrayToHexString(*b, 6));
}

void CHECK_IDL(ice::GuidTimespec* a, ice::GuidTimespec* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(OctetArrayToHexString(a->seconds, 4) == OctetArrayToHexString(b->seconds, 4));
  CHECK(OctetArrayToHexString(a->fraction, 2) == OctetArrayToHexString(b->fraction, 2));
}

void CHECK_IDL(ice::GuidPrefix* a, ice::GuidPrefix* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(&a->hostid, &b->hostid);
  CHECK_IDL(&a->timestamp, &b->timestamp);
}

void CHECK_IDL(ice::EntityId* a, ice::EntityId* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->kind_of_entity == b->kind_of_entity);
  CHECK(a->entity_key == b->entity_key);
}

void CHECK_IDL(ice::GUID* a, ice::GUID* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(&a->prefix, &b->prefix);
  CHECK_IDL(&a->entity_id, &b->entity_id);
}

void CHECK_IDL(ice::Top* a, ice::Top* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_STR(a->ice_id, b->ice_id);
  CHECK(a->handle == b->handle);
  CHECK(a->parent_handle == b->parent_handle);
  // Probably don't want to check source timestamps.  Otherwise we'd get failures
  // every time something automatically sets a timestamp to the current time.
}

void CHECK_IDL(ice::VMO* a, ice::VMO* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(static_cast<ice::Top*>(a), static_cast<ice::Top*>(b));
  CHECK_IDL(&a->type, &b->type);
}

void CHECK_IDL(ice::CT_decimal* a, ice::CT_decimal* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->value == Approx(b->value));
  CHECK(static_cast<int>(a->presentation_precision) == static_cast<int>(b->presentation_precision));
}

void CHECK_IDL(ice::Coding* a, ice::Coding* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_STR(a->system, b->system);
  CHECK_STR(a->version, b->version);
  CHECK_STR(a->code_, b->code_);
  CHECK_STR(a->display, b->display);
  CHECK(a->user_selected == b->user_selected);
}

void CHECK_IDL(ice::CodeableConcept* a, ice::CodeableConcept* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(&a->coding, &b->coding);
  CHECK_STR(a->text, b->text);
}

void CHECK_IDL(ice::SimpleQuantity* a, ice::SimpleQuantity* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(&a->value, &b->value);
  CHECK_STR(a->unit, b->unit);
  CHECK_STR(a->system, b->system);
  CHECK_STR(a->code_, b->code_);
}

void CHECK_IDL(ice::Quantity* a, ice::Quantity* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(static_cast<ice::SimpleQuantity*>(a), static_cast<ice::SimpleQuantity*>(b));
  CHECK_STR(a->comparator, b->comparator);
}

void CHECK_IDL(ice::Range* a, ice::Range* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(&a->low, &b->low);
  CHECK_IDL(&a->high, &b->high);
}

void CHECK_IDL(ice::Ratio* a, ice::Ratio* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(&a->numerator, &b->numerator);
  CHECK_IDL(&a->denominator, &b->denominator);
}

void CHECK_IDL(ice::Period* a, ice::Period* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_STR(a->start, b->start);
  CHECK_STR(a->end, b->end);
}

void CHECK_IDL(ice::EffectiveTime* a, ice::EffectiveTime* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  REQUIRE(a->_d == b->_d);
  switch (a->_d)
  {
  case ice::EffectiveTimeType::et_period:
    CHECK_IDL(&a->_u.period, &b->_u.period);
    return;
  case ice::EffectiveTimeType::et_datetime:
    CHECK_STR(a->_u.datetime, b->_u.datetime);
    return;
  }
}

// End: common.idl

// Begin: allergy.idl

void CHECK_IDL(ice::CodeSystemPair* a, ice::CodeSystemPair* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_STR(a->code_system_identifier, b->code_system_identifier);
  CHECK_STR(a->code_system_name, b->code_system_name);
}

void CHECK_IDL(ice::CodeLabelPair* a, ice::CodeLabelPair* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(&a->code_system_pair, &b->code_system_pair);
  CHECK_STR(a->code, b->code);
  CHECK_STR(a->label, b->label);
}

void CHECK_IDL(ice::SeverityType* a, ice::SeverityType* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->coded_severity == b->coded_severity);
  CHECK_STR(a->free_text_severity, b->free_text_severity);
}

void CHECK_IDL(ice::ReactionType* a, ice::ReactionType* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(&a->coded_reaction, &b->coded_reaction);
  CHECK_STR(a->free_text_reaction, b->free_text_reaction);
  CHECK_IDL(&a->severity, &b->severity);
}

void CHECK_IDL(ice::ReactionList* a, ice::ReactionList* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->length() == b->length());
  for (size_t ix = 0; ix < a->length() && ix < b->length(); ix++)
  {
    CHECK_IDL(const_cast<ice::ReactionType*>(&a->get_at(ix)),
              const_cast<ice::ReactionType*>(&b->get_at(ix)));
  }
}

void CHECK_IDL(ice::AdverseEventEntry* a, ice::AdverseEventEntry* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(&a->adverse_event_date, &b->adverse_event_date);
  CHECK(a->adverse_event_type == b->adverse_event_type);
  CHECK_IDL(&a->coded_product, &b->coded_product);
  CHECK_STR(a->free_text_product, b->free_text_product);
  CHECK_IDL(&a->reactions, &b->reactions);
}

void CHECK_IDL(ice::AdverseEventList* a, ice::AdverseEventList* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->length() == b->length());
  for (size_t ix = 0; ix < a->length() && ix < b->length(); ix++)
  {
    CHECK_IDL(const_cast<ice::AdverseEventEntry*>(&a->get_at(ix)),
              const_cast<ice::AdverseEventEntry*>(&b->get_at(ix)));
  }
}

void CHECK_IDL(ice::Allergy* a, ice::Allergy* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(static_cast<ice::Top*>(a), static_cast<ice::Top*>(b));
  CHECK(a->adverse_event_count == b->adverse_event_count);
  CHECK_IDL(&a->adverse_events, &b->adverse_events);
}

// End: allergy.idl

// Begin: diagnostics.idl

void CHECK_IDL(ice::Specimen* a, ice::Specimen* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_STR(a->id, b->id);
  CHECK_IDL(a->type, b->type);
  CHECK_STR(a->collected_time, b->collected_time);
  CHECK_STR(a->received_time, b->received_time);
  CHECK_STR(a->registered_time, b->registered_time);
}

void CHECK_IDL(ice::ObservationValue* a, ice::ObservationValue* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  REQUIRE(a->_d == b->_d);
  switch (a->_d)
  {
  case ice::ObservationValueType::ov_quantity:
    CHECK_IDL(&a->_u.val_quantity, &b->_u.val_quantity);
    return;
  case ice::ObservationValueType::ov_codeableconcept:
    CHECK_IDL(&a->_u.val_codeableconcept, &b->_u.val_codeableconcept);
    return;
  case ice::ObservationValueType::ov_string:
    CHECK_STR(a->_u.val_string, b->_u.val_string);
    return;
  case ice::ObservationValueType::ov_range:
    CHECK_IDL(&a->_u.val_range, &b->_u.val_range);
    return;
  case ice::ObservationValueType::ov_ratio:
    CHECK_IDL(&a->_u.val_ratio, &b->_u.val_ratio);
    return;
//  case ice::ObservationValueType::ov_sampleddata:
//    CHECK_IDL(&a->_u.val_sampled_data, &b->_u.val_sampleddata);
//    return;
//  case ice::ObservationValueType::ov_attachment:
//    CHECK_IDL(&a->_u.val_attachment, &b->_u.val_attachment);
//    return;
  case ice::ObservationValueType::ov_time:
    CHECK_STR(a->_u.val_time, b->_u.val_time);
    return;
  case ice::ObservationValueType::ov_datetime:
    CHECK_STR(a->_u.val_datetime, b->_u.val_datetime);
    return;
  case ice::ObservationValueType::ov_period:
    CHECK_IDL(&a->_u.val_period, &b->_u.val_period);
    return;
  }
}

void CHECK_IDL(ice::ReferenceRange* a, ice::ReferenceRange* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(a->low, b->low);
  CHECK_IDL(a->high, b->high);
  CHECK_IDL(a->type, b->type);
  CHECK_IDL(a->age, b->age);
  CHECK_STR(a->text, b->text);
}

void CHECK_IDL(ice::ObservationResult* a, ice::ObservationResult* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(&a->code_, &b->code_);
  CHECK_IDL(a->value, b->value);
  CHECK_IDL(a->data_absent_reason, b->data_absent_reason);
  CHECK_IDL(a->interpretation, b->interpretation);
  CHECK_IDL(a->reference_range, b->reference_range);
}

void CHECK_IDL(ice::Performer* a, ice::Performer* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_STR(a->id, b->id);
  CHECK_STR(a->name, b->name);
  CHECK(a->role == b->role);
}

void CHECK_IDL(ice::Observation* a, ice::Observation* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(static_cast<ice::Top*>(a), static_cast<ice::Top*>(b));
  CHECK_IDL(&a->report_id, &b->report_id);
  CHECK_IDL(&a->id, &b->id);
  CHECK(a->observation_number == b->observation_number);
  CHECK(a->component_count == b->component_count);
  CHECK_STR(a->order_id, b->order_id);
  CHECK_STR(a->status, b->status);
  CHECK_IDL(a->category, b->category);
  CHECK_IDL(a->effective, b->effective);
  CHECK_STR(a->issued, b->issued);
  CHECK_STR(a->subject, b->subject);
  CHECK_IDL(a->method, b->method);
  CHECK_IDL(a->specimen, b->specimen);
  CHECK_IDL(&a->result, &b->result);
}

void CHECK_IDL(ice::ObservationComponent* a, ice::ObservationComponent* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(static_cast<ice::Top*>(a), static_cast<ice::Top*>(b));
  CHECK_IDL(&a->observation_id, &b->observation_id);
  CHECK(a->component_number == b->component_number);
  CHECK_IDL(&a->value, &b->value);
}

void CHECK_IDL(ice::DiagnosticReport* a, ice::DiagnosticReport* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(static_cast<ice::Top*>(a), static_cast<ice::Top*>(b));
  CHECK_IDL(&a->id, &b->id);
  CHECK(a->observation_count == b->observation_count);
  CHECK_STR(a->status, b->status);
  CHECK_IDL(a->category, b->category);
  CHECK_IDL(&a->code_, &b->code_);
  CHECK_STR(a->subject, b->subject);
  CHECK_STR(a->encounter_id, b->encounter_id);
  CHECK_IDL(a->effective, b->effective);
  CHECK_STR(a->issued, b->issued);
  if (a->performer != nullptr && b->performer != nullptr)
  {
    CHECK(a->performer->length() == b->performer->length());
    for (size_t ix = 0; ix < a->performer->length() && ix < b->performer->length(); ix++)
    {
      CHECK_IDL(&(*a->performer)[ix], &(*b->performer)[ix]);
    }
  }
  else
  {
    CHECK(a->performer == b->performer);
  }
  CHECK_STR(a->ordering_doctor_specialty, b->ordering_doctor_specialty);
}

// End: diagnostics.idl

// Begin: expr.idl

void CHECK_IDL(expr::GuidTimespec* a, expr::GuidTimespec* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  for (size_t ix = 0; ix < 4; ix++)
  {
    CHECK(a->seconds[ix] == b->seconds[ix]);
  }
  for (size_t ix = 0; ix < 2; ix++)
  {
    CHECK(a->fraction[ix] == b->fraction[ix]);
  }
}

void CHECK_IDL(expr::GuidPrefix_t* a, expr::GuidPrefix_t* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(&a->hostid, &b->hostid);
  CHECK_IDL(&a->timestamp, &b->timestamp);
}

void CHECK_IDL(expr::Diagnosis* a, expr::Diagnosis* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(static_cast<ice::Top*>(a), static_cast<ice::Top*>(b));
  CHECK_STR(a->diagnosis, b->diagnosis);
  CHECK(a->procedure_list.length() == b->procedure_list.length());
  for (size_t ix = 0; ix < a->procedure_list.length() && ix < b->procedure_list.length(); ix++)
  {
    CHECK(*a->procedure_list.get_at(ix) == *b->procedure_list.get_at(ix));
  }
  CHECK_STR(a->physician, b->physician);
  CHECK_IDL(&a->patient_identification, &b->patient_identification);
}

void CHECK_IDL(expr::DxHistory* a, expr::DxHistory* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(static_cast<ice::Top*>(a), static_cast<ice::Top*>(b));
  CHECK_STR(a->health_problem, b->health_problem);
  CHECK_STR(a->recent_procedure, b->recent_procedure);
  CHECK_IDL(&a->patient_identification, &b->patient_identification);
  CHECK(a->problem_list.length() == b->problem_list.length());
  for (size_t ix = 0; ix < a->problem_list.length() && ix < b->problem_list.length(); ix++)
  {
    CHECK(*a->problem_list.get_at(ix) == *b->problem_list.get_at(ix));
  }
  CHECK_STR(a->recent_procedures, b->recent_procedures);
}

void CHECK_IDL(expr::Medication* a, expr::Medication* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_STR(a->name, b->name);
  CHECK_STR(a->dose, b->dose);
}

void CHECK_IDL(expr::MedicationList* a, expr::MedicationList* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->length() == b->length());
  for (size_t ix = 0; ix < a->length() && ix < b->length(); ix++)
  {
    CHECK_IDL(const_cast<expr::Medication*>(&a->get_at(ix)),
              const_cast<expr::Medication*>(&b->get_at(ix)));
  }
}

void CHECK_IDL(expr::PatientMedication* a, expr::PatientMedication* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(static_cast<ice::Top*>(a), static_cast<ice::Top*>(b));
  CHECK_IDL(&a->patient_identification, &b->patient_identification);
  CHECK(a->medication_count == b->medication_count);
  CHECK_IDL(&a->medication_list, &b->medication_list);
}

// End: expr.idl

// Begin: patdemo.idl

void CHECK_IDL(ice::PatMeasure* a, ice::PatMeasure* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->value == b->value);
  CHECK(a->m_unit == b->m_unit);
}

void CHECK_IDL(ice::PatientRace* a, ice::PatientRace* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK(a->race_type == b->race_type);
  CHECK_STR(a->provenance, b->provenance);
}

void CHECK_IDL(ice::PatientIdentification* a, ice::PatientIdentification* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_IDL(static_cast<ice::Top*>(a), static_cast<ice::Top*>(b));
  CHECK_STR(a->given_name, b->given_name);
  CHECK_STR(a->family_name, b->family_name);
  CHECK_STR(a->middle_name, b->middle_name);
  if (a->date_of_birth != nullptr && b->date_of_birth != nullptr)
  {
    CHECK_IDL(a->date_of_birth, b->date_of_birth);
  }
  else
  {
    CHECK(a->date_of_birth == b->date_of_birth);
  }
  CHECK_STR(a->patient_id, b->patient_id);
  CHECK_STR(a->patient_id_provenance, b->patient_id_provenance);
  CHECK(a->verified == b->verified);
  CHECK(a->pat_admit_state == b->pat_admit_state);
  CHECK(a->pat_episode_id == b->pat_episode_id);
  CHECK_IDL(&a->episode_start, &b->episode_start);
}

// HACK rengland 2017 OCT 24
// PatientIdentification may be used as either a top-level object or as a field
// within another object.  Our recording service and translation table tool databases
// currently do not record or handle the inherited Top fields within the
// PatientIdentification instances within parent objects, so I need to only concern
// myself with those fields when the PatientIdentification instance is top-level.
void CHECK_IDL(ice::PatientIdentification* a, ice::PatientIdentification* b, bool toplevel)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  if (toplevel) CHECK_IDL(static_cast<ice::Top*>(a), static_cast<ice::Top*>(b));
  CHECK_IDL(a, b);
}

void CHECK_IDL(ice::PatientIdentificationError* a, ice::PatientIdentificationError* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  CHECK_STR(a->patient_id, b->patient_id);
  CHECK_STR(a->provenance, b->provenance);
  CHECK(a->pat_episode_id == b->pat_episode_id);
  CHECK_STR(a->error, b->error);
}

// TODO rengland 02 AUG 2017
// Adding the Diagnostics IDL made me realize that all these if/else's are totally
// unnecessary for non-primitives, because CHECK_IDL and CHECK_STR have null checks
// built in, so I can clean this up some.  Still necessary for primitives though.
void CHECK_IDL(ice::NeonatalPatientInfo* a, ice::NeonatalPatientInfo* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  if (a->gestational_age != nullptr && b->gestational_age != nullptr)
  {
    CHECK_IDL(a->gestational_age, b->gestational_age);
  }
  else
  {
    CHECK(a->gestational_age == b->gestational_age);
  }
  if (a->patient_birth_length != nullptr && b->patient_birth_length != nullptr)
  {
    CHECK_IDL(a->patient_birth_length, b->patient_birth_length);
  }
  else
  {
    CHECK(a->patient_birth_length == b->patient_birth_length);
  }
  if (a->patient_birth_weight != nullptr && b->patient_birth_weight != nullptr)
  {
    CHECK_IDL(a->patient_birth_weight, b->patient_birth_weight);
  }
  else
  {
    CHECK(a->patient_birth_weight == b->patient_birth_weight);
  }
  if (a->patient_head_circumference != nullptr && b->patient_head_circumference != nullptr)
  {
    CHECK_IDL(a->patient_head_circumference, b->patient_head_circumference);
  }
  else
  {
    CHECK(a->patient_head_circumference == b->patient_head_circumference);
  }
  if (a->mother_patient_id != nullptr && b->mother_patient_id != nullptr)
  {
    CHECK_IDL(a->mother_patient_id, b->mother_patient_id);
  }
  else
  {
    CHECK(a->mother_patient_id == b->mother_patient_id);
  }
  if (a->mother_name != nullptr && b->mother_name != nullptr)
  {
    CHECK(*a->mother_name == *b->mother_name);
  }
  else
  {
    CHECK(a->mother_name == b->mother_name);
  }
}

void CHECK_IDL(ice::PatientDemographics* a, ice::PatientDemographics* b)
{
  if (a->sex != nullptr && b->sex != nullptr)
  {
    CHECK(*a->sex == *b->sex);
  }
  else
  {
    CHECK(a->sex == b->sex);
  }
  if (a->gender != nullptr && b->gender != nullptr)
  {
    CHECK(*a->gender == *b->gender);
  }
  else
  {
    CHECK(a->gender == b->gender);
  }
  if (a->race != nullptr && b->race != nullptr)
  {
    CHECK_IDL(a->race, b->race);
  }
  else
  {
    CHECK(a->race == b->race);
  }
  if (a->patient_type != nullptr && b->patient_type != nullptr)
  {
    CHECK(*a->patient_type == *b->patient_type);
  }
  else
  {
    CHECK(a->patient_type == b->patient_type);
  }
  if (a->chronological_age != nullptr && b->chronological_age != nullptr)
  {
    CHECK_IDL(a->chronological_age, b->chronological_age);
  }
  else
  {
    CHECK(a->chronological_age == b->chronological_age);
  }
  if (a->patient_height != nullptr && b->patient_height != nullptr)
  {
    CHECK_IDL(a->patient_height, b->patient_height);
  }
  else
  {
    CHECK(a->patient_height == b->patient_height);
  }
  if (a->patient_weight != nullptr && b->patient_weight != nullptr)
  {
    CHECK_IDL(a->patient_weight, b->patient_weight);
  }
  else
  {
    CHECK(a->patient_weight == b->patient_weight);
  }
  if (a->neonatal != nullptr && b->neonatal != nullptr)
  {
    CHECK_IDL(a->neonatal, b->neonatal);
  }
  else
  {
    CHECK(a->neonatal == b->neonatal);
  }
}

// End: patdemo.idl

#endif // CATCH_COMPARE_DDS_H
