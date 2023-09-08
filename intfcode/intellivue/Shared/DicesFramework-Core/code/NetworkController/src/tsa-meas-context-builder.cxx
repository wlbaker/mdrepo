#include "tsa-meas-context-builder.h"
#include <tsaSupport.h>

TSAMeasContextBuilder::TSAMeasContextBuilder() :
  TSAContextTypeBuilder()
{

}

TSAMeasContextBuilder::~TSAMeasContextBuilder()
{

}

const std::string TSAMeasContextBuilder::get_topic_name()
{
  return ice::TSAMeasContextTopic;
}
