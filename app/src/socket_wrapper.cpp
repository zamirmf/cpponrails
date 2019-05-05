
#include "socket_wrapper.hpp"
#include "exception.hpp"

/*virtual*/ int SocketWrapper::SocketNative(int ai_family, int socktype, int ai_protocol) const{
  int socket_descriptor = socket(ai_family, socktype, ai_protocol);
  if (socket_descriptor == -1) throw Exception("Failed to create socket");
  return socket_descriptor;
}

/*virtual*/ int SocketWrapper::BindNative(int socketDescriptor, const sockaddr* ai_addr, socklen_t ai_addrlen) const{
  int returnValue = bind(socketDescriptor, ai_addr, ai_addrlen);
  if (returnValue == -1) throw Exception("Failed to bind a name to a socket");
  return returnValue;
}
/*virtual*/ int SocketWrapper::ListenNative(int socketDescriptor, int queueLength) const{
  int returnValue = listen(socketDescriptor, queueLength);
  if (returnValue == -1) throw Exception("Failed to listen for connection");
  return returnValue;
}

/*virtual*/ int SocketWrapper::CloseNative(int socketDescriptor) const{
  int returnValue = close(socketDescriptor);
  if (returnValue == -1) throw Exception("Failed to close the socket");
  return returnValue;
}

/*virtual*/ int SocketWrapper::AcceptNative(int socketDescriptor, sockaddr* ai_addr, socklen_t* ai_addrlen)const{
  int returnValue = accept(socketDescriptor, ai_addr, ai_addrlen);
  if (returnValue == -1) throw Exception("Failed to accept a connection");
  return returnValue;
}