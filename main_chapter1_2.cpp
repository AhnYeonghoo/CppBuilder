#include <iostream>

int mainmain_chapter1_2(void)
{
	int val1, val2;
	int result = 0;
	std::cout << "�� ���� ���� �Է�: ";
	std::cin >> val1 >> val2;

	if (val1 < val2)
	{
		for (int i = val1 + 1; i < val2; i++)
			result += i;
	}
	else
	{
		for (int i = val2 + 1; i < val1; i++)
			result += i;
	}
	std::cout << "�� �� ������ ���� ��: " << result << std::endl;

	char name[100];
	char lang[200];
	std::cout << "�̸��� �����Դϱ�? ";
	std::cin >> name;
	std::cout << "�����ϴ� ���α׷��� ���� �����ΰ���? ";
	std::cin >> lang;

	std::cout << " �� �̸��� " << name << "�Դϴ�. \n";
	std::cout << "���� �����ϴ� ���� " << lang << "�Դϴ�. " << std::endl;

	return 0;
}