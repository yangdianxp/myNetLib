#include "base_server.h"


base_server::base_server(boost::asio::io_context& io_context, short port)
	: m_acceptor(io_context, tcp::endpoint(tcp::v4(), port))
{
	do_accept();
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
			auto session_ptr = std::make_shared<base_session>(std::move(socket),\
				m_acceptor.get_io_context(), m_session_set);
			m_session_set.insert(session_ptr);
			session_ptr->start();
			printf("m_session_cnt<%zd>\n", ++m_session_cnt);
		}

		do_accept();
	});
}