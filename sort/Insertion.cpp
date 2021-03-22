#pragma once
//插入排序
//平均时间复杂度：O(n2)
//20w整型数据表现：程序崩溃
//2w整型数据表现：2221ms
//思想和起泡不一样，但表现形式一模一样，最多需要n！次交换
#include"Sort.h"
class Insertion : public Sort {
public:
	void sort(int* _array, size_t _size)override {
		for (int i = 1; i < _size; i++) {
			for (int j = i; j > 0; j--) {
				if (_array[j] < _array[j - 1]) swap(_array[j], _array[j - 1]);
			}
		}
	}
};