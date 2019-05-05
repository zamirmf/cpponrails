#include "network_address_wrapper.hpp"
#include "exception.hpp"

/*virtual*/ int NetworkAddressWrapper::GetAddrInfoNative(const char* ip, const char* port, const addrinfo* settings, addrinfo** availableAddresses) const{
  int result = getaddrinfo(ip, port, settings, availableAddresses);
  if (result) throw Exception("Failed to find available network addresses");
  return result;
}