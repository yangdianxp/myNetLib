#ifndef __MODULE_H__
#define __MODULE_H__
#include <boost/asio.hpp>
#include "base_server.h"
#include "common_client.h"
#include "route.h"

class module : public base_server
{
public:
	module(boost::asio::io_context& io_context, short port);
	virtual ~module();

	virtual void handle_accept_succ(tcp::socket& socket);
	virtual void connect_remote(std::string ip, std::string port, uint32_t type);

	void init();
	std::shared_ptr<route> get_route();
	void set_route(std::shared_ptr<route> route);
	uint32_t get_type();
	uint32_t get_id();
protected:
	/*路由表*/
	std::shared_ptr<route> m_route;
	/*自身id*/
	uint32_t m_id = 0;
private:
	/*自身模块类型*/
	uint32_t m_type = module_none_type;
};

#endif