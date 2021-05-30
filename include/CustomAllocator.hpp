#ifndef CUSTOM_ALLOCATOR_HPP_
#define CUSTOM_ALLOCATOR_HPP_

#include <cstddef>

using namespace std;

class CustomAllocator {
    protected:
        const size_t m_totalSize; 
        size_t m_used, m_peak;
        const bool m_printInfo;
    public:
        CustomAllocator(const size_t totalSize, const bool printInfo = false) : m_totalSize(totalSize), 
            m_used(0), m_peak(0), m_printInfo(printInfo) {}
        virtual ~CustomAllocator() {}
        virtual void* malloc(const size_t size) = 0;
        virtual void  free(void* ptr) = 0;
        virtual size_t NumPeakMemory() { return m_peak; };
        virtual size_t NumUsedMemory() { return m_used; };
};

#endif
