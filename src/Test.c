#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "bst.h"

// compare functions
int less_int_(int a, int b) { return a < b;}
int more_int_(int a , int b) { return a > b;}

//macros - below bst associates keys of type int to int values
BST(int, int, less_int, more_int)
void destruct_int_int_pair(int_int_pair int_pair) {
  free(int_pair); // basic freeing, no recursive freeing for primitive data members (here ints)
  printf("freed the pair\n");
}

int main(int argc, char const *argv[]) {
  int_int_bst bst_root = NULL;
  int j;

  // seeding rand
  srand(time(NULL));

  for (size_t i = 0; i < 600; i++) {
    j = rand() % 500;
    // inserting random keys and the values (their squares)
    // you have to put the root on LHS for the effect to take place
    bst_root = insert_int_int_bst(bst_root, j, j * j);
  }

  // testing inorder traversal
  // below list contains the elements inorder
  List_int_int_pair list = recursive_inorder_int_int_bst(bst_root);

  // size of bst is needed to iterate over the list elements
  int size_bst = size_int_int_bst(bst_root);
  printf("bst size = %d\n", size_bst);
  for (size_t i = 0; i < size_bst; i++) {
    printf("key = %d, value = %d\n", list->entry->key, list->entry->value);
    list = list->next;
  }

  // testing the min bst function
  int_int_pair min = min_int_int_bst(bst_root);
  if (min) { // min can be NULL if bst_root is NULL
    printf("min key = %d, min value = %d\n", min->key, min->value);
  }

  // testing the max bst function
  int_int_pair max = max_int_int_bst(bst_root);
  if (max) { // MAX can be null if bst_root is NULL
    printf("max key = %d, max value = %d\n", max->key, max->value);
  }

  // testing find_in_int_int_bst
  int_int_pair found = find_in_int_int_bst(bst_root, 50);
  if (found) { // need to check for non null since it returns NULL if key is absent
    printf("found value = %d\n", found->value);
  }

  // testing floor helper function (it's a helper since it uses an extra paramter for floor_ptr to initiate)
  int_int_pair floor_pair_helper = helper_floor_int_int_bst(bst_root, 55, NULL);
  if (floor_pair_helper) {
    printf("floor key = %d, floor value = %d\n", floor_pair_helper->key, floor_pair_helper->value);
  }

  // testing the main floor function
  int_int_pair floor_pair = floor_int_int_bst(bst_root, 65);
  if (floor_pair) {
    printf("floor key = %d, floor value = %d\n", floor_pair->key, floor_pair->value);
  }

  // testing main ceiling function
  int_int_pair ceiling_pair = ceiling_int_int_bst(bst_root, 65);
  if (ceiling_pair) {
    printf("ceiling key = %d, ceiling value = %d\n", ceiling_pair->key, ceiling_pair->value);
  }

  // testing select_rank_
  int_int_pair pair_with_rank_10 = select_rank_int_int_bst(bst_root, 10);
  if (pair_with_rank_10) {
    printf("key = %d, value = %d\n", pair_with_rank_10->key, pair_with_rank_10->value);
  }

  // testing rank
  int rank_of_15 = rank_int_int_bst(bst_root, 15);
  printf("rank of 15 = %d\n", rank_of_15);

  // testing delete Min
  if (min) { // printing the previous min value
    printf("min key = %d, min value = %d\n", min->key, min->value);
  }
  printf("old size = %d\n", size_int_int_bst(bst_root));
  // deleting min key
  bst_root = deleteMin_int_int_bst(bst_root, destruct_int_int_pair);
  printf("new size = %d\n", size_int_int_bst(bst_root));
  min = min_int_int_bst(bst_root); // recalculating min
  if (min) { // printing the new minimum value
    printf("min key = %d, min value = %d\n", min->key, min->value);
  }

  // testing delete max
  if (max) { // MAX can be null if bst_root is NULL
    printf("max key = %d, max value = %d\n", max->key, max->value);
  }
  bst_root = deleteMax_int_int_bst(bst_root, destruct_int_int_pair);
  printf("new size = %d\n", size_int_int_bst(bst_root));
  max = max_int_int_bst(bst_root); // recalculating max
  if (max) { // MAX can be null if bst_root is NULL
    printf("max key = %d, max value = %d\n", max->key, max->value);
  }
  

  return 0;
}
