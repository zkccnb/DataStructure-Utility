// 链表二叉树.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "BinaryTree.h"
//注意：为了测试前序遍历是否好用，这里在主函数里手动定义了各节点的值，从而创建了一个二叉树
//实际上各种树应该有自己初始化的方法
//另外，使用此类构建其他树时，需要把root字段改成私有字段，这里为了便于测试将其变成公共字段
//给函数传入一个函数参数的方法是本例的重点
int main()
{
	BinaryTree<int> tree;
	tree.root = new LinkTreeNode<int>(0);
	tree.root->leftChild = new LinkTreeNode<int>(1);
	tree.root->rightChild = new LinkTreeNode<int>(2);
	tree.root->leftChild->leftChild = new LinkTreeNode<int>(3);
	tree.root->leftChild->rightChild = new LinkTreeNode<int>(4);
	tree.root->rightChild->leftChild = new LinkTreeNode<int>(5);
	tree.root->rightChild->rightChild = new LinkTreeNode<int>(6);
	tree.output();
	return 0;
}
