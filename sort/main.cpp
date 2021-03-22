#include<time.h>
#include"Bubble.cpp"
#include"Selection.cpp"
#include"Insertion.cpp"
#include"TestData.h"
#include"Shell.cpp"
#include"Quicksort.cpp"
#include"MergeSort.cpp"
#include"HeapSort.cpp"
using namespace std;
int main() {
	size_t size = sizeof(arr) / sizeof(arr[0]);
	Sort* s=new HeapSot();
	clock_t start_time = clock(); //获取此程序段开始执行时间
	s->sort(arr, size);
	clock_t end_time = clock();
	/*for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}*/
	cout << endl;
	cout << "算法执行时间：" << static_cast<double> (end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
}
	