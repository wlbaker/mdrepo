#include "dsa-calc-context-req-builder.h"
#include <dsaSupport.h>

DSACalcContextReqBuilder::DSACalcContextReqBuilder() :
  DSAContextTypeBuilder()
{

}

DSACalcContextReqBuilder::~DSACalcContextReqBuilder()
{

}

const std::string DSACalcContextReqBuilder::get_topic_name()
{
  return ice::DSACalcContextReqTopic;
}
