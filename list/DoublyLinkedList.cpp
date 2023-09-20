#include<iostream>
using namespace std;
template<typename Elem>class Node
{
public:
	Elem val;
	Node* next;
	Node* prev;
	Node() { next = prev = NULL; }
};
template<typename Elem>class DoublyLinkedList
{
	Node<Elem>* head;
	Node<Elem>* tail;
	Node<Elem>* fence;
	int size;
public:
	DoublyLinkedList() { head = new Node<Elem>;tail = fence = head;size = 0; }
	~DoublyLinkedList();
	int getSize();//获取链表长度
	bool getValue(Elem& e);//获取fence位置的元素
	bool Clear();//清空链表
	bool Next();//fence后移一位
	bool Prev();//fence前移一位
	bool setPos(int pos);//设置fence的位置
	int getPos();//获取fence的位置
	bool Insert(Elem& e);//在fence位置插入元素e
	bool Remove(Elem& e);//删除fence位置的元素，将其保存在e中
	void Print();//打印链表
};
template<typename Elem>DoublyLinkedList<Elem>::~DoublyLinkedList()
{
	Node<Elem>* p = head, * s = p->next;
	while (s != NULL)
	{
		delete p;
		p = s;
		s = s->next;
	}
	delete p;
}
template<typename Elem>int DoublyLinkedList<Elem>::getSize()
{
	return size;
}
template<typename Elem>bool DoublyLinkedList<Elem>::getValue(Elem& e)
{
	if (fence->next == NULL) return 0;
	e = fence->next->val;
	return 1;
}
template<typename Elem>bool DoublyLinkedList<Elem>::Clear()
{
	if (head == tail) return 0;
	Node<Elem>* p = head->next, * s = p->next;
	while (s != NULL)
	{
		delete p;
		p = s;
		s = s->next;
	}
	delete p;
	head->next = NULL;
	fence = tail = head;
	size = 0;
	return 1;
}
template<typename Elem>bool DoublyLinkedList<Elem>::Next()
{
	if (fence->next == NULL) return 0;
	fence = fence->next;
	return 1;
}
template<typename Elem>bool DoublyLinkedList<Elem>::Prev()
{
	if (fence->prev == NULL) return 0;
	fence = fence->prev;
	return 1;
}
template<typename Elem>bool DoublyLinkedList<Elem>::setPos(int pos)
{
	if (pos < 0 || pos > size) return 0;
	fence = head;
	for (int i = 0;i < pos;i++)
		fence = fence->next;
	return 1;
}
template<typename Elem>int DoublyLinkedList<Elem>::getPos()
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
template<typename Elem>bool DoublyLinkedList<Elem>::Insert(Elem& e)
{
	Node<Elem>* p = new Node<Elem>;
	p->val = e;
	if (fence == tail)
	{
		p->prev = fence;
		fence->next = p;
		tail = p;
	}
	else
	{
		p->next = fence->next;
		p->prev = fence;
		fence->next->prev = p;
		fence->next = p;
	}
	size++;
	return 1;
}
template<typename Elem>bool DoublyLinkedList<Elem>::Remove(Elem& e)
{
	if (fence == tail) return 0;
	Node<Elem>* p = fence->next;
	if (p->next == NULL)
	{
		delete p;
		fence->next = NULL;
		tail = fence;
	}
	else
	{
		fence->next = p->next;
		p->next->prev = fence;
		delete p;
	}
	size--;
	return 1;
}
template<typename Elem>void DoublyLinkedList<Elem>::Print()
{
	if (fence == head) cout << "|";
	Node<Elem>* p = head->next;
	while (p != NULL)
	{
		cout << p->val;
		if (p == fence) cout << "|";
		else cout << " ";
		p = p->next;
	}
	cout << endl;
	cout << "The size of the list:" << size << endl;
}

int main()
{
	DoublyLinkedList<int> a;
	bool work = 1;
	while (work)
	{
		a.Print();
		cout << "1.clear()" << '\t' << "2.getvalue(x)" << '\t' << "3.setpos(pos)" << '\t' << "4.prev()" << '\t' << "5.next()" << '\t' << "6.insert(x)" << '\t' << "7.remove(x)" << '\t' << "8.quit" << endl;
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
		case'8': {work = 0;break;}
		default:;
		}
		system("cls");
	}
}