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
			register_info();
		}
	}
}
void common_client::handle_connect_error(boost::system::error_code& ec)
{
	base_client::handle_connect_error(ec);
	handle_error_aux();
}
void common_client::handle_write_error(boost::system::error_code& ec)
{
	base_client::handle_write_error(ec);
	handle_error_aux();
}
void common_client::handle_msg_header_error(int length)
{
	base_client::handle_msg_header_error(length);
	handle_error_aux();
}
void common_client::handle_read_error(boost::system::error_code& ec)
{
	base_client::handle_read_error(ec);
	handle_error_aux();
}
void common_client::handle_error_aux()
{
	std::shared_ptr<module> server = std::dynamic_pointer_cast<module>(m_server);
	if (server)
	{
		auto route = server->get_route();
		if (m_conn_type == passive_conn ||
			(m_conn_type == active_conn && m_reconnect_time == 0))
		{
			route->delete_client(shared_from_this());
		}
		else {
			route->delete_module(shared_from_this());
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
	m_type = module_central_type;
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd] << ", self mid:" << ack.id()
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
		<< addr.ip() << ", port:" << addr.port() << ", type:" << addr.type() << " " 
		<< config_settings::instance().get_module_name(addr.type());
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
		info.set_type(server->get_type());
		info.set_ip(server->get_ip());
		info.set_port(server->get_port());
		msg.serialize_msg(info);
		write((char *)&msg, msg.size());
	}
}

void common_client::handle_register_info(proto_msg& msg)
{
	pb::internal::register_info info;
	msg.parse(info);
	m_id = info.id();
	m_type = info.type();
	m_ip = info.ip();
	m_port = info.port();
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd] 
		<< " m_id:" << m_id << " m_type:" << m_type << " " << config_settings::instance().get_module_name(m_type)
		<< " ip:" << m_ip << " port:" << m_port;
	std::shared_ptr<module> server = std::dynamic_pointer_cast<module>(m_server);
	if (server)
	{
		/*��ģ����뵽·�ɱ�*/
		std::shared_ptr<route> route = server->get_route();
		route->add_module(shared_from_this(), m_type, m_id);
		proto_msg ack_msg(cmd_register_info_ack);
		pb::internal::register_info ack;
		ack.set_id(server->get_id());
		ack.set_type(server->get_type());
		ack.set_ip(server->get_ip());
		ack.set_port(server->get_port());
		ack_msg.serialize_msg(ack);
		write((char *)&ack_msg, ack_msg.size());
	}
}

void common_client::handle_register_info_ack(proto_msg& msg)
{
	pb::internal::register_info info;
	msg.parse(info);
	m_id = info.id();
	m_type = info.type();
	m_ip = info.ip();
	m_port = info.port();
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd]
		<< " m_id:" << m_id << " m_type:" << m_type << " " << config_settings::instance().get_module_name(m_type)
		<< " ip:" << m_ip << " port:" << m_port;
	std::shared_ptr<module> server = std::dynamic_pointer_cast<module>(m_server);
	if (server)
	{
		/*��ģ����뵽·�ɱ�*/
		std::shared_ptr<route> route = server->get_route();
		route->add_module(shared_from_this(), m_type, m_id);
	}
}

void common_client::handle_monitor_route(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	std::shared_ptr<module> server = std::dynamic_pointer_cast<module>(m_server);
	if (server)
	{
		auto route = server->get_route();
		proto_msg msg(cmd_monitor_route_ack);
		pb::monitor::module_list info;
		info.set_clients_size(route->get_clients_size());
		info.set_type_clients_size(route->get_type_clients_size());
		auto self = shared_from_this();
		auto fn = [this, self, &info](std::shared_ptr<base_client> client)
		{
			std::shared_ptr<common_client> common = std::dynamic_pointer_cast<common_client>(client);
			if (common)
			{
				pb::internal::register_info* r = info.add_mid_clients();
				r->set_id(get_id());
				r->set_type(get_type());
				r->set_ip(get_ip());
				r->set_port(get_port());
			}
		};
		route->for_each_mid(fn);
		msg.serialize_msg(info);
		write((char *)&msg, msg.size());
	}
}

/*��Ϣ����*/
std::map<int, std::string> common_client::m_cmd_desc = {
	{ cmd_login_request, "client login request" },
	{ cmd_module_logon, "module logon request" },
	{ cmd_module_logon_ack, "module logon respond" },
	{ cmd_broadcast_module_logon, "broadcast module logon" },
	{ cmd_broadcast_module_logon_ack, "broadcast module logon respond" },
	{ cmd_register_info, "register module info" },
	{ cmd_request_vid_range, "gateway request vid range" },
	{ cmd_request_vid_range_ack, "gateway request vid range respond" },
	{ cmd_monitor_instruction, "monitor console instruction" },
	{ cmd_monitor_instruction_ack, "monitor console instruction respond" },
	{ cmd_monitor_route, "monitor request route info" },
	{ cmd_monitor_route_ack, "monitor request route info respond" },
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
		m_function_set[cmd_register_info] = std::bind(&common_client::handle_register_info, client, std::placeholders::_1);
		m_function_set[cmd_register_info_ack] = std::bind(&common_client::handle_register_info_ack, client, std::placeholders::_1);

		m_function_set[cmd_monitor_route] = std::bind(&common_client::handle_monitor_route, client, std::placeholders::_1);
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

uint32_t common_client::get_id()
{
	return m_id;
}