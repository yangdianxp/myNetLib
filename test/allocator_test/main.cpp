#include <iostream>
#include <vector>
#include <ext/pool_allocator.h>

int main()
{
	std::vector<int, __gnu_cxx::__pool_alloc<int>> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	for (auto n : v)
	{
		std::cout << n << std::endl;
	}
	return 0;
}