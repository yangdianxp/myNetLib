#ifndef __BASE_SERVER__
#define __BASE_SERVER__
#include <memory>
#include <boost/asio.hpp>

class base_server : public std::enable_shared_from_this<base_server>
{
	using tcp = boost::asio::ip::tcp;
public:
	base_server(boost::asio::io_context& io_context, short port);
	virtual ~base_server();
private:
	void do_accept();
	tcp::acceptor m_acceptor;
};

#endif