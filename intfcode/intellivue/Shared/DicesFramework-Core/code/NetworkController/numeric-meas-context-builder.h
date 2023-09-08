#ifndef NUMERIC_MEAS_CONTEXT_BUILDER_H
#define NUMERIC_MEAS_CONTEXT_BUILDER_H

#include "numeric-context-type-builder.h"

class NumericMeasContextBuilder : public NumericContextTypeBuilder
{
public:
  NumericMeasContextBuilder();
  ~NumericMeasContextBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  NumericMeasContextBuilder(const NumericMeasContextBuilder &other);
  NumericMeasContextBuilder &operator=(const NumericMeasContextBuilder &other);
};

#endif // NUMERIC_MEAS_CONTEXT_BUILDER_H
