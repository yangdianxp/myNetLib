#ifndef __GATEWAY_SERVER_H__
#define __GATEWAY_SERVER_H__
#include "module.h"

class login_server : public module
{
	using tcp = boost::asio::ip::tcp;
public:
	login_server(boost::asio::io_context& io_context, short port);

private:

};


#endif
