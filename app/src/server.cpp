#include "src/server.hpp"
#include "src/socket.hpp"

#include <netdb.h>

Server::Server(const typed_string& port, int protocol, int queueLength){

}

void Server::Initialize(const typed_string& port, int protocol, int queueLength){
  //Main parameters
  const char* node = NULL;
  const char* service = port.c_str();
  addrinfo hints = {};
  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = protocol;

  //Load native ip addresses
  addrinfo* internal_resources;
  int status = getaddrinfo(node, service, &hints, &internal_resources);
  if (status){
    typed_string errorMessage("getaddrinfo failed with: ");
    errorMessage += gai_strerror(status);
    Log::GetInstance().Error(errorMessage);
    return;
  }

  //Store into as a vector of NetworkAddress
  addrinfo* internet_address = internal_resources;
  while(internet_address){
    Socket socket(internet_address->ai_addrlen, internet_address->ai_socktype, internet_address->ai_family, internet_address->ai_protocol);
    socket.Initialize((sockaddr *)&internet_address->ai_addr);
    socket.Bind();
    socket.Listen(queueLength);
    //break the loop if socket is valid
    internet_address = internet_address->ai_next;
  }

  //Free native ip addresses
  freeaddrinfo(internal_resources);
}

//Method to loop into accept creating a new thread to process send and recv

//Method to process send and recv within a thread

Server::~Server(){
  
}