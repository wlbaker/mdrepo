#include "operator-authentication-obj-builder.h"
#include <operatorSupport.h>

OperatorAuthenticationObjBuilder::OperatorAuthenticationObjBuilder() :
  OperatorAuthenticationTypeBuilder()
{

}

OperatorAuthenticationObjBuilder::~OperatorAuthenticationObjBuilder()
{

}

const std::string OperatorAuthenticationObjBuilder::get_topic_name()
{
  return ice::OperatorAuthenticationObjTopic;
}
