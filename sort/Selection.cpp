#pragma once
//ѡ������
//ע�����ѭ���������Ͻ�
//ƽ��ʱ�临�Ӷȣ�O(n2)
//20w�������ݱ��֣�36123ms
//2w�������ݱ��֣�348ms
//��n2���Ӷ��㷨��ʱ��Ч����õ�һ�֣���Ϊ�����������٣������Ҫn�ν���
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