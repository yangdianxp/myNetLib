#include "media_client.h"
#include "media_server.h"

media_client::media_client(boost::asio::io_context& io_context, \
	std::string remote_ip, std::string remote_port) :
	common_client(io_context, remote_ip, remote_port)
{

}

media_client::media_client(boost::asio::io_context& io_context, tcp::socket socket) :
	common_client(io_context, std::move(socket))
{

}

void media_client::handle_create_channel(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	pb::external::modify_channel modify;
	msg.parse(modify);
	SLOG_DEBUG << modify.DebugString();
	proto_msg ack(cmd_create_channel_ack);
	auto server = std::dynamic_pointer_cast<media_server>(m_server);
	if (server)
	{
		auto route = server->get_route();
		auto gateway = route->get_client(modify.src());
		if (gateway)
		{
			route::node n(modify.type(), modify.tid(), modify.uid(), modify.vid());
			route->add_node(gateway, n);
			std::size_t dst = modify.src();
			modify.set_src(server->get_id());
			modify.set_dst(dst);
			modify.set_rslt(pb::external::modify_channel::rslt_succ);
			ack.serialize_msg(modify);
			write((char *)&ack, ack.size());
			return;
		}
	}
	modify.set_rslt(pb::external::modify_channel::rslt_fail);
	ack.serialize_msg(modify);
	write((char *)&ack, ack.size());
}
void media_client::handle_delete_channel(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd] << ", vid:" << msg.m_vid;
	pb::external::modify_channel modify;
	msg.parse(modify);
	SLOG_DEBUG << modify.DebugString();
	modify.set_rslt(pb::external::modify_channel::rslt_fail);
	auto server = std::dynamic_pointer_cast<media_server>(m_server);
	if (server)
	{
		route::node n(modify.type(), modify.tid(), modify.uid(), modify.vid());
		auto route = server->get_route();
		route->delete_node(n);
		modify.set_rslt(pb::external::modify_channel::rslt_succ);
	}
	msg.m_cmd = cmd_delete_channel_ack;
	msg.serialize_msg(modify);
	write((char *)&msg, msg.size());
}
void media_client::handle_user_disconnection(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd] << ", vid" << msg.m_vid;
	auto server = std::dynamic_pointer_cast<media_server>(m_server);
	if (server)
	{
		auto route = server->get_route();
		route->delete_node(msg.m_vid);
	}
}
void media_client::handle_interchannel_broadcast(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	pb::external::info info;
	msg.parse(info);
	SLOG_INFO << info.DebugString();
	auto server = std::dynamic_pointer_cast<media_server>(m_server);
	if (server)
	{
		auto route = server->get_route();
		route::ttnode ttn(msg.m_type, msg.m_tid);
		msg.m_cmd = cmd_interchannel_broadcast_ack;
		route::node original(msg.m_type, msg.m_tid, msg.m_uid, msg.m_vid);
		auto self = shared_from_this();
		auto fn = [self, &msg, original](std::shared_ptr<common_client> client, const route::node& n)
		{
			if (!(original == n))
			{
				msg.m_vid = n.vid;
				client->write((char *)&msg, msg.size());
			}
		};
		route->for_each_ttnode(ttn, fn);
	}
}

void media_client::init(std::shared_ptr<base_server> server)
{
	common_client::init(server);
	std::shared_ptr<media_client> client = std::dynamic_pointer_cast<media_client>(shared_from_this());
	if (client)
	{
		m_function_set[cmd_create_channel] = std::bind(&media_client::handle_create_channel, client, std::placeholders::_1);
		m_function_set[cmd_delete_channel] = std::bind(&media_client::handle_delete_channel, client, std::placeholders::_1);
		m_function_set[cmd_interchannel_broadcast] = std::bind(&media_client::handle_interchannel_broadcast, client, std::placeholders::_1);
		m_function_set[cmd_user_disconnection] = std::bind(&media_client::handle_user_disconnection, client, std::placeholders::_1);
	}
}