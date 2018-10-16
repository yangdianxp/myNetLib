#ifndef __CENTRAL_SERVER_H__
#define __CENTRAL_SERVER_H__
#include "module.h"

class central_server : public module
{
	using tcp = boost::asio::ip::tcp;
public:
	central_server(boost::asio::io_context& io_context, short port);
	virtual void handle_accept_succ(tcp::socket& socket);
	void connect_remote();
private:
	
};


#endif
