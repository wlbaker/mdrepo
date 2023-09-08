#ifndef RTSA_CONTEXT_TYPE_BUILDER_H
#define RTSA_CONTEXT_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class RTSAContextTypeBuilder : public AbstractTopicBuilder
{
public:
  RTSAContextTypeBuilder();
  ~RTSAContextTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  RTSAContextTypeBuilder(const RTSAContextTypeBuilder &other);
  RTSAContextTypeBuilder &operator=(const RTSAContextTypeBuilder &other);
};

#endif // RTSA_CONTEXT_TYPE_BUILDER_H
