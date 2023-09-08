#ifndef MODULE_SERVICE_FOCUS_BUILDER_H
#define MODULE_SERVICE_FOCUS_BUILDER_H

#include "module-service-focus-type-builder.h"

class ModuleServiceFocusBuilder : public ModuleServiceFocusTypeBuilder
{
public:
  ModuleServiceFocusBuilder();
  ~ModuleServiceFocusBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  ModuleServiceFocusBuilder(const ModuleServiceFocusBuilder &other);
  ModuleServiceFocusBuilder &operator=(const ModuleServiceFocusBuilder &other);
};

#endif // MODULE_SERVICE_FOCUS_BUILDER_H
