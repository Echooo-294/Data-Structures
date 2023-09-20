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
class Link//�����
{
public:
	E element;
	Link* next;
	Link() {}//Ĭ�Ϲ��캯��
	Link(E it, Link* l)//���캯��
	{
		element = it;
		next = l;
	}
};

template<typename E>
class Queue//����
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

void Assert(int e, string s)//����e���ش�������ֹ����ִ��
{
	assert(e);
	cout << s << endl;
}
/*
 ����front��NULL��״̬������һ��Ԫ�زŴ���ֵ��
 ����Ϊ��ʱ��rear==front
 ����ʱ��ֱ�Ӳ���rear����һ��λ��
 ��Ԫ��λ����front->next
*/

template<typename E>
class LQueue :public Queue<E>
{
private:
	Link<E>* front;//ָ����е�һ�����
	Link<E>* rear;//ָ��������һ�����
	int size;//����Ԫ�ظ���
public:
	//���캯��
	LQueue(int sz = defaultSize)
	{
		front = rear = new Link<E>;
		size = 0;
	}
	//��������
	~LQueue()
	{
		clear();
		delete front;
	}
	//��պ���
	void clear()
	{
		while (front->next != NULL)//��Ϊ�ռ�˵����û���
		{
			rear = front;//��ͷ��ʼɾ
			front = front->next;
			delete rear;
		}
		rear = front;//�ص���ʼ��״̬
		size = 0;//������Ԫ�ظ���ָ��
	}
	//���뺯�����������β��
	void enqueue(const E& it)
	{
		rear->next = new Link<E>(it, NULL);//�ڶ�β�����½��
		rear = rear->next;
		size++;//����Ԫ�ظ���+1
	}
	//ɾ��������ɾ��������Ԫ�أ�������Ԫ��
	E dequeue()
	{
		Assert(size != 0, "Queue is empty");//�ж��Ƿ��ǿն���
		E it = front->next->element;//Ϊ�˷���ɾ��Ԫ����׼��
		Link<E>* Itemp = front->next;
		if (rear == Itemp)//�ж�front->next�Ƿ��Ƕ�β������ǣ���ֱ�ӽ����׸�ֵ����β���൱�ڻص���ʼ��
			rear = front;
		delete Itemp;
		size--;
		return it;
	}
	//������Ԫ�ص�ֵ
	const E& frontValue()const
	{
		Assert(size != 0, "Queue is empty");
		return front->next->element;
	}
	//���ض��г���
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