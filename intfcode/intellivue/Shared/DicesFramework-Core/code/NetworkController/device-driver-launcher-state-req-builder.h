#ifndef DEVICE_DRIVER_LAUNCHER_STATE_REQ_BUILDER_H
#define DEVICE_DRIVER_LAUNCHER_STATE_REQ_BUILDER_H

#include "device-driver-launcher-state-type-builder.h"

enum class DicesRcEntityBuilder;

class DeviceDriverLauncherStateReqBuilder : public DeviceDriverLauncherStateTypeBuilder
{
public:
  DeviceDriverLauncherStateReqBuilder();
  ~DeviceDriverLauncherStateReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DeviceDriverLauncherStateReqBuilder(const DeviceDriverLauncherStateReqBuilder &other);
  DeviceDriverLauncherStateReqBuilder &operator=(const DeviceDriverLauncherStateReqBuilder &other);
};

#endif // DEVICE_DRIVER_LAUNCHER_STATE_REQ_BUILDER_H
