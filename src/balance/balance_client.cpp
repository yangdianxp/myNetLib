#include "balance_client.h"

balance_client::balance_client(boost::asio::io_context& io_context,
	std::string remote_ip, std::string remote_port) :
	common_client(io_context, remote_ip, remote_port)
{

}
balance_client::balance_client(boost::asio::io_context& io_context, tcp::socket socket) :
	common_client(io_context, std::move(socket))
{

}
void balance_client::handle_create_channel(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];

}

void balance_client::init(std::shared_ptr<base_server> server)
{
	common_client::init(server);
	std::shared_ptr<balance_client> client = std::dynamic_pointer_cast<balance_client>(shared_from_this());
	if (client)
	{
		m_function_set[cmd_create_channel] = std::bind(&balance_client::handle_create_channel, client, std::placeholders::_1);
	}
}