#ifndef PATIENT_DEMOGRAPHICS_BUILDER_H
#define PATIENT_DEMOGRAPHICS_BUILDER_H

#include "patient-demographics-type-builder.h"

enum class DicesRcEntityBuilder;

class PatientDemographicsBuilder : public PatientDemographicsTypeBuilder
{
public:
  PatientDemographicsBuilder();
  ~PatientDemographicsBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  PatientDemographicsBuilder(const PatientDemographicsBuilder &other);
  PatientDemographicsBuilder &operator=(const PatientDemographicsBuilder &other);
};

#endif // PATIENT_DEMOGRAPHICS_BUILDER_H
