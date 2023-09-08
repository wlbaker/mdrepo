#include "patient-demographics-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <patdemoSupport.h>

#include "rc-entity-builder.h"

PatientDemographicsTypeBuilder::PatientDemographicsTypeBuilder() :
  AbstractTopicBuilder()
{

}

PatientDemographicsTypeBuilder::~PatientDemographicsTypeBuilder()
{

}

DicesRcEntityBuilder PatientDemographicsTypeBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::PatientDemographicsTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string PatientDemographicsTypeBuilder::get_type_name()
{
  return ice::PatientDemographicsTypeSupport::get_type_name();
}
