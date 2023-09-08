#ifndef DICES_LOGGER_H
#define DICES_LOGGER_H

#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/stringhelper.h>
#include <string>

class DicesLogger
{
public:
    DicesLogger();
    ~DicesLogger() = default;

    DicesLogger(const DicesLogger &other) = delete;
    DicesLogger & operator =(const DicesLogger &other) = delete;

    static DicesLogger *get_instance();

    log4cplus::Logger get_logger();
    log4cplus::Logger get_logger(const std::string &name);

protected:
    struct impl;
    std::unique_ptr<impl> _pimpl;
};

#endif // LOGGER_H
