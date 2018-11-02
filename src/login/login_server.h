#ifndef __GATEWAY_SERVER_H__
#define __GATEWAY_SERVER_H__
#include "middleware_server.h"
#include "common_client.h"

class login_server : public middleware_server<common_client>
{
	using tcp = boost::asio::ip::tcp;
public:
	login_server(boost::asio::io_context& io_context, short port);

private:

};


#endif
