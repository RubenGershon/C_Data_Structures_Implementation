PROJECT: Generic Circular Queue

This project is the implementation of a Generic Circular Queue.
Circular Queue is a linear DS in which the operations are performed based on 
FIFO (First In First Out) principle and the last position is connected 
back to the first position to make a circle. It is also called ‘Ring Buffer’ or
'Circular Buffer'.
The Generic Circular Queue is in fact a queue of pointers to objects of any
kind. The size of each item in the container is sizeof(pointer).

The container support the following operations:

- create
- destroy
- enqueue
- dequeue
- capacity
- size
- empty
- full
- foreach


FILES:

- generic_circular_queue.h = header file with descriptive API.
- generic_circular_queue.c = .c implementation file.
- generic_circular_queue.c = test file.
- Status.h = Utility file for errors status.
- makefile.


Author(s)

    Ruben Gershon - Passionate Software Developer and Pizza Lover.

