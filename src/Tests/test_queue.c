#include "../includes/queue.h"
#include <stdio.h>
// memory leaks exist

QUEUE(int)

int main(int argc, char const *argv[]) {
  int_queue p_queue;
  init_int_queue(&p_queue);
  push_int_queue(p_queue, 1);
  printf("%d\n", dequeue_int_queue(p_queue)->val);
  return 0;
}
