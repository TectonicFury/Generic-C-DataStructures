// need to add multiple source directed dfs
#ifndef DIRECTED_DFS_H
#define DIRECTED_DFS_H

#ifndef STACK_H
#include "stack.h"
#endif

#ifndef DIGRAPH_H
#include "digraph.h"
#endif

typedef struct Directed_DFS * Directed_DFS;
struct Directed_DFS {
  int *marked;
};

void init_dfs_directed(Directed_DFS *d_dg, Digraph dg) {
  Directed_DFS p_d_dg = malloc(sizeof(struct Directed_DFS));
  p_d_dg->marked = malloc(dg->V * sizeof(int));
  for (int i = 0; i < dg->V; i++) {
    p_d_dg->marked[i] = 0;
  }
  *d_dg = p_d_dg;
}

void df_search_directed(Directed_DFS d_dg, Digraph dg, int v) {
  d_dg->marked[v] = 1;
  for (Ints_Bag bg = dg->adj[v]; bg != NULL; bg = bg->next) {
    int w = bg->v;
    if (!d_dg->marked[w]) {
      df_search_directed(d_dg, dg, w);
    }
  }
}

int is_marked_df_directed(Directed_DFS d_dg, int v) {
  return d_dg->marked[v];
}
#endif
