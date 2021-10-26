#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
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
    printf("freed the pair\n");
  }
}
int main(int argc, char const *argv[]) {
  int_int_rbt rbt_root = NULL;
  int j;
  int size_rbt;

  srand(time(NULL));

  for (size_t i = 0; i < 5000; i++) {
    j = rand() % 10000000;
    // inserting random keys and the values (their squares)
    // you have to put the root on LHS for the effect to take place
    rbt_root = insert_int_int_rbt(rbt_root, j, j * j);
    // size_rbt = size_int_int_rbt(rbt_root);
    // printf("rbt size1 = %d\n", size_rbt);
  }
  List_int_int_pair list = recursive_inorder_int_int_rbt(rbt_root);

  // printing inorder

  // for (size_t i = 0; i < size_rbt; i++) {
  //   printf("key = %d, value = %d\n", list->entry->key, list->entry->value);
  //   list = list->next;
  // }

  /* testing address sanitizer in homebrew LLVM clang using
  clang -c Test_rbt.c -Wall -g -std=c11 -fsanitize=address -fsanitize=leak -fno-omit-frame-pointer
  clang -o test_rbt Test_rbt.o -Wall -g -std=c11 -fsanitize=address */

  deep_destroy_List_int_int_rbt(list, destruct_int_int_pair); // cleans up the list as well as the underlying pair struct
  size_rbt = size_int_int_rbt(rbt_root);
  printf("rbt size2 = %d\n", size_rbt);

  // for (size_t i = 0; i < 100; i++) {
  rbt_root = delete_min_int_int_rbt(rbt_root, destruct_int_int_pair);
  size_rbt = size_int_int_rbt(rbt_root);
  printf("rbt size3 = %d\n", size_rbt);
  // frees the memory and sets rbt_root to NULL
  free_whole_rbt_int_int_(&rbt_root, destruct_int_int_pair); // no leaks and no heap use after free
  printf("pointer = %p\n", rbt_root);

  size_rbt = size_int_int_rbt(rbt_root);
  printf("rbt size3 = %d\n", size_rbt);
  // now no segfault (caused by heap use after free bugs): rbt_root is NULL
  list = recursive_inorder_int_int_rbt(rbt_root);
  size_rbt = size_int_int_rbt(rbt_root);
  for (size_t i = 0; i < size_rbt; i++) {
    printf("key = %d, value = %d\n", list->entry->key, list->entry->value);
    list = list->next;
  }
  return 0;
}
