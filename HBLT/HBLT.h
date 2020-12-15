#pragma once
#include "BinaryTree.h"
#include"ArrayQueue.h"
//键值对结构体
template<class K, class V>
struct Pair
{
	K key;
	V value;
	Pair() {}
	Pair(const K& theKey, const V& theValue)
	{
		this->key = theKey;
		this->value = theValue;
	}
	Pair(const Pair& pair)
	{
		this->key = pair.key;
		this->value = pair.value;
	}
};

template<class D>
class HBLT :
	public BinaryTree< Pair<int,D> >
	//要引用基类的字段必须要用this，否则索引不到，基类的方法也要用双冒号调用
{
public:
	HBLT(D* theArray,int array_size)
	{
		this->tree_size = array_size;
		initTree(theArray);
	}
	~HBLT() { HBLT<D>::erase(); }
	void meld(HBLT<D>& theHBLT)
	{
		meld(this->root, theHBLT.root);
		this->tree_size += theHBLT.tree_size;
		//删除被融合的树
		theHBLT.root = NULL;
		theHBLT.tree_size = 0;
	}
	//先把树根的左右子树融合到左子树，再把树根删了，把左子树赋给树根
	void pop()
	{
		LinkTreeNode<Pair<int, D>>* left;
		LinkTreeNode<Pair<int, D>>* right;
		left = this->root->leftChild;
		right = this->root->rightChild;
		meld(left, right);
		delete this->root;
		this->root = left;
		this->tree_size--;
	}
	//输入一个D型数据，构建一个s值为0的Pair，用Pair建一个树根，
	//再把这个树根和本类融合
	void push(const D& theData)
	{
		Pair<int,D>thePair(1, theData);
		LinkTreeNode<Pair<int, D>>* theTree = new LinkTreeNode<Pair<int, D>>(thePair);
		meld(this->root, theTree);
		this->tree_size++;
	}
	void HBLTOutput()
	{
		Pair<int,D>* out= HBLT<D>::output();
		for (int i = 0; i < this->tree_size; i++)
			std::cout << out[i].value << " ";
	}
	D& top()const { return this->root->data.value; }//这里是对基类top方法的覆盖，而不是重写，基类的top方法调用不到了
private:
	//初始化方法，输入一个D型数组，将数组中的元素放到HBLT中，并给每个元素赋好s值
	//书上的方法就可以的，不用担心s值，在meld里会自动赋好
	void initTree(D* theArray)
	{
		ArrayQueue< LinkTreeNode< Pair<int, D> >* > q(this->tree_size);//盛放HBLT的队列
		//把建立好的树依次入队
		for (int i = 0; i < this->tree_size; i++)
			q.push(new LinkTreeNode<Pair<int, D>>(Pair<int, D>(1, theArray[i])));
		//每次把队首两个树拿出来融合，结果放到队尾，直到队列中只有一个树
		while (q.size() > 1)
		{
			LinkTreeNode< Pair<int, D> >* first;
			LinkTreeNode< Pair<int, D> >* second;
			first = q.getFront(); q.pop();
			second = q.getFront(); q.pop();
			meld(first, second);
			q.push(first);
		}
		//把最后的一个树赋给本类树根
		this->root = q.getFront();//如果觉得前序遍历输出的树看不清楚，可以在此处打断点监视root的值，可以看清初始化后整棵树的情况
	}
	//递归融合，融合结果在x(*this)里，y的值被改变了，已经废掉不能用了
	void meld(LinkTreeNode< Pair<int, D> >* &x, LinkTreeNode< Pair<int, D> >* &y)
	{
		if (y == NULL) return;
		if (x == NULL) { x = y; return; }
		if (x->data.value < y->data.value) swap(x, y);
		meld(x->rightChild, y);//递归之前的语句是递归向下的过程，后面的语句是递归向上的过程
		//递归回到上一层立即判断当前节点的双子节点是否都有值
		if (x->leftChild != NULL && x->rightChild != NULL) 
			x->data.key++;//如果都有值，此节点的s值+1
		if (x->leftChild == NULL)
		{
			x->leftChild = x->rightChild;
			x->rightChild = NULL;
		}
		else if (x->leftChild->data.key < x->rightChild->data.key)
		{
			swap(x->leftChild, x->rightChild);
			x->data.key = x->rightChild->data.key + 1;//此处应该更新s值
		}
	}
	//交换x y
	void swap(LinkTreeNode< Pair<int, D> >* &x, LinkTreeNode< Pair<int, D> >* &y)
	{
		LinkTreeNode< Pair<int, D> >* temp;
		temp = x; x = y; y = temp;
	}
};

