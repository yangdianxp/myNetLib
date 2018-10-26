#include "vid_manage.h"

vid_manage::vid_pair vid_manage::get(std::size_t mid)
{
	vid_pair pair;
	if (!m_inventory.empty())
	{
		auto it = m_inventory.begin();
		pair = *it;
		m_inventory.erase(it);
		m_already_assigned.insert(make_pair(mid, pair));
	}
	else {
		pair.first = m_index;
		pair.second = m_index + m_unit_size - 1;
		m_index += m_unit_size;
		m_already_assigned.insert(make_pair(mid, pair));
	}
	return pair;
}

void vid_manage::repay(std::size_t mid)
{
	auto it = m_already_assigned.find(mid);
	if (it != m_already_assigned.end())
	{
		m_inventory.insert(it->second);
		m_already_assigned.erase(it);
	}
}

void vid_manage::set_unit_size(std::size_t size)
{
	m_unit_size = size;
}