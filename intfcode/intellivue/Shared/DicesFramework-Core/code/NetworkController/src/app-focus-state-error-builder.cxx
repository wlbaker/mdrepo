#include "app-focus-state-error-builder.h"

#include <ndds_namespace_cpp.h>
#include <docboxSupport.h>

#include "rc-entity-builder.h"

AppFocusStateErrorBuilder::AppFocusStateErrorBuilder() :
  AbstractTopicBuilder()
{

}

AppFocusStateErrorBuilder::~AppFocusStateErrorBuilder()
{

}

DicesRcEntityBuilder AppFocusStateErrorBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      docbox::AppFocusStateErrorTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string AppFocusStateErrorBuilder::get_type_name()
{
  return docbox::AppFocusStateErrorTypeSupport::get_type_name();
}

const std::string AppFocusStateErrorBuilder::get_topic_name()
{
  return docbox::AppFocusStateErrorTopic;
}
