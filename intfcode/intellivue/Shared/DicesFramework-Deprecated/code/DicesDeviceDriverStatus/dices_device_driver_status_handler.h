/*
 * File:   dices_device_driver_status_handler.h
 * Author: Robert England
 *
 * Declares a class for handling device driver status.
 *
 * Created on June 26, 2014
 * Last Modified on June 26, 2014
 */

#ifndef DICES_DEVICE_DRIVER_STATUS_HANDLER_H_
#define	DICES_DEVICE_DRIVER_STATUS_HANDLER_H_

#include <string>

#include "ndds/ndds_cpp.h"
#include "ndds/ndds_namespace_cpp.h"

#include "common.h"
#include "commonPlugin.h"
#include "commonSupport.h"
#include "docbox.h"
#include "docboxPlugin.h"
#include "docboxSupport.h"

#include "dices_rc_driver_status.h"

class DicesDeviceDriverStatusHandler
{
 public:

  DicesDeviceDriverStatusHandler()
    : _device_driver_state_topic(nullptr),
    _device_driver_state_data_writer(nullptr)
  {
  };

  ~DicesDeviceDriverStatusHandler() { };

  // Publishes Connecting status
  DicesRcDriverStatus Connecting()
  {
    return SetStatus(docbox::DriverStatus::connecting);
  };
  // Publishes Operating status
  DicesRcDriverStatus Operating()
  {
    return SetStatus(docbox::DriverStatus::operating);
  };
  // Publishes Shutdown status
  DicesRcDriverStatus Shutdown()
  {
    return SetStatus(docbox::DriverStatus::shutdown);
  };
  // Publishes Error status
  DicesRcDriverStatus Error()
  {
    return SetStatus(docbox::DriverStatus::error);
  };

  // Creates and initializes all DDS objects
  DicesRcDriverStatus DDSInit(
    DDS::Publisher* publisher,
    std::string udi);
  // Shuts down and deletes all DDS objects
  DicesRcDriverStatus DDSShutdown();
  // Publishes a Device Driver Status to the manager.
  DicesRcDriverStatus SetStatus(docbox::DriverStatus status);

 private:
  // Disallow use of implicitly generated member functions:
  DicesDeviceDriverStatusHandler(const DicesDeviceDriverStatusHandler &src);
  DicesDeviceDriverStatusHandler &operator=(const DicesDeviceDriverStatusHandler &rhs);

  std::string _udi;

  DDS::Topic* _device_driver_state_topic;
  docbox::DeviceDriverStateDataWriter* _device_driver_state_data_writer;
};

#endif	// DICES_DEVICE_DRIVER_STATUS_HANDLER_H_
