#include "enum-meas-context-builder.h"
#include <enumSupport.h>

EnumMeasContextBuilder::EnumMeasContextBuilder() :
  EnumContextTypeBuilder()
{

}

EnumMeasContextBuilder::~EnumMeasContextBuilder()
{

}

const std::string EnumMeasContextBuilder::get_topic_name()
{
  return ice::EnumerationMeasContextTopic;
}
