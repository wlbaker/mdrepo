#include "app-focus-state-obj-builder.h"
#include <docboxSupport.h>

AppFocusStateObjBuilder::AppFocusStateObjBuilder() :
  AppFocusStateTypeBuilder()
{

}

AppFocusStateObjBuilder::~AppFocusStateObjBuilder()
{

}

const std::string AppFocusStateObjBuilder::get_topic_name()
{
  return docbox::AppFocusStateObjTopic;
}
