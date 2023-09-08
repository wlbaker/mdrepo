#ifndef PATIENT_IDENTIFICATION_BUILDER_H
#define PATIENT_IDENTIFICATION_BUILDER_H

#include "patient-identification-type-builder.h"

class PatientIdentificationBuilder : public PatientIdentificationTypeBuilder
{
public:
  PatientIdentificationBuilder();
  ~PatientIdentificationBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  PatientIdentificationBuilder(const PatientIdentificationBuilder &other);
  PatientIdentificationBuilder &operator=(const PatientIdentificationBuilder &other);
};

#endif // PATIENT_IDENTIFICATION_BUILDER_H
