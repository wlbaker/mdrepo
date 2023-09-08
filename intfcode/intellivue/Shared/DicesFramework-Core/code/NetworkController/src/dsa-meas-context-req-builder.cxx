#include "dsa-meas-context-req-builder.h"
#include <dsaSupport.h>

DSAMeasContextReqBuilder::DSAMeasContextReqBuilder() :
  DSAContextTypeBuilder()
{

}

DSAMeasContextReqBuilder::~DSAMeasContextReqBuilder()
{

}

const std::string DSAMeasContextReqBuilder::get_topic_name()
{
  return ice::DSAMeasContextReqTopic;
}
