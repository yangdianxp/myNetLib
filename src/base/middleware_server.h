#ifndef __MIDDLEWARE_SERVER_H__
#define __MIDDLEWARE_SERVER_H__
#include "module.h"

template<typename Client = module, typename Route = route>
class middleware_server : public module
{
public:
	middleware_server(boost::asio::io_context& io_context, short port) :
		module(io_context, port) 
	{
		set_route(std::make_shared<Route>());
	}
	virtual void handle_accept_succ(tcp::socket& socket)
	{
		std::shared_ptr<Client> client = std::make_shared<Client>(get_io_context(), std::move(socket));
		client->init(shared_from_this());
		m_route->add_client(client);
	}
	virtual void connect_remote(std::string ip, std::string port, uint32_t type)
	{
		SLOG_INFO << "connect ip:" << ip << " port:" << port << " type:" << type << " "
			<< config_settings::instance().get_module_name(type);
		std::shared_ptr<Client> client = std::make_shared<Client>(get_io_context(), ip, port);
		connect_remote_sub(client, type);
	}
};

#endif