#include "patient-medication-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <exprSupport.h>

#include "rc-entity-builder.h"

PatientMedicationTypeBuilder::PatientMedicationTypeBuilder() :
  AbstractTopicBuilder()
{

}

PatientMedicationTypeBuilder::~PatientMedicationTypeBuilder()
{

}

DicesRcEntityBuilder PatientMedicationTypeBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      expr::PatientMedicationTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string PatientMedicationTypeBuilder::get_type_name()
{
  return expr::PatientMedicationTypeSupport::get_type_name();
}
