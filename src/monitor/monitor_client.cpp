#include <sstream>
#include "monitor_client.h"
#include "monitor_server.h"
monitor_client::monitor_client(boost::asio::io_context& io_context, \
	std::string remote_ip, std::string remote_port) :
	common_client(io_context, remote_ip, remote_port)
{

}

monitor_client::monitor_client(boost::asio::io_context& io_context, tcp::socket socket) :
	common_client(io_context, std::move(socket))
{

}

void monitor_client::handle_monitor_route_ack(proto_msg& msg)
{
	//SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	pb::monitor::module_list info;
	msg.parse(info);
	if (info.clients_size() > 0 || info.type_clients_size() > 0 || info.mid_clients_size() > 0)
	{
		SLOG_INFO << std::endl
			<< "clients_size:" << info.clients_size() << std::endl
			<< "type_clients_size:" << info.type_clients_size() << std::endl
			<< "mid_clients_size:" << info.mid_clients_size();
		for (int i = 0; i < info.mid_clients_size(); ++i)
		{
			const pb::internal::register_info& r = info.mid_clients(i);
			SLOG_INFO << i << " mid:" << r.id() << " type:" << config_settings::instance().get_module_name(r.type())
				<< " ip:" << r.ip() << " port:" << r.port();
		}
	}
	if (info.vid_clients_size() > 0)
	{
		SLOG_INFO << "vid_clients_size:" << info.vid_clients_size();
		for (int i = 0; i < info.vid_clients_size(); ++i)
		{
			SLOG_INFO << i << " vid:" << info.vid_clients(i);
		}
	}
	if (info.node_clients_size() > 0)
	{
		SLOG_INFO << "node_clients_size:" << info.node_clients_size();
		for (int i = 0; i < info.node_clients_size(); ++i)
		{
			const pb::monitor::node& n = info.node_clients(i);
			SLOG_INFO << i << " type:" << n.type() << " tid:" << n.tid() << " uid:"
				<< n.uid() << " vid:" << n.vid();
		}
	}
	if (info.ttnode_node_size() > 0)
	{
		SLOG_INFO << "ttnode_node_size:" << info.ttnode_node_size();
		for (int i = 0; i < info.ttnode_node_size(); ++i)
		{
			const pb::monitor::ttnode_node& ttnn = info.ttnode_node(i);
			const pb::monitor::ttnode& ttn = ttnn.ttn();
			const pb::monitor::node& n = ttnn.n();
			SLOG_INFO << i << " type:" << ttn.type() << " tid:" << ttn.tid() << " --->"
				<< " type:" << n.type() << " tid:" << n.tid() << " uid:"
				<< n.uid() << " vid:" << n.vid();
		}
	}
	if (info.vid_node_size() > 0)
	{
		SLOG_INFO << "vid_node_size:" << info.vid_node_size();
		for (int i = 0; i < info.vid_node_size(); ++i)
		{
			const pb::monitor::vid_node& vnode = info.vid_node(i);
			const pb::monitor::node& n = vnode.n();
			SLOG_INFO << i << " vid:" << vnode.vid() << " --->"
				<< " type:" << n.type() << " tid:" << n.tid() << " uid:"
				<< n.uid() << " vid:" << n.vid();
		}
	}
}
void monitor_client::handle_monitor_tv_manage_ack(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	pb::monitor::range_manage manage;
	msg.parse(manage);
	SLOG_INFO << std::endl
		<< "index:" << manage.index() << std::endl
		<< "unit_size:" << manage.unit_size();
	SLOG_INFO << "inventory_size:" << manage.inventory_size();
	for (int i = 0; i < manage.inventory_size(); ++i)
	{
		const pb::internal::range& r = manage.inventory(i);
		SLOG_INFO << i << " begin:" << r.begin() << " end:" << r.end();
	}
	SLOG_INFO << "already_assigned_size:" << manage.already_assigned_size();
	for (int i = 0; i < manage.already_assigned_size(); ++i)
	{
		const pb::internal::mid_range& r = manage.already_assigned(i);
		SLOG_INFO << i << " mid:" << r.mid() << " begin:" << r.range().begin() 
			<< " end:" << r.range().end();
	}
}

void monitor_client::handle_monitor_balance_ack(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	pb::monitor::balance_info binfo;
	msg.parse(binfo);
	SLOG_INFO << "info_size:" << binfo.info_size();
	for (int i = 0; i < binfo.info_size(); ++i)
	{
		const pb::monitor::mid_ref& mr = binfo.info(i);
		SLOG_INFO << i << " mid:" << mr.mid() << " ref:" << mr.ref();
	}
}

void monitor_client::handle_cmd_monitor_instruction(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	pb::monitor::cmd proto_cmd;
	msg.parse(proto_cmd);
	std::string content = proto_cmd.content();
	SLOG_INFO << "content:" << content;
	std::stringstream ss(content);
	std::string cmd;
	int id = -1;
	ss >> cmd >> id;
	monitor_instruction_proc(cmd, id);
}

void monitor_client::monitor_instruction_proc(std::string cmd, int id)
{
	if (cmd == "list")
	{
		handle_monitor_list();
	}
	else if (cmd == "help")
	{
		SLOG_INFO << std::endl
			<< "==============help==============" << std::endl
			<< "list" << std::endl
			<< "route [id]" << std::endl
			<< "vmanage [id] --->just for central" << std::endl
			<< "tmanage [id] --->just for central and gateway" << std::endl 
			<< "balance [id] --->just for balance";
	}
	else if (id < 0)
	{
		SLOG_WARNING << "id is illegality.";
	}
	else if (cmd == "route")
	{
		handle_monitor_route(id);
	}
	else if (cmd == "vmanage")
	{
		handle_monitor_tvmanage(id, cmd);
	}
	else if (cmd == "tmanage")
	{
		handle_monitor_tvmanage(id, cmd);
	}
	else if (cmd == "balance")
	{
		handle_monitor_balance(id);
	}
	else
	{
		SLOG_WARNING << "unsupported commands.";
	}
}
void monitor_client::handle_monitor_list()
{
	std::shared_ptr<monitor_server> server = std::dynamic_pointer_cast<monitor_server>(m_server);
	if (server)
	{
		auto self = shared_from_this();
		auto fn = [self](std::shared_ptr<common_client> client)
		{
			std::string type = config_settings::instance().get_module_name(client->get_type());
			SLOG_INFO << "id:" << client->get_id() << " type:" << type
				<< " ip:" << client->get_ip() << " port:" << client->get_port();
		};
		auto route = server->get_route();
		route->for_each_mid(fn);
	}
}
void monitor_client::handle_monitor_route(int id)
{
	std::shared_ptr<monitor_server> server = std::dynamic_pointer_cast<monitor_server>(m_server);
	if (server)
	{
		auto route = server->get_route();
		auto client = route->get_client(id);
		if (client)
		{
			proto_msg msg(cmd_monitor_route);
			client->write((char *)&msg, msg.size());
		}
		else {
			SLOG_WARNING << "module does not exist.";
		}
	}
}
void monitor_client::handle_monitor_tvmanage(int id, std::string cmd)
{
	std::shared_ptr<monitor_server> server = std::dynamic_pointer_cast<monitor_server>(m_server);
	if (server)
	{
		auto route = server->get_route();
		auto client = route->get_client(id);
		if (client)
		{
			auto client1 = std::dynamic_pointer_cast<monitor_client>(client);
			if (client1)
			{
				if (cmd == "vmanage")
				{
					if (client1->get_type() == module_central_type)
					{
						proto_msg msg(cmd_monitor_vid_manage);
						client1->write((char *)&msg, msg.size());
					}
					else {
						SLOG_WARNING << "module is not central.";
					}
				}
				else if (cmd == "tmanage")
				{
					if (client1->get_type() == module_central_type || client1->get_type() == module_gateway_type)
					{
						proto_msg msg(cmd_monitor_tid_manage);
						client1->write((char *)&msg, msg.size());
					}
					else {
						SLOG_WARNING << "module is not central or gateway.";
					}
				}
				
			}
		}
		else {
			SLOG_WARNING << "module does not exist.";
		}
	}
}
void monitor_client::handle_monitor_balance(int id)
{
	std::shared_ptr<monitor_server> server = std::dynamic_pointer_cast<monitor_server>(m_server);
	if (server)
	{
		auto route = server->get_route();
		auto client = route->get_client(id);
		if (client)
		{
			auto client1 = std::dynamic_pointer_cast<monitor_client>(client);
			if (client1)
			{
				if (client1->get_type() == module_balance_type)
				{
					proto_msg msg(cmd_monitor_balance);
					client1->write((char *)&msg, msg.size());
				}
				else {
					SLOG_WARNING << "module is not balance.";
				}
			}
		}
		else {
			SLOG_WARNING << "module does not exist.";
		}
	}
}

void monitor_client::init(std::shared_ptr<base_server> server)
{
	common_client::init(server);
	std::shared_ptr<monitor_client> client = std::dynamic_pointer_cast<monitor_client>(shared_from_this());
	if (client)
	{
		m_function_set[cmd_monitor_instruction] = std::bind(&monitor_client::handle_cmd_monitor_instruction, this, std::placeholders::_1);
		m_function_set[cmd_monitor_route_ack] = std::bind(&monitor_client::handle_monitor_route_ack, this, std::placeholders::_1);
		m_function_set[cmd_monitor_vid_manage_ack] = std::bind(&monitor_client::handle_monitor_tv_manage_ack, this, std::placeholders::_1);
		m_function_set[cmd_monitor_tid_manage_ack] = std::bind(&monitor_client::handle_monitor_tv_manage_ack, this, std::placeholders::_1);
		m_function_set[cmd_monitor_balance_ack] = std::bind(&monitor_client::handle_monitor_balance_ack, this, std::placeholders::_1);
	}
}
