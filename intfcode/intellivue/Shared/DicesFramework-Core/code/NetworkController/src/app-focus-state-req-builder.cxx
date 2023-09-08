#include "app-focus-state-req-builder.h"
#include <docboxSupport.h>

AppFocusStateReqBuilder::AppFocusStateReqBuilder() :
  AppFocusStateTypeBuilder()
{

}

AppFocusStateReqBuilder::~AppFocusStateReqBuilder()
{

}

const std::string AppFocusStateReqBuilder::get_topic_name()
{
  return docbox::AppFocusStateReqTopic;
}
