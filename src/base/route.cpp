#include "route.h"

void route::add_client(std::shared_ptr<common_client> client)
{
	m_clients.insert(client);
}

void route::add_module(std::shared_ptr<common_client> client, uint32_t type, uint32_t mid)
{
	m_mid_clients.left.insert(bm_size_t::left_value_type(mid, client));
	m_type_clients.left.insert(bm_type::left_value_type(type, client));
}
void route::delete_client(std::shared_ptr<common_client> client)
{
	m_clients.erase(client);
	m_mid_clients.right.erase(client);
	m_type_clients.right.erase(client);
}
void route::delete_module(std::shared_ptr<common_client> client)
{
	m_mid_clients.right.erase(client);
	m_type_clients.right.erase(client);
}
std::shared_ptr<common_client> route::get_client(std::size_t mid)
{
	auto it = m_mid_clients.left.find(mid);
	if (it != m_mid_clients.left.end())
	{
		return it->second;
	}
	return std::shared_ptr<common_client>();
}
std::shared_ptr<common_client> route::get_first_client(std::size_t type)
{
	auto it = m_type_clients.left.find(type);
	if (it != m_type_clients.left.end())
	{
		return it->second;
	}
	return std::shared_ptr<common_client>();
}
std::size_t route::for_each_mid(std::function<void(std::shared_ptr<common_client>)> fn)
{
	std::size_t cnt = 0;
	for (auto pair : m_mid_clients.left)
	{
		fn(pair.second);
		++cnt;
	}
	return cnt;
}

std::size_t route::for_each_type(uint32_t type, std::function<void(std::shared_ptr<common_client>)> fn)
{
	auto range = m_type_clients.left.equal_range(type);
	std::size_t cnt = 0;
	for (auto it = range.first; it != range.second; ++it, ++cnt)
	{
		fn(it->second);
	}
	return cnt;
}
std::shared_ptr<common_client> route::get_vid(std::size_t vid)
{
	auto it = m_vid_clients.left.find(vid);
	if (it != m_vid_clients.left.end())
	{
		return it->second;
	}
	return std::shared_ptr<common_client>();
}
void route::add_vid(std::shared_ptr<common_client> client, std::size_t vid)
{
	m_vid_clients.left.insert(std::make_pair(vid, client));
}
void route::delete_vid(std::shared_ptr<common_client> client)
{
	m_vid_clients.right.erase(client);
}
std::size_t route::for_each_vid_clients(std::function<void(const std::size_t, std::shared_ptr<common_client>)> fn)
{
	std::size_t cnt = 0;
	for (auto pair : m_vid_clients.left)
	{
		fn(pair.first, pair.second);
		++cnt;
	}
	return cnt;
}
void route::add_node(std::shared_ptr<common_client> client, node& n)
{
	m_node_clients.left.insert(std::make_pair(n, client));
	ttnode ttn(n.type, n.tid);
	m_ttnode_node.left.insert(std::make_pair(ttn, n));
	m_vid_node.left.insert(std::make_pair(n.vid, n));
}
void route::delete_node(std::shared_ptr<common_client> client)
{
	auto range = m_node_clients.right.equal_range(client);
	auto it_end = range.second;
	for (auto it = range.first; it != it_end; ++it)
	{
		m_ttnode_node.right.erase(it->second);
		m_vid_node.right.erase(it->second);
	}
	m_node_clients.right.erase(client);
}
void route::delete_node(node& n)
{
	m_node_clients.left.erase(n);
	m_ttnode_node.right.erase(n);
	m_vid_node.right.erase(n);
}
void route::delete_node(std::size_t vid)
{
	auto range = m_vid_node.left.equal_range(vid);
	auto it_end = range.second;
	for (auto it = range.first; it != it_end; ++it)
	{
		m_node_clients.left.erase(it->second);
		m_ttnode_node.right.erase(it->second);
	}
	m_vid_node.left.erase(vid);
}
bool route::find_node(node& n)
{
	return (m_node_clients.left.find(n) != m_node_clients.left.end());
}
std::shared_ptr<common_client> route::get_node(const node& n)
{
	auto it = m_node_clients.left.find(n);
	if (it != m_node_clients.left.end())
	{
		return it->second;
	}
	return std::shared_ptr<common_client>();
}
std::size_t route::for_each_node_clients(std::function<void(const node&, std::shared_ptr<common_client>)> fn)
{
	std::size_t cnt = 0;
	for (auto pair : m_node_clients.left)
	{
		fn(pair.first, pair.second);
		++cnt;
	}
	return cnt;
}
std::shared_ptr<common_client> route::get_ttnode(ttnode& ttn)
{
	auto it = m_ttnode_node.left.find(ttn);
	if (it != m_ttnode_node.left.end())
	{
		return get_node(it->second);
	}
	return std::shared_ptr<common_client>();
}
std::size_t route::for_each_ttnode(ttnode& ttn, std::function<void(std::shared_ptr<common_client>, const node&)> fn)
{
	std::size_t cnt = 0;
	auto range = m_ttnode_node.left.equal_range(ttn);
	for (auto it = range.first; it != range.second; ++it, ++cnt)
	{
		auto it_c = m_node_clients.left.find(it->second);
		fn(it_c->second, it->second);
	}
	return cnt;
}
std::size_t route::for_each_ttnode_node(std::function<void(const ttnode&, const node&)> fn)
{
	std::size_t cnt = 0;
	for (auto pair : m_ttnode_node.left)
	{
		fn(pair.first, pair.second);
		++cnt;
	}
	return cnt;
}
std::size_t route::for_each_vid(std::size_t vid, std::function<void(std::shared_ptr<common_client>)> fn)
{
	std::size_t cnt = 0;
	auto range = m_vid_node.left.equal_range(vid);
	for (auto it = range.first; it != range.second; ++it, ++cnt)
	{
		auto it_c = m_node_clients.left.find(it->second);
		fn(it_c->second);
	}
	return cnt;
}
std::size_t route::for_each_vid_node(std::function<void(const std::size_t, const node&)> fn)
{
	std::size_t cnt = 0;
	for (auto pair : m_vid_node.left)
	{
		fn(pair.first, pair.second);
		++cnt;
	}
	return cnt;
}

std::size_t route::get_clients_size()
{
	return m_clients.size();
}
std::size_t route::get_type_clients_size()
{
	return m_type_clients.size();
}
std::size_t route::get_mid_clients_size()
{
	return m_mid_clients.size();
}