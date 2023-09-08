/*
 * File:   dices_device_driver_status_handler.cxx
 * Author: Robert England
 *
 * Defines a class for handling device driver status.
 *
 * Created on June 26, 2014
 * Last Modified on June 26, 2014
 */

#include "dices_device_driver_status_handler.h"

// Creates and initialize all DDS objects
DicesRcDriverStatus DicesDeviceDriverStatusHandler::DDSInit(
  DDS::Publisher* publisher,
  std::string udi)
{
  if (!publisher)
  {
    return DicesRcDriverStatus::NULL_PUBLISHER_PARAMETER;
  }
    
  _udi = udi;
  
  DDS::DataWriter* base_device_driver_state_data_writer
    = publisher->lookup_datawriter_by_name("DeviceDriverStateWriter");
  if (!base_device_driver_state_data_writer)
  {
    return DicesRcDriverStatus::DRIVER_STATE_WRITER_LOOKUP_FAILURE;
  }
  _device_driver_state_data_writer
    = docbox::DeviceDriverStateDataWriter::narrow(base_device_driver_state_data_writer);
  if (!_device_driver_state_data_writer)
  {
    return DicesRcDriverStatus::DRIVER_STATE_WRITER_NARROW_FAILURE;
  }
  
  return DicesRcDriverStatus::OK;
}

// Shuts down and deletes all DDS objects
DicesRcDriverStatus DicesDeviceDriverStatusHandler::DDSShutdown()
{
  _device_driver_state_topic = 0;
  _device_driver_state_data_writer = 0;

  return DicesRcDriverStatus::OK;
}

// Publishes a Device Driver Status to the manager.
DicesRcDriverStatus DicesDeviceDriverStatusHandler::SetStatus(
  docbox::DriverStatus status)
{
  if (!_device_driver_state_data_writer)
  {
    // NOTE: No logging available in this class, but descriptive return codes
    // are used instead.
    return DicesRcDriverStatus::DRIVER_STATE_WRITER_NULL_FAILURE;
  }

  DDS::ReturnCode_t dds_retcode;

  docbox::DeviceDriverState* state_instance
    = docbox::DeviceDriverStateTypeSupport::create_data();
  if (state_instance == 0)
  {
    docbox::DeviceDriverStateTypeSupport::delete_data(state_instance);
    return DicesRcDriverStatus::STATE_INSTANCE_CREATE_FAILURE;
  }
  strncpy(state_instance->device_id, _udi.c_str(), ice::MAX_LEN_ICE_ID - 1);
  state_instance->device_id[ice::MAX_LEN_ICE_ID - 1] = '\0';
  state_instance->driver_status = status;
  
  if (_device_driver_state_data_writer->write(*state_instance, DDS::HANDLE_NIL) != DDS_RETCODE_OK)
  {
    docbox::DeviceDriverStateTypeSupport::delete_data(state_instance);
    return DicesRcDriverStatus::DRIVER_STATUS_UPDATE_FAILURE;
  }
  dds_retcode
    = docbox::DeviceDriverStateTypeSupport::delete_data(state_instance);
  return (dds_retcode != DDS::RETCODE_OK)
    ? DicesRcDriverStatus::STATE_INSTANCE_DELETE_FAILURE
    : DicesRcDriverStatus::OK;
}
