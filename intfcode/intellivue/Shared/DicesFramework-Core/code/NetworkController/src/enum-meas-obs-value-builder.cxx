#include "enum-meas-obs-value-builder.h"
#include <enumSupport.h>

EnumMeasObsValueBuilder::EnumMeasObsValueBuilder() :
  EnumObsValueTypeBuilder()
{

}

EnumMeasObsValueBuilder::~EnumMeasObsValueBuilder()
{

}

const std::string EnumMeasObsValueBuilder::get_topic_name()
{
  return ice::EnumerationMeasObservedValueTopic;
}
