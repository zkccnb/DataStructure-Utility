#pragma once
//��������
//ע�����ѭ���������Ͻ�
//ƽ��ʱ�临�Ӷȣ�O(n2)
//20w�������ݱ��֣��������
//2w�������ݱ��֣�2588ms
//���ܴ���򵥣������������ܶ࣬�ǳ���ʱ�������Ҫn���ν���
#include"Sort.h"
class Bubble:public Sort {
public:
	void sort(int* _array, size_t _size)override {
		for (int i = 0; i < _size; i++) {
			for (int j = 0; j < _size-i-1; j++) {
				if (_array[j] > _array[j + 1]) swap(_array[j], _array[j + 1]);
			}
		}
	}
};