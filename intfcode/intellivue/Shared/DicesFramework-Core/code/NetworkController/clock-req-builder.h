#ifndef CLOCK_REQ_BUILDER_H
#define CLOCK_REQ_BUILDER_H

#include "clock-type-builder.h"

enum class DicesRcEntityBuilder;

class ClockReqBuilder : public ClockTypeBuilder
{
public:
  ClockReqBuilder();
  ~ClockReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  ClockReqBuilder(const ClockReqBuilder &other);
  ClockReqBuilder &operator=(const ClockReqBuilder &other);
};

#endif // CLOCK_REQ_BUILDER_H
