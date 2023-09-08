#ifndef MODULE_SERVICE_STATE_TYPE_BUILDER_H
#define MODULE_SERVICE_STATE_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class ModuleServiceStateTypeBuilder : public AbstractTopicBuilder
{
public:
  ModuleServiceStateTypeBuilder();
  ~ModuleServiceStateTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  ModuleServiceStateTypeBuilder(const ModuleServiceStateTypeBuilder &other);
  ModuleServiceStateTypeBuilder &operator=(const ModuleServiceStateTypeBuilder &other);
};

#endif // MODULE_SERVICE_STATE_TYPE_BUILDER_H
