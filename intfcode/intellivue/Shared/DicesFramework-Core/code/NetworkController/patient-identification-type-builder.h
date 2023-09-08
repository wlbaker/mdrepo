#ifndef PATIENT_IDENTIFICATION_TYPE_BUILDER_H
#define PATIENT_IDENTIFICATION_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class PatientIdentificationTypeBuilder : public AbstractTopicBuilder
{
public:
  PatientIdentificationTypeBuilder();
  ~PatientIdentificationTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  PatientIdentificationTypeBuilder(const PatientIdentificationTypeBuilder &other);
  PatientIdentificationTypeBuilder &operator=(const PatientIdentificationTypeBuilder &other);
};

#endif // PATIENT_IDENTIFICATION_TYPE_BUILDER_H
