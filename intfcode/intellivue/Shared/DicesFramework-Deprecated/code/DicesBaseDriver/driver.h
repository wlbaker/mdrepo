/*
 * File:   driver.h
 * Author: Robert England
 *
 * Created on November 18, 2014
 * Last Modified on November 19, 2014
 */

#ifndef DRIVER_H
#define	DRIVER_H

#include <mutex>
#include <chrono>

enum class DicesRcDriver;
class Parser;
class BaseComm;
class BusComm;

class Driver
{
 public:

  Driver() : _bus_comm(nullptr), _quit_flag(false), _sleep_time_ms(std::chrono::milliseconds(0)) { };

  virtual ~Driver();

  std::chrono::milliseconds get_sleep_time_ms();
  void set_sleep_time_ms(std::chrono::milliseconds milliseconds);

  DicesRcDriver InitDDS(Parser* parser);
  DicesRcDriver RunDriver(Parser* parser, BaseComm* basecomm);

 private:
  // Disallow use of implicitly generated member functions:
  Driver(const Driver& orig);
  Driver &operator=(const Driver& orig);

  DicesRcDriver ShutdownDDS();

  bool get_quit_flag();
  void set_quit_flag(bool torf);

  BusComm* _bus_comm;
  bool _quit_flag;
  std::mutex _quit_flag_mutex;  // protects _quit_flag
  std::chrono::milliseconds _sleep_time_ms;
};

#endif	/* DRIVER_H */

