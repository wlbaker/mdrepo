#include "abstract-topic-builder.h"

#include <ndds_namespace_cpp.h>

#include "rc-entity-builder.h"

AbstractTopicBuilder::AbstractTopicBuilder() :
  AbstractEntityBuilder()
{

}

AbstractTopicBuilder::~AbstractTopicBuilder()
{

}

DicesRcEntityBuilder AbstractTopicBuilder::construct_topic()
{
  if(get_topic()) return DicesRcEntityBuilder::OK;

  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  if(get_topic_name().empty())
  {
    return DicesRcEntityBuilder::TOPIC_NAME_IS_EMPTY;
  }

  DDSTopic *topic =  get_participant()->
                       find_topic(get_topic_name().c_str(), DDS::DURATION_ZERO);

  if(!topic)
  {
    topic = get_participant()->
             create_topic(
               get_topic_name().c_str(),
               get_type_name().c_str(),
               DDS_TOPIC_QOS_DEFAULT,
               NULL,
               DDS_STATUS_MASK_NONE);
  }

  if(!topic)
  {
    return DicesRcEntityBuilder::CREATE_TOPIC_FAILED;
  }

  set_topic(topic);

  return DicesRcEntityBuilder::OK;
}

const std::string AbstractTopicBuilder::get_library_name()
{
  return "dices_dim_library";
}

const std::string AbstractTopicBuilder::get_qos_profile()
{
  return "dices_dim_durable_profile";
}
