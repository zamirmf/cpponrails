#ifndef NETWORK_ADDRESS_WRAPPER_HPP
#define NETWORK_ADDRESS_WRAPPER_HPP

#include <netdb.h>

class NetworkAddressWrapper{
  public:
    virtual int GetAddrInfoNative(const char* ip, const char* port, const addrinfo* settings, addrinfo** availableAddresses) const;
};

#endif