/**
 * @file dices_hostname.cxx
 *
 * @brief Tool for getting the device ICE ID
 *
 * @author Robert England
 */

#include <cstdint>

std::string GetDeviceIceId()
{
  const size_t max_length = ice::MAX_LEN_ICE_ID;

  // Plus one for null terminator
  char *hostname_c_str = new (std::nothrow) char[max_length + 1]();
  if (!hostname_c_str)
  {
    qCritical() << "Failed to allocate memory for hostname string";
    return "";
  }

  errno = 0;
  if (gethostname(hostname_c_str, max_length))
  {
    qWarning() << "Failed to gethostname() " << strerror(errno);
  }

  hostname_c_str[max_length]= '\0';

  std::string hostname(hostname_c_str);

  delete [] hostname_c_str;
  hostname_c_str = nullptr;

  return hostname;
}
