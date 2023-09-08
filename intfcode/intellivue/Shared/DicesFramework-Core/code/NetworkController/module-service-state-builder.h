#ifndef MODULE_SERVICE_STATE_BUILDER_H
#define MODULE_SERVICE_STATE_BUILDER_H

#include "module-service-state-type-builder.h"

class ModuleServiceStateBuilder : public ModuleServiceStateTypeBuilder
{
public:
  ModuleServiceStateBuilder();
  ~ModuleServiceStateBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  ModuleServiceStateBuilder(const ModuleServiceStateBuilder &other);
  ModuleServiceStateBuilder &operator=(const ModuleServiceStateBuilder &other);
};

#endif // MODULE_SERVICE_STATE_BUILDER_H
