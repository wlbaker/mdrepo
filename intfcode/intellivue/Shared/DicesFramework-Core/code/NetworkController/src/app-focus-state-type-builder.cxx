#include "app-focus-state-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <docboxSupport.h>

#include "rc-entity-builder.h"

AppFocusStateTypeBuilder::AppFocusStateTypeBuilder() :
  AbstractTopicBuilder()
{

}

AppFocusStateTypeBuilder::~AppFocusStateTypeBuilder()
{

}

DicesRcEntityBuilder AppFocusStateTypeBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      docbox::AppFocusStateTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string AppFocusStateTypeBuilder::get_type_name()
{
  return docbox::AppFocusStateTypeSupport::get_type_name();
}
