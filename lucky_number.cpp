#include <iostream>

int mainLuckyNumber()
{
	int lucky_number = 3;
	std::cout << "내 비밀 수를 맞추어 보세요~" << std::endl;

	int user_input;

	while (1)
	{
		std::cout << "입력: ";
		std::cin >> user_input;
		if (lucky_number == user_input)
		{
			std::cout << "맞추셨습니다~~" << std::endl; 
				break; 
		}
		else
		{
			std::cout << "다시 생각해보세요~" << std::endl;
		}
	}

	user_input = 0;

	std::cout << "저의 정보를 표시해줍니다." << std::endl;
	std::cout << "1. 이름" << std::endl;
	std::cout << "2. 나이" << std::endl;
	std::cout << "3. 성별" << std::endl;
	std::cin >> user_input;

	switch (user_input)
	{
	case 1:
		std::cout << "Psi !" << std::endl;
		break;
	case 2:
		std::cout << "99살" << std::endl;
		break;
	case 3:
		std::cout << "남자" << std::endl;
		break;
	default:
		std::cout << "궁금한 게 없군요~" << std::endl;
		break;
	}
	return 0;
}