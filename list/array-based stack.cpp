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
template <typename E>class AStack :public Stack<E>
{
private:
	int maxsize;
	int top;
	E* listArray;
public:
	//��ʼ��ջ
	AStack(int size = DEFUALTSIZE)
	{
		maxsize = size;
		top = 0;
		listArray = new E[size];
	}
	~AStack() { delete[]listArray; }
	void clear() { top = 0; }//��ջ���±����������ջ
	//��ջ
	void push(const E& it) {
		Assert(top != maxsize, "Stack is full");
		listArray[top++] = it;//���鵱ǰλ�ø�ֵ���±��һ
	}
	//��ջ
	E pop() {
		Assert(top != 0, "Stack is empty");//ջ�����Ϊ0��ջΪ��
		return listArray[--top];//�±���һ�󣬷��ص�ǰջ��ֵ
	}
	//����ջ��ֵ
	const E& topValue() const {
		Assert(top != 0, "Stack is empty");//ջ�����Ϊ0��ջΪ�գ���ջ��ֵ
		return listArray[top - 1];
	}
	//����ջ��С
	int length()const { return top; }
};
int main(){}