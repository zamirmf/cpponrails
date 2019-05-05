#include "memory_wrapper.hpp"
#include "exception.hpp"

#include <string.h>

/*virtual*/ void* MemoryWrapper::MallocNative(size_t size) const{
  if (size >= SIZE_MAX) throw Exception("Invalid size to be allocated");
  void* ptr = malloc(size);
  if (!ptr) throw Exception("Failed to allocate");
  return ptr;
}

/*virtual*/ void* MemoryWrapper::MemcpyNative(void* dest, const void* src, size_t size) const{
  void* ptr = memcpy(dest,src,size);
  if (memcmp(src,dest,size)) throw Exception("Failed to copy");
  return ptr;
}