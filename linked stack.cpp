#if 0
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

//基于链表的栈的实现
template <typename E>class LStack :public Stack<E> {
private:
	//链表单元的类的实现
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
	//初始化栈
	LStack(int sz = DEFUALTSIZE)
	{
		top = NULL;
		size = 0;
	}
	~LStack() { clear(); }
	//清除栈
	void clear() {
		while (top != NULL)//当栈顶指针不为空则一直向后删除
		{
			Link<E>* temp = top;
			top = top->next;
			delete temp;
		}

		size = 0;//清除栈后将大小置零
	}
	//进栈
	void push(const E& it) {
		top = new Link<E>(it, top);//新建项，将top指针放置链首
		size++;
	}
	//出栈
	E pop() {
		Assert(top != NULL, "Stack is empty");//判断栈顶指针为空，提示错误
		E it = top->element;
		Link<E>* Itemp = top->next;
		delete top;
		top = Itemp;
		size--;//删除栈顶值，将top指针指向下一项，栈大小减1
		return it;
	}
	//返回栈顶值
	const E& topValue() const {
		Assert(top != NULL, "Stack is empty");//判断栈顶指针为空，提示错误
		return top->element;
	}
	//返回栈大小
	int length() const { return size; }
};

int main() {}
#endif