#include "common_client.h"
#include "module.h"

common_client::common_client(boost::asio::io_context& io_context,\
	std::string remote_ip, std::string remote_port) :
	base_client(io_context, remote_ip, remote_port)
{

}
common_client::common_client(boost::asio::io_context& io_context, tcp::socket socket) :
	base_client(io_context, std::move(socket))
{

}
common_client::~common_client()
{

}
void common_client::handle_connect_succ()
{
	SLOG_INFO << "connect succ";
	if (m_conn_type == active_conn && m_active_type == module_central_type)
	{
		module_logon();
	}
}
void common_client::module_logon()
{
	config_settings& config_reader = config_settings::instance();
	std::string ip = config_reader.get_local_ip();
	uint32_t port = config_reader.get_local_port();
	SLOG_INFO << "logon central, local ip:" << ip << " local port:" << port;
	auto server = std::dynamic_pointer_cast<module>(m_server);
	if (server)
	{
		proto_msg msg(cmd_module_logon);
		pb::internal::logon logon;
		logon.set_ip(ip);
		logon.set_port(port);
		logon.set_type(server->get_type());
		msg.serialize_msg(logon);
		write((char *)&msg, msg.size());
	}
}

void common_client::init()
{
	for (int i = 0; i < cmd_end; i++)
	{
		//m_function_set[i]
	}
}
void common_client::set_active_type(uint32_t type)
{
	m_active_type = type;
}

void common_client::set_server(std::shared_ptr<base_server> server)
{
	m_server = server;
}