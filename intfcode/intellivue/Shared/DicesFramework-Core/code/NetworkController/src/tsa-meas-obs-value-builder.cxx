#include "tsa-meas-obs-value-builder.h"
#include <tsaSupport.h>

TSAMeasObsValueBuilder::TSAMeasObsValueBuilder() :
  TSAObsValueTypeBuilder()
{

}

TSAMeasObsValueBuilder::~TSAMeasObsValueBuilder()
{

}

const std::string TSAMeasObsValueBuilder::get_topic_name()
{
  return ice::TSAMeasObservedValueTopic;
}
