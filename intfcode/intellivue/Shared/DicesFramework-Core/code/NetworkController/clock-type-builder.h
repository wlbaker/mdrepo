#ifndef CLOCK_TYPE_BUILDER_H
#define CLOCK_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class ClockTypeBuilder : public AbstractTopicBuilder
{
public:
  ClockTypeBuilder();
  ~ClockTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  ClockTypeBuilder(const ClockTypeBuilder &other);
  ClockTypeBuilder &operator=(const ClockTypeBuilder &other);
};

#endif // CLOCK_TYPE_BUILDER_H
