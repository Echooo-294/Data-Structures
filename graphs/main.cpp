#include <cstdlib>
#include <ctime>

#include "GrAlgorithm.hpp"
#include "Graph.hpp"
#include "Graphl.hpp"
#include "Graphm.hpp"
#include "GrTopsort.hpp"
#include "GrUtil.hpp"

struct PreVisit {
  PreVisit(Graph* G, int v) { printf("Before visit %d.\n", v); }
};

struct PostVisit {
  PostVisit(Graph* G, int v) { printf("After visit %d.\n", v); }
};

void demo1() {
  // Set graph size to 10
  const int size = 10;
  Queue<int> q;

  Graph* gl1 = new Graphl(size);
  Graph* gl2 = new Graphl(size);
  Graph* gl3 = new Graphl(size);
  Graph* gm1 = new Graphm(size);
  Graph* gm2 = new Graphl(size);
  Graph* gm3 = new Graphl(size);
  srand(time(NULL));
  auto rd = [&size]() -> int { return rand() % size; };
  // Generate gl and gm with 10 random edges
  for (int i = 0; i < 10; i++) {
    gl1->setEdge(rd(), rd(), rand());
    gl2->setEdge(rd(), rd(), rand());
    gl3->setEdge(rd(), rd(), rand());
    gm1->setEdge(rd(), rd(), rand());
    gm2->setEdge(rd(), rd(), rand());
    gm3->setEdge(rd(), rd(), rand());
  }
  // DFS and BFS
  printf("DFS:\n");
  DFS<PreVisit, PostVisit>(gl1, 0);
  printf("DFS:\n");
  DFS<PreVisit, PostVisit>(gm1, 0);
  printf("BFS:\n");
  BFS<PreVisit>(gl2, 0, &q); q.clear();
  printf("BFS:\n");
  BFS<PreVisit>(gm2, 0, &q);q.clear();
  printf("TSort:\n");
  topsort_ite(gl3,&q);q.clear();
  printf("TSort:\n");
  topsort_ite(gm3,&q);q.clear();
}

void demo2(){
  // Set graph size to 10
  const int size = 5;
  Queue<int> q;

  Graph* g1 = new Graphl(size);
  Graph* g2 = new Graphm(size);
  const int n_edge = 6;
  int from[n_edge]  = {0,1,2,3,0,4};
  int to[n_edge]    = {1,2,3,0,2,0};
  int w[n_edge]     = {2,1,4,1,2,1};
  for (int i = 0; i < n_edge; i++) {
    g1->setEdge(from[i], to[i], w[i]);
    g2->setEdge(from[i], to[i], w[i]);
  }
  int D1[g1->n()];
  int D2[g1->n()];
  for (int i=0; i<g1->n(); i++) {     // Initialize
    D1[i] = INFINITY;
    D2[i] = INFINITY;
  }
  D1[0] = 0;
  D2[0] = 0;

  printf("Dijkstra1:\n");
  Dijkstra1(g1, D1, 0);
  for(int i = 0 ; i < g1->n(); i++){
    if(D1[i] == INFINITY)
      printf("INF");
    else
      printf("%d ",D1[i]);
  }
  printf("\n");

  printf("Dijkstra2:\n");
  Dijkstra2(g2, D2, 0);
  for(int i = 0 ; i < g1->n(); i++){
    if(D2[i] == INFINITY)
      printf("INF");
    else
      printf("%d ",D2[i]);
  }
  printf("\n");
}

void demo3(){
  const int size = 5;
  Graph* g1 = new Graphl(size);
  Graph* g2 = new Graphm(size);
  Graph* g3 = new Graphl(size);
  int D1[g1->n()];
  int D2[g2->n()];

  const int n_edge = 6;
  int from[n_edge]  = {0,1,2,3,0,4};
  int to[n_edge]    = {1,2,3,0,2,0};
  int w[n_edge]     = {2,1,4,1,2,1};
  for (int i = 0; i < n_edge; i++) {
    g1->setEdge(from[i], to[i], w[i]);
    g2->setEdge(from[i], to[i], w[i]);
  }
  for (int i=0; i<g1->n(); i++) {     // Initialize
    D1[i] = INFINITY;
    D2[i] = INFINITY;
  }
  D1[0] = 0;
  D2[0] = 0;

  printf("\nPrim1:\n");
  Prim1(g1, D1, 0);
  printf("\nPrim2:\n");
  Prim2(g2, D2, 0);
}

void demo4(){
  const int size = 10;
  Graph* g = new Graphl(size);

  srand(time(NULL));
  auto rd = [&size]() -> int { return rand() % size; };
  // Generate g1 and g2 with 10 random edges
  for (int i = 0; i < 10; i++) {
    g->setEdge(rd(), rd(), rand());
  }

  printf("\nKruskel\n");
  Kruskel(g);
}

int main(){
  demo1();
  demo2();
  demo3();
  demo4();
  return 0;
}