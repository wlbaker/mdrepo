#ifndef DX_HISTORY_BUILDER_H
#define DX_HISTORY_BUILDER_H

#include "dx-history-type-builder.h"

enum class DicesRcEntityBuilder;

class DxHistoryBuilder : public DxHistoryTypeBuilder
{
public:
  DxHistoryBuilder();
  ~DxHistoryBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DxHistoryBuilder(const DxHistoryBuilder &other);
  DxHistoryBuilder &operator=(const DxHistoryBuilder &other);
};

#endif // DX_HISTORY_BUILDER_H
