/**
 * @file  HelloIceData.h
 * @brief Initialize common data objects.
 */
//=============================================================================
#ifndef ICE_DATA_H_
#define ICE_DATA_H_

#include <string>

// ISO 11073 metric IDs, medical supervisory control and data acq (SCADA)
#define MDC_PULS_OXIM_SAT_O2    (19384)
#define MDC_PULS_OXIM_PLETH     (19380)
#define MDC_PULS_OXIM_PULS_RATE (18458)

namespace ice
{
class Timespec;
class NumericObservedValue;
class MDS;
}

//=============================================================================
class HelloIceData
{
private:
  // Disallow use of implicitly generated member functions:
  HelloIceData();
  ~HelloIceData();
  HelloIceData(const HelloIceData &src);
  HelloIceData &operator=(const HelloIceData &rhs);

public:
  static void gettimeofday_utc(ice::Timespec *timespec);
  static void init(const std::string &ice_id, ice::MDS *mds);
  static void init(
    const std::string &ice_id,
    const int metric_id,
    ice::NumericObservedValue *nov);
  static int get_ice_manager_domain_id();
  static char *mds_status_str(const int status);
  static char *metric_id_str(int metric_id);
  static void print_data(const ice::MDS &mds);
  static void print_data(const ice::NumericObservedValue &nov);
};

#endif
