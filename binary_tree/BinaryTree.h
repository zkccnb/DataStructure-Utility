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

	LinkTreeNode<T>* root;//ָ������
protected:
	int tree_size;//���Ĵ�С
	//����ط����ܼ�static��C++�о�̬����ֻ���ڱ�����ʹ�ã�����ڱ������ļ���ʹ�þͻᱨ��
	void(*visit)(LinkTreeNode<T>*);//����temp��ͨ�����˺����ֶθ�ֵ��ʵ����������
	void preOrder(LinkTreeNode<T>* t)//ǰ�����
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

