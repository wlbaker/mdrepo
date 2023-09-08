// NAME dices-time.h
// SUMMARY Declares a class for DICES time operations.

#ifndef DICESTIME_H
#define	DICESTIME_H

// forward declaration
namespace ice
{
  class Timespec;
};

class DicesTime
{
 public:
  DicesTime();
  ~DicesTime();

  DicesTime(const DicesTime& orig) = delete;
  DicesTime &operator=(const DicesTime& orig) = delete;

  static int GetTimeOfDayUtc(ice::Timespec *ts);
};

#endif	/* DICESTIME_H */

