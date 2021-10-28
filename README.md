# C_DataStructures
### Generic Data Structures in C using macros
The data structures in this repository are a C port of Sedgewick's recursive implementations in Java.
Currently, it has support for (unbalanced) BSTs and Red-Black BSTs. To make use of a data structure, include the appropriate header file and initialise it by passing relevant arguments for types and comparison functions.

As an example, here is what a macro initialisation for Red-Black tree having **int** as both key and value type looks like (pay attention to the naming convention for the comparison functions):

```C
#include <stdio.h>
#include "rbt.h" // for instantiating red-black trees

/* less_int_ takes two arguments a and b and returns 1 if a < b and 0 otherwise */
/* more_int_ takes a and b and returns 1 if a is greater than b and 0 otherwise. */
/*This convention has to hold for comparison functions for keys of any type, primitive or not */

// comparison functions must have an _ at the end of their names
int less_int_(int a, int b) {
  if (a < b) return 1;
  return 0;
}
int more_int_(int a, int b) {
  if (a > b) return 1;
  return 0;
}

// when passing the name of the comparison function, remove the trailing underscores.
// the "less" function name (minus the trailing underscore) goes first

RedBlackTree(int, int, less_int, more_int) // macro initialisation

```
The above macro initialisation defines the following types:
 Type | Description
 ---- | -----------
 int_int_rbt | the main RBT node struct (pasting **KEY** = int and **VALUE** = int in **KEY** ## **_** ## **VALUE** ## **_rbt**)
 int_int_pair | the underlying 'value_type' struct inside an RBT node which holds the Key and Value pair (pasting **KEY** = int and **VALUE** = int in **KEY** ## **_** ## **VALUE** ## **_pair**)
 List_int_int_pair |  a list type for iterating inorder over the elements of the tree (pasting **KEY** = int and **VALUE** = int in **List_** ## **KEY** ## **_** ## **VALUE** ## **_pair**)

  The following functions are also initialised:
  Function | Description
  -------- | -----------  
  insert_int_int_rbt(int_int_rbt, int, int) | takes the root node of the tree (of type int_int_rbt) and the key and value to insert. Return type is int_int_rbt
size_int_int_rbt(int_int_rbt) | takes the root and returns the size of the tree (or the size of the subtree rooted at the node). Return type is int.
min_int_int_rbt(int_int_rbt) | returns the key-value pair with the smallest key in the tree (or subtree). Return type is int_int_pair
max_int_int_rbt(int_int_rbt) | returns the key-value pair with greatest key in tree (or subtree). Return type is int_int_pair
recursive_inorder_int_int_rbt(int_int_rbt) | returns an inorder list of elements in the tree. Return type is List_int_int_pair

```C
void destruct_int_int_pair(int_int_pair int_pair) {
  // basic freeing, no recursive freeing for primitive data members (here ints)
  if (int_pair) {
    // if already freed, we don't want to double free
    free(int_pair);
  }
}
```
