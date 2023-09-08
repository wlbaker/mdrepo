#ifndef DSA_CONTEXT_TYPE_BUILDER_H
#define DSA_CONTEXT_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class DSAContextTypeBuilder : public AbstractTopicBuilder
{
public:
  DSAContextTypeBuilder();
  ~DSAContextTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  DSAContextTypeBuilder(const DSAContextTypeBuilder &other);
  DSAContextTypeBuilder &operator=(const DSAContextTypeBuilder &other);
};

#endif // DSA_CONTEXT_TYPE_BUILDER_H
