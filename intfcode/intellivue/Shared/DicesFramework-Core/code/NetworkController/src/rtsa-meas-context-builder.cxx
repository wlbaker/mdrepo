#include "rtsa-meas-context-builder.h"
#include <rtsaSupport.h>

RTSAMeasContextBuilder::RTSAMeasContextBuilder() :
  RTSAContextTypeBuilder()
{

}

RTSAMeasContextBuilder::~RTSAMeasContextBuilder()
{

}

const std::string RTSAMeasContextBuilder::get_topic_name()
{
  return ice::RTSAMeasContextTopic;
}
