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
  printf(">> Testing insertions: Inserting random key-value pairs\n");
  for (size_t i = 0; i < 50000; i++) {
    j = rand() % 100000;
    // inserting random keys and the values (their squares)
    // you have to put the root on LHS for the effect to take place
    rbt_root = insert_int_int_rbt(rbt_root, j, j * j);
  }
  size_rbt = size_int_int_rbt(rbt_root);
  printf("   : Size after insertions = %d\n", size_rbt);

  // testing delete the minimum
  printf("\n>> Testing minimum and delete the minimum\n");
  int_int_pair min_rbt = min_int_int_rbt(rbt_root);
  printf("   : Minimum key-value before deletion: key = %d, value = %d\n", min_rbt->key, min_rbt->value);
  rbt_root = delete_min_int_int_rbt(rbt_root, destruct_int_int_pair);
  int size_rbt1 = size_int_int_rbt(rbt_root);
  printf("   : Size after single deletion (delete min) = %d\n", size_rbt1);
  assert(size_rbt1 == size_rbt - 1);
  min_rbt = min_int_int_rbt(rbt_root);
  printf("   : Minimum key-value after deletion: key = %d, value = %d\n", min_rbt->key, min_rbt->value);

  // testing delete the maximum
  printf("\n>> Testing maximum and delete the maximum\n");
  int_int_pair max_rbt = max_int_int_rbt(rbt_root);
  printf("   : Maximum key-value before deletion: key = %d, value = %d\n", max_rbt->key, max_rbt->value);
  rbt_root = delete_max_int_int_rbt(rbt_root, destruct_int_int_pair);
  int size_rbt2 = size_int_int_rbt(rbt_root);
  max_rbt = max_int_int_rbt(rbt_root);
  assert(size_rbt2 == size_rbt1 - 1);
  printf("   : Maximum key-value after deletion: key = %d, value = %d\n", max_rbt->key, max_rbt->value);

  rbt_root = insert_int_int_rbt(rbt_root, 500, 27000);
  rbt_root = delete_int_int_rbt(rbt_root, 500, destruct_int_int_pair);

  List_int_int_pair list0 = recursive_inorder_int_int_rbt(rbt_root);
  List_int_int_pair list0_ref = list0; // save a reference to list head in order to free it later
  // printing inorder
  printf("\n>> Testing inorder\n");
  size_rbt = size_int_int_rbt(rbt_root);
  for (size_t i = 0; i < size_rbt; i++) {
    printf("   : key = %d, value = %d\n", list0->entry->key, list0->entry->value);
    list0 = list0->next; // memory leak if you try to free the list using list0, use list0_ref to free
  }


  //
  // /* testing address sanitizer in homebrew LLVM clang using
  // clang -c Test_rbt.c -Wall -g -std=c11 -fsanitize=address -fsanitize=leak -fno-omit-frame-pointer
  // clang -o test_rbt Test_rbt.o -Wall -g -std=c11 -fsanitize=address */
  // run with ASAN_OPTIONS=detect_leaks=1 ./test_rbt
  deep_destroy_List_int_int_rbt(list0, destruct_int_int_pair); // memory leak: list0 points to end of list because of list->next,
  // below line actually frees the memory since it uses reference to first node in list
  deep_destroy_List_int_int_rbt(list0_ref, destruct_int_int_pair); //  cleans up the list as well as the underlying pair struct

  free_whole_rbt_int_int_(&rbt_root, destruct_int_int_pair); // free the whole RBT
  //

  return 0;
}
