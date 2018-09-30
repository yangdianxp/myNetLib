#ifndef __BASE_CLIENT_H_
#define __BASE_CLIENT_H_
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "common.h"

class base_client : public std::enable_shared_from_this<base_client>
{
	using tcp = boost::asio::ip::tcp;
	static const unsigned char msg_header_length = sizeof(proto_header);
	static const unsigned int msg_body_length = 1024 * 128;
public:
	base_client(boost::asio::io_context& io_context,
		std::string remote_ip, std::string remote_port);
	base_client(boost::asio::io_context& io_context, tcp::socket socket);
	virtual ~base_client();

	void write(const char *data, int size);
	virtual void dispatch(uint16_t cmd, const char* buffer, std::size_t length);
	virtual void do_read_header();
	virtual void do_read_body();
	virtual void handle_connect_succ();
	virtual void handle_connect_error(boost::system::error_code& ec);
	virtual void handle_write_succ();
	virtual void handle_write_error(boost::system::error_code& ec);
	virtual void handle_msg_header_error(int length);
	virtual void handle_read_error(boost::system::error_code& ec);

	void set_reconnect_time(unsigned int ms);

protected:
	tcp::socket m_socket;
	proto_header m_msg_header;
	char m_msg_body[msg_body_length];

private:
	void do_connect(const tcp::resolver::results_type& endpoints);
	void handle_error();
	void reconnect();

	enum client_type {
		passive_conn = 1,  //被动连接
		active_conn = 2    //主动连接
	};
	client_type m_type;
	boost::asio::io_context& m_io_context;
	tcp::resolver::results_type m_endpoints;
	boost::asio::steady_timer m_reconnect_timer;
	int m_reconnect_time = 0;
};

#endif