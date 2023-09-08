#ifndef TSA_SETT_CONTEXT_BUILDER_H
#define TSA_SETT_CONTEXT_BUILDER_H

#include "tsa-context-type-builder.h"

class TSASettContextBuilder : public TSAContextTypeBuilder
{
public:
  TSASettContextBuilder();
  ~TSASettContextBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  TSASettContextBuilder(const TSASettContextBuilder &other);
  TSASettContextBuilder &operator=(const TSASettContextBuilder &other);
};

#endif // TSA_SETT_CONTEXT_BUILDER_H
