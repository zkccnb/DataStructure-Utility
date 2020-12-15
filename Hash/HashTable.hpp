#pragma once
#include"AbsDictionary.hpp"
#include<string>
//字典的哈希表实现
template<class K>
inline size_t getHashKey(const K& obj) { return (size_t)obj; }
template<class K,class V>
class Hash:public Dictionary<K,V>
{
public:
	Hash(const int& theCapacity);
	Hash(const Hash& theHash);
	~Hash();
	V& find(const K& theKey) const override;//返回字典中键为theKey的值V
	void insert(const Pair<K, V>& thePair)override;
	void erase(const K& theKey)override;
	
	friend std::ostream& operator<<(std::ostream& os, const Hash& theHash)
	{
		for (auto i = 0; i != theHash.capacity; i++)
		{
			if (theHash.hashTable[i] == NULL)
			{
				os << "NULL" <<std::endl;
			}
			else
			{
				os << theHash.hashTable[i]->key << "," << theHash.hashTable[i]->value << std::endl;
			}
		}
		return os;
	}
private:
	int capacity;//哈希表的最大容量，作为哈希函数的除数
	Pair<K, V>** hashTable;//存放哈希表，一维指针数组
};
template<class K, class V>
Hash<K,V>::Hash(const int& theCapacity) : capacity(theCapacity)
{
	this->dic_size = 0;
	hashTable = new Pair<K, V>*[capacity];
	for (auto i = 0; i != capacity; i++) hashTable[i] = NULL;
}
template<class K, class V>
Hash<K, V>::Hash(const Hash<K,V>& theHash) : capacity(theHash.capacity)
{
	this->dic_size = theHash.dic_size;
	if (hashTable != NULL)
	{
		for (auto i = 0; i < capacity; i++)
		{ delete hashTable[i]; hashTable[i] = NULL; }
		delete[] hashTable;
		hashTable = NULL;
	}
	//深拷贝
	hashTable = new Pair<K, V>*[capacity];
	for (auto i = 0; i < capacity; i++) hashTable[i] = new Pair<K, V>(*theHash.hashTable[i]);
	//std::cout << "copying!!!"<< std::endl;
}
template<class K, class V>
Hash<K, V>::~Hash()
{
	if (hashTable != NULL)
	{
		for (auto i = 0; i < capacity; i++)
		{
			delete hashTable[i]; hashTable[i] = NULL;
		}
		delete[] hashTable;
		hashTable = NULL;
	}
}
template<class K, class V>
V& Hash<K, V>::find(const K& theKey) const
{
	size_t target_hashKey = getHashKey(theKey);//获取目标哈希值
	size_t bucket = target_hashKey % capacity;//找到初始桶
	//如果初始桶是空的，直接确认表中无此键
	if (hashTable[bucket] == NULL) { throw "查无此键"; }
	else//初始桶非空：
	{
		//初始桶里装的不是目标数对：
		while (hashTable[bucket]->key != theKey)
		{
			bucket = (bucket + 1) % capacity;//找下一个桶
			//目前的桶装的是目标数对：
			if (hashTable[bucket]->key == theKey) return hashTable[bucket]->value;
			//已经查遍hash表:
			else if (bucket == target_hashKey)
			{
				throw "查无此键";
			}
		}
		//初始桶里装的是目标数对：
		return hashTable[bucket]->value;
	}
}
template<class K, class V>//插入的最坏复杂度是O(n)
void Hash<K, V>::insert(const Pair<K, V>& thePair)
{
	size_t hashKey = getHashKey(thePair.key);//根据键值获取哈希值
	size_t bucket = hashKey % capacity;//找到初始桶
	//不能放在初始桶：
	while (hashTable[bucket]!=NULL && hashTable[bucket]->key!=thePair.key)
	{
		bucket = (bucket + 1) % capacity;//找下一个桶
		//可以放在此桶了：
		if (hashTable[bucket] == NULL || hashTable[bucket]->key == thePair.key)
		{
			hashTable[bucket] = new Pair<K, V>(thePair);
			this->dic_size++;
			return;
		}
		//已经查遍hash表:
		else if (bucket == hashKey)
		{
			throw "表已满";
		}
	}
	//可以放在初始桶：
	hashTable[bucket] = new Pair<K, V>(thePair);
	this->dic_size++;
}
template<class K, class V>
void Hash<K, V>::erase(const K& theKey)
{
	size_t target_hashKey = getHashKey(theKey);//获取目标哈希值
	size_t bucket = target_hashKey % capacity;//找到初始桶
	//如果初始桶是空的，直接确认表中无此键
	if (hashTable[bucket] == NULL) { throw "查无此键，不需删除"; }
	else//初始桶非空：
	{
		//初始桶里装的不是目标数对：
		while (hashTable[bucket]->key != theKey)
		{
			bucket = (bucket + 1) % capacity;//找下一个桶
			//目前的桶装的是目标数对：
			if (hashTable[bucket]->key == theKey)
			{   delete hashTable[bucket]; 
			    hashTable[bucket] = NULL; 
				this->dic_size--;
				return;
			}
			//已经查遍hash表:
			else if (bucket == target_hashKey)
			{
				throw "查无此键，不需删除";
			}
		}
		//初始桶里装的是目标数对：
		delete hashTable[bucket];
		hashTable[bucket] = NULL;
		this->dic_size--;
	}
}
template<>//针对string型的获取hash值
inline size_t getHashKey(const std::string& obj)
{
	size_t hashKey = 0;
	for (auto i = 0; i < obj.length(); i++) hashKey = hashKey * 5 + obj.at(i);
	return hashKey;
}