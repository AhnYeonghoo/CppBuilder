#include <iostream>

int mainFor()
{
	int sum = 0;
	for (int i = 1; i <= 10; i++)
	{
		sum += i;
	}
	std::cout << "���� : " << sum << std::endl;

	int i = 1, sum2 = 0;
	while (i <= 10)
	{
		sum2 += i;
		i++;
	}

	std::cout << "����: " << sum2 << std::endl;


	return 0;
}