#pragma once
#include<iostream>
#include<cstdio>
template<class T>
class maxHeap
{
	//����ѵ��ص��ǣ����κ�һ��֧·���¿���ֵ��Զ�����󣨵�������ȣ���������һ����ȫ������
public:
	maxHeap(const int& initArraySize,T* initHeapArray)//���캯��
	{
		//����������С����ͶѴ�Сһ��
		array_size = initArraySize;
		heap_size = array_size;
		heap = new T[array_size];
		for (int i = 0; i < array_size; i++) heap[i]= initHeapArray[i];
		initHeap();//���ó�ʼ��������ÿ�ν����ѵ�ʱ�򶼽���һ����׼�Ķ�
	}
	maxHeap(const maxHeap<T>& theHeap)//���ƹ���
	{
		array_size = theHeap.array_size;
		heap_size = theHeap.heap_size;
		heap = theHeap.heap;
	}
	~maxHeap()//��������
	{
		for (int i = 0; i < heap_size; i++) heap[i].~T();
		delete[] heap;
	}

	bool empty() { return heap_size == 0; }
	int size() { return heap_size; }
	T& top() { return heap[0]; }
	void pop()//���ѣ������Ѷ�Ԫ��
	{
		heap[0].~T();//ɾ���Ѷ�
		int thisIndex = 1;
		int childIndex = 2;
		while (childIndex <= heap_size)
		{
			if (heap[childIndex - 1] < heap[childIndex]) childIndex++;//ȡ�����ӽڵ�������
			//�����ǰ�ڵ������ӽڵ���ڶ�β�ڵ㣬�Ѹ�����ӽڵ��������丸�ڵ�
			if (heap[heap_size - 1] < heap[childIndex - 1])
			{
				heap[thisIndex - 1] = heap[childIndex - 1];
			}
			else break;//������������ѭ����˵����ʱ��thisIndex���Դ�Ŷ�β�ڵ���
			thisIndex = childIndex;//��ǰ�ڵ����������ӽڵ�ϴ���
			childIndex *= 2;//������һ�ӽڵ�
		}
		heap[thisIndex - 1] = heap[heap_size - 1];
		heap[heap_size - 1].~T();//ɾ����β
		heap_size--;//�����˶Ѵ�С��һ
	}
	void push(const T& theData)//��ѣ���ĳһԪ���ڶ����ҵ����ʵ�λ��
	{
		if (heap_size == array_size) enlargeCapacity();
		heap_size++;
		int currentIndex = heap_size;
		while (currentIndex != 1 && heap[(currentIndex / 2)-1] < theData)
		{
			heap[currentIndex-1] = heap[(currentIndex / 2)-1];
			currentIndex /= 2;
		}
		heap[currentIndex-1] = theData;
	}
	void output()
	{
		for (int i = 0; i < heap_size; i++) std::cout << heap[i] << ", ";
		std::cout << "��ǰ�ѵĴ�СΪ��" << heap_size << std::endl;
	}
private:
	int heap_size;//��ǰ�Ѵ�С
	int array_size;//�������С
	T* heap;//������
	void initHeap()//��ʼ������
	{
		int childIndex;//��ǰ�ڵ��ֵ�����ӽڵ�
		//�ӵ����ڶ���ڵ㿪ʼ��ǰ����˳��
		for (int currentIndex = heap_size / 2; currentIndex > 0; currentIndex--)
		{
			T topNode=heap[currentIndex-1];//�ȴ��µ�ǰ�Ķ��ڵ�
			childIndex = currentIndex * 2;
			while (childIndex <= heap_size)
			{
				if (childIndex < heap_size)//�ж�һ�£���ֹ���
				{
					if (heap[childIndex + 1 - 1] > heap[childIndex - 1]) childIndex++;//���ҳ������ӽڵ�
				}
				
				if (topNode < heap[childIndex - 1] )
				{
					heap[childIndex / 2 - 1] = heap[childIndex - 1];//������ڵ�С�ڵ�ǰ�ӽڵ㣬���ӽڵ�����һ��
					childIndex *= 2;//������һ���ӽڵ�
				}
				else break;//�����ǰ���ڵ���ڵ�ǰ�ӽڵ㣬˵�����ڵ���Է��ڴ˲�
			}
			heap[childIndex / 2 - 1] = topNode;//�Ѷ��ڵ���ڴ˲�
		}
	}
	void enlargeCapacity()//�ӱ��������飬��ֹ���
	{
		T* tempHeap = new T[array_size *2];//����һ����������С������
		for (int i = 0; i < heap_size; i++) tempHeap[i] = heap[i];//�Ѿ�������ֲ��ȥ
		//����heap
		for (int i = 0; i < heap_size; i++) heap[i].~T();
		delete[] heap;
		//���ƹ�ȥ
		heap = new T[array_size * 2];
		heap = tempHeap;
		array_size *= 2;//��Ҫ���Ǹ����������ӱ�
	}
};

