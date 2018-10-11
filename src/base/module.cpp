#include "module.h"

module::module(boost::asio::io_context& io_context, short port) :
	base_server(io_context, port)
{

}

void module::handle_accept_succ(tcp::socket& socket)
{
	auto client = std::make_shared<base_client>(get_io_context(), std::move(socket));
	m_rount.add_client(client);
}