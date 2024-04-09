#include <iostream>

int Adder(int num1 = 1, int num2 = 2);

int MyFunc(int num)
{
	num++;
	return num;
}

int MyFunc(int a, int b)
{
	return a + b;
}


int mainmain_chapter1_3(void)
{
	auto result1 = MyFunc(20);
	auto result2 = MyFunc(30, 40);
	auto result3 = Adder();
	std::cout << result1 << " " << result2 << " " << result3 << std::endl;
	return 0;
}
int Adder(int num1, int num2)
{
	return num1 + num2;
}