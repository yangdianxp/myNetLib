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
	auto session_ptr = std::make_shared<base_client>(m_acceptor.get_io_context(),\
		std::move(socket));
	m_clients.insert(session_ptr);
}

void base_server::handle_accept_error(boost::system::error_code& ec)
{
	SLOG_ERROR << ec.message();
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