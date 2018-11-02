#include "login_server.h"
#include "common_client.h"

login_server::login_server(boost::asio::io_context& io_context, short port) :
	middleware_server(io_context, port)
{
	
}
