#include "base_server.h"


base_server::base_server(boost::asio::io_context& io_context, short port)
	: m_acceptor(io_context, tcp::endpoint(tcp::v4(), port))
{
	do_accept();
}

base_server::~base_server()
{

}

void base_server::handle_accept_succ(tcp::socket& socket)
{
}

void base_server::handle_accept_error(boost::system::error_code& ec)
{
	SLOG_ERROR << ec.message();
}

boost::asio::io_context& base_server::get_io_context()
{
	return m_acceptor.get_io_context();
}

void base_server::do_accept()
{
	m_acceptor.async_accept(
		[this](boost::system::error_code ec, tcp::socket socket)
	{
		if (!ec)
		{
			handle_accept_succ(socket);
		}
		else {
			handle_accept_error(ec);
		}

		do_accept();
	});           
}