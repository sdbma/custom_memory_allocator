#include <iostream>
#include <vector>

#include "PoolAllocator.hpp"
#include "FreeListAllocator.hpp"
#include "UnitTest.hpp"

int main(int argc, char** argv) {
    CustomAllocator* poolAllocator = new PoolAllocator(100*4096, 4096, true);
    UnitTest unitTest;
    unitTest.testPoolAllocation(poolAllocator, 4096);
    CustomAllocator* freeListAllocator = new FreeListAllocator(200*4096, FreeListAllocator::BEST, true);
    unitTest.testFreeListAllocation(freeListAllocator);
    return 0;
}
