#ifndef DEVICE_DRIVER_LAUNCHER_STATE_CFT_BUILDER_H
#define DEVICE_DRIVER_LAUNCHER_STATE_CFT_BUILDER_H

#include "abstract-content-filtered-topic-builder.h"

enum class DicesRcEntityBuilder;

class DeviceDriverLauncherStateCftBuilder : public AbstractContentFilteredTopicBuilder
{
public:
  DeviceDriverLauncherStateCftBuilder(std::string content_filtered_topic_name);
  ~DeviceDriverLauncherStateCftBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_library_name();

  const std::string get_topic_name();

  const std::string get_type_name();

  const std::string get_qos_profile();

private:
  // Disallow use of implicitly generated member functions:
  DeviceDriverLauncherStateCftBuilder(const DeviceDriverLauncherStateCftBuilder &other);
  DeviceDriverLauncherStateCftBuilder &operator=(const DeviceDriverLauncherStateCftBuilder &other);
};

#endif // DEVICE_DRIVER_LAUNCHER_STATE_CFT_BUILDER_H
