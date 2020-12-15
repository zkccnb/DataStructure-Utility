// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//链表用法与vector类似，索引从第0个开始

#include "ChainList.h"

int main(void)
{
	ChainList<int> array(5);
	//ChainList<int> a(array);//拷贝构造还有点问题
	int data[5] = { 1,2,3,4,5 };
	for(int i=0;i<5;i++) array.insert(i, data[i]);
	array.push_back(2);
	array.push_back(3);
	array.erase(0);
	bool is_empty=array.empty();
	int num=array.get(2);
	int index=array.IndexOf(2);
	int size=array.size();
	array.output();
	std::cout << is_empty <<std::endl;
	std::cout << num << std::endl;
	std::cout << index << std::endl;
	std::cout << size << std::endl;
	return 0;
}
