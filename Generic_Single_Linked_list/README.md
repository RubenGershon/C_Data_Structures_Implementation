PROJECT: Generic Single Linked List

This project is the implementation of a Generic Single Linked List.
A linked list is a linear data structure, in which the elements are not stored 
at contiguous memory locations. The elements in a linked list are stored in 
nodes linked one to the next using pointers. In my implementation of the 
Single Linked List, the user don't know about Nodes or about how the list is 
implemented. I provide the user with iterators to the list so he can easily
iterate over the list or do basic operations with the list.

The container support the following operations:

- Create
- Destroy
- Insert
- Remove
- Foreach
- Find
- FindMiddle
- IsEmpty
- Count
- HasLoop
- FindIntersection
- Flip (Iterative version)
- FlipRec (Recursive version)
- IteratorBegin
- IteratorEnd
- IteratorNext
- IteratorGet
- IteratorSet


FILES:

generic_single_linked_list.h = header file with descriptive API.
generic_single_linked_list.c = .c implementation file.
generic_single_linked_list_test.c = test file.
Status.h = Utility file for error status.
makefile.


Author(s)

    Ruben Gershon - Passionate Software Developer and Pizza Lover.

