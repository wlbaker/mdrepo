#include "clock-builder.h"
#include "clockSupport.h"

ClockBuilder::ClockBuilder() :
  ClockTypeBuilder()
{

}

ClockBuilder::~ClockBuilder()
{

}

const std::string ClockBuilder::get_topic_name()
{
  return ice::ClockTopic;
}
