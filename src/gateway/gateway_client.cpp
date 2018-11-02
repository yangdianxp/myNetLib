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
	auto server = std::dynamic_pointer_cast<gateway_server>(m_server);
	if (server)
	{
		server->del_vid(m_id);
	}
	common_client::handle_error_aux();
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
	pb::internal::vid_range range;
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
		msg.serialize_msg(modify);
		auto client = route->get_first_client(module_balance_type);
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
	}
}
