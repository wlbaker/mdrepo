#ifndef PATIENT_MEDICATION_TYPE_BUILDER_H
#define PATIENT_MEDICATION_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class PatientMedicationTypeBuilder : public AbstractTopicBuilder
{
public:
  PatientMedicationTypeBuilder();
  ~PatientMedicationTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  PatientMedicationTypeBuilder(const PatientMedicationTypeBuilder &other);
  PatientMedicationTypeBuilder &operator=(const PatientMedicationTypeBuilder &other);
};

#endif // PATIENT_MEDICATION_TYPE_BUILDER_H
