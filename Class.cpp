#include <iostream>

class Friend
{
public:
	std::string _name;
	std::string _address;
	int _age;
	double _height;
	double _weight;

	void print()
	{
		std::cout << _name << " " << _address << " " << _age <<
			" " << _height << " " << _weight << std::endl;
	}

};

int mainClass()
{
	Friend rachel;

	rachel._name = "Rachel";

}