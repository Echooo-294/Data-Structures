#include<iostream>
using namespace std;
//首先要了解希尔排序方式，分段数*每一段数据数量=长度n，一段中两数之间间隔为段数
template<class Elem>
void inssort2(Elem A[], int n, int from, int incr)//希尔排序的段内排序部分，A[]为待排序数组，from为数组内所选起点，incr用来读取当前段的下一个数据
{
	for (int i = from + incr; i < n; i += incr)//使用插入排序法，从小到大排序段内数据
		for (int j = i; (j > from&& A[j] < A[j - incr]); j -= incr)
			swap(A[j], A[j - incr]);//vs自带函数，交换两个参数的值，较原代码有小幅度修改
}

template<class Elem>
void shellsort(Elem A[], int n)//希尔排序的分段部分，A[]为待排序数组，n为数组长度
{
	for (int i = n / 2; i >= 1; i /= 2)//i表示分段的数量，每一次分前次数量的1/2取整
		for (int j = 0; j < i; j++)//j用来遍历每一段数据，此时i表示最后一段，所以下方的inssort2函数以i为incr
			inssort2<Elem>(A, n, j, i);//for循环嵌套和inssort2函数保证每次分段的每一段都被排序到
}

int main()//main函数中以int类型数据为例
{
	int A[1000], data;//开辟一个足够空间的数组，以data为暂存输入数的对象
	int i = 0;//计数器，用来计算长度
	while (cin >> data)
	{
		A[i] = data;//向数组中依次存入输入数据
		i++;//每输入一个数，长度+1
		if (cin.get() == '\n') break;//当换行，结束输入
	}
	shellsort<int>(A, i);//调用shellsort函数排序
	for (int j = 0; j < i; j++)//输出排序好的数组
		cout << A[j] << " ";
}

//实验数据
//36 20 11 13 28 14 23 15 59 98 17 70 65 41 42 83