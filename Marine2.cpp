#include <iostream>

class Marine2
{
private:
	static int total_marine_num;

	int hp;
	int coord_x, coord_y;
	bool is_dead;

	const int default_damage;

public:
	Marine2();
	Marine2(int x, int y);
	Marine2(int x, int y, int default_damage);

	int attack();
	void be_attacked(int damage_earn);
	void move(int x, int y);
	void show_status();

	~Marine2() { total_marine_num--; }
};

int Marine2::total_marine_num = 0;

Marine2::Marine2()
	: hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) 
{
	total_marine_num++;
}

Marine2::Marine2(int x, int y)
	: coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) 
{
	total_marine_num++;
}

Marine2::Marine2(int x, int y, int default_damage)
	: coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false)
{
	total_marine_num++;
}
void Marine2::move(int x, int y)
{
	coord_x = x;
	coord_y = y;
}

int Marine2::attack() { return default_damage; }
void Marine2::be_attacked(int damage_earn)
{
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;
}

void Marine2::show_status()
{
std::cout << "***Marine***" << std::endl;
std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
std::cout << " HP: " << hp << std::endl;
std::cout << " 현재 총 마린수:  " << total_marine_num << std::endl;
}

void create_marine()
{
	Marine2 marine3(10, 10, 4);
	marine3.show_status();
}

int main()
{
	Marine2 marine1(2, 3);
	Marine2 marine2(3, 5);

	marine1.show_status();
	marine2.show_status();

	create_marine();

	std::cout << std::endl << "마린1이 마린2를 공격! " << std:: endl;
	marine2.be_attacked(marine1.attack());
	marine1.show_status();
	marine2.show_status();
	return 0;
}