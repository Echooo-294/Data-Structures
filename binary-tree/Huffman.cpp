template <typename E> 
class HuffNode //基类
{
public:
	virtual ~HuffNode() {}
	virtual int weight() = 0;
	virtual bool isLeaf() = 0;
};
template <typename E>
class LeafNode :public HuffNode<E>//叶子结点
{
private:
	E it;//叶子的名称/值
	int wgt;//叶子权重
public:
	//构造函数，初始化叶子结点
	LeafNode(const E& val, int freq)
	{
		it = val;
		wgt = freq;
	}
	//返回权重
	int weight() 
	{
		return wgt;
	}
	//返回叶子的名称/值
	E val() 
	{
		return it;
	}
	//判断是否是叶子，是叶子结点
	bool isLeaf()
	{ 
		return true; 
	}
};
template<typename E>
class Int1Node :public HuffNode<E> //中间结点
{
private:
	HuffNode<E>* lc;//左孩子结点
	HuffNode<E>* rc;//右孩子结点
	int wgt;//中间结点的权重
public:
	//初始化结点
	Int1Node(HuffNode<E>* l, HuffNode<E>* r)
	{
		wgt = l->weight() + r->weight(); lc = 1; rc = r;//中间结点的权重=左孩子权重+右孩子权重
	}
	//返回中间权重
	int weight() { return wgt; }
	//判断是否是叶子，非叶子结点
	bool isLeaf() { return false; }
	//返回左结点
	HuffNode<E>* left() const { return lc; }
	//创建左结点
	void setLeft(HuffNode<E>* b)
	{
		lc = (HuffNode<E>*)b;
	}
	//创建右结点
	HuffNode<E>* right() const { return rc; }
	void setRight(HuffNode<E>* b)
	{
		rc = (HuffNode<E>*)b;
	}
};
template <typename E>
class HuffTree {
private:
	HuffNode<E>* Root;
public:
	//一开始只有根节点的时候，则根结点也是叶子结点
	HuffTree(E& val, int freq)
	{
		Root = new LeafNode<E>(val, freq);
	}
	//一开始就确定会有子结点的时候，则根节点是中间结点
	HuffTree(HuffTree<E>* l, HuffTree<E>* r)
	{
		Root = new Int1Node<E>(l->Root, r->Root);
	}
	~HuffTree() {}
	//返回根节点
	HuffNode<E>* root()
	{
		return Root;
	}
	//返回根的权重
	int weight()
	{
		return Root->weight();
	}
};
template <typename E>
HuffTree<E>* buildHuff(HuffTree<E>** ThreeArray, int count)
{
	
	heap<HuffTree<E>*, minTreeComp>* forest = new heap<HuffTree<E>*, minTreeComp>(ThreeArray, count, count);//创建哈夫曼数
	HuffTree<char>* temp1, * temp2, * temp3 = NULL;
	while (forest->size() > 1)
	{
		//将最前面两颗子树分别赋值给temp1和temp2
		temp1 = forest->removefirst();
		temp2 = forest->removefirst();
		//将最前面两颗子树分别赋值为新结点的左子树和右子树
		temp3 = new HuffTree<E>(temp1, temp2);
		//将新树插入到堆序列中
		forest->insert(temp3);
		delete temp1;
		delete temp2;
	}
	return temp3;
}

