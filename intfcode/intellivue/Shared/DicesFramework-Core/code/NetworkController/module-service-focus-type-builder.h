#ifndef MODULE_SERVICE_FOCUS_TYPE_BUILDER_H
#define MODULE_SERVICE_FOCUS_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class ModuleServiceFocusTypeBuilder : public AbstractTopicBuilder
{
public:
  ModuleServiceFocusTypeBuilder();
  ~ModuleServiceFocusTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  ModuleServiceFocusTypeBuilder(const ModuleServiceFocusTypeBuilder &other);
  ModuleServiceFocusTypeBuilder &operator=(const ModuleServiceFocusTypeBuilder &other);
};

#endif // MODULE_SERVICE_FOCUS_TYPE_BUILDER_H
