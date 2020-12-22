#include<iostream>
#include"SmartPointer.hpp"
using namespace std;
struct A {
	A(int a):mum(a){}
	int mum;
};
int main()
{
	A* a1=new A(1);
	SmartPtr<A> a(a1);
	a->mum = 2;
	cout << a->mum << endl;
}