#pragma once
#include<cstdio>
#include<iostream>

//����ڵ�ṹ��
template<class T>
struct ChainNode
{
	//����
	T data;//����
	ChainNode<T>* pointer;//����ָ�룩

	//����
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
	ChainStack(const ChainStack<T>& theStack)//���ƹ���
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
	ChainStack(int theCapacity)//���캯��
	{
		stack_capacity = theCapacity;
		stack_size = 0;
	}
	~ChainStack()//��������
	{
		for (int i = 0; i < stack_size; i++)
		{
			ChainNode<T>* thisNode = stackBottom;
			stackBottom = stackBottom->pointer;
			thisNode->data.~T();//���T���ǻ������͵Ļ����ǵõ���T�����������
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
		if(stack_size==0) std::cout << "ջ�ѿգ����ܵ�ջ" << std::endl;
		else
		{
			ChainNode<T>* stackTopPrevious = stackBottom;//ջ����ǰ�ڵ�
			for (int i = 0; i < stack_size - 2; i++)//�ҵ�ջ��ǰ�ڵ�
			{
				stackTopPrevious = stackTopPrevious->pointer;
			}
			//�ͷ�ջ���ڵ��ڴ�
			stackTopPrevious->pointer->data.~T();
			delete stackTopPrevious->pointer;
			stackTopPrevious->pointer = nullptr;//ջ��ǰ�ڵ�ָ��ָ��
			stack_size--;
		}
		
	}
	void push(const T& theData)
	{
		if (stack_size == stack_capacity) std::cout << "ջ����������ѹջ" << std::endl;
		else
		{
			if (stack_size == 0) stackBottom = new ChainNode<T>(theData);
			else
			{
				ChainNode<T>* stackTop = stackBottom;//ջ���ڵ�
				for (int i = 0; i < stack_size - 1; i++)//�ҵ�ջ���ڵ�
				{
					stackTop = stackTop->pointer;
				}
				ChainNode<T>* pushNode = new ChainNode<T>(theData);
				stackTop->pointer = pushNode;
			}
			stack_size++;
		}
	}
	void output() const//������뵽�������
	{
		if (!empty())
		{
			ChainNode<T>* thisNode = stackBottom;//��ǰ�ڵ�
			for (int i = 0; i < stack_size; i++)
			{
				std::cout << thisNode->data << " ";
				thisNode = thisNode->pointer;
			}

			std::cout << "stack_size is:" << stack_size << std::endl;
		}
		else std::cout << "ջ�ǿյ�"<< std::endl;
	}

private:
	ChainNode<T>* stackBottom;//ջ��
	int stack_capacity;//ջ�������
	int stack_size;//��ǰջ�Ĵ�С
};