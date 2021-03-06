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

void central_client::handle_error_aux()
{
	auto server = std::dynamic_pointer_cast<central_server>(m_server);
	if (server)
	{
		server->del_unique_mid(m_id);
		if (m_type == module_gateway_type)
		{
			auto& manage = server->get_vid_manage();
			manage.repay(m_id);
		}
		else if (m_type == module_balance_type)
		{
			auto& manage = server->get_tid_manage();
			manage.repay(m_id);
		}
	}
	common_client::handle_error_aux();
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
		route->add_module(std::dynamic_pointer_cast<common_client>(shared_from_this()), 
			m_type, m_id);
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
		auto fn = [self, &ack](std::shared_ptr<common_client> client)
		{
			pb::internal::addr* addr = ack.add_link_addr();
			addr->set_ip(client->get_ip());
			addr->set_port(client->get_port());
			addr->set_type(client->get_type());
		};
		switch (m_type)
		{
		case module_gateway_type:
		{
			auto& gateway_link_type = config_settings::instance().get_gateway_link_type();
			auto it_end = gateway_link_type.end();
			for (auto it = gateway_link_type.begin(); it != it_end; ++it)
			{
				route->for_each_type(*it, fn);
			}
			pb::internal::balance_list list;
			auto& tid_manage = server->get_tid_manage();
			auto f1 = [self, &list](std::pair<const std::size_t, range_manage::pair>& p)
			{
				pb::internal::mid_range* mr = list.add_range();
				mr->set_mid(p.first);
				pb::internal::range* r = mr->mutable_range();
				r->set_begin(p.second.first);
				r->set_end(p.second.second);
			};
			tid_manage.for_each_already_assigned(f1);
			proto_msg msg_list(cmd_update_balance_list);
			msg_list.serialize_msg(list);
			write((char *)&msg_list, msg_list.size());
			break;
		}
		case module_login_type:
		{
			auto& login_link_type = config_settings::instance().get_login_link_type();
			auto it_end = login_link_type.end();
			for (auto it = login_link_type.begin(); it != it_end; ++it)
			{
				route->for_each_type(*it, fn);
			}
			break;
		}
		case module_balance_type:
		{
			auto& balance_link_type = config_settings::instance().get_balance_link_type();
			auto it_end = balance_link_type.end();
			for (auto it = balance_link_type.begin(); it != it_end; ++it)
			{
				route->for_each_type(*it, fn);
			}
			break;
		}
		default:
		{
			if (m_type >= module_media_type)
			{
				auto& media_link_type = config_settings::instance().get_media_link_type();
				auto it_end = media_link_type.end();
				for (auto it = media_link_type.begin(); it != it_end; ++it)
				{
					route->for_each_type(*it, fn);
				}
			}
			break;
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
		auto fn = [self, &msg](std::shared_ptr<common_client> client)
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
		{
			route->for_each_type(module_gateway_type, fn);
			for (int i = module_media_type; i < module_end_type; ++i)
			{
				route->for_each_type(i, fn);
			}
			auto& tid_manage = server->get_tid_manage();
			range_manage::pair pair = tid_manage.get(m_id);
			pb::internal::balance_list list;
			pb::internal::mid_range* mr = list.add_range();
			mr->set_mid(m_id);
			pb::internal::range* r = mr->mutable_range();
			r->set_begin(pair.first);
			r->set_end(pair.second);
			proto_msg msg_list(cmd_update_balance_list);
			msg_list.serialize_msg(list);
			auto f1 = [self, &msg_list](std::shared_ptr<common_client> client)
			{
				client->write((char *)&msg_list, msg_list.size());
			};
			route->for_each_type(module_gateway_type, f1);
			break;
		}
		case module_monitor_type:
			route->for_each_type(module_gateway_type, fn);
			route->for_each_type(module_login_type, fn);
			route->for_each_type(module_balance_type, fn);
			for (int i = module_media_type; i < module_end_type; ++i)
			{
				route->for_each_type(i, fn);
			}
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
		range_manage::pair pair = server->get_vid_range(m_id);
		proto_msg r_msg(cmd_request_vid_range_ack);
		pb::internal::range range;
		range.set_begin(pair.first);
		range.set_end(pair.second);
		r_msg.serialize_msg(range);
		write((char *)&r_msg, r_msg.size());
	}
}

void central_client::handle_monitor_tv_manage(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	auto server = std::dynamic_pointer_cast<central_server>(m_server);
	if (server)
	{
		std::function<range_manage&()> fn;
		if (msg.m_cmd == cmd_monitor_vid_manage)
		{
			fn = std::bind(&central_server::get_vid_manage, server);
		}
		else if (msg.m_cmd == cmd_monitor_tid_manage)
		{
			fn = std::bind(&central_server::get_tid_manage, server);
		}
		auto& m = fn();
		pb::monitor::range_manage manage;
		manage.set_index(m.get_index());
		manage.set_unit_size(m.get_unit_size());
		auto f1 = [&manage](range_manage::pair& p)
		{
			pb::internal::range* r = manage.add_inventory();
			r->set_begin(p.first);
			r->set_end(p.second);
		};
		m.for_each_inventory(f1);
		auto f2 = [&manage](std::pair<const std::size_t, range_manage::pair>& p)
		{
			pb::internal::mid_range* mr = manage.add_already_assigned();
			mr->set_mid(p.first);
			pb::internal::range* r = mr->mutable_range();
			r->set_begin(p.second.first);
			r->set_end(p.second.second);
		};
		m.for_each_already_assigned(f2);
		proto_msg ack_msg;
		if (msg.m_cmd == cmd_monitor_vid_manage)
		{
			ack_msg.m_cmd = cmd_monitor_vid_manage_ack;
		}
		else if (msg.m_cmd == cmd_monitor_tid_manage){
			ack_msg.m_cmd = cmd_monitor_tid_manage_ack;
		}
		ack_msg.serialize_msg(manage);
		write((char *)&ack_msg, ack_msg.size());
	}
}

void central_client::init(std::shared_ptr<base_server> server)
{
	common_client::init(server);
	config_settings& config_reader = config_settings::instance();
	std::shared_ptr<central_client> client = std::dynamic_pointer_cast<central_client>(shared_from_this());
	if (client)
	{
		m_function_set[cmd_module_logon] = std::bind(&central_client::handle_module_logon, this, std::placeholders::_1);
		m_function_set[cmd_request_vid_range] = std::bind(&central_client::handle_request_vid_range, this, std::placeholders::_1);
		m_function_set[cmd_monitor_vid_manage] = std::bind(&central_client::handle_monitor_tv_manage, this, std::placeholders::_1);
		m_function_set[cmd_monitor_tid_manage] = std::bind(&central_client::handle_monitor_tv_manage, this, std::placeholders::_1);
	}
}

