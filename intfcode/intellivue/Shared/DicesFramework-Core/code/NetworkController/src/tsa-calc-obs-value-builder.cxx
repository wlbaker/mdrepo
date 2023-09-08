#include "tsa-calc-obs-value-builder.h"
#include <tsaSupport.h>

TSACalcObsValueBuilder::TSACalcObsValueBuilder() :
  TSAObsValueTypeBuilder()
{

}

TSACalcObsValueBuilder::~TSACalcObsValueBuilder()
{

}

const std::string TSACalcObsValueBuilder::get_topic_name()
{
  return ice::TSACalcObservedValueTopic;
}
