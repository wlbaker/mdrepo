#include "rtsa-context-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <rtsaSupport.h>

#include "rc-entity-builder.h"

RTSAContextTypeBuilder::RTSAContextTypeBuilder() :
  AbstractTopicBuilder()
{

}

RTSAContextTypeBuilder::~RTSAContextTypeBuilder()
{

}

DicesRcEntityBuilder RTSAContextTypeBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::RTSAContextTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string RTSAContextTypeBuilder::get_type_name()
{
  return ice::RTSAContextTypeSupport::get_type_name();
}
