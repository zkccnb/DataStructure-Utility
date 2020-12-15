#pragma once
template<class T>
class ArrayQueue
{
public:
	ArrayQueue(int initCapacity)//构造函数
	{
		queue = new T[initCapacity];
		queue_capacity = initCapacity;
		queue_size = 0;
		front = 0;
		rear = 0;
	}
	ArrayQueue(const ArrayQueue<T>& thisQueue)//复制构造函数
	{
		queue = thisQueue.queue;
		queue_capacity = thisQueue.queue_capacity;
		queue_size = thisQueue.queue_size;
		front = thisQueue.front;
		rear = thisQueue.rear;
	}
	~ArrayQueue()//析构函数
	{
		for (int i = 0; i < queue_capacity; i++)
		{
			queue[i].~T();
		}
		delete[] queue;
	}
	bool empty() const { return queue == 0; }
	int size() const { return queue_size; }
	T& getFront() const { return queue[front+1]; }
	T& getRear() const { return queue[rear]; }
	void pop()//队首出列
	{
		front = (front + 1) % queue_capacity;
		queue[front].~T();//调用队首元素的析构函数，删除队首元素
		queue_size--;//队列大小自减

		//如果当前容量-当前元素个数>2，则数组大小=当前元素个数+2
		if (queue_capacity - queue_size > 2)
		{
			queue_capacity = queue_size + 2;
			changeCapacity();
		}
	}
	void push(const T& theData)//队尾入列
	{
		//如果当前容量-当前元素个数<2，则数组大小=当前元素个数+2
		if (queue_capacity - queue_size < 2)
		{
			queue_capacity = queue_size + 2;
			changeCapacity();
		}
		rear = (rear + 1) % queue_capacity;
		queue[rear] = theData;//添加队尾元素
		queue_size++;//队列大小自增
	}
	void output() const//队列输出
	{
		for (int i = front; i < rear; i++)
		{
			std::cout << queue[i+1] << std::endl;
		}
	}

private:
	T* queue;//队列数组
	int front;//队首标志
	int rear;//队尾标志
	int queue_capacity;//队列当前容量，queue数组的大小
	int queue_size;//队列内当前元素个数
	void changeCapacity()//改变队列数组大小，提高内存利用率
	{
		T* tempQueue = new T[queue_capacity];//定义一个新容量大小的数组
		for (int i = 1; i < queue_size+1; i++) tempQueue[i] = queue[front + i];//把旧数组移植过去
		queue = tempQueue;
		front = 0;
		rear = queue_size;
	}
};

