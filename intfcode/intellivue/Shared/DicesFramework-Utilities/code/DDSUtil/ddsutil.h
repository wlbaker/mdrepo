/*********************************************************************************************
 * File:   ddsutil.h
 *
 * Declares DDS utility classes.
 *
 *********************************************************************************************/

#ifndef DDSUTIL_H
#define DDSUTIL_H

#include <functional>
#include <ostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include "ndds_namespace_cpp.h"

// macro to check DDS Return Codes
#ifndef CR
#define CR(code) DDSUTIL::checkret((code), __FILE__, __LINE__)
#endif

// macro to check DDS pointers
#ifndef CP
#define CP(code) DDSUTIL::checkptr<>((code), __FILE__, __LINE__)
#endif

namespace DDSUTIL
{
  class ReturnCode : public std::runtime_error 
  {
    public:
      // Normal constructor.
      ReturnCode(DDS_ReturnCode_t retCode, const char * const fileNamePtr, const int lineNumber);

      virtual ~ReturnCode() throw();

      // Convenience routine for stream insertion, e.g. std::cerr << retCode
      friend std::ostream & operator<<(std::ostream & os, const ReturnCode & retCode);

      // Expose the data to make alternatives to 'what()' trivial.
      DDS_ReturnCode_t retCode;
      const char * symbolNamePtr;
      const char * const fileNamePtr;
      const int lineNumber;

    protected:
      std::string makeWhat(DDS_ReturnCode_t retCode, const char * const fileNamePtr, const int lineNumber);
      const char * symbolName(DDS_ReturnCode_t retCode);

    private:
      // Copying not currently supported.
      //ReturnCode & operator=(const ReturnCode & returnCode) = delete;
      //ReturnCode(const ReturnCode & other) = delete;
  };

  // Check a return code and convert off-normal ones to exceptions
  void checkret(DDS_ReturnCode_t retCode, const char * const fileNamePtr, const int lineNumber);

  // Check a pointer before returning it for dereference
  template <typename T> T * checkptr(T * tPtr, const char * const fileNamePtr, const int lineNumber)
  {
    if (tPtr) {
      return tPtr;
    }
    else {
      throw ReturnCode(DDS_RETCODE_OK, fileNamePtr, lineNumber);
	}
  }

  // Add a QoS file to the DP Factory
  DDS::DomainParticipantFactory * loadConfig(const char * fileName);

  // Convenience wrapper of WaitSet
  class WaitSet : public DDS::WaitSet
  {
    public:
      // Constructor captures explicit notion of a guard condition to trigger shutdown.
      WaitSet(DDS::Condition * exitCond);
      
      // Attach function allows condition creation and association with a handler function
      // to be done inline, e.g. with a lambda.
      virtual WaitSet & attach_condition(DDS::Condition * cond, std::function<void(void)> handler);
      virtual WaitSet & detach_condition(DDS::Condition & cond);
      
      // Waits for and dispatches active conditions.
      virtual void process(const DDS::Duration_t & timeout = DDS::DURATION_INFINITE);
    
    protected:
      std::unordered_map<DDS::Condition *, std::function<void(void)>> conditionHandlers;
      DDS::Condition * exitCond;
  };

}

#endif // DDSUTIL_H
