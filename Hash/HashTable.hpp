#pragma once
#include"AbsDictionary.hpp"
#include<string>
//�ֵ�Ĺ�ϣ��ʵ��
template<class K>
inline size_t getHashKey(const K& obj) { return (size_t)obj; }
template<class K,class V>
class Hash:public Dictionary<K,V>
{
public:
	Hash(const int& theCapacity);
	Hash(const Hash& theHash);
	~Hash();
	V& find(const K& theKey) const override;//�����ֵ��м�ΪtheKey��ֵV
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
	int capacity;//��ϣ��������������Ϊ��ϣ�����ĳ���
	Pair<K, V>** hashTable;//��Ź�ϣ��һάָ������
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
	//���
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
	size_t target_hashKey = getHashKey(theKey);//��ȡĿ���ϣֵ
	size_t bucket = target_hashKey % capacity;//�ҵ���ʼͰ
	//�����ʼͰ�ǿյģ�ֱ��ȷ�ϱ����޴˼�
	if (hashTable[bucket] == NULL) { throw "���޴˼�"; }
	else//��ʼͰ�ǿգ�
	{
		//��ʼͰ��װ�Ĳ���Ŀ�����ԣ�
		while (hashTable[bucket]->key != theKey)
		{
			bucket = (bucket + 1) % capacity;//����һ��Ͱ
			//Ŀǰ��Ͱװ����Ŀ�����ԣ�
			if (hashTable[bucket]->key == theKey) return hashTable[bucket]->value;
			//�Ѿ����hash��:
			else if (bucket == target_hashKey)
			{
				throw "���޴˼�";
			}
		}
		//��ʼͰ��װ����Ŀ�����ԣ�
		return hashTable[bucket]->value;
	}
}
template<class K, class V>//���������Ӷ���O(n)
void Hash<K, V>::insert(const Pair<K, V>& thePair)
{
	size_t hashKey = getHashKey(thePair.key);//���ݼ�ֵ��ȡ��ϣֵ
	size_t bucket = hashKey % capacity;//�ҵ���ʼͰ
	//���ܷ��ڳ�ʼͰ��
	while (hashTable[bucket]!=NULL && hashTable[bucket]->key!=thePair.key)
	{
		bucket = (bucket + 1) % capacity;//����һ��Ͱ
		//���Է��ڴ�Ͱ�ˣ�
		if (hashTable[bucket] == NULL || hashTable[bucket]->key == thePair.key)
		{
			hashTable[bucket] = new Pair<K, V>(thePair);
			this->dic_size++;
			return;
		}
		//�Ѿ����hash��:
		else if (bucket == hashKey)
		{
			throw "������";
		}
	}
	//���Է��ڳ�ʼͰ��
	hashTable[bucket] = new Pair<K, V>(thePair);
	this->dic_size++;
}
template<class K, class V>
void Hash<K, V>::erase(const K& theKey)
{
	size_t target_hashKey = getHashKey(theKey);//��ȡĿ���ϣֵ
	size_t bucket = target_hashKey % capacity;//�ҵ���ʼͰ
	//�����ʼͰ�ǿյģ�ֱ��ȷ�ϱ����޴˼�
	if (hashTable[bucket] == NULL) { throw "���޴˼�������ɾ��"; }
	else//��ʼͰ�ǿգ�
	{
		//��ʼͰ��װ�Ĳ���Ŀ�����ԣ�
		while (hashTable[bucket]->key != theKey)
		{
			bucket = (bucket + 1) % capacity;//����һ��Ͱ
			//Ŀǰ��Ͱװ����Ŀ�����ԣ�
			if (hashTable[bucket]->key == theKey)
			{   delete hashTable[bucket]; 
			    hashTable[bucket] = NULL; 
				this->dic_size--;
				return;
			}
			//�Ѿ����hash��:
			else if (bucket == target_hashKey)
			{
				throw "���޴˼�������ɾ��";
			}
		}
		//��ʼͰ��װ����Ŀ�����ԣ�
		delete hashTable[bucket];
		hashTable[bucket] = NULL;
		this->dic_size--;
	}
}
template<>//���string�͵Ļ�ȡhashֵ
inline size_t getHashKey(const std::string& obj)
{
	size_t hashKey = 0;
	for (auto i = 0; i < obj.length(); i++) hashKey = hashKey * 5 + obj.at(i);
	return hashKey;
}