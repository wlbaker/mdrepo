#include "operator-authentication-builder.h"
#include <operatorSupport.h>

OperatorAuthenticationBuilder::OperatorAuthenticationBuilder() :
  OperatorAuthenticationTypeBuilder()
{

}

OperatorAuthenticationBuilder::~OperatorAuthenticationBuilder()
{

}

const std::string OperatorAuthenticationBuilder::get_topic_name()
{
  return ice::OperatorAuthenticationTopic;
}
