#ifndef __COMMON_CLIENT_H__
#define __COMMON_CLIENT_H__
#include "base_client.h"

class common_client : public base_client
{
	using tcp = boost::asio::ip::tcp;
public:
	common_client(boost::asio::io_context& io_context,
		std::string remote_ip, std::string remote_port);
	common_client(boost::asio::io_context& io_context, tcp::socket socket);
	virtual ~common_client();
	void handle_connect_succ();
	void module_log_on();
	void set_active_type(uint32_t type);
private:
	/*client��������ģ�������*/
	uint32_t m_active_type = module_none_type;
};

#endif
