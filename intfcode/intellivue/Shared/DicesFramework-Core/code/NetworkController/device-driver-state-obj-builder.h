#ifndef DEVICE_DRIVER_STATE_OBJ_BUILDER_H
#define DEVICE_DRIVER_STATE_OBJ_BUILDER_H

#include "device-driver-state-type-builder.h"

enum class DicesRcEntityBuilder;

class DeviceDriverStateObjBuilder : public DeviceDriverStateTypeBuilder
{
public:
  DeviceDriverStateObjBuilder();
  ~DeviceDriverStateObjBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DeviceDriverStateObjBuilder(const DeviceDriverStateObjBuilder &other);
  DeviceDriverStateObjBuilder &operator=(const DeviceDriverStateObjBuilder &other);
};

#endif // DEVICE_DRIVER_STATE_OBJ_BUILDER_H
