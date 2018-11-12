#include <iostream>
#include <deque>
#include <random>
#include <ctime>
#include "unique_code.h"

int main()
{
	unique_code my_unique(1, 20000);
	std::deque<std::size_t> unique_nums;
	for (int i = 0; i < 15000; i++)
	{
		std::size_t num = my_unique.get();
		std::cout << num << " ";
		unique_nums.push_back(num);
	}
	std::cout << std::endl << "=======================" << std::endl;
	while (!my_unique.empty())
	{
		std::size_t num = my_unique.get();
		std::cout << num << " ";
		unique_nums.push_back(num);
	}
	std::cout << std::endl << "=======================" << std::endl;

	std::default_random_engine engine(time(nullptr));
	std::uniform_int_distribution<> dis(1, 20000);
	for (int i = 0; i < 10; i++)
	{
		std::size_t num = dis(engine);
		std::cout << num << " ";
		my_unique.del(num);
	}
	std::cout << std::endl << "=======================" << std::endl;
	while (!my_unique.empty())
	{
		std::size_t num = my_unique.get();
		std::cout << num << " ";
		unique_nums.push_back(num);
	}
	std::cout << std::endl << "=======================" << std::endl;

	/*for (auto n : unique_nums)
	{
		my_unique.del(n);
	}
	unique_nums.clear();
	for (int i = 0; i < 15000; i++)
	{
		std::size_t num = my_unique.get();
		std::cout << num << " ";
		unique_nums.push_back(num);
	}
	std::cout << std::endl << "=======================" << std::endl;
	for (auto n : unique_nums)
	{
		my_unique.del(n);
	}
	for (int i = 0; i < 15000; i++)
	{
		std::size_t num = my_unique.get();
		std::cout << num << " ";
		unique_nums.push_back(num);
	}
	std::cout << std::endl << "=======================" << std::endl;*/
	
	return 0;
}

#if 0

int tmp = 0;
while ((tmp = my_unique.get()))
{
	std::cout << tmp << " ";
}
std::cout << std::endl;

my_unique.del(500);
my_unique.del(520);
my_unique.del(2);
std::cout << std::endl;
std::cout << my_unique.get() << " ";
std::cout << my_unique.get() << " ";
std::cout << my_unique.get() << " ";

for (int i = 0; i < 11; i++)
{
	std::cout << my_unique.get() << std::endl;
}

for (int i = 1; i < 10; i += 2)
{
	my_unique.del(i);
}

for (int i = 0; i < 11; i++)
{
	std::cout << my_unique.get() << std::endl;
}

my_unique.del(25);
my_unique.del(950);
my_unique.del(1025);
my_unique.del(1555);
my_unique.del(2555);
my_unique.del(5555);
my_unique.del(7855);
my_unique.del(9555);
tmp = 0;
while ((tmp = my_unique.get()))
{
	std::cout << tmp << " ";
}
std::cout << std::endl;

#endif