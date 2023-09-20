#pragma once
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <map>
#include <limits>

using std::vector;
using std::queue;
using std::priority_queue;
using std::map;
using std::pair;
using std::enable_if_t;
#define Assert(cond, msg) ((cond) ?: (perror(msg), exit(1), 0))

const int defaultSize = 10;

const int INFINITY = 9999;

void printout(int &v){
  printf("printout vertex: %d\n",v);
}

template <typename E, typename Comp>
class heap{
private:
  struct helper{
    bool operator()(const E& a, const E& b){
      return Comp::prior(a,b);
    }
  };
  priority_queue<E,vector<E>,helper> h;
public:
  heap(E* _h, int _num, int _max){
    for(int i = 0; i < _num; i++)
      h.push(_h[i]);
  }
  int size(){return h.size();}
  E removefirst(){
    E t = h.top();
    h.pop();
    return t;
  }
  void insert(E e){
    h.push(e);
  }
};

template <typename E>
class Queue {
private:
  queue<E> q;

public:

  void clear() {q = queue<E>{}; } // Reinitialize

  void enqueue(const E& it) {     // Put "it" in queue
    q.push(it);
  }

  E dequeue() {           // Take element out
    E t = q.back();
    q.pop();
    return t;
  }

  const E& frontValue() const {  // Get front value
    return q.front();
  }

  virtual int length() const         // Return length
   { return q.size(); }
};


template <typename E>
class List {
 private:
  vector<E> l;
  typename vector<E>::iterator curr;  // Access to current element

  void removeall() {  // Return link nodes to free store
    l.clear();
  }

 public:
  void clear() { l.clear(); }  // Clear list

  // Insert "it" at current position
  void insert(const E& it) { l.insert(curr, it); }

  void append(const E& it) {  // Append "it" to list
    l.emplace_back(it);
  }

  // Remove and return current element
  E remove() {
    E t = *curr;
    l.erase(curr);
    return t;
  }

  void moveToStart()  // Place curr at list start
  {
    curr = l.begin();
  }

  void moveToEnd()  // Place curr at list end
  {
    curr = l.rbegin();
  }

  // Move curr one step left; no change if already at front
  void prev() { curr--; }

  // Move curr one step right; no change if already at end
  void next() { curr++; }

  int length() const { return l.size(); }  // Return length

  // Return the position of the current element
  int currPos() const { return curr - l.begin(); }

  // Move down list to "pos" position
  void moveToPos(int pos) { curr = l.begin() + pos; }

  E getValue() const {  // Return current element
    return *curr;
  }
};


// General tree representation for UNION/FIND
template<typename E, typename = std::enable_if_t<std::is_pod<E>::value>>
class UnionFind {
private:
  const E ROOT = std::numeric_limits<E>::max();
  map<E,E> m;
  E FIND(E curr) {
    if(m.find(curr) == m.end()) return curr;
    else return FIND_helper(curr);
  }
  E FIND_helper(E curr){
    if (m[curr] == ROOT) return curr;
    m[curr] = FIND(m[curr]);
    return m[curr];
  }
public:
  UnionFind(int _size){}
  void UNION(E a, E b){
    if(m.find(a) == m.end()) m.insert(pair<E,E>{a,ROOT});
    if(m.find(b) == m.end()) m.insert(pair<E,E>{b,ROOT});
    E root1 = FIND(a);
    E root2 = FIND(b);
    if (root1 != root2) m[root2] = root1;
    if (root1 != root2)  m[root2] = root1;
  }
  bool differ(E a, E b){
    E root1 = FIND(a);
    E root2 = FIND(b);
    return root1 != root2;
  }

};


using ParPtrTree = UnionFind<int>;