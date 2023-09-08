#include "tsa-calc-context-req-builder.h"
#include <tsaSupport.h>

TSACalcContextReqBuilder::TSACalcContextReqBuilder() :
  TSAContextTypeBuilder()
{

}

TSACalcContextReqBuilder::~TSACalcContextReqBuilder()
{

}

const std::string TSACalcContextReqBuilder::get_topic_name()
{
  return ice::TSACalcContextReqTopic;
}
