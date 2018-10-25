#include "media_server.h"
#include "common_client.h"

media_server::media_server(boost::asio::io_context& io_context, short port) :
	module(io_context, port)
{
	
}
