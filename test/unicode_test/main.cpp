#include <iostream>
#include "unique_code.h"

int main()
{
	unique_code my_unique(1, 1001);
	while (!my_unique.empty())
	{
		std::cout << my_unique.get() << " ";
	}
	std::cout << std::endl;
	

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

#endif