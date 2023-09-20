#include "heap.hpp"
#include <cstdlib>
#include <ctime>

struct int_comp{
    static bool prior(int a, int b){
        return a<b;
    }
};

template <typename E, typename Comp>
void heapsort(E A[], int n) {
    E maxval;
    heap<E,Comp> H(A,n);
    for(int i = 0;i<n;i++){
        maxval = H.removefirst();
        printf("%d\n",maxval);
    }
}

int main(){
    int a[100];
    srand(time(NULL));
    for(int i = 0;i<100;i++){
        a[i] = rand();
    }
    const int size = sizeof(a)/sizeof(int);
    heapsort<int,int_comp>(a,size);
    return 0;
}