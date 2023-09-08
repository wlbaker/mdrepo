#ifndef MODULE_SERVICE_STATE_OBJ_BUILDER_H
#define MODULE_SERVICE_STATE_OBJ_BUILDER_H

#include "module-service-state-type-builder.h"

enum class DicesRcEntityBuilder;

class ModuleServiceStateObjBuilder : public ModuleServiceStateTypeBuilder
{
public:
  ModuleServiceStateObjBuilder();
  ~ModuleServiceStateObjBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  ModuleServiceStateObjBuilder(const ModuleServiceStateObjBuilder &other);
  ModuleServiceStateObjBuilder &operator=(const ModuleServiceStateObjBuilder &other);
};

#endif // MODULE_SERVICE_STATE_OBJ_BUILDER_H
