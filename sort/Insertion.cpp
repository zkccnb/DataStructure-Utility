#pragma once
//��������
//ƽ��ʱ�临�Ӷȣ�O(n2)
//20w�������ݱ��֣��������
//2w�������ݱ��֣�2221ms
//˼������ݲ�һ������������ʽһģһ���������Ҫn���ν���
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