#ifndef __MONITOR_CLIENT_H__
#define __MONITOR_CLIENT_H__
#include "common_client.h"

class monitor_client : public common_client
{
public:
	monitor_client(boost::asio::io_context& io_context,
		std::string remote_ip, std::string remote_port);
	monitor_client(boost::asio::io_context& io_context, tcp::socket socket);

	void handle_monitor_route_ack(proto_msg& msg);
	void handle_monitor_tv_manage_ack(proto_msg& msg);
	void handle_monitor_balance_ack(proto_msg& msg);

	void handle_cmd_monitor_instruction(proto_msg& msg);
	/*控制台命令处理程序*/
	void monitor_instruction_proc(std::string cmd, int id);
	void handle_monitor_list();
	void handle_monitor_route(int id);
	void handle_monitor_tvmanage(int id, std::string cmd);
	void handle_monitor_balance(int id);

	void init(std::shared_ptr<base_server>);
private:
};

#endif