//������ʵ��˳���
#include<iostream>
using namespace std;
template<typename Elem>
class List
{
public:
	virtual void Clear() = 0;
	virtual bool getValue(Elem& x) = 0;
	virtual int getSize() = 0;
	virtual bool setPos(int pos) = 0;
	virtual int getPos() = 0;
	virtual bool Prev() = 0;
	virtual bool Next() = 0;
	virtual bool Insert(Elem x) = 0;
	virtual bool Remove(Elem& x) = 0;
	virtual void swap(Elem& a, Elem& b) = 0;
	virtual void Sort(int choice) = 0;
	virtual void Print() = 0;
};
template<typename Elem>
class ArrayList :public List<Elem>
{
public:
	ArrayList(int ms);
	~ArrayList();
	void Clear();
	bool getValue(Elem& x);
	int getSize() { return size; }
	bool setPos(int pos);
	int getPos() { return fence; }
	bool Prev();
	bool Next();
	bool Insert(Elem x);
	bool Remove(Elem& x);
	void swap(Elem& a, Elem& b);
	void Sort(int choice);
	void Print();
private:
	Elem* array;
	int maxsize;
	int size;
	int fence;
};
template<typename Elem>
ArrayList<Elem>::ArrayList(int ms)
{
	maxsize = ms;
	array = new Elem[maxsize];
	fence = size = 0;
}
template<typename Elem>
ArrayList<Elem>::~ArrayList()
{
	delete[]array;
	array = nullptr;
}
template<typename Elem>
void ArrayList<Elem>::Clear()
{
	fence = size = 0;//ֻ��Ҫ��Ϊ�ռ���
}
template<typename Elem>
bool ArrayList<Elem>::getValue(Elem& x)
{
	if (fence == size) //�����ǰָ�봦��sizeλ�������ʧ��
		return 0;
	else
	{
		x = array[fence];
		return 1;
	}
}
template<typename Elem>
bool ArrayList<Elem>::setPos(int pos)
{
	if (pos <= size && pos >= 0)
	{
		fence = pos;//�±궼�Ǵ�0����
		return 1;
	}
	else
		return 0;
}
template<typename Elem>
bool ArrayList<Elem>::Prev()
{
	if (fence == 0)
		return 0;
	else
	{
		fence--;
		return 1;
	}
}
template<typename Elem>
bool ArrayList<Elem>::Next()
{
	if (fence == size)
		return 0;
	else
	{
		fence++;
		return 1;
	}
}
template<typename Elem>
bool ArrayList<Elem>::Insert(Elem x)//�˴�����Ҫ�����ò�������fence������
{
	if (size == maxsize)
		return 0;
	else
	{
		for (int j = size - 1; j >= fence; j--)
		{
			array[j + 1] = array[j];
		}
		array[fence] = x;
		size++;
		return 1;
	}
}
template<typename Elem>
bool ArrayList<Elem>::Remove(Elem& x)//��һ��������¼ɾ������Ԫ�ص�ֵ
{
	if (fence == size || size == 0) //�����ǰָ�봦��sizeλ�û��Ϊ�������ʧ��
		return 0;
	else
	{
		x = array[fence];
		for (int j = fence; j < size - 1; j++)
		{
			array[j] = array[j + 1];
		}
		size--;
		return 1;
	}
}
template<typename Elem>
void ArrayList<Elem>::swap(Elem& a, Elem& b)
{
	Elem temp;
	temp = a;
	a = b;
	b = temp;
}
template<typename Elem>
void ArrayList<Elem>::Sort(int choice)//choiceĬ�ϴ�0���򣬴�1����
{
	bool work;
	for (int pass = 1; pass < size; pass++)//����ʹ����ð�����򣬺���Ҫ�ĳɿ�������
	{
		work = 1;
		for (int i = 0; i < size - pass; i++)
		{
			if (choice == 1)
			{
				if (array[i] < array[i + 1])
				{
					swap(array[i], array[i + 1]);
					work = 0;
				}
			}
			else //Ĭ��=0����
			{
				if (array[i] > array[i + 1])
				{
					swap(array[i], array[i + 1]);
					work = 0;
				}
			}
		}
		if (work)
			break;
	}
}
template<typename Elem>
void ArrayList<Elem>::Print()
{
	for (int i = 0; i < size; i++)
	{
		if (i == fence)
			cout << "|";//��ָ���λ��Ҳ��ӡ����
		else if (i != 0)
			cout << ",";
		cout << array[i];
	}
	if (fence == size)
		cout << "|";
	cout << endl;
}