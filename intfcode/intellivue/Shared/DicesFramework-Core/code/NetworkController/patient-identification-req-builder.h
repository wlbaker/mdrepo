#ifndef PATIENT_IDENTIFICATION_REQ_BUILDER_H
#define PATIENT_IDENTIFICATION_REQ_BUILDER_H

#include "patient-identification-type-builder.h"

enum class DicesRcEntityBuilder;

class PatientIdentificationReqBuilder : public PatientIdentificationTypeBuilder
{
public:
  PatientIdentificationReqBuilder();
  ~PatientIdentificationReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  PatientIdentificationReqBuilder(const PatientIdentificationReqBuilder &other);
  PatientIdentificationReqBuilder &operator=(const PatientIdentificationReqBuilder &other);
};

#endif // PATIENT_IDENTIFICATION_REQ_BUILDER_H
