#include "maxHeap.h"

int main()
{
	//int data[] = {-3,5,8,7,20,6,2,9,12,15,30,17};
	int data[] = { 3,2,32,43,65,13,13,-3,0 };
	int size = sizeof(data)/sizeof(data[0]);
	maxHeap<int> heap(size,data);
	heap.push(30);
	heap.pop();
	heap.output();
	return 0;
}