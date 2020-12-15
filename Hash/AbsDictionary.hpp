#pragma once
//���ļ��ṩPair���ͺͳ����ࣨdictionary��Node��
#include<iostream>
#include<string>
//��ֵ�Խṹ��
template<class K, class V>
struct Pair
{
	K key;
	V value;
	Pair() = default;
	Pair(const K& theKey, const V& theValue):key(theKey),value(theValue)
	{ }
	Pair(const Pair& pair):key(pair.key),value(pair.value)
	{ }
};

//�ڵ�ṹ����࣬��Ҫ����ʵ������ɶԽڵ�ָ����Զ���
template<class K, class V>
struct Node
{
	//����
	Pair<K, V> data;//��������ֻ�ṩ����

	//����
	Node() = default;
	//�������еĹ��췽��ֻ�ṩ�����ݵĳ�ʼ��
	Node(const Pair<K, V>& theData):data(theData)
	{ }
	virtual ~Node() { };
};

//�����ֵ���
template<class K, class V>
class Dictionary
{
public:
	Dictionary() = default;
	virtual ~Dictionary() = 0;
	inline bool empty() const { return dic_size == 0; }//�ж��Ƿ�Ϊ�ձ�
	inline int size() const { return dic_size; }//�������Ա��С

	virtual V& find(const K& theKey) const = 0;//����
	virtual void insert(const Pair<K, V>& thePair) = 0;//����
	virtual void erase(const K& theKey) = 0;//ɾ��

protected:
	int dic_size; //��ǰ�ֵ�Ĵ�С
};
template<class K, class V>
Dictionary<K, V>::~Dictionary()
{

}