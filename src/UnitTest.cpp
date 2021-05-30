#include "UnitTest.hpp"
#include <array>
#include <iostream>

void UnitTest::testPoolAllocation(CustomAllocator* allocator, const size_t size) {
    cout << "Pool Allocation Test (size: " << size <<")" << endl;
    static const int numTests = 10;
    void* addresses[numTests];
    int numAllocs = 0;
    while (numAllocs < numTests) {
        addresses[numAllocs++] = allocator->malloc(size);
    }
    cout << "Allocated " << numTests << " addresses" << endl;
    cout << "   Pool Allocator Num Used Memory:" << allocator->NumUsedMemory() << endl;
    cout << "   Pool Allocator Num Peak Memory:" << allocator->NumPeakMemory() << endl;

    while (numAllocs > numTests/2) {
        allocator->free(addresses[--numAllocs]);
    }

    cout << "Half-way through freeing memory from the pool:" << endl;
    cout << "   Pool Allocator Num Used Memory:" << allocator->NumUsedMemory() << endl;
    cout << "   Pool Allocator Num Peak Memory:" << allocator->NumPeakMemory() << endl;

    while (numAllocs > 0) {
        allocator->free(addresses[--numAllocs]);
    }

    cout << "Freeing memory completely from the pool:" << endl;
    cout << "   Pool Allocator Num Used Memory:" << allocator->NumUsedMemory() << endl;
    cout << "   Pool Allocator Num Peak Memory:" << allocator->NumPeakMemory() << endl;
}

void UnitTest::testFreeListAllocation(CustomAllocator* allocator) {
    static const int numSizes = 8;
    array<int,numSizes> allocSizes{{16,32,64,256,512,1024,2048,4096}};
    cout << "Freelist Allocation Test" << endl;
    static const int numTests = 50;
    void* addresses[numTests];
    int numAllocs = 0;
    while (numAllocs < numSizes) {
        addresses[numAllocs] = allocator->malloc(allocSizes[numAllocs]);
        ++numAllocs;
    }
    cout << "Allocated " << numAllocs << " addresses" << endl;
    cout << "   Pool Allocator Num Used Memory:" << allocator->NumUsedMemory() << endl;
    cout << "   Pool Allocator Num Peak Memory:" << allocator->NumPeakMemory() << endl;

    numAllocs = 0;
    while (numAllocs < numSizes) {
        addresses[numAllocs+8] = allocator->malloc(allocSizes[numAllocs]);
        ++numAllocs;
    }

    cout << "Allocated " << numAllocs*2 << " addresses" << endl;
    cout << "   Pool Allocator Num Used Memory:" << allocator->NumUsedMemory() << endl;
    cout << "   Pool Allocator Num Peak Memory:" << allocator->NumPeakMemory() << endl;

    numAllocs = 16;
    while (numAllocs > 8) {
        allocator->free(addresses[--numAllocs]);
    }

    cout << "Half-way through freeing memory from the pool:" << endl;
    cout << "   Pool Allocator Num Used Memory:" << allocator->NumUsedMemory() << endl;
    cout << "   Pool Allocator Num Peak Memory:" << allocator->NumPeakMemory() << endl;

    while (numAllocs > 0) {
        allocator->free(addresses[--numAllocs]);
    }

    cout << "Freeing memory completely from the pool:" << endl;
    cout << "   Pool Allocator Num Used Memory:" << allocator->NumUsedMemory() << endl;
    cout << "   Pool Allocator Num Peak Memory:" << allocator->NumPeakMemory() << endl;
}
