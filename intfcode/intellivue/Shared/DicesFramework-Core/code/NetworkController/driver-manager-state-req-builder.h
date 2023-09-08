#ifndef DRIVER_MANAGER_STATE_REQ_BUILDER_H
#define DRIVER_MANAGER_STATE_REQ_BUILDER_H

#include "driver-manager-state-type-builder.h"

enum class DicesRcEntityBuilder;

class DriverManagerStateReqBuilder : public DriverManagerStateTypeBuilder
{
public:
  DriverManagerStateReqBuilder();
  ~DriverManagerStateReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DriverManagerStateReqBuilder(const DriverManagerStateReqBuilder &other);
  DriverManagerStateReqBuilder &operator=(const DriverManagerStateReqBuilder &other);
};

#endif // DRIVER_MANAGER_STATE_REQ_BUILDER_H
