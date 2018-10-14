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
	std::shared_ptr<base_client> client = std::make_shared<common_client>(get_io_context(), std::move(socket));
	m_route->add_client(client);
}

void module::init()
{
	config_settings& config_reader = config_settings::instance();
	m_type = config_reader.get_type();
}

void module::set_route(std::shared_ptr<route> route)
{
	m_route = route;
}