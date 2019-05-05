#include "gtest/gtest.h"
#include "src/network_address_wrapper.hpp"
#include "src/exception.hpp"


class NetworkAddressWrapperTest : public testing::Test {
  protected:
    addrinfo settings;
    addrinfo* availableAddresses;
    NetworkAddressWrapper network_address_wrapper;
    void SetUp(){
      memset(&this->settings, 0, sizeof this->settings);
      this->settings.ai_family = AF_UNSPEC;
      this->settings.ai_socktype = SOCK_STREAM;
      this->settings.ai_flags = AI_PASSIVE;
    }
};

//GetAddrInfoNative
TEST_F(NetworkAddressWrapperTest, RetunsZeroWhenSucceeded){
  int result;
  EXPECT_NO_THROW({
    result = this->network_address_wrapper.GetAddrInfoNative(NULL, "3490", &this->settings, &this->availableAddresses);
  });
  EXPECT_EQ(result,0);
}

TEST_F(NetworkAddressWrapperTest, ThrowsExceptionsWhenFails){
  EXPECT_THROW(this->network_address_wrapper.GetAddrInfoNative(NULL, NULL, &this->settings, &this->availableAddresses), Exception);
}