#include "gtest/gtest.h"
#include "src/log.hpp"
#include "src/exception.hpp"

#include "fstream"

class LogTest : public testing::Test {
  protected:
    void SetUp(){
      typed_string filename("./log/logtest.log");
      std::ofstream file(filename, std::ios_base::trunc);
      file.close();
      Log::GetInstance().SetFilename(filename);
    }
    void TearDown(){
      typed_string sample("./log/log.log");
      Log::GetInstance().SetFilename(sample);
    }
};
//GetInstance
TEST_F(LogTest, IsSameObject){
  Log& log = Log::GetInstance();
  Log& log2 = Log::GetInstance();
  EXPECT_EQ(&log,&log2);
}

//Constructor
TEST_F(LogTest, HasDefaultFilename){
  Log& log = Log::GetInstance();
  EXPECT_FALSE(log.GetFilename().empty());
}

TEST_F(LogTest, HasNoLastError){
  Log& log = Log::GetInstance();
  EXPECT_TRUE(log.Last().empty());
}

//SetFileName
TEST_F(LogTest, HasCustomFilename){
  Log& log = Log::GetInstance();
  typed_string sample("./testingfile.txt");
  log.SetFilename(sample);
  EXPECT_STREQ(log.GetFilename().c_str(), "./testingfile.txt");
}

//Error & Debug
//with invalid filename
TEST_F(LogTest, WithInvalidFilename){
  Log& log = Log::GetInstance();
  typed_string newName("");
  log.SetFilename(newName);
  EXPECT_THROW(log.Error("error"), Exception);
}
//for strings
TEST_F(LogTest, HasNewErrorString){
  Log& log = Log::GetInstance();
  log.Error("error");
  EXPECT_STREQ(log.Last().c_str(), "Error: error");
}

TEST_F(LogTest, HasNewDebugString){
  Log& log = Log::GetInstance();
  log.Debug("debug");
  EXPECT_STREQ(log.Last().c_str(), "Debug: debug");
}

//for integers
TEST_F(LogTest, HasNewDebugInteger){
  Log& log = Log::GetInstance();
  log.Debug(10);
  EXPECT_STREQ(log.Last().c_str(), "Debug: 10");
}

TEST_F(LogTest, HasNewErrorInteger){
  Log& log = Log::GetInstance();
  log.Error(20);
  EXPECT_STREQ(log.Last().c_str(), "Error: 20");
}

//for float numbers
TEST_F(LogTest, HasNewDebugFloat){
  Log& log = Log::GetInstance();
  log.Debug(1.5f);
  EXPECT_STREQ(log.Last().c_str(), "Debug: 1.5");
}

TEST_F(LogTest, HasNewErrorFloat){
  Log& log = Log::GetInstance();
  log.Error(5.1f);
  EXPECT_STREQ(log.Last().c_str(), "Error: 5.1");
}

//for Null
TEST_F(LogTest, HasNewDebugNULL){
  Log& log = Log::GetInstance();
  log.Debug(NULL);
  EXPECT_STREQ(log.Last().c_str(), "Debug: 0");
}