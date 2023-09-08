#ifndef NUMERIC_SETT_CONTEXT_REQ_BUILDER_H
#define NUMERIC_SETT_CONTEXT_REQ_BUILDER_H

#include "numeric-context-type-builder.h"

class NumericSettContextReqBuilder : public NumericContextTypeBuilder
{
public:
  NumericSettContextReqBuilder();
  ~NumericSettContextReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  NumericSettContextReqBuilder(const NumericSettContextReqBuilder &other);
  NumericSettContextReqBuilder &operator=(const NumericSettContextReqBuilder &other);
};

#endif // NUMERIC_SETT_CONTEXT_REQ_BUILDER_H
