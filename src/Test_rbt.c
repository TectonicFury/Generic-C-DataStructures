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
int main(int argc, char const *argv[]) {
  int_int_rbt rbt_root = NULL;
  rbt_root = insert_int_int_rbt(rbt_root, 1, 1);
  printf("size = %d\n", size_int_int_rbt(rbt_root));
  rbt_root = insert_int_int_rbt(rbt_root, 2, 4);
  printf("size = %d\n", size_int_int_rbt(rbt_root));
  rbt_root = insert_int_int_rbt(rbt_root, 3, 9);
  printf("size = %d\n", size_int_int_rbt(rbt_root));
  rbt_root = insert_int_int_rbt(rbt_root, 4, 16);
  printf("size = %d\n", size_int_int_rbt(rbt_root));
  return 0;
}
