#include "operator-authentication-req-builder.h"
#include <operatorSupport.h>

OperatorAuthenticationReqBuilder::OperatorAuthenticationReqBuilder() :
  OperatorAuthenticationTypeBuilder()
{

}

OperatorAuthenticationReqBuilder::~OperatorAuthenticationReqBuilder()
{

}

const std::string OperatorAuthenticationReqBuilder::get_topic_name()
{
  return ice::OperatorAuthenticationReqTopic;
}
