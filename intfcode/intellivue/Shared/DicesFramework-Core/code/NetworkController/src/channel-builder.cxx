#include "channel-builder.h"

#include <ndds_namespace_cpp.h>
#include <channelSupport.h>

#include "rc-entity-builder.h"

ChannelBuilder::ChannelBuilder() :
  AbstractTopicBuilder()
{

}

ChannelBuilder::~ChannelBuilder()
{

}

DicesRcEntityBuilder ChannelBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::ChannelTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string ChannelBuilder::get_type_name()
{
  return ice::ChannelTypeSupport::get_type_name();
}

const std::string ChannelBuilder::get_topic_name()
{
  return ice::ChannelTopic;
}
