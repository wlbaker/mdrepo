#include "technical-alarm-signal-builder.h"
#include <alarmSupport.h>

TechnicalAlarmSignalBuilder::TechnicalAlarmSignalBuilder() :
  AlarmSignalTypeBuilder()
{

}

TechnicalAlarmSignalBuilder::~TechnicalAlarmSignalBuilder()
{

}

const std::string TechnicalAlarmSignalBuilder::get_topic_name()
{
  return ice::TechnicalAlarmSignalTopic;
}
