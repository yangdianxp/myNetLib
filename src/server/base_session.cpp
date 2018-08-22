#include "base_session.h"
#include "common.h"

base_session::base_session(tcp::socket socket)
	: m_socket(std::move(socket))
{

}

base_session::~base_session()
{

}

void base_session::start()
{
	do_read_header();
}

int base_session::dispatch()
{
	switch (msg_header.cmd)
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
	login_request request;
	request.ParseFromArray(msg_body, msg_header.length);
	std::cout << request.name() << " " << request.passwd() << std::endl;
	return 0;
}

void base_session::do_read_header()
{
	auto self(shared_from_this());
	boost::asio::async_read(m_socket,
		boost::asio::buffer(&msg_header, msg_header_length),
		[this, self](boost::system::error_code ec, std::size_t /*length*/)
	{
		if (!ec && msg_header.check_msg(msg_body_length))
		{
			do_read_body();
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
		boost::asio::buffer(&msg_body, msg_header.length),
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