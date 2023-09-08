/**
 * @file  SpinOrBail.h
 * @brief Spin unilt specified time or bail on user signal.
 */
//=============================================================================
#ifndef SPIN_OR_BAIL_H_
#define SPIN_OR_BAIL_H_

#include <chrono>
#include <thread>
#include "kbhit_util.h"

//=============================================================================
class SpinOrBail
{
private:
  // DATA


  // NOT IMPLEMENTED
  // Disallow use of implicitly generated member functions:
  SpinOrBail(const SpinOrBail &src);
  SpinOrBail &operator=(const SpinOrBail &rhs);

public:
  // CREATORS
  SpinOrBail() { }
  ~SpinOrBail() { }

  //=============================================================================
  // Spin here for duration specified by duraspin, or until user signals bail by
  // pressing escape key. Return true if user signals bail.
  template <class T>
  bool spin_duration_or_bail(T duraspin)
  {
    bool bailout = false;
    int keyboard_char_input = 0;

    std::chrono::system_clock::time_point tstart =
      std::chrono::system_clock::now();

    std::chrono::system_clock::time_point tp = tstart + duraspin;

    while (!bailout && (std::chrono::system_clock::now() - tstart) < duraspin)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(0));
      keyboard_char_input = kbhit_util::kbhit();
      if (keyboard_char_input == kbhit_util::kAsciiEsc) bailout = true;
    }
    return bailout;
  }

  //=============================================================================
  // Spin here until the timepoint specified by tp, or until user signals bail by
  // pressing escape key. Return true if user signals bail.
  bool spin_until_or_bail(std::chrono::system_clock::time_point tp)
  {
    bool bailout = false;
    int keyboard_char_input = 0;

    while (!bailout && (std::chrono::system_clock::now() < tp))
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(0));
      keyboard_char_input = kbhit_util::kbhit();
      if (keyboard_char_input == kbhit_util::kAsciiEsc) bailout = true;
    }
    return bailout;
  }


  // MANIPULATORS


  // ACCESSORS

};

#endif
