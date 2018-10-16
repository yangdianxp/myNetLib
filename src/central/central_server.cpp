#include "central_server.h"
#include "central_client.h"

central_server::central_server(boost::asio::io_context& io_context, short port) :
	module(io_context, port)
{

}

void central_server::handle_accept_succ(tcp::socket& socket)
{
	std::shared_ptr<central_client> client = std::make_shared<central_client>(get_io_context(), std::move(socket));
	client->set_server(shared_from_this());
	auto client1 = std::dynamic_pointer_cast<base_client>(client);
	m_route->add_client(client1);
}