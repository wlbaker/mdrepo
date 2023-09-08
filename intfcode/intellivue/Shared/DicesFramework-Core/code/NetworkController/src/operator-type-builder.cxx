#include "operator-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <operatorSupport.h>

#include "rc-entity-builder.h"

OperatorTypeBuilder::OperatorTypeBuilder() :
  AbstractTopicBuilder()
{

}

OperatorTypeBuilder::~OperatorTypeBuilder()
{

}

DicesRcEntityBuilder OperatorTypeBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::OperatorTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string OperatorTypeBuilder::get_type_name()
{
  return ice::OperatorTypeSupport::get_type_name();
}
