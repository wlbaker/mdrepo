#include "numeric-meas-obs-value-builder.h"
#include <numericSupport.h>

NumericMeasObsValueBuilder::NumericMeasObsValueBuilder() :
  NumericObsValueTypeBuilder()
{

}

NumericMeasObsValueBuilder::~NumericMeasObsValueBuilder()
{

}

const std::string NumericMeasObsValueBuilder::get_topic_name()
{
  return ice::NumericMeasObservedValueTopic;
}
