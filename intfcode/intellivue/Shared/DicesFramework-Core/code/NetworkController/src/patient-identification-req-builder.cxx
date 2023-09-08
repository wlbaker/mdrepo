#include "patient-identification-req-builder.h"
#include <patdemoSupport.h>

PatientIdentificationReqBuilder::PatientIdentificationReqBuilder() :
  PatientIdentificationTypeBuilder()
{

}

PatientIdentificationReqBuilder::~PatientIdentificationReqBuilder()
{

}

const std::string PatientIdentificationReqBuilder::get_topic_name()
{
  return ice::PatientIdentificationReqTopic;
}
