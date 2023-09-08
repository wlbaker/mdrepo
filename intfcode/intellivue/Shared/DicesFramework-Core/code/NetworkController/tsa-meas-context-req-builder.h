#ifndef TSA_MEAS_CONTEXT_REQ_BUILDER_H
#define TSA_MEAS_CONTEXT_REQ_BUILDER_H

#include "tsa-context-type-builder.h"

class TSAMeasContextReqBuilder : public TSAContextTypeBuilder
{
public:
  TSAMeasContextReqBuilder();
  ~TSAMeasContextReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  TSAMeasContextReqBuilder(const TSAMeasContextReqBuilder &other);
  TSAMeasContextReqBuilder &operator=(const TSAMeasContextReqBuilder &other);
};

#endif // TSA_MEAS_CONTEXT_REQ_BUILDER_H
