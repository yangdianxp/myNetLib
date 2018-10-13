#include "module.h"

module::module(boost::asio::io_context& io_context, short port) :
	base_server(io_context, port)
{

}
module::~module()
{

}

void module::handle_accept_succ(tcp::socket& socket)
{
	std::shared_ptr<base_client> client = std::make_shared<common_client>(get_io_context(), std::move(socket));
	m_rount.add_client(client);
}

void module::init()
{
	config_settings& config_reader = config_settings::instance();
	m_type = 
}