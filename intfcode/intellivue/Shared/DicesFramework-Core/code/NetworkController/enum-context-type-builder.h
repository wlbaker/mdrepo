#ifndef ENUM_CONTEXT_TYPE_BUILDER_H
#define ENUM_CONTEXT_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class EnumContextTypeBuilder : public AbstractTopicBuilder
{
public:
  EnumContextTypeBuilder();
  ~EnumContextTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  EnumContextTypeBuilder(const EnumContextTypeBuilder &other);
  EnumContextTypeBuilder &operator=(const EnumContextTypeBuilder &other);
};

#endif // ENUM_CONTEXT_TYPE_BUILDER_H
