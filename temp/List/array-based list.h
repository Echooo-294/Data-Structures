//用数组实现顺序表
#include<iostream>
using namespace std;
template<typename Elem>
class List
{
public:
	virtual void Clear() = 0;
	virtual bool getValue(Elem& x) = 0;
	virtual int getSize() = 0;
	virtual bool setPos(int pos) = 0;
	virtual int getPos() = 0;
	virtual bool Prev() = 0;
	virtual bool Next() = 0;
	virtual bool Insert(Elem x) = 0;
	virtual bool Remove(Elem& x) = 0;
	virtual void swap(Elem& a, Elem& b) = 0;
	virtual void Sort(int choice) = 0;
	virtual void Print() = 0;
};
template<typename Elem>
class ArrayList :public List<Elem>
{
public:
	ArrayList(int ms);
	~ArrayList();
	void Clear();
	bool getValue(Elem& x);
	int getSize() { return size; }
	bool setPos(int pos);
	int getPos() { return fence; }
	bool Prev();
	bool Next();
	bool Insert(Elem x);
	bool Remove(Elem& x);
	void swap(Elem& a, Elem& b);
	void Sort(int choice);
	void Print();
private:
	Elem* array;
	int maxsize;
	int size;
	int fence;
};
template<typename Elem>
ArrayList<Elem>::ArrayList(int ms)
{
	maxsize = ms;
	array = new Elem[maxsize];
	fence = size = 0;
}
template<typename Elem>
ArrayList<Elem>::~ArrayList()
{
	delete[]array;
	array = nullptr;
}
template<typename Elem>
void ArrayList<Elem>::Clear()
{
	fence = size = 0;//只需要视为空即可
}
template<typename Elem>
bool ArrayList<Elem>::getValue(Elem& x)
{
	if (fence == size) //如果当前指针处于size位置则访问失败
		return 0;
	else
	{
		x = array[fence];
		return 1;
	}
}
template<typename Elem>
bool ArrayList<Elem>::setPos(int pos)
{
	if (pos <= size && pos >= 0)
	{
		fence = pos;//下标都是从0算起
		return 1;
	}
	else
		return 0;
}
template<typename Elem>
bool ArrayList<Elem>::Prev()
{
	if (fence == 0)
		return 0;
	else
	{
		fence--;
		return 1;
	}
}
template<typename Elem>
bool ArrayList<Elem>::Next()
{
	if (fence == size)
		return 0;
	else
	{
		fence++;
		return 1;
	}
}
template<typename Elem>
bool ArrayList<Elem>::Insert(Elem x)//此处不需要传引用参数，在fence处插入
{
	if (size == maxsize)
		return 0;
	else
	{
		for (int j = size - 1; j >= fence; j--)
		{
			array[j + 1] = array[j];
		}
		array[fence] = x;
		size++;
		return 1;
	}
}
template<typename Elem>
bool ArrayList<Elem>::Remove(Elem& x)//用一个参数记录删除掉的元素的值
{
	if (fence == size || size == 0) //如果当前指针处于size位置或表为空则访问失败
		return 0;
	else
	{
		x = array[fence];
		for (int j = fence; j < size - 1; j++)
		{
			array[j] = array[j + 1];
		}
		size--;
		return 1;
	}
}
template<typename Elem>
void ArrayList<Elem>::swap(Elem& a, Elem& b)
{
	Elem temp;
	temp = a;
	a = b;
	b = temp;
}
template<typename Elem>
void ArrayList<Elem>::Sort(int choice)//choice默认传0升序，传1降序
{
	bool work;
	for (int pass = 1; pass < size; pass++)//这里使用了冒泡排序，后续要改成快速排序
	{
		work = 1;
		for (int i = 0; i < size - pass; i++)
		{
			if (choice == 1)
			{
				if (array[i] < array[i + 1])
				{
					swap(array[i], array[i + 1]);
					work = 0;
				}
			}
			else //默认=0升序
			{
				if (array[i] > array[i + 1])
				{
					swap(array[i], array[i + 1]);
					work = 0;
				}
			}
		}
		if (work)
			break;
	}
}
template<typename Elem>
void ArrayList<Elem>::Print()
{
	for (int i = 0; i < size; i++)
	{
		if (i == fence)
			cout << "|";//把指针的位置也打印出来
		else if (i != 0)
			cout << ",";
		cout << array[i];
	}
	if (fence == size)
		cout << "|";
	cout << endl;
}