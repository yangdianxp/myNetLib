#include <boost/bind.hpp>
#include "base_session.h"
#include "common.h"

base_session::base_session(tcp::socket socket, boost::asio::io_context& io_context)
	: m_socket(std::move(socket)), m_msg_timer(io_context, boost::asio::chrono::seconds(1))
{
}

base_session::~base_session()
{

}

void base_session::start()
{
	m_msg_timer.async_wait(boost::bind(&base_session::count_msg, this));
	do_read_header();
}

int base_session::dispatch()
{
	switch (m_msg_header.cmd)
	{
	case cmd_login_request:
		return handle_login_request();
	default:
		break;
	}
	return -1;
}

int base_session::handle_login_request()
{
	pb::login_request request;
	request.ParseFromArray(m_msg_body, m_msg_header.length);
	m_msg_cnt++;
	return 0;
}

void base_session::do_read_header()
{
	auto self(shared_from_this());
	boost::asio::async_read(m_socket,
		boost::asio::buffer(&m_msg_header, msg_header_length),
		[this, self](boost::system::error_code ec, std::size_t /*length*/)
	{
		if (!ec)
		{
			if (m_msg_header.check_msg(msg_body_length))
			{
				do_read_body();
			}
		}
		else
		{
		}
	});
}

void base_session::do_read_body()
{
	auto self(shared_from_this());
	boost::asio::async_read(m_socket,
		boost::asio::buffer(&m_msg_body, m_msg_header.length),
		[this, self](boost::system::error_code ec, std::size_t /*length*/)
	{
		if (!ec)
		{
			dispatch();
			do_read_header();
		}
		else
		{
		}
	});
}

void base_session::count_msg()
{
	printf("m_msg_cnt:%zd, msg len:%zd\n", m_msg_cnt, m_msg_header.length + sizeof(m_msg_header));
	m_msg_cnt = 0;
	m_msg_timer.expires_at(m_msg_timer.expiry() + boost::asio::chrono::seconds(1));
	m_msg_timer.async_wait(boost::bind(&base_session::count_msg, this));
}