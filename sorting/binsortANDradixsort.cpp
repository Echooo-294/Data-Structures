#include<iostream>
#include<cstdio>
#include<queue>

using namespace std;


// binsort,也即bucketsort,中文常称桶排序,排序对象为整数(且通常为非负)
// 单独使用的时候采取计数为宜,即:每个桶为一个数字,记录桶中元素个数.或者采取链的形式(这一点可以在radixsort中应用)
// a为待排序数组,n为数组长度
// 这个是一个计数版本的binsort
template <typename E>
void binsort(E *a,int n){
    int *bin;E MaxValue;                                 //bin为桶,而m则表示其所能表示的范围
    for(int i=0;i<n;i++) MaxValue=max(MaxValue,a[i]);         

    bin = new int[MaxValue+1];
    memset(bin,0,sizeof(int)*(MaxValue+1));            //开桶后清空
    
    for(int i=0;i<n;i++) ++bin[a[i]];           //将a[]的元素分配到桶中

    int x=0;
    for(E i=0;i<=MaxValue;i++){
        while(bin[i]) a[x++]=i,--bin[i];                 //将bin[]中的数据收集回到a[]中
    }

    delete[] bin;
}

// extend binsort,可以用来作为radixsort的前置
// 书上的版本,一个bin装若干个元素
template<typename E,class getKey>
void exbinsort(E A[],int n,int MaxKeyValue){
    queue<E> Bin[MaxKeyValue];                  //自己写一下队列也挺快的,这里就不造轮子了.
  
    for(int i=0;i<n;i++){
        Bin[getKey::key(A[i],MaxKeyValue)].push(A[i]);      //插入对应的桶中
    }
    
    int x=0;
    for(int i=0;i<MaxKeyValue;i++){
        while(!Bin[i].empty()) A[x++]=Bin[i].front(),Bin[i].pop();      //将桶中的数据收集起来
    }
}

// 为了配合书上的getkey类,若有其它需求,比如将一个特殊的struct排序就在这里加入返回值就行.
class get{
public:
    static int key(int it) {return it;}
    static int key(long long it) {return it;}
    static int key(unsigned it) {return it;}
    static int key(unsigned long long it) {return it;}
};


// 当r为10的时候便于理解思路,按个位、十位、百位...的顺序逐位排序就容易理解了,然后推广到不同的位(进制)w
// 复杂度:时间是O(nlogn/logw);空间是O(n+w),也即O(n)
template<typename E,class getKey>
void radixsort(E A[],int n,int r,int MaxKeyValue){
    for(int rtoi=1;rtoi<MaxKeyValue;rtoi*=r){
        queue<E> Bin[r];

        for(int i=0;i<n;i++){
            Bin[getKey::key(A[i])/rtoi%r].push(A[i]);               //同binsort一样,分配进入不同的桶
        }
        
        int x=0;
        for(int i=0;i<r;i++){
            while(!Bin[i].empty()) A[x++]=Bin[i].front(),Bin[i].pop();      //再收集起来
        }

    }
    // 或者按书上的方式来,这只是细节的差异.效率差不多,甚至书上的还多了个cnt[]数组,浪费了一些空间还显得很麻烦
    /* 
    int cnt[maxn];int j;
    E B[maxn];
    for(int i=0,rtoi=1;i<k;i++,rtoi*=r){
        for(j=0;j<r;j++) cnt[j]=0;      //initialize cnt

        for(j=0;j<n;j++) cnt[getKey::key(A[j])/rtoi%r]++; //count the number of records for each bin on this pass

        for(j=1;j<r;j++) cnt[j] = cnt[j-1] + cnt[j];    //by counting the sum,cnt[j] will be index for last slot of Bin

        for(j=n-1;j>=0;j--) B[--cnt[getKey::key(A[j])/rtoi%r]] = A[j] //put records into B[]
    
        for(j=0;j<n;j++) A[j]=B[j];     //copy B back to A
    }
    */
}

int main(){
    const int maxn=1e5+3;
    int n;int a[maxn];
    int radix=10,Maxnum=100000;
    while(cin>>n){
        for(int i=0;i<n;++i) cin>>a[i];
        radixsort<int,get>(a,n,radix,Maxnum);

        for(int i=0;i<n;++i) cout<<a[i]<<" \n"[i==n-1];
    }
}
/*
test_data:
10
1 41 53 77 57 34 43 98 78 19
*/