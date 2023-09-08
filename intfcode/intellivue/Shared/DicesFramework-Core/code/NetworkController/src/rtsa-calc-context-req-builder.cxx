#include "rtsa-calc-context-req-builder.h"
#include <rtsaSupport.h>

RTSACalcContextReqBuilder::RTSACalcContextReqBuilder() :
  RTSAContextTypeBuilder()
{

}

RTSACalcContextReqBuilder::~RTSACalcContextReqBuilder()
{

}

const std::string RTSACalcContextReqBuilder::get_topic_name()
{
  return ice::RTSACalcContextReqTopic;
}
