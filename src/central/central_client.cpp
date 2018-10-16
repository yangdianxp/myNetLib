#include "central_client.h"

central_client::central_client(boost::asio::io_context& io_context, \
	std::string remote_ip, std::string remote_port) :
	common_client(io_context, remote_ip, remote_port)
{
	
}

central_client::central_client(boost::asio::io_context& io_context, tcp::socket socket) :
	common_client(io_context, std::move(socket))
{

}

void central_client::handle_module_logon(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
}

void central_client::init(std::shared_ptr<base_server> server)
{
	common_client::init(server);
	std::shared_ptr<central_client> client = std::dynamic_pointer_cast<central_client>(shared_from_this());
	m_function_set[cmd_module_logon] = std::bind(&central_client::handle_module_logon, this, std::placeholders::_1);
}

