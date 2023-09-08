#include "allergy-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <allergySupport.h>

#include "rc-entity-builder.h"

#include "network-controller.h"

AllergyTypeBuilder::AllergyTypeBuilder() :
  AbstractTopicBuilder()
{

}

AllergyTypeBuilder::~AllergyTypeBuilder()
{

}

DicesRcEntityBuilder AllergyTypeBuilder::register_type()
{
  if(!NetworkController::instance()->get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::AllergyTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string AllergyTypeBuilder::get_type_name()
{
  return ice::AllergyTypeSupport::get_type_name();
}
