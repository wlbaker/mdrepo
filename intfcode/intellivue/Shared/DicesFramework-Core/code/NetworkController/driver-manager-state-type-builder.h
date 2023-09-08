#ifndef DRIVER_MANAGER_STATE_TYPE_BUILDER_H
#define DRIVER_MANAGER_STATE_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class DriverManagerStateTypeBuilder : public AbstractTopicBuilder
{
public:
  DriverManagerStateTypeBuilder();
  ~DriverManagerStateTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  DriverManagerStateTypeBuilder(const DriverManagerStateTypeBuilder &other);
  DriverManagerStateTypeBuilder &operator=(const DriverManagerStateTypeBuilder &other);
};

#endif // DRIVER_MANAGER_STATE_TYPE_BUILDER_H
