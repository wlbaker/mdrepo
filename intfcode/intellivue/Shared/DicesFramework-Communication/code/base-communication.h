/**
 * @file base_comm.h
 * @brief Declares a base communication class.
 * @author Michael Szwaja
 */
//=============================================================================
#ifndef BASE_COMMUNICATION_H_
#define	BASE_COMMUNICATION_H_

#include <unistd.h>
#include <cstdint>

enum class DicesRcBaseComm;

class BaseComm
{
public:
    BaseComm() = default;
    virtual ~BaseComm() = default;

    BaseComm(const BaseComm &orig) = delete;
    BaseComm & operator =(const BaseComm &orig) = delete;

    // METHODS
    virtual DicesRcBaseComm Open() = 0;
    virtual DicesRcBaseComm Close() = 0;
    virtual DicesRcBaseComm Send(const uint8_t *buffer, const size_t buffer_size) = 0;
    virtual DicesRcBaseComm Read(uint8_t *buffer, const size_t buffer_size, ssize_t *bytes_transferred) = 0;
    virtual DicesRcBaseComm Flush();
};

#endif // BASE_COMMUNICATION_H_
