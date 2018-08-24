#ifndef __BASE_CLIENT_H_
#define __BASE_CLIENT_H_
#include <boost/asio.hpp>
#include "common.h"

class base_client
{
	using tcp = boost::asio::ip::tcp;
public:
	base_client(boost::asio::io_context& io_context,
		const tcp::resolver::results_type& endpoints);
	void write();

private:
	void do_connect(const tcp::resolver::results_type& endpoints);
	void do_write();

	boost::asio::io_context& m_io_context;
	tcp::socket m_socket;
	proto_msg m_login_request;
};

#endif