#ifndef LOGGER_SRC_RETURN_CODES_H_
#define LOGGER_SRC_RETURN_CODES_H_

#include <string>

enum class DicesRcLogger
{
    OK = 0,
    FAIL,

    INIT_LOGGER_FAILURE,
};

struct DicesRcLoggerStatusMessage
{
    DicesRcLoggerStatusMessage(const DicesRcLoggerStatusMessage &other) = delete;
    DicesRcLoggerStatusMessage &operator=(const DicesRcLoggerStatusMessage &other) = delete;

    const static std::string DicesRcLoggerToString(const DicesRcLogger error_code)
    {
        std::string error_message;

        switch (error_code)
        {
        case DicesRcLogger::OK:
            error_message = "Ok";
            break;
        case DicesRcLogger::FAIL:
            error_message = "Fail";
            break;

        case DicesRcLogger::INIT_LOGGER_FAILURE:
            error_message = "Failed to initialize the root logger";
            break;
        default: // should not be reached
            error_message = "Unknown error code";
        }

        return error_message;
    }
};

#endif
