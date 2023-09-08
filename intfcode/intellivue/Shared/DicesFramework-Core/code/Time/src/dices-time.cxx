// NAME dices-time.cxx
// SUMMARY Defines a class for DICES time operations.

#include "../dices-time.h"
#include <chrono>
#include "common.h"

DicesTime::DicesTime() { }

DicesTime::~DicesTime() { }

int DicesTime::GetTimeOfDayUtc(ice::Timespec *ts)
{
  // NOTE std::chrono::system_clock is the only clock required to have epoch of
  // the system time as its internal epoch.

  int iret = 1;

  typedef intmax_t Chron_seconds;
  typedef unsigned long Chron_nanoseconds;

  struct Chron_Timespec
  {
    Chron_seconds seconds;
    Chron_nanoseconds nanoseconds;
  };

  if (ts)
  {
    Chron_Timespec cts;
    
    std::chrono::system_clock::time_point tpnow =
      std::chrono::system_clock::now();
//    std::chrono::high_resolution_clock::now();

    std::chrono::system_clock::duration dura = tpnow.time_since_epoch();
    cts.seconds =
      dura.count() * std::chrono::system_clock::period::num
      / std::chrono::system_clock::period::den;
    cts.nanoseconds =
        std::chrono::duration_cast<std::chrono::nanoseconds>(dura).count()
      % std::giga::num;
    ts->seconds = static_cast<ice::TIME_T>(cts.seconds);
    ts->nanoseconds = static_cast<ice::INT32>(cts.nanoseconds);
    iret = 0;
  }

  return iret;
}

