#ifndef __BASE_SERVER_H__
#define __BASE_SERVER_H__
#include <memory>
#include <set>
#include <boost/asio.hpp>
#include "base_session.h"

class base_server : public std::enable_shared_from_this<base_server>
{
	
	using tcp = boost::asio::ip::tcp;
public:
	base_server(boost::asio::io_context& io_context, short port);
	virtual ~base_server();
private:
	void do_accept();
	tcp::acceptor m_acceptor;
	std::set<std::shared_ptr<base_session>> m_session_set;
	size_t m_session_cnt = 0;
};

#endif