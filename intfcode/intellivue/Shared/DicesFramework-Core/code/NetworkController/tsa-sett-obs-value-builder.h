#ifndef TSA_SETT_OBS_VALUE_BUILDER_H
#define TSA_SETT_OBS_VALUE_BUILDER_H

#include "tsa-obs-value-type-builder.h"

class TSASettObsValueBuilder : public TSAObsValueTypeBuilder
{
public:
  TSASettObsValueBuilder();
  ~TSASettObsValueBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  TSASettObsValueBuilder(const TSASettObsValueBuilder &other);
  TSASettObsValueBuilder &operator=(const TSASettObsValueBuilder &other);
};

#endif // TSA_SETT_OBS_VALUE_BUILDER_H
