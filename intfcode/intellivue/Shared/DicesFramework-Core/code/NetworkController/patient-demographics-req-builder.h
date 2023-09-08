#ifndef PATIENT_DEMOGRAPHICS_REQ_BUILDER_H
#define PATIENT_DEMOGRAPHICS_REQ_BUILDER_H

#include "patient-demographics-type-builder.h"

enum class DicesRcEntityBuilder;

class PatientDemographicsReqBuilder : public PatientDemographicsTypeBuilder
{
public:
  PatientDemographicsReqBuilder();
  ~PatientDemographicsReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  PatientDemographicsReqBuilder(const PatientDemographicsReqBuilder &other);
  PatientDemographicsReqBuilder &operator=(const PatientDemographicsReqBuilder &other);
};

#endif // PATIENT_DEMOGRAPHICS_REQ_BUILDER_H
