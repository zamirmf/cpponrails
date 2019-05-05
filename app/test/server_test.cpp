#include "gtest/gtest.h"
#include "src/server.hpp"
#include "src/log.hpp"

class ServerTest : public testing::Test {
  protected:
    void SetUp(){
      std::ofstream file();
      typed_string sample("./log/servertestfile.log");
      Log& log = Log::GetInstance();
      log.SetFilename(sample);
    }
    void TearDown(){
      typed_string sample("./log/log.log");
      Log& log = Log::GetInstance();
      log.SetFilename(sample);
    }
};

// TEST_F(ServerTest, SetStatusToZero){
  // Server server();
  // EXPECT_EQ(0, network.status);
  // CHECK LOG
// }