#ifndef __MODULE_H__
#define __MODULE_H__
#include <boost/asio.hpp>
#include "base_server.h"
#include "common_client.h"
#include "route.h"

class module : public base_server
{
	using tcp = boost::asio::ip::tcp;
public:
	module(boost::asio::io_context& io_context, short port);
	virtual ~module();

	virtual void handle_accept_succ(tcp::socket& socket);

	void init();
protected:
	/*·�ɱ�*/
	route m_rount;
private:
	/*����ģ������*/
	uint32_t m_type = module_none_type;
};

#endif