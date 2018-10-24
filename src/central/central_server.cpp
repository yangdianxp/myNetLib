#include "central_server.h"
#include "central_client.h"

central_server::central_server(boost::asio::io_context& io_context, short port) :
	module(io_context, port)
{
	config_settings& config_reader = config_settings::instance();
	int mid_begin = config_reader.get_mid_begin();
	int mid_end = config_reader.get_mid_end();
	m_unique_mid.init(mid_begin, mid_end);
	m_id = get_unique_mid();
}

void central_server::handle_accept_succ(tcp::socket& socket)
{
	std::shared_ptr<central_client> client = std::make_shared<central_client>(get_io_context(), std::move(socket));
	client->init(shared_from_this());
	m_route->add_client(client);
}


uint32_t central_server::get_unique_mid()
{
	return m_unique_mid.get();
}