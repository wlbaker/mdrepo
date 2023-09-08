#ifndef NUMERIC_CONTEXT_TYPE_BUILDER_H
#define NUMERIC_CONTEXT_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class NumericContextTypeBuilder : public AbstractTopicBuilder
{
public:
  NumericContextTypeBuilder();
  ~NumericContextTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  NumericContextTypeBuilder(const NumericContextTypeBuilder &other);
  NumericContextTypeBuilder &operator=(const NumericContextTypeBuilder &other);
};

#endif // NUMERIC_CONTEXT_TYPE_BUILDER_H
