#include "route.h"

void route::add_client(std::shared_ptr<base_client> client)
{
	m_clients.insert(client);
}