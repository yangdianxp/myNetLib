#ifndef __USER_CLIENT_H__
#define __USER_CLIENT_H__
#include "common_client.h"

class user_client : public common_client
{
public:
	user_client(boost::asio::io_context& io_context,
		std::string remote_ip, std::string remote_port);
	user_client(boost::asio::io_context& io_context, tcp::socket socket);

	void handle_connect_succ();
	void handle_create_channel_ack(proto_msg& msg);
	void handle_delete_channel_ack(proto_msg& msg);
	void handle_interchannel_broadcast_ack(proto_msg& msg);

	void handle_task_timer();
	void init(std::shared_ptr<base_server> server);
	void set_user_info(std::size_t tid, std::size_t uid);
private:
	std::size_t m_type = module_media_type;
	std::size_t m_tid = 1000;
	std::size_t m_uid = 10000;

	boost::asio::steady_timer m_task_timer;
};

#endif
