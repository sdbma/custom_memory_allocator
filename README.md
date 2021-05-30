## Custom Memory Allocator

The standard library functions such as *malloc* and *new* are general-purpose allocators. These functions work on multithreaded paragdigms and that makes them slow. They make calls to the Operating System kernel requesting memory, while *free* and *delete* make requests to release the memory. This means that the operating system has to switch between user-space code and kernel code every time a request for memory is made. Programs requesting repeated calls of *malloc* or *new* eventually will run slow because of the repeated context switching. [IBM page] describes the need for creating custom memory allocator in detail.

## What this repository is about?

This repository describes two ways to manage custom memory allocator. We stay with the basics - a pool allocator and a free list allocator. For the sake of simplicity, memory alignment, padding and guard bytes were not considered as part of this project. This repository is mainly to understand the nuances of implementing a custom memory allocation built from heap. 

## Advantages of custom memory allocator

To mitigate the disadvantages of general-purpose allocators, custom memory allocators improves performance by calling general purpose malloc only once to get a big chunk of memory, and then it manages this chunk internally to provide smaller allocations. It uses some data structures to keep track of the allocated/used and free blocks.

## Pool Allocator

A pool allocator splits the big memory chunk in smaller chunks of the **same size**. It uses a **stack** to keep track of free and used blocks. When an allocation is requested, it returns the next free chunk and removes it from the stack, and when a free is done, it push the free block into the stack.

License
----

GNU General Public Licence


[IBM page]: <https://developer.ibm.com/technologies/systems/tutorials/au-memorymanager/>
