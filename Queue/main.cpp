// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include"ArrayQueue.h"

int main()
{
	ArrayQueue<int> queue(10);
	int data[5] = { 1,2,3,4,5 };
	for (int i = 0; i < 5; i++) queue.push(data[i]);
	queue.pop();
	queue.push(2);
	queue.pop();
	std::cout << queue.empty() << std::endl;
	std::cout << queue.size() << std::endl;
	std::cout << queue.getFront() << std::endl;
	std::cout << queue.getRear() << std::endl;

	queue.output();
	return 0;
}
