#include "trend-event-builder.h"

#include <ndds_namespace_cpp.h>
#include <trendevtSupport.h>

#include "rc-entity-builder.h"

TrendEventBuilder::TrendEventBuilder() :
  AbstractTopicBuilder()
{

}

TrendEventBuilder::~TrendEventBuilder()
{

}

DicesRcEntityBuilder TrendEventBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      docbox::TrendEventTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string TrendEventBuilder::get_type_name()
{
  return docbox::TrendEventTypeSupport::get_type_name();
}

const std::string TrendEventBuilder::get_topic_name()
{
  return docbox::TrendEventTopic;
}
