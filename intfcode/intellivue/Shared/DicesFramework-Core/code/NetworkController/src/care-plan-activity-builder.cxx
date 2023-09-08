#include "care-plan-activity-builder.h"

#include <ndds_namespace_cpp.h>
#include <cplanSupport.h>

#include "rc-entity-builder.h"

CarePlanActivityBuilder::CarePlanActivityBuilder() :
  AbstractTopicBuilder()
{

}

CarePlanActivityBuilder::~CarePlanActivityBuilder()
{

}

DicesRcEntityBuilder CarePlanActivityBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::CarePlanActivityTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string CarePlanActivityBuilder::get_type_name()
{
  return ice::CarePlanActivityTypeSupport::get_type_name();
}

const std::string CarePlanActivityBuilder::get_topic_name()
{
  return ice::CarePlanActivityTopic;
}
