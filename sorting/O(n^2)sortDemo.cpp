#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<stack>
#include<queue>
#include<algorithm>
#include<map>
#include<set>
#include<assert.h>
#include"O(n^2)sort.cpp"
using namespace std;
//示例类
class SortDemo
{
public:
	int i1;
	int i2;
	int i3;
	SortDemo()
	{
		i1 = i2 = i3 = 0;
	}
	friend istream& operator>>(istream& i, SortDemo& d)
	{
		return i >> d.i1 >> d.i2 >> d.i3;
	}
	friend ostream& operator<<(ostream& o, SortDemo& d)
	{
		return o << d.i1 << " " << d.i2 << " " << d.i3;
	}
	SortDemo& operator=(SortDemo t)
	{
		i1 = t.i1;
		i2 = t.i2;
		i3 = t.i3;
		return *this;
	}
};
//比较器
struct Compare
{
	static bool prior(SortDemo a, SortDemo b)
	{
		//此处是将两个对象的第二个参数进行比较
		return a.i2<b.i2;
	}
};
//测试主函数
int main()
{
	//此处是根据第二个参数值从高到低排序，当前函数只测试冒泡排序
	//其余两种排序通过include剩下两个cpp文件可实现，经测试可行
	cout << "Please enter the number of objects. Each object contains three integer parameters." << endl;
	int n;
	while (cin >> n)
	{
		cout << "Object Input Example：20 30 40" << endl;
		SortDemo* in = new SortDemo[n];
		for (int i = 0; i < n; i++)cin >> in[i];
		SelectSort<SortDemo, Compare>(in, n);
		cout << "BubbleSort Completed" << endl;
		for (int i = 0; i < n; i++)cout << in[i] << endl;
		cout << endl;
		cout << "Please enter the number of objects. Each object contains three integer parameters." << endl;
	}
}