#pragma once
//堆排序
//平均时间复杂度：O(nlogn)
//20w整型数据表现：程序崩溃
//2w整型数据表现：1101ms
//堆排感觉还是很慢的，比选择排序还慢，怀疑自己是不是写错了。。。
//不过不需要递归，消耗内存肯定较小
#include"Sort.h"
class HeapSot : public Sort {
private:
	//建立一个大根堆（从倒数第二层节点开始向上整理节点）
	void buildHeap(int* _array,size_t _size) {
		for (int i = (_size - 1) / 2; i >=0 ; i--) {
			fixHeapNode(_array, i, _size);
		}
	}
	//维护一个大根堆节点，保证从此节点到指定的长度内的数组为大根堆（从node节点向下检查）
	void fixHeapNode(int* _array, int node,size_t _size) {
		int swapNode, lc=2 * node + 1, rc= 2 * node + 2;
		while (lc < _size) {
			if (rc<_size && _array[lc]<=_array[rc])
			{
				swapNode = rc;
			}
			else swapNode = lc;
			if (_array[node] < _array[swapNode]) swap(_array[node], _array[swapNode]);
			node++;
			lc = 2 * node + 1, rc = 2 * node + 2;
		}
	}
public:
	void sort(int* _array, size_t _size)override {
		buildHeap(_array, _size);//先建好一个大根堆
		for (int i = _size-1; i >=0; i--) {
			//每次循环把堆顶和堆尾交换，由于是大根堆，交换后堆尾的元素一定是最大的！
			swap(_array[0], _array[i]);
			//不要动堆尾元素了，重新维护堆顶~（堆尾前一个元素）的堆，目的是找出第二大的元素，以便下次循环放到后面相应位置
			fixHeapNode(_array, 0, i);
		}
	}
};