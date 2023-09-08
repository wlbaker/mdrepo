#include "rtsa-calc-context-builder.h"
#include <rtsaSupport.h>

RTSACalcContextBuilder::RTSACalcContextBuilder() :
  RTSAContextTypeBuilder()
{

}

RTSACalcContextBuilder::~RTSACalcContextBuilder()
{

}

const std::string RTSACalcContextBuilder::get_topic_name()
{
  return ice::RTSACalcContextTopic;
}
