#pragma once
//#pragma once 这条预编译指令必不可少，使编译器只对重复包含的头文件编译一次
//Sort算法基类
#include<iostream>
class Sort {
protected:
	//采用位运算交换两个整型数，不用中间变量，但浮点数需要额外处理
	void swap(int& a, int& b) {
		a = a ^ b;
		b = a ^ b;
		a = a ^ b;
	}
public:
	virtual void sort(int* _array, size_t _size) = 0;
};