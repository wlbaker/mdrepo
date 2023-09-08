#include "numeric-calc-context-req-builder.h"
#include <numericSupport.h>

NumericCalcContextReqBuilder::NumericCalcContextReqBuilder() :
  NumericContextTypeBuilder()
{

}

NumericCalcContextReqBuilder::~NumericCalcContextReqBuilder()
{

}

const std::string NumericCalcContextReqBuilder::get_topic_name()
{
  return ice::NumericCalcContextReqTopic;
}
