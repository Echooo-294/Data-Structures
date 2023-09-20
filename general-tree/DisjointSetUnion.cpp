#include <bits/stdc++.h>
#define ROOT -1//设置根值为-1
using namespace std;
class ParPtrTree//类的实现
{
    private:
        int *array;//父指针数组，记录每个结点的父节点下标
        int *num;//记录每个结点为根结点的子树结点数目，用于启发式合并
        int size;//创建的数组大小
        int FIND(int) const;//查找集合的根结点
    public:
        ParPtrTree(int);//初始化
        ~ParPtrTree();//析构
        void UNION(int, int);//合并集合
        bool differ(int, int);//判断根节点是否相同（是否在同一个集合）
};
ParPtrTree::ParPtrTree(int _size)//构造函数及数组初始化
{
    //赋值和创建数组
    size=_size;
    array=new int[size];
    num=new int[size];
    //初始化
    for(int i=0;i<size;i++)
    {
        array[i]=ROOT;//开始时每个结点都是根节点（-1）
        num[i]=1;//开始时每个集合数目都为1
    }
}
ParPtrTree::~ParPtrTree()//析构函数
{
    delete[] array;
    delete[] num;
}
int ParPtrTree:: FIND(int curr) const//查找集合的根结点
{
    if(array[curr]==ROOT)return curr;//如果是根节点，返回
    return array[curr]=FIND(array[curr]);//否则就递归查找父节点的根，并实现路径压缩（将根节点设为父节点减小深度）
}
void ParPtrTree::UNION(int x,int y)//合并集合
{
    int root1=FIND(x);//第一个节点的根节点
    int root2=FIND(y);//第二个节点的根节点
    if(num[x]>num[y])//比较两个子树大小，小的合并到大的上面
    {
        array[root2]=root1;//小的根节点父节点设为另一个根节点
        num[root1]+=num[root2];//新的根节点子树节点数目增加
    }
    else//同理
    {
        array[root1]=root2;
        num[root2]+=num[root1];
    }
}
bool ParPtrTree::differ(int x,int y)//判断根节点是否相同（是否在同一个集合）
{
    int root1=FIND(x);//第一个节点的根节点
    int root2=FIND(y);//第二个节点的根节点
    if(root1==root2)return 0;//如果相同说明在同一个集合里，differ值为0
    else return 1;//否则为1
}
