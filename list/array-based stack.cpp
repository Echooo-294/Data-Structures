#include<iostream>
using namespace std;
#define DEFUALTSIZE 50
//Assert函数的实现
void Assert(bool T, string s)
{
	if (!T)cout << s << endl;
	return;
}
//创建栈的抽象类
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
//基于数组的栈的实现
template <typename E>class AStack :public Stack<E>
{
private:
	int maxsize;
	int top;
	E* listArray;
public:
	//初始化栈
	AStack(int size = DEFUALTSIZE)
	{
		maxsize = size;
		top = 0;
		listArray = new E[size];
	}
	~AStack() { delete[]listArray; }
	void clear() { top = 0; }//将栈顶下标置零以清除栈
	//进栈
	void push(const E& it) {
		Assert(top != maxsize, "Stack is full");
		listArray[top++] = it;//数组当前位置赋值后，下标进一
	}
	//出栈
	E pop() {
		Assert(top != 0, "Stack is empty");//栈顶标记为0，栈为空
		return listArray[--top];//下标退一后，返回当前栈顶值
	}
	//返回栈顶值
	const E& topValue() const {
		Assert(top != 0, "Stack is empty");//栈顶标记为0，栈为空，无栈顶值
		return listArray[top - 1];
	}
	//返回栈大小
	int length()const { return top; }
};
int main(){}