#include <iostream>
#include "vid_manage.h"

int main()
{
	vid_manage manage;
	for (int i = 1; i < 10; ++i)
	{
		vid_manage::pair pair = manage.get(i);
		std::cout << "begin:" << pair.first 
			<< " end:" << pair.second << std::endl;
	}
	for (int i = 3; i < 8; ++i)
	{
		manage.repay(i);
	}
	for (int i = 1; i < 10; ++i)
	{
		vid_manage::pair pair = manage.get(i);
		std::cout << "begin:" << pair.first
			<< " end:" << pair.second << std::endl;
	}

	return 0;
}

#if 0
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