#include "enum-sett-context-builder.h"
#include <enumSupport.h>

EnumSettContextBuilder::EnumSettContextBuilder() :
  EnumContextTypeBuilder()
{

}

EnumSettContextBuilder::~EnumSettContextBuilder()
{

}

const std::string EnumSettContextBuilder::get_topic_name()
{
  return ice::EnumerationSettContextTopic;
}
