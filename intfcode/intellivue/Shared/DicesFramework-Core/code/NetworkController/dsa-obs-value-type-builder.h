#ifndef DSA_OBS_VALUE_TYPE_BUILDER_H
#define DSA_OBS_VALUE_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class DSAObsValueTypeBuilder : public AbstractTopicBuilder
{
public:
  DSAObsValueTypeBuilder();
  ~DSAObsValueTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  DSAObsValueTypeBuilder(const DSAObsValueTypeBuilder &other);
  DSAObsValueTypeBuilder &operator=(const DSAObsValueTypeBuilder &other);
};

#endif // DSA_OBS_VALUE_TYPE_BUILDER_H
