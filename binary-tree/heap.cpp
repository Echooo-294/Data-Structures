#include<string>
#include<cstring>
#include<iostream>
#include<assert.h>
using namespace std;

template<typename E>
void swap(E* e, int i, int j)
{
	E tmp = e[i];
	e[i] = e[j];
	e[j] = tmp;
}

//以下为Comp示例，其作为比较器传入两个类对象的值实现排序，对Comp重写可改变堆中的排序方式
//E类作为示范，用以演示下图Comp用法
/*class E
{

private:
	int id;
};
template <typename E>
class Comp
{
	static bool prior(E a, E b)
	{
		//以前文最大堆为例，传入两个E类对象a、b，若对于某个属性a比b大则直接返回
		return a.id > b.id;
	}
};*/


//堆类，以下实现为最大堆，要改变其堆排序方式可通过修改Comp的定义
//注意：根结点编号记为0，从0开始算起
template<typename E, typename Comp>class heap {
private:
	//堆中元素数组，用指针实现
	E* Heap;
	//堆能容纳的最大结点个数
	int maxsize;
	//目前堆里的结点个数
	int n;
	//下滤，调整儿子结点与父结点的顺序保证关系
	void siftdown(int pos)
	{
		while (!isLeaf(pos)) {
			int j = leftchild(pos);
			int rc = rightchild(pos);
			if (rc < n && Comp::prior(Heap[rc], Heap[j]))//Comp为比较器，此处是Heap[rc]大于Heap[j]的情况
			{
				j = rc;
			}
			if (Comp::prior(Heap[pos], Heap[j]))return;//因为最大堆，若pos结点比其两个儿子结点中的最大值还大直接返回
			swap(Heap, pos, j);//不返回则说明父节点比最大儿子结点还小，此时交换
			pos = j;//将pos移至原父节点其儿子结点位置
		}
	}

public:
	//堆的初始化，将h赋给堆的入口Heap
	heap(E* h, int num, int max)
	{
		if (h == NULL)Heap = new E[max];
		else Heap = h;
		n = num;
		maxsize = max;
	}
	//堆的无参初始化，默认堆大小为500
	heap()
	{
		Heap = new E[500];
		maxsize = 500;
		n = 0;
	}
	//返回堆当前结点个数
	int size() const
	{
		return n;
	}
	//判断某个位置的结点是否为叶子结点，堆中最下层叶子编号大于等于n/2和小于等于n，pos为结点编号位置
	bool isLeaf(int pos) const
	{
		return pos >= n / 2 && pos < n;
	}
	//返回某个编号结点左儿子结点的编号
	int leftchild(int pos)
	{
		return 2 * pos + 1;
	}
	//返回某个编号结点右儿子结点的编号
	int rightchild(int pos)
	{
		return 2 * pos + 2;
	}
	//返回某个编号结点父结点的编号
	int parent(int pos)
	{
		return (pos - 1) / 2;
	}
	//规范堆的操作，即保证每个儿子结点与其父节点的关系一致
	void buildHeap()
	{
		//从倒数第二层最后一位开始下滤，保证每一次都能够把大结点换在父结点中，i倒数能够保证整个过程结束时根节点最大
		for (int i = n / 2 - 1; i >= 0; i--)siftdown(i);
	}
    //查询操作，返回堆中第pos个元素
    E get(int pos)
    {
        if(pos<0||pos>=n)
        {
			cout << "Error." << endl;
		}
        assert(pos>=0&&pos<n);
        else return Heap[pos];
    }
	//插入操作，将元素it加入到堆中
	void insert(const E& it)
	{
		//若n大于等于maxsize（一般情况下不会出现大于），则堆是满的情况，直接返回
		if (n >= maxsize)
		{
			cout << "Heap is full." << endl;
			return;
		}
		//当前最后新加进来的位置编号为n，同时堆中元素个数自增1
		int curr = n++;
		//将新元素加到末尾
		Heap[curr] = it;
		//上滤，保证父结点比儿子结点大，因为堆在插入之前是已经排好序的所以新插入的结点不需要考虑与兄弟结点比较大小
		while (curr != 0 && (Comp::prior(Heap[curr], Heap[parent(curr)])))
		{
			swap(Heap, curr, parent(curr));
			//若新插入的子结点上滤导致其上层的儿子结点比父结点还大，则需要不断向上比较
			curr = parent(curr);
		}
	}
	//移除头结点操作
	E removefirst()
	{
		//若n小于等于maxsize（一般情况下不会出现小于），则堆是空的情况
		if (n <= 0)
		{
			cout << "Heap is empty." << endl;
		}
		assert(n > 0);
		//将根节点与最后的结点交换，同时堆中结点数量自减1
		swap(Heap, 0, --n);
		//下滤根结点
		if (n != 0)
		{
			siftdown(0);
		}
		//返回值为已经调换到原来n-1位置的结点值，又此时n已经完成自减返回Heap[n]就行
		return Heap[n];
	}
	//移除特定位置结点操作
	E remove(int pos)
	{
		//若pos位置在0-(n-1)之外则越界
		if (!((pos >= 0) && (pos < n)))
		{
			cout << "Bad position." << endl;
		}
		assert((pos >= 0) && (pos < n));
		//如果是最末尾的结点则数量直接减1，函数最后直接返回Heap[n]
		if (pos == n - 1)
		{
			n--;
		}
		else
		{
			//将目标节点与最后的结点交换，同时堆中结点数量自减1
			swap(Heap, pos, --n);
			//上滤，保证父结点比儿子结点大，其过程与插入操作的最后几步基本一致
			while (pos != 0 && (Comp::prior(Heap[pos], Heap[parent(pos)])))
			{
				swap(Heap, pos, parent(pos));
				pos = parent(pos);
			}
			//目标节点下滤，调整关系
			if (n) { siftdown(pos); }
			//将调换结点返回
			return Heap[n];
		}
	}
};