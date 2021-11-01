#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../includes/hash_table.h"


int equals_int_(int a, int b) {
  if (a == b) return 1;
  return 0;
}

int int_hash_(int a, int m) {
  return a % m;
}

HashTable(int, int, equals_int, int_hash)

void destruct_int_int_pair(int_int_pairST int_pair) {
  // basic freeing, no recursive freeing for primitive data members (here ints)
  if (int_pair) {
    // if already freed, we don't want to double free
    free(int_pair);
  }
}

int main(int argc, char const *argv[]) {
  int_int_hash_table hash_table;
  // printf("%p\n", hash_table);
  init_int_int_hash_table(&hash_table);
  // insert_int_int_hash_table(&hash_table, 1, 1, destruct_int_int_pair);
  srand(time(NULL));
  printf("%p\n", hash_table);
  printf("capacity = %d, size = %d\n", hash_table->capacity, hash_table->size);
  int x;
  for (size_t i = 0; i < 10000; i++) {
    x = (rand() & (-2)) % 20000;
    insert_int_int_hash_table(&hash_table, x, x * x, destruct_int_int_pair);
  }

  for (size_t i = 0; i < 20000; i++) {
    int_int_pairST p = find_in_int_int_hash_table(hash_table, i);
    if (p) {
      printf("key = %d, value = %d\n", p->key, p->value);
    }
  }
  printf("size of hashtable = %d\n", hash_table->size);
  free_int_int_hash_table(&hash_table, destruct_int_int_pair);
  printf("%p\n", hash_table); // set to NULL
  return 0;
}
