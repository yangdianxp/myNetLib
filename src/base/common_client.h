#ifndef __COMMON_CLIENT_H__
#define __COMMON_CLIENT_H__
#include "base_client.h"

class common_client : public base_client
{
	using tcp = boost::asio::ip::tcp;
public:
	/*client主动连接模块的类型*/
	enum client_active_type {
		active_none_type = 0,
		active_central_type = 1
	};
	common_client(boost::asio::io_context& io_context,
		std::string remote_ip, std::string remote_port);
	common_client(boost::asio::io_context& io_context, tcp::socket socket);
	virtual ~common_client();
	void handle_connect_succ();
	void module_log_on();
	void set_active_type(client_active_type type);
private:
	client_active_type m_active_type = active_none_type;
};

#endif
