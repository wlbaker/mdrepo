#include "abstract-content-filtered-topic-builder.h"

#include <ndds_namespace_cpp.h>

#include "rc-entity-builder.h"
#include "network-controller.h"

struct AbstractContentFilteredTopicBuilder::impl
{
  std::string _content_filtered_topic_name;

  impl(std::string content_filtered_topic_name)
    :_content_filtered_topic_name(content_filtered_topic_name)
  {
  }

  ~impl() = default;

  DicesRcEntityBuilder construct_topic(AbstractContentFilteredTopicBuilder& src)
  {
    if(!NetworkController::instance())
    {
      return DicesRcEntityBuilder::NETWORK_CONTROLLER_POINTER_IS_NULL;
    }

    if(!NetworkController::instance()->get_participant())
    {
      return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
    }

    if(src.get_topic_name().empty())
    {
      return DicesRcEntityBuilder::TOPIC_NAME_IS_EMPTY;
    }

    DDSTopicDescription *topic =
        NetworkController::instance()->
        get_participant()->
        lookup_topicdescription(src.get_topic_name().c_str());

    if(!topic)
    {
      topic = NetworkController::instance()->
              get_participant()->
              create_topic(
                src.get_topic_name().c_str(),
                src.get_type_name().c_str(),
                DDS_TOPIC_QOS_DEFAULT,
                NULL,
                DDS_STATUS_MASK_NONE);
    }

    if(!topic)
    {
      return DicesRcEntityBuilder::CREATE_TOPIC_FAILED;
    }

    DDSTopic *narrowed_topic = DDSTopic::narrow(topic);

    if(!narrowed_topic)
    {
      return DicesRcEntityBuilder::FAIL;
    }

    DDSTopicDescription *cft =
        NetworkController::instance()->
        get_participant()->
        lookup_topicdescription(_content_filtered_topic_name.c_str());

    if(!cft)
    {
      cft = src.get_participant()->create_contentfilteredtopic(
               _content_filtered_topic_name.c_str(),
               narrowed_topic,
               "*", //expression
                DDS::StringSeq()); //parameters
    }

    if(!cft)
    {
      return DicesRcEntityBuilder::FAIL;
    }

    src.set_topic(cft);

    return DicesRcEntityBuilder::OK;
  }
};

AbstractContentFilteredTopicBuilder::AbstractContentFilteredTopicBuilder(std::string content_filtered_topic_name) :
  AbstractEntityBuilder(),
  _pimpl(nullptr)
{
  _pimpl = std::unique_ptr<impl>(new (std::nothrow) impl(content_filtered_topic_name));
  if (!_pimpl)
  {
    return;
  }
}

AbstractContentFilteredTopicBuilder::~AbstractContentFilteredTopicBuilder()
{
}

DicesRcEntityBuilder AbstractContentFilteredTopicBuilder::construct_topic()
{
  return _pimpl->construct_topic(*this);
}
