#pragma once
#include<iostream>
//类中的友元声明是“假声明”，还需要在最前面声明全局函数
template<class T>
class ArrayList;
template<class T>
std::ostream& operator<<(std::ostream& out, ArrayList<T>& theList);
template<class T>
class ArrayList
{
public:
	template<class T>//友元类外实现这里必须加上模板声明
	friend std::ostream& operator<<(std::ostream& out, ArrayList<T>& theList);
	ArrayList(const int& theCapacity);//构造
	ArrayList(const ArrayList<T>& theList);//拷贝构造
	~ArrayList();//析构
	ArrayList<T>& operator=(const ArrayList<T>& theList);//重载赋值符，防止浅拷贝
	T& operator[](const int& index);//重载下标运算符，可以用下标直接访问线性表，提供一个array的接口
	void push(const T& theData);
	void delData();
	inline bool isEmpty()const { return size==0; }
	inline int sizeOf()const { return size; }
	inline int capacityOf()const { return capacity; }
private:
	int size;
	int capacity;
	T* array;
	void enlarge();//数组扩容
};

//重载输出运算符
template<class T>
std::ostream& operator<<(std::ostream& out, ArrayList<T>& theList)
{
	for (auto i=0; i != theList.size; i++)
	{
		out << theList.array[i] << " ";
	}
	return out;
}
template<class T>
ArrayList<T>::ArrayList(const int& theCapacity):capacity(theCapacity)
{
	size = 0;
	array = new T[capacity];
}
template<class T>
ArrayList<T>::ArrayList(const ArrayList<T>& theList)
{ 
	size = theList.size;
	capacity = theList.capacity;
	if (array != NULL) { delete[] array; array = NULL; }
	array = new T[capacity];//深拷贝
	for (auto i = 0; i != capacity; i++) array[i] = theList.array[i];
}
template<class T>
ArrayList<T>::~ArrayList()
{
	delete[] array;
	array = NULL;
}
template<class T>
ArrayList<T>& ArrayList<T>:: operator=(const ArrayList<T>& theList)
{
	size = theList.size;
	capacity = theList.capacity;
	if (array != NULL) { delete[] array; array = NULL; }
	array = new T[capacity];//深拷贝
	for (auto i = 0; i != capacity; i++) array[i] = theList.array[i];
	return *this;
}
template<class T>
void ArrayList<T>::push(const T& theData)
{
	if (size == capacity) enlarge();
	array[size] = theData;
	size++;
}
template<class T>
void ArrayList<T>::delData()
{
	if (size == 0) return;
	size--;
}
template<class T>
T& ArrayList<T>::operator[](const int& index)
{
	if(index<size && index>=0) return array[index];
	else
	{
		std::cout << "索引越界" << std::endl;
	}
}
template<class T>
void ArrayList<T>::enlarge()
{
	capacity *= 2;
	T* temp = new T[capacity];
	for (auto i = 0; i != capacity / 2; i++) temp[i] = array[i];
	delete array;
	array = new T[capacity];
	for (auto i = 0; i != capacity / 2; i++) array[i] = temp[i];
}