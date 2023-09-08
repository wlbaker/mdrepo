#ifndef MODULE_SERVICE_STATE_REQ_BUILDER_H
#define MODULE_SERVICE_STATE_REQ_BUILDER_H

#include "module-service-state-type-builder.h"

enum class DicesRcEntityBuilder;

class ModuleServiceStateReqBuilder : public ModuleServiceStateTypeBuilder
{
public:
  ModuleServiceStateReqBuilder();
  ~ModuleServiceStateReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  ModuleServiceStateReqBuilder(const ModuleServiceStateReqBuilder &other);
  ModuleServiceStateReqBuilder &operator=(const ModuleServiceStateReqBuilder &other);
};

#endif // MODULE_SERVICE_STATE_REQ_BUILDER_H
