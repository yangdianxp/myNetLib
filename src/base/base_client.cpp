#include <boost/bind.hpp>
#include "base_client.h"

base_client::base_client(boost::asio::io_context& io_context,
	std::string remote_ip, std::string remote_port)
	: m_socket(io_context), m_conn_type(active_conn), m_io_context(io_context)
{
	m_ip = remote_ip;
	m_port = std::stoi(remote_port);
	tcp::resolver resolver(io_context);
	m_endpoints = resolver.resolve(remote_ip, remote_port);
}

base_client::base_client(boost::asio::io_context& io_context, tcp::socket socket)
	: m_socket(std::move(socket)), m_conn_type(passive_conn), m_io_context(io_context)
{
	
}

base_client::~base_client()
{
}

void base_client::write(const char *data, int size)
{
	m_send_msgs.push_back(std::string(data, size));
	if (m_send_buffer.empty())
	{
		do_write();
	}
	
}
void base_client::do_write()
{
	auto self(shared_from_this());
	for (auto n : m_send_msgs)
	{
		m_send_buffer += n;
	}
	m_send_msgs.clear();
	boost::asio::async_write(m_socket, boost::asio::buffer(m_send_buffer),
		[this, self](boost::system::error_code ec, std::size_t /*length*/)
	{
		if (!ec)
		{
			handle_write_succ();
			m_send_buffer.clear();
			if (!m_send_msgs.empty())
			{
				do_write();
			}
		}
		else
		{
			handle_write_error(ec);
			handle_error();
		}
	});
}

void base_client::dispatch(proto_msg& msg)
{

}

void base_client::do_read_header()
{
	auto self(shared_from_this());
	m_socket.async_read_some(boost::asio::buffer(&m_recv_buffer[m_recv_index], buffer_len - m_recv_index),
		[this, self](boost::system::error_code ec, std::size_t length)
	{
		if (!ec)
		{
			m_recv_index += length;
			std::size_t index = 0;
			while (index + sizeof(proto_header) <= m_recv_index)
			{
				proto_msg* msg = (proto_msg*)&m_recv_buffer[index];
				if (msg->check_msg())
				{
					if (index + msg->size() <= m_recv_index)
					{
						dispatch(*msg);
						index += msg->size();
					}
					else {
						break;
					}
				}
				else {
					handle_msg_header_error(length);
					return;
				}
			}
			if (index > 0)
			{
				m_recv_index = m_recv_index - index;
				memcpy(m_recv_buffer, &m_recv_buffer[index], m_recv_index);
			}
			do_read_header();
		}
		else
		{
			handle_read_error(ec);
			handle_error();
		}
	});

	
	/*boost::asio::async_read(m_socket,
		boost::asio::buffer(&m_msg, msg_header_length),
		[this, self](boost::system::error_code ec, std::size_t length)
	{
		if (!ec)
		{
			if (m_msg.check_msg())
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
	});*/
}

void base_client::do_read_body()
{
	/*auto self(shared_from_this());
	boost::asio::async_read(m_socket,
		boost::asio::buffer(m_msg.m_data, m_msg.m_length),
		[this, self](boost::system::error_code ec, std::size_t)
	{
		if (!ec)
		{
			dispatch(m_msg);
			do_read_header();
		}
		else
		{
			handle_read_error(ec);
			handle_error();
		}
	});*/
}

void base_client::handle_connect_succ()
{
	SLOG_INFO << "connect succ";
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

void base_client::init(std::shared_ptr<base_server>)
{
	m_reconnect_timer = std::make_shared<boost::asio::steady_timer>(m_io_context);
	if (active_conn == m_conn_type)
	{
		do_connect(m_endpoints);
	}
	else if (passive_conn == m_conn_type){
		do_read_header();
	}
}

void base_client::set_reconnect_time(unsigned int ms)
{
	if (active_conn == m_conn_type)
	{
		m_reconnect_time = ms;
	}
}

std::string base_client::get_ip()
{
	return m_ip;
}

uint32_t base_client::get_port()
{
	return m_port;
}

void base_client::do_connect(const tcp::resolver::results_type& endpoints)
{
	auto self(shared_from_this());
	boost::asio::async_connect(m_socket, endpoints,
		[this, self](boost::system::error_code ec, tcp::endpoint)
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
		m_reconnect_timer->expires_from_now(boost::asio::chrono::milliseconds(m_reconnect_time));
		m_reconnect_timer->async_wait(boost::bind(&base_client::reconnect, shared_from_this(), _1));
	}
}

void base_client::reconnect(const boost::system::error_code& ec)
{
	if (!ec)
	{
		SLOG_INFO << "start reconnect";
		do_connect(m_endpoints);
	}
}

