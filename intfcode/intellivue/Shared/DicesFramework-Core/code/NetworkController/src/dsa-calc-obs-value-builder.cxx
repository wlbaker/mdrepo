#include "dsa-calc-obs-value-builder.h"
#include <dsaSupport.h>

DSACalcObsValueBuilder::DSACalcObsValueBuilder() :
  DSAObsValueTypeBuilder()
{

}

DSACalcObsValueBuilder::~DSACalcObsValueBuilder()
{

}

const std::string DSACalcObsValueBuilder::get_topic_name()
{
  return ice::DSACalcObservedValueTopic;
}
