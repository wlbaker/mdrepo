#include "patient-demographics-req-builder.h"
#include "patdemoSupport.h"

PatientDemographicsReqBuilder::PatientDemographicsReqBuilder() :
  PatientDemographicsTypeBuilder()
{

}

PatientDemographicsReqBuilder::~PatientDemographicsReqBuilder()
{

}

const std::string PatientDemographicsReqBuilder::get_topic_name()
{
  return ice::PatientDemographicsReqTopic;
}
