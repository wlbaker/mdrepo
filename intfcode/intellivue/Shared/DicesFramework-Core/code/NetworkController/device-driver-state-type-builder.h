#ifndef DEVICE_DRIVER_STATE_TYPE_BUILDER_H
#define DEVICE_DRIVER_STATE_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class DeviceDriverStateTypeBuilder : public AbstractTopicBuilder
{
public:
  DeviceDriverStateTypeBuilder();
  ~DeviceDriverStateTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  DeviceDriverStateTypeBuilder(const DeviceDriverStateTypeBuilder &other);
  DeviceDriverStateTypeBuilder &operator=(const DeviceDriverStateTypeBuilder &other);
};

#endif // DEVICE_DRIVER_STATE_TYPE_BUILDER_H
