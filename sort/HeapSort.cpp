#pragma once
//������
//ƽ��ʱ�临�Ӷȣ�O(nlogn)
//20w�������ݱ��֣��������
//2w�������ݱ��֣�1101ms
//���Ÿо����Ǻ����ģ���ѡ���������������Լ��ǲ���д���ˡ�����
//��������Ҫ�ݹ飬�����ڴ�϶���С
#include"Sort.h"
class HeapSot : public Sort {
private:
	//����һ������ѣ��ӵ����ڶ���ڵ㿪ʼ��������ڵ㣩
	void buildHeap(int* _array,size_t _size) {
		for (int i = (_size - 1) / 2; i >=0 ; i--) {
			fixHeapNode(_array, i, _size);
		}
	}
	//ά��һ������ѽڵ㣬��֤�Ӵ˽ڵ㵽ָ���ĳ����ڵ�����Ϊ����ѣ���node�ڵ����¼�飩
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
		buildHeap(_array, _size);//�Ƚ���һ�������
		for (int i = _size-1; i >=0; i--) {
			//ÿ��ѭ���ѶѶ��Ͷ�β�����������Ǵ���ѣ��������β��Ԫ��һ�������ģ�
			swap(_array[0], _array[i]);
			//��Ҫ����βԪ���ˣ�����ά���Ѷ�~����βǰһ��Ԫ�أ��Ķѣ�Ŀ�����ҳ��ڶ����Ԫ�أ��Ա��´�ѭ���ŵ�������Ӧλ��
			fixHeapNode(_array, 0, i);
		}
	}
};