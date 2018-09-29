#include "base_client.h"


base_client::base_client(boost::asio::io_context& io_context,
	const tcp::resolver::results_type& endpoints)
	: m_io_context(io_context), m_socket(io_context)
{
	do_connect(endpoints);
}

void base_client::write(const char *data, int size)
{
	boost::asio::async_write(m_socket,
		boost::asio::buffer(data, size),
		[this](boost::system::error_code ec, std::size_t /*length*/)
	{
		if (!ec)
		{
			handle_write_succ();
		}
		else
		{
			handle_write_error(ec);
			m_socket.close();
		}
	});
}

void base_client::dispatch(unsigned short cmd)
{

}

void base_client::do_read_header()
{
	boost::asio::async_read(m_socket,
		boost::asio::buffer(&m_msg_header, msg_header_length),
		[this](boost::system::error_code ec, std::size_t length)
	{
		if (!ec)
		{
			if (m_msg_header.check_msg(msg_body_length))
			{
				do_read_body();
			}
			else {
				handle_msg_header_error(length);
			}
		}
		else
		{
			handle_read_error(ec);
			m_socket.close();
		}
	});
}

void base_client::do_read_body()
{
	boost::asio::async_read(m_socket,
		boost::asio::buffer(&m_msg_body, m_msg_header.length),
		[this](boost::system::error_code ec, std::size_t /*length*/)
	{
		if (!ec)
		{
			dispatch(m_msg_header.cmd);
			do_read_header();
		}
		else
		{
			handle_read_error(ec);
			m_socket.close();
		}
	});
}

void base_client::handle_connect_succ()
{

}

void base_client::handle_connect_error(boost::system::error_code& ec)
{
	SLOG_ERROR << ec.message();
}

void base_client::handle_write_succ()
{

}

void base_client::handle_write_error(boost::system::error_code& ec)
{
	SLOG_ERROR << ec.message();
}

void base_client::handle_msg_header_error(int length)
{
	SLOG_ERROR << length;
}

void base_client::handle_read_error(boost::system::error_code& ec)
{
	SLOG_ERROR << ec.message();
}

void base_client::do_connect(const tcp::resolver::results_type& endpoints)
{
	boost::asio::async_connect(m_socket, endpoints,
		[this](boost::system::error_code ec, tcp::endpoint)
	{
		if (!ec)
		{
			handle_connect_succ();
			do_read_header();
		}
		else {
			handle_connect_error(ec);
		}
	});
}