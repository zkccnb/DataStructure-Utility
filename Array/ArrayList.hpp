#pragma once
#include<iostream>
//���е���Ԫ�����ǡ���������������Ҫ����ǰ������ȫ�ֺ���
template<class T>
class ArrayList;
template<class T>
std::ostream& operator<<(std::ostream& out, ArrayList<T>& theList);
template<class T>
class ArrayList
{
public:
	template<class T>//��Ԫ����ʵ������������ģ������
	friend std::ostream& operator<<(std::ostream& out, ArrayList<T>& theList);
	ArrayList(const int& theCapacity);//����
	ArrayList(const ArrayList<T>& theList);//��������
	~ArrayList();//����
	ArrayList<T>& operator=(const ArrayList<T>& theList);//���ظ�ֵ������ֹǳ����
	T& operator[](const int& index);//�����±���������������±�ֱ�ӷ������Ա��ṩһ��array�Ľӿ�
	void push(const T& theData);
	void delData();
	inline bool isEmpty()const { return size==0; }
	inline int sizeOf()const { return size; }
	inline int capacityOf()const { return capacity; }
private:
	int size;
	int capacity;
	T* array;
	void enlarge();//��������
};

//������������
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
	array = new T[capacity];//���
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
	array = new T[capacity];//���
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
		std::cout << "����Խ��" << std::endl;
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