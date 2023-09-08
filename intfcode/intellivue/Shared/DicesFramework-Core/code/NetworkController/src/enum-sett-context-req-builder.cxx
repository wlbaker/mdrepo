#include "enum-sett-context-req-builder.h"
#include <enumSupport.h>

EnumSettContextReqBuilder::EnumSettContextReqBuilder() :
  EnumContextTypeBuilder()
{

}

EnumSettContextReqBuilder::~EnumSettContextReqBuilder()
{

}

const std::string EnumSettContextReqBuilder::get_topic_name()
{
  return ice::EnumerationSettContextReqTopic;
}
