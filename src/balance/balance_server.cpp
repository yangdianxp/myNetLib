#include "balance_server.h"
#include "common_client.h"

balance_server::balance_server(boost::asio::io_context& io_context, short port) :
	module(io_context, port)
{
	
}
