#include "rtsa-sett-context-builder.h"
#include <rtsaSupport.h>

RTSASettContextBuilder::RTSASettContextBuilder() :
  RTSAContextTypeBuilder()
{

}

RTSASettContextBuilder::~RTSASettContextBuilder()
{

}

const std::string RTSASettContextBuilder::get_topic_name()
{
  return ice::RTSASettContextTopic;
}
