#ifndef TSA_CALC_CONTEXT_BUILDER_H
#define TSA_CALC_CONTEXT_BUILDER_H

#include "tsa-context-type-builder.h"

class TSACalcContextBuilder : public TSAContextTypeBuilder
{
public:
  TSACalcContextBuilder();
  ~TSACalcContextBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  TSACalcContextBuilder(const TSACalcContextBuilder &other);
  TSACalcContextBuilder &operator=(const TSACalcContextBuilder &other);
};

#endif // TSA_CALC_CONTEXT_BUILDER_H
