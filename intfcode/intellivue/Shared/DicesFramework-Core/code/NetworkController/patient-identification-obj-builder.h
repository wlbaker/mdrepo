#ifndef PATIENT_IDENTIFICATION_OBJ_BUILDER_H
#define PATIENT_IDENTIFICATION_OBJ_BUILDER_H

#include "patient-identification-type-builder.h"

enum class DicesRcEntityBuilder;

class PatientIdentificationObjBuilder : public PatientIdentificationTypeBuilder
{
public:
  PatientIdentificationObjBuilder();
  ~PatientIdentificationObjBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  PatientIdentificationObjBuilder(const PatientIdentificationObjBuilder &other);
  PatientIdentificationObjBuilder &operator=(const PatientIdentificationObjBuilder &other);
};

#endif // PATIENT_IDENTIFICATION_OBJ_BUILDER_H
