#include <iostream>

int mainmain_chapter1_2(void)
{
	int val1, val2;
	int result = 0;
	std::cout << "두 개의 숫자 입력: ";
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
	std::cout << "두 수 사이의 정수 합: " << result << std::endl;

	char name[100];
	char lang[200];
	std::cout << "이름은 무엇입니까? ";
	std::cin >> name;
	std::cout << "좋아하는 프로그래밍 언어는 무엇인가요? ";
	std::cin >> lang;

	std::cout << " 내 이름은 " << name << "입니다. \n";
	std::cout << "제일 좋아하는 언어는 " << lang << "입니다. " << std::endl;

	return 0;
}