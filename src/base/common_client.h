#ifndef __COMMON_CLIENT_H__
#define __COMMON_CLIENT_H__
#include <functional>
#include "base_client.h"
#include "base_server.h"

class common_client : public base_client
{
	using tcp = boost::asio::ip::tcp;
public:
	common_client(boost::asio::io_context& io_context,
		std::string remote_ip, std::string remote_port);
	common_client(boost::asio::io_context& io_context, tcp::socket socket);
	virtual ~common_client();
	void handle_connect_succ();
	void module_logon();

	void init();
	void set_active_type(uint32_t type);
	void set_server(std::shared_ptr<base_server>);
protected:
	/*�����ڷ�����*/
	std::shared_ptr<base_server> m_server;
	/*��Ϣ�ַ�������*/
	std::function<void(proto_msg&)> m_function_set[cmd_end];
private:
	/*client��������ģ�������*/
	uint32_t m_active_type = module_none_type;
};

#endif
