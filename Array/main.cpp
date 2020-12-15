#include "ArrayList.hpp"

int main()
{
	ArrayList<int> a(10);
	ArrayList<int>b(2);
	for(auto i=0;i!=10;i++) a.push(i);
	a.push(100);
	b = a;
	b.delData();
	ArrayList<int> c(a);
	c[1] = 1000;
	std::cout << c << std::endl;
	std::cout << c.capacityOf() << std::endl;
	std::cout << c.sizeOf() << std::endl;
}
