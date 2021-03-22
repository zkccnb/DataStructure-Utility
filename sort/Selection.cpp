#pragma once
//选择排序
//注意里层循环的索引上界
//平均时间复杂度：O(n2)
//20w整型数据表现：36123ms
//2w整型数据表现：348ms
//是n2复杂度算法中时间效果最好的一种，因为交换次数最少，最多需要n次交换
#include"Sort.h"
class Selection : public Sort {
public:
	void sort(int* _array, size_t _size)override {
		for (int i = _size - 1; i >= 0; i--) {
			int max_index = 0;
			for (int j = 0; j < i+1; j++) {
				if (_array[j] > _array[max_index]) max_index = j;
			}
			if (max_index != i) swap(_array[max_index], _array[i]);
		}
	}
};