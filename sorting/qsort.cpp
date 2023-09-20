#include <cstdlib>
#include <ctime>
#include <cstdio>

struct int_comp{
    static bool prior(int a, int b){
        return a<b;
    }
};

template <typename E>
void swap(E A[], int i, int j){
    E t = A[i];
    A[i] = A[j];
    A[j] = t;
}

template <typename E>
inline int findpivot(E A[], int i, int j)
{ return (i+j)/2; }

template <typename E, typename Comp>
inline int partition(E A[], int l, int r, E& pivot) {
    do{ // Move the bounds inward until they meet
        while(Comp::prior(A[++l],pivot));//Move l right and
        while((l<r)&&Comp::prior(pivot,A[--r])); // r left
        swap(A,l,r); //Swap out-of-place values
    } while(l<r); // Stop when they cross
    return l; // Return first position in right partition
}

template<typename E, typename Comp>
void qsort(E A[], int i, int j) { //Quicksort
    if(j<=i) return; //Don't sort 0 or 1 element
    int pivotindex = findpivot(A,i,j);
    swap(A,pivotindex,j); // Put pivot at end
    // k will be the first position in the right subarray
    int k = partition<E,Comp>(A,i-1,j,A[j]);
    swap(A,k,j); // Put pivot in place
    qsort<E,Comp>(A,i,k-1);
    qsort<E,Comp>(A,k+1,j);
}

int main(){
    int a[100];
    srand(time(NULL));
    for(int i = 0;i<100;i++){
        a[i] = rand();
    }
    const int size = sizeof(a)/sizeof(int);
    qsort<int,int_comp>(a,0,size);
    for(int i = 0;i<100;i++){
        printf("%d\n",a[i]);
    }
    return 0;
}