#pragma once
template<class T>
class ArrayQueue
{
public:
	ArrayQueue(int initCapacity)//���캯��
	{
		queue = new T[initCapacity];
		queue_capacity = initCapacity;
		queue_size = 0;
		front = 0;
		rear = 0;
	}
	ArrayQueue(const ArrayQueue<T>& thisQueue)//���ƹ��캯��
	{
		queue = thisQueue.queue;
		queue_capacity = thisQueue.queue_capacity;
		queue_size = thisQueue.queue_size;
		front = thisQueue.front;
		rear = thisQueue.rear;
	}
	~ArrayQueue()//��������
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
	void pop()//���׳���
	{
		front = (front + 1) % queue_capacity;
		queue[front].~T();//���ö���Ԫ�ص�����������ɾ������Ԫ��
		queue_size--;//���д�С�Լ�

		//�����ǰ����-��ǰԪ�ظ���>2���������С=��ǰԪ�ظ���+2
		if (queue_capacity - queue_size > 2)
		{
			queue_capacity = queue_size + 2;
			changeCapacity();
		}
	}
	void push(const T& theData)//��β����
	{
		//�����ǰ����-��ǰԪ�ظ���<2���������С=��ǰԪ�ظ���+2
		if (queue_capacity - queue_size < 2)
		{
			queue_capacity = queue_size + 2;
			changeCapacity();
		}
		rear = (rear + 1) % queue_capacity;
		queue[rear] = theData;//��Ӷ�βԪ��
		queue_size++;//���д�С����
	}
	void output() const//�������
	{
		for (int i = front; i < rear; i++)
		{
			std::cout << queue[i+1] << std::endl;
		}
	}

private:
	T* queue;//��������
	int front;//���ױ�־
	int rear;//��β��־
	int queue_capacity;//���е�ǰ������queue����Ĵ�С
	int queue_size;//�����ڵ�ǰԪ�ظ���
	void changeCapacity()//�ı���������С������ڴ�������
	{
		T* tempQueue = new T[queue_capacity];//����һ����������С������
		for (int i = 1; i < queue_size+1; i++) tempQueue[i] = queue[front + i];//�Ѿ�������ֲ��ȥ
		queue = tempQueue;
		front = 0;
		rear = queue_size;
	}
};

