#ifndef DSA_MEAS_CONTEXT_BUILDER_H
#define DSA_MEAS_CONTEXT_BUILDER_H

#include "dsa-context-type-builder.h"

class DSAMeasContextBuilder : public DSAContextTypeBuilder
{
public:
  DSAMeasContextBuilder();
  ~DSAMeasContextBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DSAMeasContextBuilder(const DSAMeasContextBuilder &other);
  DSAMeasContextBuilder &operator=(const DSAMeasContextBuilder &other);
};

#endif // DSA_MEAS_CONTEXT_BUILDER_H
