#ifndef __BASE_SERVER__
#define __BASE_SERVER__
#include <set>
#include <boost/asio.hpp>
#include "base_client.h"

class base_server : public std::enable_shared_from_this<base_server>
{
public:
	base_server(boost::asio::io_context& io_context, short port);
	virtual ~base_server();

	virtual void handle_accept_succ(tcp::socket& socket);
	virtual void handle_accept_error(boost::system::error_code& ec);

	std::string get_ip();
	std::size_t get_port();
protected:
	boost::asio::io_context& get_io_context();
	
private:
	void do_accept();
	std::string m_ip;
	std::size_t m_port;

	tcp::acceptor m_acceptor;
	std::set<std::shared_ptr<base_client>> m_clients;
};

#endif