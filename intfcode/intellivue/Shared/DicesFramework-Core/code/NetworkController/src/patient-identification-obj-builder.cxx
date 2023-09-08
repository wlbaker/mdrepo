#include "patient-identification-obj-builder.h"
#include <patdemoSupport.h>

PatientIdentificationObjBuilder::PatientIdentificationObjBuilder() :
  PatientIdentificationTypeBuilder()
{

}

PatientIdentificationObjBuilder::~PatientIdentificationObjBuilder()
{

}

const std::string PatientIdentificationObjBuilder::get_topic_name()
{
  return ice::PatientIdentificationObjTopic;
}
