#include "gateway_server.h"
#include "common_client.h"

gateway_server::gateway_server(boost::asio::io_context& io_context, short port) :
	module(io_context, port)
{
	
}
