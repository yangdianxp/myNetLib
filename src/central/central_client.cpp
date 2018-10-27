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
	std::shared_ptr<central_server> server = std::dynamic_pointer_cast<central_server>(m_server);
	if (server)
	{
		m_id = server->get_unique_mid();
		/*将模块加入到路由表*/
		std::shared_ptr<route> route = server->get_route();
		route->add_module(shared_from_this(), m_type, m_id);
	}
	SLOG_INFO << "module ip:" << m_ip << ", port:" << m_port << " m_id:" << m_id
		<< ", type:" << m_type << " " << config_settings::instance().get_module_name(m_type);
	module_logon_reply();
	broadcast_module_logon();
}

void central_client::module_logon_reply()
{
	std::shared_ptr<central_server> server = std::dynamic_pointer_cast<central_server>(m_server);
	if (server)
	{
		std::shared_ptr<route> route = server->get_route();
		proto_msg ack_msg(cmd_module_logon_ack);
		pb::internal::logon_ack ack;
		ack.set_id(m_id);
		ack.set_central_id(server->get_id());
		/*遍历登录模块需要连接的模块*/
		auto self = shared_from_this();
		auto fn = [self, &ack](std::shared_ptr<base_client> client)
		{
			std::shared_ptr<common_client> common = std::dynamic_pointer_cast<common_client>(client);
			if (common)
			{
				pb::internal::addr* addr = ack.add_link_addr();
				addr->set_ip(common->get_ip());
				addr->set_port(common->get_port());
				addr->set_type(common->get_type());
			}
		};
		if (m_type == module_gateway_type)
		{
			auto gateway_link_type = config_settings::instance().get_gateway_link_type();
			auto it_end = gateway_link_type.end();
			for (auto it = gateway_link_type.begin(); it != it_end; ++it)
			{
				route->for_each_type(*it, fn);
			}
		}
		else if (m_type >= module_media_type)
		{
			auto media_link_type = config_settings::instance().get_media_link_type();
			auto it_end = media_link_type.end();
			for (auto it = media_link_type.begin(); it != it_end; ++it)
			{
				route->for_each_type(*it, fn);
			}
		}
		SLOG_DEBUG << ack.DebugString();
		ack_msg.serialize_msg(ack);
		write((char *)&ack_msg, ack_msg.size());
	}
}

void central_client::broadcast_module_logon()
{
	std::shared_ptr<central_server> server = std::dynamic_pointer_cast<central_server>(m_server);
	if (server)
	{
		proto_msg msg(cmd_broadcast_module_logon);
		pb::internal::addr addr;
		addr.set_ip(m_ip);
		addr.set_port(m_port);
		addr.set_type(m_type);
		msg.serialize_msg(addr);
		auto self = shared_from_this();
		auto fn = [self, &msg](std::shared_ptr<base_client> client)
		{
			client->write((char *)&msg, msg.size());
		};
		std::shared_ptr<route> route = server->get_route();
		switch (m_type)
		{
		case module_login_type:
			route->for_each_type(module_gateway_type, fn);
			break;
		case module_balance_type:
			route->for_each_type(module_gateway_type, fn);
			route->for_each_type(module_media_type, fn);
			break;
		default:
			{
				if (m_type >= module_media_type)
				{
					route->for_each_type(module_gateway_type, fn);
				}
			}
			break;
		}
	}
}

void central_client::handle_request_vid_range(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd] << " m_id:" << m_id;
	std::shared_ptr<central_server> server = std::dynamic_pointer_cast<central_server>(m_server);
	if (server)
	{
		vid_manage::vid_pair pair = server->get_vid_range(m_id);
		proto_msg msg(cmd_request_vid_range_ack);
		pb::internal::vid_range range;
		range.set_begin(pair.first);
		range.set_end(pair.second);
		msg.serialize_msg(range);
		write((char *)&msg, msg.size());
	}
}

void central_client::init(std::shared_ptr<base_server> server)
{
	common_client::init(server);
	config_settings& config_reader = config_settings::instance();
	std::shared_ptr<central_client> client = std::dynamic_pointer_cast<central_client>(shared_from_this());
	if (client)
	{
		m_function_set[cmd_module_logon] = std::bind(&central_client::handle_module_logon, client, std::placeholders::_1);
		m_function_set[cmd_request_vid_range] = std::bind(&central_client::handle_request_vid_range, client, std::placeholders::_1);
	}
}

