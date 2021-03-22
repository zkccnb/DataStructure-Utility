#pragma once
//起泡排序
//注意里层循环的索引上界
//平均时间复杂度：O(n2)
//20w整型数据表现：程序崩溃
//2w整型数据表现：2588ms
//尽管代码简单，但交换次数很多，非常耗时，最多需要n！次交换
#include"Sort.h"
class Bubble:public Sort {
public:
	void sort(int* _array, size_t _size)override {
		for (int i = 0; i < _size; i++) {
			for (int j = 0; j < _size-i-1; j++) {
				if (_array[j] > _array[j + 1]) swap(_array[j], _array[j + 1]);
			}
		}
	}
};