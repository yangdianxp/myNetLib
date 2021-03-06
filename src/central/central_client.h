#ifndef __CENTRAL_CLIENT_H__
#define __CENTRAL_CLIENT_H__
#include "common_client.h"

class central_client : public common_client
{
public:
	central_client(boost::asio::io_context& io_context,
		std::string remote_ip, std::string remote_port);
	central_client(boost::asio::io_context& io_context, tcp::socket socket);

	virtual void handle_error_aux();

	void handle_module_logon(proto_msg& msg);
	void module_logon_reply();
	void broadcast_module_logon();
	void handle_request_vid_range(proto_msg& msg);
	
	void handle_monitor_tv_manage(proto_msg& msg);
	void init(std::shared_ptr<base_server>);
private:
};


#endif
