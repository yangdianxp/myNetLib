#include "base_client.h"


base_client::base_client(boost::asio::io_context& io_context,
	const tcp::resolver::results_type& endpoints, 
	std::set<std::shared_ptr<base_client>>& client_set)
	: m_io_context(io_context),
	m_socket(io_context), m_client_set(client_set)
{
	do_connect(endpoints);
}

void base_client::write()
{
	m_login_request.cmd = cmd_login_request;
	pb::login_request login_request_proto;
	login_request_proto.set_name("yangdian");
	login_request_proto.set_passwd("123456");
	m_login_request.serialize_msg(login_request_proto);
	do_write();
}

void base_client::do_connect(const tcp::resolver::results_type& endpoints)
{
	boost::asio::async_connect(m_socket, endpoints,
		[this, &endpoints](boost::system::error_code ec, tcp::endpoint)
	{
		if (!ec)
		{
			printf("connect succ\n");
			//write();
		}
		else {
			std::cout << "connect error:" << ec.message() << std::endl;
		}
		if (m_client_set.size() < 100000)
		{
			m_client_set.insert(std::make_shared<base_client>(m_io_context, endpoints, m_client_set));
		}
	});
}

void base_client::do_write()
{
	boost::asio::async_write(m_socket,
		boost::asio::buffer(&m_login_request,
			m_login_request.size()),
		[this](boost::system::error_code ec, std::size_t /*length*/)
	{
		if (!ec)
		{
			do_write();
		}
		else
		{
			m_socket.close();
		}
	});
}