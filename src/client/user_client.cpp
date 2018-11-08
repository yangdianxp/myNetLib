#include <sstream>
#include "user_client.h"

user_client::user_client(boost::asio::io_context& io_context,
	std::string remote_ip, std::string remote_port) :
	common_client(io_context, remote_ip, remote_port), m_task_timer(io_context)
{

}
user_client::user_client(boost::asio::io_context& io_context, tcp::socket socket) :
	common_client(io_context, std::move(socket)), m_task_timer(io_context)
{

}
void user_client::handle_connect_succ()
{
	pb::external::modify_channel modify;
	modify.set_type(m_type);
	modify.set_tid(m_tid);
	modify.set_uid(m_uid);
	proto_msg msg(cmd_create_channel);
	msg.serialize_msg(modify);
	write((char *)&msg, msg.size());
}

void user_client::handle_create_channel_ack(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	pb::external::modify_channel modify;
	msg.parse(modify);
	SLOG_DEBUG << modify.DebugString();
	if (modify.rslt() == pb::external::modify_channel::rslt_succ)
	{
		proto_msg msg(cmd_interchannel_broadcast, m_type, m_tid, m_uid);
		std::stringstream ss;
		ss << "hello world. ";
		pb::external::info info;
		info.set_data("hello world.");
		msg.serialize_msg(info);
		for (int i = 0; i < 10; ++i)
		{
			write((char *)&msg, msg.size());
		}
		m_task_timer.expires_from_now(boost::asio::chrono::milliseconds(5000));
		m_task_timer.async_wait(boost::bind(&user_client::handle_task_timer, 
			std::dynamic_pointer_cast<user_client>(shared_from_this())));
	}
}
void user_client::handle_interchannel_broadcast_ack(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	pb::external::info info;
	msg.parse(info);
	SLOG_DEBUG << info.DebugString();
}

void user_client::handle_task_timer()
{
	SLOG_DEBUG << "handle_task_timer";

}

void user_client::init(std::shared_ptr<base_server> server)
{
	common_client::init(server);
	std::shared_ptr<user_client> client = std::dynamic_pointer_cast<user_client>(shared_from_this());
	if (client)
	{
		m_function_set[cmd_create_channel_ack] = std::bind(&user_client::handle_create_channel_ack, client, std::placeholders::_1);
		m_function_set[cmd_interchannel_broadcast_ack] = std::bind(&user_client::handle_interchannel_broadcast_ack, client, std::placeholders::_1);
	}
}
