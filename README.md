# C_DataStructures
### Generic Data Structures in C using macros
The data structures in this repository are a C port of Sedgewick's recursive implementations in Java.
Currently, it has support for (unbalanced) BSTs and Red-Black BSTs. To make use of a data structure, include the appropriate header file and initialise it by passing relevant arguments for types and comparison functions.

As an example, here is what a macro initialisation for Red-Black tree having ints as keys and values looks like (pay attention to the naming convention for the comparison functions):

```
#include <stdio.h>
#include "rbt.h" // for instantiating red-black trees

/* less_int_ takes two arguments a and b and returns 1 if a is less than
 b and 0 otherwise; more_int_ takes a and b and returns 1 if a is greater than b and 0 otherwise.
 This convention has to hold for comparison functions for keys of any type, primitive or not */

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

/* the above macro initialisation defines the following functions:
```
