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
	//ʮ��ע�⣺ɾ���ڵ�ʱ�����ú��������
	//��ǰ������Ļ��൱��ɾ��ڵ����������һ���ڵ㣬���±���
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

protected://protected�ֶ��������ǿ��Է��ʵģ�private���У�
	LinkTreeNode<T>* root;//ָ������
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
	void postOrder(LinkTreeNode<T>* t)//�������
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
//VS2017�У�ģ�����еľ�̬��������������ʼ��
template<class T>
int BinaryTree<T>::output_index = 0;
template<class T>
T* BinaryTree<T>::outputer = NULL;
