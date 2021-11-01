#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "bst.h"
// need to fix memory leaks
typedef char *my_string; // can't paste * in macros substitutions if joining

// compare functions
int less_int_(int a, int b) { return a < b;}
int more_int_(int a , int b) { return a > b;}

int less_string_(my_string s1, my_string s2) {
  if (strcmp(s1, s2) < 0) return 1;
  return 0;
}
int more_string_(my_string s1, my_string s2) {
  if (strcmp(s1, s2) > 0) return 1;
  return 0;
}

//macros - below bst associates keys of type int to int values
BST(int, int, less_int, more_int)
/* BST with strings as keys */
BST(my_string, int, less_string, more_string)
/* destructor for int_int_pair */
void destruct_int_int_pair(int_int_pair int_pair) {
  free(int_pair); // basic freeing, no recursive freeing for primitive data members (here ints)
  printf("freed the pair\n");
}
void destruct_temp(my_string_int_pair p) {}
int main(int argc, char const *argv[]) {
  int_int_bst bst_root = NULL;
  int j;

  // seeding rand
  srand(time(NULL));

  for (size_t i = 0; i < 1; i++) {
    j = rand() % 100000;
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
  // causes heap use after free error. max points to a location which was deleted (using delete_min) and max was not set to NULL
  if (max) { // MAX can be null if bst_root is NULL
    printf("max key = %d, max value = %d\n", max->key, max->value);
  }
  bst_root = deleteMax_int_int_bst(bst_root, destruct_int_int_pair);
  printf("new size = %d\n", size_int_int_bst(bst_root));
  max = max_int_int_bst(bst_root); // recalculating max
  if (max) { // MAX can be null if bst_root is NULL
    printf("max key = %d, max value = %d\n", max->key, max->value);
  }
  // testing deletion
  bst_root = insert_int_int_bst(bst_root, 250, 500);
  printf("new size = %d\n", size_int_int_bst(bst_root));
  bst_root = delete_int_int_bst(bst_root, 250, destruct_int_int_pair);
  printf("new size = %d\n", size_int_int_bst(bst_root));
  list = recursive_inorder_int_int_bst(bst_root);
  size_bst = size_int_int_bst(bst_root);
  printf("bst size = %d\n", size_bst);
  for (size_t i = 0; i < size_bst; i++) {
    printf("key = %d, value = %d\n", list->entry->key, list->entry->value);
    list = list->next;
  }

  // testing recursive height
  printf("bst height = %d\n", height_int_int_bst(bst_root));

  /* testing bst with character string keys */
  my_string_int_bst new_bst = NULL;
  char str1[] = "tom";
  char str2[] = "marvolo";
  char str3[] = "riddle";
  char str4[] = "ziddle";

  new_bst = insert_my_string_int_bst(new_bst, str1, 1);
  new_bst = insert_my_string_int_bst(new_bst, str2, 2);
  new_bst = insert_my_string_int_bst(new_bst, str3, 3);
  new_bst = insert_my_string_int_bst(new_bst, str4, 4);
  List_my_string_int_pair list2 = recursive_inorder_my_string_int_bst(new_bst);
  int size_new_bst = size_my_string_int_bst(new_bst);
  printf("new size = %d\n", size_new_bst);
  for (size_t i = 0; i < size_new_bst; i++) {
    printf("key = %s, value = %d\n", list2->entry->key, list2->entry->value);
    list2 = list2->next;
  }
  printf("height = %d\n", height_my_string_int_bst(new_bst));
  new_bst = delete_my_string_int_bst(new_bst, "tom", destruct_temp);
  size_new_bst = size_my_string_int_bst(new_bst);
  printf("new size = %d\n", size_new_bst);
  list2 = recursive_inorder_my_string_int_bst(new_bst);
  for (size_t i = 0; i < size_new_bst; i++) {
    printf("key = %s, value = %d\n", list2->entry->key, list2->entry->value);
    list2 = list2->next;
  }
  return 0;
}
