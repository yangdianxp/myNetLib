#include "gateway_server.h"
#include "gateway_client.h"

gateway_server::gateway_server(boost::asio::io_context& io_context, short port) :
	middleware_server(io_context, port)
{
	
}
void gateway_server::handle_accept_succ(tcp::socket& socket)
{
	if (m_ready && !m_vid_range.empty())
	{
		std::shared_ptr<gateway_client> client = std::make_shared<gateway_client>(get_io_context(), std::move(socket));
		client->init(shared_from_this());
		std::size_t vid = m_vid_range.get();
		client->set_id(vid);
		client->set_type(module_user_type);
		m_route->add_vid(client, vid);
	}
}

void gateway_server::set_vid_range(uint32_t min, uint32_t max)
{
	m_vid_range.init(min, max);
	m_ready = true;
}

void gateway_server::del_vid(uint32_t id)
{
	m_vid_range.del(id);
}

std::map<std::size_t, range_manage::pair>& gateway_server::get_balance_list()
{
	return m_balance_list;
}

std::size_t gateway_server::get_balance(std::size_t tid)
{
	std::size_t mid = 0;
	for (auto n : m_balance_list)
	{
		if (tid >= n.second.first && tid <= n.second.second)
		{
			mid = n.first;
			break;
		}
	}
	return mid;
}
