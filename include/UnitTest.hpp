#ifndef UNIT_TEST_HPP
#define UNIT_TEST_HPP

#include "CustomAllocator.hpp"

class UnitTest {
    public:
        UnitTest() { }
        ~UnitTest() { }
        void testPoolAllocation(CustomAllocator* allocator, const size_t size);
        void testFreeListAllocation(CustomAllocator* allocator);
};
#endif
