#pragma once
//本文件提供Pair类型和抽象类（dictionary、Node）
#include<iostream>
#include<string>
//键值对结构体
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

//节点结构体基类，需要其他实现以完成对节点指针的自定义
template<class K, class V>
struct Node
{
	//数据
	Pair<K, V> data;//抽象类中只提供数据

	//方法
	Node() = default;
	//抽象类中的构造方法只提供对数据的初始化
	Node(const Pair<K, V>& theData):data(theData)
	{ }
	virtual ~Node() { };
};

//抽象字典类
template<class K, class V>
class Dictionary
{
public:
	Dictionary() = default;
	virtual ~Dictionary() = 0;
	inline bool empty() const { return dic_size == 0; }//判断是否为空表
	inline int size() const { return dic_size; }//返回线性表大小

	virtual V& find(const K& theKey) const = 0;//查找
	virtual void insert(const Pair<K, V>& thePair) = 0;//插入
	virtual void erase(const K& theKey) = 0;//删除

protected:
	int dic_size; //当前字典的大小
};
template<class K, class V>
Dictionary<K, V>::~Dictionary()
{

}