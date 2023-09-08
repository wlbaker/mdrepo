#include "clock-req-builder.h"
#include "clockSupport.h"

ClockReqBuilder::ClockReqBuilder() :
  ClockTypeBuilder()
{

}

ClockReqBuilder::~ClockReqBuilder()
{

}

const std::string ClockReqBuilder::get_topic_name()
{
  return ice::ClockTopicReq;
}
