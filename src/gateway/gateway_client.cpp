#include "gateway_client.h"
#include "gateway_server.h"
gateway_client::gateway_client(boost::asio::io_context& io_context, \
	std::string remote_ip, std::string remote_port) :
	common_client(io_context, remote_ip, remote_port)
{

}

gateway_client::gateway_client(boost::asio::io_context& io_context, tcp::socket socket) :
	common_client(io_context, std::move(socket))
{

}

void gateway_client::handle_error_aux()
{
	if (m_type == module_user_type)
	{
		auto server = std::dynamic_pointer_cast<gateway_server>(m_server);
		if (server)
		{
			auto route = server->get_route();
			route->delete_vid(std::dynamic_pointer_cast<common_client>(shared_from_this()));
			std::set<std::shared_ptr<common_client>> medias;
			auto self = shared_from_this();
			auto fn = [self, &medias](std::shared_ptr<common_client> client)
			{
				medias.insert(client);
			};
			route->for_each_vid(m_id, fn);
			proto_msg msg(cmd_user_disconnection, m_id);
			for (auto media : medias)
			{
				media->write((char *)&msg, msg.size());
			}
			auto balance = route->get_first_client(module_balance_type);
			if (balance)
			{
				balance->write((char *)&msg, msg.size());
			}
			route->delete_node(m_id);
			server->del_vid(m_id);
		}
	}
	else {
		common_client::handle_error_aux();
	}
}

void gateway_client::handle_module_logon_ack(proto_msg& msg)
{
	SLOG_DEBUG << "handle_module_logon_ack";
	common_client::handle_module_logon_ack(msg);
	proto_msg req(cmd_request_vid_range);
	write((char *)&req, req.size());
}

void gateway_client::handle_request_vid_range_ack(proto_msg& msg)
{
	pb::internal::range range;
	msg.parse(range);
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd] << ", vid range begin:" << range.begin()
		<< ", end:" << range.end();
	auto server = std::dynamic_pointer_cast<gateway_server>(m_server);
	if (server)
	{
		server->set_vid_range(range.begin(), range.end());
	}
}
void gateway_client::handle_create_channel(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	auto server = std::dynamic_pointer_cast<gateway_server>(m_server);
	if (server)
	{
		auto route = server->get_route();
		pb::external::modify_channel modify;
		msg.parse(modify);
		modify.set_vid(m_id);
		modify.set_src(server->get_id());
		SLOG_DEBUG << modify.DebugString();
		route::node n(modify.type(), modify.tid(), modify.uid(), modify.vid());
		if (!route->find_node(n))
		{
			route->add_node(std::shared_ptr<common_client>(), n);
			msg.serialize_msg(modify);
			auto client = route->get_first_client(module_balance_type);
			if (client)
			{
				client->write((char *)&msg, msg.size());
			}
		}
		else {
			SLOG_WARNING << "this channel already exists. type:" << modify.type() << " tid:" << modify.tid()
				<< " uid:" << modify.uid() << " vid:" << modify.vid();
			modify.set_rslt(pb::external::modify_channel::rslt_succ);
			msg.serialize_msg(modify);
			write((char *)&msg, msg.size());
		}
	}
}

void gateway_client::handle_create_channel_ack(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	auto server = std::dynamic_pointer_cast<gateway_server>(m_server);
	if (server)
	{
		auto route = server->get_route();
		pb::external::modify_channel modify;
		msg.parse(modify);
		route::node n(modify.type(), modify.tid(), modify.uid(), modify.vid());
		route->delete_node(n);
		if (modify.rslt() == pb::external::modify_channel::rslt_succ)
		{
			auto media = route->get_client(modify.src());
			if (media)
			{
				route->add_node(media, n);
			}
		}
		auto client = route->get_vid(modify.vid());
		if (client)
		{
			client->write((char *)&msg, msg.size());
		}
	}
}
void gateway_client::handle_interchannel_broadcast(proto_msg& msg)
{
	auto server = std::dynamic_pointer_cast<gateway_server>(m_server);
	if (server)
	{
		msg.m_vid = m_id;
		auto route = server->get_route();
		route::node n(msg.m_type, msg.m_tid, msg.m_uid, msg.m_vid);
		auto media = route->get_node(n);
		if (media)
		{
			media->write((char *)&msg, msg.size());
		}
	}
}
void gateway_client::handle_interchannel_broadcast_ack(proto_msg& msg)
{
	auto server = std::dynamic_pointer_cast<gateway_server>(m_server);
	if (server)
	{
		auto route = server->get_route();
		auto client = route->get_vid(msg.m_vid);
		if (client)
		{
			client->write((char *)&msg, msg.size());
		}
	}
}

void gateway_client::init(std::shared_ptr<base_server> server)
{
	common_client::init(server);
	std::shared_ptr<gateway_client> client = std::dynamic_pointer_cast<gateway_client>(shared_from_this());
	if (client)
	{
		m_function_set[cmd_module_logon_ack] = std::bind(&gateway_client::handle_module_logon_ack, client, std::placeholders::_1);
		m_function_set[cmd_request_vid_range_ack] = std::bind(&gateway_client::handle_request_vid_range_ack, client, std::placeholders::_1);
		m_function_set[cmd_create_channel] = std::bind(&gateway_client::handle_create_channel, client, std::placeholders::_1);
		m_function_set[cmd_create_channel_ack] = std::bind(&gateway_client::handle_create_channel_ack, client, std::placeholders::_1);
		m_function_set[cmd_interchannel_broadcast] = std::bind(&gateway_client::handle_interchannel_broadcast, client, std::placeholders::_1);
		m_function_set[cmd_interchannel_broadcast_ack] = std::bind(&gateway_client::handle_interchannel_broadcast_ack, client, std::placeholders::_1);
	}
}
