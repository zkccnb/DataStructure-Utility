#pragma once
#include<iostream>
#include<cstdio>
template<class T>
class maxHeap
{
	//大根堆的特点是：沿任何一条支路向下看，值永远不增大（但可以相等）；并且是一个完全二叉树
public:
	maxHeap(const int& initArraySize,T* initHeapArray)//构造函数
	{
		//传入的数组大小必须和堆大小一致
		array_size = initArraySize;
		heap_size = array_size;
		heap = new T[array_size];
		for (int i = 0; i < array_size; i++) heap[i]= initHeapArray[i];
		initHeap();//调用初始化方法，每次建立堆的时候都建立一个标准的堆
	}
	maxHeap(const maxHeap<T>& theHeap)//复制构造
	{
		array_size = theHeap.array_size;
		heap_size = theHeap.heap_size;
		heap = theHeap.heap;
	}
	~maxHeap()//析构函数
	{
		for (int i = 0; i < heap_size; i++) heap[i].~T();
		delete[] heap;
	}

	bool empty() { return heap_size == 0; }
	int size() { return heap_size; }
	T& top() { return heap[0]; }
	void pop()//出堆，弹出堆顶元素
	{
		heap[0].~T();//删除堆顶
		int thisIndex = 1;
		int childIndex = 2;
		while (childIndex <= heap_size)
		{
			if (heap[childIndex - 1] < heap[childIndex]) childIndex++;//取左右子节点中最大的
			//如果当前节点的最大子节点大于堆尾节点，把该最大子节点上移至其父节点
			if (heap[heap_size - 1] < heap[childIndex - 1])
			{
				heap[thisIndex - 1] = heap[childIndex - 1];
			}
			else break;//否则，立刻跳出循环，说明此时的thisIndex可以存放堆尾节点了
			thisIndex = childIndex;//当前节点移向左右子节点较大者
			childIndex *= 2;//移向下一子节点
		}
		heap[thisIndex - 1] = heap[heap_size - 1];
		heap[heap_size - 1].~T();//删除堆尾
		heap_size--;//别忘了堆大小减一
	}
	void push(const T& theData)//入堆，将某一元素在堆中找到合适的位置
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
		std::cout << "当前堆的大小为：" << heap_size << std::endl;
	}
private:
	int heap_size;//当前堆大小
	int array_size;//堆数组大小
	T* heap;//堆数组
	void initHeap()//初始化数组
	{
		int childIndex;//当前节点的值最大的子节点
		//从倒数第二层节点开始向前修正顺序
		for (int currentIndex = heap_size / 2; currentIndex > 0; currentIndex--)
		{
			T topNode=heap[currentIndex-1];//先存下当前的顶节点
			childIndex = currentIndex * 2;
			while (childIndex <= heap_size)
			{
				if (childIndex < heap_size)//判断一下，防止溢出
				{
					if (heap[childIndex + 1 - 1] > heap[childIndex - 1]) childIndex++;//先找出最大的子节点
				}
				
				if (topNode < heap[childIndex - 1] )
				{
					heap[childIndex / 2 - 1] = heap[childIndex - 1];//如果顶节点小于当前子节点，把子节点上移一层
					childIndex *= 2;//考察下一层子节点
				}
				else break;//如果当前顶节点大于当前子节点，说明顶节点可以放在此层
			}
			heap[childIndex / 2 - 1] = topNode;//把顶节点放在此层
		}
	}
	void enlargeCapacity()//加倍扩容数组，防止溢出
	{
		T* tempHeap = new T[array_size *2];//定义一个新容量大小的数组
		for (int i = 0; i < heap_size; i++) tempHeap[i] = heap[i];//把旧数组移植过去
		//析构heap
		for (int i = 0; i < heap_size; i++) heap[i].~T();
		delete[] heap;
		//复制过去
		heap = new T[array_size * 2];
		heap = tempHeap;
		array_size *= 2;//不要忘记给数组容量加倍
	}
};

