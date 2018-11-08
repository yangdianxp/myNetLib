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
	struct ttnode
	{
		std::size_t type;
		std::size_t tid;
		ttnode(std::size_t ty, std::size_t t) : type(ty), tid(t) {}
		bool operator ==(const ttnode& other)const
		{
			return (type == other.type && tid == other.tid);
		}
	};
	class ttnode_hash {
	public:
		std::size_t operator ()(const ttnode &n)const
		{
			return hash_val(n.type, n.tid);
		}
	};

	using bm_type = bimap<unordered_multiset_of<uint32_t>, unordered_set_of<std::shared_ptr<common_client>>>;
	using bm_node = bimap<unordered_set_of<node, node_hash>, unordered_multiset_of<std::shared_ptr<common_client>>>;
	using bm_size_t = bimap<unordered_set_of<std::size_t>, unordered_set_of<std::shared_ptr<common_client>>>;
	using bm_ttnode_node = bimap<unordered_multiset_of<ttnode, ttnode_hash>, unordered_set_of<node, node_hash>>;
	using bm_size_t_node = bimap<unordered_multiset_of<std::size_t>, unordered_set_of<node, node_hash>>;

	virtual ~route() {};
	void add_client(std::shared_ptr<common_client> client);
	virtual void add_module(std::shared_ptr<common_client> client, uint32_t type, uint32_t mid);
	virtual void delete_client(std::shared_ptr<common_client> client);
	virtual void delete_module(std::shared_ptr<common_client> client);
	std::shared_ptr<common_client> get_client(std::size_t mid);
	std::size_t for_each_mid(std::function<void(std::shared_ptr<common_client>)> fn);
	std::size_t for_each_type(uint32_t type, std::function<void(std::shared_ptr<common_client>)> fn);

	std::shared_ptr<common_client> get_vid(std::size_t vid);
	void add_vid(std::shared_ptr<common_client> client, std::size_t vid);
	void delete_vid(std::shared_ptr<common_client> client);
	std::size_t for_each_vid_clients(std::function<void(const std::size_t, std::shared_ptr<common_client>)>);
	void add_node(std::shared_ptr<common_client> client, node& n);
	void delete_node(std::shared_ptr<common_client> client);
	void delete_node(node& n);
	void delete_node(std::size_t vid);
	bool find_node(node& n);
	std::shared_ptr<common_client> get_node(const node& n);
	std::size_t for_each_node_clients(std::function<void(const node&, std::shared_ptr<common_client>)>);
	std::shared_ptr<common_client> get_ttnode(ttnode& ttn);
	std::size_t for_each_ttnode(ttnode& ttn, std::function<void(std::shared_ptr<common_client>, const node&)> fn);
	std::size_t for_each_ttnode_node(std::function<void(const ttnode&, const node&)>);
	std::size_t for_each_vid(std::size_t vid, std::function<void(std::shared_ptr<common_client>)> fn);
	std::size_t for_each_vid_node(std::function<void(const std::size_t, const node&)>);
	std::size_t for_each_vid_ttnode(std::size_t vid, std::function<void(std::shared_ptr<common_client>, const ttnode&)>);

	std::size_t get_clients_size();
	std::size_t get_type_clients_size();
	std::size_t get_mid_clients_size();
protected:
	/*内部模块部分*/
	std::set<std::shared_ptr<common_client>> m_clients;
	bm_size_t m_mid_clients;
	bm_type m_type_clients;
	/*外部user部分*/
	bm_size_t m_vid_clients;
	bm_node m_node_clients;
	bm_ttnode_node m_ttnode_node;
	bm_size_t_node m_vid_node;
};

#endif