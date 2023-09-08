#ifndef CATCH_COMPARE_DATA_STORE_H
#define CATCH_COMPARE_DATA_STORE_H

#include "catch_compare_dds.h"
#include "base-app-data-store.h"

void CHECK_DATA_STORE(BaseAppDataStore* a, BaseAppDataStore* b)
{
  if (a == nullptr || b == nullptr)
  {
    CHECK(a == b);
    return;
  }
  // Check Allergies
  CHECK(a->_allergy_update_list.size() == b->_allergy_update_list.size());
  for (size_t ix = 0; ix < a->_allergy_update_list.size() && ix < b->_allergy_req_update_list.size(); ix++)
  {
    CHECK(a->_allergy_update_list[ix].first == b->_allergy_update_list[ix].first);
    CHECK_IDL(a->_allergy_update_list[ix].second, b->_allergy_update_list[ix].second);
  }
  // Check Allergy Reqs
  CHECK(a->_allergy_req_update_list.size() == b->_allergy_req_update_list.size());
  for (size_t ix = 0; ix < a->_allergy_req_update_list.size() && ix < b->_allergy_req_update_list.size(); ix++)
  {
    CHECK(a->_allergy_req_update_list[ix].first == b->_allergy_req_update_list[ix].first);
    CHECK_IDL(a->_allergy_req_update_list[ix].second, b->_allergy_req_update_list[ix].second);
  }
  // Check Demographics
  CHECK(a->_patient_demographics_update_list.size() == b->_patient_demographics_update_list.size());
  for (size_t ix = 0; ix < a->_patient_demographics_update_list.size() && ix < b->_patient_demographics_update_list.size(); ix++)
  {
    CHECK(a->_patient_demographics_update_list[ix].first == b->_patient_demographics_update_list[ix].first);
    CHECK_IDL(a->_patient_demographics_update_list[ix].second, b->_patient_demographics_update_list[ix].second);
  }
  // Check Demographics Reqs
  CHECK(a->_patient_demographics_req_update_list.size() == b->_patient_demographics_req_update_list.size());
  for (size_t ix = 0; ix < a->_patient_demographics_req_update_list.size() && ix < b->_patient_demographics_req_update_list.size(); ix++)
  {
    CHECK(a->_patient_demographics_req_update_list[ix].first == b->_patient_demographics_req_update_list[ix].first);
    CHECK_IDL(a->_patient_demographics_req_update_list[ix].second, b->_patient_demographics_req_update_list[ix].second);
  }
  // Check Diagnosis
  CHECK(a->_diagnosis_update_list.size() == b->_diagnosis_update_list.size());
  for (size_t ix = 0; ix < a->_diagnosis_update_list.size() && ix < b->_diagnosis_update_list.size(); ix++)
  {
    CHECK(a->_diagnosis_update_list[ix].first == b->_diagnosis_update_list[ix].first);
    CHECK_IDL(a->_diagnosis_update_list[ix].second, b->_diagnosis_update_list[ix].second);
  }
  // Check Diagnosis Reqs
  CHECK(a->_diagnosis_req_update_list.size() == b->_diagnosis_req_update_list.size());
  for (size_t ix = 0; ix < a->_diagnosis_req_update_list.size() && ix < b->_diagnosis_req_update_list.size(); ix++)
  {
    CHECK(a->_diagnosis_req_update_list[ix].first == b->_diagnosis_req_update_list[ix].first);
    CHECK_IDL(a->_diagnosis_req_update_list[ix].second, b->_diagnosis_req_update_list[ix].second);
  }
  // Check History
  CHECK(a->_dx_history_update_list.size() == b->_dx_history_update_list.size());
  for (size_t ix = 0; ix < a->_dx_history_update_list.size() && ix < b->_dx_history_update_list.size(); ix++)
  {
    CHECK(a->_dx_history_update_list[ix].first == b->_dx_history_update_list[ix].first);
    CHECK_IDL(a->_dx_history_update_list[ix].second, b->_dx_history_update_list[ix].second);
  }
  // Check History Reqs
  CHECK(a->_dx_history_req_update_list.size() == b->_dx_history_req_update_list.size());
  for (size_t ix = 0; ix < a->_dx_history_req_update_list.size() && ix < b->_dx_history_req_update_list.size(); ix++)
  {
    CHECK(a->_dx_history_req_update_list[ix].first == b->_dx_history_req_update_list[ix].first);
    CHECK_IDL(a->_dx_history_req_update_list[ix].second, b->_dx_history_req_update_list[ix].second);
  }
  // Check Medications
  CHECK(a->_patient_medication_update_list.size() == b->_patient_medication_update_list.size());
  for (size_t ix = 0; ix < a->_patient_medication_update_list.size() && ix < b->_patient_medication_update_list.size(); ix++)
  {
    CHECK(a->_patient_medication_update_list[ix].first == b->_patient_medication_update_list[ix].first);
    CHECK_IDL(a->_patient_medication_update_list[ix].second, b->_patient_medication_update_list[ix].second);
  }
  // Check Medication Reqs
  CHECK(a->_patient_medication_req_update_list.size() == b->_patient_medication_req_update_list.size());
  for (size_t ix = 0; ix < a->_patient_medication_req_update_list.size() && ix < b->_patient_medication_req_update_list.size(); ix++)
  {
    CHECK(a->_patient_medication_req_update_list[ix].first == b->_patient_medication_req_update_list[ix].first);
    CHECK_IDL(a->_patient_medication_req_update_list[ix].second, b->_patient_medication_req_update_list[ix].second);
  }
  // Check Observations
  CHECK(a->_observation_update_list.size() == b->_observation_update_list.size());
  for (size_t ix = 0; ix < a->_observation_update_list.size() && ix < b->_observation_update_list.size(); ix++)
  {
    CHECK(a->_observation_update_list[ix].first == b->_observation_update_list[ix].first);
    CHECK_IDL(a->_observation_update_list[ix].second, b->_observation_update_list[ix].second);
  }
  // Check Observation Components
  CHECK(a->_observation_component_update_list.size() == b->_observation_component_update_list.size());
  for (size_t ix = 0; ix < a->_observation_component_update_list.size() && ix < b->_observation_component_update_list.size(); ix++)
  {
    CHECK(a->_observation_component_update_list[ix].first == b->_observation_component_update_list[ix].first);
    CHECK_IDL(a->_observation_component_update_list[ix].second, b->_observation_component_update_list[ix].second);
  }
  // Check Diagnostic Reports
  CHECK(a->_diagnostic_report_update_list.size() == b->_diagnostic_report_update_list.size());
  for (size_t ix = 0; ix < a->_diagnostic_report_update_list.size() && ix < b->_diagnostic_report_update_list.size(); ix++)
  {
    CHECK(a->_diagnostic_report_update_list[ix].first == b->_diagnostic_report_update_list[ix].first);
    CHECK_IDL(a->_diagnostic_report_update_list[ix].second, b->_diagnostic_report_update_list[ix].second);
  }
}

#endif // CATCH_COMPARE_DATA_STORE_H
