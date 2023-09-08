/**
 * @file  HelloIceApp.h
 * @brief Hello ICE world: intro to ICE pub/sub programming.
 */
//=============================================================================
#ifndef HELLO_ICE_APP_H_
#define HELLO_ICE_APP_H_

//=============================================================================
class HelloIceApp
{
private:
  // DATA
  long _domain_id;
  bool _run_as_subscriber;  // ... or as publisher
  std::string _statusmsg;

  // NOT IMPLEMENTED
  // Disallow use of implicitly generated member functions:
  HelloIceApp(const HelloIceApp &src);
  HelloIceApp &operator=(const HelloIceApp &rhs);

public:
  // CREATORS
  HelloIceApp();
  ~HelloIceApp();

  // MANIPULATORS
  void CmdLineHelp(
    const char *thisprogramname,
    const int exitprogram);
  int ParseCommandLineArgs(int argc, char* argv[]);
  int RunApp(char *programname);

  // ACCESSORS
  long get_domain_id() const { return _domain_id; }
  std::string get_statusmsg() const { return _statusmsg; }
  bool run_as_subscriber() const { return _run_as_subscriber; }

};

#endif
