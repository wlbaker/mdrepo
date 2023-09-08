#ifndef PATIENT_IDENTIFICATION_ERROR_BUILDER_H
#define PATIENT_IDENTIFICATION_ERROR_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class PatientIdentificationErrorBuilder : public AbstractTopicBuilder
{
public:
  PatientIdentificationErrorBuilder();
  ~PatientIdentificationErrorBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_topic_name();

  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  PatientIdentificationErrorBuilder(const PatientIdentificationErrorBuilder &other);
  PatientIdentificationErrorBuilder &operator=(const PatientIdentificationErrorBuilder &other);
};

#endif // PATIENT_IDENTIFICATION_ERROR_BUILDER_H
