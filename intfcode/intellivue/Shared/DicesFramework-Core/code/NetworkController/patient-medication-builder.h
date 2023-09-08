#ifndef PATIENT_MEDICATION_BUILDER_H
#define PATIENT_MEDICATION_BUILDER_H

#include "patient-medication-type-builder.h"

enum class DicesRcEntityBuilder;

class PatientMedicationBuilder : public PatientMedicationTypeBuilder
{
public:
  PatientMedicationBuilder();
  ~PatientMedicationBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  PatientMedicationBuilder(const PatientMedicationBuilder &other);
  PatientMedicationBuilder &operator=(const PatientMedicationBuilder &other);
};

#endif // PATIENT_MEDICATION_BUILDER_H
