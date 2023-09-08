#ifndef CLOCK_BUILDER_H
#define CLOCK_BUILDER_H

#include "clock-type-builder.h"

enum class DicesRcEntityBuilder;

class ClockBuilder : public ClockTypeBuilder
{
public:
  ClockBuilder();
  ~ClockBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  ClockBuilder(const ClockBuilder &other);
  ClockBuilder &operator=(const ClockBuilder &other);
};

#endif // CLOCK_BUILDER_H
