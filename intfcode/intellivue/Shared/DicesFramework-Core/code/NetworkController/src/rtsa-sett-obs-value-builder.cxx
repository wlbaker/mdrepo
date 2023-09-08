#include "rtsa-sett-obs-value-builder.h"
#include <rtsaSupport.h>

RTSASettObsValueBuilder::RTSASettObsValueBuilder() :
  RTSAObsValueTypeBuilder()
{

}

RTSASettObsValueBuilder::~RTSASettObsValueBuilder()
{

}

const std::string RTSASettObsValueBuilder::get_topic_name()
{
  return ice::RTSASettObservedValueTopic;
}
