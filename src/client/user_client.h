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
private:
};

#endif
