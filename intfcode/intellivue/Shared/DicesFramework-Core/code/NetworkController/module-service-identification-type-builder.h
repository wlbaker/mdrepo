#ifndef MODULE_SERVICE_IDENTIFICATION_TYPE_BUILDER_H
#define MODULE_SERVICE_IDENTIFICATION_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class ModuleServiceIdentificationTypeBuilder : public AbstractTopicBuilder
{
public:
  ModuleServiceIdentificationTypeBuilder();
  ~ModuleServiceIdentificationTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  ModuleServiceIdentificationTypeBuilder(const ModuleServiceIdentificationTypeBuilder &other);
  ModuleServiceIdentificationTypeBuilder &operator=(const ModuleServiceIdentificationTypeBuilder &other);
};

#endif // MODULE_SERVICE_IDENTIFICATION_TYPE_BUILDER_H
