#include "base_server.h"
#include "base_session.h"

base_server::base_server(boost::asio::io_context& io_context, short port)
	: m_acceptor(io_context, tcp::endpoint(tcp::v4(), port))
{

}

base_server::~base_server()
{

}

void base_server::do_accept()
{
	m_acceptor.async_accept(
		[this](boost::system::error_code ec, tcp::socket socket)
	{
		if (!ec)
		{
			std::make_shared<base_session>(std::move(socket))->start();
		}

		do_accept();
	});
}