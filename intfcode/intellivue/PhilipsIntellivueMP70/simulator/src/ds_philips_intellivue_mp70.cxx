/**
 * @file ds_masimo_pulse_oximeter.cxx
 *
 * @brief Simulates the philips intellivue mp70 device. This program listens
 * for commands and a response with the appropriate responses.
 *
 * @author M Szwaja
 */
//=============================================================================
#include <exception>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include "Communication/RS232/rs232-read-interface-three-pin.h"
#include "philips_intellivue_mp70_simulator.h"
#include "Communication/RS232/rc-rs232.h"

static const uint8_t kAsciiEOF = 0xC1;
static const char* klog4cplus_properties = "log4cplus.properties";

int main(int argc, char** argv)
{
  static const char* sfn = "main() ";
  log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

  try
  {
    log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(
      klog4cplus_properties));
  }
  catch (std::exception& ex)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Exception occurred while opening "
      << klog4cplus_properties << ". " << ex.what());
    return EXIT_FAILURE;
  }

  ThreePinRS232ReadInterface* _rs232_read_impl
    = new (std::nothrow) ThreePinRS232ReadInterface();
  if (!_rs232_read_impl)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Unable to create read interface.");
    return EXIT_FAILURE;
  }

  // Serial reader should stop reading when the end of frame character is read
  DicesRcrs232 status = _rs232_read_impl->set_terminating_character_sequence(
    &kAsciiEOF, sizeof(kAsciiEOF));
  if (status != DicesRcrs232::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Unable to set terminating sequence "
      << _rs232_read_impl->get_statusmsg(status));
    delete _rs232_read_impl;
    _rs232_read_impl = 0;
    return EXIT_FAILURE;
  }

  PhilipsIntellivueMP70Simulator sim(
    reinterpret_cast<RS232ReadInterface*>(_rs232_read_impl));
  DicesRcPhilipsIntellivueSimulatorMP70 sim_status = sim.RunSimulator(argc, argv);
  if (sim_status != DicesRcPhilipsIntellivueSimulatorMP70::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Unable to run simulator. "
      << DicesRcPhilipsIntellivueSimulatorMP70StatusMessage::
      DicesRcPhilipsIntellivueSimulatorMP70ToString(sim_status));
    delete _rs232_read_impl;
    _rs232_read_impl = 0;
    return EXIT_FAILURE;
  }

  delete _rs232_read_impl;
  _rs232_read_impl = 0;
  return 0;
}

