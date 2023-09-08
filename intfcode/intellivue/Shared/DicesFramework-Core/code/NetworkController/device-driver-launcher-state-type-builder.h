#ifndef DEVICE_DRIVER_LAUNCHER_STATE_TYPE_BUILDER_H
#define DEVICE_DRIVER_LAUNCHER_STATE_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class DeviceDriverLauncherStateTypeBuilder : public AbstractTopicBuilder
{
public:
  DeviceDriverLauncherStateTypeBuilder();
  ~DeviceDriverLauncherStateTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  DeviceDriverLauncherStateTypeBuilder(const DeviceDriverLauncherStateTypeBuilder &other);
  DeviceDriverLauncherStateTypeBuilder &operator=(const DeviceDriverLauncherStateTypeBuilder &other);
};

#endif // DEVICE_DRIVER_LAUNCHER_STATE_TYPE_BUILDER_H
