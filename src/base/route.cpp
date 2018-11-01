#include "route.h"

void route::add_client(std::shared_ptr<base_client> client)
{
	m_clients.insert(client);
}

void route::add_module(std::shared_ptr<base_client> client, uint32_t type, uint32_t mid)
{
	m_mid_clients.left.insert(bm_mid::left_value_type(mid, client));
	m_type_clients.left.insert(bm_type::left_value_type(type, client));
}
void route::delete_client(std::shared_ptr<base_client> client)
{
	m_clients.erase(client);
	m_mid_clients.right.erase(client);
	m_type_clients.right.erase(client);
}
void route::delete_module(std::shared_ptr<base_client> client)
{
	m_mid_clients.right.erase(client);
	m_type_clients.right.erase(client);
}
std::shared_ptr<base_client> route::get_client(std::size_t mid)
{
	auto it = m_mid_clients.left.find(mid);
	if (it != m_mid_clients.left.end())
	{
		return it->second;
	}
	return std::shared_ptr<base_client>();
}
std::size_t route::for_each_all(std::function<void(std::shared_ptr<base_client>)> fn)
{
	std::size_t cnt = 0;
	for (auto pair : m_mid_clients.left)
	{
		fn(pair.second);
		++cnt;
	}
	return cnt;
}

std::size_t route::for_each_type(uint32_t type, std::function<void(std::shared_ptr<base_client>)> fn)
{
	auto range = m_type_clients.left.equal_range(type);
	std::size_t cnt = 0;
	for (auto it = range.first; it != range.second; ++it, ++cnt)
	{
		fn(it->second);
	}
	return cnt;
}