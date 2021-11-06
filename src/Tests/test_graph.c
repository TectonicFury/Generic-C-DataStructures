#include "../includes/vertex_indexed_graph.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
  // Graph g = init_graph(10, 45);
  // printf("g->size = %d\n", g->V);
  // add_edge(g, 1, 2);
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
  return 0;
}
