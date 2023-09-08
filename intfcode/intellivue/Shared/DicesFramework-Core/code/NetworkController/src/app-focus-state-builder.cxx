#include "app-focus-state-builder.h"
#include <docboxSupport.h>

AppFocusStateBuilder::AppFocusStateBuilder() :
  AppFocusStateTypeBuilder()
{

}

AppFocusStateBuilder::~AppFocusStateBuilder()
{

}

const std::string AppFocusStateBuilder::get_topic_name()
{
  return docbox::AppFocusStateTopic;
}
