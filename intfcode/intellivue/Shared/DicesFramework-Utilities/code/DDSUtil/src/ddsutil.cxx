/*********************************************************************************************
 * File:   ddsutil.cxx
 *
 * Defines some DDS utility classes and functions.
 *
 *********************************************************************************************/

#include "ddsutil.h"

#include <sstream>

#define STRINGIFY(x) #x

DDSUTIL::ReturnCode::ReturnCode(DDS_ReturnCode_t retCode, const char * const fileNamePtr, const int lineNumber)
	: std::runtime_error(makeWhat(retCode, fileNamePtr, lineNumber).c_str()),
	retCode(retCode), symbolNamePtr(symbolName(retCode)), fileNamePtr(fileNamePtr), lineNumber(lineNumber)
{

}

DDSUTIL::ReturnCode::~ReturnCode() throw()
{

}

namespace DDSUTIL
{
  std::ostream & operator<<(std::ostream & os, const DDSUTIL::ReturnCode & retCode)
  {
    os << retCode.what();
    return os;
  }
}

std::string DDSUTIL::ReturnCode::makeWhat(DDS_ReturnCode_t retCode, const char * const fileNamePtr, const int lineNumber)
{
  std::stringstream ss;

  ss << "DDS Return Code: " << retCode << " (" << symbolName(retCode) << ") @ "
    << fileNamePtr << ":" << lineNumber;

  return ss.str();
}

const char * DDSUTIL::ReturnCode::symbolName(DDS_ReturnCode_t retCode)
{
  const char * symbolNamePtr = 0;

  switch (retCode) 
  {
    case DDS_RETCODE_OK:
      symbolNamePtr = "DDS_RETCODE_OK: nullptr?";
      break;

    case DDS_RETCODE_ERROR:
      symbolNamePtr = STRINGIFY(DDS_RETCODE_ERROR);
      break;

    case DDS_RETCODE_UNSUPPORTED:
      symbolNamePtr = STRINGIFY(DDS_RETCODE_UNSUPPORTED);
      break;

    case DDS_RETCODE_BAD_PARAMETER:
      symbolNamePtr = STRINGIFY(DDS_RETCODE_BAD_PARAMETER);
      break;

    case DDS_RETCODE_PRECONDITION_NOT_MET:
      symbolNamePtr = STRINGIFY(DDS_RETCODE_PRECONDITION_NOT_MET);
      break;

    case DDS_RETCODE_OUT_OF_RESOURCES:
      symbolNamePtr = STRINGIFY(DDS_RETCODE_OUT_OF_RESOURCES);
      break;

    case DDS_RETCODE_NOT_ENABLED:
      symbolNamePtr = STRINGIFY(DDS_RETCODE_NOT_ENABLED);
      break;

    case DDS_RETCODE_IMMUTABLE_POLICY:
      symbolNamePtr = STRINGIFY(DDS_RETCODE_IMMUTABLE_POLICY);
      break;

    case DDS_RETCODE_INCONSISTENT_POLICY:
      symbolNamePtr = STRINGIFY(DDS_RETCODE_INCONSISTENT_POLICY);
      break;

    case DDS_RETCODE_ALREADY_DELETED:
      symbolNamePtr = STRINGIFY(DDS_RETCODE_ALREADY_DELETED);
      break;

    case DDS_RETCODE_TIMEOUT:
      symbolNamePtr = STRINGIFY(DDS_RETCODE_TIMEOUT);
      break;

    case DDS_RETCODE_NO_DATA:
      symbolNamePtr = STRINGIFY(DDS_RETCODE_NO_DATA);
      break;

    case DDS_RETCODE_ILLEGAL_OPERATION:
      symbolNamePtr = STRINGIFY(DDS_RETCODE_ILLEGAL_OPERATION);
      break;

    default:
      symbolNamePtr = "*** UNKNOWN DDS ERROR CODE ***";
      break;
  }

  return symbolNamePtr;
}

void DDSUTIL::checkret(DDS_ReturnCode_t retCode, const char * const fileNamePtr, const int lineNumber)
{
  if (retCode != DDS_RETCODE_OK && retCode != DDS_RETCODE_NO_DATA) 
  {
    throw DDSUTIL::ReturnCode(retCode, fileNamePtr, lineNumber);
  }
}

DDS::DomainParticipantFactory* DDSUTIL::loadConfig(const char * fileName)
{
  auto factory = CP(DDS::DomainParticipantFactory::get_instance());

  // Load existing factory QoS
  DDS::DomainParticipantFactoryQos qos;
  CR(factory->get_qos(qos));

  // Increase length of any existing URL profile by one to append new element
  auto length = qos.profile.url_profile.length();
  auto index = length++;
  auto maximum = std::max(qos.profile.url_profile.maximum(), length);
  if (!qos.profile.url_profile.ensure_length(length, maximum)) { CR(DDS::RETCODE_ERROR); }
  qos.profile.url_profile[index] = DDS::String_dup(fileName);

  // Set revised factory QoS and load profiles.
  CR(factory->set_qos(qos));
  CR(factory->load_profiles());

  return factory;
}


DDSUTIL::WaitSet::WaitSet(DDS::Condition * exitCond)
  : exitCond(exitCond)
{
  CR(DDS::WaitSet::attach_condition(exitCond));
}

DDSUTIL::WaitSet & DDSUTIL::WaitSet::attach_condition(DDS::Condition * cond, std::function<void(void)> handler)
{
  CR(DDS::WaitSet::attach_condition(cond));
  conditionHandlers.insert(std::pair<DDS::Condition *, std::function<void(void)>>(cond, handler));
  return *this;
}

DDSUTIL::WaitSet & DDSUTIL::WaitSet::detach_condition(DDS::Condition & cond)
{
  CR(DDS::WaitSet::detach_condition(&cond));
  return *this;
}

void DDSUTIL::WaitSet::process(const DDS::Duration_t & timeout)
{
  while (!exitCond->get_trigger_value()) 
  {
    DDS::ConditionSeq ac;
    auto ret = wait(ac, timeout);
    if (ret == DDS::RETCODE_TIMEOUT) {
      return;
    }
    CR(ret);
    for (auto i = 0; i < ac.length() && !exitCond->get_trigger_value(); ++i) 
    {
      conditionHandlers[ac[i]]();
    }
  }
}
