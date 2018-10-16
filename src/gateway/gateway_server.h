#ifndef __GATEWAY_SERVER_H__
#define __GATEWAY_SERVER_H__
#include "module.h"

class gateway_server : public module
{
	using tcp = boost::asio::ip::tcp;
public:
	gateway_server(boost::asio::io_context& io_context, short port);

	void connect_remote();
private:

};


#endif
