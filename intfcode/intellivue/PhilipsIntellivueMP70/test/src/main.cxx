/**
 * @file main.cxx
 *
 * @breif Run suite of tests on the intellivue driver.
 *
 * @author M Szwaja
 *
 */
//=============================================================================
#define CATCH_CONFIG_MAIN
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include "Test/Catch/catch.hpp"
#include "UnitTestReturnCodes.h"
#include "intellivue_utils_unit_test.h"
#include "serial_converter_unit_test.h"
#include "intellivue_association_release_request_unit_test.h"
#include "intellivue_association_request_unit_test.h"
#include "intellivue_association_response_unit_test.h"
#include "dd_philips_intellivue_mp70_unit_test.h"
#include "ini_association_request_parser_unit_test.h"
#include "ini_dim_parser_unit_test.h"
#include "ini_rtsa_priority_list_parser_unit_test.h"
#include "intellivue_connect_indication_message_unit_test.h"

TEST_CASE("Test IntellivueUtils class", "[intellivue_utils]")
{
  const char* sfn = "main() ";
  const char* logger_properties_file = "log4cplus.properties";

  log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

  try
  {
    log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(
      logger_properties_file));
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception occured while opening "
      << logger_properties_file << ". " << ex.what());
    return;
  }

  DicesRcUnitTest test_status = DicesRcUnitTest::OK;
  IntellivueUtilsUnitTest utils_test;
  test_status = utils_test.RunTests();

  return;
}

TEST_CASE("Test SerialConverter class", "[serial_converter]")
{
  const char* sfn = "main() ";
  const char* logger_properties_file = "log4cplus.properties";

  log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

  try
  {
    log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(
      logger_properties_file));
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception occured while opening "
      << logger_properties_file << ". " << ex.what());
    return;
  }

  DicesRcUnitTest test_status = DicesRcUnitTest::OK;
  SerialConverterUnitTest converter_test;
  test_status = converter_test.RunTests();

  return;
}

TEST_CASE("Test IntellivueAssociationReleaseRequest class", "[intellivue_association_release_request]")
{
  const char* sfn = "main() ";
  const char* logger_properties_file = "log4cplus.properties";

  log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

  try
  {
    log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(
      logger_properties_file));
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception occured while opening "
      << logger_properties_file << ". " << ex.what());
    return;
  }

  DicesRcUnitTest test_status = DicesRcUnitTest::OK;
  IntellivueAssociationReleaseRequestUnitTest unit_test;
  test_status = unit_test.RunTests();

  return;
}

TEST_CASE("Test IntellivueAssociationRequest class", "[intellivue_association_request]")
{
  const char* sfn = "main() ";
  const char* logger_properties_file = "log4cplus.properties";

  log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

  try
  {
    log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(
      logger_properties_file));
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception occured while opening "
      << logger_properties_file << ". " << ex.what());
    return;
  }

  DicesRcUnitTest test_status = DicesRcUnitTest::OK;
  IntellivueAssociationRequestUnitTest unit_test;
  test_status = unit_test.RunTests();

  return;
}

TEST_CASE("Test IntellivueAssociationResponse class", "[intellivue_association_response]")
{
  const char* sfn = "main() ";
  const char* logger_properties_file = "log4cplus.properties";

  log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

  try
  {
    log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(
      logger_properties_file));
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception occured while opening "
      << logger_properties_file << ". " << ex.what());
    return;
  }

  DicesRcUnitTest test_status = DicesRcUnitTest::OK;
  IntellivueAssociationResponseUnitTest unit_test;
  test_status = unit_test.RunTests();

  return;
}

TEST_CASE("Test DDPhilipsIntellivueMP70 class", "[dd_philips_intellivue_mp70]")
{
  const char* sfn = "main() ";
  const char* logger_properties_file = "log4cplus.properties";

  log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

  try
  {
    log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(
      logger_properties_file));
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception occured while opening "
      << logger_properties_file << ". " << ex.what());
    return;
  }

  DicesRcUnitTest test_status = DicesRcUnitTest::OK;
  DDPhilipsIntellivueMP70UnitTest unit_test;
  test_status = unit_test.RunTests();

  return;
}

TEST_CASE("Test IniAssociationRequestParser class", "[ini_association_request_parser]")
{
  const char* sfn = "main() ";
  const char* logger_properties_file = "log4cplus.properties";

  log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

  try
  {
    log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(
      logger_properties_file));
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception occured while opening "
      << logger_properties_file << ". " << ex.what());
    return;
  }

  DicesRcUnitTest test_status = DicesRcUnitTest::OK;
  IniAssociationRequestParserUnitTest unit_test;
  test_status = unit_test.RunTests();

  return;
}

TEST_CASE("Test DIMParser class", "[dim_parser]")
{
  const char* sfn = "main() ";
  const char* logger_properties_file = "log4cplus.properties";

  log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

  try
  {
    log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(
      logger_properties_file));
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception occured while opening "
      << logger_properties_file << ". " << ex.what());
    return;
  }

  DicesRcUnitTest test_status = DicesRcUnitTest::OK;
  DIMParserUnitTest unit_test;
  test_status = unit_test.RunTests();

  return;
}

TEST_CASE("Test IniRTSAPriorityListParser class", "[ini_rtsa_priority_list_parser]")
{
  const char* sfn = "main() ";
  const char* logger_properties_file = "log4cplus.properties";

  log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

  try
  {
    log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(
      logger_properties_file));
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception occured while opening "
      << logger_properties_file << ". " << ex.what());
    return;
  }

  DicesRcUnitTest test_status = DicesRcUnitTest::OK;
  IniRTSAPriorityListParserUnitTest unit_test;
  test_status = unit_test.RunTests();

  return;
}

TEST_CASE("Test IntellivueConnectIndicationMessage class", "[intellivue_connect_indication_message]")
{
  const char* sfn = "main() ";
  const char* logger_properties_file = "log4cplus.properties";

  log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

  try
  {
    log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(
      logger_properties_file));
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception occured while opening "
      << logger_properties_file << ". " << ex.what());
    return;
  }

  DicesRcUnitTest test_status = DicesRcUnitTest::OK;
  IntellivueConnectIndicationMessageUnitTest unit_test;
  test_status = unit_test.RunTests();

  return;
}

