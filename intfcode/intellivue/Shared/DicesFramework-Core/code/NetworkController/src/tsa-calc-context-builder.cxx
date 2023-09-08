#include "tsa-calc-context-builder.h"
#include <tsaSupport.h>

TSACalcContextBuilder::TSACalcContextBuilder() :
  TSAContextTypeBuilder()
{

}

TSACalcContextBuilder::~TSACalcContextBuilder()
{

}

const std::string TSACalcContextBuilder::get_topic_name()
{
  return ice::TSACalcContextTopic;
}
