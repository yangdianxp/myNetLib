#ifndef __MONITOR_CLIENT_H__
#define __MONITOR_CLIENT_H__
#include "common_client.h"

class monitor_client : public common_client
{
public:
	monitor_client(boost::asio::io_context& io_context,
		std::string remote_ip, std::string remote_port);
	monitor_client(boost::asio::io_context& io_context, tcp::socket socket);

	void handle_cmd_monitor_instruction(proto_msg& msg);

	void init(std::shared_ptr<base_server>);
private:

};

#endif