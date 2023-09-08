#ifndef ENUM_SETT_CONTEXT_REQ_BUILDER_H
#define ENUM_SETT_CONTEXT_REQ_BUILDER_H

#include "enum-context-type-builder.h"

class EnumSettContextReqBuilder : public EnumContextTypeBuilder
{
public:
  EnumSettContextReqBuilder();
  ~EnumSettContextReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  EnumSettContextReqBuilder(const EnumSettContextReqBuilder &other);
  EnumSettContextReqBuilder &operator=(const EnumSettContextReqBuilder &other);
};

#endif // ENUM_SETT_CONTEXT_REQ_BUILDER_H
