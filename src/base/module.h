#ifndef __MODULE_H__
#define __MODULE_H__
#include <boost/asio.hpp>
#include "base_server.h"
#include "route.h"

class module : public base_server
{
	using tcp = boost::asio::ip::tcp;
public:
	module(boost::asio::io_context& io_context, short port);

	virtual void handle_accept_succ(tcp::socket& socket);
protected:
private:
	route m_rount;
};

#endif