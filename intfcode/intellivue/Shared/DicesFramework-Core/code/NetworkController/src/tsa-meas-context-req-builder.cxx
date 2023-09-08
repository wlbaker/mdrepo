#include "tsa-meas-context-req-builder.h"
#include <tsaSupport.h>

TSAMeasContextReqBuilder::TSAMeasContextReqBuilder() :
  TSAContextTypeBuilder()
{

}

TSAMeasContextReqBuilder::~TSAMeasContextReqBuilder()
{

}

const std::string TSAMeasContextReqBuilder::get_topic_name()
{
  return ice::TSAMeasContextReqTopic;
}
