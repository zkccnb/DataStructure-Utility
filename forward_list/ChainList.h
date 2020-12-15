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

//������
template<class T>
class ChainList
{
public:
	ChainList(int theCapacity)//���캯��,�����ʼ������������
	{
		//����һ��������
		list_capacity = theCapacity;
		headNode = nullptr;
	}
	ChainList(const ChainList<T>& theList)//���ƹ��캯��
	{
		list_capacity = theList.list_capacity;
		ChainNode<T>* sourceNode = theList.headNode;
		headNode = new ChainNode<T>(sourceNode->data);//��ͷ�ڵ㸴�ƹ�ȥ
		sourceNode = theList.headNode->pointer;//theListָ�����
		ChainNode<T>* targetNode = headNode->pointer;//Ŀ��ָ�����
		while (sourceNode != nullptr)//�ظ����������ڵ�
		{
			targetNode->data = sourceNode->data;
			sourceNode = sourceNode->pointer;
			targetNode = targetNode->pointer;
		}
		targetNode->pointer = nullptr;
	}
	~ChainList()//��������
	{
		for(int i=0;i<list_size;i++)//�������ﲻҪ��ָ����������״�
		{
			ChainNode<T>* nextNode = headNode->pointer;//�Ȱ���һ���ڵ㱣������
			headNode->data.~T();//���T���ǻ������͵Ļ����ǵõ���T�����������
			delete headNode;//ɾ����ǰ�ڵ�
			headNode = nextNode;//��ǰ�ڵ����һ��
		}
	}
	bool empty() const//�ж��Ƿ�Ϊ�ձ�
	{
		return list_size == 0;
	}
	int size() const//�������Ա��С
	{
		return list_size;
	}
	T& get(int theIndex) const//�����������ر�������
	{
		
			ChainNode<T>* thisNode = headNode;
			if (theIndex > (list_size - 1))
			{
				std::cout << "����������λ��û�д�Ԫ��" << std::endl;
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
	int IndexOf(const T& theData) const//�������ݷ��ض�Ӧ����
	{
		
			int index = 0;
			ChainNode<T>* thisNode = headNode;
			for (int i = 0; i < list_size; i++)
			{
				if (thisNode->data == theData) return i;
				thisNode = thisNode->pointer;
			}
			std::cout << "����û�и�����Ԫ��" << std::endl;
		
	}
	void erase(int theIndex)//ɾ��ָ��������Ԫ�أ�������0��ʼ����
	{
			ChainNode<T>* thisNode = headNode;//��ǰ�ڵ�
			ChainNode<T>* eraseNode = nullptr;//Ҫɾ����Ŀ��ڵ�
			ChainNode<T>* previousNode = nullptr;//Ŀ��ڵ��ǰ�ڵ�
			//�����������ڵ�ǰ����Ԫ�ظ���
			if (theIndex > list_size - 1) std::cout << "ָ��λ��û��Ԫ�أ��޷�ɾ��" << std::endl;
			else
			{
				if (theIndex == 0)//ɾ����һ���ڵ�ʱ
				{
					eraseNode = thisNode;
					headNode = headNode->pointer;//�ڶ����ڵ���Ϊͷ�ڵ�
				}
				else//ɾ�����ǵ�һ���ڵ�ʱ
				{
					for (int i = 0; i < theIndex; i++)
					{
						thisNode = thisNode->pointer;
						if (i == (theIndex - 2))  previousNode = thisNode;//��ȡǰ�ڵ�
					}
					eraseNode = thisNode;//��ȡĿ��ɾ���ڵ�
					previousNode->pointer = eraseNode->pointer;//��ǰ�ڵ��ָ��ָ��Ŀ��ڵ�ĺ�һ���ڵ�
				}

				delete eraseNode;//ɾ��Ŀ��ڵ�
				list_size--;//�������Լ�������
			}
		
	}
	void insert(int theIndex, const T& theData)//��ָ������λ�ò���Ԫ�أ�������0��ʼ����
	{
			ChainNode<T>* thisNode = headNode;//��ǰ�ڵ�
			ChainNode<T>* insertNode = new ChainNode<T>(theData);//��������Ľڵ�
			ChainNode<T>* previousNode = headNode;//����ڵ��ǰ�ڵ�

			if (list_size == list_capacity) std::cout << "�������" << std::endl;
			else
			{
				if (theIndex == 0)//����Ԫ�ز���ڵ�ʱ
				{
					headNode = new ChainNode<T>(theData);//��һ���ڵ�Ϊ��ʱ�����ʼ��
					list_size++;//����������������
				}
				else//������Ԫ�ز���ڵ�ʱ
				{
					for (int i = 0; i < theIndex - 1; i++)
					{
						thisNode = thisNode->pointer;
						previousNode = thisNode;//��ȡ����ڵ��ǰ�ڵ�
					}
					insertNode->pointer = previousNode->pointer;//������ڵ��ָ��ָ�����һ���ڵ�
					previousNode->pointer = insertNode;//������ڵ��ǰ�ڵ�ָ��ָ�����ڵ�
					list_size++;//����������������
				}
			}
	}
	void push_back(const T& theData)//�����һ������λ��ѹ��
	{
			ChainNode<T>* thisNode = headNode;//��ǰ�ڵ�
			if (list_size == 0)
			{
				headNode = new ChainNode<T>(theData);//���ѹ��֮ǰΪ�ձ�
				list_size++;
			}
			else//���ǿձ�
			{
				for (int i = 0; i < list_size-1; i++)
				{
					thisNode = thisNode->pointer;
				}
				thisNode->pointer = new ChainNode<T>(theData);//ѹ��
				list_size++;
			}
	}
	void output() const//������뵽�������
	{
		if (!empty())
		{
			ChainNode<T>* thisNode = headNode;//��ǰ�ڵ�
			for (int i = 0; i < list_size; i++)
			{
				std::cout << thisNode->data << " ";
				thisNode = thisNode->pointer;
			}

			std::cout << "list_size is:" << list_size << std::endl;
		}
	}

private:
	ChainNode<T>* headNode;//ͷ�ڵ�洢��һ������
	int list_size; //��ǰ���Ա�Ĵ�С
	int list_capacity;//�趨���������
};