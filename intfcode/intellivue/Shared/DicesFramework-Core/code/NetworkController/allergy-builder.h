#ifndef ALLERGYBUILDER_H
#define ALLERGYBUILDER_H

#include "allergy-type-builder.h"

enum class DicesRcEntityBuilder;

class AllergyBuilder : public AllergyTypeBuilder
{
public:
  AllergyBuilder();
  ~AllergyBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  AllergyBuilder(const AllergyBuilder &other);
  AllergyBuilder &operator=(const AllergyBuilder &other);
};

#endif // ALLERGYBUILDER_H
