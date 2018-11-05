#ifndef __VID_MANAGE_H__
#define __VID_MANAGE_H__
#include <map>
#include <set>

class vid_manage
{
public:
	using pair = std::pair<std::size_t, std::size_t>;
	pair get(std::size_t mid);
	void repay(std::size_t mid);
	void set_unit_size(std::size_t size);
private:
	std::size_t m_index = 1;
	std::size_t m_unit_size = 10000;
	std::set<pair> m_inventory;
	std::map<std::size_t, pair> m_already_assigned;
};


#endif
