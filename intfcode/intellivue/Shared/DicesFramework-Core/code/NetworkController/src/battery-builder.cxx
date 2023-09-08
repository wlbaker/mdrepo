#include "battery-builder.h"

#include <ndds_namespace_cpp.h>
#include <batterySupport.h>

#include "rc-entity-builder.h"

BatteryBuilder::BatteryBuilder() :
  AbstractTopicBuilder()
{

}

BatteryBuilder::~BatteryBuilder()
{

}

DicesRcEntityBuilder BatteryBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::BatteryTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string BatteryBuilder::get_type_name()
{
  return ice::BatteryTypeSupport::get_type_name();
}

const std::string BatteryBuilder::get_topic_name()
{
  return ice::BatteryTopic;
}
