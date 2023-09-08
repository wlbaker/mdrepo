#include "driver-manager-state-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <docboxSupport.h>

#include "rc-entity-builder.h"

DriverManagerStateTypeBuilder::DriverManagerStateTypeBuilder() :
  AbstractTopicBuilder()
{

}

DriverManagerStateTypeBuilder::~DriverManagerStateTypeBuilder()
{

}

DicesRcEntityBuilder DriverManagerStateTypeBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      docbox::DriverManagerStateTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string DriverManagerStateTypeBuilder::get_type_name()
{
  return docbox::DriverManagerStateTypeSupport::get_type_name();
}
