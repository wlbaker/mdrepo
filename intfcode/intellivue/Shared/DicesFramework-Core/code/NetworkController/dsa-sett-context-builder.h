#ifndef DSA_SETT_CONTEXT_BUILDER_H
#define DSA_SETT_CONTEXT_BUILDER_H

#include "dsa-context-type-builder.h"

class DSASettContextBuilder : public DSAContextTypeBuilder
{
public:
  DSASettContextBuilder();
  ~DSASettContextBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DSASettContextBuilder(const DSASettContextBuilder &other);
  DSASettContextBuilder &operator=(const DSASettContextBuilder &other);
};

#endif // DSA_SETT_CONTEXT_BUILDER_H
