#pragma once
//快速排序
//平均时间复杂度：O(nlogn)
//20w整型数据表现：40ms
//2w整型数据表现：3ms
//分而治之的思想，其实就是递归。
//关于怎么把比key小的数放到左边，把比key大的数放到右边，用到了挖坑填数的技巧，第一次写还是很不容易想到的
//别看用了递归，但速度完全不是n2算法可以比拟的 巨tmd快
#include"Sort.h"
class Quicksort: public Sort {
private:
	void quickSort(int* _array,int left,int right) {
		if (left >= right) return;
		int i = left, j = right;
		int key = _array[left];//以最左边的数为key
		while (i < j) {
			//从右向左找第一个比key小的数，找到之后，记录其下标j
			while (i<j&&_array[j]>=key) j--;
			//从左向右找第一个比key大的数，找到之后，记录其下标i
			while (i < j&&_array[i] <= key) i++;
			//找到这两个值之后，互换之
			if (i < j) swap(_array[i], _array[j]);
		}
		//以下两句相当于交换left和i（从左到右第一个比key大的数）
		_array[left] = _array[i];
		_array[i] = key;
		//向左右递归
		quickSort(_array, left, i - 1);
		quickSort(_array, i + 1, right);
	}
public:
	void sort(int* _array, size_t _size)override {
		quickSort(_array, 0, _size - 1);
	}
};