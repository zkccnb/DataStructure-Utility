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


template<class T>
class ChainStack
{
public:
	ChainStack(const ChainStack<T>& theStack)//复制构造
	{
		stack_capacity = theStack.stack_capacity;
		stack_size = theStack.stack_size;
		ChainNode<T>* sourceNode = theStack.stackBottom;
		stackBottom = new ChainNode<T>(sourceNode->data);
		ChainNode<T>* thisNode = stackBottom;
		
		for (int i = 0; i < stack_size; i++)
		{
			thisNode = thisNode->pointer;
			sourceNode = sourceNode->pointer;
			thisNode->data = sourceNode->data;
		}
	}
	ChainStack(int theCapacity)//构造函数
	{
		stack_capacity = theCapacity;
		stack_size = 0;
	}
	~ChainStack()//析构函数
	{
		for (int i = 0; i < stack_size; i++)
		{
			ChainNode<T>* thisNode = stackBottom;
			stackBottom = stackBottom->pointer;
			thisNode->data.~T();//如果T不是基础类型的话，记得调用T类的析构函数
			delete thisNode;
		}
	}
	bool empty() const { return stack_size == 0; }
	int size() const { return stack_size; }
	T& top() const
	{
		ChainNode<T>* stackTop = stackBottom;
		for (int i = 0; i < stack_size-1; i++)
		{
			stackTop = stackTop->pointer;
		}
		return stackTop->data;
	}
	void pop()
	{
		if(stack_size==0) std::cout << "栈已空，不能弹栈" << std::endl;
		else
		{
			ChainNode<T>* stackTopPrevious = stackBottom;//栈顶的前节点
			for (int i = 0; i < stack_size - 2; i++)//找到栈顶前节点
			{
				stackTopPrevious = stackTopPrevious->pointer;
			}
			//释放栈顶节点内存
			stackTopPrevious->pointer->data.~T();
			delete stackTopPrevious->pointer;
			stackTopPrevious->pointer = nullptr;//栈顶前节点指针指空
			stack_size--;
		}
		
	}
	void push(const T& theData)
	{
		if (stack_size == stack_capacity) std::cout << "栈已满，不能压栈" << std::endl;
		else
		{
			if (stack_size == 0) stackBottom = new ChainNode<T>(theData);
			else
			{
				ChainNode<T>* stackTop = stackBottom;//栈顶节点
				for (int i = 0; i < stack_size - 1; i++)//找到栈顶节点
				{
					stackTop = stackTop->pointer;
				}
				ChainNode<T>* pushNode = new ChainNode<T>(theData);
				stackTop->pointer = pushNode;
			}
			stack_size++;
		}
	}
	void output() const//将表插入到输出流中
	{
		if (!empty())
		{
			ChainNode<T>* thisNode = stackBottom;//当前节点
			for (int i = 0; i < stack_size; i++)
			{
				std::cout << thisNode->data << " ";
				thisNode = thisNode->pointer;
			}

			std::cout << "stack_size is:" << stack_size << std::endl;
		}
		else std::cout << "栈是空的"<< std::endl;
	}

private:
	ChainNode<T>* stackBottom;//栈底
	int stack_capacity;//栈最大容量
	int stack_size;//当前栈的大小
};