#ifndef __BASE_CLIENT_H__
#define __BASE_CLIENT_H__
#include <deque>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "common.h"
#include "base_server.h"

using boost::asio::io_context;
using boost::asio::ip::tcp;

class base_server;
class base_client : public std::enable_shared_from_this<base_client>
{
	static const unsigned char msg_header_length = sizeof(proto_header);
	static const uint32_t buffer_len = 1024 * 64;
public:
	base_client(boost::asio::io_context& io_context,
		std::string remote_ip, std::string remote_port);
	base_client(boost::asio::io_context& io_context, tcp::socket socket);
	virtual ~base_client();

	void write(const char *data, int size);
	void do_write();
	virtual void dispatch(proto_msg& msg);
	virtual void do_read_header();
	virtual void do_read_body();
	virtual void handle_connect_succ();
	virtual void handle_connect_error(boost::system::error_code& ec);
	virtual void handle_write_succ();
	virtual void handle_write_error(boost::system::error_code& ec);
	virtual void handle_msg_header_error(int length);
	virtual void handle_read_error(boost::system::error_code& ec);

	virtual void init(std::shared_ptr<base_server>);
	void set_reconnect_time(unsigned int ms);

	std::string get_ip();
	uint32_t get_port();
protected:
	tcp::socket m_socket;
	char m_recv_buffer[buffer_len];
	std::size_t m_recv_index = 0;
	std::deque<std::string> m_send_msgs;
	std::string m_send_buffer;

	enum client_type {
		passive_conn = 1,  //被动连接
		active_conn = 2    //主动连接
	};
	client_type m_conn_type;
	int m_reconnect_time = 0;

	std::string m_ip;
	uint32_t m_port;
protected:
	boost::asio::io_context& m_io_context;

private:
	void do_connect(const tcp::resolver::results_type& endpoints);
	void handle_error();
	void reconnect(const boost::system::error_code& ec);

	tcp::resolver::results_type m_endpoints;
	std::shared_ptr<boost::asio::steady_timer> m_reconnect_timer;
};

#endif