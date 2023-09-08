#ifndef TSA_OBS_VALUE_TYPE_BUILDER_H
#define TSA_OBS_VALUE_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class TSAObsValueTypeBuilder : public AbstractTopicBuilder
{
public:
  TSAObsValueTypeBuilder();
  ~TSAObsValueTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  TSAObsValueTypeBuilder(const TSAObsValueTypeBuilder &other);
  TSAObsValueTypeBuilder &operator=(const TSAObsValueTypeBuilder &other);
};

#endif // TSA_OBS_VALUE_TYPE_BUILDER_H
