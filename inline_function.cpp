#define SQUARE(x) ((x)*(x))
#include <iostream>

inline int inlineSQUARE(int x)
{
	return x * x;
}

int maininline_function(void)
{
	std::cout << SQUARE(5) << std::endl;
	std::cout << inlineSQUARE(5) << std::endl;
	return 0;
}