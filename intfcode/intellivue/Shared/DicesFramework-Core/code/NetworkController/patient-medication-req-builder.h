#ifndef PATIENT_MEDICATION_REQ_BUILDER_H
#define PATIENT_MEDICATION_REQ_BUILDER_H

#include "patient-medication-type-builder.h"

enum class DicesRcEntityBuilder;

class PatientMedicationReqBuilder : public PatientMedicationTypeBuilder
{
public:
  PatientMedicationReqBuilder();
  ~PatientMedicationReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  PatientMedicationReqBuilder(const PatientMedicationReqBuilder &other);
  PatientMedicationReqBuilder &operator=(const PatientMedicationReqBuilder &other);
};

#endif // PATIENT_MEDICATION_REQ_BUILDER_H
