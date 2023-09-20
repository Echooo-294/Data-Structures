#include<iostream>
using namespace std;
//二分查找，针对数组结构，要求数据升序排列（降序排列同理更改）
int binary(int A[], int n, int K)
{
	int l = -1;
	int r = n;
	while (l + 1 != r)//当左标记在右标记左侧-1位置，查找结束
	{
		int i = (l + r) / 2;

		if (K == A[i])return i;//找到目标项，跳出函数，返回目标项下标
		if (K > A[i])l = i;//目标项大于目前项，将左标记移到目前项处，查找右半边，查找范围减半
		if (K <A[i])l = i;//目标项小于目前项，将右标记移到目前项处，查找左半边，查找范围减半
	}
	return n;//未找到目标项，返回n代表查找失败
}