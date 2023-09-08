#include "enum-calc-context-builder.h"
#include <enumSupport.h>

EnumCalcContextBuilder::EnumCalcContextBuilder() :
  EnumContextTypeBuilder()
{

}

EnumCalcContextBuilder::~EnumCalcContextBuilder()
{

}

const std::string EnumCalcContextBuilder::get_topic_name()
{
  return ice::EnumerationCalcContextTopic;
}
