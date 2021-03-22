#pragma once
//ϣ������
//ƽ��ʱ�临�Ӷȣ�O(n1.5)
//20w�������ݱ��֣��������
//2w�������ݱ��֣�449ms
//���û��������������ʹ�ò�������Ч�ʻ���������һ����
//�ȶ�һ����Ϊ1�������ò�������Ȼ������С������1����Ϊ�������򣩣��������
//�����ڽϴ������������ܲ�û�в�������ã�
#include"Sort.h"
class Shell : public Sort {
public:
	void sort(int* _array, size_t _size)override {
		size_t shell = _size;
		while (shell > 1) {
			shell /= 2;
			for (int i = _size - 1; i >= 0; i-=shell) {
				int max_index = 0;
				for (int j = 0; j < i + 1; j+=shell) {
					if (_array[j] > _array[max_index]) max_index = j;
				}
				if (max_index != i) swap(_array[max_index], _array[i]);
			}
		}
	}
};