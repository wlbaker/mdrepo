#include "dx-history-req-builder.h"
#include "exprSupport.h"

DxHistoryReqBuilder::DxHistoryReqBuilder() :
  DxHistoryTypeBuilder()
{

}

DxHistoryReqBuilder::~DxHistoryReqBuilder()
{

}

const std::string DxHistoryReqBuilder::get_topic_name()
{
  return expr::DxHistoryReqTopic;
}
