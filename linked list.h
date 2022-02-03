//使用链表实现顺序表
#include<iostream>
using namespace std;
template<typename Elem>
class Node
{
public:
	Elem val;
	Node* next;
	Node() :next(nullptr) {}//除了初始化应该避免调用默认构造，或设置val默认值
	Node(Elem v) :val(v), next(nullptr) {}
};
template<typename Elem>
class List
{
public:
	virtual void Clear() = 0;
	virtual bool getValue(Elem& e) = 0;
	virtual int getSize() = 0;
	virtual bool setPos(int pos) = 0;
	virtual int getPos() = 0;
	virtual bool Prev() = 0;
	virtual bool Next() = 0;
	virtual bool Insert(Elem& e) = 0;
	virtual bool Remove(Elem& e) = 0;
	virtual void swap(Elem& a, Elem& b) = 0;
	virtual void Sort(bool choice) = 0;
	virtual void Print() = 0;
};
template<typename Elem>
class LinkedList :public List<Elem>
{
public:
	LinkedList();
	~LinkedList();
	void Clear();
	bool getValue(Elem& e);
	int getSize() { return size; }
	bool setPos(int pos);
	int getPos();//获取当前fence位置
	bool Prev();
	bool Next();
	bool Insert(Elem& e);
	bool Remove(Elem& e);
	void swap(Elem& a, Elem& b);
	void Sort(bool choice);
	void Print();
private:
	Node<Elem>* head;
	Node<Elem>* tail;
	Node<Elem>* fence;
	int size;
};
template<typename Elem>
LinkedList<Elem>::LinkedList()
{
	head = new Node<Elem>;
	fence = tail = head;
	size = 0;
}
template<typename Elem>
LinkedList<Elem>::~LinkedList()
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
		delete s;//把最后一个删了
		head = tail = fence = nullptr;
	}
}
template<typename Elem>
void LinkedList<Elem>::Clear()
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
bool LinkedList<Elem>::getValue(Elem& e)
{
	if (fence->next == nullptr)
		return 0;
	e = fence->next->val;//返回fence位置下一个元素的值
	return 1;
}
template<typename Elem>
bool LinkedList<Elem>::setPos(int pos)
{
	if (pos > size || pos < 0)
		return 0;
	fence = head;
	for (int i = 0; i < pos; i++)
		fence = fence->next;
	return 1;
}
template<typename Elem>
int LinkedList<Elem>::getPos()
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
bool LinkedList<Elem>::Prev()
{
	if (fence == head)
		return 0;
	Node<Elem>* p = head;
	while (p->next != fence)
		p = p->next;
	fence = p;
	return 1;
}
template<typename Elem>
bool LinkedList<Elem>::Next()
{
	if (fence == tail || fence->next == nullptr)
		return 0;
	fence = fence->next;
	return 1;
}
template<typename Elem>
bool LinkedList<Elem>::Insert(Elem& e)//头插法
{
	Node<Elem>* p = new Node<Elem>(e);
	p->next = fence->next;
	fence->next = p;
	if (tail->next != nullptr) //若插在了tail后面则需要调整tail位置
		tail = tail->next;
	size++;
	return 1;
}
template<typename Elem>
bool LinkedList<Elem>::Remove(Elem& e)
{
	if (fence == tail || size == 0)
		return 0;
	else
	{
		Node<Elem>* p = fence->next;//删的是fence的下一个
		e = p->val;
		fence->next = p->next;
		delete p;
		if (fence->next == nullptr) //若删除了tail前面的一个则需要调整tail位置
			tail = fence;
		size--;
		return 1;
	}
}
template<typename Elem>
void LinkedList<Elem>::swap(Elem& a, Elem& b)
{
	Elem temp;
	temp = a;
	a = b;
	b = temp;
}
template<typename Elem>
void LinkedList<Elem>::Sort(bool choice)//choice默认传0升序，传1降序
{
	const int pos = getPos();
	bool work;
	for (int pass = 1; pass < size; pass++)//这里使用了冒泡排序，后续要改成快速排序
	{
		work = 1;
		for (int i = 0; i < size - pass; i++)
		{
			setPos(i);
			Node<Elem>* a = fence;
			Next();
			Node<Elem>* b = fence;
			if (choice == 1)
			{
				if (a->next->val < b->next->val)
				{
					swap(a->next->val, b->next->val);
					work = 0;
				}
			}
			else //默认=0升序
			{
				if (a->next->val > b->next->val)
				{
					swap(a->next->val, b->next->val);
					work = 0;
				}
			}
		}
		if (work)
			break;
	}
	setPos(pos);//恢复原fence位置
}
template<typename Elem>
void LinkedList<Elem>::Print()
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