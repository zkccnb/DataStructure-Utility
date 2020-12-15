// 链表左高树(高度).cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include"HBLT.h"

int main()
{
	int data1[14] = { -3,10,2,7,6,5,9,12,35,22,15,1,3,4 };
	int size1 = sizeof(data1) / sizeof(data1[0]);
	int data2[5] = { 1,2,3,4,0 };
	int size2 = sizeof(data2) / sizeof(data2[0]);
	int data3[8] = { 10,5,7,18,6,40,30,20 };
	int size3 = sizeof(data3) / sizeof(data3[0]);
	HBLT<int> hblt1(data1, size1);
	HBLT<int> hblt2(data2, size2);
	HBLT<int> hblt3(data3, size3);
	//hblt1.meld(hblt2);
	//hblt2.push(2);
	//hblt2.pop();
	int top=hblt2.top();
	int size = hblt2.size();
	bool isEmpty = hblt2.empty();
	std::cout << top << std::endl;
	std::cout << size << std::endl;
	std::cout << isEmpty << std::endl;
	hblt2.HBLTOutput();
}