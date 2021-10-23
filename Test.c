#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

int less_int_(int a, int b) { return a < b;}
int more_int_(int a , int b) { return a > b;}
//macros - below bst associates keys of type int to int values
BST(int, int, less_int, more_int)

int main(int argc, char const *argv[]) {
  int_int_bst bst_root = NULL;
  int j;
  for (size_t i = 0; i < 400000; i++) {
    j = rand() % 50000;
    // inserting random keys and the values (their squares)
    bst_root = insert_int_int_bst(bst_root, j, j * j);
  }
  // below list contains the elements inorder
  List_int_int_pair list = recursive_inorder_int_int_bst(bst_root);
  int size_bst = size_int_int_bst(bst_root);
  printf("bst size = %d\n", size_bst);
  for (size_t i = 0; i < size_bst; i++) {
    printf("key = %d, value = %d\n", list->entry->key, list->entry->value);
    list = list->next;
  }
  return 0;
}
