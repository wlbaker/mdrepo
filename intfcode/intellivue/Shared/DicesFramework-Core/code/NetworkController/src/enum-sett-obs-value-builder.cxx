#include "enum-sett-obs-value-builder.h"
#include <enumSupport.h>

EnumSettObsValueBuilder::EnumSettObsValueBuilder() :
  EnumObsValueTypeBuilder()
{

}

EnumSettObsValueBuilder::~EnumSettObsValueBuilder()
{

}

const std::string EnumSettObsValueBuilder::get_topic_name()
{
  return ice::EnumerationSettObservedValueTopic;
}
