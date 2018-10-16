#include "gateway_server.h"
#include "common_client.h"

gateway_server::gateway_server(boost::asio::io_context& io_context, short port) :
	module(io_context, port)
{
	
}

void gateway_server::connect_remote()
{
	config_settings& config_reader = config_settings::instance();
	std::string remote_ip = config_reader.get_remote_ip();
	std::string remote_port = std::to_string(config_reader.get_remote_port());
	std::shared_ptr<common_client> client = std::make_shared<common_client>(get_io_context(), remote_ip, remote_port);
	client->set_reconnect_time(3000);
	client->set_active_type(module_central_type);
	client->init(shared_from_this());
	m_route->add_client(client);
}