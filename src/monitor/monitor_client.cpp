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
		SLOG_INFO << "==============help==============" << std::endl
			<< "list" << std::endl
			<< "route [id]";
	}
	else if (id < 0)
	{
		SLOG_WARNING << "id is illegality.";
	}
	else if (cmd == "route")
	{
		handle_monitor_route(id);
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
		auto fn = [self](std::shared_ptr<base_client> client)
		{
			std::shared_ptr<monitor_client> monitor = std::dynamic_pointer_cast<monitor_client>(client);
			if (monitor)
			{
				std::string type = config_settings::instance().get_module_name(monitor->get_type());
				SLOG_INFO << "id:" << monitor->get_id() << " type:" << type
					<< " ip:" << monitor->get_ip() << " port:" << monitor->get_port();
			}
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

void monitor_client::init(std::shared_ptr<base_server> server)
{
	common_client::init(server);
	std::shared_ptr<monitor_client> client = std::dynamic_pointer_cast<monitor_client>(shared_from_this());
	if (client)
	{
		m_function_set[cmd_monitor_instruction] = std::bind(&monitor_client::handle_cmd_monitor_instruction, client, std::placeholders::_1);
	}
}
