#ifndef LOCATION_TYPE_BUILDER_H
#define LOCATION_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class LocationTypeBuilder : public AbstractTopicBuilder
{
public:
  LocationTypeBuilder();
  ~LocationTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  LocationTypeBuilder(const LocationTypeBuilder &other);
  LocationTypeBuilder &operator=(const LocationTypeBuilder &other);
};

#endif // LOCATION_TYPE_BUILDER_H
