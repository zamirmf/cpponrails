#ifndef MEMORY_WRAPPER_HPP
#define MEMORY_WRAPPER_HPP

#include <cstdlib>

class MemoryWrapper{
  public:
    virtual void* MallocNative(size_t size) const;
    virtual void* MemcpyNative(void* dest, const void* src, size_t size) const;
};

#endif