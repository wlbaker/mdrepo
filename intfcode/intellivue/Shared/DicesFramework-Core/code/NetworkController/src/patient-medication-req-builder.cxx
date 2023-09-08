#include "patient-medication-req-builder.h"
#include "exprSupport.h"

PatientMedicationReqBuilder::PatientMedicationReqBuilder() :
  PatientMedicationTypeBuilder()
{

}

PatientMedicationReqBuilder::~PatientMedicationReqBuilder()
{

}

const std::string PatientMedicationReqBuilder::get_topic_name()
{
  return expr::PatientMedicationReqTopic;
}
