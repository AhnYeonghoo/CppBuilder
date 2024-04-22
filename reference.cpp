#include <iostream>

int change_val(int* p)
{
	*p = 3;
	return 0;
}

int change_val(int& p)
{
	p = 3;
	return 0;
}

int mainRefernce()
{
	int number = 5;

	std::cout << number << std::endl;
	change_val(&number);
	std::cout << number << std::endl;

	int a = 3;
	int& another_a = a;
	another_a = 5;
	std::cout << "a: " << a << std::endl;
	std::cout << "another_a: " << another_a << std::endl;

	int number2 = 10;
	std::cout << number2 << std::endl;
	change_val(number2);
	std::cout << number2 << std::endl;
	return 0;

}