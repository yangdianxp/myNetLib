#ifndef __COMMON_CLIENT_H__
#define __COMMON_CLIENT_H__
#include <functional>
#include "base_client.h"
#include "base_server.h"

class common_client : public base_client
{
public:
	common_client(boost::asio::io_context& io_context,
		std::string remote_ip, std::string remote_port);
	common_client(boost::asio::io_context& io_context, tcp::socket socket);
	virtual ~common_client();

	virtual void dispatch(proto_msg& msg);
	void handle_connect_succ();
	void handle_nothing(proto_msg& msg);
	void handle_module_logon_ack(proto_msg& msg);
	void module_logon();
	void handle_broadcast_module_logon(proto_msg& msg);
	void register_info();
	void handle_register_info(proto_msg& msg);
	void handle_register_info_ack(proto_msg& msg);

	virtual void init(std::shared_ptr<base_server>);
	void set_active_type(uint32_t type);
	void set_server(std::shared_ptr<base_server>);
	uint32_t get_type();
protected:
	/*�����ڷ�����*/
	std::shared_ptr<base_server> m_server;
	/*��Ϣ�ַ�������*/
	std::function<void(proto_msg&)> m_function_set[cmd_end];
	/*��Ϣ����*/
	static std::map<int, std::string> m_cmd_desc;
	/*�ͻ�������*/
	uint32_t m_type = 0;
	/*�ͻ���id, �����ģ�������mid, ����������Ŀͻ��������vid*/
	uint32_t m_id = 0;
private:
	/*client��������ģ�������*/
	uint32_t m_active_type = module_none_type;
};

#endif
