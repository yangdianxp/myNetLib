#include "gateway_server.h"
#include "common_client.h"

gateway_server::gateway_server(boost::asio::io_context& io_context, short port) :
	module(io_context, port)
{
	config_settings& config_reader = config_settings::instance();
	std::string remote_ip = config_reader.get_remote_ip();
	std::string remote_port = std::to_string(config_reader.get_remote_port());
	std::shared_ptr<common_client> client = std::make_shared<common_client>(get_io_context(), remote_ip, remote_port);
	client->set_reconnect_time(3000);
	client->set_active_type(common_client::active_central_type);
	auto client1 = std::dynamic_pointer_cast<base_client>(client);
	m_rount.add_client(client1);
}