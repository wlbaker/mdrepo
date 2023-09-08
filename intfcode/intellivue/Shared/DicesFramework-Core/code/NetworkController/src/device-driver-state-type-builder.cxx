#include "device-driver-state-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <docboxSupport.h>

#include "rc-entity-builder.h"

DeviceDriverStateTypeBuilder::DeviceDriverStateTypeBuilder() :
  AbstractTopicBuilder()
{

}

DeviceDriverStateTypeBuilder::~DeviceDriverStateTypeBuilder()
{

}

DicesRcEntityBuilder DeviceDriverStateTypeBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      docbox::DeviceDriverStateTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string DeviceDriverStateTypeBuilder::get_type_name()
{
  return docbox::DeviceDriverStateTypeSupport::get_type_name();
}
