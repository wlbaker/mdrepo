#include "tsa-obs-value-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <tsaSupport.h>

#include "rc-entity-builder.h"

TSAObsValueTypeBuilder::TSAObsValueTypeBuilder() :
  AbstractTopicBuilder()
{

}

TSAObsValueTypeBuilder::~TSAObsValueTypeBuilder()
{

}

DicesRcEntityBuilder TSAObsValueTypeBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::TSAObservedValueTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string TSAObsValueTypeBuilder::get_type_name()
{
  return ice::TSAObservedValueTypeSupport::get_type_name();
}
