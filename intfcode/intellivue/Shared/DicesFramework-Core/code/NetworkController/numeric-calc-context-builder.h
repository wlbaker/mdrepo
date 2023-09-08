#ifndef NUMERIC_CALC_CONTEXT_BUILDER_H
#define NUMERIC_CALC_CONTEXT_BUILDER_H

#include "numeric-context-type-builder.h"

class NumericCalcContextBuilder : public NumericContextTypeBuilder
{
public:
  NumericCalcContextBuilder();
  ~NumericCalcContextBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  NumericCalcContextBuilder(const NumericCalcContextBuilder &other);
  NumericCalcContextBuilder &operator=(const NumericCalcContextBuilder &other);
};

#endif // NUMERIC_CALC_CONTEXT_BUILDER_H
