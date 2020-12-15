#pragma once
#include"LinkTreeNode.h"
template<class T>
class BinaryTree
{
public:
	BinaryTree() //{ root = NULL; tree_size = 0; }
	{

	}
	~BinaryTree() { erase(); }
	void preOrder(void(*theVisit)(LinkTreeNode<T>*))
	{
		visit = theVisit;
		preOrder(root);
	}
	void postOrder(void(*theVisit)(LinkTreeNode<T>*))
	{
		visit = theVisit;
		postOrder(root);
	}
	void erase()
	//十分注意：删除节点时必须用后序遍历；
	//用前序遍历的话相当于删完节点后再索引下一个节点，导致报错
	{
		postOrder(deleteNode_1_visit);
		root = NULL;
		tree_size = 0;
	}
	T* output()
	{
		outputer = new T[tree_size];
		preOrder(output_1_visit);
		return outputer;
	}
	T& top()const { return root->data; }
	int size()const { return tree_size; }
	bool empty()const { return tree_size == 0; }

protected://protected字段派生类是可以访问的（private不行）
	LinkTreeNode<T>* root;//指向树根
	int tree_size;//树的大小
	//这个地方不能加static，C++中静态变量只能在本类中使用，如果在别的类或文件中使用就会报错
	void(*visit)(LinkTreeNode<T>*);//函数temp，通过给此函数字段赋值以实现其他功能
	void preOrder(LinkTreeNode<T>* t)//前序遍历
	{
		if (t != NULL)
		{
			BinaryTree<T>::visit(t);
			preOrder(t->leftChild);
			preOrder(t->rightChild);
		}
	}
	void postOrder(LinkTreeNode<T>* t)//后序遍历
	{
		if (t != NULL)
		{
			postOrder(t->leftChild);
			postOrder(t->rightChild);
			BinaryTree<T>::visit(t);
		}
	}
	static void deleteNode_1_visit(LinkTreeNode<T>* t)
	{
		t->~LinkTreeNode();
		delete t;
	}
	static void output_1_visit(LinkTreeNode<T>* t)
	{
		outputer[output_index] = t->data;
		output_index++;
	}
private:
	static int output_index;
    static T* outputer;
};
//VS2017中，模板类中的静态变量必须这样初始化
template<class T>
int BinaryTree<T>::output_index = 0;
template<class T>
T* BinaryTree<T>::outputer = NULL;
