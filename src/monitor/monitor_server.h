#ifndef __MONITOR_SERVER_H__
#define __MONITOR_SERVER_H__
#include "module.h"
#include "unique_code.h"

class monitor_server : public module
{
	using tcp = boost::asio::ip::tcp;
public:
	monitor_server(boost::asio::io_context& io_context, short port);
	virtual void handle_accept_succ(tcp::socket& socket);
	virtual void connect_remote(std::string ip, std::string port, uint32_t type);

private:
};


#endif
