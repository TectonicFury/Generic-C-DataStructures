// #include "../includes/vertex_indexed_graph.h"
#include "../includes/dfs.h"
#include "../includes/bfs.h"
#include "../includes/connected_components.h"
#include <stdio.h>

// memory bugs remain (leaks)

int main(int argc, char const *argv[]) {
  Graph g;
  int V, E;
  int v, w;
  scanf("%d\n %d", &V, &E);
  g = init_graph(V, E);

  for (int i = 0; i < E; i++) {
    scanf("%d", &v);
    scanf("%d", &w);
    add_edge(g, v, w);
  }

  // iterating over the vertices printing the edges
  printf("\nprinting Graph -->\n");
  for (int i = 0; i < V; i++) {
    Ints_Bag b;
    printf("%d: ", i);
    for (b = g->adj[i]; b != NULL; b = b->next) {
      printf("%d ", b->v);
    }
    printf("\n");
  }

  // printf("here1\n");
  dfs p_dfs = init_dfs(g, 0);
  // printf("here2\n");
  df_search(p_dfs, g, 0);
  // printf("here3\n");

  // for (int i = 0; i < g->V; i++) {
  //   printf("%d is connected to 0 : %s\n", i, is_marked(p_dfs, i) > 0 ? "true" : "false");
  // }
  //
  int_stack path = path_dfs(p_dfs, 3); // not necessarily the shortest (6-4-5-3)
  if (path) {
    for (int_stack i = pop_int_stack(&path); i != NULL; i = pop_int_stack(&path)) {
      printf("%d-", i->val);
    }
    printf("\n");
  }

  bfs p_bfs = init_bfs(g, 0);
  int_stack path_bfs_ = path_bfs(p_bfs, 3); // shortest (5-3)
  if (path_bfs_) {
    for (int_stack i = pop_int_stack(&path_bfs_); i != NULL; i = pop_int_stack(&path_bfs_)) {
      printf("%d-", i->val);
    }
    printf("\n");
  }

  CC components;
  init_CC(&components, g);
  printf("component count = %d\n", components->count);
  return 0;
}
