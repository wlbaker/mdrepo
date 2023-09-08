/**
 * @file device_comm.h
 * @brief Declares a base class which handles all communication between the
 * driver and the device.
 * @author Michael Szwaja
 */
//=============================================================================
#ifndef DICES_BASE_DRIVER_SRC_DEVICE_COMM_H_
#define	DICES_BASE_DRIVER_SRC_DEVICE_COMM_H_

enum class DicesRcDriver;
class BaseComm;
class Parser;

class DeviceComm
{
 public:
  DeviceComm(BaseComm* base_comm, Parser* parser);
  virtual ~DeviceComm();

  DicesRcDriver InitComm();
  DicesRcDriver ShutdownComm();
  DicesRcDriver SendToDevice();
  DicesRcDriver ReadFromDevice();
  DicesRcDriver Flush();

 private:
  // Disallow use of implicitly generated member functions:
  DeviceComm(const DeviceComm& orig);
  DeviceComm &operator=(const DeviceComm& orig);

  BaseComm* _base_comm;
  Parser* _parser;
};

#endif

