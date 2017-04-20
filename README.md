# Custom Memory Management

## 1. Purpose
The purpose of this project is to provide a means to reduce the amount of space
necessary to reference an object in a C/C++ environment.
Typically, in a 64-bit architecture, it takes 8 bytes to reference any object
regardless of the amount of RAM the user has in their machine, which results in
a lot of wasted space.  Through the use of the memory management layer laid out
in this project, it is possible to cut the size of pointers down to an arbitrary
number of bytes (1-7).

It is important to note that the memory management layer does not actually
reduce the size of pointers allocated through the malloc/calloc functions that
interact directly with the operating system.  Instead, our memory management
layer uses an array of pre-allocated pages that allows us to circumvent
traditional pointer assignment.
