/* 
 * File:   DicesCmdLnArgParser.cpp
 * Author: rfries
 *
 * Created on June 9, 2014, 8:38 AM
 */

#include <string.h>
#include <limits.h>
#include "../cmd-ln-arg-parser.h"
#include "common.h"

static const int kDefaultDomainId = ice::DDS_DOMAIN_ID_MANAGER;

struct DicesCmdLnArgParser::impl
{
  std::map<std::string, std::string> _options;

  impl() = default;

  ~impl() = default;

  DicesRcCmdLnArgParser Parse(int argc, char** argv)
  {
    static const char* sfn = "DicesCmdLnArgParser::Parse()";
    _options.clear(); // fresh start; clean slate
    std::string option;

    if (!argv)
    {
      LOG4CPLUS_ERROR(log4cplus::Logger::getRoot(), sfn << " Function argument argv is a null pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    // split her up
    for(int i = 1; i < argc; ++i)
    {
      // if we have an option
      if (argv[i][0] == '-')
      {
        // if option is blank
        if (strlen(argv[i]) < 2)
        {
          LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), "missing option " << i << " after '-'");
        }
        // we have a legit option, save it
        else
        {
          // note that this this could eat up a lot time if the map starts getting full
          // a hash table might work better
          if (_options.find(argv[i]) != _options.end())
          {
            // there should be no repeats in options; log if there is
            LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "option " << i << ": " << argv[i] <<
                           " already exists; original corresponding argument might get written over");
          }
          else
          {
            option = std::string(argv[i]);
            // create place holder in map - sets value to default string constructor
            _options[option];
          }
        }
      }
      else
      {
        // there was no option before a given argument
        // specifically: the first string put into the system is a non-option
        // or the given string already has an option associated with it
        if (_options.empty() || _options.find(option) == _options.end())
        {
          LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), "missing -option before given argument " << argv[i]);
        }
        // we have a legit argument, fit it to the corresponding option
        else
        {
          _options[option] = std::string(argv[i]);
        }
      }
    }

    return DicesRcCmdLnArgParser::OK;
  }

  DicesRcCmdLnArgParser GetDomainId(int* domain_id)
  {
    if (!domain_id)
    {
      LOG4CPLUS_DEBUG(log4cplus::Logger::getRoot(), "function argument domain_id is a null pointer.");
      return DicesRcCmdLnArgParser::FUNCTION_ARGUMENT_NULL_POINTER;
    }

    static const char* soption = "-domainId";
    auto domainid_opt = _options.find(soption);
    *domain_id = kDefaultDomainId;

    if (domainid_opt == _options.end())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), soption << " was not found in command line args."
                     << " Using default " << kDefaultDomainId);
      return DicesRcCmdLnArgParser::NO_DOMAIN_ID_OPTION;
    }
    else if (domainid_opt->second.empty())
    {
      LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "no arg provided with " << soption
                     << " in command line args. Using default "
                     << kDefaultDomainId);
      return DicesRcCmdLnArgParser::NO_DOMAIN_ID_ARGUMENT;
    }
    else
    {
      char* endptr = 0;
      long domain_id_value = strtol(domainid_opt->second.c_str(), &endptr, 10);
      if (domain_id_value == LONG_MAX || domain_id_value == LONG_MIN)
      {
        if (errno == ERANGE)
        {
          LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "String value cannot be represented as "
                                                       "long. Using default " << kDefaultDomainId);
          return DicesRcCmdLnArgParser::LONG_LIMIT_EXCEEDED;
        }
      }

      if (domain_id_value > INT_MAX || domain_id_value < INT_MIN)
      {
        LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "Unable to cast domain ID from long to "
                                                     "int. The integer limit was exceeded. Using default "
                       << kDefaultDomainId);
        return DicesRcCmdLnArgParser::INT_LIMIT_EXCEEDED;
      }

      if (!domain_id_value)
      {
        if (domainid_opt->second.c_str() == endptr)
        {
          LOG4CPLUS_WARN(log4cplus::Logger::getRoot(), "strtol error: no valid conversion could "
                                                       "be made. Using default " << kDefaultDomainId);
          return DicesRcCmdLnArgParser::NO_VALID_CONVERSION;
        }
      }

      *domain_id = static_cast<int>(domain_id_value);
      LOG4CPLUS_INFO(log4cplus::Logger::getRoot(), "domain ID being used: " << *domain_id);
      return DicesRcCmdLnArgParser::OK;
    }

    return DicesRcCmdLnArgParser::OK;
  }
};

DicesCmdLnArgParser::DicesCmdLnArgParser()
  :_pimpl(nullptr)
{
  static const char* sfn = "DicesCmdLnArgParser::DicesCmdLnArgParser() ";
  _pimpl = std::unique_ptr<impl>(new (std::nothrow) impl());
  if (!_pimpl)
  {
    LOG4CPLUS_ERROR(log4cplus::Logger::getRoot(), sfn << "Failed to create impl");
    return;
  }
}

DicesCmdLnArgParser::~DicesCmdLnArgParser() 
{
}

std::map<std::string, std::string> DicesCmdLnArgParser::get_options()
{
  return _pimpl->_options;
}

DicesRcCmdLnArgParser DicesCmdLnArgParser::Parse(int argc, char** argv)
{
  return _pimpl->Parse(argc, argv);
}

DicesRcCmdLnArgParser DicesCmdLnArgParser::GetDomainId(int* domain_id)
{
  return _pimpl->GetDomainId(domain_id);
}




