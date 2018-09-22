#ifndef __BASE_SESSION_H__
#define __BASE_SESSION_H__
#include <boost/asio.hpp>
#include <memory>
#include "common.h"

class base_session : public std::enable_shared_from_this<base_session>
{
	using tcp = boost::asio::ip::tcp;
	static const unsigned char msg_header_length = sizeof(proto_header);
	static const unsigned int msg_body_length = 1024 * 128;

public:
	base_session(tcp::socket socket, boost::asio::io_service& io_context,
		std::set<std::shared_ptr<base_session>>& session_set);
	virtual ~base_session();

	void start();
	virtual int dispatch();
	virtual int handle_login_request();
private:
	void do_read_header();
	void do_read_body();
	void count_msg();

	tcp::socket m_socket;
	proto_header m_msg_header;
	char m_msg_body[msg_body_length];
	size_t m_msg_cnt = 0;
	boost::asio::steady_timer m_msg_timer;
	std::set<std::shared_ptr<base_session>>& m_session_set;
};

#endif
