#if 0
#include<iostream>
using namespace std;
#define DEFUALTSIZE 50
//Assert������ʵ��
void Assert(bool T, string s)
{
	if (!T)cout << s << endl;
	return;
}
//����ջ�ĳ�����
template<typename E>class Stack
{
private:
	void operator =(const Stack&) {}
	Stack(const Stack&) {}
public:
	Stack() {}
	virtual ~Stack() {}
	virtual void clear() = 0;
	virtual void push(const E& it) = 0;
	virtual E pop() = 0;
	virtual const E& topValue() const = 0;
	virtual int length() const = 0;
};

//���������ջ��ʵ��
template <typename E>class LStack :public Stack<E> {
private:
	//����Ԫ�����ʵ��
	template <typename E>class Link {
	private:
		E element;
		Link* next;
	public:
		Link(E it, Link* top) {
			element = it;
			next = top;
		}
	};
	Link<E>* top;
	int size;
public:
	//��ʼ��ջ
	LStack(int sz = DEFUALTSIZE)
	{
		top = NULL;
		size = 0;
	}
	~LStack() { clear(); }
	//���ջ
	void clear() {
		while (top != NULL)//��ջ��ָ�벻Ϊ����һֱ���ɾ��
		{
			Link<E>* temp = top;
			top = top->next;
			delete temp;
		}

		size = 0;//���ջ�󽫴�С����
	}
	//��ջ
	void push(const E& it) {
		top = new Link<E>(it, top);//�½����topָ���������
		size++;
	}
	//��ջ
	E pop() {
		Assert(top != NULL, "Stack is empty");//�ж�ջ��ָ��Ϊ�գ���ʾ����
		E it = top->element;
		Link<E>* Itemp = top->next;
		delete top;
		top = Itemp;
		size--;//ɾ��ջ��ֵ����topָ��ָ����һ�ջ��С��1
		return it;
	}
	//����ջ��ֵ
	const E& topValue() const {
		Assert(top != NULL, "Stack is empty");//�ж�ջ��ָ��Ϊ�գ���ʾ����
		return top->element;
	}
	//����ջ��С
	int length() const { return size; }
};

int main() {}
#endif