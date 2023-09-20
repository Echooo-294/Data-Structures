#include<iostream>
#include<cstdio>

using namespace std;

//std
//复杂度分析:
// 1.时间复杂度,递归共logn层.每一层都有O(n),即n/w+n/w+...+n/w=n/w*w=n. 故而总的时间复杂度就是O(nlogn)
// 2.空间复杂度,两个数组,O(n)
//A是待排序数组,temp[]是余出来的临时数组,[left,right]是递归的子区间,cmp是比较函数
template <typename E,typename Comp>
void mergesortstd(E A[], E temp[], int left, int right, Comp cmp){      
    if(left==right) return;                                             //如果这个数组长度为1则已然有序,直接返回即可

    int mid=(left+right)/2;
    mergesortstd<E,Comp>(A, temp, left, mid, cmp);      
    mergesortstd<E,Comp>(A, temp, mid+1, right, cmp);                   //直接递归下一层

    for(int i=left; i<=right; i++)                                      //此时A[]的[left,mid]和[mid+1,right]两个子区间已经分别有序
        temp[i]=A[i];                                                   //复制数据到temp[]数组中
    
    int i1=left, i2=mid+1;
    for(int curr=left; curr<=right; curr++){                            //这个循环合并A[]的两个有序的子区间
        if(i1==mid+1) 
            A[curr] = temp[i2++];                                       //如果左半边被用完了,就直接从右半边拿
        else if(i2 > right)
            A[curr] = temp[i1++];                                       //同理右半边被用完了,就直接从左半边拿
        
        else if(cmp(temp[i1], temp[i2]))                                //没有唯一选择的时候就判断哪个优先选择
            A[curr] = temp[i2++];
        else A[curr] = temp[i1++];                              
    }
}




//测试用main()函数中,先输入一个n表示数组长度,然后输入n个数.输出增序数组
const int maxn=1e5+3;
int main(){
    int n;
    int a[maxn],tmp[maxn];
    while(cin>>n){
        for(int i=1;i<=n;++i){
            cin>>a[i];
        }
        mergesortstd(a, tmp, 1, n, greater<int>() );

        for(int i=1;i<=n;++i){
            cout<<a[i]<<" \n"[i==n];
        }
    }
}
/*
test_data:
5
1 4 5 2 3
*/