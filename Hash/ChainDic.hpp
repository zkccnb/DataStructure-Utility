#pragma once
#include"AbsDictionary.hpp"
//�ֵ�����Ա�ʵ��

//����ڵ�ṹ��
template<class K, class V>
//ʵ��Node�ṹ������ڵ�
struct ChainNode:Node<K,V>
{
	//����
	ChainNode<K, V>* pointer;//����ָ�룩

	//����
	ChainNode(const Pair<K, V>& theData):Node<K, V>(theData)
	{ }
	ChainNode(const Pair<K, V>& theData, ChainNode<K, V>* nextNode) 
	:Node<K, V>(theData)
	{ 
		pointer = new ChainNode<K, V>(*nextNode);//���
	}
	~ChainNode()
	{ }
};

//�����ֵ���
template<class K, class V>
class ChainDictionary:public Dictionary<K,V>
{
public:
	ChainDictionary() = default;
	ChainDictionary(const ChainDictionary& theDictionary);
	~ChainDictionary();
	
	V& find(const K& theKey) const override;//�����ֵ��м�ΪtheKey��ֵV
	void insert(const Pair<K, V>& thePair)override;
	void erase(const K& theKey)override;
	//ע�⣬��Ԫ�������������ǳ�Ա��������ʵ����
	friend std::ostream& operator<<(std::ostream& os, const ChainDictionary& theDictionary)
	{
		if (!theDictionary.empty())
		{
			ChainNode<K, V>* thisNode = theDictionary.headNode;//��ǰ�ڵ�
			for (int i = 0; i < theDictionary.dic_size; i++)
			{
				os << thisNode->data.key << "," << thisNode->data.value << std::endl;
				thisNode = thisNode->pointer;
			}

			os << "dic_size is:" << theDictionary.dic_size << std::endl;
		}
		return os;
	}
private:
	ChainNode<K, V>* headNode;//ͷ�ڵ�洢��һ������
};


template<class K, class V>
ChainDictionary<K,V>::ChainDictionary(const ChainDictionary& theDictionary)
{
	ChainNode<K, V>* sourceNode = *theDictionary.headNode;
	headNode = new ChainNode<K, V>*(sourceNode->data);//��ͷ�ڵ㸴�ƹ�ȥ
	sourceNode = theDictionary.headNode->pointer;//theDictionaryָ�����
	ChainNode<K, V>* targetNode = headNode->pointer;//Ŀ��ָ�����
	while (sourceNode != nullptr)//�ظ����������ڵ�
	{
		targetNode->data = sourceNode->data;
		sourceNode = sourceNode->pointer;
		targetNode = targetNode->pointer;
	}
	targetNode->pointer = nullptr;
}
template<class K, class V>
ChainDictionary<K, V>::~ChainDictionary()
{
	for (int i = 0; i < this->dic_size; i++)//�������ﲻҪ��ָ����������״�
	{
		ChainNode<K, V>* nextNode = headNode->pointer;//�Ȱ���һ���ڵ㱣������
		//K,V���ǻ������͵Ļ����ǵõ���K��V����������
		headNode->data.key.~K();
		headNode->data.value.~V();
		delete headNode;//ɾ����ǰ�ڵ�
		headNode = nextNode;//��ǰ�ڵ����һ��
	}
}
template<class K, class V>
V& ChainDictionary<K, V>::find(const K& theKey) const//�����ֵ��м�ΪtheKey��ֵV
{
	int i;
	ChainNode<K, V>* thisNode = headNode;
	for (i = 0; i < this->dic_size; i++)
	{
		if (i == this->dic_size - 1) break;
		else if (thisNode->data.key != theKey)
		{
			thisNode = thisNode->pointer;
		}
		else break;
	}
	if (thisNode->data.key == theKey) return thisNode->data.value;
	else throw "�ֵ���û�д�ֵ";
}
template<class K, class V>
void ChainDictionary<K, V>::insert(const Pair<K, V>& thePair)
{
	ChainNode<K, V>* endNode = headNode;
	if (this->dic_size == 0) headNode = new ChainNode<K, V>(thePair);
	else
	{
		for (int i = 0; i < this->dic_size - 1; i++) endNode = endNode->pointer;
		endNode->pointer = new ChainNode<K, V>(thePair);
	}
	this->dic_size++;
}
template<class K, class V>
void ChainDictionary<K, V>::erase(const K& theKey)
{
	int i;
	ChainNode<K, V>* previousNode = headNode;
	if (headNode->data.key == theKey)
	{
		headNode->data.key.~K();
		headNode->data.value.~V();
		headNode = headNode->pointer;
		this->dic_size--;
	}
	else
	{
		for (i = 0; i < this->dic_size; i++)
		{
			if (i == this->dic_size - 1) break;
			else if (previousNode->pointer->data.key != theKey)
			{
				previousNode = previousNode->pointer;
			}
			else break;
		}
		if (i == this->dic_size - 1) std::cout << "�ֵ���û�д�ֵ,�޷�ɾ��" << std::endl;
		else if (previousNode->pointer->data.key == theKey)
		{
			//����Ŀ���ֵ��
			previousNode->pointer->data.key.~K();
			previousNode->pointer->data.value.~V();
			//ǰ��ڵ�ָ�����ڵ�
			previousNode->pointer = previousNode->pointer->pointer;
			this->dic_size--;
		}
	}
}