#include "enum-meas-context-req-builder.h"
#include <enumSupport.h>

EnumMeasContextReqBuilder::EnumMeasContextReqBuilder() :
  EnumContextTypeBuilder()
{

}

EnumMeasContextReqBuilder::~EnumMeasContextReqBuilder()
{

}

const std::string EnumMeasContextReqBuilder::get_topic_name()
{
  return ice::EnumerationMeasContextReqTopic;
}
