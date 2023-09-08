#include "patient-identification-builder.h"
#include <patdemoSupport.h>

PatientIdentificationBuilder::PatientIdentificationBuilder() :
  PatientIdentificationTypeBuilder()
{

}

PatientIdentificationBuilder::~PatientIdentificationBuilder()
{

}

const std::string PatientIdentificationBuilder::get_topic_name()
{
  return ice::PatientIdentificationTopic;
}
