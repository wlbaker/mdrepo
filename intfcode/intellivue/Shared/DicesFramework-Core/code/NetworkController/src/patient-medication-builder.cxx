#include "patient-medication-builder.h"
#include "exprSupport.h"

PatientMedicationBuilder::PatientMedicationBuilder() :
  PatientMedicationTypeBuilder()
{

}

PatientMedicationBuilder::~PatientMedicationBuilder()
{

}

const std::string PatientMedicationBuilder::get_topic_name()
{
  return expr::PatientMedicationTopic;
}
