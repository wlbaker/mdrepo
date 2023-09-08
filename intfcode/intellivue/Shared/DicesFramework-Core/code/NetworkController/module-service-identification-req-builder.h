#ifndef MODULE_SERVICE_IDENTIFICATION_REQ_BUILDER_H
#define MODULE_SERVICE_IDENTIFICATION_REQ_BUILDER_H

#include "module-service-identification-type-builder.h"

enum class DicesRcEntityBuilder;

class ModuleServiceIdentificationReqBuilder : public ModuleServiceIdentificationTypeBuilder
{
public:
  ModuleServiceIdentificationReqBuilder();
  ~ModuleServiceIdentificationReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  ModuleServiceIdentificationReqBuilder(const ModuleServiceIdentificationReqBuilder &other);
  ModuleServiceIdentificationReqBuilder &operator=(const ModuleServiceIdentificationReqBuilder &other);
};

#endif // MODULE_SERVICE_IDENTIFICATION_REQ_BUILDER_H
