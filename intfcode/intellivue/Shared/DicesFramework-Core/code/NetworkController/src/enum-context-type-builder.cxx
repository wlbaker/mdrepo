#include "enum-context-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <enumSupport.h>

#include "rc-entity-builder.h"

EnumContextTypeBuilder::EnumContextTypeBuilder() :
  AbstractTopicBuilder()
{

}

EnumContextTypeBuilder::~EnumContextTypeBuilder()
{

}

DicesRcEntityBuilder EnumContextTypeBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::EnumerationContextTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string EnumContextTypeBuilder::get_type_name()
{
  return ice::EnumerationContextTypeSupport::get_type_name();
}
