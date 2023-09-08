#ifndef ENUM_MEAS_CONTEXT_BUILDER_H
#define ENUM_MEAS_CONTEXT_BUILDER_H

#include "enum-context-type-builder.h"

class EnumMeasContextBuilder : public EnumContextTypeBuilder
{
public:
  EnumMeasContextBuilder();
  ~EnumMeasContextBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  EnumMeasContextBuilder(const EnumMeasContextBuilder &other);
  EnumMeasContextBuilder &operator=(const EnumMeasContextBuilder &other);
};

#endif // ENUM_MEAS_CONTEXT_BUILDER_H
