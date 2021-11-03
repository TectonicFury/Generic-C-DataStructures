#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../includes/sequential_search.h"

int equals_int_(int a, int b) {
  if (a == b) return 1;
  return 0;
}

SequentialSearchST(int, int, equals_int)

void destruct_int_int_pair(int_int_pairST int_pair) {
  // basic freeing, no recursive freeing for primitive data members (here ints)
  if (int_pair) {
    // if already freed, we don't want to double free
    free(int_pair);
  }
}
int main(int argc, char const *argv[]) {
  int_int_listST head_listST = NULL;

  head_listST = insert_int_int_listST(head_listST, 1, 1);

  srand(time(NULL));
  int x;
  for (size_t i = 0; i < 100; i++) {
    x = (rand() & (-2)) % 100;
    head_listST = insert_int_int_listST(head_listST, x, x * x);
  }
  int count = 0;
  for (int_int_listST iter = head_listST; iter != NULL; iter = iter->next) {
    printf("key = %d, value = %d, count = %d\n", iter->value_type->key, iter->value_type->value, ++count);
  }

  int_int_pairST p;
  for (size_t i = 0; i < 100; i++) {
    x = (rand() & (-2)) % 100;
    p = find_in_int_int_listST(head_listST, x);
    if (p) {
      head_listST = delete_int_int_listST(head_listST, x, destruct_int_int_pair);
    }
  }
  count = 0;
  for (int_int_listST iter = head_listST; iter != NULL; iter = iter->next) {
    printf("key = %d, value = %d, count = %d\n", iter->value_type->key, iter->value_type->value, ++count);
  }
  free_whole_int_int_listST(head_listST, destruct_int_int_pair); // no memory leaks
  return 0;
}
