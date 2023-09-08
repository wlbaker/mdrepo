#ifndef MODULE_DISPLAY_STATE_TYPE_BUILDER_H
#define MODULE_DISPLAY_STATE_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class ModuleDisplayStateTypeBuilder : public AbstractTopicBuilder
{
public:
  ModuleDisplayStateTypeBuilder();
  ~ModuleDisplayStateTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  ModuleDisplayStateTypeBuilder(const ModuleDisplayStateTypeBuilder &other);
  ModuleDisplayStateTypeBuilder &operator=(const ModuleDisplayStateTypeBuilder &other);
};

#endif // MODULE_DISPLAY_STATE_TYPE_BUILDER_H
