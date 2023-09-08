#include "dsa-sett-context-builder.h"
#include <dsaSupport.h>

DSASettContextBuilder::DSASettContextBuilder() :
  DSAContextTypeBuilder()
{

}

DSASettContextBuilder::~DSASettContextBuilder()
{

}

const std::string DSASettContextBuilder::get_topic_name()
{
  return ice::DSASettContextTopic;
}
