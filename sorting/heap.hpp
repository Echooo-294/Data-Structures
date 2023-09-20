#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <functional>
#include <assert.h>

const int MAXSIZE = 1024;
typedef int RET_CODE;

// Max Heap
template <typename E,typename Comp>
class heap{
    private:
    E h[MAXSIZE];
    int n;
    bool is_leaf(int pos){return(pos<n/2)?false:true;}
    int parent(int pos){return (pos-1)/2;}
    int left_child(int pos){return 2*pos+1;}
    int right_child(int pos){return 2*pos+2;}
    void swap(E* h, int lhs, int rhs){E t;t = h[lhs];h[lhs] = h[rhs];h[rhs] = t;}
    RET_CODE sink(int pos){
        while(!is_leaf(pos)){
            int j = left_child(pos);
            int rc = right_child(pos);
            if(rc<n && Comp::prior(h[rc],h[j])) j = rc;
            if(Comp::prior(h[j], h[pos])) swap(h,pos,j); else return 0;
            pos = j;
        }
        return 0;
    }
    int rise(int pos){
        while(pos!=0 && Comp::prior(h[pos], h[parent(pos)])){
            swap(h,pos,parent(pos));
            pos = parent(pos);
        }
        return pos;
    }

    public:
    heap(E _h[],int _n){
        if(_n<=MAXSIZE){
            n = _n;
            memcpy(h,_h,_n*sizeof(E));
            build();
        }
    }
    heap(){
            n = 0;
            //build();
    }
    int get_size() const{return n;}
    RET_CODE build(){
        for(int i = n/2 - 1; i>=0; --i) sink(i);
        return 0;
    }
    RET_CODE insert(E node){
        if(n == MAXSIZE) return 1;
        int curr = n++;
        h[curr] = node;
        rise(curr);
        return 0;
    }
    E take(int pos){
        assert((pos >=0) && (pos <n));
        E value = h[pos];
        if(pos == n-1){n--;return value;}
        else{
            h[pos] = h[--n];
            pos = rise(pos);
            if(n!=0) sink(pos);
            return value;
        }
    }
    E removefirst(){
        return take(0);
    }
};


#endif