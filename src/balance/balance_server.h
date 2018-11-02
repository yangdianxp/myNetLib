#ifndef __BALANCE_SERVER_H__
#define __BALANCE_SERVER_H__
#include "middleware_server.h"
#include "balance_client.h"

class balance_server : public middleware_server<balance_client>
{
	using tcp = boost::asio::ip::tcp;
public:
	balance_server(boost::asio::io_context& io_context, short port);
private:

};


#endif
