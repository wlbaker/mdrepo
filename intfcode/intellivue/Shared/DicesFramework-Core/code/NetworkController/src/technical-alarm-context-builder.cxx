#include "technical-alarm-context-builder.h"
#include <alarmSupport.h>

TechnicalAlarmContextBuilder::TechnicalAlarmContextBuilder() :
  AlarmContextTypeBuilder()
{

}

TechnicalAlarmContextBuilder::~TechnicalAlarmContextBuilder()
{

}

const std::string TechnicalAlarmContextBuilder::get_topic_name()
{
  return ice::TechnicalAlarmContextTopic;
}
