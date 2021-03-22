#pragma once
//��������
//ƽ��ʱ�临�Ӷȣ�O(nlogn)
//20w�������ݱ��֣�40ms
//2w�������ݱ��֣�3ms
//�ֶ���֮��˼�룬��ʵ���ǵݹ顣
//������ô�ѱ�keyС�����ŵ���ߣ��ѱ�key������ŵ��ұߣ��õ����ڿ������ļ��ɣ���һ��д���Ǻܲ������뵽��
//�����˵ݹ飬���ٶ���ȫ����n2�㷨���Ա���� ��tmd��
#include"Sort.h"
class Quicksort: public Sort {
private:
	void quickSort(int* _array,int left,int right) {
		if (left >= right) return;
		int i = left, j = right;
		int key = _array[left];//������ߵ���Ϊkey
		while (i < j) {
			//���������ҵ�һ����keyС�������ҵ�֮�󣬼�¼���±�j
			while (i<j&&_array[j]>=key) j--;
			//���������ҵ�һ����key��������ҵ�֮�󣬼�¼���±�i
			while (i < j&&_array[i] <= key) i++;
			//�ҵ�������ֵ֮�󣬻���֮
			if (i < j) swap(_array[i], _array[j]);
		}
		//���������൱�ڽ���left��i�������ҵ�һ����key�������
		_array[left] = _array[i];
		_array[i] = key;
		//�����ҵݹ�
		quickSort(_array, left, i - 1);
		quickSort(_array, i + 1, right);
	}
public:
	void sort(int* _array, size_t _size)override {
		quickSort(_array, 0, _size - 1);
	}
};