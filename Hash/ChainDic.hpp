#pragma once
#include"AbsDictionary.hpp"
//字典的线性表实现

//链表节点结构体
template<class K, class V>
//实现Node结构：链表节点
struct ChainNode:Node<K,V>
{
	//数据
	ChainNode<K, V>* pointer;//链（指针）

	//方法
	ChainNode(const Pair<K, V>& theData):Node<K, V>(theData)
	{ }
	ChainNode(const Pair<K, V>& theData, ChainNode<K, V>* nextNode) 
	:Node<K, V>(theData)
	{ 
		pointer = new ChainNode<K, V>(*nextNode);//深拷贝
	}
	~ChainNode()
	{ }
};

//链表字典类
template<class K, class V>
class ChainDictionary:public Dictionary<K,V>
{
public:
	ChainDictionary() = default;
	ChainDictionary(const ChainDictionary& theDictionary);
	~ChainDictionary();
	
	V& find(const K& theKey) const override;//返回字典中键为theKey的值V
	void insert(const Pair<K, V>& thePair)override;
	void erase(const K& theKey)override;
	//注意，友元函数看起来像是成员函数，其实不是
	friend std::ostream& operator<<(std::ostream& os, const ChainDictionary& theDictionary)
	{
		if (!theDictionary.empty())
		{
			ChainNode<K, V>* thisNode = theDictionary.headNode;//当前节点
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
	ChainNode<K, V>* headNode;//头节点存储第一个数据
};


template<class K, class V>
ChainDictionary<K,V>::ChainDictionary(const ChainDictionary& theDictionary)
{
	ChainNode<K, V>* sourceNode = *theDictionary.headNode;
	headNode = new ChainNode<K, V>*(sourceNode->data);//把头节点复制过去
	sourceNode = theDictionary.headNode->pointer;//theDictionary指针后移
	ChainNode<K, V>* targetNode = headNode->pointer;//目标指针后移
	while (sourceNode != nullptr)//重复复制其他节点
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
	for (int i = 0; i < this->dic_size; i++)//建议这里不要用指针操作，容易错
	{
		ChainNode<K, V>* nextNode = headNode->pointer;//先把下一个节点保存下来
		//K,V不是基础类型的话，记得调用K，V的析构函数
		headNode->data.key.~K();
		headNode->data.value.~V();
		delete headNode;//删除当前节点
		headNode = nextNode;//当前节点后移一个
	}
}
template<class K, class V>
V& ChainDictionary<K, V>::find(const K& theKey) const//返回字典中键为theKey的值V
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
	else throw "字典中没有此值";
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
		if (i == this->dic_size - 1) std::cout << "字典中没有此值,无法删除" << std::endl;
		else if (previousNode->pointer->data.key == theKey)
		{
			//析构目标键值对
			previousNode->pointer->data.key.~K();
			previousNode->pointer->data.value.~V();
			//前序节点指向后序节点
			previousNode->pointer = previousNode->pointer->pointer;
			this->dic_size--;
		}
	}
}