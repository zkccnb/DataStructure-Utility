#pragma once
#include<cstdio>
#include<iostream>

//链表节点结构体
template<class T>
struct ChainNode
{
	//数据
	T data;//数据
	ChainNode<T>* pointer;//链（指针）

	//方法
	ChainNode();
	ChainNode(const T& theData)
	{
		this->data = theData;
	}
	ChainNode(const T& theData, ChainNode<T>* nextNode)
	{
		this->data = theData;
		this->pointer = nextNode;
	}
};

//链表类
template<class T>
class ChainList
{
public:
	ChainList(int theCapacity)//构造函数,传入初始化的链表容量
	{
		//创建一个空链表
		list_capacity = theCapacity;
		headNode = nullptr;
	}
	ChainList(const ChainList<T>& theList)//复制构造函数
	{
		list_capacity = theList.list_capacity;
		ChainNode<T>* sourceNode = theList.headNode;
		headNode = new ChainNode<T>(sourceNode->data);//把头节点复制过去
		sourceNode = theList.headNode->pointer;//theList指针后移
		ChainNode<T>* targetNode = headNode->pointer;//目标指针后移
		while (sourceNode != nullptr)//重复复制其他节点
		{
			targetNode->data = sourceNode->data;
			sourceNode = sourceNode->pointer;
			targetNode = targetNode->pointer;
		}
		targetNode->pointer = nullptr;
	}
	~ChainList()//析构函数
	{
		for(int i=0;i<list_size;i++)//建议这里不要用指针操作，容易错
		{
			ChainNode<T>* nextNode = headNode->pointer;//先把下一个节点保存下来
			headNode->data.~T();//如果T不是基础类型的话，记得调用T类的析构函数
			delete headNode;//删除当前节点
			headNode = nextNode;//当前节点后移一个
		}
	}
	bool empty() const//判断是否为空表
	{
		return list_size == 0;
	}
	int size() const//返回线性表大小
	{
		return list_size;
	}
	T& get(int theIndex) const//给定索引返回表中数据
	{
		
			ChainNode<T>* thisNode = headNode;
			if (theIndex > (list_size - 1))
			{
				std::cout << "给定的索引位置没有此元素" << std::endl;
			}
			else
			{
				for (int i = 0; i < theIndex; i++)
				{
					thisNode = thisNode->pointer;
				}
				return thisNode->data;
			}
		
	}
	int IndexOf(const T& theData) const//给定数据返回对应索引
	{
		
			int index = 0;
			ChainNode<T>* thisNode = headNode;
			for (int i = 0; i < list_size; i++)
			{
				if (thisNode->data == theData) return i;
				thisNode = thisNode->pointer;
			}
			std::cout << "表中没有给定的元素" << std::endl;
		
	}
	void erase(int theIndex)//删除指定索引的元素，索引从0开始算起
	{
			ChainNode<T>* thisNode = headNode;//当前节点
			ChainNode<T>* eraseNode = nullptr;//要删除的目标节点
			ChainNode<T>* previousNode = nullptr;//目标节点的前节点
			//输入索引大于当前表中元素个数
			if (theIndex > list_size - 1) std::cout << "指定位置没有元素，无法删除" << std::endl;
			else
			{
				if (theIndex == 0)//删除第一个节点时
				{
					eraseNode = thisNode;
					headNode = headNode->pointer;//第二个节点作为头节点
				}
				else//删除不是第一个节点时
				{
					for (int i = 0; i < theIndex; i++)
					{
						thisNode = thisNode->pointer;
						if (i == (theIndex - 2))  previousNode = thisNode;//获取前节点
					}
					eraseNode = thisNode;//获取目标删除节点
					previousNode->pointer = eraseNode->pointer;//将前节点的指针指向目标节点的后一个节点
				}

				delete eraseNode;//删除目标节点
				list_size--;//别忘了自减链表长度
			}
		
	}
	void insert(int theIndex, const T& theData)//向指定索引位置插入元素，索引从0开始算起
	{
			ChainNode<T>* thisNode = headNode;//当前节点
			ChainNode<T>* insertNode = new ChainNode<T>(theData);//即将插入的节点
			ChainNode<T>* previousNode = headNode;//插入节点的前节点

			if (list_size == list_capacity) std::cout << "链表溢出" << std::endl;
			else
			{
				if (theIndex == 0)//在首元素插入节点时
				{
					headNode = new ChainNode<T>(theData);//第一个节点为空时必须初始化
					list_size++;//别忘了自增链表长度
				}
				else//不在首元素插入节点时
				{
					for (int i = 0; i < theIndex - 1; i++)
					{
						thisNode = thisNode->pointer;
						previousNode = thisNode;//获取插入节点的前节点
					}
					insertNode->pointer = previousNode->pointer;//将插入节点的指针指向其后一个节点
					previousNode->pointer = insertNode;//将插入节点的前节点指针指向插入节点
					list_size++;//别忘了自增链表长度
				}
			}
	}
	void push_back(const T& theData)//在最后一个索引位置压表
	{
			ChainNode<T>* thisNode = headNode;//当前节点
			if (list_size == 0)
			{
				headNode = new ChainNode<T>(theData);//如果压入之前为空表
				list_size++;
			}
			else//不是空表
			{
				for (int i = 0; i < list_size-1; i++)
				{
					thisNode = thisNode->pointer;
				}
				thisNode->pointer = new ChainNode<T>(theData);//压入
				list_size++;
			}
	}
	void output() const//将表插入到输出流中
	{
		if (!empty())
		{
			ChainNode<T>* thisNode = headNode;//当前节点
			for (int i = 0; i < list_size; i++)
			{
				std::cout << thisNode->data << " ";
				thisNode = thisNode->pointer;
			}

			std::cout << "list_size is:" << list_size << std::endl;
		}
	}

private:
	ChainNode<T>* headNode;//头节点存储第一个数据
	int list_size; //当前线性表的大小
	int list_capacity;//设定的最大容量
};