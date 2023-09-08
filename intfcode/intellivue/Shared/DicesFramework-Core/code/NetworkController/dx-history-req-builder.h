#ifndef DX_HISTORY_REQ_BUILDER_H
#define DX_HISTORY_REQ_BUILDER_H

#include "dx-history-type-builder.h"

enum class DicesRcEntityBuilder;

class DxHistoryReqBuilder : public DxHistoryTypeBuilder
{
public:
  DxHistoryReqBuilder();
  ~DxHistoryReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DxHistoryReqBuilder(const DxHistoryReqBuilder &other);
  DxHistoryReqBuilder &operator=(const DxHistoryReqBuilder &other);
};

#endif // DX_HISTORY_REQ_BUILDER_H
