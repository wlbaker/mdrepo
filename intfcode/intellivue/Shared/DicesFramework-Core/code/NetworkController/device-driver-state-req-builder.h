#ifndef DEVICE_DRIVER_STATE_REQ_BUILDER_H
#define DEVICE_DRIVER_STATE_REQ_BUILDER_H

#include "device-driver-state-type-builder.h"

enum class DicesRcEntityBuilder;

class DeviceDriverStateReqBuilder : public DeviceDriverStateTypeBuilder
{
public:
  DeviceDriverStateReqBuilder();
  ~DeviceDriverStateReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DeviceDriverStateReqBuilder(const DeviceDriverStateReqBuilder &other);
  DeviceDriverStateReqBuilder &operator=(const DeviceDriverStateReqBuilder &other);
};

#endif // DEVICE_DRIVER_STATE_REQ_BUILDER_H
