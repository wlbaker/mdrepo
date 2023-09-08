#include "dsa-calc-context-builder.h"
#include <dsaSupport.h>

DSACalcContextBuilder::DSACalcContextBuilder() :
  DSAContextTypeBuilder()
{

}

DSACalcContextBuilder::~DSACalcContextBuilder()
{

}

const std::string DSACalcContextBuilder::get_topic_name()
{
  return ice::DSACalcContextTopic;
}
