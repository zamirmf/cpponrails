#include "src/socket.hpp"
#include "src/log.hpp"

Socket::Socket(socklen_t addrlen, int socktype, int family, int protocol): 
  addr(NULL), addrlen(addrlen), socktype(socktype), family(family), protocol(protocol), socketDescriptor(0){}

bool Socket::Initialize(void* addr, int socketDescriptor/* = 0*/){
  this->addr = this->MallocNative(this->addrlen);
  this->MemcpyNative(this->addr,addr, this->addrlen);
  if (socketDescriptor){
    this->socketDescriptor = socketDescriptor;
    return true;
  }
  this->socketDescriptor = this->SocketNative(this->family, this->socktype, this->protocol);
  if (this->socketDescriptor == -1){
    Log::GetInstance().Error("Failed when creating socket");
    return false;
  }
  return true;
}

bool Socket::Bind() const{
  if (this->BindNative(this->socketDescriptor, (sockaddr*)this->addr, this->addrlen) == -1){
    Log::GetInstance().Error("Failed when binding socket");
    return false;
  }
  return true;
}

bool Socket::Listen(int queueLength) const{
  if (this->ListenNative(this->socketDescriptor, queueLength) == -1){
    Log::GetInstance().Error("Failed when listening to the port");
    return false;
  }
  return true;
}

Socket::~Socket(){
  this->CloseNative(this->socketDescriptor);
}

bool Socket::Accept(){
  int socketDescriptor;
  sockaddr_storage ai_addr;
  socklen_t ai_addrlen = sizeof(ai_addr);
  socketDescriptor = this->AcceptNative(this->socketDescriptor, (sockaddr *)&ai_addr, &ai_addrlen);
  if(socketDescriptor == -1){
    Log::GetInstance().Error("Failed when accepting connections");
    return false;
  }
  return true;
}