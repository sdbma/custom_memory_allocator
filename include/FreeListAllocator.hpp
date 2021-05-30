#ifndef FREELISTALLOCATOR_HPP
#define FREELISTALLOCATOR_HPP

#include <list>
#include "CustomAllocator.hpp"

class FreeListAllocator : public CustomAllocator {
public:
    // find first or find best policy
    enum Policy {FIRST, BEST};

protected:
    Policy m_policy;
    void* m_startPtr = nullptr;

    // no extra space required, nodes will be created in
    // same heap we allocated through global malloc
    struct ListNode {
        size_t blockSize;
        ListNode* next;
    };

    void insert(ListNode* previous, ListNode* newNode);
    void remove(ListNode* previous, ListNode* removedNode);
    void mergeContiguousNodes(ListNode* prev, ListNode* curr);
    void findNextFree(const size_t reqdSize, ListNode*& prev, ListNode*& found);

    // head of freelist
    ListNode* m_head;
public:
    FreeListAllocator(const size_t totalSize, const Policy policy, const bool printDebug);
    virtual ~FreeListAllocator();
    virtual void* malloc(const size_t size) override;
    virtual void free(void* ptr) override;
};

#endif
