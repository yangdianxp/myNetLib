#ifndef __MONITOR_SERVER_H__
#define __MONITOR_SERVER_H__
#include "middleware_server.h"
#include "monitor_client.h"
#include "unique_code.h"

class monitor_server : public middleware_server<monitor_client>
{
	using tcp = boost::asio::ip::tcp;
public:
	monitor_server(boost::asio::io_context& io_context, short port);

private:
};


#endif
