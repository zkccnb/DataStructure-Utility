#pragma once
//归并排序
//平均时间复杂度：O(nlogn)
//20w整型数据表现：44ms
//2w整型数据表现：3ms
//分而治之的思想，其实就是递归。
//利用将两个有序数组合并的操作比较简单（力扣有过这种题）这一想法，递归到最低部（此时每个有序数组长度都为1）然后向上回溯，逐一合并这两两数组
//别看用了递归，但速度完全不是n2算法可以比拟的 巨tmd快
#include"Sort.h"
class MergeSort : public Sort {
private:
	//先向下递归当前数组的左右两部分，再把这两部分（有序之后）合并
	void mergeSort(int* _array, int left,int right,int* temp) {
		int mid = (left + right) / 2;
		if (right - left > 2)
		{
			mergeSort(_array, left, mid, temp);//[ , )
			mergeSort(_array, mid, right, temp);//[ , )
		}
		merge(_array, left, mid, right, temp);
	}
	//合并两个有序数组
	void merge(int* _array,int left,int mid,int right,int* temp) {
		int i = left, j = mid, temp_i = 0;
		while (i < mid || j < right) {
			//i到头了，把剩下的j移到temp里
			if (i == mid)
			{
				temp[temp_i++] = _array[j++];
				continue;
			}
			//j到头了，把剩下的i移到temp里
			if (j == right)
			{
				temp[temp_i++] = _array[i++];
				continue;
			}
			if (_array[i] < _array[j]) temp[temp_i++] = _array[i++];
			else if(_array[i] > _array[j]) temp[temp_i++] = _array[j++];
			else//左右两数组某值相等：i，j都要自增
			{
				temp[temp_i] = _array[j++]; 
				i++;
			}
		}
		for (int index = 0; index < temp_i; index++) {
			_array[left + index] = temp[index];
		}
	}
public:
	void sort(int* _array, size_t _size)override {
		int* temp= new int[_size];//这个地方要新建一块内存，直接用_array会造成两个指针指向同一片内存，改了temp指针也改了_array中的内容
		mergeSort(_array, 0, _size,temp);
		delete[] temp;
	}
};