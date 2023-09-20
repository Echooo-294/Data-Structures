#include<assert.h>
#include<iostream>
using namespace std;

int defaultSize=9999;
template<typename E>
class Queue//基类
{
private:
	void operator =(const Queue&){}
	Queue(const Queue&){}

public:
	Queue(){}
	virtual ~Queue(){}
	virtual void clear(){}
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

template <typename E>
class AQueue :public Queue<E>
{
private:
	int maxSize;//数组长度
	int front;//当前队列首元素的位置
	int rear; //当前队列尾元素的位置
	E* listArray;//指向存放队列元素数组的指针
public:
	//构造函数
	AQueue(int size = defaultSize)//defaultSize是满队列时队列储存的元素数目
	{
		maxSize = size + 1;//数组的长度是maxSize
		rear = 0;//初始化赋值，因为队列是从尾部插进去，即插入rear所在位置，所以初始化rear=0
		front = 1;
		listArray = new E[maxSize];//listArray是队列储存元素数目+1是因为空队列和满队列时front等于rear的值（因为是一个圈的轮回），
									//所以+1就可以区分出两种情况
	}
	//析构函数
	~AQueue()
	{
		delete[]listArray;
	}
	//清空函数
	void clear()//回到初始化赋值
	{
		rear = 0;
		front = 1;
	} 
	//插入尾部元素函数
	void enqueue(const E& it)
	{
		Assert((((rear + 2) % maxSize)-front )!=0 , "Queue is full");//判断队列数目是否已经满了，+2是环是因为从0开始计数的
		rear = (rear + 1) % maxSize;//队列有空余位置时将队列尾元素位置指向下一个位置
		listArray[rear] = it;//上一步已经指向下一个位置了，即当前rear位置是空的，存进该值
	}
	//删除头部元素函数
	E dequeue()
	{
		Assert(length() != 0, "Queue is empty");//队列长度为0，说明没存元素，即为空队列
												//如果不为空队列时，才进行删除（实际上是将首元素位置指向下一个位置，即相当于直接忽略掉要删除的元素）
		E it = listArray[front];
		front = (front + 1) % maxSize;//删除队列首元素，即front指向下一个元素
		return it;//返回删除的首元素的值
	}
	//返回队列首位置元素
	const E& frontValue()const
	{
		Assert(length() != 0, "Queue is empty");//队列长度为0，说明没存元素，即为空队列
		return listArray[front];//如果不为空队列时，返回队列首元素位置的元素数值
	}
	//返回队列长度函数
	virtual int length()const
	{
		return((rear + maxSize) - front + 1) % maxSize;//不能直接rear-front+1是因为这是一个环，有可能rear的位置比front的位置要前
														//（即像时钟从12点前跳到12点后，经过了一个跨越）
	}
};

int main()
{

	return 0;
	system("pause");
}
