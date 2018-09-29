#include <boost/bind.hpp>
#include "base_client.h"

base_client::base_client(boost::asio::io_context& io_context,
	std::string remote_ip, std::string remote_port)
	: m_type(active_conn), m_io_context(io_context), m_socket(io_context),
	m_reconnect_timer(io_context)
{
	tcp::resolver resolver(io_context);
	m_endpoints = resolver.resolve(remote_ip, remote_port);
	do_connect(m_endpoints);
}

base_client::base_client(boost::asio::io_context& io_context, tcp::socket socket)
	: m_type(passive_conn), m_io_context(io_context), m_socket(std::move(socket)),
	m_reconnect_timer(io_context)
{
	do_read_header();
}

base_client::~base_client()
{

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
			handle_error();
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
			handle_error();
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
			handle_error();
		}
	});
}

void base_client::handle_connect_succ()
{
	SLOG_DEBUG << "connect succ";
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

void base_client::set_reconnect_time(unsigned int ms)
{
	if (m_type == active_conn)
	{
		m_reconnect_time = ms;
	}
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
			handle_error();
		}
	});
}

void base_client::handle_error()
{
	m_socket.close();
	if (m_reconnect_time > 0)
	{
		m_reconnect_timer.expires_from_now(boost::asio::chrono::milliseconds(m_reconnect_time));
		m_reconnect_timer.async_wait(boost::bind(&base_client::reconnect, shared_from_this()));
	}
}

void base_client::reconnect()
{
	SLOG_INFO << "start reconnect";
	do_connect(m_endpoints);
}

