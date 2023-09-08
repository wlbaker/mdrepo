#ifndef DSA_CALC_OBS_VALUE_BUILDER_H
#define DSA_CALC_OBS_VALUE_BUILDER_H

#include "dsa-obs-value-type-builder.h"

class DSACalcObsValueBuilder : public DSAObsValueTypeBuilder
{
public:
  DSACalcObsValueBuilder();
  ~DSACalcObsValueBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DSACalcObsValueBuilder(const DSACalcObsValueBuilder &other);
  DSACalcObsValueBuilder &operator=(const DSACalcObsValueBuilder &other);
};

#endif // DSA_CALC_OBS_VALUE_BUILDER_H
