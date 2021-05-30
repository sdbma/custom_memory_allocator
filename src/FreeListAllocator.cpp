#include <limits>
#include <cstdlib>
#include <iostream>
#include "FreeListAllocator.hpp"

FreeListAllocator::FreeListAllocator(const size_t totalSize, const Policy policy,
        const bool printInfo) : CustomAllocator(totalSize, printInfo),
                                m_policy(policy) 
{
    m_startPtr = ::malloc(m_totalSize);
    ListNode* node = (ListNode*) m_startPtr;
    node->blockSize = totalSize;
    node->next = nullptr;
    m_head = node;
}

FreeListAllocator::~FreeListAllocator() {
    ::free(m_startPtr);
    m_startPtr = nullptr;
}

void* FreeListAllocator::malloc(const size_t size) {
     size_t reqdSize = sizeof(ListNode) + size;
     ListNode* prevNode, *foundNode;
     findNextFree(reqdSize, prevNode, foundNode);
     size_t remaining = foundNode->blockSize - reqdSize;
     if (remaining > 0) {
         ListNode* newNode = (ListNode*)((size_t)foundNode+reqdSize);
         newNode->blockSize = remaining;
         insert(foundNode, newNode);
     }
     foundNode->blockSize = size;
     m_used += foundNode->blockSize;
     m_peak = max(m_peak, m_used);
     remove(prevNode, foundNode);
     if (m_printInfo) 
         cout << "Allocated: " << (foundNode + sizeof(ListNode)) << ' ' << foundNode->blockSize << endl;
     return (void*) (foundNode + sizeof(ListNode));
}

void FreeListAllocator::free(void* ptr) {
     size_t headerAddr = (size_t)ptr - sizeof(ListNode);
     ListNode* node = (ListNode*) headerAddr;
     if (m_printInfo) 
         cout << "Freed: " << ptr << ' ' << node->blockSize << endl;
     node->next = nullptr;
     ListNode* iter = m_head;
     ListNode* prev = nullptr;
     while (iter != nullptr) {
         if (ptr < iter) {
             insert(prev, node);
             break;
         }
         prev = iter;
         iter = iter->next;
     }
     m_used -= node->blockSize;
     // merge contiguous nodes
     mergeContiguousNodes(prev, node);
}

void FreeListAllocator::mergeContiguousNodes(ListNode* prev, ListNode* curr) {
    if (curr->next != nullptr &&
            (size_t) curr + curr->blockSize == (size_t) curr->next) {
        curr->blockSize += curr->next->blockSize;
        remove(curr, curr->next); 
    }
    if (prev != nullptr &&
            (size_t) prev + prev->blockSize == (size_t) curr) {
        prev->blockSize += curr->blockSize;
        remove(prev, curr); 
    }
}

void FreeListAllocator::findNextFree(const size_t reqdSize, ListNode*& prevNode, ListNode*& foundNode) {
    ListNode* bestBlock = nullptr, *bestBlockPrev = nullptr, *iter = m_head, *prev = nullptr;
    if (m_policy == BEST) {
        size_t minDiff = numeric_limits<size_t>::max();
        while (iter != nullptr) {
           if (iter->blockSize == reqdSize)  {
               bestBlockPrev = prev;
               bestBlock = iter;
               break;
           } else if ((iter->blockSize >= reqdSize) && (iter->blockSize - reqdSize < minDiff)) {
               bestBlockPrev = prev;
               bestBlock = iter;
           }
           prev = iter;
           iter = iter->next;
        }
    } else if (m_policy == FIRST) {
        while (iter != nullptr) {
           if (iter->blockSize >= reqdSize)  {
               bestBlockPrev = prev;
               bestBlock = iter;
               break;
           }
           prev = iter;
           iter = iter->next;
        }
    }
    prevNode = bestBlockPrev;
    foundNode = bestBlock;
}

void FreeListAllocator::insert(ListNode* previousNode, ListNode* newNode) {
    if (previousNode == nullptr) {
        newNode->next = m_head;
        m_head = newNode;
    } else {
        newNode->next = previousNode->next;
        previousNode->next = newNode;
    }
}

void FreeListAllocator::remove(ListNode* previousNode, ListNode* removedNode) {
    if (previousNode == nullptr) {
        m_head = removedNode->next;
    } else {
        previousNode->next = removedNode->next;
    }
}
