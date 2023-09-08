#ifndef PATIENT_DEMOGRAPHICS_TYPE_BUILDER_H
#define PATIENT_DEMOGRAPHICS_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class PatientDemographicsTypeBuilder : public AbstractTopicBuilder
{
public:
  PatientDemographicsTypeBuilder();
  ~PatientDemographicsTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  PatientDemographicsTypeBuilder(const PatientDemographicsTypeBuilder &other);
  PatientDemographicsTypeBuilder &operator=(const PatientDemographicsTypeBuilder &other);
};

#endif // PATIENT_DEMOGRAPHICS_TYPE_BUILDER_H
