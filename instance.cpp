#include <iostream>

class Animal
{
private:
	int food;
	int weight;

public:
	void set_animal(int _food, int _weight)
	{
		food = _food;
		weight = _weight;
	}

	void increase_food(int inc)
	{
		food += inc;
		weight += (inc / 3);
	}

	void view_stat()
	{
		std::cout << "�� ������ food : " << food << std::endl;
		std::cout << "�� ������ weight: " << weight << std::endl;
	}
};

// overloading

void print(int x) { std::cout << "int: " << x << std::endl; }
void print(char x) { std::cout << "char: " << x << std::endl; }
void print(double x) { std::cout << "double: " << x << std::endl; }
int mainInstance()
{
	Animal animal;
	animal.set_animal(100, 50);
	animal.increase_food(30);
	animal.view_stat();
	return 0;
}