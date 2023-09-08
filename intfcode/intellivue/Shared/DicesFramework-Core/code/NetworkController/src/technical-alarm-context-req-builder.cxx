#include "technical-alarm-context-req-builder.h"
#include <alarmSupport.h>

TechnicalAlarmContextReqBuilder::TechnicalAlarmContextReqBuilder() :
  AlarmContextTypeBuilder()
{

}

TechnicalAlarmContextReqBuilder::~TechnicalAlarmContextReqBuilder()
{

}

const std::string TechnicalAlarmContextReqBuilder::get_topic_name()
{
  return ice::TechnicalAlarmContextReqTopic;
}
