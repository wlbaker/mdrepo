#include "numeric-calc-context-builder.h"
#include <numericSupport.h>

NumericCalcContextBuilder::NumericCalcContextBuilder() :
  NumericContextTypeBuilder()
{

}

NumericCalcContextBuilder::~NumericCalcContextBuilder()
{

}

const std::string NumericCalcContextBuilder::get_topic_name()
{
  return ice::NumericCalcContextTopic;
}
