#ifndef DICES_TYPE_REGISTER_H_
#define DICES_TYPE_REGISTER_H_

#include <ndds/ndds_namespace_cpp.h>
#include "dicestyperegisterreturncodes.h"

class DICESTypeRegister
{
 public:
  DICESTypeRegister();
  ~DICESTypeRegister();

  DICESTypeRegisterRC registerAllTypes();
  DICESTypeRegisterRC UnregisterAllTypes(DDS::DomainParticipant* participant);

 private:
  // Disallow use of implicitly generated member functions:
  DICESTypeRegister(const DICESTypeRegister &director);
  DICESTypeRegister &operator=(const DICESTypeRegister &director);
};

#endif
