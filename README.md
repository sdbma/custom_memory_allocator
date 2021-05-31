## Custom Memory Allocator

The standard library functions such as *malloc* and *new* are general-purpose allocators. These functions work on multithreaded paragdigms and that makes them slow. They make calls to the Operating System kernel requesting memory, while *free* and *delete* make requests to release the memory. This means that the operating system has to switch between user-space code and kernel code every time a request for memory is made. Programs requesting repeated calls of *malloc* or *new* eventually will run slow because of the repeated context switching. [IBM page] describes the need for creating custom memory allocator in detail.

## What this repository is about?

This repository describes two ways to manage custom memory allocator. We stay with the basics - a pool allocator and a free list allocator. For the sake of simplicity, memory alignment, padding and guard bytes were not considered as part of this project. This repository is mainly to understand the nuances of implementing a custom memory allocation built from heap. 

## Advantages of custom memory allocator

To mitigate the disadvantages of general-purpose allocators, custom memory allocators improves performance by calling general purpose malloc only once to get a big chunk of memory, and then it manages this chunk internally to provide smaller allocations. It uses some data structures to keep track of the allocated/used and free blocks.

## Pool Allocator

A pool allocator splits the big memory chunk in smaller chunks of the **same size**. It uses a **stack** to keep track of free and used blocks. When an allocation is requested, it returns the next free chunk and removes it from the stack, and when a free is done, it push the free block into the stack.

To implement the book-keeping stack, we use contiguous array and allocated the size required for the array from the same memory along with the big memory chunk requested for pool allocation.

<img src="https://user-images.githubusercontent.com/4752422/120124849-3a20bd00-c184-11eb-9c0d-4cff01d6cfed.png" alt="drawing" width="600" height="200"/>


### Pool Allocator in Action

As described above, a contiguous array is kept aside for maintenance of the pools of equal chunks. Only two stack operations **push()** and **pop()** is required for book-keeping and these operations are implemented using an **chunkIndex** variable. Whenever an allocation is required pop() operation is imitated by reserving the address at current chunkIndex for allocation, and then incrementing the chunkIndex to point to next available address in the array. Similary, whenever a free is done push() operation is imitated by decrementing the chunk Index, and then storing the free address in the new chunk Index. This free address is now available for next requested allocation.

* The book-keeping array looks like the following before any allocation or free operation is done.
  <img src="https://user-images.githubusercontent.com/4752422/120123798-042d0a00-c17f-11eb-8393-9b3be04e36c4.png" alt="drawing" width="600" height="200"/>
* After the first allocation is done, the book-keeping array looks like following:
  <img src="https://user-images.githubusercontent.com/4752422/120123876-6554dd80-c17f-11eb-9db7-701c001cddb5.png" alt="drawing" width="600" height="200"/>
* After second allocation is done, the book-keeping array looks like the following:                                                                                            
  <img src="https://user-images.githubusercontent.com/4752422/120123910-9503e580-c17f-11eb-80c9-fc752de0e8e0.png" alt="drawing" width="600" height="200"/>
* After several allocation is done but no deallocation is done, the book-keeping array may look like following:                                                                  
  <img src="https://user-images.githubusercontent.com/4752422/120123958-ca103800-c17f-11eb-976e-455a99bb9cf7.png" alt="drawing" width="600" height="200"/>
* After first deallocation is requested using address **a2**, the address **a2** is **pushed** to the stack, the book-keeping array may look like the following:                     
  <img src="https://user-images.githubusercontent.com/4752422/120124000-faf06d00-c17f-11eb-8121-1cd0cc4528e7.png" alt="drawing" width="600" height="200"/>
* After several deallocation is requested with mixed addresses being **pushed**, the book-keeping array may look like the following:
<img src="https://user-images.githubusercontent.com/4752422/120124042-2a9f7500-c180-11eb-8694-4b242bc21811.png" alt="drawing" width="600" height="200"/>

License
----

GNU General Public Licence


[IBM page]: <https://developer.ibm.com/technologies/systems/tutorials/au-memorymanager/>
