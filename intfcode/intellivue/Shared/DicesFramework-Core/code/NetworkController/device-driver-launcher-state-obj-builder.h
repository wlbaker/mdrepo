#ifndef DEVICE_DRIVER_LAUNCHER_STATE_OBJ_BUILDER_H
#define DEVICE_DRIVER_LAUNCHER_STATE_OBJ_BUILDER_H

#include "device-driver-launcher-state-type-builder.h"

enum class DicesRcEntityBuilder;

class DeviceDriverLauncherStateObjBuilder : public DeviceDriverLauncherStateTypeBuilder
{
public:
  DeviceDriverLauncherStateObjBuilder();
  ~DeviceDriverLauncherStateObjBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DeviceDriverLauncherStateObjBuilder(const DeviceDriverLauncherStateObjBuilder &other);
  DeviceDriverLauncherStateObjBuilder &operator=(const DeviceDriverLauncherStateObjBuilder &other);
};

#endif // DEVICE_DRIVER_LAUNCHER_STATE_OBJ_BUILDER_H
