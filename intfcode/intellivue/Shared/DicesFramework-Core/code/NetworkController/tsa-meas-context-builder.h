#ifndef TSA_MEAS_CONTEXT_BUILDER_H
#define TSA_MEAS_CONTEXT_BUILDER_H

#include "tsa-context-type-builder.h"

class TSAMeasContextBuilder : public TSAContextTypeBuilder
{
public:
  TSAMeasContextBuilder();
  ~TSAMeasContextBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  TSAMeasContextBuilder(const TSAMeasContextBuilder &other);
  TSAMeasContextBuilder &operator=(const TSAMeasContextBuilder &other);
};

#endif // TSA_MEAS_CONTEXT_BUILDER_H
