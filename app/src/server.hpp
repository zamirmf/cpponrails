#ifndef SERVER_HPP
#define SERVER_HPP

#include "src/log.hpp"

class Server{
  public:
    Server(const typed_string& port, int protocol, int queueLength);
    void Initialize(const typed_string& port, int protocol, int queueLength);
    virtual ~Server();
};

#endif