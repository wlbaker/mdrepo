#include "vmd-builder.h"

#include <ndds_namespace_cpp.h>
#include <vmdSupport.h>

#include "rc-entity-builder.h"

VMDBuilder::VMDBuilder() :
  AbstractTopicBuilder()
{

}

VMDBuilder::~VMDBuilder()
{

}

DicesRcEntityBuilder VMDBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::VMDTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string VMDBuilder::get_type_name()
{
  return ice::VMDTypeSupport::get_type_name();
}

const std::string VMDBuilder::get_topic_name()
{
  return ice::VMDTopic;
}
