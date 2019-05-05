
#ifndef SOCKET_WRAPPER_HPP
#define SOCKET_WRAPPER_HPP

#include <sys/socket.h>
#include <unistd.h>

class SocketWrapper{
  public:
    virtual int SocketNative(int ai_family, int socktype, int ai_protocol) const;
    virtual int BindNative(int socketDescriptor, const sockaddr* ai_addr, socklen_t ai_addrlen) const;
    virtual int ListenNative(int socketDescriptor, int queueLength) const;
    virtual int CloseNative(int socketDescriptor) const;
    virtual int AcceptNative(int socketDescriptor, sockaddr* ai_addr, socklen_t* ai_addrlen)const;
};

#endif