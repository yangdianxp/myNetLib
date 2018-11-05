#ifndef __RANGE_MANAGE_H__
#define __RANGE_MANAGE_H__
#include <map>
#include <set>
#include <functional>

class range_manage
{
public:
	using pair = std::pair<std::size_t, std::size_t>;
	pair get(std::size_t mid);
	void repay(std::size_t mid);
	void set_unit_size(std::size_t size);

	std::size_t get_index();
	std::size_t get_unit_size();
	std::size_t for_each_inventory(std::function<void(pair&)> fn);
	std::size_t for_each_already_assigned(std::function<void(std::pair<const std::size_t, pair>&)> fn);
private:
	std::size_t m_index = 1;
	std::size_t m_unit_size = 10000;
	std::set<pair> m_inventory;
	std::map<std::size_t, pair> m_already_assigned;
};


#endif
