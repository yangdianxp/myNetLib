#include "range_manage.h"

range_manage::vid_pair range_manage::get(std::size_t mid)
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

void range_manage::repay(std::size_t mid)
{
	auto it = m_already_assigned.find(mid);
	if (it != m_already_assigned.end())
	{
		m_inventory.insert(it->second);
		m_already_assigned.erase(it);
	}
}

void range_manage::set_unit_size(std::size_t size)
{
	m_unit_size = size;
}

std::size_t range_manage::get_index()
{
	return m_index;
}
std::size_t range_manage::get_unit_size()
{
	return m_unit_size;
}
std::size_t range_manage::for_each_inventory(std::function<void(vid_pair&)> fn)
{
	int cnt = 0;
	for (auto n : m_inventory)
	{
		fn(n);
		++cnt;
	}
	return cnt;
}
std::size_t range_manage::for_each_already_assigned(std::function<void(std::pair<const std::size_t, vid_pair>&)> fn)
{
	int cnt = 0;
	for (auto n : m_already_assigned)
	{
		fn(n);
		++cnt;
	}
	return cnt;
}