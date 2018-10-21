#ifndef __ROUTE_H__
#define __ROUTE_H__
#include <set>

#include <boost/bimap/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/bimap/unordered_multiset_of.hpp>
#include "base_client.h"

using boost::bimaps::bimap;
using boost::bimaps::set_of;
using boost::bimaps::list_of;
using boost::bimaps::unordered_multiset_of;

class route
{
	using bm_type_mid = bimap<set_of<uint32_t>, list_of<std::shared_ptr<base_client>>>;
public:
	void add_client(std::shared_ptr<base_client> client);
	void add_module(std::shared_ptr<base_client> client, uint32_t mid);
private:
	std::set<std::shared_ptr<base_client>> m_clients;
	bm_type_mid m_mid_clients;
};

#endif