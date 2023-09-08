#include "enum-calc-obs-value-builder.h"
#include <enumSupport.h>

EnumCalcObsValueBuilder::EnumCalcObsValueBuilder() :
  EnumObsValueTypeBuilder()
{

}

EnumCalcObsValueBuilder::~EnumCalcObsValueBuilder()
{

}

const std::string EnumCalcObsValueBuilder::get_topic_name()
{
  return ice::EnumerationCalcObservedValueTopic;
}
