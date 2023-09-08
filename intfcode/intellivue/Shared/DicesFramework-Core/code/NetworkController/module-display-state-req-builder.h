#ifndef MODULE_DISPLAY_STATE_REQ_BUILDER_H
#define MODULE_DISPLAY_STATE_REQ_BUILDER_H

#include "module-display-state-type-builder.h"

enum class DicesRcEntityBuilder;

class ModuleDisplayStateReqBuilder : public ModuleDisplayStateTypeBuilder
{
public:
  ModuleDisplayStateReqBuilder();
  ~ModuleDisplayStateReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  ModuleDisplayStateReqBuilder(const ModuleDisplayStateReqBuilder &other);
  ModuleDisplayStateReqBuilder &operator=(const ModuleDisplayStateReqBuilder &other);
};

#endif // MODULE_DISPLAY_STATE_REQ_BUILDER_H
