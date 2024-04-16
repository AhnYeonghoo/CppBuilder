#include <iostream>

int function()
{
	int a = 2;
	return a;
}

int& functionR()
{
	int a = 3;
	return a;
}

int& functionR2(int& a)
{
	a = 5;
	return a;
}
int mainarrayReference()
{
	int arr[3] = { 1,2,3 };
	int(&ref)[3] = arr;
	ref[0] = 2;
	ref[1] = 3;
	ref[2] = 1;
	std::cout << arr[0] << arr[1] << arr[2] << std::endl;
	int a = function();
	std::cout << a << std::endl;
	int b = functionR();
	std::cout << b << std::endl;

	int c = functionR2(b);
	std::cout << c << std::endl;
	return  0;
}