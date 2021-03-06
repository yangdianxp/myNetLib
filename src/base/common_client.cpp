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
			route->delete_client(std::dynamic_pointer_cast<common_client>(shared_from_this()));
		}
		else {
			route->delete_module(std::dynamic_pointer_cast<common_client>(shared_from_this()));
		}
	}
	if (m_conn_type == passive_conn)
	{
		m_heartbeat_timer->cancel();
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
		route->add_module(std::dynamic_pointer_cast<common_client>(shared_from_this()), 
			module_central_type, ack.central_id());
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
		/*将模块加入到路由表*/
		std::shared_ptr<route> route = server->get_route();
		route->add_module(std::dynamic_pointer_cast<common_client>(shared_from_this()), 
			m_type, m_id);
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
		/*将模块加入到路由表*/
		std::shared_ptr<route> route = server->get_route();
		route->add_module(std::dynamic_pointer_cast<common_client>(shared_from_this()), 
			m_type, m_id);
	}
}

void common_client::handle_heartbeat(proto_msg& msg)
{
	SLOG_DEBUG << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	proto_msg r_msg(cmd_heartbeat_ack);
	write((char *)&r_msg, r_msg.size());
}

void common_client::handle_heartbeat_ack(proto_msg& msg)
{
	SLOG_DEBUG << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	m_wait_heartbeat = false;
}

void common_client::handle_monitor_route(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	std::shared_ptr<module> server = std::dynamic_pointer_cast<module>(m_server);
	if (server)
	{
		auto route = server->get_route();
		proto_msg r_msg(cmd_monitor_route_ack);
		pb::monitor::module_list info;
		info.set_clients_size(route->get_clients_size());
		info.set_type_clients_size(route->get_type_clients_size());
		auto self = shared_from_this();
		auto f_check = [self, this, &info, &r_msg]()
		{
			if (info.ByteSize() > proto_msg::msg_data_length / 2)
			{
				r_msg.serialize_msg(info);
				write((char *)&r_msg, r_msg.size());
				info.Clear();
			}
		};
		auto fn = [self, &info, f_check](std::shared_ptr<common_client> client)
		{
			pb::internal::register_info* r = info.add_mid_clients();
			r->set_id(client->get_id());
			r->set_type(client->get_type());
			r->set_ip(client->get_ip());
			r->set_port(client->get_port());
			f_check();
		};
		route->for_each_mid(fn);
		auto fn1 = [self, &info, f_check](const std::size_t vid, std::shared_ptr<common_client> client)
		{
			info.add_vid_clients(vid);
			f_check();
		};
		route->for_each_vid_clients(fn1);
		auto fn2 = [self, &info, f_check](const route::node& n, std::shared_ptr<common_client> client)
		{
			pb::monitor::node* node = info.add_node_clients();
			node->set_type(n.type);
			node->set_tid(n.tid);
			node->set_uid(n.uid);
			node->set_vid(n.vid);
			f_check();
		};
		route->for_each_node_clients(fn2);
		auto fn3 = [self, &info, f_check](const route::ttnode& ttn, const route::node& n)
		{
			pb::monitor::ttnode_node* ttnn = info.add_ttnode_node();
			pb::monitor::ttnode* ttnode = ttnn->mutable_ttn();
			ttnode->set_type(ttn.type);
			ttnode->set_tid(ttn.tid);
			pb::monitor::node* node = ttnn->mutable_n();
			node->set_type(n.type);
			node->set_tid(n.tid);
			node->set_uid(n.uid);
			node->set_vid(n.vid);
			f_check();
		};
		route->for_each_ttnode_node(fn3);
		auto fn4 = [self, &info, f_check](const std::size_t vid, const route::node& n)
		{
			pb::monitor::vid_node* vnode = info.add_vid_node();
			vnode->set_vid(vid);
			pb::monitor::node* node = vnode->mutable_n();
			node->set_type(n.type);
			node->set_tid(n.tid);
			node->set_uid(n.uid);
			node->set_vid(n.vid);
			f_check();
		};
		route->for_each_vid_node(fn4);
		r_msg.serialize_msg(info);
		write((char *)&r_msg, r_msg.size());
	}
}

/*消息描述*/
std::map<int, std::string> common_client::m_cmd_desc = {
	{ cmd_heartbeat, "heartbeat request" },
	{ cmd_heartbeat_ack, "heartbeat respond" },
	{ cmd_login_request, "client login request" },
	{ cmd_module_logon, "module logon request" },
	{ cmd_module_logon_ack, "module logon respond" },
	{ cmd_broadcast_module_logon, "broadcast module logon" },
	{ cmd_broadcast_module_logon_ack, "broadcast module logon respond" },
	{ cmd_register_info, "register module info" },
	{ cmd_request_vid_range, "gateway request vid range" },
	{ cmd_request_vid_range_ack, "gateway request vid range respond" },
	{ cmd_update_balance_list, "central notice gateway update balance list" },
	{ cmd_update_balance_list_ack, "central notice gateway update balance list respond" },
	{ cmd_create_channel, "user create channel" },
	{ cmd_create_channel_ack, "user create channel respond" },
	{ cmd_delete_channel, "user delete channel" },
	{ cmd_delete_channel_ack, "user delete channel respond" },
	{ cmd_user_disconnection, "user offline" },
	{ cmd_user_disconnection_ack, "user offline respond" },
	{ cmd_interchannel_broadcast, "user broadcast msg in channel" },
	{ cmd_interchannel_broadcast_ack, "user broadcast msg in channel ack" },
	{ cmd_monitor_instruction, "monitor console instruction" },
	{ cmd_monitor_instruction_ack, "monitor console instruction respond" },
	{ cmd_monitor_route, "monitor request route info" },
	{ cmd_monitor_route_ack, "monitor request route info respond" },
	{ cmd_monitor_vid_manage, "monitor request central vid management info" },
	{ cmd_monitor_vid_manage_ack, "monitor request central vid management info respond" },
	{ cmd_monitor_tid_manage, "monitor request balance tid management info" },
	{ cmd_monitor_tid_manage_ack, "monitor request balance tid management info respond" },
	{ cmd_monitor_balance, "monitor request balance's balance info" },
	{ cmd_monitor_balance_ack, "monitor request balance's balance info respond" },
};

void common_client::init(std::shared_ptr<base_server> server)
{
	base_client::init(server);
	set_server(server);
	if (m_conn_type == passive_conn)
	{
		m_heartbeat_timer = std::make_shared<boost::asio::steady_timer>(m_io_context);
		m_heartbeat_timer->expires_from_now(boost::asio::chrono::milliseconds(heartbeat_time));
		m_heartbeat_timer->async_wait(boost::bind(&common_client::send_heartbeat, 
			std::dynamic_pointer_cast<common_client>(shared_from_this()), _1));
	}
	std::shared_ptr<common_client> client = std::dynamic_pointer_cast<common_client>(shared_from_this());
	if (client)
	{
		for (int i = 0; i < cmd_end; i++)
		{
			m_function_set[i] = std::bind(&common_client::handle_nothing, this, std::placeholders::_1);
		}
		m_function_set[cmd_heartbeat] = std::bind(&common_client::handle_heartbeat, this, std::placeholders::_1);
		m_function_set[cmd_heartbeat_ack] = std::bind(&common_client::handle_heartbeat_ack, this, std::placeholders::_1);
		m_function_set[cmd_module_logon_ack] = std::bind(&common_client::handle_module_logon_ack, this, std::placeholders::_1);
		m_function_set[cmd_broadcast_module_logon] = std::bind(&common_client::handle_broadcast_module_logon, this, std::placeholders::_1);
		m_function_set[cmd_register_info] = std::bind(&common_client::handle_register_info, this, std::placeholders::_1);
		m_function_set[cmd_register_info_ack] = std::bind(&common_client::handle_register_info_ack, this, std::placeholders::_1);
		
		m_function_set[cmd_monitor_route] = std::bind(&common_client::handle_monitor_route, this, std::placeholders::_1);
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

void common_client::set_type(uint32_t type)
{
	m_type = type;
}
void common_client::set_id(uint32_t id)
{
	m_id = id;
}
void common_client::send_heartbeat(const boost::system::error_code& ec)
{
	if (!ec)
	{
		if (!m_wait_heartbeat)
		{
			SLOG_DEBUG << "send_heartbeat";
			proto_msg msg(cmd_heartbeat);
			write((char *)&msg, msg.size());
			m_wait_heartbeat = true;
			m_heartbeat_timer->expires_from_now(boost::asio::chrono::milliseconds(heartbeat_time));
			m_heartbeat_timer->async_wait(boost::bind(&common_client::send_heartbeat,
				std::dynamic_pointer_cast<common_client>(shared_from_this()), _1));
		}
	}
}