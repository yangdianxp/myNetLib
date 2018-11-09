#ifndef __MEDIA_CLIENT_H__
#define __MEDIA_CLIENT_H__
#include "common_client.h"
class media_client : public common_client 
{
public:
	media_client(boost::asio::io_context& io_context,
		std::string remote_ip, std::string remote_port);
	media_client(boost::asio::io_context& io_context, tcp::socket socket);

	void handle_create_channel(proto_msg& msg);
	void handle_delete_channel(proto_msg& msg);
	void handle_user_disconnection(proto_msg& msg);
	void handle_interchannel_broadcast(proto_msg& msg);
	void init(std::shared_ptr<base_server>);

private:
};

#endif