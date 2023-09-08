#ifndef TSA_CONTEXT_TYPE_BUILDER_H
#define TSA_CONTEXT_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class TSAContextTypeBuilder : public AbstractTopicBuilder
{
public:
  TSAContextTypeBuilder();
  ~TSAContextTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  TSAContextTypeBuilder(const TSAContextTypeBuilder &other);
  TSAContextTypeBuilder &operator=(const TSAContextTypeBuilder &other);
};

#endif // TSA_CONTEXT_TYPE_BUILDER_H
