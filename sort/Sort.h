#pragma once
//#pragma once ����Ԥ����ָ��ز����٣�ʹ������ֻ���ظ�������ͷ�ļ�����һ��
//Sort�㷨����
#include<iostream>
class Sort {
protected:
	//����λ���㽻�������������������м����������������Ҫ���⴦��
	void swap(int& a, int& b) {
		a = a ^ b;
		b = a ^ b;
		a = a ^ b;
	}
public:
	virtual void sort(int* _array, size_t _size) = 0;
};