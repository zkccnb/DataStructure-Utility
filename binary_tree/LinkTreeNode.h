#pragma once
#include<cstdio>
#include<iostream>
//链表二叉树节点类
template<class T>
class LinkTreeNode
{
public:
	T data;//树节点的数据
	LinkTreeNode<T>* leftChild;//链接到左节点
	LinkTreeNode<T>* rightChild;//链接到右节点

	LinkTreeNode() { leftChild = rightChild = NULL; }
	LinkTreeNode(const T& theData) :data(theData) { leftChild = rightChild = NULL; }
	LinkTreeNode(const T& theData, LinkTreeNode* theLeftNode, LinkTreeNode* theRightNode)
		:data(theData), leftChild(theLeftNode), rightChild(theRightNode) { }
	~LinkTreeNode() { data.~T(); }
};

