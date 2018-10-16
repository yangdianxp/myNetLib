#ifndef __ROUTE_H__
#define __ROUTE_H__
#include <set>
#include "base_client.h"

class route
{
public:
	void add_client(std::shared_ptr<base_client> client);
private:
	std::set<std::shared_ptr<base_client>> m_clients;
};

#endif