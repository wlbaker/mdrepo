#ifndef APP_FOCUS_STATE_REQ_BUILDER_H
#define APP_FOCUS_STATE_REQ_BUILDER_H

#include "app-focus-state-type-builder.h"

enum class DicesRcEntityBuilder;

class AppFocusStateReqBuilder : public AppFocusStateTypeBuilder
{
public:
  AppFocusStateReqBuilder();
  ~AppFocusStateReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  AppFocusStateReqBuilder(const AppFocusStateReqBuilder &other);
  AppFocusStateReqBuilder &operator=(const AppFocusStateReqBuilder &other);
};

#endif // APP_FOCUS_STATE_REQ_BUILDER_H
