#include "numeric-meas-context-builder.h"
#include <numericSupport.h>

NumericMeasContextBuilder::NumericMeasContextBuilder() :
  NumericContextTypeBuilder()
{

}

NumericMeasContextBuilder::~NumericMeasContextBuilder()
{

}

const std::string NumericMeasContextBuilder::get_topic_name()
{
  return ice::NumericMeasContextTopic;
}
