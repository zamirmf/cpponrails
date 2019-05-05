#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "src/socket.hpp"
#include "src/log.hpp"
#include <arpa/inet.h>

using ::testing::Return;
using ::testing::_;

class SocketTest : public testing::Test {
  protected:
    void SetUp(){
      std::ofstream file();
      typed_string sample("./log/sockettestfile.log");
      Log& log = Log::GetInstance();
      log.SetFilename(sample);
    }
    void TearDown(){
      typed_string sample("./log/log.log");
      Log& log = Log::GetInstance();
      log.SetFilename(sample);
    }
};

class MockSocket : public Socket {
 public:
  MockSocket(socklen_t addrlen, int socktype, int family, int protocol): Socket(addrlen, socktype, family, protocol){};
  void* Addr() const{return this->addr;}
  size_t AddrLen() const{return this->addrlen;}
  int SocketDescriptor() const{return this->socketDescriptor;}
  MOCK_CONST_METHOD3(BindNative, int(int,const sockaddr*,socklen_t));
  MOCK_CONST_METHOD2(ListenNative, int(int,int));
  MOCK_CONST_METHOD3(AcceptNative, int(int,sockaddr*,socklen_t*));
  MOCK_CONST_METHOD1(MallocNative, void*(size_t));
  MOCK_CONST_METHOD3(MemcpyNative, void*(void*,const void*, size_t));
  MOCK_CONST_METHOD3(SocketNative, int(int,int,int));
};

// Constructor
TEST_F(SocketTest, SetsMemberVariables){
  MockSocket socket(INET_ADDRSTRLEN, SOCK_DGRAM, AF_INET, IPPROTO_TCP);
  EXPECT_EQ(socket.Addr(),nullptr);
  EXPECT_EQ(socket.AddrLen(),INET_ADDRSTRLEN);
  EXPECT_TRUE(Log::GetInstance().Last().empty());
}

//Initialize
TEST_F(SocketTest, InitializeWithoutSocketDescriptor){
  void* sample_ptr = (void*)1;
  int sample_socket_descriptor = 2;
  MockSocket socket(INET_ADDRSTRLEN, SOCK_DGRAM, AF_INET, IPPROTO_TCP);
  EXPECT_CALL(socket, MallocNative(INET_ADDRSTRLEN)).WillOnce(Return(sample_ptr));
  EXPECT_CALL(socket, MemcpyNative(sample_ptr,_,INET_ADDRSTRLEN)).Times(1);
  EXPECT_CALL(socket,SocketNative(AF_INET,SOCK_DGRAM,IPPROTO_TCP)).WillOnce(Return(sample_socket_descriptor));
  EXPECT_TRUE(socket.Initialize(sample_ptr));
  EXPECT_EQ(socket.Addr(),sample_ptr);
  EXPECT_EQ(socket.SocketDescriptor(),sample_socket_descriptor);
  EXPECT_TRUE(Log::GetInstance().Last().empty());
}

TEST_F(SocketTest, InitializeWithSocketDescriptor){
  void* sample_ptr = (void*)1;
  int sample_socket_descriptor = 2;
  MockSocket socket(INET_ADDRSTRLEN, SOCK_DGRAM, AF_INET, IPPROTO_TCP);
  EXPECT_CALL(socket, MallocNative(INET_ADDRSTRLEN)).WillOnce(Return(sample_ptr));
  EXPECT_CALL(socket, MemcpyNative(sample_ptr,_,INET_ADDRSTRLEN)).Times(1);
  EXPECT_CALL(socket,SocketNative(AF_INET,SOCK_DGRAM,IPPROTO_TCP)).Times(0);
  EXPECT_TRUE(socket.Initialize(sample_ptr, sample_socket_descriptor));
  EXPECT_EQ(socket.Addr(),sample_ptr);
  EXPECT_EQ(socket.SocketDescriptor(),sample_socket_descriptor);
  EXPECT_TRUE(Log::GetInstance().Last().empty());
}

TEST_F(SocketTest, FailsWithoutSocketDescriptor){
  void* sample_ptr = (void*)1;
  int failed_socket_descriptor = -1;
  MockSocket socket(INET_ADDRSTRLEN, SOCK_DGRAM, AF_INET, IPPROTO_TCP);
  EXPECT_CALL(socket, MallocNative(INET_ADDRSTRLEN)).WillOnce(Return(sample_ptr));
  EXPECT_CALL(socket, MemcpyNative(sample_ptr,_,INET_ADDRSTRLEN)).Times(1);
  EXPECT_CALL(socket,SocketNative(AF_INET,SOCK_DGRAM,IPPROTO_TCP)).WillOnce(Return(failed_socket_descriptor));
  EXPECT_FALSE(socket.Initialize(sample_ptr));
  EXPECT_EQ(socket.Addr(),sample_ptr);
  EXPECT_EQ(socket.SocketDescriptor(),failed_socket_descriptor);
  EXPECT_FALSE(Log::GetInstance().Last().empty());
}

//Bind
TEST_F(SocketTest, ReturnsTrueWhenBindSucceed){
  int valid_response = 0;
  MockSocket socket(INET_ADDRSTRLEN, SOCK_DGRAM, AF_INET, IPPROTO_TCP);
  EXPECT_CALL(socket, BindNative(_,_,INET_ADDRSTRLEN)).WillOnce(Return(valid_response));
  EXPECT_TRUE(socket.Bind());
  EXPECT_TRUE(Log::GetInstance().Last().empty());
}

TEST_F(SocketTest, ReturnsFalseWhenBindFails){
  int invalid_response = -1;
  MockSocket socket(INET_ADDRSTRLEN, SOCK_DGRAM, AF_INET, IPPROTO_TCP);
  EXPECT_CALL(socket, BindNative(_,_,INET_ADDRSTRLEN)).WillOnce(Return(invalid_response));
  EXPECT_FALSE(socket.Bind());
  EXPECT_FALSE(Log::GetInstance().Last().empty());
}

//Listen
TEST_F(SocketTest, ReturnsTrueWhenListenSucceed){
  int valid_response = 0;
  int queue_length = 2;
  MockSocket socket(INET_ADDRSTRLEN, SOCK_DGRAM, AF_INET, IPPROTO_TCP);
  EXPECT_CALL(socket, ListenNative(_,queue_length)).WillOnce(Return(valid_response));
  EXPECT_TRUE(socket.Listen(queue_length));
  EXPECT_TRUE(Log::GetInstance().Last().empty());
}

TEST_F(SocketTest, ReturnsFalseWhenListenFails){
  int invalid_response = -1;
  int queue_length = 2;
  MockSocket socket(INET_ADDRSTRLEN, SOCK_DGRAM, AF_INET, IPPROTO_TCP);
  EXPECT_CALL(socket, ListenNative(_,queue_length)).WillOnce(Return(invalid_response));
  EXPECT_FALSE(socket.Listen(queue_length));
  EXPECT_FALSE(Log::GetInstance().Last().empty());
}

//Accept
TEST_F(SocketTest, ReturnsTrueWhenSucceed){
  int valid_response = 0;
  MockSocket socket(INET_ADDRSTRLEN, SOCK_DGRAM, AF_INET, IPPROTO_TCP);
  EXPECT_CALL(socket, AcceptNative(_,_,_)).WillOnce(Return(valid_response));
  EXPECT_TRUE(socket.Accept());
  EXPECT_TRUE(Log::GetInstance().Last().empty());
}

TEST_F(SocketTest, DoesntLogErrorMessage){
  int invalid_response = -1;
  MockSocket socket(INET_ADDRSTRLEN, SOCK_DGRAM, AF_INET, IPPROTO_TCP);
  EXPECT_CALL(socket, AcceptNative(_,_,_)).WillOnce(Return(invalid_response));
  EXPECT_FALSE(socket.Accept());
  EXPECT_FALSE(Log::GetInstance().Last().empty());
}