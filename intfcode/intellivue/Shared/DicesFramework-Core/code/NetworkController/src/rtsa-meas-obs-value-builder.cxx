#include "rtsa-meas-obs-value-builder.h"
#include <rtsaSupport.h>

RTSAMeasObsValueBuilder::RTSAMeasObsValueBuilder() :
  RTSAObsValueTypeBuilder()
{

}

RTSAMeasObsValueBuilder::~RTSAMeasObsValueBuilder()
{

}

const std::string RTSAMeasObsValueBuilder::get_topic_name()
{
  return ice::RTSAMeasObservedValueTopic;
}
