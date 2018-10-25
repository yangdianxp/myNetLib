#ifndef __BALANCE_SERVER_H__
#define __BALANCE_SERVER_H__
#include "module.h"

class balance_server : public module
{
	using tcp = boost::asio::ip::tcp;
public:
	balance_server(boost::asio::io_context& io_context, short port);

private:

};


#endif
