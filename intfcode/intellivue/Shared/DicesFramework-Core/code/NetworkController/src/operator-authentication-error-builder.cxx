#include "operator-authentication-error-builder.h"
#include <operatorSupport.h>

OperatorAuthenticationErrorBuilder::OperatorAuthenticationErrorBuilder() :
  OperatorAuthenticationErrorTypeBuilder()
{

}

OperatorAuthenticationErrorBuilder::~OperatorAuthenticationErrorBuilder()
{

}

const std::string OperatorAuthenticationErrorBuilder::get_topic_name()
{
  return ice::OperatorAuthenticationErrorTopic;
}
