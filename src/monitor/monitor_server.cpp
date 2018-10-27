#include "monitor_server.h"
#include "monitor_client.h"

monitor_server::monitor_server(boost::asio::io_context& io_context, short port) :
	module(io_context, port)
{
	
}

void monitor_server::handle_accept_succ(tcp::socket& socket)
{
	std::shared_ptr<monitor_client> client = std::make_shared<monitor_client>(get_io_context(), std::move(socket));
	client->init(shared_from_this());
	m_route->add_client(client);
}

void monitor_server::connect_remote(std::string ip, std::string port, uint32_t type)
{
	SLOG_INFO << "connect ip:" << ip << " port:" << port << " type:" << type << " "
		<< config_settings::instance().get_module_name(type);
	std::shared_ptr<monitor_client> client = std::make_shared<monitor_client>(get_io_context(), ip, port);
	connect_remote_sub(client, type);
}
