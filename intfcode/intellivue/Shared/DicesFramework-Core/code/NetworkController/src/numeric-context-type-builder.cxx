#include "numeric-context-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <numericSupport.h>

#include "rc-entity-builder.h"

NumericContextTypeBuilder::NumericContextTypeBuilder() :
  AbstractTopicBuilder()
{

}

NumericContextTypeBuilder::~NumericContextTypeBuilder()
{

}

DicesRcEntityBuilder NumericContextTypeBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::NumericContextTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string NumericContextTypeBuilder::get_type_name()
{
  return ice::NumericContextTypeSupport::get_type_name();
}
