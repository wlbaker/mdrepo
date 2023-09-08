#ifndef TSA_SETT_CONTEXT_REQ_BUILDER_H
#define TSA_SETT_CONTEXT_REQ_BUILDER_H

#include "tsa-context-type-builder.h"

class TSASettContextReqBuilder : public TSAContextTypeBuilder
{
public:
  TSASettContextReqBuilder();
  ~TSASettContextReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  TSASettContextReqBuilder(const TSASettContextReqBuilder &other);
  TSASettContextReqBuilder &operator=(const TSASettContextReqBuilder &other);
};

#endif // TSA_SETT_CONTEXT_REQ_BUILDER_H
