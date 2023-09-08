#ifndef NUMERIC_SETT_CONTEXT_BUILDER_H
#define NUMERIC_SETT_CONTEXT_BUILDER_H

#include "numeric-context-type-builder.h"

class NumericSettContextBuilder : public NumericContextTypeBuilder
{
public:
  NumericSettContextBuilder();
  ~NumericSettContextBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  NumericSettContextBuilder(const NumericSettContextBuilder &other);
  NumericSettContextBuilder &operator=(const NumericSettContextBuilder &other);
};

#endif // NUMERIC_SETT_CONTEXT_BUILDER_H
