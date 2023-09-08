#include "enum-calc-context-req-builder.h"
#include <enumSupport.h>

EnumCalcContextReqBuilder::EnumCalcContextReqBuilder() :
  EnumContextTypeBuilder()
{

}

EnumCalcContextReqBuilder::~EnumCalcContextReqBuilder()
{

}

const std::string EnumCalcContextReqBuilder::get_topic_name()
{
  return ice::EnumerationCalcContextReqTopic;
}
