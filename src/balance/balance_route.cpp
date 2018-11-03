#include "balance_route.h"

void balance_route::add_module(std::shared_ptr<common_client> client, uint32_t type, uint32_t mid)
{
	route::add_module(client, type, mid);
	if (type >= module_media_type)
	{
		m_ref.insert(std::make_pair(client, 0));
	}
}
void balance_route::delete_client(std::shared_ptr<common_client> client)
{
	route::delete_client(client);
	m_ref.erase(client);
}
void balance_route::delete_module(std::shared_ptr<common_client> client)
{
	route::delete_module(client);
	m_ref.erase(client);
}
std::shared_ptr<common_client> balance_route::get_first_media(std::size_t type)
{
	std::shared_ptr<common_client> index;
	if (!m_ref.empty())
	{
		index = m_ref.begin()->first;
		std::size_t cnt = m_ref.begin()->second;
		for (auto n : m_ref)
		{
			if (n.first->get_type() == type)
			{
				if (n.second < cnt)
				{
					index = n.first;
					cnt = n.second;
					if (cnt == 0)
					{
						m_ref[index]++;
						return index;
					}
				}
			}
		}
		if (index)
		{
			m_ref[index]++;
		}
	}
	return index;
}