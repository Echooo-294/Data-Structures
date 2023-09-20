#pragma once
#include "Graph.hpp"

template <typename PreVisit, typename PostVisit>
void DFS(Graph* G, int v) {
  PreVisit(G, v);
  G->setMark(v, VISITED);
  for (int w = G->first(v); w < G->n(); w = G->next(v, w))
    if (G->getMark(w) == UNVISITED) DFS<PreVisit, PostVisit>(G, w);
  PostVisit(G, v);
}