# Generic Data Structures in C (using macros)
The data structures in this repository are a C port of [Sedgewick's recursive implementations](https://www.cs.princeton.edu/~rs/talks/LLRB/LLRB.pdf) in Java. Currently, it has support for Sequential Search symbol tables (ie. Linked Lists), unbalanced BSTs, Red-Black BSTs, Sets, and Hash Tables with Separate Chaining. To make use of a data structure, simply include the appropriate header file and initialise it by passing required arguments for types and comparison functions.

For working examples, check the test files. As a rough (possibly broken) example, here is what a macro initialisation for Red-Black tree having **int** as both key and value type looks like (pay attention to the naming convention for the comparison functions):

```C
// this example *might* be broken, check the test files for working programs
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

// when passing the name of the comparison function, omit the trailing underscore.
// the "less" function name (minus the trailing underscore) goes first

RedBlackTree(int, int, less_int, more_int) // macro initialisation
```
The above macro initialisation defines the following types:
 Type | Description
 ---- | -----------
 int_int_rbt | the main RBT node type (pasting **KEY** = int and **VALUE** = int in **KEY** ## **_** ## **VALUE** ## **_rbt**)
 int_int_pair | the underlying 'value_type' inside an RBT node which holds the Key and Value pair
 List_int_int_pair |  a list type for iterating inorder over the elements of the tree. Each list node contains a **int_int_pair**

  The following functions are also defined:
  Function | Description
  -------- | -----------  
  insert_int_int_rbt(int_int_rbt, int, int) | Takes the root node of the tree (of type int_int_rbt) and the key and value to insert. Return type is **int_int_rbt**
  size_int_int_rbt(int_int_rbt) | Takes the root and returns the size of the tree (or the size of the subtree rooted at the node). Return type is **int**
  min_int_int_rbt(int_int_rbt) | Returns the key-value pair with the smallest key in the tree (or subtree). Return type is **int_int_pair**
  max_int_int_rbt(int_int_rbt) | Returns the key-value pair with greatest key in tree (or subtree). Return type is **int_int_pair**
  recursive_inorder_int_int_rbt(int_int_rbt) | Returns an inorder list of elements in the tree. Return type is **List_int_int_pair**
  delete_min_int_int_rbt(int_int_rbt, void (\*destruct) (int, int)) | Deletes the minimum taking the root and *destruct function pointer* as argument. Return type is **int_int_rbt**
  delete_max_int_int_rbt(int_int_rbt, void (\*destruct) (int, int)) | deletes the maximum taking the root and *destruct function pointer* as argument. Return type is **int_int_rbt**
  delete_int_int_rbt(int_int_rbt, int, void (*destruct) (int, int)) | Takes the *key* to delete in addition to the root and *destruct function pointer*. Return type is **int_int_rbt**
  deep_destroy_List_int_int_rbt(List_int_int_pair) | Frees memory used for inorder traversal
  free_whole_rbt_int_int_(int_int_rbt) | Cleans up the RBT

For the delete functions, you need a *destruct* function appropriate for your key and value types to ensure that there are no memory leaks. For freeing a *value_type* of type int_int_pair, you would have a destruct function like so:

```C
void destruct_int_int_pair(int_int_pair int_pair) {

  // call appropriate destructors for your key and value here

  // then free the value_type pair struct   
  if (int_pair) { // if already freed, we don't want to double free
    free(int_pair);
  }
}
```
If the types have a '*' in them, `typedef` them to 'remove' any *. eg. if key is `char*`, then do:
```C
typedef char *my_string;
RedBlackTree(my_string, int, some_less, some_more)
```
### Sample program

```C
// sample_rbt.c
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "rbt.h"
int less_int_(int a, int b) {
  if (a < b) return 1;
  return 0;
}
int more_int_(int a, int b) {
  if (a > b) return 1;
  return 0;
}
RedBlackTree(int, int, less_int, more_int)

void destruct_int_int_pair(int_int_pair int_pair) {
  // basic freeing, no recursive freeing for primitive data members (here ints)
  if (int_pair) {
    // if already freed, we don't want to double free
    free(int_pair);
  }
}
int main(int argc, char const *argv[]) {
  int_int_rbt rbt_root = NULL;
  int j;
  int size_rbt;

  srand(time(NULL));

  // testing insert
  printf("Inserting random key-value pairs\n");
  for (size_t i = 0; i < 50000; i++) {
    j = rand() % 100000;
    // inserting random keys and the values (their squares)
    // you have to put the root on LHS for the effect to take place
    rbt_root = insert_int_int_rbt(rbt_root, j, j * j);
  }
  size_rbt = size_int_int_rbt(rbt_root);
  printf("Size after insertions = %d\n", size_rbt);

  // delete the minimum

  rbt_root = delete_min_int_int_rbt(rbt_root, destruct_int_int_pair);

  // delete the maximum
  rbt_root = delete_max_int_int_rbt(rbt_root, destruct_int_int_pair);

  // inorder list
  List_int_int_pair list0 = recursive_inorder_int_int_rbt(rbt_root);
  List_int_int_pair list0_ref = list0; // save a reference to list head in order to free it later

  // printing inorder
  size_rbt = size_int_int_rbt(rbt_root);
  for (size_t i = 0; i < size_rbt; i++) {
    printf("   : key = %d, value = %d\n", list0->entry->key, list0->entry->value);
    list0 = list0->next;
  }

  // clean up
  deep_destroy_List_int_int_rbt(list0, destruct_int_int_pair); // memory leak: list0 points to end of list because of list->next,
  // below line actually frees the memory since it uses reference to first node in list
  deep_destroy_List_int_int_rbt(list0_ref, destruct_int_int_pair); //  cleans up the list as well as the underlying pair struct

  free_whole_rbt_int_int_(&rbt_root, destruct_int_int_pair); // free the whole RBT

  return 0;
}
```
### Compiling
`clang -o sample_rbt sample_rbt.c -std=c11`

### More examples
Read the test files for more examples. Currently BST implementation is having memory bugs.
