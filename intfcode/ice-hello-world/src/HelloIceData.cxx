/**
 * @file  HelloIceData.cxx
 * @brief Initialize common data objects.
 */
//=============================================================================
#include <chrono>
#include "mds.h"
#include "numeric.h"
#include "HelloIceData.h"

enum dimobjecthandles
{
  h_dimobj_ice_manager = 10,
  h_dimobj_mds = 100,
  h_dimobj_num_sat_o2 = 300,
  h_dimobj_num_pleth = 301,
  h_dimobj_num_pr = 302,
};

//=============================================================================
int HelloIceData::get_ice_manager_domain_id()
  { return ice::DDS_DOMAIN_ID_MANAGER; }

//=============================================================================
void HelloIceData::gettimeofday_utc(ice::Timespec *timespec)
{
  if (timespec)
  {
    std::chrono::system_clock::time_point tepoch;
    std::chrono::system_clock::duration delta =
      std::chrono::system_clock::now() - tepoch;
    std::chrono::nanoseconds ns =
      std::chrono::duration_cast<std::chrono::nanoseconds>(delta);

    timespec->seconds = static_cast<long>(ns.count() / std::giga::num);
    timespec->nanoseconds = static_cast<long>(ns.count() % std::giga::num);
  }
}

char *HelloIceData::mds_status_str(const int status)
{
  char *ss {0};

  switch(status)
  {
  case ice::disconnected: ss = "disconnected"; break;
  case ice::unassociated: ss = "unassociated"; break;
  case ice::associating: ss = "associating"; break;
  case ice::associated: ss = "associated"; break;
  case ice::configuring: ss = "configuring"; break;
  case ice::configured: ss = "configured"; break;
  case ice::operating: ss = "operating"; break;
  case ice::re_initializing: ss = "re_initializing"; break;
  case ice::terminating: ss = "terminating"; break;
  case ice::disassociating: ss = "disassociating"; break;
  case ice::disassociated: ss = "disassociated"; break;
  case ice::re_configuring: ss = "re_configuring"; break;
  default: ss = "UNKNOWN"; break;
  }
  return ss;
}

char *HelloIceData::metric_id_str(const int metric_id)
{
  char *ss {0};

  switch(metric_id)
  {
  case MDC_PULS_OXIM_SAT_O2:    ss = "MDC_PULS_OXIM_SAT_O2"; break;
  case MDC_PULS_OXIM_PLETH:     ss = "MDC_PULS_OXIM_PLETH"; break;
  case MDC_PULS_OXIM_PULS_RATE: ss = "MDC_PULS_OXIM_PULS_RATE"; break;
  default: ss = "UNKNOWN"; break;
  }
  return ss;
}

void HelloIceData::init(
  const std::string &ice_id,
  ice::MDS *mds)
{
  if (!mds) return;

  strncpy(mds->ice_id, ice_id.c_str(), ice::MAX_LEN_ICE_ID);
  mds->handle = h_dimobj_mds;
  mds->parent_handle = h_dimobj_ice_manager;
  mds->mds_status = ice::unassociated;
  gettimeofday_utc(&mds->source_timestamp);
}

void HelloIceData::init(
  const std::string &ice_id,
  const int metric_id,
  ice::NumericObservedValue *nov)
{
  if (!nov) return;

  strncpy(nov->ice_id, ice_id.c_str(), ice::MAX_LEN_ICE_ID);
  nov->nu_observed_value.metric_id = metric_id;
  switch(metric_id)
  {
  case MDC_PULS_OXIM_SAT_O2:    nov->handle = h_dimobj_num_sat_o2; break;
  case MDC_PULS_OXIM_PLETH:     nov->handle = h_dimobj_num_pleth; break;
  case MDC_PULS_OXIM_PULS_RATE: nov->handle = h_dimobj_num_pr; break;
  default: nov->handle = -1; break;
  }
  nov->parent_handle = h_dimobj_mds;
  gettimeofday_utc(&nov->source_timestamp);
}

void HelloIceData::print_data(const ice::MDS &mds)
{
  printf(
    "  ice id:           %s\n"
    "  mds status:       %d\t%s\n"
    "  source timestamp: %d.%09d seconds UTC since epoch\n",
    mds.ice_id,
    static_cast<int>(mds.mds_status),
    HelloIceData::mds_status_str(mds.mds_status),
    mds.source_timestamp.seconds,
    mds.source_timestamp.nanoseconds);
}

void HelloIceData::print_data(const ice::NumericObservedValue &nov)
{
  printf(
    "  ice id:           %s\n"
    "  metric id:        %u\t%s\n"
    "  value:            %.2f\n"
    "  source timestamp: %d.%09d seconds UTC since epoch\n",
    nov.ice_id,
    static_cast<unsigned int>(nov.nu_observed_value.metric_id),
    HelloIceData::metric_id_str(nov.nu_observed_value.metric_id),
    static_cast<ice::FLOATType>(nov.nu_observed_value.value),
    nov.source_timestamp.seconds,
    nov.source_timestamp.nanoseconds);
}
