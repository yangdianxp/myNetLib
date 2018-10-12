#include "central_server.h"

central_server::central_server(boost::asio::io_context& io_context, short port) :
	module(io_context, port)
{

}