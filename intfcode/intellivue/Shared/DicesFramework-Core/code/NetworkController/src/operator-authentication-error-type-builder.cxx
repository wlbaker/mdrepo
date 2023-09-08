#include "operator-authentication-error-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <operatorSupport.h>

#include "rc-entity-builder.h"

OperatorAuthenticationErrorTypeBuilder::OperatorAuthenticationErrorTypeBuilder() :
  AbstractTopicBuilder()
{

}

OperatorAuthenticationErrorTypeBuilder::~OperatorAuthenticationErrorTypeBuilder()
{

}

DicesRcEntityBuilder OperatorAuthenticationErrorTypeBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::OperatorAuthenticationErrorTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string OperatorAuthenticationErrorTypeBuilder::get_type_name()
{
  return ice::OperatorAuthenticationErrorTypeSupport::get_type_name();
}
