#include "gtest/gtest.h"
#include "src/socket_wrapper.hpp"
#include "src/exception.hpp"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

class SocketWrapperTest : public testing::Test {
  protected:
    int invalid_result;
    addrinfo hints;
    addrinfo *res;
    SocketWrapper socket_wrapper;
    void SetUp(){
      this->invalid_result = -1;
      
      memset(&hints, 0, sizeof hints);
      hints.ai_family = AF_UNSPEC;
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_flags = AI_PASSIVE;
      getaddrinfo(NULL, "3490", &hints, &res);
    }
};

//SocketNative
TEST_F(SocketWrapperTest, ReturnsInvalidDescriptor){
  EXPECT_THROW(socket_wrapper.SocketNative(AF_INET, SOCK_STREAM, IPPROTO_UDP), Exception);
}

TEST_F(SocketWrapperTest, ReturnsValidDescriptor){
  int descriptor;

  EXPECT_NO_THROW({
    descriptor = socket_wrapper.SocketNative(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  });

  EXPECT_NE(descriptor, invalid_result);
  int result = socket_wrapper.CloseNative(descriptor);
  EXPECT_NE(result, invalid_result);
}

//BindNative
TEST_F(SocketWrapperTest, ReturnZeroForBindingSucceeded){
  int descriptor = socket_wrapper.SocketNative(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  int result;
  EXPECT_NO_THROW({
    result = socket_wrapper.BindNative(descriptor, res->ai_addr, res->ai_addrlen);
    socket_wrapper.CloseNative(descriptor);
  });

  EXPECT_EQ(result, 0);
}

TEST_F(SocketWrapperTest, ThrowsExceptionWhenFailedToBind){
  int descriptor = socket_wrapper.SocketNative(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  int result;
  EXPECT_NO_THROW({
    result = socket_wrapper.BindNative(descriptor, res->ai_addr, res->ai_addrlen);
    socket_wrapper.CloseNative(descriptor);
  });
  EXPECT_EQ(result, 0);
  EXPECT_THROW({
    socket_wrapper.BindNative(descriptor, res->ai_addr, res->ai_addrlen);
  }, Exception);

}

//ListenNative
TEST_F(SocketWrapperTest,ReturnZeroWhenListenSucceeded){
  int descriptor = socket_wrapper.SocketNative(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  int result;
  EXPECT_NO_THROW({
    result = socket_wrapper.ListenNative(descriptor, 100);
    socket_wrapper.CloseNative(descriptor);
  });
  EXPECT_EQ(result, 0);
}

TEST_F(SocketWrapperTest,ThrowExpectionWhenListenFails){
  int descriptor = -1;
  EXPECT_THROW({
    socket_wrapper.ListenNative(descriptor, 100);
    socket_wrapper.CloseNative(descriptor);
  }, Exception);
}

//CloseNative
TEST_F(SocketWrapperTest, ReturnsZeroWhenCloseSucceeds){
  int descriptor = socket_wrapper.SocketNative(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  int result;
  EXPECT_NO_THROW({
    result = socket_wrapper.CloseNative(descriptor);
  });
  EXPECT_EQ(result, 0);
}

TEST_F(SocketWrapperTest, ThrowExceptionWhenCloseFails){
  int descriptor = -1;
  EXPECT_THROW({
    socket_wrapper.CloseNative(descriptor);
  },Exception);
}


//AcceptNative
TEST_F(SocketWrapperTest, ReturnsEAGAINWhenAcceptSucceeds){
  int descriptor = socket_wrapper.SocketNative(AF_INET, SOCK_STREAM | O_NONBLOCK, IPPROTO_TCP);
  socket_wrapper.ListenNative(descriptor, 100);
  sockaddr_storage addr;
  socklen_t addrlen;
  EXPECT_THROW({
    socket_wrapper.AcceptNative(descriptor, (sockaddr*)&addr, &addrlen);
    socket_wrapper.CloseNative(descriptor);
  },Exception);
  EXPECT_EQ(errno, EAGAIN);
}

TEST_F(SocketWrapperTest, ThrowExceptionWhenAcceptFails){
  int descriptor = socket_wrapper.SocketNative(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  sockaddr addr;
  socklen_t addrlen;
  EXPECT_THROW({
    socket_wrapper.AcceptNative(descriptor, &addr, &addrlen);
    socket_wrapper.CloseNative(descriptor);
  },Exception);
  EXPECT_NE(errno, EAGAIN);
}