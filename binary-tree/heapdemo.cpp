//以下为一个示范范例
//这是一个用来示范Heap的cpp文件
//定义了一个Demo的类，其含有一个字符串和一个整型变量
//根据修改Compare中的比较函数可实现不同堆排序方式
#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<stack>
#include<queue>
#include<algorithm>
#include<map>
#include<set>
#include"Heap.cpp"
using namespace std;
//示例类
class Demo
{
	//方便起见所有属性设置为public
public :
	string name;
	int i1;
	Demo()
	{
		name = "";
		i1 = 0;
	}
	friend istream& operator>>(istream&i,Demo&d)
	{
		return i >> d.name >> d.i1;
	}
	Demo& operator=(Demo t)
	{
		name = t.name;
		i1 = t.i1;
		return *this;
	}
};
//---------------------------------------------分割线-------------------------------------------------------------------
//以下为定义的比较器，在比较器中传入自定义的类对象，函数定义比较方式
//举例：定义一个Student类，其中含name，chinese，math等参数
//若按照名字进行比较，如下所示
/*
prior(Student a,Student b)
{return a.name.compare(b.name)>0;}这是名字按照首字母比较的情况，其按Z到A的顺序，改为<0则按A到Z的顺序
*/
//若按照语文成绩进行比较，如下所示
/*
prior(Student a,Student b)
{return a.chinese>b.chinese;}这是按照语文成绩比较的情况，其从高到低，改为<号则从低到高
*/
//---------------------------------------------分割线-------------------------------------------------------------------

struct Compare
{
	static bool prior(Demo a, Demo b)
	{
		//以前文最大堆为例，传入两个E类对象a、b，若对于某个属性a比b大则直接返回
		//此时比较i1值，且顺序是从大到小
		return a.i1>b.i1;
	}
};

//---------------------------------------------分割线-------------------------------------------------------------------

int main()
{
	Demo* in = new Demo[7];
	heap<Demo, Compare>new_heap;
	for (int i = 0; i < 7; i++)
	{
		cin >> in[i];//重载了Demo的输入运算符，输入一个对象时需要输入一个字符串和一个整型变量
		new_heap.insert(in[i]);
	}
	for (int i = 0; i < 7; i++)
	{
		cout << new_heap.size() << endl;
		Demo tmp = new_heap.removefirst();
		cout << tmp.name << " " << tmp.i1 << endl;
	}
	cout << new_heap.size() << endl;
}


