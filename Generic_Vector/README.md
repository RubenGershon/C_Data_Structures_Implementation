PROJECT: Generic Vector

This project is the implementation of a Generic Dynamic Vector.
Generic Vector is convenient to store generic data-type in a single container.
The generic vector is in fact a vector of pointers to objects of any kind.
The size of each item in the vector is sizeof(pointer).
The Vector is heap allocated and can grow and shrink on demand.

The container support the following operations:

- create
- destroy
- push
- pop
- get
- set
- capacity
- size
- foreach


FILES:

- generic_vector.h = header file with descriptive API.
- generic_vector.c = .c implementation file.
- generic_vector_test.c = test file.
- Status.h = Utility file for error status.
- makefile.


Author(s)

    Ruben Gershon - Passionate Software Developer and Pizza Lover.

