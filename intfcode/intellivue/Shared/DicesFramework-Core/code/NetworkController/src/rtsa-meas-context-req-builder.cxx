#include "rtsa-meas-context-req-builder.h"
#include <rtsaSupport.h>

RTSAMeasContextReqBuilder::RTSAMeasContextReqBuilder() :
  RTSAContextTypeBuilder()
{

}

RTSAMeasContextReqBuilder::~RTSAMeasContextReqBuilder()
{

}

const std::string RTSAMeasContextReqBuilder::get_topic_name()
{
  return ice::RTSAMeasContextReqTopic;
}
