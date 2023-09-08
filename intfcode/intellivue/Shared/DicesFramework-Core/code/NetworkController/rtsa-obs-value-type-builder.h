#ifndef RTSA_OBS_VALUE_TYPE_BUILDER_H
#define RTSA_OBS_VALUE_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class RTSAObsValueTypeBuilder : public AbstractTopicBuilder
{
public:
  RTSAObsValueTypeBuilder();
  ~RTSAObsValueTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  RTSAObsValueTypeBuilder(const RTSAObsValueTypeBuilder &other);
  RTSAObsValueTypeBuilder &operator=(const RTSAObsValueTypeBuilder &other);
};

#endif // RTSA_OBS_VALUE_TYPE_BUILDER_H
