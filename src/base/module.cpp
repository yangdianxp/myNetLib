#include "module.h"

module::module(boost::asio::io_context& io_context, short port) :
	base_server(io_context, port), m_route(new route())
{
	init();
}
module::~module()
{

}

void module::handle_accept_succ(tcp::socket& socket)
{
	std::shared_ptr<common_client> client = std::make_shared<common_client>(get_io_context(), std::move(socket));
	client->init(shared_from_this());
	m_route->add_client(client);
}

void module::connect_remote(std::string ip, std::string port, uint32_t type)
{
	SLOG_INFO << "connect ip:" << ip << " port:" << port << " type:" << type << " " 
		<< config_settings::instance().get_module_name(type);
	std::shared_ptr<common_client> client = std::make_shared<common_client>(get_io_context(), ip, port);
	client->set_reconnect_time(3000);
	client->set_active_type(type);
	client->init(shared_from_this());
	m_route->add_client(client);
}

void module::init()
{
	config_settings& config_reader = config_settings::instance();
	m_type = config_reader.get_type();
}

std::shared_ptr<route> module::get_route()
{
	return m_route;
}

void module::set_route(std::shared_ptr<route> route)
{
	m_route = route;
}

uint32_t module::get_type()
{
	return m_type;
}

uint32_t module::get_id()
{
	return m_id;
}

void module::set_id(uint32_t id)
{
	m_id = id;
}