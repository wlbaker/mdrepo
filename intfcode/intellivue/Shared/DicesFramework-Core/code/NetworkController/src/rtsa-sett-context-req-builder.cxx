#include "rtsa-sett-context-req-builder.h"
#include <rtsaSupport.h>

RTSASettContextReqBuilder::RTSASettContextReqBuilder() :
  RTSAContextTypeBuilder()
{

}

RTSASettContextReqBuilder::~RTSASettContextReqBuilder()
{

}

const std::string RTSASettContextReqBuilder::get_topic_name()
{
  return ice::RTSASettContextReqTopic;
}
