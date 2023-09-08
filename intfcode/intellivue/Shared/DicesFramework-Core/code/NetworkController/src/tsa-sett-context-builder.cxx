#include "tsa-sett-context-builder.h"
#include <tsaSupport.h>

TSASettContextBuilder::TSASettContextBuilder() :
  TSAContextTypeBuilder()
{

}

TSASettContextBuilder::~TSASettContextBuilder()
{

}

const std::string TSASettContextBuilder::get_topic_name()
{
  return ice::TSASettContextTopic;
}
