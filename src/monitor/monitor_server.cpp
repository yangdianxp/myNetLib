#include "monitor_server.h"
#include "monitor_client.h"

monitor_server::monitor_server(boost::asio::io_context& io_context, short port) :
	middleware_server(io_context, port)
{
	
}
