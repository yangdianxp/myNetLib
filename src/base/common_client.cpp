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
void common_client::dispatch(proto_msg& msg)
{
	m_function_set[msg.m_cmd](msg);
}
void common_client::handle_connect_succ()
{
	SLOG_INFO << "connect succ";
	if (m_conn_type == active_conn)
	{
		if (m_active_type == module_central_type)
		{
			module_logon();
		}
		else {
			
		}
	}
}
void common_client::handle_nothing(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
}
void common_client::handle_module_logon_ack(proto_msg& msg)
{
	pb::internal::logon_ack ack;
	msg.parse(ack);
	m_id = ack.central_id();
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd] << ", mid:" << ack.id()
		<< ", central id:" << m_id;
	std::shared_ptr<module> server = std::dynamic_pointer_cast<module>(m_server);
	if (server)
	{
		server->set_id(ack.id());
		std::shared_ptr<route> route = server->get_route();
		route->add_module(shared_from_this(), module_central_type, ack.central_id());
		for (int i = 0; i < ack.link_addr_size(); ++i)
		{
			const pb::internal::addr& addr = ack.link_addr(i);
			server->connect_remote(addr.ip(), std::to_string(addr.port()), addr.type());
		}
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

void common_client::handle_broadcast_module_logon(proto_msg& msg)
{
	pb::internal::addr addr;
	msg.parse(addr);
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd] << ", ip:"
		<< addr.ip() << ", port:" << addr.port() << ", type:" << addr.type();
	std::shared_ptr<module> server = std::dynamic_pointer_cast<module>(m_server);
	if (server)
	{
		server->connect_remote(addr.ip(), std::to_string(addr.port()), addr.type());
	}
}

void common_client::register_info()
{
	std::shared_ptr<module> server = std::dynamic_pointer_cast<module>(m_server);
	if (server)
	{
		proto_msg msg(cmd_register_info);
		pb::internal::register_info info;
		info.set_id(server->get_id());
		msg.serialize_msg(info);
		write((char *)&msg, msg.size());
	}
}

/*œ˚œ¢√Ë ˆ*/
std::map<int, std::string> common_client::m_cmd_desc = {
	{ cmd_login_request, "client login request" },
	{ cmd_module_logon, "module logon request" },
	{ cmd_module_logon_ack, "module logon respond" },
	{ cmd_broadcast_module_logon, "broadcast module logon" },
	{ cmd_broadcast_module_logon_ack, "broadcast module logon respond" },
};

void common_client::init(std::shared_ptr<base_server> server)
{
	set_server(server);
	std::shared_ptr<common_client> client = std::dynamic_pointer_cast<common_client>(shared_from_this());
	if (client)
	{
		for (int i = 0; i < cmd_end; i++)
		{
			m_function_set[i] = std::bind(&common_client::handle_nothing, client, std::placeholders::_1);
		}
		m_function_set[cmd_module_logon_ack] = std::bind(&common_client::handle_module_logon_ack, client, std::placeholders::_1);
		m_function_set[cmd_broadcast_module_logon] = std::bind(&common_client::handle_broadcast_module_logon, client, std::placeholders::_1);
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

uint32_t common_client::get_type()
{
	return m_type;
}