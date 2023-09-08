#include "dsa-meas-obs-value-builder.h"
#include <dsaSupport.h>

DSAMeasObsValueBuilder::DSAMeasObsValueBuilder() :
  DSAObsValueTypeBuilder()
{

}

DSAMeasObsValueBuilder::~DSAMeasObsValueBuilder()
{

}

const std::string DSAMeasObsValueBuilder::get_topic_name()
{
  return ice::DSAMeasObservedValueTopic;
}
