#ifndef DEVICE_DRIVER_LAUNCHER_STATE_BUILDER_H
#define DEVICE_DRIVER_LAUNCHER_STATE_BUILDER_H

#include "device-driver-launcher-state-type-builder.h"

class DeviceDriverLauncherStateBuilder : public DeviceDriverLauncherStateTypeBuilder
{
public:
  DeviceDriverLauncherStateBuilder();
  ~DeviceDriverLauncherStateBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DeviceDriverLauncherStateBuilder(const DeviceDriverLauncherStateBuilder &other);
  DeviceDriverLauncherStateBuilder &operator=(const DeviceDriverLauncherStateBuilder &other);
};

#endif // DEVICE_DRIVER_LAUNCHER_STATE_BUILDER_H
