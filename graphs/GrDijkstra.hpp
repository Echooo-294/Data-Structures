#include "Graph.hpp"
#include "GrUtil.hpp"

int minVertex_(Graph* G, int* D) { // Find min cost vertex
  int i, v = -1;
  // Initialize v to some unvisited vertex
  for (i=0; i<G->n(); i++)
    if (G->getMark(i) == UNVISITED) { v = i; break; }
  for (i++; i<G->n(); i++)  // Now find smallest D value
    if ((G->getMark(i) == UNVISITED) && (D[i] < D[v]))
      v = i;
  return v;
}


// Compute shortest path distances from "s".
// Return these distances in "D".
void Dijkstra1(Graph* G, int* D, int s) {
  int i, v, w;
  for (i=0; i<G->n(); i++) {      // Process the vertices
    v = minVertex_(G, D);
    if (D[v] == INFINITY) return; // Unreachable vertices
    G->setMark(v, VISITED);
    for (w=G->first(v); w<G->n(); w = G->next(v,w))
      if (D[w] > (D[v] + G->weight(v, w)))
        D[w] = D[v] + G->weight(v, w);
  }
}

// Simple class to represent objects to be stored in the priority queue
// Store a vertex and its best known distance
class DijkElem {
public:
  int vertex, distance;
  DijkElem() { vertex = -1; distance = -1; }
  DijkElem(int v, int d) { vertex = v; distance = d; }
};

// Comparator class for comparing DijkElem's
class DDComp {
public:
  static bool prior(DijkElem x, DijkElem y)
    { return x.distance < y.distance; }
};

// Dijkstra's shortest paths algorithm with priority queue
void Dijkstra2(Graph* G, int* D, int s) {
  int i, v, w;            // v is current vertex
  DijkElem temp;
  DijkElem E[G->e()];     // Heap array with lots of space
  temp.distance = 0; temp.vertex = s;
  E[0] = temp;            // Initialize heap array
  heap<DijkElem, DDComp> H(E, 1, G->e()); // Create heap
  for (i=0; i<G->n(); i++) {         // Now, get distances
    do {
      if (H.size() == 0) return; // Nothing to remove
      temp = H.removefirst();
      v = temp.vertex;
    } while (G->getMark(v) == VISITED);
    G->setMark(v, VISITED);
    if (D[v] == INFINITY) return;    // Unreachable vertices
    for (w=G->first(v); w<G->n(); w = G->next(v,w))
      if (D[w] > (D[v] + G->weight(v, w))) { // Update D
        D[w] = D[v] + G->weight(v, w);
        temp.distance = D[w]; temp.vertex = w;
        H.insert(temp);   // Insert new distance in heap
      }
  }
}