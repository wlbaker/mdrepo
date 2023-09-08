#ifndef ICE_DOMAIN_READER_SRC_RETURN_CODES_H_
#define ICE_DOMAIN_READER_SRC_RETURN_CODES_H_

#include <string>

enum class DicesRcICEDomainReader
{
  OK = 0,
  FAIL
};

class DicesRcICEDomainReaderStatusMessage
{
 public:

  const static std::string DicesRcICEDomainReaderToString(const DicesRcICEDomainReader error_code)
  {
    std::string error_message;

    switch (error_code)
    {
      case DicesRcICEDomainReader::OK:
        error_message = "Ok";
        break;
      case DicesRcICEDomainReader::FAIL:
        error_message = "Fail";
        break;

      default: // should not be reached
        error_message = "Unknown error code";
        break;
    }

    return error_message;
  }

 private:
  // Disallow use of implicitly generated member functions:
  DicesRcICEDomainReaderStatusMessage(const DicesRcICEDomainReaderStatusMessage &other);
  DicesRcICEDomainReaderStatusMessage &operator=(const DicesRcICEDomainReaderStatusMessage &other);
};

#endif
