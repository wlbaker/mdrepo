#include "reminder-signal-builder.h"

#include <ndds_namespace_cpp.h>
#include <alarmSupport.h>

#include "rc-entity-builder.h"

ReminderSignalBuilder::ReminderSignalBuilder() :
  AbstractTopicBuilder()
{

}

ReminderSignalBuilder::~ReminderSignalBuilder()
{

}

DicesRcEntityBuilder ReminderSignalBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::ReminderSignalTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string ReminderSignalBuilder::get_type_name()
{
  return ice::ReminderSignalTypeSupport::get_type_name();
}

const std::string ReminderSignalBuilder::get_topic_name()
{
  return ice::ReminderSignalTopic;
}
