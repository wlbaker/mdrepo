#ifndef DX_HISTORY_TYPE_BUILDER_H
#define DX_HISTORY_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class DxHistoryTypeBuilder : public AbstractTopicBuilder
{
public:
  DxHistoryTypeBuilder();
  ~DxHistoryTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  DxHistoryTypeBuilder(const DxHistoryTypeBuilder &other);
  DxHistoryTypeBuilder &operator=(const DxHistoryTypeBuilder &other);
};

#endif // DX_HISTORY_TYPE_BUILDER_H
