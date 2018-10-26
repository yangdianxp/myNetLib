#ifndef __GATEWAY_CLIENT_H__
#define __GATEWAY_CLIENT_H__
#include "common_client.h"

class gateway_client : public common_client
{
public:
	gateway_client(boost::asio::io_context& io_context,
		std::string remote_ip, std::string remote_port);
	gateway_client(boost::asio::io_context& io_context, tcp::socket socket);

private:

};

#endif