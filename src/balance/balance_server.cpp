#include "balance_server.h"
#include "balance_client.h"
#include "balance_route.h"

balance_server::balance_server(boost::asio::io_context& io_context, short port) :
	middleware_server(io_context, port)
{
	set_route(std::make_shared<balance_route>());
}
