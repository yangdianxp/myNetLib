#include <iostream>
#include <ctime>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>

int main()
{
	boost::mt19937 rng(time(0));
	boost::uniform_int<> ui(0, 5);
	for (int i = 0; i < 10; ++i)
	{
		std::cout << ui(rng) << std::endl;
	}

	return 0;
}

/*
	1
	10
	11
	100
*/