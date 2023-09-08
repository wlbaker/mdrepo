#include "rtsa-calc-obs-value-builder.h"
#include <rtsaSupport.h>

RTSACalcObsValueBuilder::RTSACalcObsValueBuilder() :
  RTSAObsValueTypeBuilder()
{

}

RTSACalcObsValueBuilder::~RTSACalcObsValueBuilder()
{

}

const std::string RTSACalcObsValueBuilder::get_topic_name()
{
  return ice::RTSACalcObservedValueTopic;
}
