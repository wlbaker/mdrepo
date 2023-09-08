/**
 * @file UnitTestReturnCodes.h
 *
 * @brief Declares and defines a set of all return codes used in the Philips
 * Intellivue MP70 unit tests
 *
 * @author Michael Szwaja
 */
//=============================================================================

#ifndef PHILIPS_INTELLIVUE_MP70_TEST_SRC_UNIT_TEST_RETURN_CODES_H_
#define PHILIPS_INTELLIVUE_MP70_TEST_SRC_UNIT_TEST_RETURN_CODES_H_

#include <string>

enum class DicesRcUnitTest
{
  OK = 0,
  FAIL = 1,
};

class DicesRcUnitTestStatusMessage
{
 public:

  const static std::string DicesRcUnitTestToString(const DicesRcUnitTest error_code)
  {
    std::string error_message;
    switch (error_code)
    {
      case DicesRcUnitTest::OK:
        error_message = "Ok";
        break;
      case DicesRcUnitTest::FAIL:
        error_message = "Fail";
        break;
      default: // should not be reached
        error_message = "Unknown error code";
        break;
    }
    return error_message;
  }

 private:
  // Disallow use of implicitly generated member functions:
  DicesRcUnitTestStatusMessage(const DicesRcUnitTestStatusMessage &src);
  DicesRcUnitTestStatusMessage &operator=(const DicesRcUnitTestStatusMessage &rhs);
};

#endif
