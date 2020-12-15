#include"ChainStack.h"

int main()
{
	ChainStack<int> stack(5);
	int data[5] = { 1,2,3,4,5 };
	for (int i = 0; i < 5; i++) stack.push(data[i]);
	stack.pop();
	/*stack.pop();
	stack.pop();
	stack.pop();
	stack.pop();
	stack.pop();*/
	bool is_empty=stack.empty();
	int stack_top=stack.top();
	int size=stack.size();
	stack.output();
	std::cout << is_empty << std::endl;
	std::cout << stack_top << std::endl;
	std::cout << size << std::endl;
}