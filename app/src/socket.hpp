#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "src/socket_wrapper.hpp"
#include "src/memory_wrapper.hpp"

class Socket: protected SocketWrapper, protected MemoryWrapper{
  protected:
    int socketDescriptor;
    void* addr; 
    socklen_t addrlen;
    int socktype;
    int family;
    int protocol;
  public:
    Socket(socklen_t addrlen, int socktype, int ai_family, int ai_protocol);
    ~Socket();
    bool Accept();
    bool Listen(int queueLength) const;
    bool Bind() const;
    bool Initialize(void* addr, int socketDescriptor = 0);
};

#endif