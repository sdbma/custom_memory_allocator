#ifndef POOL_ALLOCATOR_HPP
#define POOL_ALLOCATOR_HPP

#include <vector>
#include "CustomAllocator.hpp"

class PoolAllocator : public CustomAllocator {
protected:
    void* m_startPtr = nullptr;
    size_t m_chunkSize;
    // used a stack to keep track of list of chunks
    size_t* m_chunksList;
    int m_freeChunkIdx;

public:
    PoolAllocator(const size_t totalSize, const size_t chunkSize, const bool printInfo);
    virtual ~PoolAllocator();
    virtual void* malloc(const size_t size);
    virtual void free(void* ptr);
};

#endif
