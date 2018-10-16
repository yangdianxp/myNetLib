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

void module::connect_remote()
{

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