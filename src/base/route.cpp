#include "route.h"

void route::add_client(std::shared_ptr<base_client> client)
{
	m_clients.insert(client);
}

void route::add_module(std::shared_ptr<base_client> client, uint32_t mid)
{
	m_mid_clients.left.insert(bm_type_mid::left_value_type(mid, client));
}