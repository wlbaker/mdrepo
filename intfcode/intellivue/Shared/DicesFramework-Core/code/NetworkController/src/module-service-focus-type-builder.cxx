#include "module-service-focus-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <docboxSupport.h>

#include "rc-entity-builder.h"

ModuleServiceFocusTypeBuilder::ModuleServiceFocusTypeBuilder() :
  AbstractTopicBuilder()
{

}

ModuleServiceFocusTypeBuilder::~ModuleServiceFocusTypeBuilder()
{

}

DicesRcEntityBuilder ModuleServiceFocusTypeBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      docbox::ModuleServiceFocusTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string ModuleServiceFocusTypeBuilder::get_type_name()
{
  return docbox::ModuleServiceFocusTypeSupport::get_type_name();
}
