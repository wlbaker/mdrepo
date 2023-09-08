#include "enum-sett-obs-value-req-builder.h"
#include <enumSupport.h>

EnumSettObsValueReqBuilder::EnumSettObsValueReqBuilder() :
  EnumObsValueTypeBuilder()
{

}

EnumSettObsValueReqBuilder::~EnumSettObsValueReqBuilder()
{

}

const std::string EnumSettObsValueReqBuilder::get_topic_name()
{
  return ice::EnumerationSettObservedValueReqTopic;
}
