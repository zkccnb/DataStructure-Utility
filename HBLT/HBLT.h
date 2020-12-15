#pragma once
#include "BinaryTree.h"
#include"ArrayQueue.h"
//��ֵ�Խṹ��
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
	//Ҫ���û�����ֶα���Ҫ��this��������������������ķ���ҲҪ��˫ð�ŵ���
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
		//ɾ�����ںϵ���
		theHBLT.root = NULL;
		theHBLT.tree_size = 0;
	}
	//�Ȱ����������������ںϵ����������ٰ�����ɾ�ˣ�����������������
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
	//����һ��D�����ݣ�����һ��sֵΪ0��Pair����Pair��һ��������
	//�ٰ���������ͱ����ں�
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
	D& top()const { return this->root->data.value; }//�����ǶԻ���top�����ĸ��ǣ���������д�������top�������ò�����
private:
	//��ʼ������������һ��D�����飬�������е�Ԫ�طŵ�HBLT�У�����ÿ��Ԫ�ظ���sֵ
	//���ϵķ����Ϳ��Եģ����õ���sֵ����meld����Զ�����
	void initTree(D* theArray)
	{
		ArrayQueue< LinkTreeNode< Pair<int, D> >* > q(this->tree_size);//ʢ��HBLT�Ķ���
		//�ѽ����õ����������
		for (int i = 0; i < this->tree_size; i++)
			q.push(new LinkTreeNode<Pair<int, D>>(Pair<int, D>(1, theArray[i])));
		//ÿ�ΰѶ����������ó����ںϣ�����ŵ���β��ֱ��������ֻ��һ����
		while (q.size() > 1)
		{
			LinkTreeNode< Pair<int, D> >* first;
			LinkTreeNode< Pair<int, D> >* second;
			first = q.getFront(); q.pop();
			second = q.getFront(); q.pop();
			meld(first, second);
			q.push(first);
		}
		//������һ����������������
		this->root = q.getFront();//�������ǰ��������������������������ڴ˴���ϵ����root��ֵ�����Կ����ʼ���������������
	}
	//�ݹ��ںϣ��ںϽ����x(*this)�y��ֵ���ı��ˣ��Ѿ��ϵ���������
	void meld(LinkTreeNode< Pair<int, D> >* &x, LinkTreeNode< Pair<int, D> >* &y)
	{
		if (y == NULL) return;
		if (x == NULL) { x = y; return; }
		if (x->data.value < y->data.value) swap(x, y);
		meld(x->rightChild, y);//�ݹ�֮ǰ������ǵݹ����µĹ��̣����������ǵݹ����ϵĹ���
		//�ݹ�ص���һ�������жϵ�ǰ�ڵ��˫�ӽڵ��Ƿ���ֵ
		if (x->leftChild != NULL && x->rightChild != NULL) 
			x->data.key++;//�������ֵ���˽ڵ��sֵ+1
		if (x->leftChild == NULL)
		{
			x->leftChild = x->rightChild;
			x->rightChild = NULL;
		}
		else if (x->leftChild->data.key < x->rightChild->data.key)
		{
			swap(x->leftChild, x->rightChild);
			x->data.key = x->rightChild->data.key + 1;//�˴�Ӧ�ø���sֵ
		}
	}
	//����x y
	void swap(LinkTreeNode< Pair<int, D> >* &x, LinkTreeNode< Pair<int, D> >* &y)
	{
		LinkTreeNode< Pair<int, D> >* temp;
		temp = x; x = y; y = temp;
	}
};

