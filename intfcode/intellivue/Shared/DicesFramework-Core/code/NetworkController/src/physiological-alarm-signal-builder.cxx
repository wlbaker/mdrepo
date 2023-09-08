#include "physiological-alarm-signal-builder.h"
#include <alarmSupport.h>

PhysiologicalAlarmSignalBuilder::PhysiologicalAlarmSignalBuilder() :
  AlarmSignalTypeBuilder()
{

}

PhysiologicalAlarmSignalBuilder::~PhysiologicalAlarmSignalBuilder()
{

}

const std::string PhysiologicalAlarmSignalBuilder::get_topic_name()
{
  return ice::PhysiologicalAlarmSignalTopic;
}
