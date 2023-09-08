#ifndef MODULE_SERVICE_FOCUS_REQ_BUILDER_H
#define MODULE_SERVICE_FOCUS_REQ_BUILDER_H

#include "module-service-focus-type-builder.h"

enum class DicesRcEntityBuilder;

class ModuleServiceFocusReqBuilder : public ModuleServiceFocusTypeBuilder
{
public:
  ModuleServiceFocusReqBuilder();
  ~ModuleServiceFocusReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  ModuleServiceFocusReqBuilder(const ModuleServiceFocusReqBuilder &other);
  ModuleServiceFocusReqBuilder &operator=(const ModuleServiceFocusReqBuilder &other);
};

#endif // MODULE_SERVICE_FOCUS_REQ_BUILDER_H
