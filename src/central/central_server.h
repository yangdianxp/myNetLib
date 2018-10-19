#ifndef __CENTRAL_SERVER_H__
#define __CENTRAL_SERVER_H__
#include "module.h"
#include "unique_code.h"

class central_server : public module
{
	using tcp = boost::asio::ip::tcp;
public:
	central_server(boost::asio::io_context& io_context, short port);
	virtual void handle_accept_succ(tcp::socket& socket);
	void connect_remote();

	unique_code& get_unique_mid();
private:
	unique_code m_unique_mid;
};


#endif
