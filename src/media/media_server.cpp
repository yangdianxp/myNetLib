#include "media_server.h"
#include "common_client.h"

media_server::media_server(boost::asio::io_context& io_context, short port) :
	middleware_server(io_context, port)
{
	
}
