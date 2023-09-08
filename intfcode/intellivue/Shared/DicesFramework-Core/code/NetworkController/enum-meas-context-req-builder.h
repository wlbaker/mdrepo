#ifndef ENUM_MEAS_CONTEXT_REQ_BUILDER_H
#define ENUM_MEAS_CONTEXT_REQ_BUILDER_H

#include "enum-context-type-builder.h"

class EnumMeasContextReqBuilder : public EnumContextTypeBuilder
{
public:
  EnumMeasContextReqBuilder();
  ~EnumMeasContextReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  EnumMeasContextReqBuilder(const EnumMeasContextReqBuilder &other);
  EnumMeasContextReqBuilder &operator=(const EnumMeasContextReqBuilder &other);
};

#endif // ENUM_MEAS_CONTEXT_REQ_BUILDER_H
