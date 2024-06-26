#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>

class Marine
{
	int hp;
	int coord_x, coord_y;
	int damage;
	bool is_dead;
	char* name;

public:
	Marine();
	Marine(int x, int y);
	Marine(int x, int y, const char* marine_name);
	~Marine();

	int attack();
	void be_attacked(int damage_earn);
	void move(int x, int y);
	void show_status();
};

Marine::Marine()
{
	hp = 50;
	coord_x = coord_y = 0;
	damage = 5;
	is_dead = false;
	name = NULL;
}

Marine::Marine(int x, int y)
{
	hp = 50;
	coord_x = x;
	coord_y = y;
	damage = 5;
	is_dead = false;
	name = NULL;
}

Marine::~Marine()
{
	std::cout << name << "의 소멸자 호출!" << std::endl;
	if (name != NULL)
		delete[] name;

}

Marine::Marine(int x, int y, const char* marine_name)
{
	name = new char[strlen(marine_name) + 1];
	strcpy(name, marine_name);


	coord_x = x;
	coord_y = y;
	hp = 50;
	damage = 5;
	is_dead = false;
}

void Marine::move(int x, int y)
{
	coord_x = x;
	coord_y = y;
}

int Marine::attack() { return damage; }

void Marine::be_attacked(int damage_earn)
{
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;
}

void Marine::show_status()
{
	std::cout << "*** Marine ***" << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
		<< std::endl;
	std::cout << " HP : " << hp << std::endl;
}  

int mainMarine()
{
	Marine marine1(2, 3);
	Marine marine2(3, 5);

	marine1.show_status();
	marine2.show_status();

	std::cout << std::endl << "마린1 이 마린 2를 공격!" << std::endl;
	marine2.be_attacked(marine1.attack());
	marine1.show_status();

	Marine* marines[100];
	marines[0] = new Marine(2, 3);
	marines[1] = new Marine(3, 5);

	marines[0]->show_status();
	marines[1]->show_status();
	std::cout << std::endl << "마린1이 마린2를 공격!" << std::endl;

	marines[0]->be_attacked(marines[1]->attack());
	marines[0]->show_status();
	marines[1]->show_status();

	delete marines[0];
	delete marines[1];

	return 0;
}