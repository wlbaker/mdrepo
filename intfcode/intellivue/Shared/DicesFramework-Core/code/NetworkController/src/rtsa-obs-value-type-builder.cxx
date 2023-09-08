#include "rtsa-obs-value-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <rtsaSupport.h>

#include "rc-entity-builder.h"

RTSAObsValueTypeBuilder::RTSAObsValueTypeBuilder() :
  AbstractTopicBuilder()
{

}

RTSAObsValueTypeBuilder::~RTSAObsValueTypeBuilder()
{

}

DicesRcEntityBuilder RTSAObsValueTypeBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::RTSAObservedValueTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string RTSAObsValueTypeBuilder::get_type_name()
{
  return ice::RTSAObservedValueTypeSupport::get_type_name();
}
