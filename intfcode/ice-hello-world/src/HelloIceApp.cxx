/**
 * @file  HelloIceApp.cxx
 * @brief Hello ICE world: intro to ICE application DDS pub/sub programming.
 *
 * In pub (publish) mode, this writes to the DDS bus fake medical device data.
 * In sub (subscribe) mode, this reads data from DDS bus and shows it.
 */
//=============================================================================
#ifndef _WIN32
#include <sys/time.h>
#endif
#include <chrono>
#include <thread>
#include <string>
#include "ndds/ndds_cpp.h"
#include "ndds/ndds_namespace_cpp.h"
#include "kbhit_util.h"
#include "DDSTypeWrapper.h"
#include "mdsSupport.h"
#include "MDSWriterInterface.h"
#include "MDSReaderInterface.h"
#include "numericSupport.h"
#include "NumericWriterInterface.h"
#include "NumericReaderInterface.h"
#include "HelloIceData.h"
#include "HelloIceApp.h"
//#include "medicationsSupport.h"

#ifdef _WIN32
#include <Processthreadsapi.h>
static const int _procid = static_cast<int>(GetCurrentProcessId());
#else
#include <sys/types.h>
#include <unistd.h>
static const int _procid = static_cast<int>(getpid());
#endif

#ifdef _WIN32
#define STRNCASECMP _strnicmp
#else
#define STRNCASECMP strncasecmp
#endif
#define IS_OPTION(str, option) (STRNCASECMP(str, option, strlen(str)) == 0)

static const std::chrono::milliseconds _publish_period_milliseconds(5000);
static bool spin_until_or_bail(std::chrono::system_clock::time_point tp);
static int run_sub(HelloIceApp *hiapp);
static int run_pub(HelloIceApp *hiapp);
static void create_ice_id(std::string *ice_id);

//=============================================================================
//=============================================================================
HelloIceApp::HelloIceApp()
  : _domain_id(HelloIceData::get_ice_manager_domain_id()),
    _run_as_subscriber(true)
{
}

HelloIceApp::~HelloIceApp()
{
}

//=============================================================================
/*
 * Print help message.
 * @param [in] thisprogramname The name of the executable (argv[0]).
 * @param [in] exitprogram 0 or 1 value signifies whether or not to close
 * application after help message is printed.
 */
void HelloIceApp::CmdLineHelp(
  const char *thisprogramname,
  const int exitprogram)
{
  const char* smsg =
    "\nUSAGE:\n"
    "  %s [-domainID <id>] [sub | pub]\n"
    "  {} Required\n"
    "  [] Optional\n"
    "  |  Separator between option choices\n"
    "where:\n"
    "  -help            Print help message\n"
    "  -domainId <id>   DDS domain id, default %d\n"
    "  sub              Run this instance as subscriber, default\n"
    "  pub              Run this instance as publisher\n"
    "\n"
    "Brief Description:\n"
    "  Hello world ICE app.\n\n";

  printf(
    smsg,
    thisprogramname,
    HelloIceData::get_ice_manager_domain_id());
  if (exitprogram) exit(0);
}

// Return 0 for success.
int HelloIceApp::ParseCommandLineArgs(int argc, char* argv[])
{
  const static char *sfn = "HelloIceApp::ParseCommandLineArgs";

  // Load command line parameters
  for (int ix = 1; ix < argc; ++ix)
  {
    if (IS_OPTION(argv[ix], "-domainId"))
    {
      if ((ix == (argc - 1)) || *argv[++ix] == '-')
      {
        _statusmsg = "Command argument error: missing <id> after -domainId";
        return 1;
      }
      _domain_id = strtol(argv[ix], 0, 10);
      if ((_domain_id < 0) || (errno == ERANGE))
      {
        _statusmsg =
          "Command argument error: the domain <id> value is out of range";
        return 1;
      }
    }
    else if (IS_OPTION(argv[ix], "pub"))
    {
      _run_as_subscriber = false;
    }
    else if (IS_OPTION(argv[ix], "sub"))
    {
      _run_as_subscriber = true;
    }
    else if (strlen(argv[ix]) > 0)
    {
      _statusmsg = "Command argument error: unrecognized argument";
      return 1;
    }
  }
  return 0;
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

//
// Create a fake ICE ID based on process id
static void create_ice_id(std::string *ice_id)
{
  static const char prefix[] = "D4X-";
  std::stringstream ss;
  ss << prefix << _procid;
  *ice_id = ss.str();
}

//=============================================================================
// Run in subscriber mode. This reads from the data bus MDS and numeric
// observed value samples and write values to the screen.
int run_sub(HelloIceApp *hiapp)
{
  const char *sfn {"HelloIceApp.run_sub"};
  int rc {DDS::RETCODE_OK};
  int istat {0};

  try 
  {
    MDSReaderInterface irmds;
    DdsAutoType<ice::MDS> mds;
    NumericReaderInterface irnumeric;
    DdsAutoType<ice::NumericObservedValue> nov;

    const char *stopic_mds = ice::MDSTopic;
    rc = irmds.Initialize(
      hiapp->get_domain_id(),
      stopic_mds,
      "dices_dim_library",
      "default_profile");
    if (rc != DDS::RETCODE_OK)
    {
      std::stringstream ss;
      ss << sfn
        << ": Failed to Initialize MDSReaderInterface"
        << ", topic " << stopic_mds << " [" << rc << "]";
      throw ss.str();
    }

    const char *stopic_numeric = ice::NumericMeasObservedValueTopic;
     rc = irnumeric.Initialize(
      hiapp->get_domain_id(),
      stopic_numeric,
      "dices_dim_library",
      "default_profile");
    if (rc != DDS::RETCODE_OK)
    {
      std::stringstream ss;
      ss << sfn
        << ": Failed to Initialize NumericReaderInterface"
        << ", topic " << stopic_numeric << " [" << rc << "]";
      throw ss.str();
    }

    int keyboard_char_input {0};

    while(1)
    {
      keyboard_char_input = kbhit_util::kbhit();
      if (keyboard_char_input == kbhit_util::kAsciiEsc)
      {
        std::cout << std::endl << "User requested exit." << std::endl;
        break;
      }

      static const DDS_Duration_t dtimeout {0, 1000 * std::mega::num};

      if (irmds.GetData(dtimeout, &mds))
      {
        printf("\nData sample FROM ice::MDSTopic:\n");
        HelloIceData::print_data(mds);
      }

      if (irnumeric.GetData(dtimeout, &nov))
      {
        printf("\nData sample FROM ice::NumericMeasObservedValueTopic:\n");
        HelloIceData::print_data(nov);
      }
    }
  }
  catch (std::string message)
  {
    std::cout << "Application exception: " << message << std::endl;
    istat = 1;
  }
  TheParticipantFactory->finalize_instance();
  return istat;
}

//=============================================================================
// Run in publisher mode. This simulates a medical device system that
// writes an MDS data object and, periodically, a numeric observed value.
int run_pub(HelloIceApp *hiapp)
{
  const char *sfn = {"HelloIceApp.run_pub"};
  int istat {0};
  int rc {DDS::RETCODE_OK};
  ice::Timespec current_time = {0};
  std::string ice_id;

  try
  {
    MDSWriterInterface iwmds;
    DdsAutoType<ice::MDS> mds;
    NumericWriterInterface iwnumeric;
    DdsAutoType<ice::NumericObservedValue> pulsrate;

    create_ice_id(&ice_id);

    rc = iwmds.Initialize(
      hiapp->get_domain_id(),
      ice::MDSTopic,
      "dices_dim_library",
      "default_profile");
    if (rc != DDS::RETCODE_OK)
    {
      std::stringstream ss;
      ss << sfn
        << ": Failed to Initialize MDSWriterInterface ["
        << rc << "]";
      throw ss.str();
    }

    rc = iwnumeric.Initialize(
      hiapp->get_domain_id(),
      ice::NumericMeasObservedValueTopic,
      "dices_dim_library",
      "default_profile");
    if (rc != DDS::RETCODE_OK)
    {
      std::stringstream ss;
      ss << sfn
        << ": Failed to Initialize NumericWriterInterface ["
        << rc << "]";
      throw ss.str();
    }

    HelloIceData::init(ice_id, &mds);
    HelloIceData::init(ice_id, MDC_PULS_OXIM_PULS_RATE, &pulsrate);

    // Good to go

    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();

    while(1)
    {
      tp += _publish_period_milliseconds;
      if (spin_until_or_bail(tp))
      {
        std::cout << std::endl << "User requested exit." << std::endl;
        break;
      }
      HelloIceData::gettimeofday_utc(&mds.source_timestamp);
      pulsrate.source_timestamp = mds.source_timestamp;

      if (mds.mds_status != ice::operating)
      {
        // The medical device is not yet in operating state.

        if (mds.mds_status == ice::associated)    mds.mds_status = ice::operating;
        if (mds.mds_status == ice::associating)   mds.mds_status = ice::associated;
        if (mds.mds_status == ice::unassociated)  mds.mds_status = ice::associating;

        printf("\nPublish Medical Device System (MDS) data\n");
        HelloIceData::print_data(mds);

        rc = iwmds.Write(mds);
        if (rc != DDS::RETCODE_OK)
        {
          std::stringstream ss;
          ss << sfn
            << ": Failed to MDSWriterInterface::Write [" << rc << "]";
          throw ss.str();
        }
        continue;
      }

      // Medical device is operating. Publish some physio data.

      printf("\nPublish numeric data\n");
      pulsrate.nu_observed_value.value =
        static_cast<ice::FLOATType>((time(0) % 50) + 50);
      HelloIceData::print_data(pulsrate);

      rc = iwnumeric.Write(pulsrate);
      if (rc != DDS::RETCODE_OK)
      {
        std::stringstream ss;
        ss << sfn
          << ": Failed to NumericWriterInterface::Write [" << rc << "]";
        throw ss.str();
      }
    }
  }
  catch (std::string message)
  {
    std::cout << "Application exception: " << message << std::endl;
    istat = 1;
  }
  TheParticipantFactory->finalize_instance();
  return istat;
}

int HelloIceApp::RunApp(char *programname)
{
  std::string suborpub = _run_as_subscriber ? "subscriber" : "publisher";

  std::cout << std::endl << programname;
  std::cout << std::endl << "  Running as: " << suborpub;
  std::cout << std::endl << "  DDS domain: " << _domain_id;
  std::cout << std::endl << std::endl;
  std::cout << "Press Esc to end.";
  std::cout << std::endl << std::endl;
  if (_run_as_subscriber)  std::cout << "Ready to read samples ...";
  if (!_run_as_subscriber) std::cout << "Begin writing samples ...";
  std::cout << std::endl << std::endl;

  int istat = _run_as_subscriber ? run_sub(this) : run_pub(this);
  return istat;
}
