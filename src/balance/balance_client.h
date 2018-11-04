#ifndef __BALANCE_CLIENT_H__
#define __BALANCE_CLIENT_H__
#include "common_client.h"

class balance_client : public common_client
{
public:
	balance_client(boost::asio::io_context& io_context,
		std::string remote_ip, std::string remote_port);
	balance_client(boost::asio::io_context& io_context, tcp::socket socket);

	void handle_create_channel(proto_msg& msg);
	void handle_create_channel_ack(proto_msg& msg);
	void handle_user_disconnection(proto_msg& msg);

	void init(std::shared_ptr<base_server>);
private:
};

#endif