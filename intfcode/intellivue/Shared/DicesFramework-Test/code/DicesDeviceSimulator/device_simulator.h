/**
 * @file device_simulator.h
 *
 * @brief Declares a base class for device simulator.
 *
 * @author M Szwaja
 */
//=============================================================================

#ifndef DICES_DEVICE_SIMULATOR_SRC_DEVICE_SIMULATOR_H
#define DICES_DEVICE_SIMULATOR_SRC_DEVICE_SIMULATOR_H

#include <string>
#include "rs232.h"
#include "DeviceSimulatorReturnCodes.h"

class RS232ReadInterface;

class DeviceSimulator
{
public:

  /**
   * Parses command line arguments.
   * @param [in] argc The number of arguments in argv
   * @param [in] argv An array of char pointers which contain command line
   *   arguments.
   * @return Returns DicesRcDeviceSimulator::OK for success 
   */
  DicesRcDeviceSimulator ParseCommandLine(int argc, char** argv);

  /**
   * Opens serial port.
   * @return Returns zero for success.
   */
  virtual DicesRcDeviceSimulator OpenRS232Port();

protected:
  DeviceSimulator(RS232ReadInterface* serial_impl);
  ~DeviceSimulator();

  std::string _portname;
  int _baud;
  int _databits;
  rs232_stopbits _stopbits;
  rs232_parity _parity;
  int _handshaking;
  bool _sw_flow_control;
  bool _hw_flow_control;
  std::string _model;
  std::string _data_file_name;
  std::string _network_interface;

  RS232* _rs232;

private:
  // Disallow use of implicitly generated member functions:
  DeviceSimulator(const DeviceSimulator& src);
  DeviceSimulator &operator=(const DeviceSimulator& rhs);
};

#endif

