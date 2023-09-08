#ifndef DSA_SETT_OBS_VALUE_BUILDER_H
#define DSA_SETT_OBS_VALUE_BUILDER_H

#include "dsa-obs-value-type-builder.h"

class DSASettObsValueBuilder : public DSAObsValueTypeBuilder
{
public:
  DSASettObsValueBuilder();
  ~DSASettObsValueBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DSASettObsValueBuilder(const DSASettObsValueBuilder &other);
  DSASettObsValueBuilder &operator=(const DSASettObsValueBuilder &other);
};

#endif // DSA_SETT_OBS_VALUE_BUILDER_H
