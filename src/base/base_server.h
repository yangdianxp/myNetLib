#ifndef __BASE_SERVER__
#define __BASE_SERVER__
#include <memory>
#include <set>
#include <boost/asio.hpp>
#include "base_client.h"

class base_server : public std::enable_shared_from_this<base_server>
{
	
	using tcp = boost::asio::ip::tcp;
public:
	base_server(boost::asio::io_context& io_context, short port);
	virtual ~base_server();

	virtual void handle_accept_succ(tcp::socket& socket);
	virtual void handle_accept_error(boost::system::error_code& ec);
private:
	void do_accept();
	tcp::acceptor m_acceptor;
	std::set<std::shared_ptr<base_client>> m_clients;
};

#endif