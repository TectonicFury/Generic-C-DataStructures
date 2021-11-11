#include "../includes/digraph.h"
#include "../includes/directed_dfs_digraph.h"
#include "../includes/directed_cycle.h"
#include "../includes/dfs_order.h"
#include "../includes/topological.h"

#include <stdio.h>
// topological sort is just a reverse post-order ordering of a DAG (maybe even a preorder will do)
int main(int argc, char const *argv[]) {
  Digraph dg;
  int V, E;
  scanf("%d", &V);
  scanf("%d\n", &E);
  init_digraph(&dg, V);

  int v, w;

  for (int i = 0; i < E; i++) {
    scanf("%d", &v);
    scanf("%d", &w);
    add_edge_digraph(dg, v, w);
  }

  // testing reverse
  Digraph reverse_dg = reverse_digraph(dg);

  // testing digraph DFS
  Directed_DFS d_dg;
  init_dfs_directed(&d_dg, dg);
  df_search_directed(d_dg, dg, 6); // single source
  for (int i = 0; i < V; i++) {
    printf("%d %s connected\n", i, is_marked_df_directed(d_dg, i) > 0 ? "is" : "is not");
  }

  int_stack st;
  init_int_stack(&st);
  push_int_stack(&st, 1);
  push_int_stack(&st, 2);
  push_int_stack(&st, 6);

  df_search_directed_multi_source(d_dg, dg, &st);

  for (int i = 0; i < dg->V; i++) {
    if (d_dg->marked[i]) {
      printf("multi-source connected: %d \n", i);
    }
  }
  printf("\n");

  // testing directed cycle
  // for a DAG nothing should be printed
  Directed_Cycle dc;
  init_directed_cycle(&dc, dg);

  if (dc->cycle) { // if cycle is present
    printf("Printing Cycle\n"); // 3 -> 5 -> 4 -> 3
    for (int_stack s_c = pop_int_stack(&(dc->cycle)); s_c != NULL; s_c = pop_int_stack(&(dc->cycle))) {
        printf("-> %d ", s_c->val);
    }
  }
  printf("\n");

  // testing Dfs_Order
  Dfs_Order ord;
  init_dfs_order(&ord, dg);
  int_queue pre_order = pre_dfs_order(ord);
  int_queue post_order = post_dfs_order(ord);
  int_stack reverse_post_order = reverse_post_dfs_order(ord);

  printf("PreOrder >>\n");
  for (int_node nd = dequeue_int_queue(pre_order); nd != NULL; nd = dequeue_int_queue(pre_order)) {
    printf("%d ", nd->val);
  }
  printf("\n\nPostOrder >>\n");
  for (int_node nd = dequeue_int_queue(post_order); nd != NULL; nd = dequeue_int_queue(post_order)) {
    printf("%d ", nd->val);
  }
  printf("\n\nReverse post-order >>\n");
  for (int_stack st = pop_int_stack(&reverse_post_order); st != NULL; st = pop_int_stack(&reverse_post_order)) {
    printf("%d ", st->val);
  }
  printf("\n");

  // testing topological sort for DAG
  Toplogical_Sort ts;
  init_toplogical_sort(&ts, dg);
  printf("\nTopological sort >>\n");
  for (int_stack st = pop_int_stack(&ts->reverse_post_order); st != NULL; st = pop_int_stack(&ts->reverse_post_order)) {
    printf("%d ", st->val);
  }
  printf("\n");
  return 0;
}
