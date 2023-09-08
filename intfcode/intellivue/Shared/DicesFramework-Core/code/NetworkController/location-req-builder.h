#ifndef LOCATION_REQ_BUILDER_H
#define LOCATION_REQ_BUILDER_H

#include "location-type-builder.h"

enum class DicesRcEntityBuilder;

class LocationReqBuilder : public LocationTypeBuilder
{
public:
  LocationReqBuilder();
  ~LocationReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  LocationReqBuilder(const LocationReqBuilder &other);
  LocationReqBuilder &operator=(const LocationReqBuilder &other);
};

#endif // LOCATION_REQ_BUILDER_H
