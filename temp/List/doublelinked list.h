//˫������
#include<iostream>
using namespace std;
template<typename Elem>
class Node
{
public:
	Elem val;
	Node* prev;
	Node* next;
	Node() :prev(nullptr), next(nullptr) {}//���˳�ʼ��Ӧ�ñ������Ĭ�Ϲ��죬������valĬ��ֵ
	Node(Elem v) :val(v), prev(nullptr), next(nullptr) {}
};
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
class DoublyLinkedList
{
public:
	DoublyLinkedList();
	~DoublyLinkedList();
	void Clear();
	bool getValue(Elem& e);
	int getSize() { return size; }
	bool setPos(int pos);
	int getPos();
	bool Prev();
	bool Next();
	bool Insert(Elem& e);
	bool Remove(Elem& e);
	//swap,Sort
	void Print();
private:
	Node<Elem>* head;
	Node<Elem>* tail;
	Node<Elem>* fence;
	int size;
};
template<typename Elem>
DoublyLinkedList<Elem>::DoublyLinkedList()
{
	head = new Node<Elem>;
	tail = fence = head;
	size = 0;
}
template<typename Elem>
DoublyLinkedList<Elem>::~DoublyLinkedList()
{
	if (head != nullptr)
	{
		Node<Elem>* s = head, * p = s->next;
		while (s != nullptr)
		{
			delete s;
			s = p;
			if (p == nullptr)
				break;
			p = p->next;
		}
		delete s;//�����һ��ɾ��
		head = tail = fence = nullptr;
	}
}
template<typename Elem>
void DoublyLinkedList<Elem>::Clear()
{
	if (head != tail && head != nullptr)
	{
		Node<Elem>* s = head->next, * p = s->next;
		while (s != nullptr)
		{
			delete s;
			s = p;
			if (p == nullptr)
				break;
			p = p->next;
		}
		delete s;
		head->next = nullptr;
		fence = tail = head;
		size = 0;
	}
}
template<typename Elem>
bool DoublyLinkedList<Elem>::getValue(Elem& e)
{
	if (fence->next == nullptr)
		return 0;
	e = fence->next->val;//����fenceλ����һ��Ԫ�ص�ֵ
	return 1;
}
template<typename Elem>
bool DoublyLinkedList<Elem>::setPos(int pos)
{
	if (pos > size || pos < 0)
		return 0;
	fence = head;
	for (int i = 0; i < pos; i++)
		fence = fence->next;
	return 1;
}
template<typename Elem>
int DoublyLinkedList<Elem>::getPos()
{
	Node<Elem>* p = head;
	int i = 0;
	while (p != fence)
	{
		p = p->next;
		i++;
	}
	return i;
}
template<typename Elem>
bool DoublyLinkedList<Elem>::Prev()
{
	if (fence == head || fence->prev == nullptr)
		return 0;
	fence = fence->prev;
	return 1;
}
template<typename Elem>
bool DoublyLinkedList<Elem>::Next()
{
	if (fence == tail || fence->next == nullptr)
		return 0;
	fence = fence->next;
	return 1;
}
template<typename Elem>
bool DoublyLinkedList<Elem>::Insert(Elem& e)
{
	Node<Elem>* p = new Node<Elem>(e);
	p->next = fence->next;
	fence->next = p;
	if (tail->next != nullptr) //��������tail��������Ҫ����tailλ��
		tail = tail->next;
	size++;
	return 1;
}
template<typename Elem>bool DoublyLinkedList<Elem>::Remove(Elem& e)
{
	if (fence == tail || size == 0)
		return 0;
	else
	{
		Node<Elem>* p = fence->next;//ɾ����fence����һ��
		e = p->val;
		fence->next = p->next;
		delete p;
		if (fence->next == nullptr) //��ɾ����tailǰ���һ������Ҫ����tailλ��
			tail = fence;
		size--;
		return 1;
	}
}
template<typename Elem>
void DoublyLinkedList<Elem>::Print()
{
	if (fence == head)
		cout << "|";
	Node<Elem>* p = head->next;
	while (p != nullptr)
	{
		cout << p->val;
		if (p == fence)
			cout << "|";
		else
			cout << " ";
		p = p->next;
	}
	cout << endl;
}