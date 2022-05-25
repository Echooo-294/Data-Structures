/*
	The description about the code.......
	---------Created by chencuilian
	---------Email or other contact method like QQ: 1926267819
*/
#if 0
#include<iostream>
#include<assert.h>
using namespace std;
int defaultSize = 9999;

template<typename E>
class Link//结点类
{
public:
	E element;
	Link* next;
	Link() {}//默认构造函数
	Link(E it, Link* l)//构造函数
	{
		element = it;
		next = l;
	}
};

template<typename E>
class Queue//基类
{
private:
	void operator =(const Queue&) {}
	Queue(const Queue&) {}

public:
	Queue() {}
	virtual ~Queue() {}
	virtual void clear() {}
	virtual void enqueue(const E&) = 0;
	virtual E dequeue() = 0;
	virtual const E& frontValue()const = 0;
	virtual int length()const = 0;
};

void Assert(int e, string s)//条件e返回错误，则终止程序执行
{
	assert(e);
	cout << s << endl;
}
/*
 队列front是NULL的状态，在下一个元素才储存值，
 队列为空时，rear==front
 插入时是直接插入rear的下一个位置
 首元素位置是front->next
*/

template<typename E>
class LQueue :public Queue<E>
{
private:
	Link<E>* front;//指向队列第一个结点
	Link<E>* rear;//指向队列最后一个结点
	int size;//队列元素个数
public:
	//构造函数
	LQueue(int sz = defaultSize)
	{
		front = rear = new Link<E>;
		size = 0;
	}
	//析构函数
	~LQueue()
	{
		clear();
		delete front;
	}
	//清空函数
	void clear()
	{
		while (front->next != NULL)//不为空即说明还没清空
		{
			rear = front;//从头开始删
			front = front->next;
			delete rear;
		}
		rear = front;//回到初始化状态
		size = 0;//将队列元素个数指令
	}
	//插入函数，插入队列尾部
	void enqueue(const E& it)
	{
		rear->next = new Link<E>(it, NULL);//在队尾插入新结点
		rear = rear->next;
		size++;//队列元素个数+1
	}
	//删除函数，删除队列首元素，返回首元素
	E dequeue()
	{
		Assert(size != 0, "Queue is empty");//判断是否是空队列
		E it = front->next->element;//为了返回删除元素做准备
		Link<E>* Itemp = front->next;
		if (rear == Itemp)//判断front->next是否是队尾，如果是，则直接将队首赋值给队尾，相当于回到初始化
			rear = front;
		delete Itemp;
		size--;
		return it;
	}
	//返回首元素的值
	const E& frontValue()const
	{
		Assert(size != 0, "Queue is empty");
		return front->next->element;
	}
	//返回队列长度
	virtual int length()const
	{
		return size;
	}
};

int main()
{
	return 0;
}
#endif