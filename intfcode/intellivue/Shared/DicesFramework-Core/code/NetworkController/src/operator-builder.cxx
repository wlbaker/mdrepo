#include "operator-builder.h"
#include <operatorSupport.h>

OperatorBuilder::OperatorBuilder() :
  OperatorTypeBuilder()
{

}

OperatorBuilder::~OperatorBuilder()
{

}

const std::string OperatorBuilder::get_topic_name()
{
  return ice::OperatorTopic;
}
