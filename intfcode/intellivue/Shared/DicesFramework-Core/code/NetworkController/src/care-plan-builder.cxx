#include "care-plan-builder.h"

#include <ndds_namespace_cpp.h>
#include <cplanSupport.h>

#include "rc-entity-builder.h"

CarePlanBuilder::CarePlanBuilder() :
  AbstractTopicBuilder()
{

}

CarePlanBuilder::~CarePlanBuilder()
{

}

DicesRcEntityBuilder CarePlanBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::CarePlanTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string CarePlanBuilder::get_type_name()
{
  return ice::CarePlanTypeSupport::get_type_name();
}

const std::string CarePlanBuilder::get_topic_name()
{
  return ice::CarePlanTopic;
}
