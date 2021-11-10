#include "../includes/digraph.h"
#include "../includes/directed_dfs_digraph.h"
#include <stdio.h>

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
      printf("%d ", i);
    }
  }
  printf("\n");
  return 0;
}
