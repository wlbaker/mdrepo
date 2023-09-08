#include "dsa-meas-context-builder.h"
#include <dsaSupport.h>

DSAMeasContextBuilder::DSAMeasContextBuilder() :
  DSAContextTypeBuilder()
{

}

DSAMeasContextBuilder::~DSAMeasContextBuilder()
{

}

const std::string DSAMeasContextBuilder::get_topic_name()
{
  return ice::DSAMeasContextTopic;
}
