Project name: Generic Stack

This project is the implementation of a Generic Stack.
This Stack is designed to store different data-type in a single container
and to operate in a LIFO context (last-in first-out), where elements are 
inserted and extracted only from one end of the container.
We can store int, float, char variables or any user-defined variables 
in the same container.
The generic stack is in fact a stack of pointers to objects of any kind.
The size of each item in the vector is sizeof(pointer).
Moreover, in this Generic Stack implementation, I decided to add
an optional Min Stack operation options.
This very useful operation allow the user to extract the minimum value present
in the stack with a O(1) time complexity.

The container support the following operations:

- create
- destroy
- push
- pop
- top
- min
- empty
- full
- size


FILES:

generic_stack.h = header file with descriptive API.
generic_stack.c = .c implementation file.
generic_stack_test.c = test file.
Status.h = Utility file for errors status.
makefile.


Author(s)

    Ruben Gershon - Passionate Software Developer and Pizza Lover.

