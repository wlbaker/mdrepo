#ifndef NUMERIC_MEAS_CONTEXT_REQ_BUILDER_H
#define NUMERIC_MEAS_CONTEXT_REQ_BUILDER_H

#include "numeric-context-type-builder.h"

class NumericMeasContextReqBuilder : public NumericContextTypeBuilder
{
public:
  NumericMeasContextReqBuilder();
  ~NumericMeasContextReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  NumericMeasContextReqBuilder(const NumericMeasContextReqBuilder &other);
  NumericMeasContextReqBuilder &operator=(const NumericMeasContextReqBuilder &other);
};

#endif // NUMERIC_MEAS_CONTEXT_REQ_BUILDER_H
