//swap模板函数，用以交换一个数组中的两个对象
template<typename E>
void swap(E*& e, int i, int j)
{
	E tmp = e[i];
	e[i] = e[j];
	e[j] = tmp;
}
//插入排序
template<typename E,typename Comp>
void InsertSort(E*& A, int n)
{
	for (int i = 1; i < n; i++)
	{
		//此处以从高到低举例
		for (int j = i;(j > 0) && Comp::prior(A[j], A[j - 1]); j--)
		{
			//若A[j]一直大于A[j-1]，则需要不断将其与其前元素进行交换
			swap(A, j, j - 1);
		}
		
	}
}

//冒泡排序
template<typename E, typename Comp>
void BubbleSort(E*& A, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = n - 1; j > i; j--)
		{
			//若A[j]和A[j-1]满足某种关系，比如大于关系时需要交换则此时插入排序是从大到小排的
			if (Comp::prior(A[j], A[j - 1]))
				swap(A, j, j - 1);
		}
	}
}

//选择排序
template<typename E, typename Comp>
void SelectSort(E*& A, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int lowindex = i;
		for (int j = n - 1; j > i; j--)//经过从后往前的遍历找出最大或最小元素的索引值index
		{
			if (Comp::prior(A[j], A[lowindex]))//若A[j]和A[j-1]满足某种关系，比如大于关系时需要交换则此时插入排序是从大到小排的
				lowindex = j;
		}swap(A, i, lowindex);//将最大或最小元素与每轮迭代最起始的元素进行交换，若i==index则交换本身进入下一循环
	}
}