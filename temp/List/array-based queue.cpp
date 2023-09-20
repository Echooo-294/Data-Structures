// ������ʵ�ֶ���
#if 0
#include<iostream>
#include<assert.h>
using namespace std;

int defaultSize = 9999;
template<typename Elem>
class Queue
{
private:
	void operator =(const Queue&) {}
	Queue(const Queue&) {}

public:
	virtual void Clear() = 0;
	virtual void enqueue(const Elem&) = 0;
	virtual Elem dequeue() = 0;
	virtual const Elem& frontValue()const = 0;
	virtual int length()const = 0;
};

void Assert(int e, string s)//����e���ش�������ֹ����ִ��
{
	assert(e);
	cout << s << endl;
}

template <typename Elem>
class AQueue :public Queue<Elem>
{
private:
	int maxSize;//���鳤��
	int front;//��ǰ������Ԫ�ص�λ��
	int rear; //��ǰ����βԪ�ص�λ��
	Elem* listArray;//ָ���Ŷ���Ԫ�������ָ��
public:
	//���캯��
	AQueue(int size = defaultSize)//defaultSize��������ʱ���д����Ԫ����Ŀ
	{
		maxSize = size + 1;//����ĳ�����maxSize
		rear = 0;//��ʼ����ֵ����Ϊ�����Ǵ�β�����ȥ��������rear����λ�ã����Գ�ʼ��rear=0
		front = 1;
		listArray = new Elem[maxSize];//listArray�Ƕ��д���Ԫ����Ŀ+1����Ϊ�ն��к�������ʱfront����rear��ֵ����Ϊ��һ��Ȧ���ֻأ���
									//����+1�Ϳ������ֳ��������
	}
	~AQueue()
	{
		delete[]listArray;
	}
	void Clear()
	{
		rear = 0;
		front = 1;
	}
	//����β��Ԫ�غ���
	void enqueue(const Elem& it)
	{
		Assert((((rear + 2) % maxSize) - front) != 0, "Queue is full");//�ж϶�����Ŀ�Ƿ��Ѿ����ˣ�+2�ǻ�����Ϊ��0��ʼ������
		rear = (rear + 1) % maxSize;//�����п���λ��ʱ������βԪ��λ��ָ����һ��λ��
		listArray[rear] = it;//��һ���Ѿ�ָ����һ��λ���ˣ�����ǰrearλ���ǿյģ������ֵ
	}
	//ɾ��ͷ��Ԫ�غ���
	Elem dequeue()
	{
		Assert(length() != 0, "Queue is empty");//���г���Ϊ0��˵��û��Ԫ�أ���Ϊ�ն���
												//�����Ϊ�ն���ʱ���Ž���ɾ����ʵ�����ǽ���Ԫ��λ��ָ����һ��λ�ã����൱��ֱ�Ӻ��Ե�Ҫɾ����Ԫ�أ�
		Elem it = listArray[front];
		front = (front + 1) % maxSize;//ɾ��������Ԫ�أ���frontָ����һ��Ԫ��
		return it;//����ɾ������Ԫ�ص�ֵ
	}
	//���ض�����λ��Ԫ��
	const Elem& frontValue()const
	{
		Assert(length() != 0, "Queue is empty");//���г���Ϊ0��˵��û��Ԫ�أ���Ϊ�ն���
		return listArray[front];//�����Ϊ�ն���ʱ�����ض�����Ԫ��λ�õ�Ԫ����ֵ
	}
	//���ض��г��Ⱥ���
	virtual int length()const
	{
		return((rear + maxSize) - front + 1) % maxSize;//����ֱ��rear-front+1����Ϊ����һ�������п���rear��λ�ñ�front��λ��Ҫǰ
														//������ʱ�Ӵ�12��ǰ����12��󣬾�����һ����Խ��
	}
};
#endif