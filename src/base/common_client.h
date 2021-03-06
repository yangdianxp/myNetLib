#ifndef __COMMON_CLIENT_H__
#define __COMMON_CLIENT_H__
#include <functional>
#include "base_client.h"
#include "base_server.h"

class base_server;
class common_client : public base_client
{
	static const std::size_t heartbeat_time = 60000;
public:
	common_client(boost::asio::io_context& io_context,
		std::string remote_ip, std::string remote_port);
	common_client(boost::asio::io_context& io_context, tcp::socket socket);
	virtual ~common_client();

	virtual void dispatch(proto_msg& msg);
	virtual void handle_connect_succ();
	void handle_connect_error(boost::system::error_code& ec);
	void handle_write_error(boost::system::error_code& ec);
	void handle_msg_header_error(int length);
	void handle_read_error(boost::system::error_code& ec);
	virtual void handle_error_aux();

	void handle_nothing(proto_msg& msg);

	virtual void handle_module_logon_ack(proto_msg& msg);
	void module_logon();
	void handle_broadcast_module_logon(proto_msg& msg);
	void register_info();
	void handle_register_info(proto_msg& msg);
	void handle_register_info_ack(proto_msg& msg);
	void handle_heartbeat(proto_msg& msg);
	void handle_heartbeat_ack(proto_msg& msg);

	virtual void handle_monitor_route(proto_msg& msg);

	virtual void init(std::shared_ptr<base_server>);
	void set_active_type(uint32_t type);
	void set_server(std::shared_ptr<base_server>);
	uint32_t get_type();
	uint32_t get_id();
	void set_type(uint32_t type);
	void set_id(uint32_t id);
	void send_heartbeat(const boost::system::error_code& ec);
protected:
	/*从属于服务器*/
	std::shared_ptr<base_server> m_server;
	/*消息分发函数集*/
	std::function<void(proto_msg&)> m_function_set[cmd_end];
	/*消息描述*/
	static std::map<int, std::string> m_cmd_desc;
	/*客户端类型*/
	uint32_t m_type = 0;
	/*客户端id, 如果是模块则代表mid, 如果是真正的客户端则代表vid*/
	uint32_t m_id = 0;
private:
	/*client主动连接模块的类型*/
	uint32_t m_active_type = module_none_type;
	std::shared_ptr<boost::asio::steady_timer> m_heartbeat_timer;
	bool m_wait_heartbeat = false;
};

#endif
