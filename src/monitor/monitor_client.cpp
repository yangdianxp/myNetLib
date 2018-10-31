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
		std::shared_ptr<monitor_server> server = std::dynamic_pointer_cast<monitor_server>(m_server);
		if (server)
		{
			auto self = shared_from_this();
			auto fn = [self](std::shared_ptr<base_client> client)
			{
				SLOG_INFO << "ip:" << client->get_ip() << " port:" << client->get_port();
			};
			auto route = server->get_route();
			route->for_each_all(fn);
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