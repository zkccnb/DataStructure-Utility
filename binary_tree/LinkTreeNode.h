#pragma once
#include<cstdio>
#include<iostream>
//����������ڵ���
template<class T>
class LinkTreeNode
{
public:
	T data;//���ڵ������
	LinkTreeNode<T>* leftChild;//���ӵ���ڵ�
	LinkTreeNode<T>* rightChild;//���ӵ��ҽڵ�

	LinkTreeNode() { leftChild = rightChild = NULL; }
	LinkTreeNode(const T& theData) :data(theData) { leftChild = rightChild = NULL; }
	LinkTreeNode(const T& theData, LinkTreeNode* theLeftNode, LinkTreeNode* theRightNode)
		:data(theData), leftChild(theLeftNode), rightChild(theRightNode) { }
	~LinkTreeNode() { data.~T(); }
};

