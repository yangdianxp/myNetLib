#include "monitor_client.h"
monitor_client::monitor_client(boost::asio::io_context& io_context, \
	std::string remote_ip, std::string remote_port) :
	common_client(io_context, remote_ip, remote_port)
{

}

monitor_client::monitor_client(boost::asio::io_context& io_context, tcp::socket socket) :
	common_client(io_context, std::move(socket))
{

}

void monitor_client::init(std::shared_ptr<base_server> server)
{
	common_client::init(server);
	std::shared_ptr<monitor_client> client = std::dynamic_pointer_cast<monitor_client>(shared_from_this());
	if (client)
	{
	}
}
