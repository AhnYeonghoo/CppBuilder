#include <iostream>

namespace BestComImpl
{
	void SimpleFunc(void)
	{
		std::cout << "Bestcom이 정의한 함수" << std::endl;
	}
}

namespace ProgComImpl
{
	void SimpleFunc(void)
	{
		std::cout << "ProgCom이 정의한 함수" << std::endl;
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
	std::cout << "Bestcom이 정의한 함수" << std::endl;
}

void ProgCom1::SimpleFunc(void)
{
	std::cout << "ProgCom이 정의한 함수" << std::endl;
}