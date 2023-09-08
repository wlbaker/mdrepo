#ifndef DEVICE_DRIVER_STATE_BUILDER_H
#define DEVICE_DRIVER_STATE_BUILDER_H

#include "device-driver-state-type-builder.h"

class DeviceDriverStateBuilder : public DeviceDriverStateTypeBuilder
{
public:
  DeviceDriverStateBuilder();
  ~DeviceDriverStateBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DeviceDriverStateBuilder(const DeviceDriverStateBuilder &other);
  DeviceDriverStateBuilder &operator=(const DeviceDriverStateBuilder &other);
};

#endif // DEVICE_DRIVER_STATE_BUILDER_H
