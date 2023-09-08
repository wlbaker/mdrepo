#include "tsa-context-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <tsaSupport.h>

#include "rc-entity-builder.h"

TSAContextTypeBuilder::TSAContextTypeBuilder() :
  AbstractTopicBuilder()
{

}

TSAContextTypeBuilder::~TSAContextTypeBuilder()
{

}

DicesRcEntityBuilder TSAContextTypeBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::TSAContextTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string TSAContextTypeBuilder::get_type_name()
{
  return ice::TSAContextTypeSupport::get_type_name();
}
