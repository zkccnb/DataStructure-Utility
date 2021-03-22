#pragma once
//希尔排序
//平均时间复杂度：O(n1.5)
//20w整型数据表现：程序崩溃
//2w整型数据表现：449ms
//利用基本有序的数组中使用插入排序，效率会提提升这一性质
//先对一个不为1的增量用插入排序，然后逐步缩小增量到1（即为插入排序），完成排序
//但对于较大的随机数据性能并没有插入排序好！
#include"Sort.h"
class Shell : public Sort {
public:
	void sort(int* _array, size_t _size)override {
		size_t shell = _size;
		while (shell > 1) {
			shell /= 2;
			for (int i = _size - 1; i >= 0; i-=shell) {
				int max_index = 0;
				for (int j = 0; j < i + 1; j+=shell) {
					if (_array[j] > _array[max_index]) max_index = j;
				}
				if (max_index != i) swap(_array[max_index], _array[i]);
			}
		}
	}
};