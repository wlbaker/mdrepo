#include "physiological-alarm-context-req-builder.h"
#include <alarmSupport.h>

PhysiologicalAlarmContextReqBuilder::PhysiologicalAlarmContextReqBuilder() :
  AlarmContextTypeBuilder()
{

}

PhysiologicalAlarmContextReqBuilder::~PhysiologicalAlarmContextReqBuilder()
{

}

const std::string PhysiologicalAlarmContextReqBuilder::get_topic_name()
{
  return ice::PhysiologicalAlarmContextReqTopic;
}
