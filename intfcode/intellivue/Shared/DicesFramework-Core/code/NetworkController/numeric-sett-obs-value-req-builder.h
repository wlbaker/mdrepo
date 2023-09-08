#ifndef NUMERIC_SETT_OBS_VALUE_REQ_BUILDER_H
#define NUMERIC_SETT_OBS_VALUE_REQ_BUILDER_H

#include "numeric-obs-value-type-builder.h"

class NumericSettObsValueReqBuilder : public NumericObsValueTypeBuilder
{
public:
  NumericSettObsValueReqBuilder();
  ~NumericSettObsValueReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  NumericSettObsValueReqBuilder(const NumericSettObsValueReqBuilder &other);
  NumericSettObsValueReqBuilder &operator=(const NumericSettObsValueReqBuilder &other);
};

#endif // NUMERIC_SETT_OBS_VALUE_REQ_BUILDER_H
