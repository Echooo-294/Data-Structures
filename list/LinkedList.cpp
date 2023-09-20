#include<iostream>
using namespace std;
template<typename Elem>
class Node
{
public:
	Elem val;
	Node* next;
	Node() { next = NULL; }
	Node(Elem v) { val = v;next = NULL; }
};

template<typename Elem>
class List
{
public:
	virtual void Clear() = 0;
	virtual bool getValue(Elem& e) = 0;
	virtual bool setPos(int pos) = 0;
	virtual bool Prev() = 0;
	virtual bool Next() = 0;
	virtual bool Insert(Elem& e) = 0;
	virtual bool Remove(Elem& e) = 0;
	virtual void Sort(bool choice) = 0;
	virtual void Print() = 0;
};

template<typename Elem>
class LinkedList
{
	Node<Elem>* head;
	Node<Elem>* tail;
	Node<Elem>* fence;
	int size;
public:
	LinkedList();
	~LinkedList();
	void Clear();
	bool getValue(Elem& e);
	bool setPos(int pos);
	int getPos();
	bool Prev();
	bool Next();
	bool Insert(Elem& e);
	bool Remove(Elem& e);
	void Sort(bool choice);
	void Print();
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
	if (head != NULL)
	{
		Node<Elem>* s = head, * p = s->next;
		for (;s != NULL;p = p->next)
		{
			delete s;
			s = p;
			if (p == NULL) break;
		}
		head = tail = fence = NULL;
	}
}

template<typename Elem>
void LinkedList<Elem>::Clear()
{
	if (head != tail)
	{
		Node<Elem>* s = head->next, * p = s->next;
		for (;s != NULL;p = p->next)
		{
			delete s;
			s = p;
			if (p == NULL) break;
		}
		head->next = NULL;
		fence = tail = head;
		size = 0;
	}
}

template<typename Elem>
bool LinkedList<Elem>::getValue(Elem& e)
{
	if (fence->next != NULL)
	{
		e = fence->next->val;
		return 1;
	}
	return 0;
}

template<typename Elem>
bool LinkedList<Elem>::setPos(int pos)
{
	if (pos > size || pos < 0) return 0;
	fence = head;
	for (int i = 0;i < pos;i++)
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
	if (fence == head) return 0;
	Node<Elem>* p = head;
	while (p->next != fence)
		p = p->next;
	fence = p;
	return 1;
}

template<typename Elem>
bool LinkedList<Elem>::Next()
{
	if (fence == tail) return 0;
	fence = fence->next;
	return 1;
}

template<typename Elem>
bool LinkedList<Elem>::Insert(Elem& e)
{
	Node<Elem>* p = new Node<Elem>(e);
	p->next = fence->next;
	fence->next = p;
	if (tail->next != NULL) tail = tail->next;
	size++;
	return 1;
}

template<typename Elem>
bool LinkedList<Elem>::Remove(Elem& e)
{
	if (tail == fence) return 0;
	else
	{
		Node<Elem>* p = fence->next;
		e = p->val;
		fence->next = p->next;
		delete p;
		if (fence->next == NULL) tail = fence;
		size--;
		return 1;
	}
}

template<typename Elem>
void LinkedList<Elem>::Sort(bool choice)
{
	int pos = getPos();
	int pass, i;
	bool work;
	Elem temp;
	for (pass = 1;pass < size;pass++)
	{
		work = 1;
		for (i = 0;i < size - pass;i++)
		{
			setPos(i);
			Node<Elem>* a = fence;
			Next();
			Node<Elem>* b = fence;
			if (!choice)
			{
				if (a->next->val > b->next->val)
				{
					temp = a->next->val;
					a->next->val = b->next->val;
					b->next->val = temp;
					work = 0;
				}
			}
			else
			{
				if (a->next->val < b->next->val)
				{
					temp = a->next->val;
					a->next->val = b->next->val;
					b->next->val = temp;
					work = 0;
				}
			}
		}
		if (work) break;
	}
	setPos(pos);
}

template<typename Elem>
void LinkedList<Elem>::Print()
{
	Node<Elem>* p = head;
	while (p->next != NULL)
	{
		cout << p->next->val << " ";
		p = p->next;
	}
	cout << endl << "The position of the fence:" << getPos() << endl;
	cout << "The size of the list:" << size << endl;
}

int main()
{
	LinkedList<int> a;
	bool work = 1;
	while (work)
	{
		a.Print();
		cout << "1.clear()" << '\t' << "2.getvalue(x)" << '\t' << "3.setpos(pos)" << '\t' << "4.prev()" << '\t' << "5.next()" << '\t' << "6.insert(x)" << '\t' << "7.remove(x)" << '\t' << "8.sort(seq)" << '\t' << "9.quit" << endl;
		char choice;
		cin >> choice;
		switch (choice)
		{
		case'1': {a.Clear();break;}
		case'2': {int x;if (a.getValue(x)) { cout << "The value:" << x << endl;cout << "Please input something to continue...";string a;cin >> a; }break;}
		case'3': {int x;cout << "Please input the index:";cin >> x;a.setPos(x);break;}
		case'4': {a.Prev();break;}
		case'5': {a.Next();break;}
		case'6': {int x;cout << "Please input the value:";cin >> x;a.Insert(x);break;}
		case'7': {int x;if (a.getValue(x)) { a.Remove(x);cout << "The value excluded is:" << x << endl;cout << "Please input something to continue...";string a;cin >> a; }break;}
		case'8': {int seq;cout << "Please input the sequence(0 for increase order and 1 for decrease order):";cin >> seq;a.Sort(seq);break;}
		case'9': {work = 0;break;}
		default:;
		}
		system("cls");
	}
}