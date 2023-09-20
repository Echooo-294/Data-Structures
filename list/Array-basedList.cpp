#include<iostream>
using namespace std;

template<typename T>
class List
{
public:
	virtual void Clear() = 0;
	virtual bool getValue(T& x) = 0;
	virtual bool setPos(int pos) = 0;
	virtual bool Prev() = 0;
	virtual bool Next() = 0;
	virtual bool Insert(T x) = 0;
	virtual bool Remove(T& x) = 0;
	virtual void Sort(int choice) = 0;
	virtual void Print() = 0;
};

template<typename T>
class ArrayList :public List<T>
{
	T* array;
	int maxsize;
	int size;
	int fence;
public:
	ArrayList(int ms);
	~ArrayList();
	void Clear();
	bool getValue(T& x);
	bool setPos(int pos);
	bool Prev();
	bool Next();
	bool Insert(T x);
	bool Remove(T& x);
	void Sort(int choice);
	void Print();
};
template<typename T>ArrayList<T>::ArrayList(int ms)
{
	maxsize = ms;
	array = new T[maxsize];
	fence = size = 0;
}
template<typename T>ArrayList<T>::~ArrayList()
{
	delete[]array;
}
template<typename T>void ArrayList<T>::Clear()
{
	fence = size = 0;
}
template<typename T>bool ArrayList<T>::getValue(T& x)
{
	if (fence == size) return 0;
	else
	{
		x = array[fence];
		return 1;
	}
}
template<typename T>bool ArrayList<T>::setPos(int pos)
{
	if (pos <= size && pos >= 0)
	{
		fence = pos;
		return 1;
	}
	else return 0;
}
template<typename T>bool ArrayList<T>::Prev()
{
	if (fence == 0) return 0;
	else
	{
		fence--;
		return 1;
	}
}
template<typename T>bool ArrayList<T>::Next()
{
	if (fence == size) return 0;
	else
	{
		fence++;
		return 1;
	}
}
template<typename T>bool ArrayList<T>::Insert(T x)
{
	if (size == maxsize) return 0;
	else
	{
		for (int j = size - 1;j >= fence;j--)
		{
			array[j + 1] = array[j];
		}
		array[fence] = x;
		size++;
		return 1;
	}
}
template<typename T>bool ArrayList<T>::Remove(T& x)
{
	if (size == 0) return 0;
	else
	{
		x = array[fence];
		for (int j = fence;j < size - 1;j++)
		{
			array[j] = array[j + 1];
		}
		size--;
		return 1;
	}
}
template<typename T>void ArrayList<T>::Sort(int choice)
{
	int pass, i;
	bool work;
	T temp;
	for (pass = 1;pass < size;pass++)
	{
		work = 1;
		for (i = 0;i < size - pass;i++)
		{
			if (choice == 0)
			{
				if (array[i] > array[i + 1])
				{
					temp = array[i];
					array[i] = array[i + 1];
					array[i + 1] = temp;
					work = 0;
				}
			}
			else
			{
				if (array[i] < array[i + 1])
				{
					temp = array[i];
					array[i] = array[i + 1];
					array[i + 1] = temp;
					work = 0;
				}
			}
		}
		if (work) break;
	}
}
template<typename T>void ArrayList<T>::Print()
{
	cout << "[";
	for (int i = 0;i < size;i++)
	{
		if (i == fence) cout << "|";
		else if (i != 0) cout << ",";
		cout << array[i];
	}
	if (fence == size) cout << "|";
	cout << "]" << endl;
}

int main()
{
	cout << "The size of the array:";
	int maxsize;
	cin >> maxsize;
	ArrayList<int> a(maxsize);
	system("cls");

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