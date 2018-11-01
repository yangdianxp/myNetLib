#ifndef __ROUTE_H__
#define __ROUTE_H__
#include <set>
#include <functional>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/unordered_multiset_of.hpp>
#include "base_client.h"

using boost::bimaps::bimap;
using boost::bimaps::unordered_set_of;
using boost::bimaps::unordered_multiset_of;

class route
{
	using bm_mid = bimap<unordered_set_of<uint32_t>, unordered_set_of<std::shared_ptr<base_client>>>;
	using bm_type = bimap<unordered_multiset_of<uint32_t>, unordered_set_of<std::shared_ptr<base_client>>>;
public:
	void add_client(std::shared_ptr<base_client> client);
	void add_module(std::shared_ptr<base_client> client, uint32_t type, uint32_t mid);
	void delete_client(std::shared_ptr<base_client> client);
	void delete_module(std::shared_ptr<base_client> client);
	std::shared_ptr<base_client> get_client(std::size_t mid);
	std::size_t for_each_mid(std::function<void(std::shared_ptr<base_client>)> fn);
	std::size_t for_each_type(uint32_t type, std::function<void(std::shared_ptr<base_client>)> fn);

	std::size_t get_clients_size();
	std::size_t get_type_clients_size();
	std::size_t get_mid_clients_size();
private:
	std::set<std::shared_ptr<base_client>> m_clients;
	bm_mid m_mid_clients;
	bm_type m_type_clients;
};

#endif