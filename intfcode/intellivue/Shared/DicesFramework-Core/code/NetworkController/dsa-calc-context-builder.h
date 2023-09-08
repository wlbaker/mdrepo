#ifndef DSA_CALC_CONTEXT_BUILDER_H
#define DSA_CALC_CONTEXT_BUILDER_H

#include "dsa-context-type-builder.h"

class DSACalcContextBuilder : public DSAContextTypeBuilder
{
public:
  DSACalcContextBuilder();
  ~DSACalcContextBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DSACalcContextBuilder(const DSACalcContextBuilder &other);
  DSACalcContextBuilder &operator=(const DSACalcContextBuilder &other);
};

#endif // DSA_CALC_CONTEXT_BUILDER_H
