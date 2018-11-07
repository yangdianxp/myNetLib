#include "balance_client.h"
#include "balance_server.h"

balance_client::balance_client(boost::asio::io_context& io_context,
	std::string remote_ip, std::string remote_port) :
	common_client(io_context, remote_ip, remote_port)
{

}
balance_client::balance_client(boost::asio::io_context& io_context, tcp::socket socket) :
	common_client(io_context, std::move(socket))
{

}
void balance_client::handle_create_channel(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	pb::external::modify_channel modify;
	msg.parse(modify);
	SLOG_DEBUG << modify.DebugString();
	auto server = std::dynamic_pointer_cast<balance_server>(m_server);
	if (server)
	{
		auto route = std::dynamic_pointer_cast<balance_route>(server->get_route());
		route::ttnode ttn(modify.type(), modify.tid());
		route::node n(modify.type(), modify.tid(), modify.uid(), modify.vid());
		auto media = route->get_ttnode(ttn);
		if (media)
		{
			route->add_node(media, n);
			media->write((char *)&msg, msg.size());
			return;
		}
		auto media1 = route->get_first_media(modify.type());
		if (media1)
		{
			route->add_node(media1, n);
			media1->write((char *)&msg, msg.size());
			return;
		}
	}
}
void balance_client::handle_create_channel_ack(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	pb::external::modify_channel modify;
	msg.parse(modify);
	SLOG_DEBUG << modify.DebugString();
	auto server = std::dynamic_pointer_cast<balance_server>(m_server);
	if (server)
	{
		auto route = server->get_route();
		auto gateway = route->get_client(modify.dst());
		if (gateway)
		{
			if (modify.rslt() == pb::external::modify_channel::rslt_succ)
			{
				gateway->write((char *)&msg, msg.size());
			}
			else {
				route::node n(modify.type(), modify.tid(), modify.uid(), modify.vid());
				route->delete_node(n);
				gateway->write((char *)&msg, msg.size());
			}
		}
	}
}
void balance_client::handle_user_disconnection(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd] << ", vid" << msg.m_vid;
	auto server = std::dynamic_pointer_cast<balance_server>(m_server);
	if (server)
	{
		auto route = server->get_route();
		route->delete_node(msg.m_vid);
	}
}

void balance_client::handle_monitor_balance(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	
}

void balance_client::init(std::shared_ptr<base_server> server)
{
	common_client::init(server);
	std::shared_ptr<balance_client> client = std::dynamic_pointer_cast<balance_client>(shared_from_this());
	if (client)
	{
		m_function_set[cmd_create_channel] = std::bind(&balance_client::handle_create_channel, client, std::placeholders::_1);
		m_function_set[cmd_create_channel_ack] = std::bind(&balance_client::handle_create_channel_ack, client, std::placeholders::_1);
		m_function_set[cmd_user_disconnection] = std::bind(&balance_client::handle_user_disconnection, client, std::placeholders::_1);
		m_function_set[cmd_monitor_balance] = std::bind(&balance_client::handle_monitor_balance, client, std::placeholders::_1);
	}
}