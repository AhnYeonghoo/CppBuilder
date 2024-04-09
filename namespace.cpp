#include <iostream>

namespace BestComImpl
{
	void SimpleFunc(void)
	{
		std::cout << "Bestcom�� ������ �Լ�" << std::endl;
	}
}

namespace ProgComImpl
{
	void SimpleFunc(void)
	{
		std::cout << "ProgCom�� ������ �Լ�" << std::endl;
	}
}

namespace BestCom1
{
	void SimpleFunc(void);
}

namespace ProgCom1
{
	void SimpleFunc(void);
}

int main()
{
	BestComImpl::SimpleFunc();
	ProgComImpl::SimpleFunc();
	BestCom1::SimpleFunc();
	ProgCom1::SimpleFunc();
	return 0;
}

void BestCom1::SimpleFunc(void)
{
	std::cout << "Bestcom�� ������ �Լ�" << std::endl;
}

void ProgCom1::SimpleFunc(void)
{
	std::cout << "ProgCom�� ������ �Լ�" << std::endl;
}