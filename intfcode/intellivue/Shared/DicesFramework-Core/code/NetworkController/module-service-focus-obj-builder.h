#ifndef MODULE_SERVICE_FOCUS_OBJ_BUILDER_H
#define MODULE_SERVICE_FOCUS_OBJ_BUILDER_H

#include "module-service-focus-type-builder.h"

enum class DicesRcEntityBuilder;

class ModuleServiceFocusObjBuilder : public ModuleServiceFocusTypeBuilder
{
public:
  ModuleServiceFocusObjBuilder();
  ~ModuleServiceFocusObjBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  ModuleServiceFocusObjBuilder(const ModuleServiceFocusObjBuilder &other);
  ModuleServiceFocusObjBuilder &operator=(const ModuleServiceFocusObjBuilder &other);
};

#endif // MODULE_SERVICE_FOCUS_OBJ_BUILDER_H
