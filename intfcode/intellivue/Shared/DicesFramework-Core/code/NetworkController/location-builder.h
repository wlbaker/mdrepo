#ifndef LOCATION_BUILDER_H
#define LOCATION_BUILDER_H

#include "location-type-builder.h"

enum class DicesRcEntityBuilder;

class LocationBuilder : public LocationTypeBuilder
{
public:
  LocationBuilder();
  ~LocationBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  LocationBuilder(const LocationBuilder &other);
  LocationBuilder &operator=(const LocationBuilder &other);
};

#endif // LOCATION_BUILDER_H
