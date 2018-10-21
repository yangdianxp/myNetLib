#include "central_client.h"
#include "central_server.h"

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
	pb::internal::logon logon;
	msg.parse(logon);
	m_ip = logon.ip();
	m_port = logon.port();
	m_type = logon.type();
	SLOG_INFO << "module ip:" << m_ip << ", port:" << m_port << ", type:" << m_type << " " 
		<< config_settings::instance().get_module_name(m_type);
	std::shared_ptr<central_server> server = std::dynamic_pointer_cast<central_server>(m_server);
	if (server)
	{
		int id = server->get_unique_mid();
		m_id = id;
		/*将模块加入到路由表*/
		std::shared_ptr<route> route = server->get_route();
		route->add_module(shared_from_this(), m_type, id);
		/*遍历登录模块需要连接的模块*/
		proto_msg ack_msg(cmd_module_logon_ack);
		pb::internal::logon_ack ack;
		ack.set_id(id);
		ack.set_central_id(server->get_id());
		ack_msg.serialize_msg(ack);
		write((char *)&ack_msg, ack_msg.size());
	}
}

void central_client::init(std::shared_ptr<base_server> server)
{
	common_client::init(server);
	std::shared_ptr<central_client> client = std::dynamic_pointer_cast<central_client>(shared_from_this());
	if (client)
	{
		m_function_set[cmd_module_logon] = std::bind(&central_client::handle_module_logon, client, std::placeholders::_1);
	}
}

