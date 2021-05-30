#include <cassert>
#include <cstring>
#include <cstdlib>
#include <numeric>
#include <iostream>
#include "PoolAllocator.hpp"


PoolAllocator::PoolAllocator(const size_t totalSize, const size_t chunkSize, 
        const bool printInfo) : CustomAllocator(totalSize, printInfo), 
                          m_chunkSize(chunkSize), m_freeChunkIdx(0)
{
    const size_t numChunks = m_totalSize/m_chunkSize;
    m_startPtr = ::malloc(totalSize+numChunks*sizeof(size_t));
    m_chunksList = (size_t*)((size_t)m_startPtr + totalSize);
    // create a stack with all free positions
    iota(m_chunksList, m_chunksList+numChunks, (size_t) m_startPtr);
}

PoolAllocator::~PoolAllocator() {
    ::free(m_startPtr);
    m_startPtr = nullptr;
}

void* PoolAllocator::malloc(const size_t size) {
    // size should be equal to chunk size
    assert(size == m_chunkSize);
    size_t freeAddr = m_chunksList[m_freeChunkIdx++];
    ++m_used;
    m_peak = max(m_used, m_peak);
    if (m_printInfo) {
        cout << "Allocated " << freeAddr << endl;
    }
    return (void*) freeAddr;
}

void PoolAllocator::free(void* ptr) {
    // size should be equal to chunk size
    memset(ptr,0,m_chunkSize); // clear memory (sometimes required)
    --m_used;
    m_chunksList[--m_freeChunkIdx] = (size_t) ptr;
    if (m_printInfo) {
        cout << "Freed " << (size_t) ptr << endl;
    }
}
