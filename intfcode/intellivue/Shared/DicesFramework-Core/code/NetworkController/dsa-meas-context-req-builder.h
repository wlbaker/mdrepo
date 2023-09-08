#ifndef DSA_MEAS_CONTEXT_REQ_BUILDER_H
#define DSA_MEAS_CONTEXT_REQ_BUILDER_H

#include "dsa-context-type-builder.h"

class DSAMeasContextReqBuilder : public DSAContextTypeBuilder
{
public:
  DSAMeasContextReqBuilder();
  ~DSAMeasContextReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DSAMeasContextReqBuilder(const DSAMeasContextReqBuilder &other);
  DSAMeasContextReqBuilder &operator=(const DSAMeasContextReqBuilder &other);
};

#endif // DSA_MEAS_CONTEXT_REQ_BUILDER_H
