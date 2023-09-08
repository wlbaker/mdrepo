#ifndef APP_FOCUS_STATE_OBJ_BUILDER_H
#define APP_FOCUS_STATE_OBJ_BUILDER_H

#include "app-focus-state-type-builder.h"

enum class DicesRcEntityBuilder;

class AppFocusStateObjBuilder : public AppFocusStateTypeBuilder
{
public:
  AppFocusStateObjBuilder();
  ~AppFocusStateObjBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  AppFocusStateObjBuilder(const AppFocusStateObjBuilder &other);
  AppFocusStateObjBuilder &operator=(const AppFocusStateObjBuilder &other);
};

#endif // APP_FOCUS_STATE_OBJ_BUILDER_H
