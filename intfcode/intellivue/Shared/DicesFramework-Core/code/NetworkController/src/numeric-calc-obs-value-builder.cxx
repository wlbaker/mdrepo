#include "numeric-calc-obs-value-builder.h"
#include <numericSupport.h>

NumericCalcObsValueBuilder::NumericCalcObsValueBuilder() :
  NumericObsValueTypeBuilder()
{

}

NumericCalcObsValueBuilder::~NumericCalcObsValueBuilder()
{

}

const std::string NumericCalcObsValueBuilder::get_topic_name()
{
  return ice::NumericCalcObservedValueTopic;
}
