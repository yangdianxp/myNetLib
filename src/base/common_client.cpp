#include "common_client.h"


common_client::common_client(boost::asio::io_context& io_context,\
	std::string remote_ip, std::string remote_port) :
	base_client(io_context, remote_ip, remote_port)
{

}
common_client::common_client(boost::asio::io_context& io_context, tcp::socket socket) :
	base_client(io_context, std::move(socket))
{

}
common_client::~common_client()
{

}
void common_client::handle_connect_succ()
{
	SLOG_INFO << "connect succ";
	if (m_conn_type == active_conn && m_active_type == module_central_type)
	{
		module_logon();
	}
}
void common_client::module_logon()
{
	config_settings& config_reader = config_settings::instance();
	SLOG_INFO << "logon central, local ip:" << config_reader.get_local_ip() 
		<< " local port:" << config_reader.get_local_port();


}
void common_client::set_active_type(uint32_t type)
{
	m_active_type = type;
}

void common_client::set_server(std::shared_ptr<base_server> server)
{
	m_server = server;
}