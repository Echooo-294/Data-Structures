#pragma once
#include "GrUtil.hpp"
#include "Graph.hpp"

void AddEdgetoMST(int v1, int v2) {
  printf("Add edge %d to %d\n",v1,v2);
}

int minVertex(Graph* G, int* distance_of) { // Find min cost vertex
  int i, v = -1;
  for (i=0; i<G->n(); i++) // Initialize v to some unvisited vertex;
    if (G->getMark(i) == UNVISITED) { v = i; break; }
  for (i=0; i<G->n(); i++)  // Now find smallest value
    if ((G->getMark(i) == UNVISITED) && (distance_of[i] < distance_of[v])) v = i;
  return v;
}

void Prim1(Graph* G, int* distance_of, int s) { // Prim's MST algorithm
  int V[G->n()];                     // Store closest vertex
  int i, w;
  for (i=0; i<G->n(); i++) {         // Process the vertices
    int v = minVertex(G, distance_of);
    G->setMark(v, VISITED);
    if (distance_of[v] == INFINITY) return;    // Unreachable vertices
    // 上面这句话不能放在AddEdgetoMST后面，因为当不连通时，那个INFINITY的点对应的V[v]是没初始化的。
    if (v != s)
      AddEdgetoMST(V[v], v);         // Add edge to MST
    for (w=G->first(v); w<G->n(); w = G->next(v,w))
      if (distance_of[w] > G->weight(v,w)) {
        distance_of[w] = G->weight(v,w);       // Update distance
        V[w] = v;                    // Where it came from
      }
  }
}


// class DijkElem {
// public:
//   int vertex, distance;
//   DijkElem() { vertex = -1; distance = -1; }
//   DijkElem(int v, int d) { vertex = v; distance = d; }
// };

// // Comparator class for comparing DijkElem's
// class DDComp {
// public:
//   static bool prior(DijkElem x, DijkElem y)
//     { return x.distance < y.distance; }
// };

// // Prim's MST algorithm: priority queue version
// void Prim2(Graph* G, int* D, int s) {
//   int i, v, w;           // "v" is current vertex
//   int V[G->n()];         // V[I] stores I's closest neighbor
//   DijkElem temp;
//   DijkElem E[G->e()];    // Heap array with lots of space
//   temp.distance = 0; temp.vertex = s;
//   E[0] = temp;           // Initialize heap array
//   heap<DijkElem, DDComp> H(E, 1, G->e()); // Create heap
//   for (i=0; i<G->n(); i++) {           // Now build MST
//     do {
//       if(H.size() == 0) return; // Nothing to remove
//       temp = H.removefirst();
//       v = temp.vertex;
//     } while (G->getMark(v) == VISITED);
//     G->setMark(v, VISITED);
//     if (v != s) AddEdgetoMST(V[v], v); // Add edge to MST
//     if (D[v] == INFINITY) return;      // Ureachable vertex
//     for (w=G->first(v); w<G->n(); w = G->next(v,w))
//       if (D[w] > G->weight(v, w)) {    // Update D
//         D[w] = G->weight(v, w);
//         V[w] = v;        // Update who it came from
//         temp.distance = D[w]; temp.vertex = w;
//         H.insert(temp);  // Insert new distance in heap
//       }
//   }
// }
struct Node {
  int v, dis;
};

struct Comp_{
    bool operator()(Node d1,Node d2){
        return d1.dis < d2.dis;
    }
};

// Prim's MST algorithm: priority queue version
void Prim2(Graph* G, int* distance_to, int s) {
  int i, v, w;
  int n = G->n();
  int source_of[n];
  priority_queue<Node,vector<Node>, Comp_> q;

  q.push(Node{s,0});

  for (i=0; i<n; i++) {

    L:
      if(q.empty()) return;
      v = q.top().v; // 把v从q里pop出来
      q.pop();
    if (G->getMark(v) == VISITED) goto L; // 这个queue里可能有重复的节点。因为下面那个更新的没有管q里先前有没有相同的。
    // 但这并不影响，因为近的那个总是在前面；而访问到那个被淘汰的相同节点的时候，这个节点是VISITED的，就跳过去了。

    G->setMark(v, VISITED); // 对这个v打个VISITED标记

    if (v != s) AddEdgetoMST(source_of[v], v); // 汇报成果
    if (distance_to[v] == INFINITY) return;      // 这图已经是最大生成子图了

    for (w=G->first(v); w<n; w = G->next(v,w)){ // 如果发现v到它邻居的距离对我们有益，就更新一下
      auto weight = G->weight(v,w);
      if ( weight < distance_to[w] ) {
        distance_to[w] = weight;
        source_of[w] = v;
        q.push(Node{w,weight});
      }

    }

  }
}


// Simple class to store data in the heap: edge and its distance
class KruskElem {         // An element for the heap
public:
  int from, to, distance; // The edge being stored
  KruskElem() { from = -1;  to = -1; distance = -1; }
  KruskElem(int f, int t, int d)
    { from = f; to = t; distance = d; }
};

// Comparator to compare two KruskElem's
class Comp {
public:
  static bool prior(KruskElem x, KruskElem y)
    { return x.distance < y.distance; }
};

void Kruskel(Graph* G) {   // Kruskal's MST algorithm
  ParPtrTree A(G->n());    // Equivalence class array
  KruskElem E[G->e()];     // Array of edges for min-heap
  int i;
  int edgecnt = 0;
  for (i=0; i<G->n(); i++) // Put the edges on the array
    for (int w=G->first(i); w<G->n(); w = G->next(i,w)) {
      E[edgecnt].distance = G->weight(i, w);
      E[edgecnt].from = i;
      E[edgecnt++].to = w;
    }
  // Heapify the edges
  heap<KruskElem, Comp> H(E, edgecnt, edgecnt);
  int numMST = G->n();       // Initially n equiv classes
  for (i=0; numMST>1; i++) { // Combine equiv classes
    KruskElem temp;
    if(H.size() == 0) break; // 书上没有这句。但没有这句的话，当G不连通时就会死循环了，因为numMST总不为1！
    temp = H.removefirst(); // Get next cheapest edge
    int v = temp.from;  int u = temp.to;
    if (A.differ(v, u)) {  // If in different equiv classes
      A.UNION(v, u);       // Combine equiv classes
      AddEdgetoMST(temp.from, temp.to);  // Add edge to MST
      numMST--;            // One less MST
    }
  }
}