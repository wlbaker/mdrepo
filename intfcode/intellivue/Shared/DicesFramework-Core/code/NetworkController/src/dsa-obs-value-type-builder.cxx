#include "dsa-obs-value-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <dsaSupport.h>

#include "rc-entity-builder.h"

DSAObsValueTypeBuilder::DSAObsValueTypeBuilder() :
  AbstractTopicBuilder()
{

}

DSAObsValueTypeBuilder::~DSAObsValueTypeBuilder()
{

}

DicesRcEntityBuilder DSAObsValueTypeBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::DSAObservedValueTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string DSAObsValueTypeBuilder::get_type_name()
{
  return ice::DSAObservedValueTypeSupport::get_type_name();
}
