#include "../includes/stack.h"
#include <stdio.h>

STACK(int)

int main(int argc, char const *argv[]) {
  int_stack s, t;
  init_int_stack(&s); // basically setting s = NULL, essential, otherwise segfault
  for (size_t i = 0; i < 10; i++) {
    push_int_stack(&s, i);
  }
  // to avoid memory leak, save a reference to head
  t = s;
  for (size_t i = 0; i < 10; i++) {
    printf("popped = %d\n", pop_int_stack(&s)->val);
  }
  free_int_stack(&t);
  return 0;
}
