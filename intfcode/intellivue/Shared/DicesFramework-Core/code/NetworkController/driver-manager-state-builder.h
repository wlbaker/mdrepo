#ifndef DRIVER_MANAGER_STATE_BUILDER_H
#define DRIVER_MANAGER_STATE_BUILDER_H

#include "driver-manager-state-type-builder.h"

class DriverManagerStateBuilder : public DriverManagerStateTypeBuilder
{
public:
  DriverManagerStateBuilder();
  ~DriverManagerStateBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DriverManagerStateBuilder(const DriverManagerStateBuilder &other);
  DriverManagerStateBuilder &operator=(const DriverManagerStateBuilder &other);
};

#endif // DRIVER_MANAGER_STATE_BUILDER_H
