#pragma once
//�鲢����
//ƽ��ʱ�临�Ӷȣ�O(nlogn)
//20w�������ݱ��֣�44ms
//2w�������ݱ��֣�3ms
//�ֶ���֮��˼�룬��ʵ���ǵݹ顣
//���ý�������������ϲ��Ĳ����Ƚϼ򵥣������й������⣩��һ�뷨���ݹ鵽��Ͳ�����ʱÿ���������鳤�ȶ�Ϊ1��Ȼ�����ϻ��ݣ���һ�ϲ�����������
//�����˵ݹ飬���ٶ���ȫ����n2�㷨���Ա���� ��tmd��
#include"Sort.h"
class MergeSort : public Sort {
private:
	//�����µݹ鵱ǰ��������������֣��ٰ��������֣�����֮�󣩺ϲ�
	void mergeSort(int* _array, int left,int right,int* temp) {
		int mid = (left + right) / 2;
		if (right - left > 2)
		{
			mergeSort(_array, left, mid, temp);//[ , )
			mergeSort(_array, mid, right, temp);//[ , )
		}
		merge(_array, left, mid, right, temp);
	}
	//�ϲ�������������
	void merge(int* _array,int left,int mid,int right,int* temp) {
		int i = left, j = mid, temp_i = 0;
		while (i < mid || j < right) {
			//i��ͷ�ˣ���ʣ�µ�j�Ƶ�temp��
			if (i == mid)
			{
				temp[temp_i++] = _array[j++];
				continue;
			}
			//j��ͷ�ˣ���ʣ�µ�i�Ƶ�temp��
			if (j == right)
			{
				temp[temp_i++] = _array[i++];
				continue;
			}
			if (_array[i] < _array[j]) temp[temp_i++] = _array[i++];
			else if(_array[i] > _array[j]) temp[temp_i++] = _array[j++];
			else//����������ĳֵ��ȣ�i��j��Ҫ����
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
		int* temp= new int[_size];//����ط�Ҫ�½�һ���ڴ棬ֱ����_array���������ָ��ָ��ͬһƬ�ڴ棬����tempָ��Ҳ����_array�е�����
		mergeSort(_array, 0, _size,temp);
		delete[] temp;
	}
};