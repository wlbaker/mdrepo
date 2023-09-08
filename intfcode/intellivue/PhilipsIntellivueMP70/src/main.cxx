/*
 * @file main.cxx
 *
 * @brief The main method initializes and configures log4cplus. The main method
 * runs the Philips Intellivue MP70 device driver.
 *
 * @author M Szwaja
 */
//=============================================================================
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include "PhilipsIntellivueMP70ReturnCodes.h"
#include "dd_philips_intellivue_mp70.h"
#include "Core/DatabaseConnection/connection-utilities.h"

static const char* klog4cplus_properties =
  "./log4cplus.properties";
static const char* kIntellivueSchemaDir =
  "./createdb.sh";

int main(int argc, char** argv)
{
  static const char* sfn = "main() ";

  log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

  try
  {
    log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(
      klog4cplus_properties));
  }
  catch (std::exception &ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception occured while opening "
      << klog4cplus_properties << ". " << ex.what());
    exit(EXIT_FAILURE);
  }

  // use script to determine if database already exists & create if it doesn't.
  std::string result = "";
  try
  {
    result = exec(kIntellivueSchemaDir);
  }
  catch (const std::exception& e)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << " Exception creating database: " << e.what());
    result = "ERROR";
  }

  if (std::string::npos == result.find("OK"))
  {
    LOG4CPLUS_ERROR(root_logger, sfn << " Error creating database.");
    exit(EXIT_FAILURE);
  }

  DDPhilipsIntellivueMP70 driver;

  DicesRcPhilipsIntellivueMP70 driver_status = driver.RunDriver(argc, argv);
  if (driver_status != DicesRcPhilipsIntellivueMP70::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
      << DicesRcPhilipsIntellivueMP70StatusMessage::
      DicesRcPhilipsIntellivueMP70ToString(driver_status));
    exit(EXIT_FAILURE);
  }

  return 0;
}
