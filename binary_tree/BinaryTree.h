#pragma once
#include"LinkTreeNode.h"
template<class T>
class BinaryTree
{
public:
	BinaryTree() //{ root = NULL; tree_size = 0; }
	{
		
	}
	~BinaryTree() {  }
	void preOrder(void(*theVisit)(LinkTreeNode<T>*))
	{
		visit = theVisit;
		preOrder(root);
	}
	void erase()
	{
		preOrder(deleteNode_1_visit);
		root = NULL;
		tree_size = 0;
	}
	void output()
	{
		preOrder(output_1_visit);
	}
	T& top()const { return root->data; }
	int size()const { return tree_size; }
	bool empty()const { return tree_size == 0; }

	LinkTreeNode<T>* root;//指向树根
protected:
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
	static void deleteNode_1_visit(LinkTreeNode<T>* t)
	{
		t->~LinkTreeNode();
		delete t;
	}
	static void output_1_visit(LinkTreeNode<T>* t)
	{
		std::cout << t->data << " ";
	}
	
};

