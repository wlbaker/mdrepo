#include "numeric-sett-context-builder.h"
#include <numericSupport.h>

NumericSettContextBuilder::NumericSettContextBuilder() :
  NumericContextTypeBuilder()
{

}

NumericSettContextBuilder::~NumericSettContextBuilder()
{

}

const std::string NumericSettContextBuilder::get_topic_name()
{
  return ice::NumericSettContextTopic;
}
