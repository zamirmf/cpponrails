#include "gtest/gtest.h"
#include "src/memory_wrapper.hpp"
#include "src/exception.hpp"

#include <climits>

class MemoryWrapperTest : public testing::Test {
  public:
    MemoryWrapper memoryWrapper;
};

//MallocNative
TEST_F(MemoryWrapperTest, NegativeSize){
  EXPECT_THROW(memoryWrapper.MallocNative(-1),Exception);
}

TEST_F(MemoryWrapperTest, OutofBoundsSize){
  EXPECT_THROW(memoryWrapper.MallocNative(ULLONG_MAX),Exception);
}

TEST_F(MemoryWrapperTest, ValidSize){
  EXPECT_NO_THROW({
    void* ptr = memoryWrapper.MallocNative(INT_MAX/2);
    EXPECT_NE(ptr,nullptr);
    free(ptr);
  });
}

//MemcpyNative
TEST_F(MemoryWrapperTest, SizeMismatch){
  int sample[] = {1, 2, 3, 4};
  size_t valid_size = sizeof(sample);
  int destine[] = {0, 0};

  EXPECT_THROW(memoryWrapper.MemcpyNative(destine, sample, valid_size), Exception);
}

TEST_F(MemoryWrapperTest, ValidParams){
  int sample[] = {1, 2, 3, 4};
  size_t valid_size = sizeof(sample);
  int destine[] = {0, 0, 0, 0};

  EXPECT_NO_THROW(memoryWrapper.MemcpyNative(destine, sample, valid_size));

  for(int i=0; i<4;i++){
    EXPECT_EQ(sample[i], destine[i]);
    EXPECT_EQ(sample[i], i+1);
  }
}