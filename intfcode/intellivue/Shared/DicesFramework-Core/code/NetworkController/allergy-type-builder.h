#ifndef ALLERGYTYPEBUILDER_H
#define ALLERGYTYPEBUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class AllergyTypeBuilder : public AbstractTopicBuilder
{
public:
  AllergyTypeBuilder();
  ~AllergyTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  AllergyTypeBuilder(const AllergyTypeBuilder &other);
  AllergyTypeBuilder &operator=(const AllergyTypeBuilder &other);
};

#endif // ALLERGYBUILDER_H
