#include "physiological-alarm-context-builder.h"
#include <alarmSupport.h>

PhysiologicalAlarmContextBuilder::PhysiologicalAlarmContextBuilder() :
  AlarmContextTypeBuilder()
{

}

PhysiologicalAlarmContextBuilder::~PhysiologicalAlarmContextBuilder()
{

}

const std::string PhysiologicalAlarmContextBuilder::get_topic_name()
{
  return ice::PhysiologicalAlarmContextTopic;
}
