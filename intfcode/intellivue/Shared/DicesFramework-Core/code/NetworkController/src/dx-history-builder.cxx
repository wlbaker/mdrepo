#include "dx-history-builder.h"
#include "exprSupport.h"

DxHistoryBuilder::DxHistoryBuilder() :
  DxHistoryTypeBuilder()
{

}

DxHistoryBuilder::~DxHistoryBuilder()
{

}

const std::string DxHistoryBuilder::get_topic_name()
{
  return expr::DxHistoryTopic;
}
