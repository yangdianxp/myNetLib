#include <iostream>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/unordered_multiset_of.hpp>

using boost::bimaps::bimap;
using boost::bimaps::unordered_set_of;
using boost::bimaps::unordered_multiset_of;

int main()
{
	bimap<unordered_multiset_of<int>, unordered_set_of<int>> my_map;
	my_map.left.insert(std::make_pair(10, 1));
	my_map.left.insert(std::make_pair(11, 2));
	my_map.left.insert(std::make_pair(20, 3));
	my_map.left.insert(std::make_pair(21, 4));
	my_map.right.erase(1);
	for (auto pair : my_map.left)
	{
		std::cout << pair.first << " " << pair.second << std::endl;
	}

	return 0;
}

/*
	1
	10
	11
	100
*/