#include <iostream>
#include <vector>
#include <array>
#include <ext/pool_allocator.h>
#include <ext/array_allocator.h>

int main()
{
	//int my[65536];
	std::tr1::array<int, 65536> my;
	__gnu_cxx::array_allocator<int, std::tr1::array<int, 65536>> myalloc(&my);

	int* p1 = myalloc.allocate(1);
	std::cout << p1 << std::endl;
	myalloc.deallocate(p1, 1);
	p1 = myalloc.allocate(1);
	std::cout << p1 << std::endl;

#if 0
	std::vector<int, __gnu_cxx::__pool_alloc<int>> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	for (auto n : v)
	{
		std::cout << n << std::endl;
	}
#endif
	return 0;
}