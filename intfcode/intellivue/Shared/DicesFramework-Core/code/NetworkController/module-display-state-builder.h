#ifndef MODULE_DISPLAY_STATE_BUILDER_H
#define MODULE_DISPLAY_STATE_BUILDER_H

#include "module-display-state-type-builder.h"

class ModuleDisplayStateBuilder : public ModuleDisplayStateTypeBuilder
{
public:
  ModuleDisplayStateBuilder();
  ~ModuleDisplayStateBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  ModuleDisplayStateBuilder(const ModuleDisplayStateBuilder &other);
  ModuleDisplayStateBuilder &operator=(const ModuleDisplayStateBuilder &other);
};

#endif // MODULE_DISPLAY_STATE_BUILDER_H
