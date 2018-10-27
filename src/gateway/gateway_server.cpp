#include "gateway_server.h"
#include "gateway_client.h"

gateway_server::gateway_server(boost::asio::io_context& io_context, short port) :
	module(io_context, port)
{
	
}

void gateway_server::handle_accept_succ(tcp::socket& socket)
{
	std::shared_ptr<gateway_client> client = std::make_shared<gateway_client>(get_io_context(), std::move(socket));
	client->init(shared_from_this());
	m_route->add_client(client);
}

void gateway_server::connect_remote(std::string ip, std::string port, uint32_t type)
{
	SLOG_INFO << "connect ip:" << ip << " port:" << port << " type:" << type << " "
		<< config_settings::instance().get_module_name(type);
	std::shared_ptr<gateway_client> client = std::make_shared<gateway_client>(get_io_context(), ip, port);
	connect_remote_sub(client, type);
}
