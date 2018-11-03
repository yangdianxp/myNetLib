#include "gateway_server.h"
#include "gateway_client.h"

gateway_server::gateway_server(boost::asio::io_context& io_context, short port) :
	middleware_server(io_context, port)
{
	
}
void gateway_server::handle_accept_succ(tcp::socket& socket)
{
	if (m_ready)
	{
		std::shared_ptr<gateway_client> client = std::make_shared<gateway_client>(get_io_context(), std::move(socket));
		client->init(shared_from_this());
		std::size_t vid = m_vid_range.get();
		client->set_id(vid);
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
