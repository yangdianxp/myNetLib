#ifndef __ROUTE_H__
#define __ROUTE_H__
#include <set>
#include <functional>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/unordered_multiset_of.hpp>
#include "common_client.h"
#include "hash_function.h"

using boost::bimaps::bimap;
using boost::bimaps::unordered_set_of;
using boost::bimaps::unordered_multiset_of;

class route
{
public:
	struct node
	{
		std::size_t type;
		std::size_t tid;
		std::size_t uid;
		std::size_t vid;
		node(std::size_t ty, std::size_t t, std::size_t u, std::size_t v) :
			type(ty), tid(t), uid(u), vid(v) {}
		bool operator ==(const node& other)const
		{
			return (type == other.type && tid == other.tid
				&& uid == other.uid && vid == other.vid);
		}
	};
	class node_hash {
	public:
		std::size_t operator ()(const node &n)const
		{
			return hash_val(n.type, n.tid, n.uid, n.vid);
		}
	};

	using bm_mid = bimap<unordered_set_of<uint32_t>, unordered_set_of<std::shared_ptr<common_client>>>;
	using bm_type = bimap<unordered_multiset_of<uint32_t>, unordered_set_of<std::shared_ptr<common_client>>>;
	using bm_node = bimap<unordered_set_of<node, node_hash>, unordered_set_of<std::shared_ptr<common_client>>>;
	using bm_size_t = bimap<unordered_set_of<std::size_t>, unordered_set_of<std::shared_ptr<common_client>>>;

	virtual ~route() {};
	void add_client(std::shared_ptr<common_client> client);
	virtual void add_module(std::shared_ptr<common_client> client, uint32_t type, uint32_t mid);
	virtual void delete_client(std::shared_ptr<common_client> client);
	virtual void delete_module(std::shared_ptr<common_client> client);
	std::shared_ptr<common_client> get_client(std::size_t mid);
	/*获取第一个这种类型的模块*/
	std::shared_ptr<common_client> get_first_client(std::size_t type);
	std::size_t for_each_mid(std::function<void(std::shared_ptr<common_client>)> fn);
	std::size_t for_each_type(uint32_t type, std::function<void(std::shared_ptr<common_client>)> fn);

	void add_vid(std::shared_ptr<common_client> client, std::size_t vid);
	void delete_vid(std::shared_ptr<common_client> client);
	void add_node(std::shared_ptr<common_client> client, node n);
	void delete_node(std::shared_ptr<common_client> client);
	bool find_node(node n);

	std::size_t get_clients_size();
	std::size_t get_type_clients_size();
	std::size_t get_mid_clients_size();
protected:
	std::set<std::shared_ptr<common_client>> m_clients;
	/*内部模块部分*/
	bm_mid m_mid_clients;
	bm_type m_type_clients;
	/*外部user部分*/
	bm_size_t m_vid_clients;
	bm_node m_node_clients;
};

#endif