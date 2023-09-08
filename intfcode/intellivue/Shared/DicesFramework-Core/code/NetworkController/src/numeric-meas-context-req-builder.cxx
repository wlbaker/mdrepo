#include "numeric-meas-context-req-builder.h"
#include <numericSupport.h>

NumericMeasContextReqBuilder::NumericMeasContextReqBuilder() :
  NumericContextTypeBuilder()
{

}

NumericMeasContextReqBuilder::~NumericMeasContextReqBuilder()
{

}

const std::string NumericMeasContextReqBuilder::get_topic_name()
{
  return ice::NumericMeasContextReqTopic;
}
