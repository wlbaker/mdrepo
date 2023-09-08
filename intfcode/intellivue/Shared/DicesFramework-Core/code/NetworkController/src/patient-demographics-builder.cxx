#include "patient-demographics-builder.h"
#include "patdemoSupport.h"

PatientDemographicsBuilder::PatientDemographicsBuilder() :
  PatientDemographicsTypeBuilder()
{

}

PatientDemographicsBuilder::~PatientDemographicsBuilder()
{

}

const std::string PatientDemographicsBuilder::get_topic_name()
{
  return ice::PatientDemographicsTopic;
}
