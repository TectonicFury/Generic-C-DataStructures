#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../includes/set.h"

int less_int_(int a, int b) {
  if (a < b) return 1;
  return 0;
}
int more_int_(int a, int b) {
  if (a > b) return 1;
  return 0;
}
// define a set of int keys
SET(int, less_int, more_int)

void destruct_int_set_entry(int_set_entry int_entry) {
  // basic freeing, no recursive freeing for primitive data members (here ints)
  if (int_entry) {
    // if already freed, we don't want to double free
    free(int_entry);
  }
}

int main(int argc, char const *argv[]) {
  int_set p_set = NULL;
  p_set = insert_int_set(p_set, 1); // no & operator unlike hash tables and like RBT
  printf("%p\n", p_set);
  srand(time(NULL));

  // testing insert
  for (size_t i = 0; i < 20000; i++) {
    p_set = insert_int_set(p_set, rand() % 5000);
  }
  printf("size of set = %d\n", p_set->size);

  // testing find
  for (size_t i = 0; i < 5000; i++) {
    int_set_entry p_e = find_in_int_set(p_set, i);
    if (p_e) {
      printf("found key = %d\n", p_e->key);
    }
  }

  for (size_t i = 0; i < 4000; i++) {
    int_set_entry p_e = find_in_int_set(p_set, i);
    if (p_e) {
      p_set = delete_int_set(p_set, i, destruct_int_set_entry);
    }
  }
  printf("size of set = %d\n", p_set->size);
  printf("%p\n", p_set);
  free_whole_int_set(&p_set, destruct_int_set_entry);
  return 0;
}
