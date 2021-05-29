## Custom Memory Allocator

The standard library functions such as *malloc* and *new* are general-purpose allocators. These functions work on multithreaded paragdigms and that makes them slow. They make calls to the Operating System kernel requesting memory, while *free* and *delete* make requests to release the memory. This means that the operating system has to switch between user-space code and kernel code every time a request for memory is made. Programs requesting repeated calls of *malloc* or *new* eventually will run slow because of the repeated context switching. [IBM page] describes the need for creating custom memory allocator in detail.

## What this page is about?

This page describes different ways to manage custom memory allocator. We start with basic 

License
----

GNU General Public Licence


[IBM page]: <https://developer.ibm.com/technologies/systems/tutorials/au-memorymanager/>
