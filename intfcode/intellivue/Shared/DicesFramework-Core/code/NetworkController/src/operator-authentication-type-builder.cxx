#include "operator-authentication-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <operatorSupport.h>

#include "rc-entity-builder.h"

OperatorAuthenticationTypeBuilder::OperatorAuthenticationTypeBuilder() :
  AbstractTopicBuilder()
{

}

OperatorAuthenticationTypeBuilder::~OperatorAuthenticationTypeBuilder()
{

}

DicesRcEntityBuilder OperatorAuthenticationTypeBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::OperatorAuthenticationTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string OperatorAuthenticationTypeBuilder::get_type_name()
{
  return ice::OperatorAuthenticationTypeSupport::get_type_name();
}
