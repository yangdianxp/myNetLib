#include "route.h"

void route::add_client(std::shared_ptr<base_client> client)
{
	m_clients.insert(client);
}

void route::add_module(std::shared_ptr<base_client> client, uint32_t type, uint32_t mid)
{
	m_mid_clients.left.insert(bm_mid::left_value_type(mid, client));
	m_type_mid.left.insert(bm_type_mid::left_value_type(type, client));
}

std::size_t route::for_each_type(uint32_t type)
{
	auto lower = m_type_mid.left.lower_bound(type);
	auto upper = m_type_mid.left.upper_bound(type);
	std::size_t cnt = 0;
	for (auto it = lower; it != upper; ++it, ++cnt)
	{

	}
}