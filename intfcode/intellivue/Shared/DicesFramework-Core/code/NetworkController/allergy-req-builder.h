#ifndef ALLERGYREQUESTBUILDER_H
#define ALLERGYREQUESTBUILDER_H

#include "allergy-type-builder.h"

enum class DicesRcEntityBuilder;

class AllergyReqBuilder : public AllergyTypeBuilder
{
public:
  AllergyReqBuilder();
  ~AllergyReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  AllergyReqBuilder(const AllergyReqBuilder &other);
  AllergyReqBuilder &operator=(const AllergyReqBuilder &other);
};

#endif // ALLERGYREQUESTBUILDER_H

